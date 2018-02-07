
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	//read,write
//#include <error.h>

#define FILE_PATH "./test.txt"
#define BUF_MAX	100

int main(void)
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
	lseek(fd,-3,SEEK_CUR);	//when read 1 char, pos will move 1 automatically

	read(fd,buf,1);
	write(STDOUT_FILENO,buf,1);printf("\n");
	return 0;
}




