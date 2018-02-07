
#include <sys/socket.h>	//socket
#include <unistd.h>	//close
#include <netinet/in.h>	//sockaddr_in
#include <arpa/inet.h>	//inet_addr
#include <stdio.h> //perror
#include <stdlib.h> //perror
#include <string.h> //strlen,strncmp,strcmp

#define SERVERIP "127.0.0.1"
#define SERVERPORT 8888
#define ERROR(par) {perror((par));exit(-1);}
#define MAXLEN 128

char message[MAXLEN];

int main()
{
	memset(message,0,sizeof(message));
	sockaddr_in servaddr;
	servaddr.sin_family=PF_INET;
	servaddr.sin_port=htons(SERVERPORT);
	servaddr.sin_addr.s_addr=inet_addr(SERVERIP);

	int sockfd=socket(PF_INET,SOCK_STREAM,0);
	if(sockfd<0)ERROR("socket err");
	if(connect(sockfd,(sockaddr*)&servaddr,sizeof(servaddr))<0)ERROR("connect err");
	while(1){
		printf("enter your cmd(echo/time/quit): ");
		memset(message,0,sizeof(message));
		fgets(message,MAXLEN,stdin);
		send(sockfd,message,strlen(message),0);
		if(0==strncmp(message,"echo",strlen("echo"))){
			do{
				memset(message,0,sizeof(message));
				fgets(message,MAXLEN,stdin);
				send(sockfd,message,strlen(message),0);
				memset(message,0,sizeof(message));
				if(recv(sockfd,message,MAXLEN,0)<0)ERROR("recv err");
				printf("%s\n",message);
			}while(0!=strncmp(message,"eof",strlen("eof")));
		}
		else{
			if(recv(sockfd,message,MAXLEN,0)<0)ERROR("recv err");
			printf("%s\n",message);
			if(0==strncmp(message,"server closed",strlen("server closed"))){
				break;
			}

		}
	}
	close(sockfd);
	return 0;
}




