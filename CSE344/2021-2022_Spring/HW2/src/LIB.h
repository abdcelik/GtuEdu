#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "VECTOR.h"

#define NO_EINTR(stmt) while((stmt) == -1 && errno == EINTR);

/*
	Opens file with syscall open with given parameters
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int x_open(const char* pathname, int flags);

/*
	Opens file with syscall open with given parameters
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int x_openm(const char* pathname, int flags, int mode);

/*
	Closes given file with syscall close
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
void x_close(int fd);

/*
	write() writes up to count bytes from the buffer pointed buf to the
       file referred to by the file descriptor fd.
    Doesn't allow failing system call with ENITR
    If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_write(int fd, const void* buf, size_t count);

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
	The realloc() function changes the size of the memory block pointed to
	by ptr to size bytes. The contents will be unchanged in the range from
	the start of the region up to the minimum of the old and new sizes
	If there is out of memory, program exit with error message
*/
void* x_realloc(void* ptr, size_t size);

/*
	Prints error message and exit
	Paremeter f for function name, parameter msg for usefull message
*/
void x_error(const char* f, char* msg);

#endif