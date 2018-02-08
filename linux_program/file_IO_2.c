
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	//read,write
//#include <error.h>
#include <sys/select.h>
#include <string.h>	//strcmp

#define FILE_PATH "./test.txt"
#define MICE_DEV "/dev/input/mice"
#define BUF_MAX	100

int main(int argc, char* argv[])
{

	//int open(const str* pathname, int oflag, [..., mode_t mode])	==>ret:fd;-1 is err
	//ssize_t read(int fd, void* buf, size_t count)		==>ret:read bytes;0 is atend;-1 is err
	//ssize_t write(int fd, const void* buf, size_t count)	==>ret:write bytes;-1 is err
	//off_t lseek(int filesdes, off_t offset, int whence)	==>ret:offset bytes;-1 is err
	//ssize<==>signed int	size_t<==>unsigned int	off_t<==>signed int
	int fd;
	if((fd=open(FILE_PATH,O_RDWR|O_CREAT|O_TRUNC,0666))<0){	//why 0666 and result is -rw-rw-r-- ?
		perror("open");
		//exit(-1);
	}else{
		printf("open success\n");
	}

	char buf[BUF_MAX];
	int num = 0;
	//get keyboard input
	if((num=read(STDIN_FILENO, buf, BUF_MAX))<0){
		perror("read");	//perror(),exit()?
	}else{
		//output to screen and test.txt
		write(STDOUT_FILENO, buf, num);
		if((num=write(fd,buf,num))<0){
			perror("write");
		}
	}

	read(fd,buf,1);
	write(STDOUT_FILENO,buf,1);printf("\n");
	lseek(fd,2,SEEK_SET);
	
	read(fd,buf,1);
	write(STDOUT_FILENO,buf,1);printf("\n");
	lseek(fd,-2,SEEK_END);	//last char is enter,so move to the pos before enter

	read(fd,buf,1);
	write(STDOUT_FILENO,buf,1);printf("\n");
	lseek(fd,-4,SEEK_CUR);	//when read 1 char, pos will move 1 automatically

	read(fd,buf,1);
	write(STDOUT_FILENO,buf,1);printf("\n");
	read(fd,buf,1);
	write(STDOUT_FILENO,buf,1);printf("\n");
	lseek(fd,1,SEEK_CUR);

	read(fd,buf,1);
	write(STDOUT_FILENO,buf,1);printf("\n");


	//	/dev/input/mice is devfile of mouse
	//in POSIX program:
	//0==>STDIN_FILENO(default keyborad)
	//1==>STDOUT_FILENO(default screen)
	//2==>STDERR_FILENO(default screen)
	read(0,buf,BUF_MAX);	//block untile keyboard input
	if((fd=open(MICE_DEV,O_RDONLY))<0){
		perror("open mice");
	}else{
		printf("open mice success\n");
		read(fd,buf,BUF_MAX);
	}

	//int select(int maxfd, fd_set* readset, fd_set* writeset, \
	// \fd_set* exceptset, const struct timeval* timeout)
	//==>ret:num of fd changed in readset/writeset/exceptset;-1 is err;0 is timeout
	fd_set rfds;
	struct timeval tv;
	int retval, fd1;
	char buf1[BUF_MAX];

	fd1=open(MICE_DEV,O_RDONLY);
	while(1){
		FD_ZERO(&rfds);
		FD_SET(0,&rfds);
		FD_SET(fd1,&rfds);
		tv.tv_sec=3;
		tv.tv_usec=0;

		retval=select(fd1+1,&rfds,NULL,NULL,&tv);	//why maxfd=fd+1?
		if(retval<0)	perror("select err");
		else if(retval==0)	printf("Nodata within 3 sec\n");
		else{
			if(FD_ISSET(0,&rfds)){
				printf("Data is available from keyboard now\n");
				memset(buf1,0,sizeof(buf1));
				read(0,buf1,BUF_MAX);
				printf("received buf is: %s\n",buf1);
				if(strncmp(buf1,"exit",strlen("exit"))==0){
					printf("break loop!!!!!!!!\n");
					break;
				}
			}
			if(FD_ISSET(fd1,&rfds)){
				printf("Data is available from mouse now\n");
				memset(buf1,0,sizeof(buf1));
				read(fd1,buf1,BUF_MAX);
			}
		}
	}
	
	return 0;
}


