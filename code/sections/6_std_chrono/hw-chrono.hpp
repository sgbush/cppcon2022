

#pragma once



#include <chrono>
#include <cstdint>

// hardware-specific definitions
struct TIM_TypeDef
{
    uint16_t PSC;
    uint16_t ARR;
    uint16_t CNT;
}; 

struct ClockTreeStruct { uint32_t pclk2; };
struct ClockTreeStruct ClockTree { .pclk2 = 64'000'000 };

static TIM_TypeDef* ChronoHWTimer = nullptr;

bool MicrosecondClockConfigure(TIM_TypeDef* timer, volatile uint32_t& rccreg, const uint32_t rccvalue)
{
    bool success = true;
    const uint32_t timer_freq = 1'000'000;

    // program timer for std::chrono functions
	ChronoHWTimer = timer;
    rccreg |= rccvalue;
    timer->PSC = (ClockTree.pclk2/timer_freq) - 1;
    timer->ARR = 0xFFFFFFFF;
    timer->CNT = 0ul;

    return success;
}



