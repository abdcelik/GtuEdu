#ifndef _BASIS_H_
#define _BASIS_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "LIB.h"
#include "MATRIX.h"
#include "String.h"

#define BUFFER_SIZE 256

struct MyThread
{
	pthread_t thread;
	int i;
};

typedef struct MyThread MyThread;

extern char *FILEPATH1ARGUMENT, *FILEPATH2ARGUMENT, *OUTPUTFILEARGUMENT;
extern int ARGUMENT_N, ARGUMENT_M;
extern MATRIX* MATRIXA, *MATRIXB;
extern MyThread* THREADS;

void handleArguments(int argc, char* argv[]);
void changeSignalAction(void (*handler)(int), int signal);
void SIGINT_handler(int signal_number);
void checkSIGINT();
void terminateProgram();
MATRIX* readFromFile(const char* filePath);
void writeToFile(const char* filePath, void** items);
void buildHelperVariable();
void buildMutexAndConditionalVariable();
void buildThreads(MyThread* threads, void* (*func)(void*));
void** joinThreads(MyThread* threads);
void* ThreadFunc(void* arg);
void printWithTimeStamp(FILE* fd, const char* format, ...);
int power(int, int);

#endif