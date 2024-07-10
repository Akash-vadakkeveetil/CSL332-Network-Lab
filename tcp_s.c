//! main point to be noted the cliend address is used for send and recveve in server side
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
//* No connect in server
//* create socket , bind it , listen , accept ,send and receive ,end
#define MAX_MSG_SIZE 1024

int main() {
    int sockfd, nsd, clilen;
    char recvmsg[MAX_MSG_SIZE], sendmsg[MAX_MSG_SIZE];
    struct sockaddr_in cliaddr, servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections on any interface
    servaddr.sin_port = htons(2000); // Port to bind

    // Bind socket to the server address
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Listen for incoming connections
    listen(sockfd, 5);
    // Accept connection from client
    clilen = sizeof(cliaddr);
    nsd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
    while (1) {
        // Receive message from client
        ssize_t recv_size = recv(nsd, recvmsg, sizeof(recvmsg), 0);
        if (recv_size <= 0) {
            perror("Error receiving message from client");
            break;
        }

        // Add null terminator to received message
        recvmsg[recv_size] = '\0';

        // Print received message from client
        printf("Client: %s\n", recvmsg);

        // If received 'exit' from client, break out of the loop
        if (strcmp(recvmsg, "exit") == 0)
            break;

        // Prompt user for message to send
        printf("Enter message to send (or type 'exit' to quit): ");
        fgets(sendmsg, MAX_MSG_SIZE, stdin);

        // Remove newline character from input
        sendmsg[strcspn(sendmsg, "\n")] = '\0';

        // Send message to client
        send(nsd, sendmsg, strlen(sendmsg), 0);
    }
    close(nsd);
    close(sockfd);
    return 0;
}
