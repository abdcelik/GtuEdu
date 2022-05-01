#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define NUM_OF_CHILD 8
#define NUM_OF_COORDINATE 8

sig_atomic_t SIGINT_val = 0, SIGUSR_val = 0;

void SIGINT_Handler(int sig_num) { SIGINT_val = sig_num; }
void SIGUSR_Handler(int sig_num) { SIGUSR_val = sig_num; }
void setSA(struct sigaction*, void (*handler)(int), int);

void childFirstRound(FILE*, int);
void childSecondRound(FILE*, int);
void parentFirstRound(FILE*);
void parentSecondRound(FILE*);
void parentRound(FILE*, int);

void lockFile(FILE*, struct flock*, int);
void unlockFile(FILE*, struct flock*);

float lagrange(float[][2], int, float);
void printCoefficient(float[][2], int);
void printValue(FILE*, float);
void fswap(FILE*, long int, long int);
int digit(int);

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Error! Program must be called \"./programName pathToFile\".\n");
		exit(EXIT_FAILURE);
	}

	FILE* fp;

	if(!(fp = fopen(argv[1], "r+")))
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	pid_t child[NUM_OF_CHILD];
	struct sigaction SIGINTAct, SIGUSR1Act, SIGUSR2Act;
	sigset_t sigBlock, sigChld;

	setSA(&SIGINTAct, SIGINT_Handler, SIGINT);
	setSA(&SIGUSR1Act, SIGUSR_Handler, SIGUSR1);
	setSA(&SIGUSR2Act, SIGUSR_Handler, SIGUSR2);

	if(sigemptyset(&sigBlock) || sigemptyset(&sigChld))
	{
		perror("sigemptyset");
		exit(EXIT_FAILURE);
	}

	if(sigfillset(&sigBlock) || sigfillset(&sigChld))
	{
		perror("sigfillset");
		exit(EXIT_FAILURE);
	}
	
	if(sigdelset(&sigChld, SIGINT) || sigdelset(&sigChld, SIGUSR1) || sigdelset(&sigChld, SIGUSR2))
	{
		perror("sigdelset");
		exit(EXIT_FAILURE);
	}

	if(sigprocmask(SIG_BLOCK, &sigBlock, NULL))
	{
		perror("sigprocmask");
		exit(EXIT_FAILURE);
	}

	for(int i=0 ; i < NUM_OF_CHILD ; ++i)
		switch(child[i] = fork())
		{
			case -1:
				perror("fork");
				exit(EXIT_FAILURE);

			case 0:
				childFirstRound(fp, i);

				if(sigsuspend(&sigChld) && errno == EFAULT)
				{
					perror("sigsuspend");
					exit(EXIT_FAILURE);
				}

				if(kill(getppid(), SIGUSR1))
				{
					perror("kill");
					exit(EXIT_FAILURE);
				}

				if(sigsuspend(&sigChld) && errno == EFAULT)
				{
					perror("sigsuspend");
					exit(EXIT_FAILURE);
				}

				childSecondRound(fp, i);
				exit(EXIT_SUCCESS);

			default:
				break;
		}

	if(SIGINT_val)
		exit(EXIT_FAILURE);

	for(int i=0 ; i < NUM_OF_CHILD ; ++i)
	{
		if(kill(child[i], SIGUSR2))
		{
			perror("kill");
			exit(EXIT_FAILURE);
		}

		if(sigsuspend(&sigChld) && errno == EFAULT)
		{
			perror("sigsuspend");
			exit(EXIT_FAILURE);
		}
	}

	parentRound(fp, 1); // First round

	if(SIGINT_val)
		exit(EXIT_FAILURE);

	for(int i=0 ; i < NUM_OF_CHILD ; ++i)
		if(kill(child[i], SIGUSR2) == -1)
		{
			perror("kill");
			exit(EXIT_FAILURE);
		}

	while(wait(NULL) != -1) { /* Intentionally left blank  */ }

	parentRound(fp, 2); // Second round

	if(fclose(fp))
	{
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	return 0;
}

