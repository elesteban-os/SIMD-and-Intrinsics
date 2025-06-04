#include "../char_count.hpp"
#include <iostream>
#include <cstring>
#include <chrono>
#include <stdexcept>

// Compile with: g++ main_simd.cpp char_count_simd.cpp -o main_simd -mavx
// Execute with perf: perf stat ./main_simd

int main() {
    const char* str = "this is a text for testing the character count with SIMD or Serial methods. And we will compare those methods.";
    char char_x = 't';
    size_t m = strlen(str); 

    try {
        auto start = std::chrono::high_resolution_clock::now();
        
        int count = char_count_simd(str, char_x, m);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
        std::cout << "Character '" << char_x << "' appears " << count << " times in the string." << std::endl;
        std::cout << "Execution time: " << elapsed.count() << " nanoseconds." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}