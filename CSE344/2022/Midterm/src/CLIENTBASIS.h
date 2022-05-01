#ifndef _CLIENTBASIS_H_
#define _CLIENTBASIS_H_

#include "LIB.h"
#include "STRING.h"
#include "MATRIX.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <time.h>

#define BUFFER_SIZE 255
#define TEMPLATE_CLIENT_FIFO "/tmp/"
#define CLIENT_FIFO_NAME_LEN (sizeof(TEMPLATE_CLIENT_FIFO) + 20)
#define TEMPLATE_SUBMIT_OUTPUT "[%s] Client PID#%d (%s) is submitting a %dx%d matrix\n"
#define TEMPLATE_RECEIVE_OUTPUT "[%ld] Client PID#%d: the matrix is %s, total time %.2lf seconds, goodbye.\n"

char clientFifo[CLIENT_FIFO_NAME_LEN];

extern char* SERVERFIFOPATH, *DATAFILEPATH;

/*
	Changes the receiving signal response
	Sets the handler for the signal given as a parameter and changes the response of program
*/
void changeAction(void (*handler)(int), int signal);

/*
	Reads data from data file path
	Returns string representation of data
	lenghtofstring|string
*/
char* readData();

/*	Builds unique client's fifo name	*/
void buildClientFifoName(pid_t);

/*
	Handles arguments
	Returns 0 if there is no unvalidity. Otherwise returns positive integer
	If there is an unvalidty, call printArgumentError
*/
int handleArguments(int, char*[]);

/*	Prints usefull error message to stderr with using own global variable	*/
void printArgumentError();

/*	Counts given integer digit number	*/
int countDigit(int);

#endif