#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_THREADS 5

void* printHello(void *threadid){
    long tid ;
    tid = (long) threadid;
    int s =0;
    if(tid==(long)1){sleep(5);}
    printf("Hello it's me, thread %ld ! \n",tid);
    pthread_exit(NULL);
}

int main (char argc, char *argv[]){
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0;t<NUM_THREADS;t++){
        printf("in main : creating thread %ld \n",t);
        rc = pthread_create(&threads[t],NULL,printHello,(void*)t);
        if(rc){
            printf("ERROR ; return code from pthread_create() is %d\n",rc);
        }

    }
}