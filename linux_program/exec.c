/*************************************************************************
    > File Name: exec.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月11日 星期日 21时54分02秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>	//fork
#include<stdlib.h>	//exit

int main(int argc, char* argv[], char* envp[])
{
	pid_t pid;
	if((pid=fork())<0){
		perror("fork");
		exit(-1);
	}
	else if(pid==0){
		printf("child==>\n");
		execle("./echoall","echoall","fuck",(char*)0,envp);
	}
	printf("parent==>\n");


	exit(0);
}
