#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
//* create socket , sendto , receive
#define MAX_MSG_SIZE 100

int main() {
    int sockfd;
    char recvmsg[MAX_MSG_SIZE], sendmsg[MAX_MSG_SIZE];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address (localhost)
    servaddr.sin_port = htons(3000); // Server port

    while (1) {
        printf("Enter message to send (or type 'exit' to quit):");
        fgets(sendmsg, MAX_MSG_SIZE, stdin);

        // Remove newline character if present
        sendmsg[strcspn(sendmsg, "\n")] = '\0';

        // Send message to server
        sendto(sockfd, sendmsg, strlen(sendmsg), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

        // If user typed 'exit', break out of the loop
        if (strcmp(sendmsg, "exit") == 0)
            break;

        // Receive message from server
        ssize_t recv_size = recvfrom(sockfd, recvmsg, MAX_MSG_SIZE, 0, NULL, NULL);
        if (recv_size < 0) {
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
