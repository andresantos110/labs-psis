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

	//READ FIFO
	while((fdC = open("/tmp/exercise3_fifoClient", O_RDONLY))== -1){
	  if(mkfifo("/tmp/exercise3_fifoClient", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("FIFO Created\n");
	  }
	}

	//WRITE FIFO
	while((fdS = open("/tmp/exercise3_fifoServer", O_WRONLY))== -1){
	 if(mkfifo("/tmp/exercise3_fifoServer", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("FIFO Created\n");
	  }
	}
	printf("FIFO Opened for Writing\n");

	int n;
	int i;
	char str[2];
	int count = 0;
	int rValue;

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
			rValue = 0;
			write(fdS, &rValue, sizeof(rValue));
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

			rValue = function();
			printf("Return: %d\n", rValue);

			write(fdS, &rValue, sizeof(rValue));

		}

	}

}
