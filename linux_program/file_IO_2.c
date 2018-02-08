
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	//read,write
//#include <error.h>
#include <sys/select.h>
#include <string.h>	//strcmp,strlen
#include <dirent.h>	//opendir

#define FILE_PATH "./test.txt"
#define MICE_DEV "/dev/input/mice"
#define BUF_MAX	100

int main(int argc, char* argv[])
{
	//int stat(const char* path, struct stat* buf)	==>ret:0 is success;i is err
	/*
	struct stat {
    dev_t       st_dev;
    ino_t       st_ino;
    mode_t      st_mode;
    nlink_t     st_nlink;
    uid_t       st_uid;
    gid_t       st_gid;
    dev_t       st_rdev;
    off_t       st_size;
    blksize_t   st_blksize;
    blkcnt_t    st_blocks;
    time_t      st_atime;
    time_t      st_mtime;
    time_t      st_ctime;
	};
	*/
	struct stat statbuf;
	char file_mode[80];
	if(argc != 2){
		printf("Usage: stat <pathname>\n");
		exit(-1);
	}
	if(stat(argv[1],&statbuf)!=0){
		perror("stat err");
		exit(-1);
	}
	if(S_ISREG(statbuf.st_mode))
		strcpy(file_mode,"-");
	else if(S_ISDIR(statbuf.st_mode))
		strcpy(file_mode,"d");
	else if(S_ISCHR(statbuf.st_mode))
		strcpy(file_mode,"c");
	else if(S_ISBLK(statbuf.st_mode))
		strcpy(file_mode,"b");
	else if(S_ISLNK(statbuf.st_mode))
		strcpy(file_mode,"l");
	else if(S_ISSOCK(statbuf.st_mode))
		strcpy(file_mode,"s");
	/////////////////////////////////////////
	if(statbuf.st_mode|S_IRWXU)
		strcat(file_mode,"|RWXU");
	else if(statbuf.st_mode|S_IRUSR)
		strcat(file_mode,"|RUSR");
	else if(statbuf.st_mode|S_IWUSR)
		strcat(file_mode,"|WUSR");
	else if(statbuf.st_mode|S_IXUSR)
		strcat(file_mode,"|XUSR");

	printf("#i-node:	%ld\n",statbuf.st_ino);
	printf("#link:		%ld\n",statbuf.st_nlink);
	printf("UID:		%d\n",statbuf.st_uid);
	printf("GID:		%d\n",statbuf.st_gid);
	printf("Size:		%ld\n",statbuf.st_size);	
	printf("Mode:		%s\n",file_mode);

	/////////////////////////////////////////
	//DIR* opendir(const char* name)	==>ret:dir stream;NULL is err
	//struct dirent* readdir(DIR* dir)	==>ret:subdir of dir;NULL is err or readend
	/*
	struct dirent {
   		ino_t   d_ino;
   		off_t   d_off;
   		unsigned short  d_reclen;
   		unsigned char   d_type;
   		char    d_name[256];
   	}
   */
   //int closedir(DIR* dir)	==>ret:0 is success;-1 is err and reason at errno
	DIR* dp;
	struct dirent* entp;
	if(argc!=2){
		printf("usage: showdir dirname\n");
		exit(0);
	}
	if((dp=opendir(argv[1]))==NULL){
		perror("opendir");
		exit(-1);
	}
	printf("<===========>\n");
	while((entp=readdir(dp))!=NULL)
		printf("%s\n",entp->d_name);
	closedir(dp);
	printf("<============>\n");

	return 0;
}


