#include <stdio.h>
#include <ctype.h>

void block(int col, char table[9][9]){
    for(int i=8; i>=0; i--){
        if (table[i][col] == ' '){
            table[i][col] = '1';
            break;
        }
    }
}

int main() {
    int rows = 9;
    int cols = 9;
    char c;
    
    char table[rows][cols];
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            table[i][j] = ' ';
        }
    }
    while(1){
    
    for(int j = 1; j <= cols; j++) {
        table[0][j] = 'A' + j-1;
    }
    
    for(int i = 1; i < rows; i++) {
        table[i][0] = '0' + i;
    }
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%c| ", table[i][j]);
        }
        printf("\n");
    }
    printf("Enter column: ");
    scanf(" %c", &c);
    switch (tolower(c)){
        case 'a':
            block(1, table);
            break;
        case 'b':
            block(2, table);
            break;
        case 'c':
            block(3, table);
            break;
        case 'd':
            block(4, table);
            break;
        case 'e':
            block(5, table);
            break;
        case 'f':
            block(6, table);
            break;
        case 'g':
            block(7, table);
            break;
        case 'h':
            block(8, table);
            break;
        default:
            printf("Invalid Input\n");
    }}
    return 0;
}
