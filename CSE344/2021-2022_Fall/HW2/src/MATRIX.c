#include "MATRIX.h"

double calculateMean(int[], int);
double calculateSampleVariance(int[], double, int);
double calculateSampleCovariance(int[], int[], int, double, double);

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

MATRIX* MATRIX_buildWithString(char* str)
{
	if(!str)
		return NULL;

	int len = strlen(str);
	int r = 0, c = 0;

	for(int i=0 ; i < len ; ++i)
	{
		if(str[i] == '(')
			++r;
		else if(str[i] == ' ')
			++c;
	}

	c = c / r + 1;

	MATRIX* m = MATRIX_build(r, c);
	++str; // for '['

	for(int i=0 ; i < m->row ; ++i)
	{
		for(int j=0 ; j < m->column ; ++j)
		{
			if(*str == '(')
				++str;

			sscanf(str, "%lf", &m->m[i][j]);

			while(*str != ' ' && *str != ')')
				++str;

			if(*str == ' ')
				++str;
		}
		++str; // for ')'
	}

	return m;
}

int MATRIX_setItem(MATRIX* m, int row, int column, double item)
{
	if(!m || row < 0 || column < 0 || row > m->row || column > m->column)
		return 0;

	m->m[row-1][column-1] = item;
	return 1;
}

STRING* MATRIX_toString(MATRIX* m)
{
	if(!m)
		return NULL;

	STRING* str = STRING_build();
	STRING_addChar(str, '[');

	for(int i=0 ; i < m->row ; ++i)
	{
		STRING_addChar(str, '(');
		for(int j=0 ; j < m->column ; ++j)
		{
			STRING_addDouble(str, m->m[i][j], 3);

			if(j < m->column - 1)
				STRING_addChar(str, ' ');
		}

		STRING_addChar(str, ')');
	}

	STRING_addCharArr(str, "]");
	return str;
}

void MATRIX_print(void* m)
{
	STRING* s = MATRIX_toString(m);

	if(s == NULL)
		return;

	fprintf(stdout, "%s", STRING_getCharArr(s));
}

void MATRIX_free(void* matrix)
{
	if(matrix)
	{
		MATRIX* mptr = (MATRIX*)matrix;

		if(mptr && mptr->m)
		{
			for(int i=0 ; i < mptr->row ; ++i)
				if(mptr->m[i])
					free(mptr->m[i]);
			free(mptr->m);
		}

		free(mptr);
	}
}

double calculateFrobeniusNorm(MATRIX* m)
{
	if(!m)
		return 0;

	double total = 0;

	for(int i=0 ; i < m->row ; ++i)
		for(int j=0 ; j < m->column ; ++j)
			total += pow(m->m[i][j], 2);

	return sqrt(total);
}

MATRIX* calcuateCovarianceMatrix(char** point)
{
	if(!point)
		return NULL;

	int size = 10;
	int sampleX[size], sampleY[size], sampleZ[size];

	for(int i=0 ; point[i] ; ++i)
		sscanf(point[i], "(%d,%d,%d)", &sampleX[i], &sampleY[i], &sampleZ[i]);

	double meanX = calculateMean(sampleX, size);
	double meanY = calculateMean(sampleY, size);
	double meanZ = calculateMean(sampleZ, size);

	MATRIX* m = MATRIX_build(MATRIX_SIZE, MATRIX_SIZE);

	MATRIX_setItem(m, 1, 1, calculateSampleVariance(sampleX, meanX, size));
	MATRIX_setItem(m, 2, 2, calculateSampleVariance(sampleY, meanY, size));
	MATRIX_setItem(m, 3, 3, calculateSampleVariance(sampleZ, meanZ, size));

	double sampleCovarXY = calculateSampleCovariance(sampleX, sampleY, size, meanX, meanY);
	double sampleCovarXZ = calculateSampleCovariance(sampleX, sampleZ, size, meanX, meanZ);
	double sampleCovarYZ = calculateSampleCovariance(sampleY, sampleZ, size, meanY, meanZ);

	MATRIX_setItem(m, 1, 2, sampleCovarXY);
	MATRIX_setItem(m, 2, 1, sampleCovarXY);

	MATRIX_setItem(m, 1, 3, sampleCovarXZ);
	MATRIX_setItem(m, 3, 1, sampleCovarXZ);

	MATRIX_setItem(m, 2, 3, sampleCovarYZ);
	MATRIX_setItem(m, 3, 2, sampleCovarYZ);

	return m;
}

double calculateMean(int arr[], int size)
{
	double mean = 0;

	for(int i=0 ; i < size ; ++i)
		mean += arr[i];

	return mean / size;
}

double calculateSampleVariance(int sample[], double mean, int size)
{
	double total = 0;

	for(int i=0 ; i < size ; ++i)
		total += pow(sample[i] - mean, 2);

	return total / size;
}

double calculateSampleCovariance(int sample1[], int sample2[], int size, double sample1Mean, double sample2Mean)
{
	double total = 0;

	for(int i=0 ; i < size ; ++i)
		total += (sample1[i] - sample1Mean) * (sample2[i] - sample2Mean);

	return total / size;
}