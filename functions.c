#include <stdio.h>
#include <time.h>

void display(char table[9][9]){
    for(int j = 1; j <= 8; j++) {
        table[0][j] = 'A' + j - 1;
    }//rows

    for(int i = 1; i < 9; i++) {
        table[i][0] = '0' + i;
    }//columns

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            printf("%c| ", table[i][j]);
        }
        printf("\n");
    }
}
void modify_table(char *buffer, char table[9][9]){

	int rows = 9;
	int cols = 9;	
	for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            table[i][j] = buffer[i*cols+j];
        }
    }
    display(table);
}
bool choices(char input, int shuffle_count, int swap_count){
	return (input != 'a' && input != 'b' &&
    	input != 'c' && input != 'd' &&
    	input != 'e' && input != 'f' &&
    	input != 'g' && input != 'h' && input != '1' && input != '3' ||
    	(input == '1' && shuffle_count == 0) && (input == '3' && swap_count == 0));
}
void die_with_error(char *error_msg){
    printf("%s", error_msg);
    exit(-1);
}

void powerups_display(int shuffle_count, int doubleturn_count, int swap_count){

	if(shuffle_count != 0)
		printf("1 - Shuffle    \n");
	if(doubleturn_count != 0)
		printf("2 - Double Turn    \n");
	if(swap_count != 0)
		printf("3 - Swap     \n");
}

void block(int col, char table[9][9], char player){
    for(int i=8; i>=0; i--){
        if (table[i][col] == ' '){
            table[i][col] = player;
            break;
        }
    }
    display(table);
}

void shuffle(char table[9][9]) {
    int size = 0;
    char temp[81];
    int index = 0;
    for (int i = 0; i < 9; i++){
    	for(int j = 0; j < 9; j++){
    		
    		temp[index++] = table[i][j];
    		if (table[i][j] == 'X' || table[i][j] == 'O')
    			size++;
    	}
    }
    int arr_index[size];
    int counter = 0;
    for (int i = 0; i < 81; i ++){
    	if(temp[i] == 'X' || temp[i] == 'O')
    	arr_index[counter++] = i;
    }
   
    srand(time(NULL));
    for(int i = size - 1; i > 0; i--){
    	int j = rand() % i + 1;
    	int temp_storage = temp[arr_index[i]];
    	temp[arr_index[i]] = temp[arr_index[j]];
    	temp[arr_index[j]] = temp_storage;
    }
    
    
    
    index = 0;
    for(int i = 0 ; i < 9; i++){
    	for(int j = 0; j < 9; j++){
    		table[i][j] = temp[index++];
    	}
    }
    display(table);
    
}
int convert_char(char col){
	switch ((tolower(col))){
	case 'a':
            return 1;
            break;
        case 'b':
            return 2;
            break;
        case 'c':
            return 3;
            break;
        case 'd':
            return 4;
            break;
        case 'e':
            return 5;
            break;
        case 'f':
            return 6;
            break;
        case 'g':
            return 7;
            break;
        case 'h':
            return 8;
            break;
        default:
            return -1;
	}
}
void swap(char col1, int row1,  char col2, int row2, char table[9][9]) {            //coordinates of the two position to swap
    
    if (tolower(col1) >= 'a' && tolower(col1) <= 'h'&& row1 >= 1 && row1 <= 8  &&
        tolower(col2) >= 'a' && tolower(col2) <= 'h' && row2 >= 1 && row2 <= 8) 
         {                 // Check if the provided coordinates are within the valid range
        char temp = table[row1][convert_char(col1)];
        table[row1][convert_char(col1)] = table[row2][convert_char(col2)];
        table[row2][convert_char(col2)] = temp;
        
    }
   
    display(table);
}

void block_column(int col, char table[9][9]){
	for(int i = 0; i < 9; i++){
		if(table[i][col] == ' ')
			table[i][col] = '-'; 
	}
	display(table);

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
        case '1':
            shuffle(table);
            break;
        case '3':
            break;
        default:
            printf("Invalid Input\n");
    }
}

bool Winner(char table[9][9]) {
    //horizontal
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == 'X' && table[i][j+1] == 'X' && table[i][j+2] == 'X' && table[i][j+3] == 'X' && table[i][j+4] == 'X'){
            	printf("Player 2 WINS!\n");
            	printf("Game Over!\n");
                return true;
                }
            if (table[i][j] == 'O' && table[i][j+1] == 'O' && table[i][j+2] == 'O' && table[i][j+3] == 'O' && table[i][j+4] == 'O'){
            	printf("Player 1 WINS!\n");
            	printf("Game Over!\n");
                return true;
                }
        }
    }

    //vertical
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (table[i][j] == 'X' && table[i+1][j] == 'X' && table[i+2][j] == 'X' && table[i+3][j] == 'X' && table[i+4][j] == 'X'){
            	printf("Player 2 WINS!\n");
            	printf("Game Over!\n");
                return true;
                }
            if (table[i][j] == 'O' && table[i+1][j] == 'O' && table[i+2][j] == 'O' && table[i+3][j] == 'O' && table[i+4][j] == 'O'){
            	printf("Player 1 WINS!\n");
            	printf("Game Over!\n");
                return true;
                }
        }
    }

    //diagonal(top-left to bottom-right)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == 'X' && table[i+1][j+1] == 'X' && table[i+2][j+2] == 'X' && table[i+3][j+3] == 'X' && table[i+4][j+4] == 'X'){
            	printf("Player 2 WINS!\n");
            	printf("Game Over!\n");
                return true;
                }
            if (table[i][j] == 'O' && table[i+1][j+1] == 'O' && table[i+2][j+2] == 'O' && table[i+3][j+3] == 'O' && table[i+4][j+4] == 'O'){
            	printf("Player 1 WINS!\n");
            	printf("Game Over!\n");
                return true;
                }
        }
    }

    //diagonal(bottom-left to top-right)
    for (int i = 4; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == 'X' && table[i-1][j+1] == 'X' && table[i-2][j+2] == 'X' && table[i-3][j+3] == 'X' && table[i-4][j+4] == 'X'){
            	printf("Player 2 WINS!");
            	printf("Game Over!\n");
                return true;
                }
            if (table[i][j] == 'O' && table[i-1][j+1] == 'O' && table[i-2][j+2] == 'O' && table[i-3][j+3] == 'O' && table[i-4][j+4] == 'O'){
            	printf("Player 1 WINS!");
            	printf("Game Over!\n");
                return true;
                }
        }
    }
	
    return false;
}