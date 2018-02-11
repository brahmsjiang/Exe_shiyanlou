
#include <stdio.h>	//perror
#include <fcntl.h>	//open,O_RDONLY
#include <unistd.h>	//fork,sleep
#include <stdlib.h>	//exit
//#include <sys/types.h>	//
#include <string.h>	//strlen

int main(int argc, char* argv[], char* envp[])
{
	int fd,pid,status;
	char buf[10];

	if((pid=fork())<0){
		perror("fork");exit(-1);
	}
	else if(pid==0){
		write(STDOUT_FILENO,"child==>",strlen("child==>"));
		if((fd=open("./filetest.txt",O_RDONLY))<0){
			perror("child open");
			exit(-1);
		}
		read(fd,buf,2);
		write(STDOUT_FILENO,buf,2);
		write(STDOUT_FILENO,"\n",1);
	}else{
		sleep(2);
		write(STDOUT_FILENO,"parent==>",strlen("parent==>"));
		if((fd=open("./filetest.txt",O_RDONLY))<0){
			perror("parent open");
			exit(-1);
		}
		lseek(fd,1,SEEK_CUR);
		read(fd,buf,2);
		write(STDOUT_FILENO,buf,2);
		write(STDOUT_FILENO,"\n",1);
	}


#if 0
	if((fd=open("./test.txt",O_RDONLY))<0){
		perror("open");exit(-1);
	}
	if((pid=fork(i))<0){
		perror("fork");exit(-1);
	}else if(pid==0){
		read(fd,buf,2);
		write(STDOUT_FILENO,buf,2);
		write(STDOUT_FILENO,"\n",1);
		printf("=====================\n");
	}else{
		sleep(2);
		lseek(fd,1,SEEK_CUR);
		read(fd,buf,3);
		write(STDOUT_FILENO,"parent==>",strlen("parent==>"));
		write(STDOUT_FILENO,buf,3);
		write(STDOUT_FILENO,"\n",1);
	}
#endif
	return 0;
}






