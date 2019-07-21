/**
  ******************************************************************************
  * @author  Eduard S.
  * @version V1.0.0
  * @date    23-December-2014
  * @brief   Main Program body.
  *          Initialization of the GPIOs.
  ******************************************************************************
*/

#include "lib/stm32f4xx_exti.h"
#include "lib/stm32f4xx_gpio.h"
#include "lib/stm32f4xx_rcc.h"
#include "lib/stm32f4xx_syscfg.h"
#include "lib/stm32f4xx_tim.h"
#include "lib/stm32f4xx_dac.h"
#include "lib/stm32f4xx_dma.h"
#include "lib/system_stm32f4xx.h"
#include "lib/misc.h"
#include "lib/spi_flash.h"

#include "lib/repeat.h"

#include <stdbool.h>

#include "audio.h"
#include "cart_emulation.h"
#include "game_state.h"
#include "rom_patch.h"

#define RedLEDOn  (GPIOB->ODR |= (1 << 14))
#define RedLEDOff (GPIOB->ODR &= !(1 << 14))

GPIO_InitTypeDef  GPIO_InitStructure;

volatile extern unsigned char rom_gb[];

extern uint8_t rom_bank;

/* Configure GPIO PC0 to trigger interrupt on rise */
void configure_clock_interrupt(void) {
  EXTI_InitTypeDef EXTI_InitStruct;
  NVIC_InitTypeDef NVIC_InitStruct;

  /* Enable clock for SYSCFG */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Tell system that you will use PC0 for EXTI_Line0 */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0);

  /* PC0 is connected to EXTI_Line0 */
  EXTI_InitStruct.EXTI_Line = EXTI_Line0;
  /* Enable interrupt */
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
  /* Interrupt mode */
  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
  /* Triggers on rising and falling edge */
  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
  /* Add to EXTI */
  EXTI_Init(&EXTI_InitStruct);

  /* Add IRQ vector to NVIC */
  /* PC0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
  NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
  /* Set priority */
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
  /* Set sub priority */
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
  /* Enable interrupt */
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  /* Add to NVIC */
  NVIC_Init(&NVIC_InitStruct);
}

