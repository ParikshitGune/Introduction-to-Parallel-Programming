#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int rank; 
	int num_of_processes;
	int namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_of_processes);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(processor_name,&namelen);
	
	printf("Hello Parallel World!!!! Rank: %d on %s out of %d Processes\n", rank,processor_name,num_of_processes);
	
	MPI_Finalize();
	
	return 0;
}