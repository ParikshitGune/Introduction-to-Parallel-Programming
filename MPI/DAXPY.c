#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define length 65336

int X[length], Y[length], serial_X[length], serial_Y[length];
int a = 2;

void Array_init()
{
    for (int i = 0; i < length; i++)
    {
        X[i] = rand()%4;
        serial_X[i] = X[i];
        Y[i] = rand()%4;
        serial_Y[i] = Y[i];
    }
}

int main(int argc, char* argv[])
{
    int rank, number_of_processors;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processors);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) printf("No. of processes: %d\n", number_of_processors);
    double work = (double)length/number_of_processors;
    double t1 = MPI_Wtime();
    for (int i = rank*work; i < (rank+1)*work; i++)
    {
        X[i] = a*X[i] + Y[i];
    }
    t1 = MPI_Wtime() - t1;
    double t2 = MPI_Wtime();

    if(rank == 0)
    {
        for (int i = 0; i < length; i++)
        {
            serial_X[i] = a*serial_X[i] + serial_Y[i];
        }
    }

   
    t2 = MPI_Wtime() - t2;

    if (rank == 0)
    {
        printf("Time taken for multiprocessor calculation: %lf\n", t1);
        printf("Time taken for uniprocessor implementation: %lf\n", t2);
        printf("%lf times faster\n", t2/t1);
    }    

    MPI_Finalize();

    return 0;
}