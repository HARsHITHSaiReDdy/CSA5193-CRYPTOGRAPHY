#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include<stdlib.h>

// MD5 Constants
#define MD5_BLOCK_SIZE 64
#define MD5_HASH_SIZE 16

// MD5 functions
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

// Left-rotate operation
#define LEFT_ROTATE(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
static const uint32_t k[64] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5,
    // Add the rest of the 64 MD5 constants here
};

static const uint32_t r[64] = {
    7, 12, 17, 22,
    // Add the rest of the 64 rotation amounts here
};
void md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest) {
    // Initialize variables
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;

    // Append padding bits
    size_t new_len = ((initial_len + 8) / 64 + 1) * 64;
    uint8_t *msg = (uint8_t *)malloc(new_len);
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // Padding bit

    // Append length
    uint64_t bits_len = initial_len * 8;
    memcpy(msg + new_len - 8, &bits_len, 8);

    // Process message in 512-bit blocks
    for (size_t i = 0; i < new_len; i += 64) {
        uint32_t w[16];
        for (size_t j = 0; j < 16; j++) {
            w[j] = *((uint32_t *)(msg + i + j * 4));
        }

        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;

        for (size_t j = 0; j < 64; j++) {
            uint32_t f, g;
            if (j < 16) {
                f = F(b, c, d);
                g = j;
            } else if (j < 32) {
                f = G(b, c, d);
                g = (5 * j + 1) % 16;
            } else if (j < 48) {
                f = H(b, c, d);
                g = (3 * j + 5) % 16;
            } else {
                f = I(b, c, d);
                g = (7 * j) % 16;
            }

            uint32_t temp = d;
            d = c;
            c = b;
            b = b + LEFT_ROTATE((a + f + k[j] + w[g]), r[j]);
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }

    // Copy the final hash value to the output buffer
    memcpy(digest, &h0, 4);
    memcpy(digest + 4, &h1, 4);
    memcpy(digest + 8, &h2, 4);
    memcpy(digest + 12, &h3, 4);

    // Clean up
    free(msg);
}

int main() {
     char msg[100];
    printf("enter the string:");
    fgets(msg, sizeof(msg), stdin);

    uint8_t digest[MD5_HASH_SIZE];

    md5((uint8_t *)msg, strlen(msg), digest);

    printf("Message: %s\n", msg);
    printf("MD5 Hash: ");
    for (size_t i = 0; i < MD5_HASH_SIZE; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}
