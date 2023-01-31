#ifndef _LIB_H_
#define _LIB_H_

#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

#define NO_EINTR(stmt) while((stmt) == -1 && errno == EINTR)

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
	x_sigfillset() initializes set to full, including all signals
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_sigfillset(sigset_t* set);

/*
	The xm_sigaction() system call is used to change the action taken by a process on receipt of a specific signal
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

/*
	Opens file with syscall open with given parameters
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE. Otherwise returns file descriptor
*/
int xm_open(const char* pathname, int flags);

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
	x_read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf
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
	x_write() writes up to count bytes from the buffer pointed buf to the
		file referred to by the file descriptor fd.
	Doesn't allow failing system call with ENITR
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int xm_write(int fd, const void* buf, size_t count);

/*
	Allocates memory for an array of given nmemb elements of given size and returns a pointer to the allocated memory
	The memory is set 0
	If there is out of memory, program exit with error message
*/
void* x_calloc(size_t nmemb, size_t size);

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
	x_kill() system call can be used to send any signal to any process group or process
	If the error occurs, calls perror function and terminates program with EXIT_FAILURE
*/
int x_kill(pid_t pid, int sig);

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
	The x_pthread_cancel() function sends a cancellation request to the thread
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_cancel(pthread_t thread);

/*
	The x_pthread_mutex_init() function shall initialize the mutex referenced by mutex with attributes specified by attr
	If the error occurs, prints error and terminates program with EXIT_FAILURE	
*/
int x_pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);

/*
	The x_pthread_mutex_destroy() function shall destroy the mutex object referenced by mutex
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_mutex_destroy(pthread_mutex_t *mutex);

/*
	The x_pthread_cond_init() function shall initialize the condition variable referenced by cond with attributes referenced by attr
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);

/*
	The x_pthread_cond_destroy() function shall destroy the given condition variable specified by cond
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_cond_destroy(pthread_cond_t *cond);

/*
	The mutex object referenced by mutex shall be locked by a call to x_pthread_mutex_lock()
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_mutex_lock(pthread_mutex_t *mutex);

/*
	The x_pthread_mutex_unlock() function shall release the mutex object referenced by mutex
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_mutex_unlock(pthread_mutex_t *mutex);

/*
	x_pthread_cond_wait() functions shall block on a condition variable
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex);

/*
	The x_pthread_cond_broadcast() function shall unblock all threads currently blocked on the specified condition variable cond
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_pthread_cond_broadcast(pthread_cond_t* cond);

/*
	x_readlink() places the contents of the symbolic link pathname in the buffer buf, which has size bufsiz
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
ssize_t x_readlink(const char* pathname, char* buf, size_t bufsiz);

/*
	x_socket() creates an endpoint for communication and returns a descriptor
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_socket(int domain, int type, int protocol);

/*
	x_inet_pton converts the character string src into a network address structure 
		in the af address family, then  copies  the  network  address structure to dst
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_inet_pton(int af, const char* src, void* dst);

/*
	x_bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/*
	x_listen() marks the socket referred to by sockfd as a passive socket, that is,
		as a socket that will be used to  accept  incoming  connection requests using accept(2)
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_listen(int sockfd, int backlog);

/*
	x_connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/*
	The x_accept() system call is used with connection-based socket types (SOCK_STREAM, SOCK_SEQPACKET)
		It extracts the first connection request on the queue of pending connections for the listening socket,
		sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.
		The newly created socket is not in the listening state. The original socket sockfd is unaffected by this call
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/*
	x_setsockopt() manipulate options for the socket referred to by the file descriptor sockfd
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

/*
	The x_opendir() function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
DIR* x_opendir(const char* name);

/*
	The x_closedir() function closes the directory stream associated with dirp
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_closedir(DIR* dirp);

/*
	The x_scandir() function scans the directory dirp, calling filter() on each directory entry
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
int x_scandir(const char* dirp, struct dirent*** namelist, int (*filter)(const struct dirent*), int (*compar)(const struct dirent**, const struct dirent**));

/*
	The x_readdir() function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp
	If the error occurs, prints error and terminates program with EXIT_FAILURE
*/
struct dirent* x_readdir(DIR* dirp);

#endif