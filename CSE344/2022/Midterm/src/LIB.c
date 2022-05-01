#include "LIB.h"

int x_open(const char* pathname, int flags, const char* message)
{
	int fd = -1;

	if((fd = open(pathname, flags)) == -1)
		x_exit(EXIT_FAILURE, message);

	return fd;
}

int x_mopen(const char* pathname, int flags, const char* message)
{
	int fd = 0;

	NO_EINTR(fd = open(pathname, flags));

	if(fd == -1)
		x_exit(EXIT_FAILURE, message);

	return fd;
}

int x_openm(const char* pathname, int flags, int mode, const char* message)
{
	int fd = 0;

	if((fd = open(pathname, flags, mode)) == -1)
		x_exit(EXIT_FAILURE, message);

	return fd;
}

int x_mopenm(const char* pathname, int flags, int mode, const char* message)
{
	int fd = 0;

	NO_EINTR(fd = open(pathname, flags, mode));

	if(fd == -1)
		x_exit(EXIT_FAILURE, message);

	return fd;
}

void x_close(int fd)
{
	int returnValue = 0;

	NO_EINTR(returnValue = close(fd));

	if(returnValue == -1)
		x_exit(EXIT_FAILURE, "x_close");
}

int x_write(int fd, const void* buf, size_t count)
{
	int returnValue = 0;

	NO_EINTR(returnValue = write(fd, buf, count));

	if(returnValue == -1)
		x_exit(EXIT_FAILURE, "x_write");

	return returnValue;
}

int x_pipe(int pipefd[2])
{
	int returnValue = 0;

	NO_EINTR(returnValue = pipe(pipefd));
		
	if(returnValue == -1)
		x_exit(EXIT_FAILURE, "x_pipe");

	return returnValue;
}

pid_t x_fork(void)
{
	pid_t returnValue = 0;

	NO_EINTR(returnValue = fork());

	if(returnValue == -1)
		x_exit(EXIT_FAILURE, "x_fork");

	return returnValue;
}

ssize_t x_read(int fd, void* buf, size_t count)
{
	int returnValue = 0;

	if(read(fd, buf, count) == -1)
		x_exit(EXIT_FAILURE, "x_read");

	return returnValue;
}

ssize_t x_mread(int fd, void* buf, size_t count)
{
	int returnValue = 0;

	NO_EINTR(returnValue = read(fd, buf, count));

	if(returnValue == -1)
		x_exit(EXIT_FAILURE, "x_mread");

	return returnValue;
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

void x_exit(int state, const char* message)
{
	perror(message);
	exit(state);
}

void x_atexit(void (*function)(void))
{
	if(atexit(function) != 0)
	{
		fprintf(stderr, "Cannot set exit function...\n");
		exit(EXIT_FAILURE);
	}
}

int x_shm_open(const char* name, int oflag, mode_t mode, int fd)
{
	int sharedMemFd = shm_open(name, oflag, mode);

	if(sharedMemFd == -1)
	{
		dprintf(fd, "ERROR! While opening shared memory file descriptor\n");
		exit(EXIT_FAILURE);
	}

	return sharedMemFd;
}

int x_mftruncate(int fd, off_t length)
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = ftruncate(fd, length));

	if(returnedValue == -1)
	{
		perror("x_ftruncate");
		exit(EXIT_FAILURE);
	}

	return returnedValue;
}

void* x_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset, int logFd)
{
	void* memAddr = mmap(addr, length, prot, flags, fd, offset);

	if(memAddr == MAP_FAILED)
	{
		dprintf(logFd, "Cannot be maped...\n");
		exit(EXIT_FAILURE);
	}

	return memAddr;
}

int x_msem_init(sem_t *sem, int pshared, unsigned int value, int fd)
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = sem_init(sem, pshared, value));

	if(returnedValue == -1)
	{
		dprintf(fd, "%s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return returnedValue;
}

int x_msem_destroy(sem_t *sem, int fd)
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = sem_destroy(sem));

	if(returnedValue == -1)
	{
		dprintf(fd, "%s", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return returnedValue;
}