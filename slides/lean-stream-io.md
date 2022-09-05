# Use Stream-Based IO, But Skip the Library
---
# Lean Stream-Based IO
```c++
#include <iostream>

int main(int , char** )
{
    std::cout << "Hello, world!" << "\r\n";
}
```
```bash
$ arm-none-eabi-g++ -g0 -Os -std=c++20 \
-march=armv7e-m+fp -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mtune=cortex-m4 \
-Wall -Wextra -Wpedantic -Wno-psabi \
-fno-rtti -fno-exceptions -ffunction-sections \
-specs=nosys.specs -Wl,--gc-sections \
main.cpp -o main.elf && arm-none-eabi-objcopy ...
```
<!-- .element: class="fragment" -->
```console
$ du -bh main-bare.bin main-conventional.bin
65K     main-bare.bin
413K    main-conventional.bin
```
<!-- .element: class="fragment" -->
---
# Lean Stream-Based IO
Create a Lightweight Filestream Object
```c++ [1-4|5-6|8-13|15-22|23-26]
namespace mcu
{
class FileStream
{
    public:
    using Radix_t = enum class RadixEnum { Binary=2, Octal=8, Decimal=10, Hexadecimal=16, };

    protected:
    size_t mFileDescriptor;
    Radix_t mRadixSetting;

    public:
    FileStream(size_t fd) : mFileDescriptor(fd), mRadixSetting(RadixEnum::Hexadecimal) {}

    public:
    FileStream& operator<<(const char* string)
    {
        const size_t length = std::strlen(string);
        _write(mFileDescriptor, string, length);

        return *this;
    }
    template<typename U> requires std::integral<U>
    FileSteam& operator<<(const U value) { ... }
    template<typename U> requires std::floating_point<U>
    FileSteam& operator<<(const U value) { ... }
```
---
# Lean Stream-Based IO
Instantiate Filestreams for Each Output
```c++
namespace mcu
{
    FileStream debug(1);
    FileStream swo(2);
}
```
---
# Lean Stream-Based IO
Some Plumbing for Output Modes
```c++
extern "C" int _write(int fd, const void* data, size_t length)
{
    switch (fd)
    {
        case 1:
            SWOWrite((const char*)data, length);
            break;
        case 2:
            UARTWrite((const char*)data, length);
            break;
        case 3:
            UDPWrite(connection, (const char*)data, length)
        ...
    }
}
```
---
# Lean Stream-Based IO
The Traditional Use Case
```c++
#include "filestream.hpp"

int main(int , char** )
{
    mcu::swo << "Hello, Serial Wire Debug!" << "\r\n";
    mcu::debug << "Hello, UART Debug!" << "\r\n";
}
```
---
# Lean Stream-Based IO
It's Pretty Small
```c++
#include "filestream.hpp"

int main(int , char** )
{
    mcu::swo << "Hello, Serial Wire Debug!" << "\r\n";
    mcu::debug << "Hello, UART Debug!" << "\r\n";
}
```
```console
$ du -bh *.bin
65K     main-bare.bin
66K     main-better.bin
413K    main-conventional.bin
```
<!-- .element: class="fragment" -->
---
# Lean Stream-Based IO
Add Some Bells and Whistles
```c++
void TroublesomeFunction()
{
    mcu::debug << FileStream::RadixEnum::Hexadecimal << 32 << "\r\n";
}
```
```console
0x20
```
---
# Lean Stream-Based IO
Extending to Other Types
```c++ [1-2|4-10|12-14]
template<typename T>
class Tensor { ... };

FileStream& operator<<(FileStream& stream, const Tensor<float>& tensor)
{
    for(size_t i=0; i < tensor.Dimension(1); i++)
    {
        for(size_t j=0; j < tensor.Dimension(0); j++) ...
    }
}

Tensor<float> result( {10,10} );
mcu::debug << result;
```







