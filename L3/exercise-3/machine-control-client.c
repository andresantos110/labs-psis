#include "remote-char.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main()
{

    struct message m;

     //TODO_4
	int fd;
	while((fd = open(fifo_location, O_WRONLY))== -1){
	 if(mkfifo(fifo_location, 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("FIFO Created\n");
	  }
	}

    //TODO_5
    char inputChar;
    printf("Enter the character to control: ");
    scanf("%c", &inputChar);
    m.ch = (int)inputChar;
    m.msg_type = 0;

    // TODO_6
   write(fd, &m, sizeof(m)); 

    

    int sleep_delay;
    direction_t direction;
    int n = 0;
    while (1)
    {
        sleep_delay = random()%700000;
        usleep(sleep_delay);
        direction = random()%4;
        n++;

        m.msg_type = 1;
        m.direction = direction;

        //TODO_9
        //TODO_10
        write(fd, &m, sizeof(m)); 
    }

 
	return 0;
}
