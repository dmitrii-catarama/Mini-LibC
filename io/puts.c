#include <internal/io.h>
#include <stdio.h>

int puts(const char* str) {
    while (*str != '\0') {
        const char *c = str;
        ssize_t writeCall = write(1, c, 1);

        if (writeCall < 0) {
            return -1;
        }

        str++;
    }

    char newLine = '\n';
    ssize_t newLineSet = write(1, &newLine, 1);

    if (newLineSet < 0) {
        return -1;
    }

    return 1;
}
