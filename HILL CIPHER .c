#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt using the Hill cipher
void encrypt(int keyMatrix[2][2], char input[]) {
    int len = strlen(input);
    char output[len];

    // Encryption
    for (int i = 0; i < len; i += 2) {
        if (isalpha(input[i]) && isalpha(input[i + 1])) {
            int vec[2] = {toupper(input[i]) - 'A', toupper(input[i + 1]) - 'A'};
            int enc[2] = {0, 0};

            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    enc[j] += keyMatrix[j][k] * vec[k];
                }
                enc[j] %= 26; // Modulo 26 to wrap around the alphabet
            }

            output[i] = enc[0] + 'A';
            output[i + 1] = enc[1] + 'A';
        } else {
            output[i] = input[i];
            output[i + 1] = input[i + 1];
        }
    }

    printf("Encrypted Text: ");
    for (int i = 0; i < len; i++) {
        printf("%c", output[i]);
    }
    printf("\n");
}

int main() {
    int keyMatrix[2][2];
    printf("Enter the 2x2 key matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &keyMatrix[i][j]);
        }
    }

    char input[100];
    printf("Enter text to encrypt: ");
    scanf("%s", input);

    encrypt(keyMatrix, input);

    return 0;
}