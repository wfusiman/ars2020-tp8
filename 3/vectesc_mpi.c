/*************************************************************************************************************
* FILE: vectesc_mpi.c
* DESCRPTIOM: Multiplica un vector por un escalar distribuyendo el calculo entre varios procesos paralelos.
* AUTHOR: Waldo Fusiman
**************************************************************************************************************/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_VECTOR 1000
#define MASTER 0

int main( int argc, char *argv[] ) {

	int id_proc;		// id del proceso actual.
	int num_procs; 		// numero total de procesos.
	double V[MAX_VECTOR];  		// V: vector inicial 
	double c; 			// escalar
	double R[MAX_VECTOR]; 			// Vector resultado
	double item; 		// item del vector
	int ierr;
	MPI_Status status;
	int i;
	double ans;
	int tag_done = MAX_VECTOR + 1;

	ierr = MPI_Init( &argc, &argv );
	if (ierr != 0) {
		printf( "\nVECTESC_MPI - Fatal error\n" );
		exit( 1 );
	}
	
	ierr = MPI_Comm_rank( MPI_COMM_WORLD, &id_proc );
	ierr = MPI_Comm_size( MPI_COMM_WORLD, &num_procs );

	if(id_proc == MASTER) {
		printf( "\n VECTESC_MPI - Proceso maestro: programa MPI que calcula el producto de un vector por un escalar R = V * c. \n\n" );
		printf( "compilado %s a las %s\n", __DATE__, __TIME__ );
		printf( "El numero de procesos es %d\n", num_procs );
	}

	if (id_proc == MASTER) {
		printf( "Inicializando vector V. \n" );
		for (i = 0; i < MAX_VECTOR; i++) {
			V[i] = rand() % MAX_VECTOR; // asigna un numero aleatorio entre 0 y 1000.
		}
		printf( "inicializando escalar c. \n" );
		c = rand() % MAX_VECTOR;
	}

	ierr = MPI_Bcast( c, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD ); // envia a todos los procesos el escalar.

	if (id_proc == MASTER) { // proceso master
		int worker = 1;
		for (i = 0; i < MAX_VECTOR; i++) { // El master envia a cada proceso un numero del vector a calcular.
			ierr = MPI_Send( V[i], 1, MPI_DOUBLE, worker, 1, MPI_COMM_WORLD );
			if (worker == num_procs-1)
				worker = 1;
			else
				worker++;
		}
		for (i = 1; i <= num_procs-1; i++) 
			ierr = MPI_Send( V[0], 1, MPI_DOUBLE, i, tag_done, MPI_COMM_WORLD );

		for (; ; ) {
			ierr = MPI_Recv( &ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORL, &status );
			
		}
	
	}
	else {  // procesos workers
	
	}

	if (id_proc == MASTER) {
		for (i=0; i <= MAX_VECTOR; i++) {
			printf( "$d %f", i, V[i] );
			if (i % 10) 
				printf( "\n" );
		}
	}
}
		
