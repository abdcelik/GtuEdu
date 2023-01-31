#include "ClientBase.h"

char* REQUESTFILE_ARG = NULL, *IP_ARG = NULL;
int PORT_ARG = 0;

int REQUEST_FD = -1;
String* REQUEST_FILE_CONTENT = NULL;
StringArray* REQUEST = NULL;

pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t COND = PTHREAD_COND_INITIALIZER;
int NUMBER_OF_ARRIVED_THREAD = 0;

Thread* THREAD = NULL;
int NUMBER_OF_THREADS = 0;

void readFile(int, String*);

void handleArguments(int argc, char* argv[])
{
	if(argc != 7)
	{
		fprintf(stderr, "ERROR! Usage: ./client -r requestFile -q PORT -s IP\n");
		exit(EXIT_FAILURE);
	}

	for(int opt = 0 ; (opt = getopt(argc, argv, ":r:q:s:")) != -1 ;)
		switch(opt)
		{
			case 'r': REQUESTFILE_ARG = optarg; break;
			case 'q':
				if((PORT_ARG = stringToPositiveInt(optarg)) < 0)
				{
					fprintf(stderr, "ERROR! Port number should be positive integer!\n");
			 		exit(EXIT_FAILURE);
				}
				break;
			case 's': IP_ARG = optarg; break;
			case ':': // option needs a value
				fprintf(stderr, "ERROR! Option needs a value...\n");
				exit(EXIT_FAILURE);
			case '?': // unknown option
				fprintf(stderr, "ERROR! Unknown option...\n");
				exit(EXIT_FAILURE);
		}

	if(optind < argc) // extra arguments
	{
		fprintf(stderr, "ERROR! Extra arguments detected...\n");
		exit(EXIT_FAILURE);
	}
}

void terminateClient()
{
	if(isSIGINT())
		fprintf(stdout, "SIGINT has been received. Goodbye.\n");

	if(REQUEST_FD != -1)
		xm_close(REQUEST_FD);

	if(REQUEST_FILE_CONTENT != NULL)
		String_free(REQUEST_FILE_CONTENT);

	if(REQUEST != NULL)
		StringArray_free(REQUEST);

	if(THREAD != NULL)
	{
		for(int i = 0 ; i < NUMBER_OF_THREADS ; ++i)
		{
			if(THREAD[i].clientRequest != NULL)
				free(THREAD[i].clientRequest);

			if(THREAD[i].socketFd != 0)
				xm_close(THREAD[i].socketFd);
		}

		free(THREAD);
	}
}

void readAllRequestFromFile()
{
	REQUEST_FD = xm_open(REQUESTFILE_ARG, O_RDONLY);
	REQUEST_FILE_CONTENT = String_build();

	readFile(REQUEST_FD, REQUEST_FILE_CONTENT);
	REQUEST = String_split(REQUEST_FILE_CONTENT, "\n");
	StringArray_removeItems(REQUEST, "\n");

	for(int i = 0 ; i < StringArray_size(REQUEST) ; ++i)
	{
		String* item = StringArray_get(REQUEST, i);
		String_removeAllOccurences(item, '\n');
	}

	xm_close(REQUEST_FD);
	REQUEST_FD = -1;

	String_free(REQUEST_FILE_CONTENT);
	REQUEST_FILE_CONTENT = NULL;

	fprintf(stdout, "Client: I have loaded %d requests and I’m creating %d threads.\n", StringArray_size(REQUEST), StringArray_size(REQUEST));
}

void readFile(int fd, String* buffer)
{
	char charBuffer = 0;

	for(int loopExit = FALSE ; !loopExit ;)
	{
		if(xm_read(fd, &charBuffer, sizeof(char)) == 0)
		{
			loopExit = TRUE;
			continue;
		}

		String_addChar(buffer, charBuffer);
		checkSIGINT();
	}
}

void buildThreads(void* (*func)(void*))
{
	NUMBER_OF_THREADS = StringArray_size(REQUEST);
	THREAD = x_calloc(NUMBER_OF_THREADS, sizeof(Thread));

	for(int i = 0 ; i < NUMBER_OF_THREADS ; ++i)
	{
		THREAD[i].index = i;
		THREAD[i].clientRequest = x_calloc(1, sizeof(Request));
		THREAD[i].clientRequest->who = CLIENT_REQUEST;
		strcpy(THREAD[i].clientRequest->content, String_getCharArr(StringArray_get(REQUEST, i)));
		x_pthread_create(&THREAD[i].threadID, NULL, func, &THREAD[i].index);
	}
}

void syncronizationBarrier()
{
	x_pthread_mutex_lock(&MUTEX);

	if(++NUMBER_OF_ARRIVED_THREAD < StringArray_size(REQUEST))
		x_pthread_cond_wait(&COND, &MUTEX);
	else
		x_pthread_cond_broadcast(&COND);

	x_pthread_mutex_unlock(&MUTEX);
}

void joinThreads()
{
	for(int i = 0 ; i < NUMBER_OF_THREADS ; ++i)
		x_pthread_join(THREAD[i].threadID, NULL);
		
	fprintf(stdout, "Client: All threads have terminated, goodbye.\n");
}

void buildSocketAndConnect(int index)
{
	struct sockaddr_in sockaddr;

	THREAD[index].socketFd = x_socket(AF_INET, SOCK_STREAM, 0);

	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT_ARG);

	x_inet_pton(AF_INET, IP_ARG, &sockaddr.sin_addr);
	x_connect(THREAD[index].socketFd, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
}

char* getRequestMessage(int index)
{
	return THREAD[index].clientRequest->content;
}

void writeSocket(int index)
{
	xm_write(THREAD[index].socketFd, THREAD[index].clientRequest, sizeof(*THREAD[index].clientRequest));
}

int readSocket(int index)
{
	int buffer = 0;

	xm_read(THREAD[index].socketFd, &buffer, sizeof(int));
	return buffer;
}