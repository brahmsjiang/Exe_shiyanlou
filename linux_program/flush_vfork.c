
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define err_sys(info)	\
{						\
	printf("%s\n",info);\
	exit(0);			\
}

int glob=6;	//external variable in initialized data
char buf[]="a write to stdout\n";

int main(int argc, char* argv[], char* envp[])
{
	int var;//automatic variable on the stack
	pid_t pid;
	var = 88;
	if(write(STDOUT_FILENO,buf,sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error");
	
	printf("before fork...\n");	//we don't flush stdout
	if((pid=vfork())<0){	//or fork, the result of glob,var will change
		err_sys("fork error");
	}
	else if(pid==0){	//child
		printf("child==>");
		glob++;
		var++;
	}
	else{
		printf("parent==>");
		sleep(2);	//parent
	}
	printf("pid=%d, ppid=%d, glob=%d, var=%d\n",getpid(),getppid(),glob,var);
	exit(0);
}


