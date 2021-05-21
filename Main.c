//
// Main.c
// Practica4
//
// Created by Beatriz Paulina Garcia Salgado
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ParallelMatrix.h"

int main(int argc, char** argv)
{
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////No cambiar este segmento////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Variables for matrix operations
	long double* A = NULL;
	long double* B = NULL;
	long double* C = NULL;
	long double count;
	int sizeMat = 100;
	int row,col;
	
	//Variables for thread management and time
	int numThreads;
	struct timespec t0, t1;
	double tiempoMedido;
	
	//Allocate matrices
	A = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	B = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	C = (long double*)malloc(sizeMat * sizeMat * sizeof(long double));
	if(!A || !B || !C)
	{
		printf("Cannot allocate the matrices\n");
		exit(EXIT_FAILURE);
	}
	
	//Set the maximum number of cores as available threads
	numThreads = getNumberOfCPUs();
	printf("Available cores: %d\n",numThreads);
	omp_set_num_threads(numThreads);
	
	//Initialise the matrices
	for(row = 0; row < sizeMat; row++)
	{
		count = 1;
		for(col = 0; col < sizeMat; col++)
		{
			*(A + row * sizeMat + col) = count;
			*(B + row * sizeMat + col) = 2;
			count++;
		}
	}
	
	checkSumAll(&count, A, sizeMat);
	printf("The addition of all components of A is %Lf\n",count);
	
	checkSumAll(&count, B, sizeMat);
	printf("The addition of all components of B is %Lf\n",count);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("\n-------------------------------------------------------------------\n");
	printf("\nMultiplicaion Normal\n");
	if(clock_gettime(CLOCK_MONOTONIC,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}
	
	matrixMult(&C, A, B, sizeMat);
	
	
	if(clock_gettime(CLOCK_MONOTONIC, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
	
	tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
	printf("Tiempo transcurrido: %lf segundos\n",tiempoMedido);
	checkSumAll(&count, C, sizeMat);
	printf("La suma de los componentes de C es %Lf\n",count);

	printf("\n-------------------------------------------------------------------\n");
	printf("\nMultiplicaion en Paralelo\n");

	if(clock_gettime(CLOCK_MONOTONIC,&t0) != 0)
	{
		printf("Error al llamar clock_gettime para t0\n");
		exit(EXIT_FAILURE);
	}
	
	ompParallelmatrixMult(&C, A, B, sizeMat);
	
	
	if(clock_gettime(CLOCK_MONOTONIC, &t1) != 0)
	{
		printf("Error al llamar clock_gettime para t1\n");
		exit(EXIT_FAILURE);
	}
	
	tiempoMedido = (double)(t1.tv_sec - t0.tv_sec) + ((double)(t1.tv_nsec - t0.tv_nsec)/1000000000L);
	printf("Tiempo transcurrido: %lf segundos\n",tiempoMedido);
	checkSumAll(&count, C, sizeMat);
	printf("La suma de los componentes de C es %Lf\n",count);
	

	//La multiplicacion a realizar es A*B.
	//El maximo debe obtenerse de la matriz A.
	
	//Inserte el codigo solicitado en la practica aqui.
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	return EXIT_SUCCESS;
}
