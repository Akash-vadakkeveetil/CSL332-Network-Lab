/*
! ERROR CHECKING TO BE CONSIDERD
! sockfd == -1 -> creation failed else success
! if bind and listen !=0 the failed else successs
! if accept < 0 then failed else success
! send or recv == -1 then error
! connect == -1 then error
*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
//* creation of socket , connect , send and recv
#define MAX_MSG_SIZE 1024

int main() {
    int sockfd;
    char sendmsg[MAX_MSG_SIZE], recvmsg[MAX_MSG_SIZE];
    struct sockaddr_in servaddr;//sockaddr_in defined in netinet/in.h to store socket address information for IPv4.

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loopback address
    servaddr.sin_port = htons(2000);

    // Connect to server
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    while (1) {
        printf("Enter message to send (or type 'exit' to quit):");
        //fgets(sendmsg, MAX_MSG_SIZE, stdin);
        gets(sendmsg);
        
        sendmsg[strcspn(sendmsg, "\n")] = '\0';//finds index of \n and replce it with \0
        // Send message to server
        send(sockfd, sendmsg, strlen(sendmsg), 0);

        // If user typed 'exit', break out of the loop
        if (strcmp(sendmsg, "exit") == 0)
            break;

        // Receive message from server
        ssize_t recv_size = recv(sockfd, recvmsg, sizeof(recvmsg), 0);
        if (recv_size <= 0) {
            perror("Error receiving message from server");
            break;
        }

        // Add null terminator to received message
        recvmsg[recv_size] = '\0';

        // Print received message from server
        printf("Server: %s\n", recvmsg);
    }
    close(sockfd);

    return 0;
}
