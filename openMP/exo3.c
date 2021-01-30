#include<stdio.h>
#include<omp.h>
int main (){
    float debut, fin,temps;
    static long nb_pas = 100000;
    double pas;
    int i; double x, pi, som = 0.0;
    pas = 1.0/(double) nb_pas;

    printf("\n-----execution seq  ------\n");
    debut= omp_get_wtime();

    for (i=1; i<= nb_pas; i++){
        x = (i-0.5)*pas;
        som = som + 4.0/(1.0+x*x);
    }
    pi = pas * som;
    printf("PI=%f\n",pi);
    som = 0;
    fin= omp_get_wtime(); temps=fin-debut;
    printf ("\nCalcul parallel %f secondes\n", temps);
    printf("\n-----fin execution seq  ------\n\n");





    printf("\n-----execution PARALLEL  ------\n");
    debut= omp_get_wtime();
    #pragma omp parallel for schedule(static,16666) reduction(+:som)
    for (i=1; i<= nb_pas; i++){
        x = (i-0.5)*pas;
        som += 4.0/(1.0+x*x);
    }
    pi = pas * som;
    printf("PI=%f\n",pi);

    fin= omp_get_wtime(); temps=fin-debut;
    printf ("\nCalcul parallel %f secondes\n", temps);
    printf("\n-----fin execution parallel  ------\n\n");

    return 0;
}