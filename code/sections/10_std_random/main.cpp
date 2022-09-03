


#include <cstddef>
#include <random>

#include "bimodal-dist.hpp"
#include "hw-random.hpp"



int main(int , char** )
{
    BimodalDistrubution dist;
    mcu::random_device device;

    size_t index = 0;
    while ( index < 1000 )
    {
        dist(device);
        index += 1;
    }
    return 0;
}











