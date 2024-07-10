//clinet side code for gobackn
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>

int main()
{
    int sockfd,choice;
    char buffer[20],error[20];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family =  AF_INET;
    servaddr.sin_addr.s_addr = htonl("127.0.0.1");
    servaddr.sin_port =  htons(5465);

    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    while (1)
    {
        /* code */
        read(sockfd,buffer,20);
        if(!strcmp(buffer,"EXIT"))
        {
            printf("\nEXITING...\n");
            break;
        }
    printf("\nReceived %s",buffer);
    printf("\nDo you want to report error ?? (1-YES , 0-NO):\t");
    scanf("%d",&choice);
    if(!choice)
        write(sockfd,"-1",sizeof("-1"));
    else
    {
        printf("Enter the sequence of frame where error has occured: ");
        scanf("%s",error);
        write(sockfd,error,sizeof(error));
        read(sockfd,buffer,20);

        printf("\n Received the retransimited frames:%s\n",buffer);

    }

    }
    close(sockfd);
    
}