#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long int power(unsigned long long int base, unsigned long long int exponent, unsigned long long int modulus) {
    unsigned long long int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int main() {
    unsigned long long int p, g, privateA, privateB;
    
    printf("Enter prime number (q): ");
    scanf("%llu", &p);
    
    printf("Enter primitive root (a): ");
    scanf("%llu", &g);
    
    printf("Enter private key of XA: ");
    scanf("%llu", &privateA);
    
    printf("Enter private key OF XB: ");
    scanf("%llu", &privateB);

    unsigned long long int publicA = power(g, privateA, p);
    unsigned long long int publicB = power(g, privateB, p);

    unsigned long long int secretA = power(publicB, privateA, p);
    unsigned long long int secretB = power(publicA, privateB, p);

    printf("Alice's public key: %llu\n", publicA);
    printf("Bob's public key: %llu\n", publicB);
    printf("Shared secret for Alice: %llu\n", secretA);
    printf("Shared secret for Bob: %llu\n", secretB);

    if (secretA == secretB) {
        printf("Key exchange successful!\n");
    } else {
        printf("Key exchange failed!\n");
    }

    return 0;
}