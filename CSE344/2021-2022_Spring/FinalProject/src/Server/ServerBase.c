#include "ServerBase.h"

int PORT_ARG = -1, NUMBEROFTHREADS_ARG = 0;

int TOTAL_HANDLED_REQUEST = 0;

Queue* REQUEST = NULL;
pthread_t* THREAD = NULL;

int SOCKET_FD = -1;
struct sockaddr_in SERVER_ADDRESS;
int ADDRESS_LENGTH = 0;
const int BACKLOG = 4096;

Vector* SERVANT = NULL;

int queryAllServant(char*);
int queryServant(char*, int);
int getMessageFromServant(int);
int sendMessageToServant(char*, int);
int findCityIndex(char*);

void printWithTimeStamp(FILE* fd, const char* format, ...)
{
	va_list args;
	char timeBuffer[BUFFER_128];
	char buffer[BUFFER_512];
	time_t t = x_time(NULL);
	struct tm* ptm = localtime(&t);

	if(ptm == NULL)
		return;

	strftime(timeBuffer, BUFFER_128, "[%d/%m/%Y - %T]", ptm);
	sprintf(buffer, "%s%s", timeBuffer, format);

	va_start(args, format);
	vfprintf(fd, buffer, args);
	va_end(args);
}

void handleArguments(int argc, char* argv[])
{
	if(argc != 5)
	{
		fprintf(stderr, "ERROR! Usage: ./server -p PORT -t numberOfThreads\n");
		exit(EXIT_FAILURE);
	}

	for(int opt = 0 ; (opt = getopt(argc, argv, ":p:t:")) != -1 ;)
		switch(opt)
		{
			case 'p':
				if((PORT_ARG = stringToPositiveInt(optarg)) < 0)
				{
					fprintf(stderr, "ERROR! Port number should be positive integer\n");
			 		exit(EXIT_FAILURE);
				}
				break;
			case 't':
				if((NUMBEROFTHREADS_ARG = stringToPositiveInt(optarg)) < 0 || NUMBEROFTHREADS_ARG < 5)
				{
					fprintf(stderr, "ERROR! Number of threads should be positive integer and greater than 5\n");
					exit(EXIT_FAILURE);
				}
				break;
			case ':':
				fprintf(stderr, "ERROR! Option needs a value\n");
				exit(EXIT_FAILURE);
			case '?':
				fprintf(stderr, "ERROR! Unknown option\n");
				exit(EXIT_FAILURE);
		}

	if(optind < argc)
	{
		fprintf(stderr, "ERROR! Extra arguments detected\n");
		exit(EXIT_FAILURE);
	}
}

void terminateServer()
{
	if(isSIGINT())
		fprintf(stdout, "SIGINT has been received. I handled a total of %d requests. Goodbye.\n", TOTAL_HANDLED_REQUEST);

	if(THREAD != NULL)
	{
		for(int i = 0 ; i < NUMBEROFTHREADS_ARG ; ++i)
			x_pthread_cancel(THREAD[i]);

		free(THREAD);
	}

	if(REQUEST != NULL)
		Queue_free(REQUEST);

	if(SOCKET_FD != -1)
		xm_close(SOCKET_FD);

	if(SERVANT != NULL)
	{
		for(int i = 0 ; i < Vector_size(SERVANT) ; ++i)
			x_kill(((ServantAttr*)Vector_get(SERVANT, i))->pid, SIGINT);

		Vector_free(SERVANT, free);
	}
}

void buildRequestQueue()
{
	REQUEST = Queue_init();
}

void buildDetachedThreads(void* (*func)(void*))
{
	THREAD = x_calloc(NUMBEROFTHREADS_ARG, sizeof(pthread_t));

	for(int i = 0 ; i < NUMBEROFTHREADS_ARG ; ++i)
	{
		x_pthread_create(&THREAD[i], NULL, func, NULL);
		x_pthread_detach(THREAD[i]);
	}
}

