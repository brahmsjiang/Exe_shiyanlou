
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <error.h>
#include <string.h>	//strcmp,strlen
#include <dirent.h>	//opendir
#include <unistd.h>

int main(int argc, char* argv[])
{
#if 0
	pid_t pid;
	if((pid=vfork())<0){
		perror("vfork");
	}
	else if(pid==0){
		printf("child start,pid: %d\n",getpid());
		printf("child===>sleep...\n");
		sleep(5);
		printf("child===>exit\n");
		exit(-1);
	}
	else if(pid>0){
		printf("parent start,pid: %d\n",getpid());
	}
#endif
//#if 0

	pid_t pid;
	if(!(pid=vfork())){
		printf("curr getpid: %d,pid: %d,sleep...\n",getpid(),pid);
		sleep(100);
	}
//#endif

	return 0;
}


