#include "ServerBase.h"

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t COND = PTHREAD_COND_INITIALIZER;

void* serverThread(void*);

int main(int argc, char* argv[])
{
	changeSignalAction(SIGINT_handler, SIGINT);
	handleArguments(argc, argv);
	x_setvbuf(stdout, NULL, _IONBF, 0);
	x_atexit(terminateServer);

	buildRequestQueue();
	buildDetachedThreads(serverThread);
	buildSocketAndListen();
	initServantVector();

	for(int acceptedFd = 0 ; TRUE ;)
	{
		acceptedFd = acceptSocket();
		
		if(isSIGINT())
		{
			if(acceptedFd != -1)
				xm_close(acceptedFd);
			exit(EXIT_FAILURE);
		}

		x_pthread_mutex_lock(&MUTEX);
		addRequestQueue(acceptedFd);
		x_pthread_cond_broadcast(&COND);
		x_pthread_mutex_unlock(&MUTEX);
	}

	return 0;
}

void* serverThread(void* arg)
{
	for(int requestFd = 0 ; TRUE ;)
	{
		x_pthread_mutex_lock(&MUTEX);

		while(!isRequestQueueBusy())
			x_pthread_cond_wait(&COND, &MUTEX);

		requestFd = getRequestFromQueue();
		x_pthread_mutex_unlock(&MUTEX);

		Request request;

		memset(&request, 0, sizeof(Request));
		xm_read(requestFd, &request, sizeof(Request));

		switch(request.who)
		{
			case CLIENT_REQUEST:
				printWithTimeStamp(stdout, "Request arrived \"%s\"\n", request.content);
				respondClientRequest(requestFd, request.content);
				break;
			case SERVANT_INFO_REQUEST:
				addServantInfo(request.content);
				break;
		}

		xm_close(requestFd);
	}

	pthread_exit(NULL);		// thread cannot reach this point
}