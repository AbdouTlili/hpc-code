#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void carre(float tab[],int length){
    float total=0;
    #pragma omp for schedule(static) reduction(+:total)
    for(int i=0; i <length;i++){
        tab[i] = tab[i]*tab[i];
        total += tab[i];
    }
    
}

int main(char argc, char * argv[]){

    //declarations 
    omp_set_num_threads(6);

    int N ;
    float debut,fin,temps;
    
    // casting the table length
    N = atoi(argv[1]);

    float tab[N];
    
    debut= omp_get_wtime();

    #pragma omp parallel private(total)
    //printf("le num de threads creer : %d\n",omp_get_num_threads());
    #pragma omp for schedule(static)
    for(int i = 0; i <N;i++){
        tab[i]=(rand() % 10000) + 0.2547896;
    }
    carre(tab,N);
    fin= omp_get_wtime(); temps=fin-debut;
    printf ("\nCalcul parallel %f secondes\n", temps);

    /*
    for(int i = 0; i <N;i++){
        printf("%d-",tab[i]);
    }
    */



    /*
    printf("\n");
    for(int i = 0; i <N;i++){
        printf("%d-",tab[i]);
    }
    */


    return 0;
}

