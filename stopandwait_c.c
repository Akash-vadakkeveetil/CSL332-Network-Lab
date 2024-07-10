#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 3000
#define MAX_DATA_SIZE 1024

typedef struct {
    int frame_kind; // 0 for acknowledgment, 1 for data frame
    int sq_no;      // Sequence number
    int ack;        // Acknowledgment number
    char data[MAX_DATA_SIZE];  // Data packet
} Frame;

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    Frame send_frame, recv_frame;
    socklen_t addrLen = sizeof(serverAddr);
    char buffer[MAX_DATA_SIZE];
    int frame_id = 0;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(PORT);

    while (1) {
        // Sending data frame
        send_frame.frame_kind = 1;  // Data frame
        send_frame.sq_no = frame_id;  // Sequence number
        send_frame.ack = 0;  // No acknowledgment for client in basic Stop-and-Wait
        printf("Enter data: ");
        scanf("%s", buffer);
        strcpy(send_frame.data, buffer);

        // Send data frame to server
        sendto(sockfd, &send_frame, sizeof(Frame), 0,
               (struct sockaddr *)&serverAddr, addrLen);
        printf("Frame Sent\n");

        // Receive acknowledgment from server
        int recv_len = recvfrom(sockfd, &recv_frame, sizeof(Frame), 0,
                                (struct sockaddr *)&serverAddr, &addrLen);
        if (recv_len < 0) {
            perror("Receive error");
            continue;
        }

        // Check if received frame is an acknowledgment with expected sequence number
        if (recv_frame.frame_kind == 0 && recv_frame.ack == frame_id + 1) {
            printf("ACK received\n");
            frame_id++;  // Move to the next frame ID
        } else {
            printf("Invalid ACK received or out-of-order\n");
        }
    }

    close(sockfd);
    return 0;
}
