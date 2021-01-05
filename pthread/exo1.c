#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define NUM_THREADS 4

void* helloWorld(void *arg){
    long tid ;

    printf("Hello it's me, thread %p pid : %d \n",(void*)pthread_self(),getpid());
    return NULL;
}

int main (char argc, char *argv[]){
    pthread_t threads[NUM_THREADS];
    int t,rc;
 

    for(t=0;t<NUM_THREADS;t++){
        printf("in main : creating thread %ld \n",t);
        rc = pthread_create(&threads[t],NULL,helloWorld,NULL);
        if(rc){
            printf("ERROR ; return code from pthread_create() is %d\n",rc);
        }
    }
    printf("debut d' attente :\n");

    for(t=0;t<NUM_THREADS;t++){
        pthread_join(threads[t],NULL);
    }
    printf("Fin d attente");
    return 0 ;

}