#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<sys/types.h>

#define SERV_PORT 5576

void main(int argc,char** argv)
{
 int k;
 char f[80],s[80];
 struct sockaddr_in servaddr;
 int sockfd;
 
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 
 bzero(&servaddr,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(SERV_PORT);
 servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
 //inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
 connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

 for(;;)
 {
  
 bzero(f,sizeof(f));
 printf("Enter the msg: ");
 k=0;
 while((f[k++]=getchar())!='\n');
  write(sockfd,f,sizeof(f));
 bzero(f,sizeof(f));
  read(sockfd,f,sizeof(f));
  printf("From Server: %s\n",f);

 if((strncmp(f,"exit",4))==0)
 {
   printf("Client Exit\n");
   break;
 }
  
 }

 close(sockfd);
}

