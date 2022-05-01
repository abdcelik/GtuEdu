#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "VECTOR.h"
#include "RULE.h"

// Global lock variable
extern struct flock _FILE_lock;

/*
	Opens file with syscall open with given parameters
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int openFile(const char* pathName, int flags);

/*
	Closes given file with syscall close
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
void closeFile(int fd);

/*
	Sets own global lock variable with given parameters
	Then syscall fcntl with given file descriptor and checks returned value
	If there is an error call perror function and terminates program with EXIT_FAILURE
*/
void lockFile(int fd, short l_type, int cmd);

/*
	Reads file from given fromfd, applies rules then writes to file from given tofd
	It performs all operation with syscall(read, write)
	If there is an error call perror function and terminates program with EXIT_FAILURE
*/
void applyRule(int fromfd, int tofd, VECTOR* rule);

/*
	Sets the offset of the given file descriptors to 0 with lseek syscall
	Reads from srcFd with read syscall and writes targetFd with write syscall
	If there is an error call perror function and terminates program with EXIT_FAILURE
*/
void copyFile(int targetFd, int srcFd);

/*
	Causes referenced by fd to be truncated to a size of precisely length bytes
	If there is an error call perror function and terminates program with EXIT_FAILURE
*/
void ftruncateFile(int fd, off_t length);

/*
	Opens temp file with mkstemp syscall
	Unlinks temp file with unlink syscall
	Returns file descriptor
	If there is an error call perror function and terminates program with EXIT_FAILURE
*/
int openTempFile();

#endif