#include <stdio.h>
#include <string.h>

void railFenceEncrypt(char message[], int rails) {
    int messageLength = strlen(message);
    char railMatrix[rails][messageLength];
    
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < messageLength; j++) {
            railMatrix[i][j] = '\0';
        }
    }
    
    int row = 0;
    int direction = 1; // 1 for down, -1 for up
    
    for (int i = 0; i < messageLength; i++) {
        railMatrix[row][i] = message[i];
        
        if (row == 0) {
            direction = 1;
        }
        else if (row == rails - 1) {
            direction = -1;
        }
        
        row += direction;
    }
    
    printf("Encrypted message: ");
    
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < messageLength; j++) {
            if (railMatrix[i][j] != '\0') {
                printf("%c", railMatrix[i][j]);
            }
        }
    }
    
    printf("\n");
}

int main() {
    char message[100];
    int rails;
    
    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    
    printf("Enter the number of rails: ");
    scanf("%d", &rails);
    
    railFenceEncrypt(message, rails);
    
    return 0;
}