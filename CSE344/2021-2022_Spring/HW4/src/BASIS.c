#include "BASIS.h"

sig_atomic_t sigint_count = 0;

int NUMBEROFCONSUMER = -1, N = -1;
char* INPUTFILEPATH = NULL;
int inputFd = -1;
int semId = -1;

int basisErrno = 0;

int handle(int, char*[]);
void printArgumentError();

void handleArguments(int argc, char* argv[])
{
	int returnedValue = handle(argc, argv);

	if(returnedValue != 0)
	{
		printArgumentError();
		exit(EXIT_FAILURE);
	}
}

int handle(int argc, char* argv[])
{
	if(argc != 7)
		return basisErrno = 1;

	for(int opt = 0 ; (opt = getopt(argc, argv, ":C:N:F:")) != -1 ;)
		switch(opt)
		{
			case 'C':
				if((NUMBEROFCONSUMER = atoi(optarg)) <= 4)
					return basisErrno = 5;
			case 'N':
				if((N = atoi(optarg)) <= 1)
					return basisErrno = 6;
			case 'F': INPUTFILEPATH = optarg; break;
			case ':': // option needs a value
				return basisErrno = 2;
			case '?': // unknown option
				return basisErrno = 3;
		}

	if(optind < argc) // extra arguments
		return basisErrno = 4;

	return 0;
}

void printArgumentError()
{
	switch(basisErrno)
	{
		case 1: fprintf(stderr, "ERROR! Usage: ./hw4 -C <int> -N <int> -F inputfilePath\n"); break;
		case 2: fprintf(stderr, "ERROR! Option needs a value...\n"); break;
		case 3: fprintf(stderr, "ERROR! Unknown option...\n"); break;
		case 4: fprintf(stderr, "ERROR! Extra arguments detected...\n"); break;
		case 5: fprintf(stderr, "ERROR! Number of consumer(C) must be greater than 4...\n"); break;
		case 6: fprintf(stderr, "ERROR! N must be greater than 1...\n"); break;
	}
}

void changeSignalAction(void (*handler)(int), int signal)
{
	struct sigaction sa;
	int sigactreturn = 0;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;

	if(sigfillset(&sa.sa_mask) == -1)
	{
		perror("sigset");
		exit(EXIT_FAILURE);
	}

	NO_EINTR(sigactreturn = sigaction(signal, &sa, NULL));

	if(sigactreturn == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void SIGINT_handler(int signal_number) { ++sigint_count; }

void checkSIGINT()
{
	if(sigint_count)
		exit(EXIT_FAILURE);
}

void printWithTimeStamp(const char* format, ...)
{
	va_list args;
	int timeBufferSize = BUFFER_SIZE/4;
	char timeBuffer[timeBufferSize];
	char buffer[BUFFER_SIZE];
	time_t t = x_time(NULL);
	struct tm* ptm = localtime(&t);

	if(ptm == NULL)
		return;

	strftime(timeBuffer, timeBufferSize, "[%d/%m/%Y - %T]", ptm);
	sprintf(buffer, "%s%s", timeBuffer, format);

	va_start(args, format);
	vprintf(buffer, args);
	va_end(args);
}

void buildSystemVSemaphores()
{
	union semun
	{
		int val;
		struct semid_ds* buf;
		unsigned short* array;
		struct seminfo* __buf;
	};

	union semun arg;
	unsigned short semVal[2] = {0, 0};
	int numberOfSemaphore = 2;

	semId = x_semget(IPC_PRIVATE, numberOfSemaphore, 0777 | IPC_CREAT);

	arg.array = semVal;

	if(semctl(semId, 0, SETALL, arg) == -1)
		x_exit(EXIT_FAILURE, "semctl");
}

void destroySystemVSemaphores()
{
	if(semId == -1)
		return;

	x_semctl(semId, 0 , IPC_RMID);
}

void buildDetachedSupplierThread(void* (*func)(void*), pthread_t* thread)
{
	x_pthread_create(thread, NULL, func, NULL);
	x_pthread_detach(*thread);
}

void buildConsumerThreads(void* (*func)(void*), struct ThreadAttr* consumers)
{
	for(int i=0 ; i < NUMBEROFCONSUMER ; ++i)
	{
		consumers[i].i = i;
		x_pthread_create(&consumers[i].thread, NULL, func, &consumers[i].i);
	}
}

void joinConsumerThreads(struct ThreadAttr* consumers)
{
	for(int i=0 ; i < NUMBEROFCONSUMER ; ++i)
		x_pthread_join(consumers[i].thread, NULL);
}