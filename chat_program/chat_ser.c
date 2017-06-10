#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>

#define SERV_PORT 5576

void main(int argc,char** argv)
{
 int k;
 char s[80], f[80];
 struct sockaddr_in servaddr,cliaddr;
 int listenfd,connfd,clilen;

 listenfd=socket(AF_INET,SOCK_STREAM,0);
 bzero(&servaddr,sizeof(servaddr));

 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(SERV_PORT);
 servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");

 clilen=sizeof(cliaddr); 
 bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
 listen(listenfd,1);
 connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);

 printf("\n client connected\n");

 for(;;)
 {
   bzero(f,sizeof(f));
   read(connfd,f,sizeof(f));
   printf("\nFrom client: %s\n",f);
   bzero(f,sizeof(f));
   printf("\nEnter the msg: ");
   k=0;
   while((f[k++]=getchar())!='\n');
     write(connfd,f,sizeof(f));
   if(strncmp("exit",f,4)==0)
   {
     printf("Server exit\n");
     break;
   }
   
 }

 close(listenfd);
}

