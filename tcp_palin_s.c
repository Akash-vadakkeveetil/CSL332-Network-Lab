#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define MAX_MSG_SIZE 1024

int main() {
    int sockfd, nsd, clilen;
    char recvmsg[MAX_MSG_SIZE], sendmsg[MAX_MSG_SIZE];
    int i, j, flag = 1; // Initialize flag to 1 for palindrome assumption
    struct sockaddr_in cliaddr, servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections on any interface
    servaddr.sin_port = htons(2000); // Port to bind

    // Bind socket to the server address
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Binding failed");
        close(sockfd);
        return 1;
    }

    // Listen for incoming connections
    listen(sockfd, 5);

    // Accept connection from client
    clilen = sizeof(cliaddr);
    nsd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
    if (nsd < 0) {
        perror("Error accepting connection");
        close(sockfd);
        return 1;
    }

    // Receive message from client
    ssize_t recv_size = recv(nsd, recvmsg, sizeof(recvmsg), 0);
    if (recv_size <= 0) {
        perror("Error receiving message from client");
        close(nsd);
        close(sockfd);
        return 1;
    }

    

    // Null-terminate received message
    recvmsg[recv_size] = '\0';

    printf("From client : %s\n",recvmsg);

    // Remove newline character from received message
    recvmsg[strcspn(recvmsg, "\r\n")] = '\0';

    // Check if the received message is a palindrome
    for (i = strlen(recvmsg) - 1, j = 0; i > j; i--, j++) {
        if (recvmsg[i] != recvmsg[j]) {
            flag = 0;
            break;
        }
    }

    // Prepare response based on palindrome check
    if (flag == 1) {
        strcpy(sendmsg, "Palindrome");
    } else {
        strcpy(sendmsg, "Not Palindrome");
    }

    // Send response to client
    send(nsd, sendmsg, strlen(sendmsg), 0);
    printf("Response is send to client\n");

    // Close connections
    close(nsd);
    close(sockfd);

    return 0;
}
