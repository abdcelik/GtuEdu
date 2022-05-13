#include "LIB.h"

int xm_open(const char* pathname, int flags)
{
	int fd = 0;

	NO_EINTR(fd = open(pathname, flags));

	if(fd == -1)
		x_exit(EXIT_FAILURE, "xm_open");

	return fd;
}

void xm_close(int fd)
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = close(fd));

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_close");
}

ssize_t xm_read(int fd, void* buf, size_t count)
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = read(fd, buf, count));

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_read");

	return returnedValue;
}

void* x_calloc(size_t nmemb, size_t size)
{
	void* v = calloc(nmemb, size);

	if(!v)
		x_error(__func__, "Calloc could not allocate space properly");

	return v;
}

void x_atexit(void (*function)(void))
{
	if(atexit(function) != 0)
	{
		fprintf(stderr, "Cannot set exit function...\n");
		exit(EXIT_FAILURE);
	}
}

int x_setvbuf(FILE* stream, char* buf, int mode, size_t size)
{
	int returnedValue = setvbuf(stream, buf, mode, size);

	if(returnedValue != 0)
		x_exit(EXIT_FAILURE, "x_setvbuf");

	return returnedValue;
}

time_t x_time(time_t* tloc)
{
	time_t returnedValue = time(tloc);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_time");

	return returnedValue;
}

int x_pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (*start_routine)(void*), void* arg)
{
	int returnedValue = pthread_create(thread, attr, start_routine, arg);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));
	
	return returnedValue;
}

int x_pthread_detach(pthread_t thread)
{
	int returnedValue = pthread_detach(thread);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));
	
	return returnedValue;
}

int x_pthread_join(pthread_t thread, void** retval)
{
	int returnedValue = pthread_join(thread, retval);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));
	
	return returnedValue;
}

int x_semget(key_t key, int nsems, int semflg)
{
	int returnedValue = semget(key, nsems, semflg);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_semget");

	return returnedValue;
}

int x_semop(int semid, struct sembuf* sops, size_t nsops)
{
	int returnedValue = semop(semid, sops, nsops);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_semop");

	return returnedValue;
}

int x_semctl(int semid, int semnum, int cmd)
{
	int returnedValue = semctl(semid, semnum, cmd);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_semctl");

	return returnedValue;
}

void x_error(const char* f, char *msg)
{
	fprintf(stderr, "Error, %s: %s with [errno:%s]\n", f, msg, strerror(errno));
	exit(EXIT_FAILURE);
}

void x_exit(int state, const char* message)
{
	perror(message);
	exit(state);
}