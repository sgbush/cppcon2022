



#include <cstdlib>
#include <cstddef>

#include "filestream.hpp"



namespace mcu
{
    FileStream debug(1);
    FileStream swo(2);
}


int main(int, char** )
{

    mcu::debug << "Hello, world!\r\n";

    mcu::debug << mcu::FileStream::RadixEnum::Hexadecimal << 6 << "\r\n";

    while (true) continue;
}





