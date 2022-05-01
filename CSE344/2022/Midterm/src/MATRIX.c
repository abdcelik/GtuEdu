#include "MATRIX.h"

struct MATRIX
{
	int* m;
	int n;
};

int calculateDeterminant(const SQMATRIX*);
int myPower(int, int);

SQMATRIX* MATRIX_create(int n)
{
	if(n < 0)
		return NULL;

	SQMATRIX* matrix = x_malloc(sizeof(SQMATRIX));

	matrix->m = x_calloc(n * n, sizeof(int));
	matrix->n = n;

	return matrix;
}

SQMATRIX* MATRIX_createWith(const char* strMatrix)
{
	if(strMatrix == NULL)
		return NULL;

	int size = mySqrt(countComma(strMatrix) + 1);
	SQMATRIX* matrix = MATRIX_create(size);

	int var = 0, j = 0, sign = 1;

	for(int i=0 ; i < strlen(strMatrix) ; ++i)
	{
		if(strMatrix[i] == ',')
		{
			matrix->m[j++] = var * sign;
			var = 0;
			sign = 1;
		}
		else if(strMatrix[i] == '-')
			sign = -1;
		else if(i == strlen(strMatrix) -1)
			matrix->m[j] = var * sign;
		else
		{
			var *= 10;
			var += strMatrix[i] - '0';
		}
	}

	return matrix;
}

int MATRIX_size(const SQMATRIX* matrix)
{
	if(matrix == NULL)
		return -1;

	return matrix->n;
}

SQMATRIX* MATRIX_minor(const SQMATRIX* matrix, int row, int column)
{
	if(matrix == NULL || matrix->n < 2 || row < 1 || row > matrix->n || column < 1 || column > matrix->n)
		return NULL;

	SQMATRIX* minor = MATRIX_create(matrix->n - 1);

	for(int i=0, j=0, r=1, c=1 ; i < matrix->n * matrix->n ; ++i, ++c)
	{
		if(row != r && column != c)
			minor->m[j++] = matrix->m[i];

		if((i + 1) % matrix->n == 0)
			++r;

		if(c == matrix->n)
			c = 0;
	}

	return minor;
}

int MATRIX_isInvertible(const SQMATRIX* matrix)
{
	if(matrix == NULL)
		return 0;
	return calculateDeterminant(matrix) == 0 ? 0 : 1;
}

int MATRIX_determinant(const SQMATRIX* matrix)
{
	if(matrix == NULL)
		return 0;

	return calculateDeterminant(matrix);
}

void MATRIX_free(void* m)
{
	if(m == NULL)
		return;

	SQMATRIX* sqm = (SQMATRIX*)m;

	if(sqm == NULL)
		return;

	free(sqm->m);
	free(sqm);
}

int calculateDeterminant(const SQMATRIX* matrix)
{
	if(matrix->n == 2)
		return matrix->m[0] * matrix->m[3] - matrix->m[1] * matrix->m[2];

	int determinant = 0;

	for(int i=0 ; i < matrix->n ; ++i)
	{
		SQMATRIX* temp = MATRIX_minor(matrix, 1, i + 1);
		determinant += matrix->m[i] * myPower(-1, i + 2) * calculateDeterminant(temp);
		MATRIX_free(temp);
	}

	return determinant;
}

int countComma(const char* s)
{
	int counter = 0;

	for(; *s ; ++s)
		if(*s == ',')
			++counter;

	return counter;
}

int mySqrt(int var)
{
	for(int i = 2 ; i < var ; ++i)
		if(i * i == var)
			return i;
	return -1;
}

int myPower(int base, int exp)
{
	int res = 1;

	for(int i=0 ; i < exp ; ++i)
		res *= base;

	return res;
}