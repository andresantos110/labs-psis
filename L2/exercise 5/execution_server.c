#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

#include <string.h>
#include "funcs.h"

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
	struct message_type message;
	int count = 0;
	int rValue;
	char fname[2];
	memset(fname, '\0', sizeof(fname));

	while(1){

		n = read(fdC, &message, sizeof(struct message_type));
		if(n<=0){
			perror("read ");
			exit(-1);
		}


		strncpy(fname, message.f_name, 2);

		printf("Function type: %d\n", message.funct_type);
		printf("Function %s (%d bytes)\n", fname, sizeof(fname));	
		printf("Function argument: %d\n", message.arg);

		if(strcmp(fname, "f1") != 0 && strcmp(fname, "f2") != 0 && strcmp(fname, "f3") != 0)
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

			int (*function)(int);

			function = dlsym(lib_handler, fname);

			if(function == NULL)
			{
				printf("Error\n");
				exit(1);
			}

			rValue = function(message.arg);

			printf("Return: %d\n", rValue);

			write(fdS, &rValue, sizeof(rValue));

		}

	}

}
