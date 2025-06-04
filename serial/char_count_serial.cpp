#include "../char_count.hpp"
#include <stdexcept>

int char_count_serial(const char* str, char char_x, int M) {
    if (str == nullptr) {
        throw std::invalid_argument("Input string cannot be null.");
    }

    int count = 0;
    int i = 0;
    while (*str != '\0' && i < M) {
        if (*str == char_x) {
            count++;
        }
        str++;
        i++;
    }
    return count;
}