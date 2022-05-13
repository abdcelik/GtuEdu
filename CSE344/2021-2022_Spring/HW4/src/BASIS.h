#ifndef _BASIS_H_
#define _BASIS_H_

#include <stdarg.h>
#include <sys/ipc.h>
#include "LIB.h"

#define BUFFER_SIZE 255
#define SYSTEMVKEY "SYSTEMVKEYFILE"

struct ThreadAttr
{
	pthread_t thread;
	int i;
};

extern int NUMBEROFCONSUMER, N;
extern char* INPUTFILEPATH;
extern int inputFd;
extern int semId;

void handleArguments(int argc, char* argv[]);
void changeSignalAction(void (*handler)(int), int signal);
void SIGINT_handler(int signal_number);
void checkSIGINT();
void printWithTimeStamp(const char* format, ...);
void buildSystemVSemaphores();
void destroySystemVSemaphores();
void buildDetachedSupplierThread(void* (*func)(void*), pthread_t* thread);
void buildConsumerThreads(void* (*func)(void*), struct ThreadAttr* consumers);
void joinConsumerThreads(struct ThreadAttr* consumers);

#endif