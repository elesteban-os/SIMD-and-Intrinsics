#include "../char_count.hpp"
#include <iostream>
#include <cstring>
#include <chrono>
#include <stdexcept>

// compile with g++ main_serial.cpp char_count_serial.cpp -o main_serial
// execute with perf: perf stat ./main_serial

int main() {    
    const char* str = "this is a text for testing the character count with SIMD or Serial methods. And we will compare those methods.";
    char char_x = 't'; // Character to count
    size_t m = strlen(str); 

    try {
        auto start = std::chrono::high_resolution_clock::now();
        
        int count = char_count_serial(str, char_x, m);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
        std::cout << "Character '" << char_x << "' appears " << count << " times in the string." << std::endl;
        std::cout << "Execution time: " << elapsed.count() << " nanoseconds." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
     
}
