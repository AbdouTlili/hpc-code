#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



void* helloWorld(void *arg){
    long tid ;

    printf("Hello it's me, thread_self : %p | pid : %d \n",(void*)pthread_self(),getpid());
    
    return NULL;
}

int main (char argc, char *argv[]){
    printf("nombre de threads%s\n",argv[1]); // getting argv dynamically
    int NUM_THREADS = atoi(argv[1])  ;
    pthread_t *threads;
    threads = malloc(NUM_THREADS * sizeof(pthread_t));
    int t,rc;
    printf("%s\n",argv[1]); // getting argv dynamically

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