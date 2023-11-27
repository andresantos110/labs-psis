#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <ctype.h> 
#include <stdlib.h>
#include <zmq.h>
 

int main()
{

    struct message m;
   
    //TODO_4
    // create and open the FIFO for writing
    /*
    int fd;
	while((fd = open(fifo_location, O_WRONLY))== -1){
	 if(mkfifo(fifo_location, 0666)!=0){
			printf("problem creating the fifo\n");
			exit(-1);
	  }else{
		  printf("FIFO Created\n");
	  }
	}
	*/

	void *context = zmq_ctx_new();
	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5555");



    //TODO_5
    // read the character from the user
    char inputChar;
    printf("Enter the character to control: ");
    scanf("%c", &inputChar);
    m.ch = (int)inputChar;
    m.msg_type = 0;

    // TODO_6
    // send connection message
    //write(fd, &m, sizeof(m));
    if(zmq_send(requester, &m, sizeof(m), 0) == -1) printf("Error sending message.\n");
    if(zmq_recv(requester, &m, sizeof(m), 0) == -1) printf("Error receiving reply.\n");
  



	initscr();			/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    
    int ch;

    m.msg_type = 1;
    int n = 0;
    do
    {
    	ch = getch();		
        n++;
        switch (ch)
        {
            case KEY_LEFT:
                mvprintw(0,0,"%d Left arrow is pressed", n);
                m.direction = LEFT;
                break;
            case KEY_RIGHT:
                mvprintw(0,0,"%d Right arrow is pressed", n);
                m.direction = RIGHT;
                break;
            case KEY_DOWN:
                mvprintw(0,0,"%d Down arrow is pressed", n);
                m.direction = DOWN;
                break;
            case KEY_UP:
                mvprintw(0,0,"%d :Up arrow is pressed", n);
                m.direction = UP;
                break;
            default:
                ch = 'x';
                    break;
        }
        refresh();			/* Print it on to the real screen */
        //TODO_9
        // prepare the movement message
        // done above
        

        //TODO_10
        //send the movement message
        if(zmq_send(requester, &m, sizeof(m), 0) == -1) printf("Error sending message.\n");
        if(zmq_recv(requester, &m, sizeof(m), 0) == -1) printf("Error receiving reply.\n");

        
    }while(ch != 27);
    
    
  	endwin();			/* End curses mode		  */

  	zmq_close(requester);
  	zmq_ctx_destroy(context);

	return 0;
}
