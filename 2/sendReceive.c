/*********************************************************************************
* FILE: sendReceive.c
* 
*
**********************************************************************************/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ) {

	int size, rank, dest, source, tag=1;
	char inmsg, outmsg='x';
	MPI_Status Stat;

	MPI_Init( &argc, &argv );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	
	if (rank == 0) {
		dest = 1;
		source = 1;
		MPI_Send( &outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD );
		MPI_Recv( &inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat );
		printf( "Soy el processo %d de %d y recibi %c\n", rank, size, inmsg );
	}
	else if (rank == 1) {
		dest = 0;
		source = 0;
		MPI_Recv( &inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &Stat );
		MPI_Send( &outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD );
		printf( "Soy el proceso %d de %d y recivi %c\n", rank, size, inmsg );
	}
	MPI_Finalize();
}

