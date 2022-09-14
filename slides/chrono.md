# Implement One Function to Unlock All of Time <span>(Functions)</span> <!-- .element: class="fragment" -->
---
# Unlock std::chrono
* Embedded time sources
    * Relative (Hardware timer)
    * Absolute (RTC)
* Applications
    * Performance instrumentation
    * Time-of-day and calendaring
---
# Unlock std::chrono
```c++ [3|6|8-14]
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
```
---
# Unlock std::chrono
```c++
namespace std::chrono
{
	time_point<high_resolution_clock> high_resolution_clock::now()
	{
		return time_point(
            nanoseconds(
                1000ull*static_cast<nanoseconds::rep>(chrono_timer->CNT)));
	}
} // namespace std::chrono
```
---
# Unlock std::chrono
Demo time


