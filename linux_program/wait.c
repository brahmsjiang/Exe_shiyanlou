/*************************************************************************
    > File Name: wait.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月11日 星期日 20时04分07秒
 ************************************************************************/

#include<stdio.h>	//perror
#include<unistd.h>	//fork,sleep
#include<stdlib.h>	//exit.abort
#include<wait.h>	//wait

#define sys_err(info,errno)\
{						\
	perror(info);		\
	exit(errno);			\
}

void pr_exit(int status);

int main(int argc, char* argv[], char* envp[])
{
	//pid_t wait(int* status)	ret:childID;-1 is err	par:proc end status
	//let parent block util child end,if child end or err,will ret directory
	pid_t pid;
	int status;
	if((pid=fork())<0)
	{
	sys_err("fork",-1);
	}
	//sys_err("fork",-1)	//or,don't forget it is a macro
	else if(pid==0){
		printf("in child...\n");
		sleep(1);
		exit(101);
	}
	if(wait(&status)<0)	sys_err("wait",-2);
	printf("in parent...\n");
	pr_exit(status);
	////////////////////////////////////////////////////////////
	if((pid=fork())<0)	sys_err("fork",-1)
	else if(pid==0)	abort();	//SIGABRT
	if(wait(&status)<0)	sys_err("wait",-2);
	pr_exit(status);	
	///////////////////////////////////////////////////////////
	if((pid=fork())<0)	sys_err("fork",-1)
	else if(pid==0)	status /= 0;	//SIGFPE	
	if(wait(&status)!=pid)	sys_err("wait",-2);
	pr_exit(status);

	exit(0);
}


void pr_exit(int status){
	if(WIFEXITED(status))
		printf("normally termination,high-order 8 bit of exit status = %d\n",WEXITSTATUS(status));	//high 8-bit normal exitcode
	else if(WIFSIGNALED(status))
		printf("abnormally termination,signal number = %d\n",WTERMSIG(status));	//low 8-bit 
}







