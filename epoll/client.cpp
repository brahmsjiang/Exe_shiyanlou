
#include "utility.h"

int main(int argc, char* argv[])
{
	//server's IP+port to connect
	struct sockaddr_in serverAddr;
	serverAddr.sin_family=PF_INET;
	serverAddr.sin_port=htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr=inet_addr(SERVER_IP);
	//create socket
	int sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock<0){
		perror("sock error");exit(-1);
	}
	//connect to server
	if(connect(sock,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
		perror("connect error");exit(-1);
	}
	//create pipe,fd[0] for father read,fd[1] for child write
	int pipe_fd[2];
	if(pipe(pipe_fd)<0){
		perror("pipe error");exit(-1);
	}
	//create epoll
	int epfd=epoll_create(EPOLL_SIZE);
	if(epfd<0){
		perror("epfd error");exit(-1);
	}
	static struct epoll_event events[2];
	//add sock and pipe readfd to event tables
	addfd(epfd,sock,true);
	addfd(epfd,pipe_fd[0],true);
	//client is work or not
	bool isClientwork=true;
	//message buf
	char message[BUF_SIZE];
	//fork
	int pid=fork();
	if(pid<0){
		perror("fork error");exit(-1);
	}
	else if(pid==0){
		//child to write,close read
		close(pipe_fd[0]);
		printf("Please input 'exit' to exit the chat room\n");
		while(isClientwork){
			bzero(&message,BUF_SIZE);
			fgets(message,BUF_SIZE,stdin);
			//user input exit then exit
			if(strncasecmp(message,EXIT,strlen(EXIT))==0){
				isClientwork=0;
			}
			else{
				if(write(pipe_fd[1],message,strlen(message)-1)<0){
					perror("fork error");exit(-1);
				}
			}
		}
	}
	else{
		//father to read,close write
		close(pipe_fd[1]);
		//main loop
		while(isClientwork){
			int epoll_events_count=epoll_wait(epfd,events,2,-1);
			//slove event
			for(int i=0;i<epoll_events_count;i++){
				bzero(&message,	BUF_SIZE);
				//server send message
				if(events[i].data.fd==sock){
					//receive from server
					int ret=recv(sock,message,BUF_SIZE,0);
					//server closed
					if(ret==0){
						printf("Server closed connection:%d",sock);
						close(sock);
						isClientwork=0;
					}
					else
						printf("%s\n",message);
				}
				//child write occur,father solve send event
				else{
					int ret=read(events[i].data.fd,message,BUF_SIZE);
					if(ret==0)
						isClientwork=0;
					else{
						send(sock,message,BUF_SIZE,0);
					}
				}
			}//for
		}//while
	}

	if(pid){
		close(pipe_fd[0]);
		close(sock);
	}else{
		close(pipe_fd[1]);
	}
	return 0;

}






















