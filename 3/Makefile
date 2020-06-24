CC=mpicc
RUN=mpirun
CFLAGS=-o 
RFLAGS=-np
LIBS=-lm
SRC1=matvec_mpi.c
SRC2=vectesc_mpi.c
DIST=dist
EX1=matvec
EX2=vectesc
p=4

.PHONY: default
default: compile

.PHONY: clean
clean:	
		@echo '------------------------------------------'
		@echo 'Eliminando directorio $(DIST) '
		rm -fr $(DIST)
		@echo '------------------------------------------'


compile: mkd program2

compileall: mkd program1 program2 

run: compile
	@echo '------------------------------------'
	@echo Ejecutando $(EX2) con $(p) procesos
	$(RUN) $(RFLAGS) $(p) $(DIST)/$(EX2) 


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