void buildSocketAndListen()
{
	int option = 1;

	SOCKET_FD = x_socket(AF_INET, SOCK_STREAM, 0);
	x_setsockopt(SOCKET_FD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(int));

	SERVER_ADDRESS.sin_family = AF_INET;
	SERVER_ADDRESS.sin_addr.s_addr = INADDR_ANY;
	SERVER_ADDRESS.sin_port = htons(PORT_ARG);
	ADDRESS_LENGTH = sizeof(SERVER_ADDRESS);

	x_bind(SOCKET_FD, (struct sockaddr*)&SERVER_ADDRESS, sizeof(SERVER_ADDRESS));
	x_listen(SOCKET_FD, BACKLOG);
}

void initServantVector()
{
	SERVANT = Vector_init();
}

int acceptSocket()
{
	return x_accept(SOCKET_FD, (struct sockaddr*)&SERVER_ADDRESS, (socklen_t*)&ADDRESS_LENGTH);
}

void addRequestQueue(int fd)
{
	Queue_offer(REQUEST, fd);
}

int isRequestQueueBusy()
{
	return Queue_size(REQUEST) != 0;
}

int getRequestFromQueue()
{
	return Queue_poll(REQUEST);
}

void addServantInfo(char* request)
{
	ServantAttr* servant = x_calloc(1, sizeof(ServantAttr));

	Vector_add(SERVANT, servant);
	sscanf(request, "%d %s %d %s %s", &servant->pid, servant->ip, &servant->portNumber, servant->firstCity, servant->lastCity);

	servant->address.sin_family = AF_INET;
	servant->address.sin_port = htons(servant->portNumber);

	x_inet_pton(AF_INET, servant->ip, &servant->address.sin_addr);
	printWithTimeStamp(stdout, "Servant %d present at port %d handling cities %s-%s\n", servant->pid, servant->portNumber, servant->firstCity, servant->lastCity);
}

void respondClientRequest(int fd, char* request)
{
	char command[BUFFER_32], city[DIRECTORY_NAME_SIZE];
	int index = 0, result = 0;

	++TOTAL_HANDLED_REQUEST;
	memset(city, 0, DIRECTORY_NAME_SIZE);

	if(sscanf(request, "%s %s %s %s %s", command, TEMP_BUFFER_128, TEMP_BUFFER_128, TEMP_BUFFER_128, city) < 4 || strcmp("transactionCount", command) != 0)
	{
		result = -2;
		printWithTimeStamp(stdout, "Invalid query. Error was sent to client\n");
		xm_write(fd, &result, sizeof(int));
		return;
	}

	switch(index = findCityIndex(city))
	{
		case -2:
			result = -1;
			break;
		case -1:
			printWithTimeStamp(stdout, "Contacting ALL servants\n");
			result = queryAllServant(request);
			break;
		default:
			printWithTimeStamp(stdout, "Contacting servant %d\n", ((struct ServantAttr*)Vector_get(SERVANT, index))->pid);
			result = queryServant(request, index);
			break;
	}

	if(index == -2 || result == -1)
	{
		printWithTimeStamp(stdout, "No servant found to handle the query. Error was sent to client\n");
		xm_write(fd, &result, sizeof(int));
		return;
	}

	xm_write(fd, &result, sizeof(int));
	printWithTimeStamp(stdout, "Response received: %d, forwarded to client\n", result);
}

int queryAllServant(char* message)
{
	int total = 0;

	for(int i = 0 ; i < Vector_size(SERVANT) ; ++i)
		total += getMessageFromServant(sendMessageToServant(message, i));

	return total;
}

int queryServant(char* message, int index)
{
	return getMessageFromServant(sendMessageToServant(message, index));
}

int getMessageFromServant(int fd)
{
	int result = 0;

	x_read(fd, &result, sizeof(int));
	return result;
}

int sendMessageToServant(char* message, int index)
{
	int servantSocketFd = x_socket(AF_INET, SOCK_STREAM, 0);
	ServantAttr* servant = Vector_get(SERVANT, index);

	x_connect(servantSocketFd, (struct sockaddr*)&servant->address, sizeof(servant->address));
	xm_write(servantSocketFd, message, strlen(message) + 1);

	return servantSocketFd;
}

int findCityIndex(char* city)
{
	if(*city == '\0')
		return -1;

	for(int i = 0 ; i < Vector_size(SERVANT) ; ++i)
	{
		struct ServantAttr* item = Vector_get(SERVANT, i);

		if(String_cmp(city, item->firstCity) >= 0 && String_cmp(city, item->lastCity) <= 0)
			return i;
	}

	return -2;
}