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

int main(void) {
  // Just deinit the flash pins so we can connect to the SPI flash
  // from a programmer without having this STM32 interfere.
  sFLASH_DeInit();

  RedLEDOn;
  while (1);
}

