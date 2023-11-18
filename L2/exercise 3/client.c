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
	int n;
	while((fdC = open("/tmp/exercise3_fifoClient", O_WRONLY))== -1){
	 if(mkfifo("/tmp/exercise3_fifoClient", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("FIFO Created\n");
	  }
	}
	printf("FIFO Opened for Writing\n");


	while(1){

		printf("write the function to use:");
		fgets(str, 100, stdin);
		write(fdC, str, 2);

	}



}
