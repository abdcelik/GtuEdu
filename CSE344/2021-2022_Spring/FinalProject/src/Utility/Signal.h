#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "Lib.h"

/*
	Changes the signal action
	I any error occurs, program terminates with printing error message to stderr
*/
void changeSignalAction(void (*handler)(int), int);

/*
	Handles SIGINT signal and increases global variable by one
*/
void SIGINT_handler(int);

/*
	Checks global variable whether SIGINT signal is arrived or not
*/
void checkSIGINT();

/*
	Returns 1 if SIGINT signal is arrived. Otheriwse returns 0
*/
int isSIGINT();

#endif