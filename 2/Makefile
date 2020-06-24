CC=mpicc
CFLAGS=-o
SRC1=helloWorld.c
SRC2=sendReceive.c
SRC3=mpi_helloBsend.c
DIST=dist
EX1=hello
EX2=sendRcv
EX3=helloBsend

.PHONY: default
default: all

.PHONY: clean
clean:	
		@echo '-------------------------------- '
		@echo 'Eliminando directorio $(DIST)'
		rm -fr $(DIST)
		@echo '-------------------------------- '

all: mkd program1 program2 program3 

mkd: 
	@echo '-------------------------------- '
	@echo 'Creando directorio $(DIST)'
	@mkdir -p $(DIST)
	@echo '-------------------------------- '


program1:
		@echo 'Compilando $(SRC1)'
		$(CC) $(SRC1) $(CFLAGS) $(DIST)/$(EX1)
		@echo '-------------------------------- '

program2:
		@echo 'Compilando $(SRC2) '
		$(CC) $(SRC2) $(CFLAGS) $(DIST)/$(EX2)
		@echo '-------------------------------- '

program3:
		@echo 'Compilando $(SRC3) '
		$(CC) $(SRC3) $(CFLAGS) $(DIST)/$(EX3)
		@echo '-------------------------------- '
		
		
