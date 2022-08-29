

#include <cstddef>
#include <unistd.h>

extern "C" int _write(int fd, const void * buffer, size_t length)
{
    auto retval = write(fd, buffer, length);

    return retval;
}


