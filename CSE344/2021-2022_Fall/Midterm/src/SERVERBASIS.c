#include "SERVERBASIS.h"

char* SERVERFIFOPATH = NULL, *LOGFILEPATH = NULL;
int poolSizeOfServerY = 0, poolSizeOfServerZ = 0, sleepDuration = 0;
int BASIS_ERRNO = 0;

int doubleInitiationFd = -1;
struct flock doubleInitiationLock;

int logFd = -1;

pid_t serverZPId = -1;
int pipeYZ[2] = {0, 0};
int* serverz_childPId = NULL;

int* sharedMemAddr = NULL;
int sharedMemLen = 0;

int totalRequest = 0, totalInvertible = 0, totalForwardedRequest = 0;
int serverFd = -1, dummyFd = -1;

CHILD* child = NULL;

void serverZ_bye();
void serverZ_checkSIGINT();
void serverZ_child_checkSIGINT();
void serverZ_child_bye();

int calculateReadByteNumber(STRING*);
int countBusyWorker(int*);
int lockMyFile(struct flock* lock, int fd, short l_type, int cmd);

int handleArguments(int argc, char* argv[])
{
	if(argc != 11)
		return BASIS_ERRNO = 1;

	for(int opt = 0 ; (opt = getopt(argc, argv, ":s:o:p:r:t:")) != -1 ;)
		switch(opt)
		{
			case 's':	SERVERFIFOPATH		= optarg;		break;
			case 'o':	LOGFILEPATH			= optarg;		break;
			case 'p':
				poolSizeOfServerY = atoi(optarg);

				if(poolSizeOfServerY < 2)
					return BASIS_ERRNO = 1;
				break;

			case 'r':
				poolSizeOfServerZ = atoi(optarg);	

				if(poolSizeOfServerZ < 2)
					return BASIS_ERRNO = 1;
				break;

			case 't':	sleepDuration		= atoi(optarg);	break;
			case ':': // option needs a value
				return BASIS_ERRNO = 2;
			case '?': // unknown option
				return BASIS_ERRNO = 3;
		}

	if(optind < argc) // extra arguments
		return BASIS_ERRNO = 4;

	return 0;
}

void printArgumentError()
{
	switch(BASIS_ERRNO)
	{
		case 1: fprintf(stderr, "ERROR! Usage: ./serverY -s pathToServerFifo -o pathToLogFile –p poolSize -r poolSize2 -t 2\npoolSize >= 2, poolSize2 >= 2\n"); break;
		case 2: fprintf(stderr, "ERROR! Option needs a value...\n"); break;
		case 3: fprintf(stderr, "ERROR! Unknown option...\n"); break;
		case 4: fprintf(stderr, "ERROR! Extra arguments detected...\n"); break;
	}
}

void changeAction(void (*handler)(int), int signal)
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

char* getMessage(int fd)
{
	STRING* message = STRING_build();
	char buffer = 0;

	for(int loopExit=0 ; !loopExit ;)
	{
		int res = read(fd, &buffer, sizeof(char));

		if(res == -1)
		{
			STRING_free(message);

			if(errno != EINTR)
			{
				perror("While getting message: read:");
				exit(EXIT_FAILURE);
			}

			return NULL;
		}

		STRING_addChar(message, buffer);

		if(buffer == '.')
		{
			int toReadByte = calculateReadByteNumber(message);

			for(int j=0; j < toReadByte ; ++j)
			{
				if(read(fd, &buffer, sizeof(char)) == -1)
				{
					STRING_free(message);

					if(errno != EINTR)
					{
						perror("While getting message: read:");
						exit(EXIT_FAILURE);
					}
			
					return NULL;
				}
				
				STRING_addChar(message, buffer);
			}

			loopExit = 1;
		}
	}

	char* messageCharArr = x_calloc(STRING_length(message) + 1, sizeof(char));
	STRING_cpy(messageCharArr, STRING_getCharArr(message));
	STRING_free(message);
	return messageCharArr;
}

int calculateReadByteNumber(STRING* s)
{
	int len = STRING_length(s);
	char* str = STRING_getCharArr(s);
	int num = 0;

	for(int i = 0 ; i < len - 1 ; ++i)
	{
		num *= 10;
		num += str[i] - '0';
	}

	return num - len;
}

CHILD* createChild(int size)
{
	return x_calloc(size, sizeof(CHILD));
}

