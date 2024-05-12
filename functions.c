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
void die_with_error(char *error_msg){
    printf("%s", error_msg);
    exit(-1);
}

void powerups_display(int shuffle_count, int block_count, int swap_count){

	if(shuffle_count != 0)
		printf("Z - Shuffle    ");
	if(block_count !=0)
		printf("Q - Block     ");
	if(swap_count != 0)
		printf("W - Swap     \n");
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
void block_column(int col, char table[9][9]){
	for(int i = 0; i < 9; i++){
		if(table[i][col] == ' ')
			table[i][col] = '-'; 
	}
	display(table);

}
void power_block (char input, char table[9][9]){
	switch (tolower(input)){
        case 'a':
            block_column(1, table);
            break;
        case 'b':
            block_column(2, table);
            break;
        case 'c':
            block_column(3, table);
            break;
        case 'd':
            block_column(4, table);
            break;
        case 'e':
            block_column(5, table);
            break;
        case 'f':
            block_column(6, table);
            break;
        case 'g':
            block_column(7, table);
            break;
        case 'h':
            block_column(8, table);
            break;
        default:
            printf("Invalid Input\n");
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
        case 'q':
            power_block(tolower(input[1]), table);
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
            	printf("Player 2 WINS!");
                return true;
                }
            if (table[i][j] == 'O' && table[i][j+1] == 'O' && table[i][j+2] == 'O' && table[i][j+3] == 'O' && table[i][j+4] == 'O'){
            	printf("Player 1 WINS!");
                return true;
                }
        }
    }

    //vertical
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 9; j++) {
            if (table[i][j] == 'X' && table[i+1][j] == 'X' && table[i+2][j] == 'X' && table[i+3][j] == 'X' && table[i+4][j] == 'X'){
            	printf("Player 2 WINS!");
                return true;
                }
            if (table[i][j] == 'O' && table[i+1][j] == 'O' && table[i+2][j] == 'O' && table[i+3][j] == 'O' && table[i+4][j] == 'O'){
            	printf("Player 1 WINS!");
                return true;
                }
        }
    }

    //diagonal(top-left to bottom-right)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == 'X' && table[i+1][j+1] == 'X' && table[i+2][j+2] == 'X' && table[i+3][j+3] == 'X' && table[i+4][j+4] == 'X'){
            	printf("Player 2 WINS!");
                return true;
                }
            if (table[i][j] == 'O' && table[i+1][j+1] == 'O' && table[i+2][j+2] == 'O' && table[i+3][j+3] == 'O' && table[i+4][j+4] == 'O'){
            	printf("Player 1 WINS!");
                return true;
                }
        }
    }

    //diagonal(bottom-left to top-right)
    for (int i = 4; i < 9; i++) {
        for (int j = 0; j < 5; j++) {
            if (table[i][j] == 'X' && table[i-1][j+1] == 'X' && table[i-2][j+2] == 'X' && table[i-3][j+3] == 'X' && table[i-4][j+4] == 'X'){
            	printf("Player 2 WINS!");
                return true;
                }
            if (table[i][j] == 'O' && table[i-1][j+1] == 'O' && table[i-2][j+2] == 'O' && table[i-3][j+3] == 'O' && table[i-4][j+4] == 'O'){
            	printf("Player 1 WINS!");
                return true;
                }
        }
    }
	
    return false;
}
