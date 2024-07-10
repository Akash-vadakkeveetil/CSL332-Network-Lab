#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

#define max 1024

void main()
{
    int sockfd, nsd, i, num;
    struct sockaddr_in servaddr, cliaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Bind socket to IP and port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(2000);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Listen for incoming connections
    listen(sockfd, 5);

    // Accept connection from client
    int clilen = sizeof(cliaddr);
    nsd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);

    // Receive number from client
    ssize_t recv_size = recv(nsd, &num, sizeof(num), 0);

    // Check if recv was successful
    if (recv_size > 0) {
        printf("Received number from client: %d\n", num);

        // Reverse the number (assuming single digit for simplicity)
        int reversed = 0;
        while (num > 0) {
            reversed = reversed * 10 + num % 10;
            num /= 10;
        }

        // Send reversed number back to client
        send(nsd, &reversed, sizeof(reversed), 0);
        printf("Sent reversed number to client: %d\n", reversed);
    } else {
        printf("Failed to receive number from client.\n");
    }

    // Close sockets
    close(nsd);
    close(sockfd);
}
