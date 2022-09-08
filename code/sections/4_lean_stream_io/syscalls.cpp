

#include <cstddef>
#include <cstdint>

#include "linker-symbols.h"

#include <time.h>
#include <sys/types.h>


extern "C"     int         _system        (const char *) { return -1; }
extern "C"     int         _rename        (const char *, const char *) { return -1; }
extern "C"     int         _isatty        (int) { return 0; }
extern "C"     clock_t     _times         (struct tms *) { return (clock_t)(-1); }
extern "C"     int         _gettimeofday  (struct timeval *, void *) { return -1; }
extern "C"     void        _raise         (void) { return; }
extern "C"     int         _unlink        (const char *) { return -1; }
extern "C"     int         _link          (const char *, const char *) { return -1; }
extern "C"     int         _stat          (const char *, struct stat *) { return -1; }
extern "C"     int         _fstat         (int, struct stat *)  { return -1; }
extern "C"     void*       _sbrk          (ptrdiff_t) { return (unsigned char *)HeapStart; }
extern "C"     pid_t       _getpid        (void) { return -1; }
extern "C"     int         _kill          (int, int) { return -1; }
extern "C"     void        _exit          (int) { __asm("BKPT #0"); __builtin_unreachable(); }
extern "C"     int         _close         (int) { return -1; }
extern "C"     int         _swiclose      (int) { return -1; }
extern "C"     int         _open          (const char *, int, ...) { return -1;}
extern "C"     int         _swiopen       (const char *, int) { return -1; }
extern "C"     int         _write         (int, const void *, size_t) { return -1; }
extern "C"     int         _swiwrite      (int, const void *, size_t) { return -1; }
extern "C"     off_t       _lseek         (int, off_t, int) { return (off_t)(-1); }
extern "C"     off_t       _swilseek      (int, off_t, int) { return (off_t)(-1); }
extern "C"     int         _read          (int, void *, size_t) { return -1; }
extern "C"     int         _swiread       (int, void *, size_t) { return -1; }




