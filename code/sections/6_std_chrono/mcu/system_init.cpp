


#include <cstddef>

#define STM32H743xx
#include "stm32h7xx.h"


extern bool SystemClockConfigure();
extern bool ChronoConfigure(TIM_TypeDef* timer, volatile uint32_t& rccreg, const uint32_t rccvalue);
extern bool SerialCommChannelConfigure(size_t baudrate, size_t txbuffersize);
extern bool GPIOConfigure();



extern "C" void SystemInit()
{
    SystemClockConfigure();
    ChronoConfigure(TIM2, RCC->APB1LENR, RCC_APB1LENR_TIM2EN);
    GPIOConfigure();
    SerialCommChannelConfigure(115'200, 2048);
}











