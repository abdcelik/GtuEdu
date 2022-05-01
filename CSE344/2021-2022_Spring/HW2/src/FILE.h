#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "MATRIX.h"
#include "STRING.h"

/*
	Sets own global lock variable with given parameters
	Then syscall fcntl with given file descriptor and checks returned value
	If there is an error call perror function and terminates program with EXIT_FAILURE
*/
void lockFile(struct flock* lock, int fd, short l_type, int cmd);

/*
	Writes given matrix to given file descriptor
	If there is an error call perror function and terminates program with EXIT_FAILURE
*/
void writeFile(int fd, MATRIX* m);

#endif