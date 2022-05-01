#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "STRING.h"
#include "LIB.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MATRIX_SIZE 3

struct MATRIX
{
	double** m;
	int row, column;
};

typedef struct MATRIX MATRIX;

/*
	Creates a matrix with given row and column number
	Builds each item in the matrix with 0
	If there is not enough memory, program terminates
*/
MATRIX* MATRIX_build(int row, int column);

/*
	Creates a matrix with given string
	String format should be correct. Otehrwise returns NULL
*/
MATRIX* MATRIX_buildWithString(char* str);

/*
	Sets given item to the given matrix with given row and column
	Returns 1 if operation is successfull. Otherwise returns 0
*/
int MATRIX_setItem(MATRIX* m, int row, int column, double item);

/*
	Returns string form of given matrix
	If there is not enough memory, program terminates
*/
STRING* MATRIX_toString(MATRIX* m);

void MATRIX_print(void* m);

/*	Frees given matrix	*/
void MATRIX_free(void* matrix);

/*
	The function calculates covarianca matrix using given parameter
	Returns the covariance matrix
	Given character array size must be 10
	The given character array format must be %d=%d,%d,%d
*/
MATRIX* calcuateCovarianceMatrix(char**);

/*	Calculates frobenius norm of given matrix	*/
double calculateFrobeniusNorm(MATRIX* m);

#endif