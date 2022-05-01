#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*
	Allocates size bytes and returns a pointer to the allocated memory
	If there is out of memory, program exit with error message
*/
void* x_malloc(size_t size);

/*
	Allocates memory for an array of given nmemb elements of given size and returns a pointer to the allocated memory
	The memory is set 0
	If there is out of memory, program exit with error message
*/
void* x_calloc(size_t nmemb, size_t size);

/*
	Prints error message and exit
	Paremeter f for function name, parameter msg for usefull message
*/
void x_error(const char* f, char* msg);

#endif