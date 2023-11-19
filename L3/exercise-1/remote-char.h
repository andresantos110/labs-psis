#include <ncurses.h>
#include <stdio.h>
typedef enum direction_t {UP, DOWN, LEFT, RIGHT} direction_t;
// TODO_1 
// declaration the struct corresponding to the exchanged messages

struct message{
  int msg_type; //type = 0 connection, type = 1 movement
  direction_t direction;
  int ch;
} message;


// TODO_2
//declaration of the FIFO location

#define fifo_location "/tmp/L3E1fifo"
