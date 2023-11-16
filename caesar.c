#include <stdio.h>
#include <string.h>
void caesarEncrypt(char text[], int shift) {
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
        }
    }
}
void caesarDecrypt(char text[], int shift) {
    caesarEncrypt(text, 26 - shift); 
}
int main() {
    char plaintext[100];
    int shift;
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the shift value: ");
    scanf("%d", &shift);
    caesarEncrypt(plaintext, shift);
    printf("Encrypted text: %s\n", plaintext);
    caesarDecrypt(plaintext, shift);
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}
