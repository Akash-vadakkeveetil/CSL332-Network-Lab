#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

void main()
{
    int sockfd, num, reversed;
    struct sockaddr_in servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Connect to server
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(2000);
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Input number from user
    printf("Enter number to send: ");
    scanf("%d", &num);

    // Send number to server
    send(sockfd, &num, sizeof(num), 0);
    printf("Sent number to server: %d\n", num);

    // Receive reversed number from server
    ssize_t recv_size = recv(sockfd, &reversed, sizeof(reversed), 0);
    if (recv_size > 0) {
        printf("Received reversed number from server: %d\n", reversed);
    } else {
        printf("Failed to receive reversed number from server.\n");
    }

    // Close socket
    close(sockfd);
}
