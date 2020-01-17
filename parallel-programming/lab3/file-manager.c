//
// Created by matvey on 09.12.2019.
//

#include <unistd.h>
#include <asm/errno.h>
#include <string.h>

void printToFile(char *str, int fileDescriptor) {
    size_t length = strlen(str);
    size_t size = 0;

    while (size != length) {
        size_t s = write(fileDescriptor, str + size, length - size);
        if (s == -1) {
            _exit(EIO);
        }
        size += s;
    }
}

