#include <pthread.h>
#include <stdio.h>


struct data_struct {
    int* tab1;
    int* tab2;
    int* res;
    int iterations;
} ; 


void * sum_tab(void* args){
    //casting args from void type object 
    struct data_struct* arg= (struct data_struct*) args;
    for (int i=0;i < arg->iterations;i++){
        arg->res[i]=arg->tab1[i]+arg->tab2[i];
    }
}



int main (char argc, char* argv[]){
    //number of threads 
    int NUM_THREADS = 3;
    
    //init tables 
    int tab1[9] = {1,2,3,4,5,6,7,8,9};
    int tab2[9] = {1,2,3,4,5,6,7,8,9};
    int res[9] = {0};
    
    // init the data_struct (arg for pthread_create )
    struct data_struct args[3];
    args[0].tab1 = &tab1[0]; args[1].tab1 = &tab1[3]; args[2].tab1 = &tab1[6]; 
    args[0].tab2 = &tab2[0]; args[1].tab2 =&tab2[3]; args[2].tab2 = &tab2[6]; 
    args[0].res = &res[0]; args[1].res = &res[3]; args[2].res = &res[6]; 
    args[0].iterations = 3; args[1].iterations = 3; args[2].iterations = 3; 
    args[1].tab1 = tab1; 


    // init of Pthread structures :
    pthread_t threads[NUM_THREADS];

    int rc = 0; //exit code value 

    for(int i=0;i<NUM_THREADS;i++){
        printf("creating Thread : %d",i);
        rc = pthread_create(&threads[i],NULL,sum_tab,(void *)&args[i]);
        if (rc){
            printf("ERROR; exit code from pthread_create() is : %d ",rc);
        }
    }


    // master waiting for threads to finish 
    for(int i=0; i < NUM_THREADS; i++){
        pthread_join(threads[i],NULL);
    }

    // all threads are finished at this point 
    //master can print the results 
    printf("the summ table : \n");
    for(int i = 0; i < 9;i ++){
        printf("%d-",res[i]);
    }

    return res;

}