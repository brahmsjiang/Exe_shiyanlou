/*************************************************************************
    > File Name: gdb_multi_proc.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月12日 星期一 16时56分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>	//exit
#include<unistd.h>	//fork
#include<wait.h>	//wait

int main(int argc,char* argv[],char* envp[])
{
	pid_t pid;
	int status;
	if((pid=fork())<0){
		perror("fork");
		exit(-1);
	}
	else if(pid==0){
		printf("child start,sleep...\n");
		sleep(30);
		printf("child start end\n");

		exit(0);
	}
	wait(&status);
	printf("ret parent...\n");
	exit(0);
}
