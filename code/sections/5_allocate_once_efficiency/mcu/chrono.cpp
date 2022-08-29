


#include <chrono>

#define STM32H743xx
#include "stm32h7xx.h"

#include "clock-impl.hpp"

static TIM_TypeDef* chrono_timer = nullptr;

namespace std::chrono
{

	time_point<high_resolution_clock> high_resolution_clock::now()
	{
		return time_point(nanoseconds(1000ull*static_cast<nanoseconds::rep>(chrono_timer->CNT)));
	}

} // namespace std::chrono


bool ChronoConfigure(TIM_TypeDef* timer, volatile uint32_t& rccreg, const uint32_t rccvalue)
{
    bool success = true;

    // program timer for std::chrono functions
	chrono_timer = timer;
    rccreg |= rccvalue;
    const uint32_t timer_freq = 1'000'000;
    timer->PSC = (ClockTree.pckl1_tim/timer_freq) - 1;
    timer->ARR = 0xFFFFFFFF;
    timer->CNT = 0ul;
    timer->EGR |= TIM_EGR_UG;
    timer->CR1 |= TIM_CR1_CEN;

    return success;
}












