#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
int main()
{
  int fd;

  unlink("/tmp/exercise_3fifo");

	char str[100];
	int n;
	while((fd = open("/tmp/exercise_3fifo", O_WRONLY))== -1){
	 if(mkfifo("/tmp/exercise_3fifo", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
	printf("fifo just opened for writing\n");

	while(1){

		printf("write the function to use:");
		fgets(str, 100, stdin);
		write(fd, str, 100);

	}



}
