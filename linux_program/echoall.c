/*************************************************************************
    > File Name: echoall.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2018年02月11日 星期日 21时25分02秒
 ************************************************************************/

#include<stdio.h>

int main(int argc,char* argv[],char* envp[])
{
	//int execl(const* char pathname, const char* arg0, ..., (char*)0, const* const envp[])
	//==>ret:-1 is err;success never ret
	//par:pathname is whole path of new program;arg0 is first comd par(program name);...;(char*)0 is end;envp is env variable of new program
	
	int i;
	char** ptr;
	extern char** environ;
	for(i=0; i<argc; ++i)
		printf("argv[%d]:	%s\n",i,argv[i]);
	printf("===========================================\n");
	for(ptr=environ; *ptr!=0; ptr++)
		printf("%s\n",*ptr);
	return 0;
}
