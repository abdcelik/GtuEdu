#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include "LIB.h"

typedef struct MATRIX SQMATRIX;

SQMATRIX* MATRIX_create(int);
/*
	Creates matrix with given formatted string
	Returns square matrix or NULL if any error occurs
*/
SQMATRIX* MATRIX_createWith(const char*);

/*	Returns given matrix's size	*/
int MATRIX_size(const SQMATRIX*);

/*	Returns given matrix's minor with given row and column number	*/
SQMATRIX* MATRIX_minor(const SQMATRIX*, int row, int column);

/*
	Calculates determinant of given matrix using cofactor method
	If determinant is 0, matrix isn't invertible
	Returns 1 if given matrix is invertible. Otherwise returns 0
*/
int MATRIX_isInvertible(const SQMATRIX*);

/*	Returns given matrix's determinant using cofactor method	*/
int MATRIX_determinant(const SQMATRIX*);

/*	Frees given matrix	*/
void MATRIX_free(void*);

/*	Counts number of comma for given string	*/
int countComma(const char*);

/*	Simple sqrt function	*/
int mySqrt(int);

#endif