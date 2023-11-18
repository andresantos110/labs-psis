#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
int main()
{
  int fdC, fdS;

  //unlink("/tmp/exercise3_fifoClient");

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

		printf("write the function to use:");
		fgets(str, 100, stdin);
		write(fdC, str, 2);

		n = read(fdS, &i, 4);
		printf("Return Value: %d\n", i);

	}



}
