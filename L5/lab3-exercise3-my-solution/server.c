
#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <zmq.h>
#include <string.h>
#include <time.h>

#define WINDOW_SIZE 15

direction_t random_direction(){
  return  random()%4;

}
void new_position(int* x, int *y, direction_t direction){
    switch (direction)
    {
    case UP:
        (*x) --;
        if(*x ==0)
            *x = 2;
        break;
    case DOWN:
        (*x) ++;
        if(*x ==WINDOW_SIZE-1)
            *x = WINDOW_SIZE-3;
        break;
    case LEFT:
        (*y) --;
        if(*y ==0)
            *y = 2;
        break;
    case RIGHT:
        (*y) ++;
        if(*y ==WINDOW_SIZE-1)
            *y = WINDOW_SIZE-3;
        break;
    default:
        break;
    }
}

int main()
{	

    srand(time(NULL));

	char token[100];

	int tokenInt = rand()%1024;

    void *context = zmq_ctx_new();

    void *responder = zmq_socket(context, ZMQ_REP);

    void *publisher = zmq_socket(context, ZMQ_PUB);

    int rc = zmq_bind(responder, "tcp://localhost:5555");

    int rcPub = zmq_bind(publisher, "tcp://localhost:6666");  

    if(zmq_recv(responder, &token, sizeof(token), 0) == -1) printf("Error receiving payment.\n");
    if(strcmp(token, "PAY") == 0)
    {
        //strcpy(token, "PAID");
        sprintf(token, "%d", tokenInt);
        if(zmq_send(responder,&token, sizeof(token), 0) == -1) printf("Error responding.\n");
    }
    else
    {
        strcpy(token, "NOTPAID");
        if(zmq_send(responder,&token, sizeof(token), 0) == -1) printf("Error responding.\n");
        //strcpy(token, "PAID");
        sprintf(token, "%d", tokenInt);
 
    }

    // ncurses initialization
	initscr();		    	
	cbreak();				
    keypad(stdscr, TRUE);   
	noecho();			    

    /* creates a window and draws a border */
    WINDOW * my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
    box(my_win, 0 , 0);	
	wrefresh(my_win);


    direction_t  direction;
    int n;
    struct message m;
    /* There are 127 elements in the ASCII table. The first printable one is index 32: therefore, 127-32 allows us
     * to store all the printable values and use the received char minus the offset (32) as the index. This
     * removes the need to store the char. */
    struct client_info clients[95];
    int currIndex = 0;

    while (1)
    {

        if(zmq_recv(responder, &m, sizeof(m), 0) == -1) printf("Error receiving message.\n");
        if(zmq_send(responder,&m, sizeof(m), 0) == -1) printf("Error responding.\n");

        if(m.msg_type == 0)
        {
            currIndex = m.ch - 32;
            clients[currIndex].pos_x = WINDOW_SIZE/2; 
            clients[currIndex].pos_y = WINDOW_SIZE/2;
        }

        if(m.msg_type = 1)
        {
            currIndex = m.ch - 32;
            wmove(my_win, clients[currIndex].pos_x, clients[currIndex].pos_y);
            waddch(my_win,' '); 
            new_position(&clients[currIndex].pos_x, &clients[currIndex].pos_y, m.direction);
        }
        if(zmq_send(publisher, token, sizeof(token), ZMQ_SNDMORE) == -1) printf("Error sending type.\n");

        if(zmq_send(publisher, &m.ch, sizeof(m.ch), ZMQ_SNDMORE) == -1) printf("Error sending char.\n");

        if(zmq_send(publisher, &clients[currIndex], sizeof(struct client_info), 0) == -1) printf("Error sending client info.\n");

        wmove(my_win, clients[currIndex].pos_x, clients[currIndex].pos_y);
        waddch(my_win,m.ch| A_BOLD);
        wrefresh(my_win);			
    }
  	endwin();			/* End curses mode		  */

  	zmq_close(responder);
  	zmq_close(publisher);
  	zmq_ctx_destroy(context);

	return 0;
}
