/*************************************************************************************************************
* FILE: vectesc_mpi.c
* DESCRPTIOM: Multiplica un vector por un escalar distribuyendo el calculo entre varios procesos paralelos.
* AUTHOR: Waldo Fusiman
**************************************************************************************************************/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100
#define MAX_VECTOR 100
#define MASTER 0

int main( int argc, char *argv[] ) {

	int id_proc;		// id del proceso actual.
	int num_procs; 		// numero total de procesos.
	double V[MAX_VECTOR];  		// V: vector inicial 
	double c; 			// escalar
	double R[MAX_VECTOR]; 			// Vector resultado
	int ierr;
	MPI_Status status;
	int i;
	double ans;
	int index;
	int proc_dest;
	int tag;
	int workers;
	int tag_done = MAX_VECTOR + 1;
	int empty = 0;

	ierr = MPI_Init( &argc, &argv );
	if (ierr != 0) {
		printf( "\nVECTESC_MPI - Fatal error\n" );
		exit( 1 );
	}
	
	ierr = MPI_Comm_rank( MPI_COMM_WORLD, &id_proc );
	ierr = MPI_Comm_size( MPI_COMM_WORLD, &num_procs );

	if(id_proc == MASTER) {
		printf( "\n\n\n\t VECTESC_MPI - Proceso maestro: programa MPI que calcula el producto de un vector por un escalar R = V * c. \n\n" );
		printf( " \t compilado %s a las %s\n", __DATE__, __TIME__ );
		printf( " \t Numero de procesos: %d\n", num_procs );
	}

	if (id_proc == MASTER) {
		for (i = 0; i < MAX_VECTOR; i++) {
			V[i] = rand() % MAX_NUM; // asigna un numero aleatorio entre 0 y 1000.
		}
		c = rand() % MAX_NUM;
	 }

	ierr = MPI_Bcast( &c, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD ); // envia a todos los procesos el escalar.

	if (id_proc == MASTER) { // proceso master
		index = 0;
		for (i = 1; i <= num_procs -1; i++) {
			proc_dest = i;
			tag = index;
			ierr = MPI_Send( &V[index], 1, MPI_DOUBLE, proc_dest, tag, MPI_COMM_WORLD );
			index++;
		}
		workers = num_procs-1;
		for ( ; ; ) {
			ierr = MPI_Recv( &ans, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
			tag = status.MPI_TAG;
			R[tag] = ans;
			if (index < MAX_VECTOR) {
				proc_dest = status.MPI_SOURCE;
				tag = index;
				ierr = MPI_Send( &V[index], 1, MPI_DOUBLE, proc_dest, tag, MPI_COMM_WORLD );
				index++;
			}
			else {
				workers--;
				proc_dest = status.MPI_SOURCE;
				tag = tag_done;
				ierr = MPI_Send( &empty, 1, MPI_INT, proc_dest, tag, MPI_COMM_WORLD );
				if (workers == 0)
					break;				 
			}			
		}
	}	
	else {  // procesos workers
		double result;
		double item;
		for ( ; ; ) {
			ierr = MPI_Recv( &item, 1, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
			tag = status.MPI_TAG;
			if (tag == tag_done) {
				break;
			}
			result = c * item;
			ierr = MPI_Send( &result, 1, MPI_DOUBLE, MASTER, tag, MPI_COMM_WORLD );
		}	
	}

	/* Imprimir los resultado */
	if (id_proc == MASTER) {
		printf( "\n--------------------------------------------------------------------------------------------------------------------------------------------------------" );
		printf( "\nESCALAR \n c = %f\n", c ); // Imprime escalar

		printf( "\n\nVECTOR ORIGINAL: \n" );
		for (i=0; i < MAX_VECTOR; i++) { // Imprime vector original.
			printf( "\t%d- %5.2f", i, V[i] );
			if (i % 5 == 0) 
				printf("\n" );
		}

		printf( "\n\nVECTOR RESULTADO: \n" );
		for (i=0; i < MAX_VECTOR; i++) {  // Imprime vector resultado.
			printf( "\t%d- %5.2f", i, R[i] );
			if (i % 5 == 0) 
				printf("\n" );
		}
		printf( "\n--------------------------------------------------------------------------------------------------------------------------------------------------------" );
	}

	ierr = MPI_Finalize();

	if (id_proc == MASTER) 
		printf( "\n\n\n\n VECTESC_MPI - Proceso maestro: final de ejecucion normal \n\n\n\n" );
	
	return 0;		
}
		
