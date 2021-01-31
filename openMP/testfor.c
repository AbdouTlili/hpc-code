#include <omp.h>
#include <stdio.h>


int main(char argc, char* argv[]){

    int i,j,sum; 
    sum=0;
    double s,f;
    omp_set_num_threads(2);
    s = omp_get_wtime();
    #pragma omp parallel private(j)
    {
        i = 0; j = 0;
        #pragma omp for schedule(static) nowait
        for (int i = 0 ; i < 1000000 ; i++){
        j++;
        }
        #pragma omp critical
        sum +=j;
    }

    f = omp_get_wtime();
    printf("\n finished in %lf the result is %d",f-s,sum);

    return 0;
}