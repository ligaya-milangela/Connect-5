#include <stdio.h>
#include <time.h>


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

void shuffle(char table[9][9]) {
    srand(time(NULL));
    for(int j = 1; j < 9; j++) {
        int disc_count = 0;
        char temp_discs[8] = {0};

        // copy discs to temp arr
        for(int i = 8; i >= 1; i--) {
            if (table[i][j] != ' ') {
                temp_discs[disc_count] = table[i][j];
                disc_count++;
            }
        }

        // shuffle discs in temp arr
        for (int i = 0; i < disc_count - 1; i++) {
            int rand_index = rand() % (disc_count - i) + i;
            char temp = temp_discs[i];
            temp_discs[i] = temp_discs[rand_index];
            temp_discs[rand_index] = temp;
        }

        // copy shuffled discs back to the table
        for(int i = 8, k = 0; i >= 1; i--) {
            if (table[i][j] != ' ') {
                table[i][j] = temp_discs[k];
                k++;
            }
        }
    }
}

void option(const char* input, char player_turn, char table[9][9]){
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
        case 'z':
            shuffle(table);
            break;
        default:
            printf("Invalid Input\n");
    }
}

void display(char table[9][9]){
    for(int j = 1; j <= 8; j++) {
        table[0][j] = 'A' + j - 1;
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
                return true;
        }
    }

    //vertical
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (table[i][j] == player && table[i+1][j] == player && table[i+2][j] == player && table[i+3][j] == player && table[i+4][j] == player)
                return true;
        }
    }

    //diagonal(top-left to bottom-right)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == player && table[i+1][j+1] == player && table[i+2][j+2] == player && table[i+3][j+3] == player && table[i+4][j+4] == player)
                return true;
        }
    }

    //diagonal(bottom-left to top-right)
    for (int i = 4; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == player && table[i-1][j+1] == player && table[i-2][j+2] == player && table[i-3][j+3] == player && table[i-4][j+4] == player)
                return true;
        }
    }

    return false;
}
