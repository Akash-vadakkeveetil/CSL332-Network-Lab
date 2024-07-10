#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

int main()
{   
    FILE *fp1;
    char f[100];

    int sd,len,nsd,clilen;
    char sendmsg[30],recvmsg[30],s[100];

    struct sockaddr_in cliaddr,servaddr;
    sd =socket(AF_INET,SOCK_STREAM,0);//create socket


    //initialize
    servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(2000);


    //bind to network
    bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    //listen to socket
    listen(sd,5);

    //accepet listening thihgs__
    clilen=sizeof(cliaddr);
    nsd=accept(sd,(struct sockaddr*)&cliaddr,&clilen);

    //receive from client
    recv(nsd,recvmsg,sizeof(recvmsg),0);

    printf("Destination file name: \n");
    scanf("%s",f);
    fp1 = fopen(f,"w");
    fprintf(fp1,"%s",recvmsg);
}
