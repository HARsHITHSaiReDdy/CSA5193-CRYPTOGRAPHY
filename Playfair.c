#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int i, j, k = 0;
    int flag[26] = {0};
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (k < strlen(key)) {
                if (!flag[key[k] - 'A']) {
                    keyTable[i][j] = key[k];
                    flag[key[k] - 'A'] = 1;
                } else {
                    j--;
                }
                k++;
            } else {
                for (k = 0; k < 26; k++) {
                    if (!flag[k]) {
                        keyTable[i][j] = k + 'A';
                        flag[k] = 1;
                        break;
                    }
                }
            }
        }
    }
}
void search(char keyTable[SIZE][SIZE], char a, char b, int arr[4]) {
    int i, j;
    if (a == 'J') a = 'I';
    else if (b == 'J') b = 'I';
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            if (keyTable[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}
void encrypt(char keyTable[SIZE][SIZE], char str[]) {
    int i, j, a[4];
    for (i = 0; i < strlen(str); i += 2) {
        search(keyTable, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            printf("%c%c", keyTable[a[0]][(a[1] + 1) % SIZE], keyTable[a[0]][(a[3] + 1) % SIZE]);
        } else if (a[1] == a[3]) {
            printf("%c%c", keyTable[(a[0] + 1) % SIZE][a[1]], keyTable[(a[2] + 1) % SIZE][a[1]]);
        } else {
            printf("%c%c", keyTable[a[0]][a[3]], keyTable[a[2]][a[1]]);
        }
    }
}
int main() {
    char key[26], keyTable[SIZE][SIZE], plaintext[100];
    printf("Enter the key (uppercase letters): ");
    scanf("%s", key);
    printf("Enter the plaintext (uppercase letters): ");
    scanf("%s", plaintext);
	for (int i = 0; i < strlen(key); i++) {
        key[i] = toupper(key[i]);
    }
	int len = strlen(key);
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len;) {
            if (key[j] == key[i]) {
                for (int k = j; k < len; k++) {
                    key[k] = key[k + 1];
                }
                len--;
            } else {
                j++;
            }        }
    }
	generateKeyTable(key, keyTable);
	printf("Key Table:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", keyTable[i][j]);
        }
        printf("\n");
    }
	printf("Encrypted Text: ");
    encrypt(keyTable, plaintext);
	
}