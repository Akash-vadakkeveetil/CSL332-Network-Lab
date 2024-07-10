#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define MAX_MSG_SIZE 1024

int main() {
    int sockfd;
    char sendmsg[MAX_MSG_SIZE], recvmsg[MAX_MSG_SIZE];
    struct sockaddr_in servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Loopback address
    servaddr.sin_port = htons(2000);

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    // Input message from user
    printf("Enter message to check palindrome or not: ");
    fgets(sendmsg, MAX_MSG_SIZE, stdin);

    // Remove newline character from sendmsg
    sendmsg[strcspn(sendmsg, "\r\n")] = '\0';

    // Send message to server
    send(sockfd, sendmsg, strlen(sendmsg), 0);

    // Receive message from server
    ssize_t recv_size = recv(sockfd, recvmsg, sizeof(recvmsg), 0);
    if (recv_size <= 0) {
        perror("Error receiving message from server");
        close(sockfd);
        return 1;
    }

    // Null-terminate received message
    recvmsg[recv_size] = '\0';

    // Print received message from server
    printf("Server: %s\n", recvmsg);

    // Close socket
    close(sockfd);

    return 0;
}
