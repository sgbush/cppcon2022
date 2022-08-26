



#pragma once



#include <random>
#include <cstdint>
#include <limits>


// represents the hardware peripheral
struct RNGStruct {
    static constexpr uint32_t IsBusy = 0x01;
    uint32_t status;
    uint32_t value;
} RNG;


// note that since the library implements std::random_device::operator() as an in-class member, we cannot supply our own definition to link against, so we must implement in our own namespace

namespace mcu
{
class random_device
{
    public:
    using result_type = uint32_t;

    public:
    random_device() = default;
    random_device(const random_device& other) = delete;
    random_device& operator=(const random_device& other) = delete;

    double entropy() const noexcept { return 10.0; }
    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    result_type operator()()
    {
        while ( RNG.status & RNG.IsBusy ) continue;
        return RNG.value;
    }
};
}

