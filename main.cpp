#include "random-str.hpp"
#include "char_count.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>

// Compile with: g++ -std=c++17 -O2 main.cpp random_str/random-str.cpp serial/char_count_serial.cpp simd/char_count_simd.cpp -o test -mavx
// Execute with: ./test

int main() {
    // 1. create 50 random strings with different lengths and alignments
    std::vector<randomString*> strings;
    for (int i = 0; i < 50; ++i) {
        unsigned int len = 16 + rand() % 100; // length between 16 and 115
        size_t align = (i < 25) ? 8 : 16;
        strings.push_back(new randomString(len, align));
    }

    std::vector<int> lengths;
    std::vector<int> counts_serial;
    std::vector<int> counts_simd;
    std::vector<int> execution_times_serial;
    std::vector<int> execution_times_simd;
    char target = 'a'; // Character to count

    // 2. char_count_serial
    for (auto s : strings) {
        auto start_serial = std::chrono::high_resolution_clock::now();
    
        int count_serial = char_count_serial(s->str, target, s->length);

        auto end_serial = std::chrono::high_resolution_clock::now();
        auto duration_serial = std::chrono::duration_cast<std::chrono::nanoseconds>(end_serial - start_serial).count();
        
        lengths.push_back(s->length);
        counts_serial.push_back(count_serial);
        execution_times_serial.push_back(duration_serial);
    }
    
    // 3. char_count_simd
    for (auto s : strings) {
        auto start_simd = std::chrono::high_resolution_clock::now();

        int count_simd = char_count_simd(s->str, target, s->length);

        auto end_simd = std::chrono::high_resolution_clock::now();
        auto duration_simd = std::chrono::duration_cast<std::chrono::nanoseconds>(end_simd - start_simd).count();

        counts_simd.push_back(count_simd);
        execution_times_simd.push_back(duration_simd);

    }
    // 4. save results in a CSV file
    std::ofstream csv("results.csv");
    csv << "Length,CountSerial,CountSIMD,TimeSerial_ns,TimeSIMD_ns\n";
    for (size_t i = 0; i < strings.size(); ++i) {
        csv << lengths[i] << ","
            << counts_serial[i] << ","
            << counts_simd[i] << ","
            << execution_times_serial[i] << ","
            << execution_times_simd[i] << "\n";
    }
    csv.close();
    std::cout << "Results saved in results.csv\n";

    // 5. free memory
    for (auto s : strings) delete s;

    return 0;
}