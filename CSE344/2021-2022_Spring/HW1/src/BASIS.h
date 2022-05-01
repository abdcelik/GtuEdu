#ifndef _BASIS_H_
#define _BASIS_H_

#include <stdio.h>
#include <stdlib.h>
#include "VECTOR.h"
#include "LIB.h"
#include "RULE.h"

extern int _BASIS_ERRNO_;

/*
	Checks whether arguments is valid or not
	Returns 0 if there is no error. Otherwise sets own global variable and returns a non zero number
	If there is an error after checkArgument, call printArgumentError
*/
int checkArgument(int argc, char* argv[]);

/*
	Prints usefull error message to stderr using own global variable
*/
void printArgumentError();

/*
	Parses given rule
	WARNING: Does not check errors. Befor calling this function, must call checkArgument function
	Returns parsed rules. If function can't allocate memory returns NULL
*/
VECTOR* parseRule(char* argv[]);

/*
	Checks whether given integer is letter or digit or not
	Returns 1 if it is. Otherwise returns 0
*/
int is_al_num(int);

/*	Returns length of the string	*/
int str_len(const char*);

/*	Copies given second parameter to first parameter	*/
void str_cpy(char*, const char*);

/*	Compares two given string and returns 0 if they are equal	*/
int str_cmp(const char*, const char*);

#endif