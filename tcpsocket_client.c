#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<netdb.h>
#include<stdarg.h>
#include<string.h>

#define MAXSIZE 80
void str_cli(FILE *,int);

int main(int argc,char * argv[])
{
	int sockfd,ret,len;
	struct sockaddr_in ser_addr;
	char *myname;
	struct hostent *sh;
	struct in_addr addrs;

//	if (argc!=2)
//	{
//		printf("parameters not match!\n");
//		exit(0);
//	}

//	if((sh=gethostbyname(argv[1]))==NULL)
//	{
//		printf("error when gethostbyname!\n");
//		exit(0);
//	}
  

	addrs.s_addr=inet_addr("127.0.0.1");
//	for (;*addrs!=NULL;addrs++)
//	{
		sockfd=socket(AF_INET,SOCK_STREAM,0);
		if(sockfd<0)
		{
			printf("error in socket\n");
			exit(0);
		}

		ser_addr.sin_family=AF_INET;
		ser_addr.sin_port=htons(6379);
		memcpy(&ser_addr.sin_addr,&addrs,sizeof(struct in_addr));
		bzero(ser_addr.sin_zero,8);
		ret=connect(sockfd,(struct sockaddr *)&ser_addr,sizeof(struct sockaddr));
		if(ret==0)
;
		else
		{
			printf("error connecting!\n");
			close(sockfd);
		}
//	}

//		if(*addrs==NULL)
//		{
//			printf("can't get connected with server!\n");
//			exit(0);
//		}
		str_cli(stdin,sockfd);

		close(sockfd);
		exit(0);
}

void str_cli(FILE *fp,int sockfd)
{
	char sends[MAXSIZE],recvs[MAXSIZE];
	memset(sends,0,sizeof(sends));
	memset(recvs,0,sizeof(recvs));
	int n=0;
	printf("127.0.0.0:6379>");
	while(fgets(sends,MAXSIZE,fp)!=NULL)
	{

		send(sockfd,sends,strlen(sends),0);
		if((n=recv(sockfd,recvs,MAXSIZE,0))==0)
		{
			printf("error receiving data!\n");
				exit(1);
		}
		recvs[n]=0;
		fputs(recvs,stdout);
		memset(recvs,0,sizeof(recvs));
	   printf("127.0.0.0:6379>");
	}
}












