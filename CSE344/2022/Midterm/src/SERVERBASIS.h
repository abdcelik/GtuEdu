#ifndef _SERVERBASIS_H_
#define _SERVERBASIS_H_

#include "DEAMON.h"
#include "STRING.h"
#include "MATRIX.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <semaphore.h>

#define FALSE 0
#define TRUE 1
#define BUSY 0
#define AVAILABLE 1
#define PIPE_READ_END 0
#define PIPE_WRITE_END 1
#define BUFFER_SIZE 255

#define SHARED_MEMORY_FILENAME "shraredMemory"
#define DOUBLE_INITIATIN_FILENAME "doubleInitiationFile"
#define TEMPLATE_SERVERY_START "Server Y (%s, p=%d, t=%d) started\n"
#define TEMPLATE_SERVERZ_START "Z:Server Z (%s, t=%d, r=%d) started\n"
#define TEMPLATE_SERVER_RECEIVED "[%s] Worker PID#%d is handling client PID#%d, matrix size %dx%d, pool busy %d/%d\n"
#define TEMPLATE_SIGINT_RECEIVED "SIGINT received, terminating Z and exiting server Y. Total requests handled: %d, %d invertible, %d not. %d requests were forwarded\n"

struct CHILD
{
	pid_t id;
	int filedes[2];
};

typedef struct CHILD CHILD;

extern sig_atomic_t sigint_count;

extern char* SERVERFIFOPATH, *LOGFILEPATH;
extern int poolSizeOfServerY, poolSizeOfServerZ, sleepDuration;

extern int doubleInitiationFd;
extern struct flock doubleInitiationLock;

extern int logFd;

extern pid_t serverZPId;
extern int pipeYZ[2];
extern int* serverz_childPId;
extern sem_t* shmSemAddr;

extern int* sharedMemAddr;
extern int sharedMemLen;

extern int totalRequest, totalInvertible, totalForwardedRequest;
extern int serverFd, dummyFd;

extern CHILD* child;

/*
	Handles arguments
	Returns 0 if there is no unvalidity. Otherwise returns positive integer
	If there is an unvalidty, call printArgumentError
*/
int handleArguments(int, char*[]);

/*	Prints usefull error message to stderr with using own global variable	*/
void printArgumentError();

/*
	Changes the receiving signal response
	Sets the handler for the signal given as a parameter and changes the response of program
*/
void changeAction(void (*handler)(int), int signal);

/*	Reads formatted message from given file descriptor	*/
char* getMessage(int fd);

CHILD* createChild(int size);

void parseMessage(const char* message, pid_t* pid, int* matrixSize, int* busyWorker);

int findMatrixStartIndex(const char* message);

int findClientNameStartIndex(const char* message);

void buildAndSetChildPipe(CHILD*);

void printWorkerMessage(const char* message, pid_t pid, int* memAddr, int logFd);

void mydprint(int fd, const char* format, ...);

void takeMeasureAgainstDoubleInitiation();

void serverY_makeServerFifo();

int serverY_findAvailableWorkerIndex();

void serverY_bye();

void serverY_checkSIGINT();

void serverY_child();

void serverY_child_printWorkerMessage(const char* message, pid_t pid);

int serverY_child_isInvertible(const char* message);

char* serverY_child_buildClientName(const char* message);

void serverY_child_bye();

void serverY_child_checkSIGINT();

void serverZ_create();

void SIGINT_handler(int signal_number);

#endif