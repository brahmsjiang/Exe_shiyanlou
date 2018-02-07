
#include <sys/socket.h>	//socket
#include <sys/types.h>	//setsockopt
#include <unistd.h>	//close
#include <netinet/in.h>	//sockaddr_in
#include <arpa/inet.h>	//inet_addr
#include <stdio.h>	//perror
#include <stdlib.h>	//perror
#include <string.h>	//strlen,strncmp,strcmp
#include <time.h>	//time


#define SERV_PORT 8888
#define SERV_ADDR "127.0.0.1"
#define ERROR(par) {perror((par));exit(-1);}
#define MAXLEN 128

char recvmesg[MAXLEN];
char sendmesg[MAXLEN];

int main(){
	memset(recvmesg,0,sizeof(recvmesg));
	memset(sendmesg,0,sizeof(sendmesg));
	sockaddr_in skadd_in;
	skadd_in.sin_family=PF_INET;
	skadd_in.sin_port=htons(SERV_PORT);
	skadd_in.sin_addr.s_addr=inet_addr(SERV_ADDR);
	int sockfd=socket(PF_INET,SOCK_STREAM,0);
	if(sockfd<0)ERROR("socket err");
	//set socket option to avoid err
	int on=1;
	if((setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)ERROR("setsocketopt err");

	if(bind(sockfd,(sockaddr*)&skadd_in,sizeof(skadd_in))<0)ERROR("bind err");
	if(listen(sockfd,5)<0)ERROR("listen err");
	int confd;
	if((confd=accept(sockfd,NULL,NULL)) <0)ERROR("accept err");
	printf("accept ok!!\n");	
	while(1){
			if(recv(confd,recvmesg,sizeof(recvmesg),0)<=0)ERROR("recv err");
			printf("recv ok!!\n");	
			if(0==strncmp(recvmesg,"echo",strlen("echo"))){
				printf("recv cmd: echo\n");
				do{
					memset(recvmesg,0,sizeof(recvmesg));
					if(recv(confd,recvmesg,sizeof(recvmesg),0)<=0)ERROR("recv err");
					printf("echo mode:cur recvmesg is %s!!\n",recvmesg);
					memcpy(sendmesg,recvmesg,sizeof(recvmesg)+1);
					send(confd,sendmesg,strlen(sendmesg),0);
					memset(sendmesg,0,sizeof(sendmesg));
				}while(0!=strncmp(recvmesg,"eof",strlen("eof")));
			}
			else if(0==strncmp(recvmesg,"time",strlen("time"))){
				printf("recv cmd: time\n");
				time_t timenow;
				time(&timenow);
				memcpy(sendmesg,ctime(&timenow),sizeof(ctime(&timenow)+1));
				send(confd,sendmesg,strlen(sendmesg),0);

			}
			else if(0==strncmp(recvmesg,"quit",strlen("quit"))){
				memcpy(sendmesg,"server closed",sizeof("server closed")+1);
				send(confd,sendmesg,strlen(sendmesg),0);
				break;
			}else{
				printf("recv cmd:others\n");
				memcpy(sendmesg,"cmd invaild",sizeof("cmd invaild")+1);
				send(confd,sendmesg,strlen(sendmesg),0);
			}
	}
	close(sockfd);

	return 0;
}
