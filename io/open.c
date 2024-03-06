// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>


// Implemented with
// https://opensource.apple.com/source/Libc/Libc-583/sys/open.c.auto.html
int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	mode_t mode = 0;
    if (flags & O_CREAT) {
        va_list args;
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    int result = syscall(__NR_open, filename, flags, mode);

    if (result < 0) {
        errno = -result;
        return -1;
    }

    return result;
}
