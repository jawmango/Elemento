
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

typedef struct{
	int val;
	char elem[10];
	int hp1;
    int hp2;
}MyData;

typedef struct {
    char suit[10];
    int rank;
} Card;

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


int main(int argc,  char *argv[]){

	
    
    int client_sock,  port_no,  n;
    struct sockaddr_in server_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
        printf("Usage: %s hostname port_no",  argv[0]);
        exit(1);
    }

    printf("Client starting ...\n");
    // Create a socket using TCP
    client_sock = socket(AF_INET,  SOCK_STREAM,  0);
    if (client_sock < 0) 
        die_with_error("Error: socket() Failed.");

    printf("Looking for host '%s'...\n", argv[1]);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        die_with_error("Error: No such host.");
    }
    printf("Host found!\n");

    // Establish a connection to server
    port_no = atoi(argv[2]);
    bzero((char *) &server_addr,  sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,  
         (char *)&server_addr.sin_addr.s_addr, 
         server->h_length);
         
    server_addr.sin_port = htons(port_no);

    printf("Connecting to server at port %d...\n", port_no);
    if (connect(client_sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
        die_with_error("Error: connect() Failed.");

    printf("Connection successful!\n");

    // Communicate
    char *card[]= {"water1", "water2", "water3", "water4", "water5", "fire1", "fire2", "fire3", "fire4", "fire5", "grass1", "grass2", "grass3", "grass4", "grass5"};
    shuffle(card, 15);

    MyData sendData;
    
    MyData receivedData;
    receivedData.hp1 = 10;
    receivedData.hp2 = 10;
    
    while(1){
    
    if(strcmp(card[0], "used") == 0 && strcmp(card[1], "used") == 0 && strcmp(card[2], "used") == 0 && strcmp(card[3], "used") == 0 && strcmp(card[4], "used") == 0)
    {

    printf("All cards used!\n");
    if (receivedData.hp1>receivedData.hp2)
    {
        printf("Opponent Wins!\n");
    }
    else if(receivedData.hp1<receivedData.hp2)
    {
        printf("You Win!\n");
    }
    else
    {
        printf("It's a draw!\n");
    }
   if (client_sock != -1) {
        close(client_sock);
        
    }

    
    break;
    }
    
    if(receivedData.hp2<=0)
{
	printf("Opponent Wins!\n");
	if (client_sock != -1) {
        close(client_sock);
        
    }

    
    break;
}

if(receivedData.hp1<=0)
{
	printf("You Win!\n");
	if (client_sock != -1) {
        close(client_sock);
        
    }

    
    break;
}

        
    displayCards(card);
    
    printf("Enter an Card Element: ");
    scanf("%9s", sendData.elem);
    
    printf("Enter an Card Number: ");
    scanf("%d", &sendData.val);
    
    
    
      if (send(client_sock, &sendData, sizeof(sendData), 0) == -1) {
        perror("Send failed");
        close(client_sock);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for opponent's turn\n");

    
	if (recv(client_sock, &receivedData, sizeof(receivedData), 0) == -1) {
    perror("Receive failed");
    close(client_sock);
    exit(EXIT_FAILURE);
    
}



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

printf("Opponent used: ");
printf("%s", receivedData.elem);
printf("%d\n", receivedData.val);
displayHP(receivedData.hp2, receivedData.hp1);



}
    close(client_sock);
    
    return 0;

}
