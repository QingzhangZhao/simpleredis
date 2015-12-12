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


#include"sds.h"
#include"hash.h"
#include"cmd_parse.h"
#include"call.h"
#define MAXSIZE 80
#define MYPORT 1234
#define BACKLOG 10
#define BUFSIZE 100

void str_ser(hashTable *table,int sockfd);
int main()
{

	extern int errno;

	int sockfd,new_fd,numbytes,ret;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	char *buf;
	pid_t pid;

	//socket
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Error whenn  socket()!\n");
		printf("Reason:%s\n",strerror(errno));
		exit(1);
	}

	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(MYPORT);
	my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	bzero(&(my_addr.sin_zero),8);
	
	//bind
	ret=bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));
	if(ret<0)
	{
		printf("Error when bind()\n");
		printf("Reason:%s\n",strerror(errno));
		exit(0);
	}
	
	//listen
	ret=listen(sockfd,BACKLOG);
	if(ret<0)
	{
		printf("Error in listen()");
		printf("Reason:%s\n",strerror(errno));
		exit(0);
	}else{
	 printf("The server is now ready to accept connections on port %d\n",MYPORT);

	}

     //init db
	 hashTable * table = new_Table(3);
	 
	//EventLoop accept
	while(1)
	{
		sin_size=sizeof(struct sockaddr_in);
		new_fd=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size);
		if(new_fd<0)
		{
			printf("Error when  accept()!\n");
			printf("Reason:%s\n",strerror(errno));
			exit(0);
		}
        
//		printf("23333");
		//if((pid=fork())==0)
		//{
	//		close(sockfd);
//			str_ser(new_fd);
//
//			close(new_fd);
//			exit(0);
//		}
//		else 
//			close(sockfd);	
              
	      str_ser(table,new_fd);

		  printf("connecting  over\n");
	}

		close(sockfd);
		exit(0);
}

void str_ser(hashTable* table,int sockfd)
{
	char recvs[MAXSIZE];char *sends;
	memset(recvs,0,sizeof(recvs));
	int n=0;
	char * a;
	a="\n";

	while(1)
	{
		if((n=recv(sockfd,recvs,MAXSIZE,0))==0)
		{
			printf("OK");
			return;
		}
		sends = cmd_parse(table,recv_parse(recvs));
		memset(recvs,0,sizeof(recvs));
		send(sockfd,sends,strlen(sends),0);
		send(sockfd,a,1,0);
		//free(sends);
	}
}
