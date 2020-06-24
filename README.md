# ARQUITECTURA DE REDES Y SERVICIOS - 2020 
## RESOLUCION TRABAJO PRACTICO 8
## Parallel programming MPI

1. Instalacion openMPI en Ubuntu 18.04

sudo apt-get install openmpi-bin openmpi-common openssh-client openssh-server libopenmpi2 libopenmpi-dev

2. Compilacion de los programas anexos.

codigo de los programas: https://github.com/wfusiman/ars2020-tp8/2

En la carpeta 2 ejecutar el comando make, para compilar y generar los binarios en la carpeta 2/dist.
Ejecutar make clean para eliminar eliminar los binarios.

3 Programa que dado, un vector y un escalar, resuelve el producto. Se distrubuyen los elementos del vector entre procesos disponibles.
Muestra el vector original y el vector resultado.

codigo del  programa: https://github.com/wfusiman/ars2020-tp8/3

En la carpeta 3 ejecutar el comando make, para compilar y generar los binarios en la carpeta 3/dist.
Ejecutar make clean si se quiere eliminar los binarios.
