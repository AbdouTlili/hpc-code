#include <omp.h>
#include <stdio.h>



int main(char argc, char * argv[]){
    int id =0;
    //omp_set_num_threads(12);
    #pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        printf("\nmy id is : %d",id);

        #pragma omp single 
        {
            printf("\nSalam world");
        }
    }
    return 0;
}