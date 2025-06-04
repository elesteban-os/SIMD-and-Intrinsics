#include "../random-str.hpp"
#include <iostream>
#include <random>
#include <string>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

using namespace std;

randomString::randomString(unsigned int length, size_t alignment)
    : length(length), align(alignment) {
    if ((alignment & (alignment - 1)) != 0) {
        throw invalid_argument("Alignment must be power of 2.");
    }

    const string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, characters.size() - 1);

    adjustedSize = ((length + 1 + alignment - 1) / alignment) * alignment;
    void* ptr = aligned_alloc(alignment, adjustedSize);
    if (!ptr) {
        throw bad_alloc();
    }

    str = static_cast<char*>(ptr);

    for (int i = 0; i < length; ++i) {
        str[i] = characters[distribution(generator)];
    }
    str[length] = '\0';
}

randomString::~randomString() {
    free(str);
}
