//server code for udp palindrome
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
    int sockfd,i,j;
    char sendmsg[max],recvmsg[max],sample[max];
    struct sockaddr_in servaddr,cliaddr;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(3000);

    if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
        perror("BINDING FAILED\n");

    int len = sizeof(cliaddr);



    int recv_size = recvfrom(sockfd,recvmsg,sizeof(recvmsg),0,(struct sockaddr*)&cliaddr,&len);
    puts(recvmsg);

    recvmsg[recv_size] = '\0';


    
    for(i=0,j=strlen(recvmsg)-1;i<strlen(recvmsg);i++,j--)
    {
        sample[j] = recvmsg[i];
    }
    sample[strlen(recvmsg)] = '\0'; // Ensure null termination

    if(strcmp(sample,recvmsg) == 0)
    {
        strcpy(sendmsg, "PALINDROME");
    }
    else{
        strcpy(sendmsg, "NOT PALINDROME");
    }

    sendmsg[sizeof(sendmsg)] = '\0';
    
    sendto(sockfd,sendmsg,strlen(sendmsg),0,(struct sockaddr*)&cliaddr,len);

    close(sockfd);
}