/* Input Signals GPIO pins on CLK -> PC0, RD -> PC2, WR -> PC3 */
void config_gpio_sig(void) {
  /* GPIOC Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  /* Configure GPIO Settings */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/* Input/Output data GPIO pins on PE{8..15} */
void config_gpio_data(void) {
  /* GPIOE Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

  /* Configure GPIO Settings */
  GPIO_InitStructure.GPIO_Pin =
    GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
    GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/* Input Address GPIO pins on PD{0..7} and PB{0..6, 8}
   Split across PD and PB on the NUCLEO-F446ZE board
   due to pins being inacessible.
 */
void config_gpio_addr(void) {
  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Configure GPIO Settings */
  GPIO_InitStructure.GPIO_Pin =
    GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 |
    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* GPIOB Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* Configure GPIO Settings */
  GPIO_InitStructure.GPIO_Pin =
    GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

/* Configure GPIO Settings */
  GPIO_InitStructure.GPIO_Pin =
    GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  // On Nucleo board: PB14 has a red LED.
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void reset_gb(void) {
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

  // Pull PG0 to ground briefly to reset the Game Boy.

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  // ... and hold it there for a while
  REPH(9,9,9,asm("NOP"););
  REPH(9,9,9,asm("NOP"););

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
}

uint32_t offset = 0;

enum PlayerState { Stopped, PlayingRepeat, PlayingThru, Paused };

enum PlayerState player_state;

inline void processAudioCommand() {
  if (AUDIO_REGISTER_COMMANDS == AUDIO_COMMAND_PLAY) {
    player_state = PlayingRepeat;
  }

  if (AUDIO_REGISTER_COMMANDS == AUDIO_COMMAND_PAUSE) {
    player_state = Paused;
  }

  if (AUDIO_REGISTER_COMMANDS == AUDIO_COMMAND_UNPAUSE) {
    player_state = PlayingRepeat;
  }

  AUDIO_REGISTER_COMMANDS = AUDIO_COMMAND_NONE;

  switch (AUDIO_REGISTER_GAME_STATE) {
    case GAME_STATE_NORMAL_GAMEPLAY:
      break;

    case GAME_STATE_PRE_DYING:
      break;

    // Restart music:
    case GAME_STATE_RESET_TO_CHECKPOINT:
    case GAME_STATE_INCREMENT_LEVEL:
      offset = TrackMetadataForLevel(AUDIO_REGISTER_LEVEL).start_offset;
      break;

    // Stop music:
    case GAME_STATE_GAME_OVER:
      offset = TrackMetadataForLevel(0).start_offset;
      player_state = Stopped;
      break;
    case GAME_STATE_START_MENU:
      offset = TrackMetadataForLevel(0).start_offset;
      player_state = PlayingThru;
      break;
  }
}

inline void playerTick() {
  switch (player_state) {
    case PlayingRepeat:
      if (offset > (TrackMetadataForLevel(AUDIO_REGISTER_LEVEL).end_offset)) {
        offset = TrackMetadataForLevel(AUDIO_REGISTER_LEVEL).start_offset;
      } else {
        #ifdef DOUBLE_BUFFERING_ENABLED
        offset += BUFFER_SIZE_BYTE;
        #else
        offset += BUFFER_SIZE_BYTE / 2;
        #endif
      }
      break;
    case PlayingThru:
      #ifdef DOUBLE_BUFFERING_ENABLED
      offset += BUFFER_SIZE_BYTE;
      #else
      offset += BUFFER_SIZE_BYTE / 2;
      #endif
    case Stopped:
      offset = 0;
    case Paused:
      break;
  }
}

#define VOLUME_DIVISOR 1

volatile extern uint8_t number_of_times_logo_read;

volatile uint32_t ticks;
extern volatile uint16_t first_logo_read_ticks;
extern volatile uint16_t second_logo_read_ticks;

void SysTick_Handler(void) {
  ticks++;
}

void systickInit(uint16_t frequency) {
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  (void) SysTick_Config(RCC_Clocks.HCLK_Frequency / frequency);
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // Second-highest priority
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void disableSystick() {
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = SysTick_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // Second-highest priority
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
}

int main(void) {
  /* PE{8..15} */
  config_gpio_data();
  /* PD{0..15} */
  config_gpio_addr();
  /* PC{0, 2, 3} */
  config_gpio_sig();

  // Adjust the internal clock speed.
  // 14 = 15.97MHz
  // 15 = default
  RCC_AdjustHSICalibrationValue(14);

  systickInit(1000);

  sFLASH_Init();
  sFLASH_DMA_Init();

  configure_clock_interrupt();

  config_audio();

  rom_bank = 0x01;

  #ifdef DOUBLE_BUFFERING_ENABLED
  uint8_t *target_buffer;
  #endif

  offset = TrackMetadataForLevel(AUDIO_REGISTER_LEVEL).start_offset;

  // Once ready, toggle the reset pin.
  reset_gb();

  // If it takes fewer than this many ticks between the first and second reads
  // of the NINTENDO logo, we know we're on a CGB. Otherwise, we're on a DMG.
  #define CGB_SECOND_READ_THRESHOLD_IN_TICKS 200

  while (first_logo_read_ticks == 0 || (ticks - first_logo_read_ticks) < CGB_SECOND_READ_THRESHOLD_IN_TICKS) {
    if (first_logo_read_ticks != 0) {
      if (number_of_times_logo_read == 2) {
        device = CGB;
        patch_to_cgb(rom_gb);
        RedLEDOn;
        break;
      }
    }
  }

  if (device == Unknown) {
    device = DMG;
    patch_to_dmg(rom_gb);
    number_of_times_logo_read = 0;
    reset_gb();
  }

  disableSystick();

  while (1) {
    #ifdef DOUBLE_BUFFERING_ENABLED
    if (SET == DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5)) {
      DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);

      if (DMA_GetCurrentMemoryTarget(DMA1_Stream5) == DMA_Memory_0) {
        target_buffer = BufferB;
      } else {
        target_buffer = BufferA;
      }

      switch (player_state) {
        case PlayingRepeat:
        case PlayingThru:
          sFLASH_ReadBuffer(target_buffer, offset, BUFFER_SIZE_BYTE, VOLUME_DIVISOR);
          break;
        case Stopped:
        case Paused:
          for (int i = 0; i < BUFFER_SIZE_BYTE; i++) {
            target_buffer[i] = 171;
          }
          break;
      }

      processAudioCommand();
      playerTick();
    }

    #else
    if (SET == DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_TCIF5)) {
      DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_TCIF5);

      switch (player_state) {
        case PlayingRepeat:
        case PlayingThru:
          sFLASH_ReadBuffer(&AudioBuffer[0], offset, BUFFER_SIZE_BYTE / 2, VOLUME_DIVISOR);
          break;
        case Stopped:
        case Paused:
          for (int i = 0; i < BUFFER_SIZE_BYTE / 2; i++) {
            AudioBuffer[i] = 0;
          }
          break;
      }
      processAudioCommand();
      playerTick();
      continue;
    }

    if (SET == DMA_GetFlagStatus(DMA1_Stream5, DMA_FLAG_HTIF5)) {
      DMA_ClearFlag(DMA1_Stream5, DMA_FLAG_HTIF5);

      switch (player_state) {
        case PlayingRepeat:
        case PlayingThru:
          sFLASH_ReadBuffer(&AudioBuffer[BUFFER_SIZE_BYTE / 2], offset, BUFFER_SIZE_BYTE / 2, VOLUME_DIVISOR);
          break;
        case Stopped:
        case Paused:
          for (int i = BUFFER_SIZE_BYTE / 2; i < BUFFER_SIZE_BYTE; i++) {
            AudioBuffer[i] = 0;
          }
          break;
      }

      processAudioCommand();
      playerTick();
      continue;
    }
    #endif
  }
  RedLEDOn;
  while (1);
}

