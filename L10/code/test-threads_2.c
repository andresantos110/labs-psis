#include <stdio.h>
#include <pthread.h>  
#include <unistd.h> 
#include <stdlib.h>

void * thread_function(void * arg){
    int n = 0;
    int sleeptime = *(int *) arg;
    long int r = random()%100;
    printf("Start Thread %lu with sleeptime %d\n", r, sleeptime);
    while(n <10){
        sleep(sleeptime);
        n++;
        printf("inside Thread %lu %d\n", r, n);
    }
    printf("End Thread %lu\n", r);
    return (void *)r;
}

int main(){
    char line[100];
    int n_threads;
    void *thread_ret;

    int *wait;

    printf("How many threads: ");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &n_threads);
    pthread_t thread_ids[n_threads];

    int i = 0;
    while( i < n_threads) {
        wait = malloc(sizeof(int));
        *wait = rand()%4;
        pthread_create(&thread_ids[i], NULL,thread_function, wait);
        i++;
    };
    i = 0;
    while ( i < n_threads ) {
        pthread_join(thread_ids[i], &thread_ret);
        printf("Value returned by thread %d = %d\n", i, (long int) thread_ret);
        i++;
    }
    printf("Carregue em enter para terminar\n");
    fgets(line, 100, stdin);
    exit(0);
}