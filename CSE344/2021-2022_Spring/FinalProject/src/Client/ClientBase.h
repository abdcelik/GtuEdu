#ifndef _CLIENTBASE_H_
#define _CLIENTBASE_H_

#include <arpa/inet.h>
#include <stdlib.h>
#include "../Utility/Lib.h"
#include "../Utility/Utility.h"
#include "../Utility/Signal.h"
#include "../DataStructure/String.h"

struct Thread
{
	pthread_t threadID;
	int index;
	int socketFd;
	Request* clientRequest;
};

typedef struct Thread Thread;

/*
	Checks the command line arguments
	If there is an error, useful message is printed to stderr and terminated
*/
void handleArguments(int, char*[]);

/*
	Frees client allocated memory
	If the program terminates at any point due to an error, deallocates all allocated memory
*/
void terminateClient();

/*
	Reads all request from given file from command line argument
	If there are empty rows, it removes it from whole request structure(Structure is an StringArray)
	If any error occurs, the program prints error message to stderr and terminates
*/
void readAllRequestFromFile();

/*
	Builds thread array structure and creates thread
	Threads runs given function
	If any error occurs, the program prints error message to stderr and terminates
*/
void buildThreads(void* (*func)(void*));

/*
	Blocks thread until all threads reach the same point
	If any error occurs, the program prints error message to stderr and terminates
*/
void syncronizationBarrier();

/*
	Joins all threads
	If any error occurs, the program prints error message to stderr and terminates
*/
void joinThreads();

/*
	Builds socket and connects using given IP address and port number from command line
	If any error occurs, the program prints error message to stderr and terminates
*/
void buildSocketAndConnect(int);

/*
	Returns request message at given index from request array(StringArray)
*/
char* getRequestMessage(int);

/*
	Writes the request message at given index to the socket which is created and connected
*/
void writeSocket(int);

/*
	Reads an integer the socket at given index and returns it
*/
int readSocket(int);

#endif