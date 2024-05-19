#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include "functions.c"

int main(int argc,  char *argv[]){
    int rows = 9;
    int cols = 9;
    char c;
    char player_turn = 'O'; //first turn starts with 'O'
   int shuffle_count = 1;
   int doubleturn_count = 1;
    int swap_count = 1;
    char table[rows][cols];
    int row1, row2;
    char col1;
    char col2;
    
    
    
    int client_sock,  port_no,  n;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
        printf("Usage: %s hostname port_no",  argv[0]);
        exit(1);
    }

    printf("PC1 starting ...\n");
    // Create a socket using TCP
    client_sock = socket(AF_INET,  SOCK_STREAM,  0);
    if (client_sock < 0) 
        die_with_error("Error: socket() Failed.");

    //printf("Looking for host '%s'...\n", argv[1]);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        die_with_error("Error: No such host.");
    }
    //printf("Game!!\n");

    // Establish a connection to server
    port_no = atoi(argv[2]);
    bzero((char *) &server_addr,  sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,  
         (char *)&server_addr.sin_addr.s_addr, 
         server->h_length);
         
    server_addr.sin_port = htons(port_no);

    //printf("Connecting to PC2 at port %d...\n", port_no);
    if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
        die_with_error("Error: connect() Failed.");

    printf("Connection successful!\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            table[i][j] = ' ';
        }
    }
    display(table);
    while(1){
    powerups_display(shuffle_count, doubleturn_count, swap_count);
    // Communicate
  
    bzero(buffer, 256);
    do {
     	printf("Enter column : ");
    	fgets(buffer, 255, stdin);
    	if (tolower(buffer[0]) == '2' && doubleturn_count != 0)
    	{
    		for(int i = 0; i < 2; i++){
    			do{
    				printf("Enter column: ");
    			fgets(buffer, 255, stdin);
    			}
    			while(
    				tolower(buffer[0]) < 'a' || tolower(buffer[0]) > 'h'
    			);
    			
    			if(i == 0)
    			{
    				option(buffer, 'O', table);
    				
    			}
    		}
    		doubleturn_count = 0;
    	}
    	else if (tolower(buffer[0] == '3') && swap_count != 0){
    		printf("Enter coordinates for the first position (e.g., A8): ");
    		scanf(" %c%d", &col1, &row1);
    		printf("Enter coordinates for the second position (e.g., B8): ");
    		scanf(" %c%d", &col2, &row2);
    		swap(col1, row1, col2, row2, table);
    		
    	}
    } while (
    	choices(tolower(buffer[0]), shuffle_count, doubleturn_count)
    	
    	);

    if (shuffle_count == 1 && tolower(buffer[0]) == '1'){
    	shuffle_count = 0;}
    if(doubleturn_count == 1 && tolower(buffer[0]) == '2'){
    	doubleturn_count = 0; }
    if(swap_count == 1 && tolower(buffer[0]) == '3'){
    	swap_count = 0;}
    option(buffer, 'O', table);
    
    n = send(client_sock, table, 81, 0);
    if (Winner(table)){
        break;
    }
    printf("Sending move to PC2 ...\n");
    
    
    if (n < 0) 
         die_with_error("Error: send() Failed.");
         
    //printf("Message sent! Awaiting reply ...\n");
    bzero(buffer, 256);
    n = recv(client_sock, buffer, 255, 0);
    modify_table(buffer, table);

    
    if (Winner(table)) {
        break;
    }
    if (n < 0) 
         die_with_error("Error: recv() Failed.");
    }
    close(client_sock);
    
    return 0;
}