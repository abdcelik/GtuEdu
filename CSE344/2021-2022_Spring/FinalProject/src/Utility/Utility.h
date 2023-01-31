#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdio.h>

#define BUFFER_16 16
#define BUFFER_32 32
#define BUFFER_128 128
#define BUFFER_512 512

#define CLIENT_REQUEST 1
#define SERVANT_INFO_REQUEST 2

#define REQUEST_MESSAGE_SIZE 512

struct Request
{
	int who;	// 0 indicates client, 1 indicates servant
	char content[REQUEST_MESSAGE_SIZE];
};

typedef struct Request Request;

//	Temporary variables for avoid creating unnecessary variables
extern int TEMP_INT;
extern char TEMP_BUFFER_128[BUFFER_128];

/*
	Converts string to integer
	Number should be positive integer. Otherwise returns -1
*/
int stringToPositiveInt(const char* string);

/*
	Check given character is digit or not
	Returns 1 if given character is digit. Otherwise returns 0
*/
int isDigit(char var);

#endif