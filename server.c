
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

void die_with_error(char *error_msg){
    printf("%s", error_msg);
    exit(-1);
}

void displayCards(char *cards[]) {
    printf("+-----------------+\n");
    printf("|   Your Cards    |\n");
    printf("+-----------------+\n");

    for (int i = 0; i < 5; i++) {
        printf("| %-15s |\n", cards[i]);
    }

    printf("+-----------------+\n");
}

void displayHP(int player1HP, int player2HP) {
    printf("╔══════════════════════╗\n");
    printf("║      Player Status   ║\n");
    printf("╠══════════════════════╣\n");
    printf("║ Your HP: %-3d         ║\n", player1HP);
    printf("║ Opponent's HP: %-3d   ║\n", player2HP);
    printf("╚══════════════════════╝\n");
}


void shuffle(char *cards[], int n)
{
    
    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        
        int r = i + (rand() % (15 - i));

        
        char *temp = cards[i];
        cards[i] = cards[r];
        cards[r] = temp;
    }
}

void game(int *A, int *B, char elem1[], char elem2[], int val1, int val2)
{

    if (strcmp(elem1, "water") == 0  && strcmp(elem2, "fire") == 0 && val1>val2)
        {
            *B = *B - (val1-val2);
        }
    else if (strcmp(elem1, "water") == 0 && strcmp(elem2, "fire") == 0 && val1<val2)
        {
            *B = *B-0;
        }
    else if (strcmp(elem1, "water") == 0 && strcmp(elem2, "fire") == 0 && val1==val2)
        {
            *B=*B-1;
        }

    if (strcmp(elem1, "water") == 0 && strcmp(elem2, "grass") == 0 && val1>val2)
        {
            *B = *B-0;
        }
    else if (strcmp(elem1, "water") == 0 && strcmp(elem2, "grass") == 0 && val1<val2)
        {
            *A = *A-(val2-val1);
        }
    else if (strcmp(elem1, "water") == 0 && strcmp(elem2, "grass") == 0 && val1==val2)
        {
            *A=*A-1;
        }

    if (strcmp(elem1, "water") == 0 && strcmp(elem2, "water") == 0 && val1==val2)
        {
            *A=*A-1;
            *B=*B-1;
        }
        else if (strcmp(elem1, "water") == 0 && strcmp(elem2, "water") == 0 && val1>val2)
        {
            *B=*B-1;
        }
        else if (strcmp(elem1, "water") == 0 && strcmp(elem2, "water") == 0 && val1<val2)
        {
            *A=*A-1;
        }

    if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "grass") == 0 && val1>val2)
        {
            *B = *B - (val1-val2);
        }
    else if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "grass") == 0 && val1<val2)
        {
            *B = *B-0;
        }
    else if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "grass") == 0 && val1==val2)
        {
            *B=*B-1;
        }

    if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "water") == 0 && val1>val2)
        {
            *B = *B-0;
        }
    else if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "water") == 0 && val1<val2)
        {
            *A = *A-(val2-val1);
        }
    else if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "water") == 0 && val1==val2)
        {
            *A=*A-1;
        }

    if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "fire") == 0 && val1==val2)
        {
            *A=*A-1;
            *B=*B-1;
        }
        else if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "fire") == 0 && val1>val2)
        {
            *B=*B-1;
        }
        else if (strcmp(elem1, "fire") == 0 && strcmp(elem2, "fire") == 0 && val1<val2)
        {
            *A=*A-1;
        }

    if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "water") == 0 && val1>val2)
        {
            *B = *B - (val1-val2);
        }
    else if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "water") == 0 && val1<val2)
        {
            *B = *B-0;
        }
    else if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "water") == 0 && val1==val2)
        {
            *B=*B-1;
        }

    if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "fire") == 0 && val1>val2)
        {
            *B = *B-0;
        }
    else if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "fire") == 0 && val1<val2)
        {
            *A = *A-(val2-val1);
        }
    else if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "fire") == 0 && val1==val2)
        {
            *A=*A-1;
        }

    if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "grass") == 0 && val1==val2)
        {
            *A=*A-1;
            *B=*B-1;
        }
        else if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "grass") == 0 && val1>val2)
        {
            *B=*B-1;
        }
        else if (strcmp(elem1, "grass") == 0 && strcmp(elem2, "grass") == 0 && val1<val2)
        {
            *A=*A-1;
        }

}

