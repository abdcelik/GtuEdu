#include "ServantBase.h"

void* servantThread(void*);

int main(int argc, char* argv[])
{
	changeSignalAction(SIGINT_handler, SIGINT);
	handleArguments(argc, argv);
	x_setvbuf(stdout, NULL, _IONBF, 0);
	x_atexit(terminateServant);

	arrangePid();
	loadDataFromFile();
	openOwnConnectionAndListen();
	connectServer();
	checkSIGINT();

	sendInformationToServer();
	initThreadVector();

	for(int acceptedFd = -1 ; TRUE ;)
	{
		acceptedFd = acceptSocket();

		if(isSIGINT())
		{
			if(acceptedFd != -1)
				xm_close(acceptedFd);
			exit(EXIT_FAILURE);
		}

		createDetachedThread(servantThread, acceptedFd);
	}

	return 0;
}

void* servantThread(void* arg)
{
	char request[REQUEST_MESSAGE_SIZE];
	int fd = *(int*)arg, result = 0;

	memset(request, 0 , REQUEST_MESSAGE_SIZE);
	xm_read(fd, request, REQUEST_MESSAGE_SIZE);

	result = query(request);
	increaseTotalHandledRequest();

	xm_write(fd, &result, sizeof(int));
	xm_close(fd);

	pthread_exit(NULL);
}