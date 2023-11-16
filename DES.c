#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int initial_permutation_table[64] = { 
    58, 50, 42, 34, 26, 18, 10, 2, 
    60, 52, 44, 36, 28, 20, 12, 4, 
    62, 54, 46, 38, 30, 22, 14, 6, 
    64, 56, 48, 40, 32, 24, 16, 8, 
    57, 49, 41, 33, 25, 17, 9, 1, 
    59, 51, 43, 35, 27, 19, 11, 3, 
    61, 53, 45, 37, 29, 21, 13, 5, 
    63, 55, 47, 39, 31, 23, 15, 7
};

void initial_permutation(uint64_t *block) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        result |= (((*block) >> (64 - initial_permutation_table[i])) & 1) << (63 - i);
    }
    *block = result;
}

int main() {
    
    uint64_t block = 0x123456789abcdef0;
    printf("Original Block: 0x%016llx\n", block);
    initial_permutation(&block);
    printf("Permuted Block: 0x%016llx\n", block);
    return 0;
}
