#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <float.h>
#include "BASIS.h"
#include "FILE.h"
#include "VECTOR.h"

sig_atomic_t sigint_count = 0;
VECTOR* child = NULL;

void SIGINT_handler(int signal_number)
{
	++sigint_count;
}

void notifyAndTerminate()
{
	if(child)
	{
		for(int i=0 ; i < child->size ; ++i)
			kill(*(int*)child->item[i], SIGINT);
		VECTOR_free(child, free);
	}
}

void readAndCreateProcess(int fd);
void readAndCalculateFinal(int fd);

int main(int argc, char* argv[])
{
	atexit(notifyAndTerminate);

	if(setArguments(argc, argv))
	{
		printArgumentError();
		exit(EXIT_FAILURE);
	}

	child = VECTOR_init();
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

	if(sigint_count)
		exit(EXIT_FAILURE);

	struct flock lock;
	int fd = x_open(ARG_INPUT, O_RDONLY);
	x_close(x_openm(ARG_OUTPUT, O_WRONLY | O_CREAT | O_TRUNC, 0666));	// Create and clean output file

	lockFile(&lock, fd, F_RDLCK, F_SETLKW);
	readAndCreateProcess(fd);
	lockFile(&lock, fd, F_UNLCK, F_SETLKW);
	x_close(fd);

	if(sigint_count)
		exit(EXIT_FAILURE);

	while(wait(NULL) != -1);

	if(errno != ECHILD)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}

	if(sigint_count)
		exit(EXIT_FAILURE);

	fd = x_open(ARG_OUTPUT, O_RDONLY);

	lockFile(&lock, fd, F_RDLCK, F_SETLKW);
	readAndCalculateFinal(fd);
	lockFile(&lock, fd, F_UNLCK, F_SETLKW);
	x_close(fd);

	return 0;
}

void readAndCreateProcess(int fd)
{
	int bufferSize = 3, envSize = 10;
	char buffer[bufferSize + 1];
	char* env[envSize + 1];

	memset(buffer, 0, sizeof(buffer));
	memset(env, 0, sizeof(env));
	fprintf(stdout, "Process P reading %s\n", ARG_INPUT);

	for(int i=0, bytes_read = 0 ;; ++i)
	{
		if(sigint_count)
		{
			for(int i=0 ; i < envSize; ++i)
				if(env[i])
					free(env[i]);
			exit(EXIT_FAILURE);
		}

		NO_EINTR(bytes_read = read(fd, buffer, bufferSize));

		if(bytes_read == -1)		{ perror("read"); exit(EXIT_FAILURE); }
		if(bytes_read < bufferSize)	{ fprintf(stdout, "Reached EOF, collecting outputs from %s\n", ARG_OUTPUT); break;}

		STRING* str = STRING_build(16);

		STRING_addChar(str, '(');
		for(int j=0 ; j < bufferSize ; ++j)
		{
			STRING_addInt(str, (int)buffer[j]);
			if(j == bufferSize - 1)	STRING_addChar(str, ')');
			else					STRING_addChar(str, ',');
		}

		int tmpi = i % envSize;

		env[tmpi] = x_calloc(STRING_length(str) + 1, sizeof(char));
		strcpy(env[tmpi], STRING_getCharArr(str));

		if((i+1) % envSize == 0)
		{
			printEnvironmentVariables(env, (i + 1) / envSize);
			fflush(stdout);
			int pid = fork();

			switch(pid)
			{
				case -1:
					perror("fork");
					exit(EXIT_FAILURE);
				case 0:
					execve(CHLD_PROCESS_EXEC, ChildArgv, env);
					fprintf(stderr, "ERROR! execve...\n");
			}

			int* tmp = x_malloc(sizeof(int));
			*tmp = pid;
			VECTOR_add(child, tmp);

			for(int j=0 ; j < envSize ; ++j)
			{
				free(env[j]);
				env[j] = NULL;
			}
		}

		STRING_free(str);
	}

	for(int i=0 ; i < envSize; ++i)
		if(env[i])
			free(env[i]);
}

void readAndCalculateFinal(int fd)
{
	VECTOR* matrices = VECTOR_init();

	for(int loopexit = 0; !loopexit ;)
	{
		if(sigint_count)
		{
			VECTOR_free(matrices, MATRIX_free);
			exit(EXIT_FAILURE);
		}

		STRING* str = STRING_build(16);
		char buffer = 0;

		for(int bytes_read = 0;;)
		{
			NO_EINTR(bytes_read = read(fd, &buffer, sizeof(char)));

			if(bytes_read == -1)	{ perror("read"); exit(EXIT_FAILURE); }
			if(bytes_read ==  0)	{ loopexit = 1; break; };

			if(buffer == '\n')
			{
				VECTOR_add(matrices, MATRIX_buildWithString(STRING_getCharArr(str)));
				break;
			}
			else
				STRING_addChar(str, buffer);
		}

		STRING_free(str);
	}

	if(matrices->size < 2)
	{
		fprintf(stdout, "There are only one matrix. Closest matrix could not calculated...\n");
		return;
	}

	MATRIX* s1 = NULL, *s2 = NULL;
	double closest = DBL_MAX;

	for(int i=0 ; i < matrices->size ; ++i)
	{
		MATRIX* curr = matrices->item[i];
		double currNorm = calculateFrobeniusNorm(curr);

		for(int j=i+1 ; j < matrices->size ; ++j)
		{
			MATRIX* other = matrices->item[j];
			double otherNorm = calculateFrobeniusNorm(other);

			if(fabs(currNorm - otherNorm) < closest)
			{
				s1 = curr;
				s2 = other;
				closest = fabs(currNorm - otherNorm);
			}
		}
	}

	STRING* matrixstr1 = MATRIX_toString(s1);
	STRING* matrixstr2 = MATRIX_toString(s2);

	fprintf(stdout, "The closest 2 matrices are %s and %s, and their distance is %.3lf\n", STRING_getCharArr(matrixstr1), STRING_getCharArr(matrixstr2), closest);

	VECTOR_free(matrices, MATRIX_free);
	STRING_free(matrixstr1);
	STRING_free(matrixstr2);
}