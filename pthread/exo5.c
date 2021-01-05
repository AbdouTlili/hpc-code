#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

struct threadargs{
    int i;
    pthread_mutex_t *mutex;
    int *sum;
}

void* helloWorld(void *arg){
    long tid ;
    printf("Hello it's me, thread_self : %p | pid : %d  | order %d\n",(void*)pthread_self(),getpid(),*(int*)arg);
    for(int i = 0; i<100000;i++){
        pthread_mutex_lock(&mutex);
        sum+=*(int*)arg;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main (char argc, char *argv[]){
    //printf("nombre de threads%s\n",argv[1]); // getting argv dynamically
    int NUM_THREADS = atoi(argv[1])  ;
    int sum ; 
    pthread_mutex_t mutex ; 

    int *id = malloc(NUM_THREADS * sizeof(int));
    pthread_t *threads;
    threads = malloc(NUM_THREADS * sizeof(pthread_t));
    int t,rc;
    printf("%s\n",argv[1]); // getting argv dynamically
    pthread_mutex_init(&mutex,NULL);

    for(t=0;t<NUM_THREADS;t++){
        printf("in main : creating thread %ld \n",t);
        id[t]=t;
        rc = pthread_create(&threads[t],NULL,helloWorld,(void*)&id[t]);
        if(rc){
            printf("ERROR ; return code from pthread_create() is %d\n",rc);
        }
    }
    printf("debut d' attente :\n");

    for(t=0;t<NUM_THREADS;t++){
        pthread_join(threads[t],NULL);
    }
    printf("Fin d attente");
    printf("la somme : %d\n",sum);
    return 0 ;

}

//the arg structure is created but i need to : link both the threads and main in pthread_create 
// :) 