
#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <iostream>
#include <list>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define EPOLL_SIZE 5000
#define BUF_SIZE 0xFFFF
#define SERVER_WELCOME "Welcome you join to the chat room! Your chat ID is: Client #%d"
#define SERVER_MESSAGE "ClientID %d say >> %s"
#define EXIT "EXIT"
#define CAUTION "There is only one in the chat room!"

using namespace std;

list<int> clients_list;

int setnonblocking(int sockfd)
{
	fcntl(sockfd,F_SETFL,fcntl(sockfd,F_GETFL,0)|O_NONBLOCK);
	return 0;
}

void addfd(int epollfd,int fd,bool enable_et)
{
	struct epoll_event ev;
	ev.data.fd=fd;
	ev.events=EPOLLIN;
	if(enable_et)
		ev.events=EPOLLIN|EPOLLET;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
	setnonblocking(fd);
	printf("fd added to epoll!\n\n");
}

int sendBroadcastmessage(int clientfd)
{
	char buf[BUF_SIZE],message[BUF_SIZE];
	bzero(buf,BUF_SIZE);
	bzero(message,BUF_SIZE);
	//receive message
	printf("read from client(ID=%d)\n",clientfd);
	int len=recv(clientfd,buf,BUF_SIZE,0);
	if(len==0){
		close(clientfd);
		clients_list.remove(clientfd);//server remove the client
		printf("ClientID=%d closed. Now there are %d client in the chat room\n",clientfd,(int)clients_list.size());
	}
	else{
		if(clients_list.size()==1){
			send(clientfd,CAUTION,strlen(CAUTION),0);
			return len;
		}
		sprintf(message,SERVER_MESSAGE,clientfd,buf);

		list<int>::iterator it;
		for(it=clients_list.begin();it!=clients_list.end();it++){
			if(*it!=clientfd){
				if(send(*it,message,BUF_SIZE,0)<0){
					perror("error");
					exit(-1);
				}
			}
		}
	}
	return len;
}

#endif	//UTILITY_H_INCLUDED















