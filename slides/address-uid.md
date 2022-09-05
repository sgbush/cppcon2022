# Code With Number Structures Humans Can Actually Read and Edit
---
# Address-Like Structures
* Many embedded applications use long numeric structures
    * Frequently known at compile time for storage in nonvolatile memory <!-- .element: class="fragment" -->
* Bluetooth <!-- .element: class="fragment" -->
    * 128-bit UUIDs <!-- .element: class="fragment" -->
    * 48-bit MAC address <!-- .element: class="fragment" -->
* Internet Protocol <!-- .element: class="fragment" -->
    * 32-bit IPv4 addresses <!-- .element: class="fragment" -->
    * 128-bit IPv6 addresses <!-- .element: class="fragment" -->
* USB <!-- .element: class="fragment" -->
    * Unicode encoded string (descriptors) <!-- .element: class="fragment" -->
---
# Address-Like Structures
The Old Way
```c++
// canonical UUID
// { 01234567-89AB-CDEF-0123-456789ABCDEF }
static constexpr uint8_t uuid1[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
```
---
# Address-Like Structures
The Old Way
```c++
// canonical MAC
// 12:34:56:78:90:AB
static constexpr uint8_t mac1[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB };
```
---
# Address-Like Structures
The Old Way
```c++ [1-3|5-7]
// canonical IPv4 address
// 192.168.0.1/24
static constexpr struct IP4Addr { uint8_t Address[4]; uint8_t MaskBits; } address = { {192,168,0,1}, 24 };

// canonical IPv6 address
// 2001:db8::1:0
uint16_t IPv6Addr[] = { 0x2001, 0x0db8, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000 };
```
---
# Address-Like Structures
The Old Way
```c++ [1-2|4-6|8-9]
// Unicode string constant
static constexpr char devicedesc[] = { 'W', 0, 'i', 0, 'd', 0, 'g', 0, 'e', 0, 't', 0 };

// USB string descriptor
#define USB_STRING 0x03
static constexpr char DeviceStringDescriptor[] = { 14, USB_STRING, 'W', 0, 'i', 0, 'd', 0, 'g', 0, 'e', 0, 't', 0 }

#define CHAR_TO_UNICODE(x) x, 0x00
static constexpr uint8_t DeviceDescription[] = { CHAR_TO_UNICODE('M'), CHAR_TO_UNICODE('y'), CHAR_TO_UNICODE(' '), CHAR_TO_UNICODE('D'), CHAR_TO_UNICODE('e'), CHAR_TO_UNICODE('v'), CHAR_TO_UNICODE('i'), CHAR_TO_UNICODE('c'), CHAR_TO_UNICODE('e'),  };
```
---
# Address-Like Structures
```c++
class UUID
{
    private:
    std::array<uint8_t,16> mData {0};

    public:
    UUID() = default;

    friend constexpr UUID operator""_uuid(const char* text, size_t length);
};
```
---
# Address-Like Structures
```c++
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
```
---
# Address-Like Structures
```c++
static const UUID uuid = "{ 01234567-89AB-CDEF-0123-456789ABCDEF }"_uuid;
static const MACAddr mac = "12:34:56:78:90:AB"_macaddr;
static const IP4Addr addr = "192.168.0.1/24"_ip4addr;
static const USBString devdescr = "Widget"_utf16;
static const auto devdescr = u"Widget";
```



