#pragma once
#include <cstddef>

struct randomString {
    char *str;
    int length;
    int align;
    size_t adjustedSize;

    randomString(unsigned int length, size_t alignment);
    ~randomString();
};