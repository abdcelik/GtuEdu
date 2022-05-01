#include "LIB.h"

int x_open(const char* pathname, int flags)
{
	int fd = 0;

	NO_EINTR(fd = open(pathname, flags));

	if(fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	return fd;
}

int x_openm(const char* pathname, int flags, int mode)
{
	int fd = 0;

	NO_EINTR(fd = open(pathname, flags, mode));

	if(fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	return fd;
}

void x_close(int fd)
{
	int r = 0;

	NO_EINTR(r = close(fd));

	if(r == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

int x_write(int fd, const void* buf, size_t count)
{
	int r = 0;

	NO_EINTR(r = write(fd, buf, count));

	if(r == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}

	return r;
}

void* x_malloc(size_t size)
{
	void* v = malloc(size);

	if(!v)
		x_error(__func__, "Malloc could not allocate space properly");

	return v;
}

void* x_calloc(size_t nmemb, size_t size)
{
	void* v = calloc(nmemb, size);

	if(!v)
		x_error(__func__, "Calloc could not allocate space properly");

	return v;
}

void* x_realloc(void* ptr, size_t size)
{
	ptr = realloc(ptr, size);

	if(!ptr)
		x_error(__func__, "Realloc could not allocate space properly");

	return ptr;
}

void x_error(const char* f, char *msg)
{
	fprintf(stderr, "Error, %s: %s with [errno:%s]\n", f, msg, strerror(errno));
	exit(EXIT_FAILURE);
}