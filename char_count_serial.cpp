
#include <iostream>


int char_count_serial(const char* str, char char_x, size_t M) {
    if (str == nullptr) {
        throw std::invalid_argument("Input string cannot be null.");
    }

    int count = 0;
    int i;
    while (*str != '\0' && i < M) {
        if (*str == char_x) {
            count++;
        }
        str++;
        i++;
    }
    return count;
}



int main() {
    const char text[] = "texttotexttotto";

    int times = 0;
    size_t text_length = sizeof(text) / sizeof(text[0]) - 1; 
    //size_t text_length = 8;   // Tamano de ejemplo

    try {
        times = char_count_serial(text, 'o', text_length);
        std::cout << "Character 'o' appears " << times << " times in the string." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
}

