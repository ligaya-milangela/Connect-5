#include <stdio.h>

void die_with_error(char *error_msg){
    printf("%s", error_msg);
    exit(-1);
}
void block(int col, char table[9][9], char player){
    for(int i=8; i>=0; i--){
        if (table[i][col] == ' '){
            table[i][col] = player;
            break;
        }
    }
}
void option (const char* input, char player_turn, char table[9][9]){
     switch (tolower(input[0])){
        case 'a':
            block(1, table, player_turn);
            break;
        case 'b':
            block(2, table, player_turn);
            break;
        case 'c':
            block(3, table, player_turn);
            break;
        case 'd':
            block(4, table, player_turn);
            break;
        case 'e':
            block(5, table, player_turn);
            break;
        case 'f':
            block(6, table, player_turn);
            break;
        case 'g':
            block(7, table, player_turn);
            break;
        case 'h':
            block(8, table, player_turn);
            break;
        default:
            printf("Invalid Input\n");
    }
}
void display (char table [9][9]){
    for(int j = 1; j <= 8; j++) {
        table[0][j] = 'A' + j-1;
    }
   
    for(int i = 1; i < 9; i++) {
        table[i][0] = '0' + i;
    }
   
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%c| ", table[i][j]);
        }
        printf("\n");
    }
}
bool Winner(char table[9][9], char player) {
    //horizontal
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == player && table[i][j+1] == player && table[i][j+2] == player && table[i][j+3] == player && table[i][j+4] == player)
                return 1;
        }
    }

    //vertical
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (table[i][j] == player && table[i+1][j] == player && table[i+2][j] == player && table[i+3][j] == player && table[i+4][j] == player)
                return 1;
        }
    }

    //diagonal(top-left to bottom-right)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == player && table[i+1][j+1] == player && table[i+2][j+2] == player && table[i+3][j+3] == player && table[i+4][j+4] == player)
                return 1;
        }
    }

    //diagonal(bottom-left to top-right)
    for (int i = 4; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == player && table[i-1][j+1] == player && table[i-2][j+2] == player && table[i-3][j+3] == player && table[i-4][j+4] == player)
                return 1;
        }
    }

    return 0;
}
