#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define SERV_PORT 5576

void main(int argc,char** argv[])
{
 FILE fp;
 char s[80],f[80];
 struct sockaddr_in servaddr;
 int sockfd;

 sockfd=socket(AF_INET,SOCK_STREAM,0);
 bzero(&servaddr,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(SERV_PORT);
 inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
 connect(sockfd,(struct servaddr*)&servaddr,sizeof(servaddr));
 printf("Enter the command:");
 scanf("%s",s);
 write(sockfd,s,sizeof(s));
 printf("\n Data from the server: \n");
 while(read(sockfd,f,80)!=0)
 {
  fputs(f,stdout);
 }
 close(sockfd);
}