typedef struct{
	int val;
	char elem[10];
	int hp1;
    int hp2;
}MyData;

int main(int argc, char *argv[]){
    int server_sock, client_sock, port_no, client_size, n;
    char buffer[256];
    struct sockaddr_in server_addr, client_addr;
    if (argc < 2) {
        printf("Usage: %s port_no", argv[0]);
        exit(1);
    }

    char *card[]= {"water1", "water2", "water3", "water4", "water5", "fire1", "fire2", "fire3", "fire4", "fire5", "grass1", "grass2", "grass3", "grass4", "grass5"};
    shuffle(card, 15);
   
    
    printf("Server starting ...\n");
    // Create a socket for incoming connections
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) 
       die_with_error("Error: socket() Failed.");
       
    // Bind socket to a port
    bzero((char *) &server_addr, sizeof(server_addr));
    port_no = atoi(argv[1]);
    server_addr.sin_family = AF_INET; // Internet address 
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Any incoming interface
    server_addr.sin_port = htons(port_no); // Local port
    
    if (bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
       die_with_error("Error: bind() Failed.");
       
    // Mark the socket so it will listen for incoming connections
    listen(server_sock, 5);
    printf("Server listening to port %d ...\n", port_no);
    
    printf("Waiting for connection(s) ...\n");

    // Accept new connection
    client_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &client_size);
    if (client_sock < 0) 
        die_with_error("Error: accept() Failed.");

    printf("Client succesfully connected ...\n");    
    // Communicate  
    
    MyData sendData;
    
    sendData.hp1= 10;
    sendData.hp2= 10;
    MyData receivedData;
    
    
    while(1){
    
    	if (recv(client_sock, &receivedData, sizeof(receivedData), 0) == -1) {
    perror("Receive failed");
    close(client_sock);
    exit(EXIT_FAILURE);
}


displayCards(card);

printf("Enter an Card Element: ");
    scanf("%9s", sendData.elem);
    
    printf("Enter an Card Number: ");
    scanf("%d", &sendData.val);
    
    game(&sendData.hp1, &sendData.hp2, sendData.elem, receivedData.elem, sendData.val, receivedData.val);
    
      if (send(client_sock, &sendData, sizeof(sendData), 0) == -1) {
        perror("Send failed");
        close(client_sock);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for opponent's turn...\n");

   char buffer[20];
   snprintf(buffer, sizeof(buffer), "%d", sendData.val);
   
  char result[30];
   strncpy(result, sendData.elem, sizeof(result) - 1);
    result[sizeof(result) - 1] = '\0'; 

    
    strncat(result, buffer, sizeof(result) - strlen(result) - 1);

 
int indexToChange = -1;
    for (int i = 0; i < sizeof(card) / sizeof(card[0]); ++i) {
        if (strcmp(card[i], result) == 0) {
            indexToChange = i;
            break;
        }
    }

    if (indexToChange != -1) {
        card[indexToChange] = "used";
    }

if(strcmp(card[0], "used") == 0 && strcmp(card[1], "used") == 0 && strcmp(card[2], "used") == 0 && strcmp(card[3], "used") == 0 && strcmp(card[4], "used") == 0)
{
    displayHP(sendData.hp1, sendData.hp2);
    printf("All cards used!\n");
    if (sendData.hp1>sendData.hp2)
    {
        printf("You Win!\n");
    }
    else if(sendData.hp1<sendData.hp2)
    {
        printf("Opponent Wins!\n");
    }
    else
    {
        printf("It's a draw!\n");
    }
   if (client_sock != -1) {
        close(client_sock);
        
    }

    if (server_sock != -1) {
        close(server_sock);
        
    }
    break;
}

if(sendData.hp1<=0)
{
	printf("Opponent Wins!\n");
	if (client_sock != -1) {
        close(client_sock);
        
    }

    if (server_sock != -1) {
        close(server_sock);
        
    }
    break;
}

if(sendData.hp2<=0)
{
	printf("You Win!\n");
	if (client_sock != -1) {
        close(client_sock);
        
    }

    if (server_sock != -1) {
        close(server_sock);
        
    }
    break;
}

printf("Opponent used: ");
printf("%s", receivedData.elem);
printf("%d\n", receivedData.val);

displayHP(sendData.hp1, sendData.hp2);


    }
    
    close(client_sock);
    
    close(server_sock);
    
    return 0; 

}
