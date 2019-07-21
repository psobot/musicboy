/**
  ******************************************************************************
  * @author  Peter Sobot (@psobot).
  * @version V1.2.0
  * @date    31-August-2018
  * @brief   Interrupt handlers.
  *          The interrupt handler for the rising flag trigger is defined here.
  *          It handles the read and write operations of the gameboy to the
  *          cartridge.
  *          Based on code by @dhole, modified heavily.
  ******************************************************************************
  */

#include "lib/stm32f4xx_exti.h"
#include "lib/repeat.h"

#include "cart_emulation.h"

#include "data/rom.h"
#include "data/boot_logo.h"
#include "audio_constants.h"

/*
 * Macros to relate the GPIO and the functionality
 */
#define BUS_RD (GPIOC->IDR & (1 << 2))
#define BUS_WR (GPIOC->IDR & (1 << 3))

#define PD_ GPIOD->IDR
#define PB_ GPIOB->IDR
#define PC_ GPIOC->IDR

/*
 * On the STM32F446ZE, we're using:
 * GPIOC:    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
 * ADDR BUS:                         X  X  X  X
 * GPIOD:    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
 * ADDR BUS: X  X  X  X  X  X  X  X              X  X  X  X
*/
#define ADDR_IN ((PD_ & 0xF0FF) | (PC_ & 0x0F00))
#define DATA_IN (GPIOE->IDR >> 8)
#define DATA_OUT GPIOE->ODR
#define SET_DATA_MODE_IN GPIOE->MODER = 0x00000000;
#define SET_DATA_MODE_OUT GPIOE->MODER = 0x55550000;

uint8_t rom_bank;

// Memory "shared" between the GB and STM32
// not readable by the GB, though. (Could be, but isn't to
// save cycles because we don't use that for anything)
uint8_t SHARED_MEMORY[4096] = {0};

static inline void mbc1_bank_switch(uint16_t addr, uint8_t data) {
	if (addr >= 0x2000 && addr < 0x4000) {
		/* ROM Bank Number */
		data &= 0x1F;
		rom_bank = (rom_bank & 0xE0) | data;
		if (data == 0x00) {
			rom_bank |= 0x01;
		}
	}
}

/* Write cartridge operation for MBC1 */
static inline void mbc1_write(uint16_t addr, uint8_t data) {
	if (addr >= 0xA000 && addr <= 0xAFFF) {
		SHARED_MEMORY[addr - 0xA000] = data;
	}

	mbc1_bank_switch(addr, data);
}

volatile uint32_t ticks;
volatile uint8_t number_of_times_logo_read = 0;
volatile uint16_t first_logo_read_ticks = 0;
volatile uint16_t second_logo_read_ticks = 0;

volatile enum Device device = Unknown;

/* Read cartridge operation for MBC1 */
static inline uint8_t mbc1_read(uint16_t addr) {
	if (addr < 0x4000) {

		if (addr == 0x104) {
			number_of_times_logo_read++;
			if (number_of_times_logo_read == 1) {
				first_logo_read_ticks = ticks;
			}
		}

		switch (device) {
			case Unknown:
				return rom_gb[addr];
			case DMG:
				if (number_of_times_logo_read < 2) {
					return boot_logo_bin[addr - 0x104];
				} else {
					return rom_gb[addr];
				}
			case CGB:
				if (number_of_times_logo_read == 3) {
					if (addr == 0x133) {
						number_of_times_logo_read++;
					}
					return boot_logo_bin[addr - 0x104];
				} else {
					return rom_gb[addr];
				}
		}

	} else if (addr < 0x8000) {
		/* 16KB ROM Bank 01-7F */
		return rom_gb[addr + 0x4000 * (rom_bank - 1)];
	}
	return 0x00;
}

/* Handle PC0 interrupt (rising edge of the gameboy CLK) */
void EXTI0_IRQHandler(void) {
	uint16_t addr;
	uint8_t data;

	uint32_t enablestatus;
	enablestatus =  EXTI->IMR & EXTI_Line0;

	if (((EXTI->PR & EXTI_Line0) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET)) {
		/* Do stuff on trigger */

		/* Wait 10 NOPs, until the ADDR is ready in the bus */
		REP(1,3,asm("NOP"););
		/* Read ADDR from the bus */
		addr = ADDR_IN;

		if (BUS_RD || !BUS_WR) {
			/* Write operation */

			/* Wait 30 NOPs, until the DATA is ready in the bus */
			REP(3,2,asm("NOP"););
			/* Read DATA from the bus */
			data = DATA_IN;
			/* Write data to cartridge at addr */
			mbc1_write(addr, data);
		} else {
			/* Read operation */

			/* Set the GPIOE in output mode */
			SET_DATA_MODE_OUT;
			/* Output the data read at addr through GPIOE */
			DATA_OUT = ((uint16_t)mbc1_read(addr)) << 8;
			/* Wait 14 NOPs, until the gameboy has read the DATA
			 * in the bus */
			REP(1,4,asm("NOP"););
			/* Set the GPIOE back to input mode */
			SET_DATA_MODE_IN;
		}
	}
	/* Clear interrupt flag */
	EXTI->PR = EXTI_Line0;
	// EXTI_ClearITPendingBit(EXTI_Line0);
}
