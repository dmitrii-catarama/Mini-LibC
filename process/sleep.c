#include <unistd.h>
#include <time.h>

unsigned int sleep(unsigned int seconds) {
    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    if (nanosleep(&req, &rem) == (unsigned int) -1) {
        // If nanosleep returns -1, sleep was interrupted; return the remaining seconds
        return rem.tv_sec;
    }

    // Sleep completed without interruption
    return 0;
}
