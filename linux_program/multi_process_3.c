
#include <stdio.h>
#include <stdlib.h>	//about env
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <error.h>
#include <unistd.h>

int globle_init_val=100;
int globle_noninit_val;
extern char** environ;

int main(int argc, char* argv[], char* envp[])
{
	static int localstaticval=10;
	char* localval;
	localval = (char*)malloc(10);
	
	printf("addr of text	is:	%p\n",main);
	printf("addr of data	is:	%p, %p\n",&globle_init_val,&localstaticval);
	printf("addr of bss		is:	%p\n",&globle_noninit_val);
	printf("addr of heap	is:	%p\n",localval);
	printf("addr of stack	is: %p\n",&localval);
	free(localval);

	printf("&environ = %p, environ = %p\n",&envp,envp);
	printf("&argv = %p, argv = %p\n", &argv, argv);
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
#if 0
	for(int i=0;;++i){
		if(envp[i]){
			printf("envp[%d]:	%s\n",i,envp[i]);
		}
		else{
			break;
		}
	}
#endif

	//char* getenv(const char* name)
	//int putenv(const char* str)
	//int setenv(const char* name, const char* value, int rewrite)
	
	char** ptr;
	for(ptr=envp; *ptr!=0; ++ptr)
		printf("%s\n",*ptr);

	printf("\n\n--------My environment variable--------\n\n");
	return 0;
}


