/*********************************************************************************************************************
* FILE: matvec_mpi.c
* DESCRIPTION: multiplica un vector por una matriz.
*********************************************************************************************************************/

#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
* timestamp: TIMESTAMP prints the current YMDHMS date as a time stamp.
*/
void timestamp() {
#define TIME_SIZE 40
	
	static char time_buffer[TIME_SIZE];
	const struct tm *tm;
	time_t now;

	now = time( NULL );
	tm = localtime( &now );
	strftime( time_buffer, TIME_SIZE, "%d %B %Y %I %M %S %p", tm );
	printf( "%s\n", time_buffer );
	return;
#undef TIME_SIZE	
}


int main( int argc, char *argv[] ) 
{
 	double *a;
	double *a_row;
	double ans;
	double *b;
	int dest;
	int dummy;
	int i, ierr, j, j_one, k, m, s;
	int master = 0;
	int my_id, n, num_procs, num_rows, num_workers;
	double pi = 3.141592653589793;
	MPI_Status status;
	int tag;
	int tag_done;
	double *x;

	/* Initializa MPI */
	ierr = MPI_Init( &argc, &argv );
	if (ierr != 0) {
		printf( "\n" );
		printf( "MATVEC_MPI - Fatal error \n" );
		printf( " MPI_INIT return nonzero IERR \n" );
		exit( 1 );
	}

	/* get id processor */
	ierr = MPI_Comm_rank( MPI_COMM_WORLD, &my_id );
	/* get the number of processors. */
	ierr = MPI_Comm_size( MPI_COMM_WORLD, &num_procs );

	if (my_id == 0) {
		timestamp();
		printf( "\n" );
		printf( "MATVEC MPI - Master process \n C version \n A MPI example program to compute a matrix-vector product b = A * x. \n\n" );
		printf( "compiled on %s at %s\n", __DATE__, __TIME__ );
		printf( " \n" );
		printf( "The number of processes is %d.\n", num_procs );
	}

	printf( "\n" );
	printf( "Process %d is active.\n", my_id );
	
	m = 1000;
	n = 50;
	tag_done = m + 1;

	if (my_id == 0) {
		printf( "\n" );
		printf( "The number of rows is %d\n", m );
		printf( "The number of columns is %d\n", n );
	}
	
	/* The master prcess allocates and inicializes A and X. */
	if (my_id == master)  {
		a = (double *) malloc( m * n * sizeof( double ) );
		x = (double *) malloc( n * sizeof( double ) );
		b = (double *) malloc( m * sizeof( double ) );
		
		k = 0;
		for (i = 1; i <= m; i++ ) {
			for (j = 1; j <= n; j++) {
				a[k] = sqrt( 2.0 / (double)(n + 1)) * sin( (double)(i * j) * pi / (double)(n + 1) );
				k = k + 1;
			}
		}
		
		/* X is specially choosen so that b = A * x is known in advance. The value of b will be zero, except that entry J_ONE will be 1. Pick any value of J_ONE between 1 and M. */
		j_one = 17;
		for (i = 0; i < n; i++) {
			x[i] = sqrt( 2.0 / (double)(n + 1) ) * sin( (double)((i + 1) * j_one) * pi / (double)(n + 1) );
		}

		printf( "\n" );
		printf( "MATVEC- Master process:\n" );
		printf( "  Vector x: \n" );
		printf( " \n" );
		
		for (i = 0; i < n; i++) 
			printf( "%d %f\n", i, x[i] );
	}
	else { /* Worker processes set aside room for one row of A, and for the vector X. */
		a_row = (double *) malloc( n * sizeof( double ) );
		x = (double *) malloc( n * sizeof( double ) );
	}
	/* Process 0 broadcast the vector X to the other processes */	
		ierr = MPI_Bcast( x, n, MPI_DOUBLE, master, MPI_COMM_WORLD );

	/* Process 0 send one row of A to all the other processes. */
	if (my_id == master) {
		num_rows = 0;
		for (i = 1; i <= num_procs - 1; i++) {
			dest = i;
			tag = num_rows;
			k = num_rows * n;
			ierr = MPI_Send( a+k, n, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD );
			num_rows = num_rows + 1;
		}
		
		num_workers = num_procs - 1;
		for (; ; ) {
			ierr = MPI_Recv( &ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
			tag = status.MPI_TAG;
			b[tag] = ans;
			
			if (num_rows < m) {
				num_rows = num_rows + 1;
				dest = status.MPI_SOURCE;
				tag = num_rows;
				k = num_rows * n;
				ierr = MPI_Send( a+k,n, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD );
			}
			else {
				num_workers = num_workers - 1;
				dummy = 0;
				dest = status.MPI_SOURCE;
				tag = tag_done;
				ierr = MPI_Send( &dummy, 1, MPI_INT, dest, tag, MPI_COMM_WORLD );
				if (num_workers == 0) 
					break;
			}
		}
		
		free( a );
		free( x );
	}
	else {
		for (; ; ) {
			ierr = MPI_Recv( a_row, n, MPI_DOUBLE, master, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
			tag = status.MPI_TAG;
			if (tag == tag_done) {
				printf( "  Process %d shutting down.\n" , my_id );
				break;
			}
			ans = 0.0;
			for (i = 0; i < n; i++) 
				ans = ans + a_row[i] * x[i];
			ierr = MPI_Send( &ans, 1, MPI_DOUBLE, master, tag, MPI_COMM_WORLD );
		}
		free( a_row );
		free( x );
	}

	/* Print out the answer */
	if (my_id == master) {
		printf( "\n" );
		printf( "MATVEC- Master process:\n" );
		printf( "  Product vector b = A * x.\n (should be zero, except for a 1 in entry %d) \n",j_one - 1 );
		printf( " \n" );
		for (i = 0; i < m; i++ ) {
			printf( "%d %f \n",i, b[i] );
		}
		free( b );
	}

	/* Terminate MPI */
	ierr = MPI_Finalize();
	
	/* Terminate */
	if (my_id == master) {
		printf( "\n" );
		printf( "MATVEC- Master process:\n" );
		printf( "  Normal end of execution... \n" );
		printf( " \n" );
		timestamp();
	}
	
	return 0;
}

			
			
