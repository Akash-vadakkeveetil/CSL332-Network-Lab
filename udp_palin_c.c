//client program for udp palindorme
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>

#define max 1024
void main()
{
    int sockfd;
    char sendmsg[max],recvmsg[max];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(3000);


    printf("Enter word or type 'EXIT' to quit:\n");
    fgets(sendmsg,sizeof(sendmsg),stdin);


    sendmsg[strcspn(sendmsg,"\n")] = '\0';

    sendto(sockfd,sendmsg,strlen(sendmsg),0,(struct sockaddr*)&servaddr,sizeof(servaddr));


    recvfrom(sockfd,recvmsg,sizeof(recvmsg),0,NULL,NULL);
    // recvmsg[strlen(recvmsg) - 1] = '\0'; // Ensure null termination
    puts(recvmsg);


    close(sockfd);
}