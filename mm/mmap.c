// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    // Make the syscall to mmap
    void *result = (void *)syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

    if ((long)result < 0) {
        errno = -(long)result;
        return MAP_FAILED;
    }

    return result;
}
void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	/* TODO: Implement mremap(). */
	 void *result = (void *)syscall(__NR_mremap, old_address, old_size, new_size, flags);

    if (result == MAP_FAILED) {
        errno = -errno;
        return MAP_FAILED;
    }

    return result;
}

int munmap(void *addr, size_t length)
{
	/* TODO: Implement munmap(). */
	int result = syscall(__NR_munmap, addr, length);

    if (result == -1) {
        errno = -errno;
        return -1;
    }

    return 0;
	return -1;
}
