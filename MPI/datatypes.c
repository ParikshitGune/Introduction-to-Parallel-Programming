
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

struct new_structure
{
    char c;
    int i[2];
    float f[4];
}s, send_broadcast, send_point_to_point;

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
  
    int number_of_blocks = 3;
    int array_of_block_length[] = {1, 2, 5};
    

    MPI_Aint displacements[3];
    displacements[0] = (MPI_Aint)0;
    int block_1_address, block_2_address, block_3_address;
    MPI_Get_address(&s.c, &block_1_address);
    MPI_Get_address(s.i, &block_2_address);
    MPI_Get_address(s.f, &block_3_address);
    displacements[1] = block_2_address - block_1_address;
    displacements[2] = block_3_address - block_2_address;

    MPI_Datatype types[] = {MPI_CHAR, MPI_INT, MPI_FLOAT};
    MPI_Datatype new_type;

    MPI_Type_create_struct(number_of_blocks, array_of_block_length, displacements, types, &new_type);
    MPI_Type_commit(&new_type); //Committing our new type


    ////////BROADCAST COMMUNICATION////////////
    //struct send_broadcast filled in 0
    if (rank == 0)
    {
        send_broadcast.c = 'A';
        send_broadcast.i[0] = 1;
        send_broadcast.i[1] = 2;
        send_broadcast.f[0] = 3.1;
        send_broadcast.f[1] = 4.2;
        send_broadcast.f[2] = 5.3;
        send_broadcast.f[3] = 6.4;
        printf("\nMaster setting send_broadcast as follows: \n");
        printf("c: %c\n i: {%d, %d}\n f: {%f, %f, %f, %f}\n", send_broadcast.c, send_broadcast.i[0], 
            send_broadcast.i[1], send_broadcast.f[0], send_broadcast.f[1], send_broadcast.f[2], send_broadcast.f[3]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&send_broadcast, 1, new_type, 0, MPI_COMM_WORLD);
    printf("\nBCAST: %d received send_broadcast as follows:\n c: %c\n i: {%d, %d}\n f: {%f, %f, %f, %f}\n", rank, send_broadcast.c, send_broadcast.i[0], 
        send_broadcast.i[1], send_broadcast.f[0], send_broadcast.f[1], send_broadcast.f[2], send_broadcast.f[3]);


   
    if (rank == 0)
    {
        send_point_to_point.c = 'B';
        send_point_to_point.i[0] = 6;
        send_point_to_point.i[1] = 7;
        send_point_to_point.f[0] = 8.1;
        send_point_to_point.f[1] = 8.2;
        send_point_to_point.f[2] = 8.3;
        send_point_to_point.f[3] = 8.4;
        printf("\nMaster setting send_point_to_point as follows:\n ");
        printf("c: %c\n i: {%d, %d}\n f: {%f, %f, %f, %f}\n", send_point_to_point.c, send_point_to_point.i[0], 
            send_point_to_point.i[1], send_point_to_point.f[0], send_point_to_point.f[1], send_point_to_point.f[2], send_point_to_point.f[3]);
    }

    for (int i = 1; i < size; i++)
    {
        if (rank == 0)
        {
            MPI_Send(&send_point_to_point, 1, new_type, i, 0, MPI_COMM_WORLD);
        }
        if (rank == i)
        {
            MPI_Recv(&send_point_to_point, 1, new_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("\nP2P: %d received send_point_to_point as follows:\nc: %c\n i: {%d, %d}\n f: {%f, %f, %f, %f}\n", rank, send_point_to_point.c, send_point_to_point.i[0], 
                send_point_to_point.i[1], send_point_to_point.f[0], send_point_to_point.f[1], send_point_to_point.f[2], send_point_to_point.f[3]);
        }
    }

    MPI_Finalize();
    return 0;
}