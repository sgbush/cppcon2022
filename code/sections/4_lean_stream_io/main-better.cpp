



#include <cstdlib>
#include <cstddef>

#include "filestream.hpp"


extern "C" int _write(int, const void *, size_t)
{
    return 0;       // trivial implementation of the 'write' syscall
}

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





