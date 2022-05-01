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
#include <sys/wait.h>
#include <semaphore.h>

#define NO_EINTR(stmt) while((stmt) == -1 && errno == EINTR)

#define READ_END 0
#define WRITE_END 1

/*
	Opens file with syscall open with given parameters
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int x_open(const char* pathname, int flags);

/*
	Opens file with syscall open with given parameters
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int xm_open(const char* pathname, int flags);

/*
	Opens file with syscall open with given parameters
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int x_openm(const char* pathname, int flags, int mode);

/*
	Opens file with syscall open with given parameters
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int xm_openm(const char* pathname, int flags, int mode);

/*
	Closes given file with syscall close
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
void xm_close(int fd);

/*
	xm_write() writes up to count bytes from the buffer pointed buf to the
		file referred to by the file descriptor fd.
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int xm_write(int fd, const void* buf, size_t count);

/*
	xm_pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int xm_pipe(int pipefd[2]);

/*
	xm_fork() creates a new process by duplicating the calling process
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
pid_t xm_fork(void);

/*
	The x_kill() system call can be used to send any signal to any process group or process
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_kill(pid_t pid, int sig);

/*
	Wait for state changes in a child of the calling process, and
		obtain information about the child whose state has changed
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
pid_t xm_wait(int* status);

/*
	The xm_waitpid() system call suspends execution of the calling process
		until a child specified by pid argument has changed state
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
pid_t xm_waitpid(pid_t pid, int* status, int options);

/*
	x_read() attempts to read up to count bytes from file descriptor fd into
		the buffer starting at buf
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
ssize_t x_read(int fd, void* buf, size_t count);

/*
	xm_read() attempts to read up to count bytes from file descriptor fd into
		the buffer starting at buf
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
ssize_t xm_read(int fd, void* buf, size_t count);

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
	x_shm_open() creates and opens a new, or opens an existing, POSIX shared memory object
	If the error occurs, writes stderr and terminates program with EXIT_FAILURE
*/
int x_shm_open(const char* name, int oflag, mode_t mode);

/*
	The shm_unlink() function performs the converse operation, removing
       an object previously created by shm_open()
	If the error occurs, writes stderr and terminates program with EXIT_FAILURE
*/
int x_shm_unlink(const char* name);

/*
	The xm_ftruncate() functions cause the referenced by fd to
		be truncated to a size of precisely length bytes
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int xm_ftruncate(int fd, off_t length);

/*
	The x_mmap() creates a new mapping in the virtual address space of the calling process
	If the error occurs, writes stderr and terminates program with EXIT_FAILURE
*/
void* x_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset);

/*
	The x_munmap() system call deletes the mappings for the specified address range, and causes further
		references to addresses within the range to generate invalid memory references
*/
int x_munmap(void* addr, size_t length);

/*
	xmsem_init() initializes the unnamed semaphore at the address pointed to by sem
		The value argument specifies the initial value for the semaphore
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_sem_init(sem_t* sem, int pshared, unsigned int value);

/*
	x_sem_open() creates a new POSIX semaphore or opens an existing semaphore
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
sem_t* x_sem_open(const char* name, int oflag, mode_t mode, unsigned int value);

/*
	x_sem_wait() decrements (locks) the semaphore pointed to by sem
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_sem_wait(sem_t *sem);

/*
	xm_sem_post() increments (unlocks) the semaphore pointed to by sem
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_sem_post(sem_t *sem);

/*
	x_sem_destroy() destroys the unnamed semaphore at the address pointed to by sem
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_sem_destroy(sem_t* sem);

/*
	x_sem_close() closes the named semaphore referred to by sem, allowing any resources that the system
		has allocated to the calling process for this semaphore to be freed.
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_sem_close(sem_t* sem);

/*
	x_sem_unlink() removes the named semaphore referred to by name
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_sem_unlink(const char* name);

#endif