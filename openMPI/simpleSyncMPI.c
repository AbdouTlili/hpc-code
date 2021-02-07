#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    int rang,p,val,tag=10;
    MPI_Status status;


    /* MPI initialize */
    MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD,&rang);


    if(rang==1){
        val = 99;
        MPI_Send(&val,1,MPI_INT,0,tag,MPI_COMM_WORLD);
        printf("\nmessage send t0 communicator 0\n");
    }
    if (rang ==0 ){
        printf("\nthe value of val in process 0 is %d\n",val);
        MPI_Recv(&val,1,MPI_INT,1,tag,MPI_COMM_WORLD,
        &status);
        printf("\n successfuly received the value from process 1, it's value is : %d\n",val);       
    }

    MPI_Finalize();
    return 0 ;
}