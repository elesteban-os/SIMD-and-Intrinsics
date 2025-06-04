#include "../random-str.hpp"
#include <stdexcept>
#include <iostream>

// Compile with: g++ main_random_str.cpp random-str.cpp -o main_random_str
// Execute with: ./main_random_str

int main() {
    try {
        unsigned int length = 24; // random string length
        size_t alignment = 8; // alignment in bytes

        randomString myString(length, alignment);
        std::cout << "Random String: " << myString.str << std::endl;
        std::cout << "Adjusted Size: " << myString.adjustedSize << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}