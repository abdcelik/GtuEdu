#ifndef _STRING_H_
#define _STRING_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct String String;
typedef struct StringArray StringArray;

/*
	Builds a string with size 1
	If an error occurs, prints an error message to stderr and terminates program. Otherwise returns String*
*/
String* String_build();

/*	Frees given string	*/
void String_free(String*);

/*	Prints string to stdout	*/
void String_print(const String*);

/*	Returns length of the given string	*/
int String_length(const String*);

/*	Returns character array of given string	*/
char* String_getCharArr(const String*);

/*
	Adds given character to given string
	Returns:
		1 if adding is successful
		0 if adding is unsuccessful
		-1 if occurs an error while reallocation
*/
int String_addChar(String*, char);

/*
	Adds given characters to given string
	Returns;
		1 if adding is successfull
		0 if adding is unsuccessful
		-1 if occurs an error while reallocation
*/
int String_addCharArr(String*, const char*);

/*
	Adds given integer to given string
	Number of digits of the given integer must be less than 256
	Returns;
		1 if adding is successfull
		0 if adding is unsuccessful
		-1 if occurs an error while reallocation
*/
int String_addInt(String*, int);

/*
	Adds given double to given string
	Number of digits of the given double must be less than 256
	Returns;
		1 if adding is successfull
		0 if adding is unsuccessful
		-1 if occurs an error while reallocation
*/
int String_addDouble(String*, double);

int String_remove(String*, int);

int String_removeAllOccurences(String*, char);

/*	Returns length of given character array	*/
int String_len(const char*);

/* Returns comparision result	*/
int String_cmp(const char*, const char*);

StringArray* String_split(const String*, const char*);

int StringArray_remove(StringArray*, int);

int StringArray_removeItems(StringArray*, const char*);

String* StringArray_get(const StringArray*, int);

int StringArray_size(const StringArray*);

void StringArray_free(StringArray*);

#endif