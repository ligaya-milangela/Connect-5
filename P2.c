#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include "functions.c"

int main(int argc, char *argv[]){
    char c;
    char player_turn = 'O'; //first turn starts with 'O'
    int shuffle_count = 1;
    int block_count = 1;
    int swap_count = 1;
    char table[9][9];
    int server_sock, client_sock, port_no, client_size, n;
    char buffer[256];
    bool ismain_loop = 1;
    struct sockaddr_in server_addr, client_addr;
    if (argc < 2) {
        printf("Usage: %s port_no", argv[0]);
        exit(1);
    }

    printf("PC2 starting ...\n");
    // Create a socket for incoming connections
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) 
       die_with_error("Error: socket() Failed.");
       
    // Bind socket to a port
    bzero((char *) &server_addr, sizeof(server_addr));
    port_no = atoi(argv[1]);
    server_addr.sin_family = AF_INET; // Internet address 
    server_addr.sin_addr.s_addr = INADDR_ANY; // Any incoming interface
    server_addr.sin_port = htons(port_no); // Local port
    
    if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
       die_with_error("Error: bind() Failed.");
       
    // Mark the socket so it will listen for incoming connections
    listen(server_sock, 5);
    printf("PC2 listening to port %d ...\n", port_no);
    
    printf("Waiting for connection(s) ...\n");
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            table[i][j] = ' ';
        }
    }
    while(ismain_loop == 1){
    display(table);
    
    // Accept new connection
    client_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &client_size);
    if (client_sock < 0) 
        die_with_error("Error: accept() Failed.");

    printf("PC1 succesfully connected ...\n");    
    // Communicate  
    while(1){  
    
    bzero(buffer, 256);
    n = recv(client_sock, buffer, 255, 0);
    display(table);
    if (n < 0) die_with_error("Error: recv() Failed.");
    printf("Message received from PC1 : %s", buffer);
     powerups_display(shuffle_count, block_count, swap_count);
    option(buffer, 'O', table);
    
    if (Winner(table)) {
        ismain_loop = 0;
        break;
    }

    bzero(buffer, 256);
    do {
     	printf("Enter column : ");
    	fgets(buffer, 255, stdin);
    } while (!((tolower(buffer[0]) >= 'a' && tolower(buffer[0]) <= 'h') ||
         (tolower(buffer[0]) == 'z' && shuffle_count == 0) ||
         (tolower(buffer[0]) == 'q' && block_count == 0 ||
          (tolower(buffer[1]) >= 'a' && tolower(buffer[1]) <= 'h'))));



    if(shuffle_count == 1 && tolower(buffer[0]) == 'z')
    	shuffle_count = 0;
    if(block_count == 1 && tolower(buffer[0]) == 'q')
    	block_count = 0;
    option(buffer, 'X', table);
    
    n = send(client_sock, buffer, strlen(buffer), 0);
    if (Winner(table)) {
        ismain_loop = 0;
        break;
    }
    
    
    if (n < 0) die_with_error("Error: send() Failed.");
    }
    }
    printf("Closing connection ...\n");
    close(client_sock);
    close(server_sock);
    
    return 0; 
}