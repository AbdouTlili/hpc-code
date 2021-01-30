#include <stdio.h>
#include <omp.h>



int main (){


    #pragma omp parallel
    {
        printf("thread %d started ",omp_get_thread_num());
        #pragma omp for 
        for(int i = 0; i <50;i++){
            if (i == 49) printf("bip\n");
        }
        printf("thread %d finished ",omp_get_thread_num());

    }

    return 0 ;
}