#include <unistd.h>
#include <time.h>


unsigned int nanosleep(const struct timespec *req, struct timespec *rem) {
    int result = syscall(__NR_nanosleep, req, rem);

    if (result < 0) {
        return -1;
    }

    return 0;
}
