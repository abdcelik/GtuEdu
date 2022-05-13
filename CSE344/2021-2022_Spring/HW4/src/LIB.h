#ifndef _LIB_H_
#define _LIB_H_

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NO_EINTR(stmt) while((stmt) == -1 && errno == EINTR)

/*
	Opens file with syscall open with given parameters
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int xm_open(const char* pathname, int flags);

/*
	Closes given file with syscall close
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
void xm_close(int fd);

/*
	xm_read() attempts to read up to count bytes from file descriptor fd into
		the buffer starting at buf
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
ssize_t xm_read(int fd, void* buf, size_t count);

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

/*
	Prints given message using perror function and exit given state
*/
void x_exit(int state, const char* message);

/*
	x_atexit() function registers the given function to be called at normal process
		termination, either via exit or via return from the  program's  main() 
*/
void x_atexit(void (*function)(void));

/*	If the error occurs, calls perror function and terminates program with EXIT_FAILURE	*/
int x_setvbuf(FILE* stream, char* buf, int mode, size_t size);

/*
	Returns the time as the number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
time_t x_time(time_t* tloc);

/*
	The x_pthread_create() function starts a new thread in the calling process
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg);

/*
	The x_pthread_detach() function marks the thread identified by thread as detached
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_detach(pthread_t thread);

/*
	The x_pthread_join() function waits for the thread specified by thread to terminate
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_join(pthread_t thread, void** retval);

/*
	The x_semget() system call returns the System V semaphore set identifier associated with the argument key
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_semget(key_t key, int nsems, int semflg);

/*
	x_semop() performs operations on selected semaphores in the set indicated by semid
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_semop(int semid, struct sembuf* sops, size_t nsops);

/*
	x_semctl() performs the control operation specified by cmd on the System V semaphore set identified by semid,
		or on the semnum-th semaphore of that set
	If the error occurs, prints error and terminates program with EXIT_FAILURE	
*/
int x_semctl(int semid, int semnum, int cmd);

#endif