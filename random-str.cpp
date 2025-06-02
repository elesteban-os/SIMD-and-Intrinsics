
#include <iostream>
#include <random>
#include <string>
#include <cstddef>
#include <cstring>

using namespace std;

struct randomString {
    char *str;
    int length;
    int align;
    size_t adjustedSize;

    randomString(unsigned int length, size_t alignment) : length(length), align(alignment) {
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
            throw bad_alloc(); // Handle allocation failure
        }

        str = static_cast<char*>(ptr);

        for (int i = 0; i < length; ++i) {
            str[i] = characters[distribution(generator)];
        }
        str[length] = '\0'; // Null-terminate the string
    }

    ~randomString() {
        free(str);
    }
};

int main() {
    try {
        unsigned int length = 24; // Tamaño de la cadena aleatoria
        size_t alignment = 8; // Alineación en bytes

        randomString myString(length, alignment);
        cout << "Random String: " << myString.str << endl;
        cout << "Adjusted Size: " << myString.adjustedSize << endl;

    } catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

