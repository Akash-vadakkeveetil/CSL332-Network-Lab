//! in udp no connect and accept rest all same
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
//* create socket , bind to it , send and receive
#define MAX_MSG_SIZE 100

int main() {
    int sockfd, n;
    char recvmsg[MAX_MSG_SIZE], sendmsg[MAX_MSG_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any IP
    servaddr.sin_port = htons(3000); // Port to bind to

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
        perror("Bind failed");
        return 1;
    }

    len = sizeof(cliaddr);

    while (1) {
        // Receive message from client
        n = recvfrom(sockfd, recvmsg, MAX_MSG_SIZE, 0, (struct sockaddr *) &cliaddr, &len);
        if (n < 0) {
            perror("Error receiving message from client");
            break;
        }
        
        // Add null terminator to received message
        recvmsg[n] = '\0';
        printf("Client: %s\n", recvmsg);

        // If received message is 'exit', break out of the loop
        if (strcmp(recvmsg, "exit") == 0)
            break;

        // Get message to send back to client
        printf("Enter reply: ");
        fgets(sendmsg, MAX_MSG_SIZE, stdin);

        // Remove newline character if present
        sendmsg[strcspn(sendmsg, "\n")] = '\0';

        // Send message back to client
        sendto(sockfd, sendmsg, strlen(sendmsg), 0, (const struct sockaddr *) &cliaddr, len);
    }

    close(sockfd);
    return 0;
}
