//server code for goback n
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#define WINDOW_SIZE 4
int main()
{
    int sockfd,socket_2,length,i,j,status,client_address_length;
    char buffer[20],frame[20],temp[20],ack[20];
    struct sockaddr_in servaddr,client_address;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family =  AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port =  htons(5465);
    bind(sockfd,(struct  sockaddr*)&servaddr,sizeof(servaddr));
    listen(sockfd,5);
    client_address_length = sizeof(&client_address);
    socket_2 = accept(sockfd,(struct sockaddr*)&client_address,&client_address_length);
    printf("Enter the text\n");
    scanf("%s",buffer);
    i=0;
    while(i<strlen(buffer))
    {
        memset(frame,0,20);
        strncpy(frame,buffer+i,WINDOW_SIZE);
        printf("\nTransmitting frames\n");
        for(j=0;j<length;j++)
        {
            printf("%d",i+j);
            sprintf(temp,"%d",i+j);
            strcat(frame,temp);
        }
        printf("\n");
        write(socket_2,frame,sizeof(frame));
        read(socket_2,ack,20);
        sscanf(ack,"%d",&status);
        if(status == -1)
        {
            printf("Transmission is successful\n");
        }
        else{
            printf("Received error in %d\n",status);
            printf("Retransmitting Frames\n");
            for(j=0;;)
            {
                frame[j] =  buffer[j+status];
                printf("%d",j+status);
                j++;
                if((j+status)%WINDOW_SIZE == 0)
                    break;
            }
        printf("\n");
        frame[j] = '\0';
        length = strlen(frame);
        for(j=0;j<length;j++)
        {
            sprintf(temp,"%d",j+status);
            strcat(frame,temp);
        }
        write(socket_2,frame,sizeof(frame));
        }
        i+=WINDOW_SIZE;
    }
    write(socket_2,"EXIT",sizeof("EXIT"));
    printf("\nEXITING...\n");
    close(sockfd);
    close(socket_2);
}