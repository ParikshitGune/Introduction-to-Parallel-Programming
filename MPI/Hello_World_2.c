#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


#define BUFFER 20


int main(int argc, char* argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size<2)
    {
        printf("Only 2 or less processes!!\n");
        MPI_Finalize();
        exit(0);
    }

    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank == 0)
    {
        printf("Master with rank %d waiting for messages\n", 0);
        char str[BUFFER];
        for (int i = 0; i < size-1; i++)
        {
            MPI_Recv(str, BUFFER, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            int source = status.MPI_SOURCE;
            printf("Received message \"%s\" from process %d\n", str, source);
        }
    }
    else
    {
        char str[] = "Hello World!";
        MPI_Send(str, BUFFER, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
