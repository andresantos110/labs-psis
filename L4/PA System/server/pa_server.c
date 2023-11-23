#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include "zhelpers.h"

int main (void){

    void *context = zmq_ctx_new ();
    // Bind a ZMQ_REP socket
    void *responder = zmq_socket(context, ZMQ_REP);
    int rcRep = zmq_bind(responder, "tcp://localhost:5556");


    // Bind a ZMQ_PUB socket
    void *publisher = zmq_socket(context, ZMQ_PUB);
    int rcPub = zmq_bind(publisher, "tcp://localhost:6666");



    while (1) {

        // receive messages from the microphones
        char *dpt = s_recv(responder);
        char *s = s_recv(responder);

        printf("department %s message %s", dpt, s); 

        // publish message to speakers

        s_sendmore(publisher, dpt);
        s_send(publisher, s);
        s_send(responder, s);

        free(dpt);
        free(s);
    }
    return 0;
}
