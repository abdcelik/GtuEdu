#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Vector Vector;

/*
	Initializes a new vector with size 0
	Return NULL if an error occurs. Otherwise return created vector
*/
Vector* Vector_init();

/*
	Frees the given vector
	Uses given function adress for each vector's item to freeing item
*/
void Vector_free(Vector* vector, void (*freeVectorItem)(void*));

/*
	Adds the given item to the given vector
	If the size exceeds the capacity, the capacity is doubled
	Returns
		0 if adding operation is successful
		-1 if given vector is NULL
		-2 if vector size reach the UINT_MAX
		-3 if there is no enough memort
*/
int Vector_add(Vector* vector, void* item);

/*
	Removes item at given index from given vector
	Returns item at given index or NULL if given index is not correct
*/
void* Vector_remove(Vector* vector, int index);

/*
	Returns given vector's size or -1 if given vector is NULL
*/
int Vector_size(Vector* vector);

/*
	
*/
void* Vector_get(Vector* vector, int index);

/*
	Prints the given vector's item
	Uses given function adress for each vector's item to print item
*/
void Vector_print(Vector* vector, void (*printVectorItem)(void*));

#endif