void parseMessage(const char* message, pid_t* pid, int* matrixSize, int* busyWorker)
{
	int clientIdStartIndex = findClientNameStartIndex(message) + 5;
	int matrixStartIndex = findMatrixStartIndex(message);

	*matrixSize = mySqrt(countComma(message) + 1);
	*pid = 0, *busyWorker = 0;

	for(int i = clientIdStartIndex ; i < matrixStartIndex - 1 ; ++i)
		*pid = *pid * 10 + message[i] - '0';

	for(int i=0 ; i < poolSizeOfServerY; ++i)
		if(sharedMemAddr[i] == 0)
			++(*busyWorker);
}

int findMatrixStartIndex(const char* message)
{
	int index = -1;

	for(int i=0 ; message[i] ; ++i)
		if(message[i] == '.')
			index = i;

	return index + 1;
}

int findClientNameStartIndex(const char* message)
{
	int index = -1;

	for(int i=0 ; message[i] ; ++i)
		if(message[i] == '.')
		{
			index = i;
			break;
		}

	return index + 1;
}

void buildAndSetChildPipe(CHILD* child)
{
	for(int i=0 ; i < poolSizeOfServerY; ++i)
		x_pipe(child[i].filedes);
}

int countBusyWorker(int* memAddr)
{
	int busy = 0;

	for(int i=0 ; i < poolSizeOfServerY; ++i)
		if(memAddr[i] == 0)
			++busy;

	return busy;
}

