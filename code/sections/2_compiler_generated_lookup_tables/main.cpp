

#include <cstddef>
#include <cstdlib>
#include <array>
#include <iostream>

#include "lookup-tables.hpp"


static constexpr std::array<float,4> ThermistorCoefficients { 1.0e-3, 1.0e-4, 1.0e-6, 1.0e-8 };

constexpr auto ThermistorLookup = ThermistorTable(ThermistorCoefficients, 10.0e3, 3.3f, 3.3f);

int main(int , char** )
{

    for( auto element : ThermistorLookup ) std::cout << element << "\r\n";

}



