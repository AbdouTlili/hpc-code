#include <stdio.h>
#include <stdlib.h>


void carre(int tab[],int length){
    for(int i=0; i <length;i++){
        tab[i] = tab[i]*tab[i];
    }
}


int main(char argc, char * argv[]){

    //declarations 
    int N ;
    
    // casting the table length
    N = atoi(argv[1]);

    int tab[N];
    
    for(int i = 0; i <N;i++){
        tab[i]=rand() % 1000;
    }


/*
    for(int i = 0; i <N;i++){
        printf("%d-",tab[i]);
    }
*/
    carre(tab,N);
/*
    printf("\n");

    for(int i = 0; i <N;i++){
        printf("%d-",tab[i]);
    }
*/
    return 0;
}

