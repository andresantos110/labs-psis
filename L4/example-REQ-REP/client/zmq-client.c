//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "ipc:///tmp/s1");

    while(1) {
        int n;
        char buffer [10];

        printf("type an integer ");
        scanf("%d", &n);
        printf ("Sending number %d...\n", n);
        if(zmq_send (requester, &n, sizeof(n), 0) == -1) printf("Erorr sending value.\n");
        if(zmq_recv (requester, &n, sizeof(n), 0) == -1) printf("Error receiving value.\n");
        printf ("Received number %d\n", n);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}
