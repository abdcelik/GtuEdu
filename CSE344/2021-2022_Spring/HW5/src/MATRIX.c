#include "MATRIX.h"

MATRIX* MATRIX_build(int row, int column)
{
	if(row <= 0 || column <= 0)
		return NULL;

	MATRIX* m = x_calloc(1, sizeof(MATRIX));

	m->row = row;
	m->column = column;
	m->m = x_calloc(m->row, sizeof(double*));

	for(int i=0 ; i < m->row ; ++i)
		m->m[i] = x_calloc(m->column, sizeof(double));

	return m;
}

int MATRIX_setRow(MATRIX* m, int row, const char* items)
{
	if(row < 0 || row > m->row)
		return 0;

	for(int i=0 ; i  < m->column ; ++i)
		m->m[row][i] = (int)items[i];

	return 1;
}

double MATRIX_productForOneUnit(MATRIX* m1, MATRIX* m2, int rowNum, int columnNum)
{
	double res = 0;

	for(int i=0 ; i < m1->column ; ++i)
		res += m1->m[rowNum][i] * m2->m[i][columnNum];

	return res;
}

String* ComplexMatrix_rowToString(const ComplexMatrix* m, int rowNumber, int precision)
{
	if(m == NULL)
		return NULL;

	String* str = String_build();

	for(int i=0; i < m->real->column ; ++i)
	{
		String_addDoubleWithPrecision(str, m->real->m[rowNumber][i], precision);
		String_addCharArr(str, " + ");
		String_addDoubleWithPrecision(str, m->complex->m[rowNumber][i], precision);
		String_addChar(str, 'i');

		if(i != m->real->column - 1)
			String_addChar(str, ',');
	}

	return str;
}

void MATRIX_free(void* matrix)
{
	if(matrix)
	{
		MATRIX* mptr = (MATRIX*)matrix;

		if(mptr == NULL)
			return;

		if(mptr->m)
		{
			for(int i=0 ; i < mptr->row ; ++i)
				free(mptr->m[i]);
			
			free(mptr->m);
		}

		free(mptr);
	}
}

ComplexMatrix* ComplexMatrix_build(int row, int column)
{
	if(row <= 0 || column <= 0)
		return NULL;

	ComplexMatrix* m = x_calloc(1, sizeof(ComplexMatrix));

	m->real = MATRIX_build(row, column);
	m->complex = MATRIX_build(row, column);

	return m;
}

void ComplexMatrix_free(void* matrix)
{
	if(matrix)
	{
		ComplexMatrix* cm = (ComplexMatrix*)matrix;

		if(cm == NULL)
			return;

		if(cm->real != NULL)
			MATRIX_free(cm->real);

		if(cm->complex != NULL)
			MATRIX_free(cm->complex);

		free(cm);
	}
}