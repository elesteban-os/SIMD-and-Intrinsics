#pragma once
#include <cstddef>

int char_count_serial(const char* str, char char_x, int M);
int char_count_simd(const char* str, char char_x, int M);