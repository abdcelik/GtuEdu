#ifndef _SERVANT_BASE_H_
#define _SERVANT_BASE_H_

#include <netdb.h>
#include "../DataStructure/String.h"
#include "../DataStructure/FileSystem.h"
#include "../DataStructure/Vector.h"
#include "../Utility/Signal.h"
#include "../Utility/Utility.h"

#define PORT_START_NUMBER 10000
#define PORT_MAX_NUMBER 33000

struct ThreadAttr
{
	pthread_t threadId;
	int arg;
};

typedef struct ThreadAttr ThreadAttr;

/*
	Checks the command line arguments
	If there is an error, useful message is printed to stderr and terminated
*/
void handleArguments(int, char*[]);

/*
	Frees server allocated memory
	If the program terminates at any point due to an error, deallocates all allocated memory
*/
void terminateServant();

/*
	Sets global pid number to process number without using getpid function
	If any error occurs, the program prints error message to stderr and terminates
*/
void arrangePid();

/*
	Loads data from file using given dataset path from command line
	If any error occurs, the program prints error message to stderr and terminates
*/
void loadDataFromFile();

/*
	Creates socket with a unique port number
	Port number starts to be tested from the global starting point. If the port is busy, one more port number is tried
	Created socket is listen
	If any error occurs, the program prints error message to stderr and terminates
*/
void openOwnConnectionAndListen();

/*
	Builds socket and connect using given IP and port number from command line
	If any error occurs, the program prints error message to stderr and terminates
*/
void connectServer();

/*
	Builds message which contains process id, IP address, unique port number and city names
	Sends this information to server using socket file descriptor which connectServer function builds it
	If any error occurs, the program prints error message to stderr and terminates
*/
void sendInformationToServer();

/*
	Initializes global thread vector
*/
void initThreadVector();

/*
	Accepts incoming connections
	If any error occurs, the program prints error message to stderr and terminates
*/
int acceptSocket();

/*
	Creates a new detached thread and adds it global thread vector
	If any error occurs, the program prints error message to stderr and terminates
*/
void createDetachedThread(void* (*threadFunc)(void*), int);

/*	Queries the given message in the global dataset	*/
int query(char*);

/*	Increases the global total variable	*/
void increaseTotalHandledRequest();

#endif