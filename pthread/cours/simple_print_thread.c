#include <pthread.h>
#include <stdio.h>

void *hello(void *args){
    int* id = (int*) args;
    printf("thread %d says hello \n",*id);
    pthread_exit(NULL);
}

int main(char argc, char* argv[]){
    pthread_t thread[3];
    int id[3] = {0,1,2};
    int i;

    for(i=0;i<3;i++){
        printf("thread %d created\n",i);
        pthread_create(&thread[i],NULL,hello,(void*)&id[i]);
    }
    pthread_exit(NULL);
}

// whats wrong with the out put.. it should be 3 creates then 3 prints 