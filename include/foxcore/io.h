#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct file {
    char* data;
    size_t len;
    bool isValid;
} File;

File ioFileRead(const char *path);
int ioFileWrite(void* buffer, size_t size, const char *path);
