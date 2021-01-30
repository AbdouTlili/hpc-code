#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <omp.h>
int main() {
    const int DIM = 1000;
    int i,j,k;
    double debut, fin, temps;
    double **a, **b, **cresu, **ctest;
    a= (double**) malloc(DIM*sizeof(double*));
    b= (double**) malloc(DIM*sizeof(double*));
    cresu= (double**) malloc(DIM*sizeof(double*));
    ctest= (double**) malloc(DIM*sizeof(double*));

    // initialisations etc.
    for (i=0; i<DIM; i++) {
        a[i]=(double*) malloc(DIM*sizeof(double));
        b[i]=(double*) malloc(DIM*sizeof(double));
        cresu[i]=(double*) malloc(DIM*sizeof(double));
        ctest[i]=(double*) malloc(DIM*sizeof(double));
        for (j = 0; j < DIM; j++) {
            a[i][j] = (double)(i-j);
            b[i][j] = (double)(i+j);
            cresu[i][j] = 0.0; ctest[i][j] = 0.0;
        }
    }
    // Multiplication C = A x B (séquentielle)
    printf("Multiplication séquentielle:\n");
    debut= omp_get_wtime();
    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            for (k = 0; k < DIM; k++)
                ctest[i][j] += a[i][k] * b[k][j];


    fin= omp_get_wtime(); temps=fin-debut;
    printf ("Calcul séquentiel %f secondes\n", temps);
    printf("Multiplication parallelle:\n");
    for (int t=2;t <=14;t+=2){
        printf("\n-----execution parallel avece %d threads ------\n",t);
        debut= omp_get_wtime();
        #pragma omp parallel for schedule(static,1000) num_threads(t) collapse(3)
        for (i = 0; i < DIM; i++)
            for (j = 0; j < DIM; j++)
                for (k = 0; k < DIM; k++)
                    ctest[i][j] += a[i][k] * b[k][j];
    
        fin= omp_get_wtime(); temps=fin-debut;
        printf ("\nCalcul parallel %f secondes\n", temps);
        printf("\n-----fin execution parallel avece %d threads ------\n\n",t);
    }

    return 0;
}