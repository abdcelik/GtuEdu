#include "ClientBase.h"

void* clientThread(void*);

int main(int argc, char* argv[])
{
	changeSignalAction(SIGINT_handler, SIGINT);
	handleArguments(argc, argv);
	x_setvbuf(stdout, NULL, _IONBF, 0);
	x_atexit(terminateClient);

	readAllRequestFromFile();
	buildThreads(clientThread);
	joinThreads();
	return 0;
}

void* clientThread(void* arg)
{
	int index = *(int*)arg, result = 0;

	fprintf(stdout, "Client-Thread-%d: Thread-%d has been created\n", index, index);
	syncronizationBarrier();

	buildSocketAndConnect(index);

	fprintf(stdout, "Client-Thread-%d: I am requesting \"/%s\"\n", index, getRequestMessage(index));
	writeSocket(index);

	result = readSocket(index);

	switch(result)
	{
		case -2:
			fprintf(stdout, "Client-Thread-%d: ERROR! \"%s\" in invalid query\n", index, getRequestMessage(index));
			break;
		case -1:
			fprintf(stdout, "Client-Thread-%d: ERROR! The server's response to \"%s\" is \"No servant is found to handle!\"\n", index, getRequestMessage(index));
			break;
		default:
			fprintf(stdout, "Client-Thread-%d: The server's response to \"%s\" is %d\n", index, getRequestMessage(index), result);
			break;
	}
	
	fprintf(stdout, "Client-Thread-%d: Terminating\n", index);
	pthread_exit(NULL);
}