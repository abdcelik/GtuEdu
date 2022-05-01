#ifndef _LIB_H_
#define _LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#define NO_EINTR(stmt) while((stmt) == -1 && errno == EINTR)

/*
	Opens file with syscall open with given parameters
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int x_open(const char* pathname, int flags, const char* message);

/*
	Opens file with syscall open with given parameters
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int x_mopen(const char* pathname, int flags, const char* message);

/*
	Opens file with syscall open with given parameters
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int x_openm(const char* pathname, int flags, int mode, const char* message);

/*
	Opens file with syscall open with given parameters
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int x_mopenm(const char* pathname, int flags, int mode, const char* message);

/*
	Closes given file with syscall close
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
void x_close(int fd);

/*
	x_write() writes up to count bytes from the buffer pointed buf to the
		file referred to by the file descriptor fd.
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_write(int fd, const void* buf, size_t count);

/*
	x_pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_pipe(int pipefd[2]);

/*
	x_fork() creates a new process by duplicating the calling process
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
pid_t x_fork(void);

/*
	x_read() attempts to read up to count bytes from file descriptor fd into
		the buffer starting at buf
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
ssize_t x_read(int fd, void* buf, size_t count);

/*
	x_mread() attempts to read up to count bytes from file descriptor fd into
		the buffer starting at buf
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
ssize_t x_mread(int fd, void* buf, size_t count);

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

/*
	Prints given message using perror function and exit given state
*/
void x_exit(int state, const char* message);

/*
	x_atexit() function registers the given function to be called at normal process
		termination, either via exit or via return from the  program's  main() 
*/
void x_atexit(void (*function)(void));

/*
	shm_open()  creates  and  opens  a  new,  or opens an existing, POSIX shared memory object
	If the error occurs, writes given log file descriptor and terminates program with EXIT_FAILURE
*/
int x_shm_open(const char* name, int oflag, mode_t mode, int fd);

/*
	The ftruncate() functions cause the referenced by fd to
		be truncated to a size of precisely length bytes
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_mftruncate(int fd, off_t length);

/*
	The mmap() creates a new mapping in the virtual address space of the calling process
	If the error occurs, writes given log file descriptor and terminates program with EXIT_FAILURE
*/
void* x_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset, int logFd);

/*
	sem_init() initializes the unnamed semaphore at the address pointed to by sem
		The value argument specifies the initial value for the semaphore
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_msem_init(sem_t *sem, int pshared, unsigned int value, int fd);

/*
	sem_destroy() destroys the unnamed semaphore at the address pointed to by sem
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_msem_destroy(sem_t *sem, int fd);

#endif