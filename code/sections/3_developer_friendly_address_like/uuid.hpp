



#pragma once


#include <cstdint>
#include <array>
#include <string>
#include <stdexcept>

// the old way

// canonical UUID
// { 01234567-89AB-CDEF-0123-456789ABCDEF }
const uint8_t uuid1[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };

// canonical MAC
// 12:34:56:78:90:AB
const uint8_t mac1[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB };

// canonical IPv4 address
// 192.168.0.1/24
struct IP4Addr { uint8_t Address[4]; uint8_t MaskBits; } address = { {192,168,0,1}, 24 };

// Unicode string constant
char devicedesc[] = { 'W', 0, 'i', 0, 'd', 0, 'g', 0, 'e', 0, 't', 0 };

// better way

class UUID
{
    private:
    std::array<uint8_t,16> mData {0};

    public:
    UUID() = default;

    friend constexpr UUID operator""_uuid(const char* text, size_t length);
};

constexpr UUID operator""_uuid(const char* text, size_t length)
{
    UUID result;
    size_t index = 0;
    size_t count = 0;
    while ( index < length )
    {
        if ( ( text[index] >= '0' ) && (text[index] <= '9') )
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
            // bogus character checking here
            index += 1;
        }
    }
    if ( count != 32 ) throw std::invalid_argument("Invalid UUID string");

    return result;
}

static UUID uuid2 = "01234567-89AB-CDEF-0123-456789ABCDEF"_uuid;











