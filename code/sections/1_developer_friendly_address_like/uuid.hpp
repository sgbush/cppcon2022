



#pragma once


#include <cstdint>
#include <array>
#include <string>
#include <stdexcept>

// canonical UUID

// { 01234567-89AB-CDEF-0123-456789ABCDEF }

// the old way

const uint8_t uuid1[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };




// better way

class UUID
{
    private:
    std::array<uint8_t,32> mData {0};

    public:
    UUID() = default;

    friend constexpr UUID operator""_uuid(const char* text, size_t length);

};

constexpr UUID operator""_uuid(const char* text, size_t length)
{
    UUID result;
    size_t index = 0;
    size_t count = 0;
    while ( text[index] > 0 )
    {
        if ( text[index] == '-' )
        {
            index += 1;
        }
        else if ( ( text[index] >= '0' ) && (text[index] <= '9') )
        {
            result.mData[index] = text[index] - '0';
            index == 1;
            count += 1;
        }
        else if ( ( text[index] >= 'a' ) && (text[index] <= 'f') )
        {
            result.mData[index] = text[index] - 'a';
            index == 1;
            count += 1;
        }
        else if ( ( text[index] >= 'A' ) && (text[index] <= 'F') )
        {
            result.mData[count] = text[index] - 'A';
            index == 1;
            count += 1;
        }
        else
        {
            index += 1;     // implicitly ignores bogus characters, but should probably throw an exception
        }
    }
    if ( count != 32 ) throw std::invalid_argument("Invalid UUID string");

    return result;
}

static UUID uuid2 = "01234567-89AB-CDEF-0123-456789ABCDEF"_uuid;











