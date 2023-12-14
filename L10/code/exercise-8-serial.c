#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 

int * rand_num_array;

#define LIMIT 100

void * n_mult(void * arg){
    long int c = 0;
    int n = *(int *) arg;
    for(int i = 0 ; i <LIMIT; i++){
        if(rand_num_array[i]%n == 0)
        c ++;
    }
    return (void*)c;
}
int main(){

    int n_threads;
    void *thread_ret;

    rand_num_array = calloc(LIMIT, sizeof(int));

    for(int i = 0 ; i <LIMIT; i++){
        rand_num_array[i] = random();
    }

    n_threads = 5;
    pthread_t thread_ids[n_threads];
    int *numMult;

    int i = 0;
    while( i < n_threads) {
        numMult = malloc(sizeof(int));
        switch (i){
            case(0):
                *numMult = 2;
                break;
            case(1):
                *numMult = 3;
                break;
            case(2):
                *numMult = 5;
                break;
            case(3):
                *numMult = 7;
                break;
            case(4):
                *numMult = 11;
                break;
        }

        pthread_create(&thread_ids[i], NULL,n_mult, numMult);
        i++;
    };
    i = 0;
    while ( i < n_threads ) {
        pthread_join(thread_ids[i], &thread_ret);
        printf("Value returned by thread %d = %d\n", i, (long int) thread_ret);
        i++;
    }
    /*
    int n_2 = n_mult(2);
    int n_3 = n_mult(3);
    int n_5 = n_mult(5);
    int n_7 = n_mult(7);
    int n_11 = n_mult(11);
    printf("%d %d %d %d %d \n", n_2, n_3, n_5, n_7, n_11);
    */
    exit(0);

}