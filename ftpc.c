#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

int main()
{
FILE *fp1; // File pointer for file operations
char f[100]; //array to store file name

int sockfd,len;
char sendmsg[30],recvmsg[30],s[100];

struct sockaddr_in cliaddr,servaddr;//struct for client and server address

sockfd  =socket(AF_INET,SOCK_STREAM,0);//create socket

//initiaze server address struct
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
servaddr.sin_port = htons(2000);

//connect to server
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));


//read and write from file
printf("Enter the file name :\n");
scanf("%s",f);
fp1 = fopen(f,"r");

fscanf(fp1,"%s",s);
strcpy(sendmsg,s);
len = strlen(sendmsg);

//send to server
send(sockfd,sendmsg,strlen(sendmsg),0);
}