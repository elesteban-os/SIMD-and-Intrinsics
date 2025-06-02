
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <chrono>


void print_memory_usage() {
    std::ifstream status_file("/proc/self/status");
    std::string line;
    while (std::getline(status_file, line)) {
        if (line.find("VmRSS:") == 0) { // RAM utilizada
            std::cout << "Memoria RAM del proceso / " << line << std::endl;
        }
        if (line.find("VmSize:") == 0) { 
            std::cout << "Memoria virtual del proceso / " << line << std::endl;
        }
    }
}

int char_count_serial(const char* str, char char_x, size_t M) {
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

// Compilar con g++
// Ejecutar con perf: perf stat ./char_count_serial

int main() {    
    print_memory_usage();
    int times = 0;
    const char *text = "texttooooooogjho";
    size_t text_length = strlen(text); 

    try {
        auto start = std::chrono::high_resolution_clock::now();
        
        times = char_count_serial(text, 'o', text_length);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
        std::cout << "Character 'o' appears " << times << " times in the string." << std::endl;
        std::cout << "Execution time: " << elapsed.count() << " nanoseconds." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    print_memory_usage();
     
}


