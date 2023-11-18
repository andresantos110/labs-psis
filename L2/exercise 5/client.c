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

	struct message_type message;

	char str[100];
	int n, i;
	while((fdC = open("/tmp/exercise3_fifoClient", O_WRONLY))== -1){
		if(mkfifo("/tmp/exercise3_fifoClient", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
		}else{
			printf("FIFO Created\n");
		}
	}
	printf("FIFO Opened for Writing\n");

	while((fdS = open("/tmp/exercise3_fifoServer", O_RDONLY))== -1){
		if(mkfifo("/tmp/exercise3_fifoServer", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
		}else{
			printf("FIFO Created\n");
		}
	}	



	while(1){

		printf("Insert function type: (0 or 1 - Use or don't use arguments)\n");
		fgets(str, 100, stdin);
		sscanf(str, "%d", &message.funct_type);
		printf("Insert function name:\n");
		fgets(message.f_name, 100, stdin);
		if(message.funct_type == 1)
		{
			printf("Insert function argument (int):\n");
			fgets(str, 100, stdin);
			sscanf(str, "%d", &message.arg);
		}
		else message.arg = 0;

		write(fdC, &message, sizeof(struct message_type));

		n = read(fdS, &i, 4);
		printf("Return Value: %d\n", i);

	}



}
