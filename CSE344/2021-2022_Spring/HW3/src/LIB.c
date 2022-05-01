#include "LIB.h"

int x_open(const char* pathname, int flags)
{
	int fd = -1;

	if((fd = open(pathname, flags)) == -1)
		x_exit(EXIT_FAILURE, "x_open");

	return fd;
}

int xm_open(const char* pathname, int flags)
{
	int fd = 0;

	NO_EINTR(fd = open(pathname, flags));

	if(fd == -1)
		x_exit(EXIT_FAILURE, "xm_open");

	return fd;
}

int x_openm(const char* pathname, int flags, int mode)
{
	int fd = 0;

	if((fd = open(pathname, flags, mode)) == -1)
		x_exit(EXIT_FAILURE, "x_openm");

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

int xm_write(int fd, const void* buf, size_t count)
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = write(fd, buf, count));

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_write");

	return returnedValue;
}

int xm_pipe(int pipefd[2])
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = pipe(pipefd));
		
	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_pipe");

	return returnedValue;
}

pid_t xm_fork(void)
{
	pid_t returnedValue = 0;

	NO_EINTR(returnedValue = fork());

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_fork");

	return returnedValue;
}

int x_kill(pid_t pid, int sig)
{
	int returnedValue = kill(pid, sig);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_kill");

	return returnedValue;
}

pid_t xm_wait(int* status)
{
	pid_t returnedValue = 0;

	NO_EINTR(returnedValue = wait(status));

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_wait");

	return returnedValue;
}

pid_t xm_waitpid(pid_t pid, int* status, int options)
{
	pid_t returnedValue = 0;

	NO_EINTR(returnedValue = waitpid(pid, status, options));

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_waitpid");

	return returnedValue;
}

ssize_t x_read(int fd, void* buf, size_t count)
{
	int returnedValue = 0;

	if(read(fd, buf, count) == -1)
		x_exit(EXIT_FAILURE, "x_read");

	return returnedValue;
}

ssize_t xm_read(int fd, void* buf, size_t count)
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = read(fd, buf, count));

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_read");

	return returnedValue;
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

void x_atexit(void (*function)(void))
{
	if(atexit(function) != 0)
	{
		fprintf(stderr, "Cannot set exit function...\n");
		exit(EXIT_FAILURE);
	}
}

int x_shm_open(const char* name, int oflag, mode_t mode)
{
	int sharedMemFd = shm_open(name, oflag, mode);

	if(sharedMemFd == -1)
	{
		fprintf(stderr, "ERROR! While opening shared memory file descriptor\n");
		exit(EXIT_FAILURE);
	}

	return sharedMemFd;
}

int x_shm_unlink(const char* name)
{
	int returnedValue = shm_unlink(name);

	if(returnedValue == -1)
	{
		fprintf(stderr, "ERROR! While unlinking shared memory file\n");
		exit(EXIT_FAILURE);
	}

	return returnedValue;
}

int xm_ftruncate(int fd, off_t length)
{
	int returnedValue = 0;

	NO_EINTR(returnedValue = ftruncate(fd, length));

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "xm_ftruncate");

	return returnedValue;
}

void* x_mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	void* memAddr = mmap(addr, length, prot, flags, fd, offset);

	if(memAddr == MAP_FAILED)
		x_exit(EXIT_FAILURE, "x_mmap");

	return memAddr;
}

int x_munmap(void* addr, size_t length)
{
	int returnedValue = munmap(addr, length);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_munmap");

	return returnedValue;
}

int x_sem_init(sem_t* sem, int pshared, unsigned int value)
{
	int returnedValue = sem_init(sem, pshared, value);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_sem_init");

	return returnedValue;
}

sem_t* x_sem_open(const char* name, int oflag, mode_t mode, unsigned int value)
{
	sem_t* sem = sem_open(name, oflag, mode, value);

	if(sem == SEM_FAILED)
		x_exit(EXIT_FAILURE, "x_sem_open");

	return sem;
}

int x_sem_wait(sem_t *sem)
{
	int returnedValue = sem_wait(sem);

	if(returnedValue == -1 && errno != EINTR)
		x_exit(EXIT_FAILURE, "x_sem_wait");

	return returnedValue;
}

int x_sem_post(sem_t *sem)
{
	int returnedValue = sem_post(sem);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_sem_post");

	return returnedValue;
}

int x_sem_destroy(sem_t* sem)
{
	int returnedValue = sem_destroy(sem);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_sem_destroy");

	return returnedValue;
}

int x_sem_close(sem_t* sem)
{
	int returnedValue = sem_close(sem);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_sem_close");

	return returnedValue;
}

int x_sem_unlink(const char* name)
{
	int returnedValue = sem_unlink(name);

	if(returnedValue == -1)
		x_exit(EXIT_FAILURE, "x_sem_unlink");

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