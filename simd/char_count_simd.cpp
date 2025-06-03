
#include <immintrin.h>
#include <iostream>
#include <cstring>

int count_ocurrences(const char* str, int m, char char_x) {
    int count = 0;

    // Replicate char_x into an AVX register
    __m128i vect_x = _mm_set1_epi8(char_x);     // Load char_x into all bytes of the vector. Equivalent to setvect

    // First: Count ocurrences with SIMD for efficiency
    int i = 0;
    int simd_end = m - (m % 16);

    for (; i < simd_end; i += 16) {
        // Load str into an AVX register (unaligned)
        __m128i vect_temp = _mm_loadu_si128(reinterpret_cast<const __m128i*>(str + i));

        // Compare vectors vect_x and vect_temp
        __m128i vect_out = _mm_cmpeq_epi8(vect_x, vect_temp);

        // Get mask from vect_out
        unsigned int mask = _mm_movemask_epi8(vect_out);

        // Analize mask and count ones
        count += _mm_popcnt_u32(mask);

    }

    // Second: Count ocurrences serially for security
    for (; i < m; i++) {
        if (str[i] == char_x) count++;
    }
    return count;

}

// Compile with: g++ -o char_count_simd char_count_simd.cpp -mavx

int main() {
    // Example usage
    const char* str = "this is a text for testing the character count with SIMD or Serial methods. And we will compare those methods.";
    size_t m = strlen(str); 
    char char_x = 't';
    int count = count_ocurrences(str, m, char_x);
    std::cout << "Occurrences of '" << char_x << "': " << count << std::endl;
}

