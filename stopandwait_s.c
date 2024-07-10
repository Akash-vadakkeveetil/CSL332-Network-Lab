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
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    Frame recv_frame, send_frame;
    int expected_sq_no = 0;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket to server address
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Receive frame from client
        int recv_len = recvfrom(sockfd, &recv_frame, sizeof(Frame), 0,
                                (struct sockaddr *)&clientAddr, &addrLen);
        if (recv_len < 0) {
            perror("Receive error");
            continue;
        }

        // Check if the received frame is a data frame with the expected sequence number
        if (recv_frame.frame_kind == 1 && recv_frame.sq_no == expected_sq_no) {
            printf("Frame received: %s\n", recv_frame.data);

            // Prepare ACK frame to send back
            send_frame.frame_kind = 0;  // ACK frame
            send_frame.sq_no = 0;       // ACK sequence number (not used in basic Stop-and-Wait)
            send_frame.ack = recv_frame.sq_no + 1;  // Next expected sequence number
            strcpy(send_frame.data, "");  // No data in ACK frame

            // Send ACK to client
            sendto(sockfd, &send_frame, sizeof(Frame), 0,
                   (struct sockaddr *)&clientAddr, addrLen);
            
            printf("ACK Sent\n");

            // Move to the next expected sequence number
            expected_sq_no = (expected_sq_no + 1) % 2;
        } else {
            printf("Invalid frame received or out-of-order\n");
        }
    }

    close(sockfd);
    return 0;
}
