#ifndef _BASIS_H_
#define _BASIS_H_

#include <stdio.h>
#include <unistd.h>
#include "STRING.h"

#define CHLD_PROCESS_EXEC "childP"

extern char* ChildArgv[];
extern char* ARG_INPUT, *ARG_OUTPUT;
extern int _BASIS_ERRNO;

/*
	Sets arguments
	Returns 0 if there is no unvalidity. Otherwise returns positive integer
	If there is an unvalidty, call printArgumentError
*/
int setArguments(int argc, char* argv[]);

/*
	Prints usefull error message to stderr with using own global variable
*/
void printArgumentError();

/*	Prints given array with given number	*/
void printEnvironmentVariables(char**, int);

#endif