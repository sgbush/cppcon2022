


#include <cstddef>
#include <random>

#include "bimodal-dist.hpp"
#include "hw-random.hpp"



int main(int , char** )
{
    BimodalDistrubution<mcu::random_device> dist;

    size_t index = 0;
    while ( index < 1000 )
    {
        dist();
        index += 1;
    }
    return 0;
}











