
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <error.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	pid_t pid;
	if (pid=fork()){
		printf("par==>retpid: %d\n",pid);
		printf("par==>curpid: %d\n",getpid());
		printf("par==>curppid: %d\n",getppid());

		printf("par==>sleep...\n");
		sleep(15);
		printf("par==>exit...\n");

	}
	else if(!pid){
		printf("son==>retpid: %d\n",pid);
		printf("son==>curpid: %d\n",getpid());
		printf("son==>curppid: %d\n",getppid());
		printf("son==>exit...\n");
	}
	return 0;
}


