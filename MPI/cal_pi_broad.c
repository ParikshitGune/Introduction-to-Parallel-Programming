#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define STEPS 100000

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    double PI = 3.141592653589793238462643;
    double start , end;
    start = MPI_Wtime();
    double step = 1.0/(double)STEPS, work;

    if (rank == 0)
    {
        work = STEPS/size;
    }

   
    MPI_Bcast(&work, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double x, sum=0;
    for (int i = rank*work; i < (rank+1)*work; i++)
    {
        x = (i+0.5)*step;
        sum += 4.0/(1.0+x*x);
    }
    double pi = step * sum;
    
    double pisum;
    MPI_Reduce(&pi, &pisum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0) 
        {
            printf("Approximated value of pi: %.16f \n Error is: %.16f \n", pisum, fabs(PI-pisum));
            end = MPI_Wtime();
            printf("Time taken is : %f\n",end-start );
        }
    MPI_Finalize();
    return 0;
}