void setSA(struct sigaction* sa, void (*handler)(int), int signum)
{
	memset(sa, 0, sizeof(*sa));
	sa->sa_handler = handler;

	if(sigaction(signum, sa, NULL) != 0)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void childFirstRound(FILE* fp, int id)
{
	struct flock flock;

	lockFile(fp, &flock, F_WRLCK);

	for(int i=0 ; i < id ; ++i)
		while(fgetc(fp) != '\n');

	float data[NUM_OF_COORDINATE][2]; // (x_0, y_0), (x_1, y_1) ...

	for(int i=0 ; i < NUM_OF_COORDINATE ; ++i)
	{
		fscanf(fp, "%f,%f", &data[i][0], &data[i][1]);

		if(fseek(fp, 1, SEEK_CUR) == -1)
		{
			perror("fseek");
			exit(EXIT_FAILURE);
		}
	}

	if(fseek(fp, -1, SEEK_CUR) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	printValue(fp, lagrange(data, 6, data[7][0]));

	if(fseek(fp, 0, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	if(fflush(fp) == EOF)
	{
		perror("fflush");
		exit(EXIT_FAILURE);
	}

	unlockFile(fp, &flock);
}

void childSecondRound(FILE* fp, int id)
{
	struct flock flock;

	lockFile(fp, &flock, F_WRLCK);

	for(int i=0 ; i < id ; ++i)
		while(fgetc(fp) != '\n');

	float data[NUM_OF_COORDINATE][2], tmp;

	for(int i=0 ; i < NUM_OF_COORDINATE ; ++i)
	{
		fscanf(fp, "%f,%f", &data[i][0], &data[i][1]);

		if(fseek(fp, 1, SEEK_CUR) == -1)
		{
			perror("fseek");
			exit(EXIT_FAILURE);
		}
	}

	fscanf(fp, "%f", &tmp); // for coming last item in a row

	printValue(fp, lagrange(data, 7, data[7][0]));

	printf("Polynomial %d: ", id);
	printCoefficient(data, 7);

	if(fseek(fp, 0, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	if(fflush(fp) == EOF)
	{
		perror("fflush");
		exit(EXIT_FAILURE);
	}

	if(fflush(stdout) == EOF)
	{
		perror("fflush");
		exit(EXIT_FAILURE);
	}

	unlockFile(fp, &flock);
}

void parentRound(FILE* fp, int round) // round 1 or 2
{
	struct flock flock;
	float val, y_7 = 0, sum = 0;

	lockFile(fp, &flock, F_RDLCK);

	for(int i=0, j=1; fscanf(fp, "%f", &val) != -1 ; ++i)
	{
		if(fgetc(fp) == '\n') // p(x_7)
		{
			++j;
			sum += fabs(y_7 - val);
		}

		if((16 + round) * j - round -1 == i) // f(x_7)
			y_7 = val;
	}

	fprintf(stdout, "Error of polynomial of degree %d: %.1f\n", 4 + round, sum / 8.);

	if(fseek(fp, 0, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	if(fflush(fp) == EOF)
	{
		perror("fflush");
		exit(EXIT_FAILURE);
	}

	if(fflush(stdout) == EOF)
	{
		perror("fflush");
		exit(EXIT_FAILURE);
	}

	unlockFile(fp, &flock);
}

void printCoefficient(float point[][2], int size)
{
	float coefficients[size];

	for(int i=0; i < size ; ++i)
		coefficients[i] = 0;

	for(int i=0; i < size ; ++i)
	{
		float newCoefficients[size];

		for(int j=0 ; j < size ; ++j)
			newCoefficients[j] = 0;

		if(i > 0)
		{
			newCoefficients[0] -= point[0][0] / (point[i][0] - point[0][0]);
			newCoefficients[1] = 1 / (point[i][0] - point[0][0]);
		}
		else
		{
			newCoefficients[0] -= point[1][0] / (point[i][0] - point[1][0]);
			newCoefficients[1] = 1 / (point[i][0] - point[1][0]);
		}

		int startIndex = 1; 

		if(i == 0)
			startIndex = 2; 

		for(int j = startIndex; j < size ; ++j)
		{
			if(i == j)
				continue;

			for(int nc = size - 1 ; nc >= 1; --nc)
				newCoefficients[nc] = newCoefficients[nc] * (-point[j][0] / (point[i][0] - point[j][0])) + newCoefficients[nc - 1] / (point[i][0] - point[j][0]);

			newCoefficients[0] = newCoefficients[0] * (-point[j][0] / (point[i][0] - point[j][0]));
		}

		for(int j=0 ; j < size ; ++j)
			coefficients[j] += point[i][1] * newCoefficients[j];
	}

	for(int i=0 ; i < size ; ++i)
	{
		if(i < size -1)
			printf("%.1f,", coefficients[i]);
		else
			printf("%.1f\n", coefficients[i]);
	}
}

void printValue(FILE* fp, float val)
{
	int len = digit((int)val) + 3; // + 3 because ',' and '.0' 

	if(val < 0)
		++len;

	long int fpos = ftell(fp);

	if(fseek(fp, 0 , SEEK_END) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	for(int i=0 ; i < len ; ++i)
		fprintf(fp, "%c", 'a');

	for(long int i = ftell(fp) ; i - len != fpos ; --i)
		fswap(fp, i-len-1, i-1);

	if(fseek(fp, fpos, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	fprintf(fp, ",%.1lf", val);
}

void lockFile(FILE* fp, struct flock* flock, int status)
{
	memset(flock, 0, sizeof(*flock));
	flock->l_type = status;

	if(fcntl(fileno(fp), F_SETLKW, flock) == -1)
	{
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
}

void unlockFile(FILE* fp, struct flock* flock)
{
	flock->l_type = F_UNLCK;

	if(fcntl(fileno(fp), F_SETLKW, flock) == -1)
	{
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
}

float lagrange(float data[][2], int size, float x)
{
	float yp = 0, p;

	for(int i=0 ; i < size ; ++i)
	{
		p = 1;

		for(int j=0 ; j < size ; ++j)
			if(i != j)
				p = p * (x - data[j][0]) / (data[i][0] - data[j][0]);

		yp = yp + p * data[i][1];
	}

	return yp;
}

int digit(int num)
{
	int len;

	for(len = 0 ; num != 0 ; ++len)
		num = num / 10;

	return len;
}

void fswap(FILE* fp, long int pos1, long int pos2)
{
	long int savedPos = ftell(fp);
	char chr1, chr2;

	if(fseek(fp, pos1, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	chr1 = fgetc(fp);

	if(fseek(fp, pos2, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	chr2 = fgetc(fp);

	if(fseek(fp, pos1, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	fputc(chr2, fp);

	if(fseek(fp, pos2, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}

	fputc(chr1, fp);

	if(fseek(fp, savedPos, SEEK_SET) == -1)
	{
		perror("fseek");
		exit(EXIT_FAILURE);
	}
}