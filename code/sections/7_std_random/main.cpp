


#include <cstddef>
#include <random>
#include <iostream>
#include <cmath>
#include <array>

#include "bimodal-dist.hpp"

template<typename T>
T Clamp(T value, T minvalue, T maxvalue)
{
    return std::max( std::min(value, maxvalue), minvalue);
}

int main(int , char** )
{
    BimodalDistrubution dist;
    std::random_device device;

    std::array<size_t,32> pdf = {0};

    size_t index = 0;
    while ( index < 10'000 )
    {
        auto value = dist(device);
        auto sub = Clamp( static_cast<size_t>( 32.0f*(value + 15.0f)/30.0f ), size_t(0), size_t(31));
        pdf[sub] += 1;

        index += 1;
    }
    for ( auto binheight : pdf )
    {
        for (size_t i=0; i < binheight/20; i += 1) std::cout << "*";
        std::cout << "\r\n";
    }
    return 0;
}











