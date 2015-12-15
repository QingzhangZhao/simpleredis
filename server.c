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
#include<sys/epoll.h>
#include<string.h>
#include<signal.h>




#include"sds.h"
#include"hash.h"
#include"cmd_parse.h"
#include"call.h"


#define MAXSIZE 80
#define MYPORT 6379
#define BACKLOG 10
#define BUFSIZE 100



void str_ser(hashTable *table,int sockfd);
int main()
{
  //  signal(SIGINT, sig_handler);
   // signal(SIGQUIT, sig_handler);
	extern int errno;
            
	int sockfd,new_fd,numbytes,ret,epfd,nfds,i,socketfd;
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
  
    struct epoll_event ev,events[20];
	
	//256 is nomeaning
	epfd  = epoll_create(256);
	ev.data.fd=sockfd;
	ev.events=EPOLLIN|EPOLLET;
    
	//?
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);     
    
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
	 printf("db init success!\n");

	 //Loop events
	 for ( ; ; ) {

        nfds=epoll_wait(epfd,events,20,500);

        for(i=0;i<nfds;++i)
        {
            if(events[i].data.fd==sockfd)

            {
            	new_fd=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size);
				if(new_fd<0)
				{
					printf("Error when  accept()!\n");
					printf("Reason:%s\n",strerror(errno));
					exit(0);
		        }

                char *str = inet_ntoa(their_addr.sin_addr);
                printf("accapt a connection from %s\n",str);

                ev.data.fd=new_fd;

                ev.events=EPOLLIN|EPOLLET;
                //ev.events=EPOLLIN;

                epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&ev);
            }
            else if(events[i].events&EPOLLIN)

            {
                if ( (socketfd = events[i].data.fd) < 0)
                    continue;
                str_ser(table,socketfd);

                 


                ev.data.fd=socketfd;

                ev.events=EPOLLIN|EPOLLET;

                epoll_ctl(epfd,EPOLL_CTL_MOD,socketfd,&ev);

            }
        }
    }
   //free db
   freeTable(table);
	 return 0;
}







void str_ser(hashTable* table,int sockfd)
{
	char recvs[MAXSIZE];char *sends;
	memset(recvs,0,sizeof(recvs));
	int n=0;
	char * a;
	a="\n";
		if((n=recv(sockfd,recvs,MAXSIZE,0))==0)
		{
			close(sockfd);
			printf("a connection lost\n");
			return;
		}
		sends = cmd_parse(table,recv_parse(recvs));
		memset(recvs,0,sizeof(recvs));
		send(sockfd,sends,strlen(sends),0);
		send(sockfd,a,1,0);
		//free(sends);
}


