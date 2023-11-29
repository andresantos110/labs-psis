#include <ncurses.h>
#include "remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdlib.h>
#include <zmq.h>
#include <string.h>

#define WINDOW_SIZE 15

int main()
{
  char type[100];

  void *context = zmq_ctx_new();

  void *subscriber = zmq_socket(context, ZMQ_SUB);

	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5555");

  zmq_connect(subscriber, "tcp://localhost:6666");


  char c;

  char token[100];

	printf("DO YOU WANT TO PAY TO WATCH? y or n\n");
	scanf("%c", &c);
	if(strcmp(&c, "y") == 0)
	{
        if(zmq_send(requester, "PAY", 3, 0) == -1) printf("Could not pay.\n");
        if(zmq_recv(requester, &token, sizeof(token), 0) == -1) printf("Could not receive token.\n");
	}
	else
	{
	    printf("Not paying.\n");
      if(zmq_send(requester, "NOT", 3, 0) == -1) printf("Could not pay.\n");
      if(zmq_recv(requester, &token, sizeof(token), 0) == -1) printf("Could not receive token.\n");
	}


  zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, token, sizeof(token));

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
  int currIndex = 0, ch = 0;

  for(int i = 0; i < 95; i++)
  {
    clients[i].pos_x = WINDOW_SIZE/2;
    clients[i].pos_y = WINDOW_SIZE/2;
  }


  while(1)
  {
    if(zmq_recv(subscriber, &type, sizeof(type), 0) == -1) printf("Error receiving type.\n");
    if(zmq_recv(subscriber, &ch, sizeof(ch), 0) == -1) printf("Error receiving char.\n");
    currIndex = ch - 32;

    wmove(my_win, clients[currIndex].pos_x, clients[currIndex].pos_y);
    waddch(my_win,' '); 

    if(zmq_recv(subscriber, &clients[currIndex], sizeof(struct client_info), 0) == -1) printf("Error receiving info.\n");
    //printf("Drawing char: %d in position %d %d.\n", currIndex, clients[currIndex].pos_x, clients[currIndex].pos_y);
  
    /* draw mark on new position */
    wmove(my_win, clients[currIndex].pos_x, clients[currIndex].pos_y);
    waddch(my_win, ch | A_BOLD);
    wrefresh(my_win);		
  }
  endwin();

  zmq_close(subscriber);
  zmq_close(requester);
  zmq_ctx_destroy(context);

}
