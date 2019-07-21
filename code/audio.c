#include "audio.h"

#define   DAC_DHR12R1_ADDR  0x40007408                            // DMA writes into this reg on every request
#define   DAC_DHR8R1_ADDR   0x40007410
#define   CNT_FREQ          45000000                              // TIM6 counter clock (prescaled APB1)
#define   TIM_PERIOD        (CNT_FREQ / (AUDIO_SAMPLE_RATE / 2)); // Autoreload reg value

#ifdef DOUBLE_BUFFERING_ENABLED
uint8_t BufferA[DMA_BUFFER_SIZE] = {0};
uint8_t BufferB[DMA_BUFFER_SIZE] = {0};
#else
uint8_t AudioBuffer[BUFFER_SIZE_BYTE] = {0};
#endif

void config_audio() {
  GPIO_InitTypeDef gpio_A;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  gpio_A.GPIO_Pin  = GPIO_Pin_4;
  gpio_A.GPIO_Mode = GPIO_Mode_AN;
  gpio_A.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &gpio_A);

  TIM_TimeBaseInitTypeDef TIM6_TimeBase;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

  TIM_TimeBaseStructInit(&TIM6_TimeBase);
  TIM6_TimeBase.TIM_Period        = (uint16_t)TIM_PERIOD;
  TIM6_TimeBase.TIM_Prescaler     = 0;
  TIM6_TimeBase.TIM_ClockDivision = 0;
  TIM6_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM6, &TIM6_TimeBase);
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

  TIM_Cmd(TIM6, ENABLE);

  DAC_InitTypeDef DAC_INIT;
  DMA_InitTypeDef DMA_INIT;

  DAC_INIT.DAC_Trigger        = DAC_Trigger_T6_TRGO;
  DAC_INIT.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_INIT.DAC_OutputBuffer   = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_INIT);

  DMA_DeInit(DMA1_Stream5);
  DMA_INIT.DMA_Channel            = DMA_Channel_7;
  DMA_INIT.DMA_PeripheralBaseAddr = (uint32_t)DAC_DHR8R1_ADDR;
  #ifdef DOUBLE_BUFFERING_ENABLED
  DMA_INIT.DMA_Memory0BaseAddr    = (uint32_t)BufferA;
  #else
  DMA_INIT.DMA_Memory0BaseAddr    = (uint32_t)AudioBuffer;
  #endif
  DMA_INIT.DMA_DIR                = DMA_DIR_MemoryToPeripheral;
  DMA_INIT.DMA_BufferSize         = BUFFER_SIZE_BYTE;
  DMA_INIT.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_INIT.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_INIT.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_INIT.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
  DMA_INIT.DMA_Mode               = DMA_Mode_Circular;
  DMA_INIT.DMA_Priority           = DMA_Priority_Low;
  DMA_INIT.DMA_FIFOMode           = DMA_FIFOMode_Disable;
  DMA_INIT.DMA_FIFOThreshold      = DMA_FIFOThreshold_HalfFull;
  DMA_INIT.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
  DMA_INIT.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream5, &DMA_INIT);

  #ifdef DOUBLE_BUFFERING_ENABLED
  DMA_DoubleBufferModeConfig(DMA1_Stream5, (uint32_t)BufferA, DMA_Memory_0);
  DMA_DoubleBufferModeConfig(DMA1_Stream5, (uint32_t)BufferB, DMA_Memory_1);
  DMA_DoubleBufferModeCmd(DMA1_Stream5, ENABLE);
  #endif

  DMA_Cmd(DMA1_Stream5, ENABLE);
  DAC_Cmd(DAC_Channel_1, ENABLE);
  DAC_DMACmd(DAC_Channel_1, ENABLE);
}
