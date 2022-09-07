


#include <cstddef>
#include <random>
#include <cmath>
#include <array>
#include <limits>

#include "bimodal-dist.hpp"
#include "filestream.hpp"

#include "stm32h743xx.h"


namespace mcu
{
class random_device
{
    public:
    using result_type = unsigned int;
    static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
    static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

    random_device()
    {
        RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
        RNG->CR |= RNG_CR_RNGEN;
    }
    result_type operator()()
    {
        while ( !(RNG->SR & RNG_SR_DRDY) ) continue;
        return RNG->DR;
    }
};
}

template<typename T>
T Clamp(T value, T minvalue, T maxvalue)
{
    return std::max( std::min(value, maxvalue), minvalue);
}

int main(int , char** )
{
    BimodalDistrubution dist;
    mcu::random_device device;

    std::array<size_t,64> pdf = {0};

    size_t index = 0;
    while ( index < 10'000 )
    {
        auto value = dist(device);
        auto sub = Clamp( static_cast<size_t>( 64.0f*(value + 15.0f)/30.0f ), size_t(0), size_t(63));
        pdf[sub] += 1;

        index += 1;
    }
    for ( auto binheight : pdf )
    {
        for (unsigned int i=0; i < binheight/20; i += 1) mcu::debug << "*";
        mcu::debug << "\r\n";
    }
    return 0;
}











