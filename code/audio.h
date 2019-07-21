#ifndef __audio_h
#define __audio_h

#include "lib/stm32f4xx_exti.h"
#include "lib/stm32f4xx_gpio.h"
#include "lib/stm32f4xx_rcc.h"
#include "lib/stm32f4xx_syscfg.h"
#include "lib/stm32f4xx_tim.h"
#include "lib/stm32f4xx_dac.h"
#include "lib/stm32f4xx_dma.h"
#include "lib/system_stm32f4xx.h"
#include "lib/misc.h"
#include "audio_constants.h"
#include "data/flash_constants.h"


void config_audio(void);

// Turn on this #define if you want to try double buffering mode.
// This causes a bit of instability (maybe we need more free clock cycles in the cart emulation ISR?)
// but makes the audio less glitchy and produces fewer artifacts.
#define DOUBLE_BUFFERING_ENABLED

#ifdef DOUBLE_BUFFERING_ENABLED

#define   SPI_COMMAND_SIZE 4
#define DMA_BUFFER_SIZE (BUFFER_SIZE_BYTE + SPI_COMMAND_SIZE)
extern uint8_t BufferA[DMA_BUFFER_SIZE];
extern uint8_t BufferB[DMA_BUFFER_SIZE];

#else

extern uint8_t AudioBuffer[BUFFER_SIZE_BYTE];

#endif

#endif
