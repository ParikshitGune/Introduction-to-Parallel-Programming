#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>

#define MATRIX_SIZE 20

int main(int argc, char* argv[])
{
	int size, rank_of_process, i, j, a[MATRIX_SIZE][MATRIX_SIZE];
	int block_lengths[MATRIX_SIZE],displacement[MATRIX_SIZE];
	MPI_Datatype upper_trinagular_matrix;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank_of_process);

	for(i = 0; i < MATRIX_SIZE; i++)
	{
		block_lengths[i] = MATRIX_SIZE - i;
		displacement[i] = i * MATRIX_SIZE + i;
	}



	MPI_Type_indexed(MATRIX_SIZE, block_lengths, displacement, MPI_INT, &upper_trinagular_matrix);
	MPI_Type_commit(&upper_trinagular_matrix);
	if(rank_of_process == 0)
	{
		for(i = 0; i < MATRIX_SIZE; i++)
			{
			for(j = 0; j < MATRIX_SIZE; j++){

				a[i][j] = rand() % 10;
				printf("%d ",a[i][j]);}
			printf("\n");
		}
		MPI_Send(a, 1, upper_trinagular_matrix, 1, 0, MPI_COMM_WORLD);
	}
	else if(rank_of_process == 1)
	{
		
	
		for(i = 0; i < MATRIX_SIZE; i++)
			for(j = 0; j < MATRIX_SIZE; j++)
				a[i][j] = 0;
		MPI_Recv(a, 1, upper_trinagular_matrix, 0, 0, MPI_COMM_WORLD, &status);
		printf("\n");
		printf("output upper triangular matrix \n");
		printf("\n");
		for(i = 0; i < MATRIX_SIZE; i++)
		{
			for(j = 0; j < MATRIX_SIZE; j++)
				printf("%d ",a[i][j]);
			printf("\n");
		}
	}
	MPI_Type_free(&upper_trinagular_matrix);
	MPI_Finalize();

}