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
    
    char buffer_broadcast[200], buffer_point_to_point[200];
    int position;

 
    if (rank == 0)
    {
        send_broadcast.c = 'B';
        send_broadcast.i[0] = 3;
        send_broadcast.i[1] = 4;
        send_broadcast.f[0] = 5.2;
        send_broadcast.f[1] = 5.5;
        send_broadcast.f[2] = 5.1;
        send_broadcast.f[3] = 6.1;
        printf("\nMaster setting send_broadcast as follows: \n");
        printf("c: %c\n i: {%d, %d}\n f: {%f, %f, %f, %f}\n", send_broadcast.c, send_broadcast.i[0], 
            send_broadcast.i[1], send_broadcast.f[0], send_broadcast.f[1], send_broadcast.f[2], send_broadcast.f[3]);
        
        position = 10;
        MPI_Pack(&send_broadcast.c, 1, MPI_CHAR, buffer_broadcast, 200, &position, MPI_COMM_WORLD);
        MPI_Pack(send_broadcast.i, 2, MPI_INT, buffer_broadcast, 200, &position, MPI_COMM_WORLD);
        MPI_Pack(send_broadcast.f, 5, MPI_FLOAT, buffer_broadcast, 200, &position, MPI_COMM_WORLD);
    }

    MPI_Bcast(buffer_broadcast, 200, MPI_CHAR, 0, MPI_COMM_WORLD);
    position = 10;
    MPI_Unpack(buffer_broadcast, 200, &position, &send_broadcast.c, 1, MPI_CHAR, MPI_COMM_WORLD);
    MPI_Unpack(buffer_broadcast, 200, &position, send_broadcast.i, 2, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(buffer_broadcast, 200, &position, send_broadcast.f, 4, MPI_FLOAT, MPI_COMM_WORLD);
    
    printf("\nBCAST: %d received buffer_broadcast and unpacked send_broadcast as follows:\n c: %c\n i: {%d, %d}\n f: {%f, %f, %f, %f}\n", rank, send_broadcast.c, send_broadcast.i[0], 
        send_broadcast.i[1], send_broadcast.f[0], send_broadcast.f[1], send_broadcast.f[2], send_broadcast.f[3]);


    if (rank == 0)
    {
        send_point_to_point.c = 'P';
        send_point_to_point.i[0] = 7;
        send_point_to_point.i[1] = 8;
        send_point_to_point.f[0] = 9.3;
        send_point_to_point.f[1] = 9.5;
        send_point_to_point.f[2] = 9.1;
        send_point_to_point.f[3] = 9.4;
        printf("\nMaster setting send_point_to_point as follows:\n ");
        printf("c: %c\n i: {%d, %d}\n f: {%f, %f, %f, %f}\n", send_point_to_point.c, send_point_to_point.i[0], 
            send_point_to_point.i[1], send_point_to_point.f[0], send_point_to_point.f[1], send_point_to_point.f[2], send_point_to_point.f[3]);

        position = 0;
        MPI_Pack(&send_point_to_point.c, 1, MPI_CHAR, buffer_point_to_point, 200, &position, MPI_COMM_WORLD);
        MPI_Pack(send_point_to_point.i, 2, MPI_INT, buffer_point_to_point, 200, &position, MPI_COMM_WORLD);
        MPI_Pack(send_point_to_point.f, 5, MPI_FLOAT, buffer_point_to_point, 200, &position, MPI_COMM_WORLD);
    }

    for (int i = 1; i < size; i++)
    {
        if (rank == 0)
        {
            MPI_Send(&buffer_point_to_point, 200, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        if (rank == i)
        {
            MPI_Recv(&buffer_point_to_point, 200, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            position = 0;
            MPI_Unpack(buffer_point_to_point, 200, &position, &send_point_to_point.c, 1, MPI_CHAR, MPI_COMM_WORLD);
            MPI_Unpack(buffer_point_to_point, 200, &position, send_point_to_point.i, 2, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffer_point_to_point, 200, &position, send_point_to_point.f, 4, MPI_FLOAT, MPI_COMM_WORLD);
            printf("\nP2P: %d received buffer_point_to_point and unpacked send_point_to_point as follows:\n c: %c\n i: {%d, %d}\n f: {%f, %f, %f, %f}\n", rank, send_point_to_point.c, send_point_to_point.i[0], 
                send_point_to_point.i[1], send_point_to_point.f[0], send_point_to_point.f[1], send_point_to_point.f[2], send_point_to_point.f[3]);
        }
    }

    MPI_Finalize();
    return 0;
}