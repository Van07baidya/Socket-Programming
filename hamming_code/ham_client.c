#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<math.h>
#include<string.h>

#define SERV_PORT 5576

void main(int argc,char** argv)
{
 int i;
 struct sockaddr_in servaddr;
 int sockfd;

 sockfd=socket(AF_INET,SOCK_STREAM,0);
 bzero(&servaddr,sizeof(servaddr));
 servaddr.sin_family=AF_INET;
 servaddr.sin_port=htons(SERV_PORT);
 servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
 connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

 int data1[8];
 int data2[12]={0};
 printf("Enter the binary data (8 bits) : ");
 for(i=0;i<8;i++)
 {
  scanf("%d",&data1[i]);
 }

 int r=1;
 while(pow(2,r) < 8+r+1)
 {
  r++;
 }

 int k=0;
 int d1=0;
 int l=8+r;

 for(i=1;i<=l;i++)
 {
  if(i==pow(2,k))
  {
   data2[i-1]=-1;
   k++;
  }
  else
  {
   data2[i-1]=data1[d1];
   d1++;
  }
 }

 printf("Redundant array: ");
 for(i=0;i<l;i++)
  printf("%d ",data2[i]);
 
 int r1 = (((data2[3-1]^data2[5-1]) ^ (data2[7-1]^data2[9-1])) ^ data2[11-1]);
 int r2 = (((data2[3-1]^data2[6-1]) ^ (data2[7-1]^data2[10-1])) ^ data2[11-1]);
 int r3 = ((data2[5-1]^data2[6-1]) ^ (data2[7-1]^data2[12-1]));
 int r4 = ((data2[9-1]^data2[10-1]) ^ (data2[11-1]^data2[12-1]));

 data2[1-1]=r1;
 data2[2-1]=r2;
 data2[4-1]=r3;
 data2[8-1]=r4;
 
 printf("\n Redundant array: ");
 
 for(i=0;i<l;i++)
  printf("%d",data2[i]);
 
 write(sockfd,data2,sizeof(data2));
 close(sockfd);
}

