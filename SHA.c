#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include<stdlib.h>

// SHA-1 Constants
#define SHA1_BLOCK_SIZE 64
#define SHA1_HASH_SIZE 20

// Left-rotate operation
#define LEFT_ROTATE(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// SHA-1 functions
#define CH(x, y, z) (((x) & (y)) ^ ((~(x)) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
static const uint32_t k[64] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
    // Add the rest of the 64 MD5 constants here
};

void sha1(const uint8_t *message, size_t message_len, uint8_t *digest) {
    // Initialize variables
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    // Append padding bits and length
    uint64_t bit_len = message_len * 8;
    size_t padding_len = (message_len % SHA1_BLOCK_SIZE < 56) ?
                         (SHA1_BLOCK_SIZE - (message_len % SHA1_BLOCK_SIZE)) :
                         (2 * SHA1_BLOCK_SIZE - (message_len % SHA1_BLOCK_SIZE));

    size_t padded_len = message_len + padding_len;
    uint8_t *padded_message = (uint8_t *)malloc(padded_len);
    memcpy(padded_message, message, message_len);
    padded_message[message_len] = 0x80; // Padding bit
    for (size_t i = message_len + 1; i < padded_len - 8; i++) {
        padded_message[i] = 0x00; // Padding zeros
    }
    for (size_t i = 0; i < 8; i++) {
        padded_message[padded_len - 8 + i] = (bit_len >> (56 - i * 8)) & 0xFF;
    }

    // Process message in 512-bit blocks
    
for (size_t i = 0; i < padded_len; i += SHA1_BLOCK_SIZE) {
    uint32_t w[80]; // Message schedule

    // Prepare the message schedule (Wt)
    for (size_t t = 0; t < 16; t++) {
        w[t] = ((uint32_t)padded_message[i + t * 4] << 24) |
               ((uint32_t)padded_message[i + t * 4 + 1] << 16) |
               ((uint32_t)padded_message[i + t * 4 + 2] << 8) |
               ((uint32_t)padded_message[i + t * 4 + 3]);
    }
    for (size_t t = 16; t < 80; t++) {
        w[t] = LEFT_ROTATE(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);
    }

    // Initialize hash values for this block
    uint32_t a = h0;
    uint32_t b = h1;
    uint32_t c = h2;
    uint32_t d = h3;
    uint32_t e = h4;

    // Main loop
    for (size_t t = 0; t < 80; t++) {
        uint32_t temp = LEFT_ROTATE(a, 5) + CH(b, c, d) + e + k[t] + w[t];
        e = d;
        d = c;
        c = LEFT_ROTATE(b, 30);
        b = a;
        a = temp;
    }

    // Update hash values for this block
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
}

// Compute the final hash value
digest[0] = (h0 >> 24) & 0xFF;
digest[1] = (h0 >> 16) & 0xFF;
digest[2] = (h0 >> 8) & 0xFF;
digest[3] = h0 & 0xFF;

digest[4] = (h1 >> 24) & 0xFF;
digest[5] = (h1 >> 16) & 0xFF;
digest[6] = (h1 >> 8) & 0xFF;
digest[7] = h1 & 0xFF;

digest[8] = (h2 >> 24) & 0xFF;
digest[9] = (h2 >> 16) & 0xFF;
digest[10] = (h2 >> 8) & 0xFF;
digest[11] = h2 & 0xFF;

digest[12] = (h3 >> 24) & 0xFF;
digest[13] = (h3 >> 16) & 0xFF;
digest[14] = (h3 >> 8) & 0xFF;
digest[15] = h3 & 0xFF;

digest[16] = (h4 >> 24) & 0xFF;
digest[17] = (h4 >> 16) & 0xFF;
digest[18] = (h4 >> 8) & 0xFF;
digest[19] = h4 & 0xFF;

      // Clean up
    free(padded_message);
}

int main() {
    char input[100];
    printf("enter the string:");
    fgets(input, sizeof(input), stdin);
    uint8_t hash[SHA1_HASH_SIZE]; // SHA-1 hash will be stored here

    // Calculate the SHA-1 hash
    sha1((const uint8_t *)input, strlen(input), hash);

    // Print the SHA-1 hash
    printf("SHA-1 Hash: ");
    for (int i = 0; i < SHA1_HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
