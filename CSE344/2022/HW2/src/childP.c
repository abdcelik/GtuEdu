#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "MATRIX.h"
#include "FILE.h"

extern char** environ;
sig_atomic_t sigint_count = 0;

void SIGINT_handler(int signal_number)
{
	++sigint_count;
}

int main(int argc, char* argv[])
{
	struct sigaction sa;
	int sigactreturn = 0;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &SIGINT_handler;

	if(sigfillset(&sa.sa_mask) == -1 || sigdelset(&sa.sa_mask, SIGINT) == -1)
	{
		perror("sigset");
		exit(EXIT_FAILURE);
	}

	NO_EINTR(sigactreturn = sigaction(SIGINT, &sa, NULL));

	if(sigactreturn == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	MATRIX* matrix = calcuateCovarianceMatrix(environ);

	if(sigint_count)
	{
		MATRIX_free(matrix);
		kill(getppid(), SIGINT);
		exit(EXIT_FAILURE);
	}

	if(!matrix)
	{
		fprintf(stderr, "ERROR! Convariance matrix cannot build!\n");
		exit(EXIT_FAILURE);
	}

	int fd = x_openm(argv[1], O_RDWR | O_APPEND | O_CREAT, 0666);
	struct flock lock;

	lockFile(&lock, fd, F_WRLCK, F_SETLKW);
	writeFile(fd, matrix);

	if(sigint_count)
	{
		MATRIX_free(matrix);
		kill(getppid(), SIGINT);
		x_close(fd);
		exit(EXIT_FAILURE);
	}

	lockFile(&lock, fd, F_UNLCK, F_SETLKW);
	x_close(fd);

	MATRIX_free(matrix);
	exit(EXIT_SUCCESS);
}