CC=mpicc
CFLAGS=-o 
LIBS=-lm
SRC1=matvec_mpi.c
SRC2=vectesc_mpi.c
DIST=dist
EX1=matvec
EX2=vectesc

.PHONY: default
default: all

.PHONY: clean
clean:	
		@echo '------------------------------------------'
		@echo 'Eliminando directorio $(DIST) '
		rm -fr $(DIST)
		@echo '------------------------------------------'

all: mkd program1 program2 

mkd:
	@echo '------------------------------------'
	@echo 'Creando directorio $(DIST)'
	mkdir -p $(DIST)
	@echo '------------------------------------'

program1:
		@echo '------------------------------------'
		@echo 'Compilando $(SRC1) '
		$(CC) $(SRC1) $(CFLAGS) $(DIST)/$(EX1) $(LIBS)
		@echo '------------------------------------'

program2:
		@echo '------------------------------------'
		@echo 'Compilando $(SRC2) '
		$(CC) $(SRC2) $(CFLAGS) $(DIST)/$(EX2) $(LIBS)
		@echo '------------------------------------'

