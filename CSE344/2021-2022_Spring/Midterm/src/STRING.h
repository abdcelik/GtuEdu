#ifndef _STRING_H_
#define _STRING_H_

#include "LIB.h"

typedef struct STRING STRING;

/*
	Builds a string with size 1
	If an error occurs, prints an error message to stderr and terminates program. Otherwise returns STRING*
*/
STRING* STRING_build();

/*
	Builds a string with given size
	Size must be positive. Otherwise returns NULL
	If an error occurs, prints an error message to stderr and terminates program. Otherwise returns STRING*
*/
STRING* STRING_buildWithSize(int size);

/*	Frees given string	*/
void STRING_free(STRING*);

/*	Returns length of the given string	*/
int STRING_length(STRING*);

/*	Returns character array of given string	*/
char* STRING_getCharArr(STRING*);

/*
	Adds given character to given string
	Returns 1 if operation is successfull. Otherwise returns 0
*/
int STRING_addChar(STRING*, char);

/*
	Adds given characters to given string
	Returns 1 if operation is successfull. Otherwise returns 0
*/
int STRING_addCharArr(STRING*, char*);

/*
	Adds given integer to given string
	Returns 1 if operation is successfull. Otherwise returns 0
*/
int STRING_addInt(STRING*, int);

/*
	Adds given double to given string with given precise(precise shouldn't be greater than 5 and less than 1)
	Returns 1 if operation is successfull. Otherwise returns 0
*/
int STRING_addDouble(STRING*, double, int);

/*	Copies second one to first one	*/
void STRING_cpy(char*, char*);

/*	Copies second one to first one with given size	*/
void STRING_ncpy(char*, const char*, int);

/*	Calculates string length	*/
int STRING_len(char*);

#endif