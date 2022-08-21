





#pragma once

#include <string>
#include <cstddef>
#include <cstring>
#include <chrono>

extern "C" int _write(int, const void *, size_t);

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
    FileStream& operator<<(const std::string& msg)
    {
        const size_t length = msg.length();
        _write(mFileDescriptor, msg.c_str(), length);

        return *this;
    }
    FileStream& operator<<(unsigned int value)
    {
        const char* const digits = "0123456789ABCDEF";
        const unsigned int radix = static_cast<unsigned int>(mRadixSetting);
        static constexpr size_t MaxFieldWidth = 34;
        char fielddata[MaxFieldWidth];
        size_t fieldindex = 0;

        int first = 0;
        switch (mRadixSetting)
        {
        case RadixEnum::Binary:
            fielddata[0] = '0';
            fielddata[1] = 'b';
            fieldindex += 2;
            first += 2;
            break;
        case RadixEnum::Octal:
            fielddata[0] = '0';
            fielddata[1] = 'o';
            fieldindex += 2;
            first += 2;
            break;
        case RadixEnum::Decimal:
            break;
        case RadixEnum::Hexadecimal:
            fielddata[0] = '0';
            fielddata[1] = 'x';
            fieldindex += 2;
            first += 2;
            break;
        }

        // calculate digits (they will be reversed)
        unsigned int remainder;
        do {
            remainder = value % radix;
            fielddata[fieldindex] = digits[remainder];
            value /= radix;
            fieldindex += 1;
        } while ( value != 0 );

        // reverse order
        int last = fieldindex-1;
        while ( (last-first) > 0 )
        {
            char tmp = fielddata[last];
            fielddata[last] = fielddata[first];
            fielddata[first] = tmp;
            first += 1;
            last -= 1;
        }

        _write(mFileDescriptor, fielddata, fieldindex);

        return *this;
    }
    FileStream& operator<<(Radix_t radix)
    {
        mRadixSetting = radix;

        return *this;
    }
    FileStream& operator<<(std::chrono::milliseconds time)
    {
        operator<<(time.count());
        operator<<("ms");
    }
    size_t Descriptor() { return mFileDescriptor; }
};


extern FileStream swo;
extern FileStream debug;



}








