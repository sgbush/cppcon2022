



#include <cstddef>
#include <chrono>

#include <malloc.h>

#include "filestream.hpp"


static size_t AllocatedBytes = 0;

static constexpr bool use_arena = false;

void* operator new(size_t size)
{
    constexpr size_t ArenaSize = 0x1000;
    static char Arena[ArenaSize];

    AllocatedBytes += size;
    if constexpr ( use_arena )
    {
        if ( AllocatedBytes < ArenaSize ) return (Arena + AllocatedBytes);
        else return 0;
    }
    else
    {
        return malloc(size);
    }
}

void operator delete(void* ptr)
{
    if constexpr ( !use_arena )
    {
        free(ptr);
    }
}

void operator delete(void* ptr, size_t )
{
    if constexpr ( !use_arena )
    {
        free(ptr);
    }
}




int main(int , char** )
{
    size_t* ptr = nullptr;

    mcu::debug << "Application start...\r\n";

    size_t index = 0;
    while ( (ptr = new size_t) != nullptr )
    {
        index += 1;
    }

    // delay a little to allow serial port to attach
    auto timeout = std::chrono::high_resolution_clock::now() + std::chrono::seconds(5);
    while ( std::chrono::high_resolution_clock::now() < timeout ) continue;

    mcu::debug << "Number of allocations: " << mcu::FileStream::RadixEnum::Decimal << index << "\r\n";

    while (true) continue;
}