int lockMyFile(struct flock* lock, int fd, short l_type, int cmd)
{
	int returnedValue = -1;

	if(l_type != F_UNLCK)
		memset(lock, 0, sizeof(*lock));

	lock->l_type = l_type;

	if((returnedValue = fcntl(fd, cmd, lock)) == -1)
	{
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	return returnedValue;
}

void mydprint(int fd, const char* format, ...)
{
	struct flock lock;
	va_list args;

	lockMyFile(&lock, fd, F_WRLCK, F_SETLKW);
	va_start(args, format);
	vdprintf(fd, format, args);
	va_end(args);
	lockMyFile(&lock, fd, F_UNLCK, F_SETLKW);
}

void takeMeasureAgainstDoubleInitiation()
{
	doubleInitiationFd = x_mopenm(DOUBLE_INITIATIN_FILENAME, O_WRONLY | O_CREAT, 0777, "Double initiation: x_mopen:");

	memset(&doubleInitiationLock, 0, sizeof(doubleInitiationLock));
	doubleInitiationLock.l_type = F_WRLCK;

	if(fcntl(doubleInitiationFd, F_SETLK, &doubleInitiationLock))
	{
		dprintf(logFd, "Double initiation!\n");
		exit(EXIT_FAILURE);
	}
}

void serverY_makeServerFifo()
{
	int returnedValue = -1;

	NO_EINTR(returnedValue = mkfifo(SERVERFIFOPATH, 0777));

	if(returnedValue == -1 && errno != EEXIST)
	{
		perror("Creating server fifo: mkfifo");
		exit(EXIT_FAILURE);
	}
}

int serverY_findAvailableWorkerIndex()
{
	int index = -1;

	for(int i = index + 1 ; i < poolSizeOfServerY ; ++i)
		if(sharedMemAddr[i] == 1)
		{
			index = i;
			break;
		}

	return index;
}

void serverY_bye()
{
	for(int i=0 ; i < poolSizeOfServerY ; ++i)
		kill(child[i].id, SIGINT);

	kill(serverZPId, SIGINT);

	unlink(SERVERFIFOPATH);

	if(serverFd != -1)
	{
		x_close(serverFd);
		remove(SERVERFIFOPATH);
	}

	if(dummyFd != -1)
		x_close(dummyFd);

	if(logFd != -1)
		x_close(logFd);

	if(child != NULL)
		free(child);

	if(doubleInitiationFd != -1)
	{
		lockMyFile(&doubleInitiationLock, doubleInitiationFd, F_UNLCK, F_SETLKW);
		x_close(doubleInitiationFd);
		remove(DOUBLE_INITIATIN_FILENAME);
	}
}

void serverY_checkSIGINT()
{
	if(sigint_count != 0)
	{
		for(int i=0 ; i < poolSizeOfServerY ; ++i)
			kill(child[i].id, SIGINT);

		mydprint(logFd, TEMPLATE_SIGINT_RECEIVED, totalRequest, sharedMemAddr[sharedMemLen], totalRequest - sharedMemAddr[sharedMemLen], totalForwardedRequest);
		exit(EXIT_FAILURE);
	}
}

void serverY_child(int indexOfChild)
{
	x_atexit(serverY_child_bye);
	x_close(child[indexOfChild].filedes[PIPE_WRITE_END]);
	sharedMemAddr[indexOfChild] = AVAILABLE;

	do
	{
		char* message, *clientFifo;

		if((message = getMessage(child[indexOfChild].filedes[PIPE_READ_END])) == NULL)
		{
			serverY_child_checkSIGINT();
			continue;
		}

		sharedMemAddr[indexOfChild] = BUSY;
		sleep(sleepDuration);

		serverY_child_printWorkerMessage(message, getpid());
		int isInvertible = serverY_child_isInvertible(message);
		sharedMemAddr[sharedMemLen] += isInvertible;

		clientFifo = serverY_child_buildClientName(message);
		char charBuffer = isInvertible ? '1' : '0';

		int clientFd = x_open(clientFifo, O_WRONLY, "Opening client fifo: x_open");
		x_write(clientFd, &charBuffer, sizeof(char));

		free(clientFifo);
		free(message);
		x_close(clientFd);
		sharedMemAddr[indexOfChild] = AVAILABLE;
		serverY_child_checkSIGINT();

	} while(TRUE);

	exit(EXIT_SUCCESS);
}

void serverY_child_printWorkerMessage(const char* message, pid_t pid)
{
	char timeStamp[BUFFER_SIZE];
	int matrixSize = 0, busyWorker = 0;
	pid_t clientPId = 0;
	time_t t = time(NULL);
	struct tm* ptm = localtime(&t);

	memset(timeStamp, 0, BUFFER_SIZE);
	strftime(timeStamp, BUFFER_SIZE, "%d/%m/%Y - %T", ptm);

	parseMessage(message, &clientPId, &matrixSize, &busyWorker);	
	mydprint(logFd, TEMPLATE_SERVER_RECEIVED, timeStamp, pid, clientPId,
		matrixSize, matrixSize, busyWorker, poolSizeOfServerY);
}

int serverY_child_isInvertible(const char* message)
{
	int matrixStartIndex = findMatrixStartIndex(message);
	SQMATRIX* matrix = MATRIX_createWith(message + matrixStartIndex);
	int isInvertible = MATRIX_isInvertible(matrix);

	MATRIX_free(matrix);
	return isInvertible;
}

char* serverY_child_buildClientName(const char* message)
{
	int clientNameStartIndex = findClientNameStartIndex(message);
	int matrixStartIndex = findMatrixStartIndex(message);

	char* name = x_calloc(matrixStartIndex - clientNameStartIndex + 1, sizeof(char));
	STRING_ncpy(name, message + clientNameStartIndex, matrixStartIndex - clientNameStartIndex -1);

	return name;
}

void serverY_child_bye()
{
	kill(getppid(), SIGINT);

	if(logFd != -1)
		x_close(logFd);

	if(child != NULL)
		free(child);
}

void serverY_child_checkSIGINT()
{
	if(sigint_count != 0)
		exit(EXIT_FAILURE);
}

void serverZ_create()
{
	x_pipe(pipeYZ);

	switch((serverZPId = x_fork()))
	{
		case 0:
			x_close(pipeYZ[PIPE_WRITE_END]);
			break;
		default:
			x_close(pipeYZ[PIPE_READ_END]);
			return;
	}

	serverz_childPId = x_calloc(poolSizeOfServerZ, sizeof(int));

	for(int i=0 ; i < poolSizeOfServerZ ; ++i)
	{
		switch(serverz_childPId[i] = x_fork())
		{
			case 0:
				atexit(serverZ_child_bye);
				exit(EXIT_SUCCESS);
			default:
				break;
		}
	}

	x_atexit(serverZ_bye);
	serverZ_checkSIGINT();
	mydprint(logFd, TEMPLATE_SERVERZ_START, LOGFILEPATH, sleepDuration, poolSizeOfServerZ);

	for(int i=0 ; i < poolSizeOfServerZ ; ++i)
		wait(NULL);

	exit(EXIT_SUCCESS);
}

void serverZ_bye()
{
	free(serverz_childPId);
	x_close(logFd);
	x_close(pipeYZ[PIPE_READ_END]);
}

void serverZ_checkSIGINT()
{
	if(sigint_count)
	{
		kill(getppid(), SIGINT);

		for(int i=0 ; i < poolSizeOfServerZ ; ++i)
			kill(serverz_childPId[i], SIGINT);

		exit(EXIT_FAILURE);
	}
}

void serverZ_child_checkSIGINT()
{
	if(sigint_count)
	{
		kill(getppid(), SIGINT);
		exit(EXIT_FAILURE);
	}
}

void serverZ_child_bye()
{
	free(serverz_childPId);
	x_close(logFd);
}

void SIGINT_handler(int signal_number) { ++sigint_count; }