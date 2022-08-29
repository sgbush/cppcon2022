




#pragma once


#include <cstdint>


// the old way #1

#define CHAR_TO_UNICODE(x) x, 0x00
static const uint8_t DeviceDescription[] = { CHAR_TO_UNICODE('M'), CHAR_TO_UNICODE('y'), CHAR_TO_UNICODE(' '), CHAR_TO_UNICODE('D'), CHAR_TO_UNICODE('e'), CHAR_TO_UNICODE('v'), CHAR_TO_UNICODE('i'), CHAR_TO_UNICODE('c'), CHAR_TO_UNICODE('e'),  };

// the old way #2

static const uint16_t DeviceDescription[] = { 'M', 0x00, 'y', 0x00, ' ', 0x00, 'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00, 'c', 0x00, 'e', 0x00, }



// better way










