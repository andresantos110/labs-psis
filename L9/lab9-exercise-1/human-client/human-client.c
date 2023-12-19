#include <ncurses.h>
#include "../remote-char.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <ctype.h> 
#include <stdlib.h>
#include "../balls.pb-c.h"
 
#include <zmq.h>
#include "zhelpers.h"

int main()
{

    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    int rc = zmq_connect (requester, "tcp://localhost:55555");
    if (rc!=0){
        printf("error connecting REQ socket");
        exit(-1);
    }
	printf("socket connected\n");

    char ch;
    do{
        printf("what is your character(a..z)?: ");
        ch = getchar();
        ch = tolower(ch);  
    }while(!isalpha(ch));


    direction_t direction;
    int msg_type = 0;
    zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);

    // TODO 7 - create and fill a message of type client_connection_req   
    //           and send the packed message to the server
    //remote_char_t m;
    //m.ch = ch;
    //zmq_send (requester, &m, sizeof(remote_char_t), 0);
    // TODO 7

    ClientConnectionReq clientconnection = CLIENT_CONNECTION_REQ__INIT;

    clientconnection.ch = (int)ch;

    int msg_len = client_connection_req__get_packed_size(&clientconnection);
    char * msg_buf = malloc(msg_len);
    client_connection_req__pack(&clientconnection, msg_buf);

    zmq_send (requester, msg_buf, msg_len, 0);

    char * str = s_recv(requester);
    free(str);   


	initscr();			/* Start curses mode 		*/
	cbreak();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */

    int n = 0;
    

    int key;
    do
    {
    	key = getch();		
        n++;
        switch (key)
        {
        case KEY_LEFT:
            mvprintw(0,0,"%d Left arrow is pressed", n);
           direction = LEFT;
            break;
        case KEY_RIGHT:
            mvprintw(0,0,"%d Right arrow is pressed", n);
            direction = RIGHT;
            break;
        case KEY_DOWN:
            mvprintw(0,0,"%d Down arrow is pressed", n);
            direction = DOWN;
            break;
        case KEY_UP:
            mvprintw(0,0,"%d :Up arrow is pressed", n);
            direction = UP;
            break;

        default:
            key = 'x'; 
            break;
        }

         if (key != 'x'){
            int msg_type = 1;
            zmq_send(requester, &msg_type, sizeof(msg_type), ZMQ_SNDMORE);

            // TODO 10 - create and fill a message of type  movement_req  
            //           and send the packed message to the server
            //zmq_send (requester, &m, sizeof(remote_char_t), 0);
            // TODO 10

            MovementReq movementreq = MOVEMENT_REQ__INIT;

            movementreq.ch = (int)ch;
            movementreq.direction = (int) direction;

            int msg_len = movement_req__get_packed_size(&movementreq);
            char * msg_buf = malloc(msg_len);
            movement_req__pack(&movementreq, msg_buf);

            zmq_send (requester, msg_buf, msg_len, 0);


            char * str = s_recv(requester);
            free(str);   
        }
        refresh();			/* Print it on to the real screen */
    }while(key != 27);
    
    
  	endwin();			/* End curses mode		  */

	return 0;
}