#ifndef _SERVER_BASE_H_
#define _SERVER_BASE_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../Utility/Lib.h"
#include "../Utility/Utility.h"
#include "../Utility/Signal.h"
#include "../DataStructure/Queue.h"
#include "../DataStructure/Vector.h"
#include "../DataStructure/String.h"
#include "../DataStructure/FileSystem.h"

struct ServantAttr
{
	pid_t pid;
	char ip[BUFFER_16];
	int portNumber;
	char firstCity[DIRECTORY_NAME_SIZE];
	char lastCity[DIRECTORY_NAME_SIZE];
	struct sockaddr_in address;
};

typedef struct ServantAttr ServantAttr;

/*
	Prints message with time stamp
	Message starts with time stamp
	Thread switch cannot occur while a thread is using this function
*/
void printWithTimeStamp(FILE*, const char*, ...);

/*
	Checks the command line arguments
	If there is an error, useful message is printed to stderr and terminated
*/
void handleArguments(int, char*[]);

/*
	Frees server allocated memory
	If the program terminates at any point due to an error, deallocates all allocated memory
*/
void terminateServer();

/*
	Builds queue for thread pool
	If any error occurs, the program prints error message to stderr and terminates
*/
void buildRequestQueue();

/*
	Builds thread structure and creates thread with given function
	If any error occurs, the program prints error message to stderr and terminates
*/
void buildDetachedThreads(void* (*func)(void*));

/*
	Builds socket using given IP and port number from command line
	Builds server address then listen it
	If any error occurs, the program prints error message to stderr and terminates
*/
void buildSocketAndListen();

/*
	Builds servants vector to keep information about its
*/
void initServantVector();

/*
	Accepts socket which is created buildSocketAndListen function
	If any error occurs, the program prints error message to stderr and terminates
*/
int acceptSocket();

/*
	Adds given integer to global queue for non-busy threads
*/
void addRequestQueue(int);

/*
	Returns global queue's for non-busy threads size
*/
int isRequestQueueBusy();

/*
	Returns head of queue for non-busy threads
*/
int getRequestFromQueue();

/*
	Parses given message and builds ServantAttr
	Adds new ServantAttr to global servant vector
	If any error occurs, the program prints error message to stderr and terminates
*/
void addServantInfo(char*);

/*
	Responds client request
	If any error occurs, the program prints error message to stderr and terminates
*/
void respondClientRequest(int, char*);

#endif