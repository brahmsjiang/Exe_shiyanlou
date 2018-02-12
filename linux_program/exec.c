/*************************************************************************
    > File Name: exec.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月11日 星期日 21时54分02秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>	//fork
#include<stdlib.h>	//exit
#include<wait.h>

int main(int argc, char* argv[], char* envp[])
{
	pid_t pid;
	int status;
	if((pid=fork())<0){
		perror("fork");
		exit(-1);
	}
	else if(pid==0){
		printf("child1......\n");
		printf("execl......\n");
		execl("./echoall","echoall","fuck","shit",(char*)0);	//execl dont need envp par
	}
	wait(&status);
	printf("child1 end,now is parent......\n");
	
	
	if((pid=fork())<0){
		perror("fork");
		exit(-1);
	}
	else if(pid==0){
		printf("child2......\n");
		
		//execle("./echoall","echoall",argv[1],argv[2],(char*)0);	//execle without envp, echoall prog wont have environment
		printf("execle......\n");
		execle("./echoall","echoall",argv[1],argv[2],(char*)0,envp);//execle must with envp par
		//execv("./echoall",argv);	//wont exec to here, becaue elecle will not return
		
	}
	wait(&status);
	printf("child2 end,now is parent......\n");

	if((pid=fork())<0){
		perror("fork");
		exit(-1);
	}
	else if(pid==0){
		printf("child3......\n");
		printf("execv......\n");
		execv("./echoall",argv);
	}
	wait(&status);
	printf("child3 end,now is parent......\n");
	exit(0);
}
