/*************************************************************************
    > File Name: exithandler.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月12日 星期一 16时11分00秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>	//write,STDOUT_FILENO
#include<string.h>
#include<stdlib.h>	//exit

static void my_exit0(int, void*);
static void my_exit1(void);
static void my_exit2(void);
char str[9]="for test";

int main(int argc, char* argv[], char* envp[])
{
	
	//int atexit(void(* func)(void))
	//int on_exit(void(* func)(int,void*))	//par int is exitval,par void* is argument
	if(atexit(my_exit2)!=0){
		perror("cant register my_exit2");
		exit(-1);
	}
	if(atexit(my_exit1)!=0){
		perror("cant register my_exit1");
		exit(-1);
	}
	if(on_exit(my_exit0,(void*)str)!=0){
		perror("cant register my_exit0");
		exit(-1);
	}
	printf("main is start\n");
	printf("hello");
	write(STDOUT_FILENO,"sleep 2s...\n",strlen("sleep 2s...\n"));
	//printf("\n");	//flush
	//or I/O buf is full
	//_exit(1234);	//ret to core directory/syscall, no flush,no call exithandler
	exit(1234);	//c lib func, flush and call exithandler
}

static void my_exit0(int status, void* arg){
	printf("zero exit handler\n");
	printf("exit %d\n",status);
	printf("arg=%s\n",(char*)arg);
}

static void my_exit1(void){
	printf("first exit handler\n");
}

static void my_exit2(void){
	printf("second exit handler\n");
}













