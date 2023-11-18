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

  unlink("/tmp/exercise3_fifo");

	while((fd = open("/tmp/exercise3_fifo", O_RDONLY))== -1){
	  if(mkfifo("/tmp/exercise3_fifo", 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("fifo created\n");
	  }
	}
	printf("fifo just opened\n");
	int n = 0;
	int i;
	char str[100];
	int count = 0;

	while(n<=0){

		n = read(fd, str, 100);
		if(n<=0){
			perror("read ");
			exit(-1);
		}
		printf("Str %s (%d bytes)\n", str, n);	

	}

	void* lib_handler = dlopen("funcs.so", RTLD_LAZY);

	int (*function)();	

	function = dlsym(lib_handler, str);

	if(function == NULL)
	{
		printf("Error\n");
		exit(1);
	}

	int rValue = function();

	printf("Return Value: &d\n", rValue);

	return 0;

}
