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
		rm -fr $(DIST)

all: program1 program2 program3

program1:
		mkdir -p $(DIST)
		$(CC) $(SRC1) $(CFLAGS) $(DIST)/$(EX1)

program2:
		mkdir -p $(DIST)
		$(CC) $(SRC2) $(CFLAGS) $(DIST)/$(EX2)

program3:
		mkdir -p $(DIST)
		$(CC) $(SRC3) $(CFLAGS) $(DIST)/$(EX3)
		
		
