#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

#include <string.h>

int main()
{
  int fdC, fdS;

  //unlink("/tmp/exercise3_fifoClient");

	//READ FIFO
	while((fdC = open("/tmp/exercise3_fifoClient", O_RDONLY))== -1){
	  if(mkfifo("/tmp/exercise3_fifoClient", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("FIFO Created\n");
	  }
	}

	int n;
	int i;
	char str[2];
	int count = 0;

	while(1){

		n = read(fdC, str, 2);
		if(n<=0){
			perror("read ");
			exit(-1);
		}
		printf("Function %s (%d bytes)\n", str, n);	
		if(strcmp(str, "f1") != 0 && strcmp(str, "f2") != 0)
		{
			printf("Invalid function name.\n");
		}
		else
		{
			void* lib_handler = dlopen("./funcs.so", RTLD_LAZY);
			if(lib_handler == NULL)
			{
				printf("Error opening library. Exiting...\n");
				exit(1);
			}

			int (*function)();	

			function = dlsym(lib_handler, str);

			if(function == NULL)
			{
				printf("Error\n");
				exit(1);
			}

			int rValue = function();

			printf("Return Value: %d\n", rValue);
		}

	}

}
