#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <zmq.h>

#define WINDOW_SIZE 15

int main()
{
  void *context = zmq_ctx_new();

  void *subscriber = zmq_socket(context, ZMQ_SUB);

  zmq_connect(subscriber, "tcp://localhost:6666");

  //ncurses initialization
 	initscr();		    	
 	cbreak();				
  keypad(stdscr, TRUE);   
	noecho();			    


  /* creates a window and draws a border */
  WINDOW * my_win = newwin(WINDOW_SIZE, WINDOW_SIZE, 0, 0);
  box(my_win, 0 , 0);	
	wrefresh(my_win);


  
  int n;
  /* There are 127 elements in the ASCII table. The first printable one is index 32: therefore, 127-32 allows us
   * to store all the printable values and use the received char minus the offset (32) as the index. This
   * removes the need to store the char. */
  struct client_info clients[95];
  int currIndex = 0; 

  while(1)
  {
    if(zmq_recv(subscriber, &currIndex, sizeof(currIndex), 0) == -1) printf("Error receiving char.\n");
    if(zmq_send(subscriber, &currIndex, sizeof(currIndex), 0) == -1) printf("Error replying.\n");
    if(zmq_recv(subscriber, &clients[currIndex], sizeof(struct client_info), 0) == -1) printf("Error receiving info.\n");
    if(zmq_send(subscriber, &clients[currIndex], sizeof(struct client_info), 0) == -1) printf("Error replying.\n");

    /* draw mark on new position */
    wmove(my_win, clients[currIndex].pos_x, clients[currIndex].pos_y);
    waddch(my_win,currIndex | A_BOLD);
    wrefresh(my_win);		
  }
  endwin();

  zmq_close(subscriber);
  zmq_ctx_destroy(context);

}
