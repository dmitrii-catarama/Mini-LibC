// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/types.h>
#include <unistd.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

#define makedev(x, y) ( \
		(((x)&0xfffff000ULL) << 32) | \
	(((x)&0x00000fffULL) << 8) | \
		(((y)&0xffffff00ULL) << 12) | \
	(((y)&0x000000ffULL)) \
	)

/* Structure describing file characteristics as defined in linux/stat.h */
struct statx {
	uint32_t stx_mask;
	uint32_t stx_blksize;
	uint64_t stx_attributes;
	uint32_t stx_nlink;
	uint32_t stx_uid;
	uint32_t stx_gid;
	uint16_t stx_mode;
	uint16_t pad1;
	uint64_t stx_ino;
	uint64_t stx_size;
	uint64_t stx_blocks;
	uint64_t stx_attributes_mask;
	struct {
		int64_t tv_sec;
		uint32_t tv_nsec;
		int32_t pad;
	} stx_atime, stx_btime, stx_ctime, stx_mtime;
	uint32_t stx_rdev_major;
	uint32_t stx_rdev_minor;
	uint32_t stx_dev_major;
	uint32_t stx_dev_minor;
	uint64_t spare[14];
};

//Implemented with ChatGPT and
//https://git.musl-libc.org/cgit/musl/tree/src/stat/fstatat.c?h=v1.1.24

int fstatat_statx(int fd, const char *restrict path, struct stat *restrict st, int flag)
{
	/* TODO: Implement fstatat_statx(). Use statx and makedev above. */
	struct statx buf;
	int ret = syscall(__NR_statx, fd, path, flag, STATX_TYPE | STATX_MODE |
					STATX_NLINK | STATX_UID | STATX_GID |
                   	STATX_ATIME | STATX_MTIME | STATX_CTIME |
					STATX_INO | STATX_SIZE | STATX_BLOCKS, &buf);
	if (ret == 0) {
		st->st_dev = makedev(buf.stx_dev_major, buf.stx_dev_minor);
		st->st_ino = buf.stx_ino;
		st->st_mode = buf.stx_mode;
		st->st_nlink = buf.stx_nlink;
		st->st_uid = buf.stx_uid;
		st->st_gid = buf.stx_gid;
		st->st_rdev = makedev(buf.stx_rdev_major, buf.stx_rdev_minor);
		st->st_size = buf.stx_size;
		st->st_blksize = buf.stx_blksize;
		st->st_blocks = buf.stx_blocks;
	}
	return ret;
}

int fstatat(int fd, const char *restrict path, struct stat *restrict st, int flag)
{
	/* TODO: Implement fstatat(). Use fstatat_statx(). */
	return fstatat_statx(fd, path, st, flag);
}
