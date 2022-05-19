#include "LIB.h"

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

int x_sigfillset(sigset_t* set)
{
	int returnedValue = sigfillset(set);

	if(returnedValue != 0)
		x_exit(EXIT_FAILURE, "x_sigfillset");

	return returnedValue;
}

int x_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
{
	int returnedValue = sigaction(signum, act, oldact);

	if(returnedValue != 0)
		x_exit(EXIT_FAILURE, "x_sigaction");

	return returnedValue;
}

int xm_open(const char* pathname, int flags)
{
	int fd = 0;

	NO_EINTR(fd = open(pathname, flags));

	if(fd == -1)
		x_exit(EXIT_FAILURE, "xm_open");

	return fd;
}

int xm_openm(const char* pathname, int flags, int mode)
{
	int fd = 0;

	NO_EINTR(fd = open(pathname, flags, mode));

	if(fd == -1)
		x_exit(EXIT_FAILURE, "xm_openm");

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

int xm_write(int fd, const void* buf, size_t count)
{
	int returnValue = 0;

	NO_EINTR(returnValue = write(fd, buf, count));

	if(returnValue == -1)
		x_exit(EXIT_FAILURE, "xm_write");

	return returnValue;
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

int x_pthread_join(pthread_t thread, void** retval)
{
	int returnedValue = pthread_join(thread, retval);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));
	
	return returnedValue;
}

int x_pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)
{
	int returnedValue = pthread_mutex_init(mutex, attr);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));

	return returnedValue;
}

int x_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	int returnedValue = pthread_mutex_destroy(mutex);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));

	return returnedValue;
}

int x_pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr)
{
	int returnedValue = pthread_cond_init(cond, attr);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));

	return returnedValue;
}

int x_pthread_cond_destroy(pthread_cond_t *cond)
{
	int returnedValue = pthread_cond_destroy(cond);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));

	return returnedValue;
}

int x_pthread_mutex_lock(pthread_mutex_t *mutex)
{
	int returnedValue = pthread_mutex_lock(mutex);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));

	return returnedValue;
}

int x_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	int returnedValue = pthread_mutex_unlock(mutex);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));

	return returnedValue;
}

int x_pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex)
{
	int returnedValue = pthread_cond_wait(cond, mutex);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));

	return returnedValue;
}

int x_pthread_cond_broadcast(pthread_cond_t* cond)
{
	int returnedValue = pthread_cond_broadcast(cond);

	if(returnedValue != 0)
		x_error(__func__, strerror(returnedValue));

	return returnedValue;
}