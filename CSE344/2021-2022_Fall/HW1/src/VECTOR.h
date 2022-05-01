#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "LIB.h"

/* Generic vector */
struct VECTOR
{
	void** item;
	unsigned int size;
	unsigned int capacity;
};

typedef struct VECTOR VECTOR;

/*	
	Initializes the vector with size 0 
	If an error occurs, prints an error message to stderr and terminates program. Otherwise returns VECTOR*
*/
VECTOR* VECTOR_init();

/*
	Adds the item to the vector. If the size exceeds the capacity, the capacity is doubled
	If an error occurs, prints an error message to stderr and return -1. Otherwise returns 0
*/
int VECTOR_add(VECTOR*, void*);

/*	Returns size of the given vector if there is a vector. Otherwise returns -1	*/
int VECTOR_size(VECTOR*);

/*
	Prints the given vector's item
	It must know that how to print an item. Therefore it takes function address for printing an item
*/
void VECTOR_print(VECTOR*, void (*f)(void*));

/* For print a string */
void VECTOR_print_str(void*);

/*
	Releases a vector
	It must know that how to free an item. Therefore it takes function address for freeing an item
*/
void VECTOR_free(VECTOR*, void (*f)(void*));

/* For free a string space */
void VECTOR_free_str(void*);

#endif