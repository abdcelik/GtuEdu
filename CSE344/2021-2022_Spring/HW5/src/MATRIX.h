#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "LIB.h"
#include "String.h"

struct MATRIX
{
	double** m;
	int row, column;
};

typedef struct MATRIX MATRIX;

struct ComplexMatrix
{
	MATRIX* real;
	MATRIX* complex;
};

typedef struct ComplexMatrix ComplexMatrix;

/*
	Creates a matrix with given row and column number
	Builds each item in the matrix with 0
	If there is not enough memory, program terminates
*/
MATRIX* MATRIX_build(int row, int column);

/*
	Sets given items to the given matrix with given row number
	Returns 1 if operation is successfull. Otherwise returns 0
*/
int MATRIX_setRow(MATRIX* m, int row, const char* items);

/*
	Applies matrix multiplicatin to the columnNum column of the given matrix m2 with the rowNum row of the given matrix m1
	Returns the calculated result
	Does not check error
*/
double MATRIX_productForOneUnit(MATRIX* m1, MATRIX* m2, int rowNum, int columnNum);

/*	Frees given matrix	*/
void MATRIX_free(void* matrix);

ComplexMatrix* ComplexMatrix_build(int row, int column);

void ComplexMatrix_free(void* matrix);

String* ComplexMatrix_rowToString(const ComplexMatrix* m, int rowNumber, int precision);

#endif