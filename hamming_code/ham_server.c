#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

#define SERV_PORT 5576

void main(int argc,char** argv)
{
 struct sockaddr_in servaddr,cliaddr;
 int listenfd,connfd,clilen;

 listenfd=socket(AF_INET,SOCK_STREAM,0);
 bzero(&servaddr,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(SERV_PORT);
 servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
 bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
 listen(listenfd,1);
 clilen=sizeof(cliaddr);
 connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
 printf("Client connected\n");

 int data2[100];
 read(connfd,data2,100);
 
 int c1 = (((data2[3-1]^data2[5-1]) ^ (data2[7-1]^data2[9-1])) ^ (data2[11-1]^data2[1-1]));
 int c2 = (((data2[3-1]^data2[6-1]) ^ (data2[7-1]^data2[10-1])) ^ (data2[11-1]^data2[2-1]));
 int c3 = (((data2[5-1]^data2[6-1]) ^ (data2[7-1]^data2[12-1])) ^ data2[4-1]);
 int c4 = (((data2[9-1]^data2[10-1]) ^ (data2[11-1]^data2[12-1])) ^ data2[8-1]);

 printf("%d %d %d %d",c1,c2,c3,c4);

 if(c1==0 && c2==0 && c3==0 && c4==0)
   printf("No Error\n");
 else
   printf("Error\n");

 close(listenfd);
}
