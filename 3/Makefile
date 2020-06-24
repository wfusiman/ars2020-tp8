CC=mpicc
CFLAGS=-o 
MPIFLAGS=-lm
SRC1=matvec_mpi.c
SRC2=vectesc_mpi.c
DIST=dist
EX1=matvec
EX2=vectesc

.PHONY: default
default: all

.PHONY: clean
clean:	
		rm -fr $(DIST)

all: program1 program2 

program1:
		mkdir -p $(DIST)
		$(CC) $(SRC1) $(CFLAGS) $(DIST)/$(EX1) $(MPIFLAGS)

program2:
		mkdir -p $(DIST)
		$(CC) $(SRC2) $(CFLAGS) $(DIST)/$(EX2) $(MPIFLAGS)

