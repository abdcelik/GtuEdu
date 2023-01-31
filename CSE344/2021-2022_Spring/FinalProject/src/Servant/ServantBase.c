#include "ServantBase.h"

char* DIRECTORYPATH_ARG = NULL, *IP_ARG = NULL;
int CITYLOWERRANGE_ARG = 0, CITYUPPERRANGE_ARG = 0, PORT_ARG = 0;

int TOTAL_HANDLED_REQUEST = 0;

pid_t PID = 0;
Dataset* DATASET = NULL;

struct dirent** ENTRY = NULL;
int ENTRY_SIZE = 0;

String* SUB_PATH = NULL, *SUB_FILE_PATH = NULL;
DIR* DIRECTORY = NULL;
int FD = -1;
String* CONTENT = NULL;

int SOCKET_TO_LISTEN = -1;
struct sockaddr_in ADDRESS;
int ADDRESS_LENGTH = 0;
const int BACKLOG = 4096;

int SERVER_SOCKET_FD = -1;

Vector* THREAD = NULL;

int parseCityRange(const char*);
void readDirectoryAndAddStructure(const char*, Directory*);
void readFileAndParse(const char*, File*);
void buildInfoMessage(Request*);

void handleArguments(int argc, char* argv[])
{
	if(argc != 9)
	{
		fprintf(stderr, "ERROR! Usage: ./servant -d directoryPath -c 10-19 -r IP -p PORT\n");
		exit(EXIT_FAILURE);
	}

	for(int opt = 0 ; (opt = getopt(argc, argv, ":d:c:r:p:")) != -1 ;)
		switch(opt)
		{
			case 'd': DIRECTORYPATH_ARG = optarg; break;
			case 'c':
				if(parseCityRange(optarg) < 0)
				{
					fprintf(stderr, "ERROR! City range format is invalid. Example city range format: 1-19\n");
			 		exit(EXIT_FAILURE);
				}
				break;
			case 'r': IP_ARG = optarg; break;
			case 'p':
				if((PORT_ARG = stringToPositiveInt(optarg)) < 0)
				{
					fprintf(stderr, "ERROR! Port number should be positive integer\n");
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

int parseCityRange(const char* input)
{
	int total = 0, res = 0;

	res = sscanf(input, "%d-%d%n", &CITYLOWERRANGE_ARG, &CITYUPPERRANGE_ARG, &total);

	if(res != 2 || total != strlen(input))
		return -1;

	if(CITYLOWERRANGE_ARG < 1 || CITYUPPERRANGE_ARG < 1 || CITYLOWERRANGE_ARG > CITYUPPERRANGE_ARG)
		return -1;

	return 0;
}

void terminateServant()
{
	if(DATASET != NULL)
		Dataset_free(DATASET);

	if(ENTRY != NULL)
	{
		for(int i = 0 ; i < ENTRY_SIZE ; ++i)
			free(ENTRY[i]);
		free(ENTRY);
	}

	if(SUB_PATH != NULL)
		String_free(SUB_PATH);

	if(DIRECTORY != NULL)
		x_closedir(DIRECTORY);

	if(SUB_FILE_PATH != NULL)
		String_free(SUB_FILE_PATH);

	if(FD != -1)
		xm_close(FD);

	if(CONTENT != NULL)
		String_free(CONTENT);

	if(SOCKET_TO_LISTEN != -1)
		xm_close(SOCKET_TO_LISTEN);

	if(SERVER_SOCKET_FD != -1)
		xm_close(SERVER_SOCKET_FD);

	if(THREAD != NULL)
		Vector_free(THREAD, free);

	if(isSIGINT())
		fprintf(stdout, "Servant %d: termimation message received, handled %d requests in total\n", PID, TOTAL_HANDLED_REQUEST);
}

void arrangePid()
{
	char processId[BUFFER_32];

	memset(processId, 0 , BUFFER_32);
	x_readlink("/proc/self", processId, BUFFER_32);
	sscanf(processId, "%d", &PID);
}

void loadDataFromFile()
{
	DATASET = Dataset_init();
	ENTRY_SIZE = x_scandir(DIRECTORYPATH_ARG, &ENTRY, NULL, alphasort);

	int lowerBound = CITYLOWERRANGE_ARG + 1;
	int upperBound = CITYUPPERRANGE_ARG + 1 >= ENTRY_SIZE ? ENTRY_SIZE - 1 : CITYUPPERRANGE_ARG + 1;

	if(lowerBound >= ENTRY_SIZE) // for . and ..
	{
		fprintf(stderr, "ERROR! City lower bound exceeded the total number of cities!\n");
		exit(EXIT_FAILURE);
	}

	for(int i = lowerBound ; i <= upperBound ; ++i)
	{
		checkSIGINT();

		Directory* dir = Directory_initWithName(ENTRY[i]->d_name);

		Dataset_add(DATASET, dir);
		SUB_PATH = String_build();

		String_addCharArr(SUB_PATH, DIRECTORYPATH_ARG);
		String_addChar(SUB_PATH, '/');
		String_addCharArr(SUB_PATH, ENTRY[i]->d_name);

		readDirectoryAndAddStructure(String_getCharArr(SUB_PATH), dir);

		String_free(SUB_PATH);
		SUB_PATH = NULL;
	}

	fprintf(stdout, "Servant %d: loaded dataset, cities %s-%s\n", PID, Dataset_getFirstDirName(DATASET), Dataset_getLastDirName(DATASET));
}

void readDirectoryAndAddStructure(const char* directoryPath, Directory* directory)
{
	struct dirent* entry = NULL;

	DIRECTORY = x_opendir(directoryPath);

	for(int loopExit = FALSE ; !loopExit ;)
	{
		checkSIGINT();

		if((entry = x_readdir(DIRECTORY)) == NULL)
		{
			loopExit = TRUE;
			continue;
		}

		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		File* file = File_initWithDate(entry->d_name);

		Directory_add(directory, file);
		SUB_FILE_PATH = String_build();

		String_addCharArr(SUB_FILE_PATH, directoryPath);
		String_addChar(SUB_FILE_PATH, '/');
		String_addCharArr(SUB_FILE_PATH, entry->d_name);

		readFileAndParse(String_getCharArr(SUB_FILE_PATH), file);

		String_free(SUB_FILE_PATH);
		SUB_FILE_PATH = NULL;
	}

	x_closedir(DIRECTORY);
	DIRECTORY = NULL;
}

void readFileAndParse(const char* filePath, File* file)
{
	char buffer = 0;
	FD = xm_open(filePath, O_RDONLY);
	CONTENT = String_build();

	for(int bytesRead = 0, loopExit = FALSE ; !loopExit ;)
	{
		checkSIGINT();
		bytesRead = xm_read(FD, &buffer, sizeof(char));

		if(bytesRead == 0)
		{
			loopExit = TRUE;
			continue;
		}

		if(buffer == '\n')
		{
			Record* record = Record_initWithContent(String_getCharArr(CONTENT));

			if(record != NULL)
				File_add(file, record);

			String_free(CONTENT);
			CONTENT = String_build();
		}
		else
			String_addChar(CONTENT, buffer);
	}

	xm_close(FD);
	FD = -1;
	String_free(CONTENT);
	CONTENT = NULL;
}

void openOwnConnectionAndListen()
{
	int option = 1;

	SOCKET_TO_LISTEN = x_socket(AF_INET, SOCK_STREAM, 0);
	x_setsockopt(SOCKET_TO_LISTEN, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

	ADDRESS.sin_family = AF_INET;
	ADDRESS.sin_addr.s_addr = INADDR_ANY;

	for(int i = PORT_START_NUMBER, loopExit = FALSE ; i < PORT_MAX_NUMBER && !loopExit ; ++i)
	{
		ADDRESS.sin_port = htons(i);
		ADDRESS_LENGTH = sizeof(ADDRESS);

		if(bind(SOCKET_TO_LISTEN, (struct sockaddr*)&ADDRESS, ADDRESS_LENGTH) == -1)
		{
			if(errno == EADDRINUSE)
				continue;

			x_exit(EXIT_FAILURE, "bind");
		}

		loopExit = TRUE;
	}
	
	x_listen(SOCKET_TO_LISTEN, BACKLOG);
	fprintf(stdout, "Servant %d: listening at port %d\n", PID, ntohs(ADDRESS.sin_port));
}

void connectServer()
{
	struct sockaddr_in sockaddr;

	SERVER_SOCKET_FD = x_socket(AF_INET, SOCK_STREAM, 0);

	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(PORT_ARG);

	x_inet_pton(AF_INET, IP_ARG, &sockaddr.sin_addr);
	x_connect(SERVER_SOCKET_FD, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
}

void sendInformationToServer()
{
	Request request = {SERVANT_INFO_REQUEST};

	buildInfoMessage(&request);
	xm_write(SERVER_SOCKET_FD, &request, sizeof(request));

	xm_close(SERVER_SOCKET_FD);
	SERVER_SOCKET_FD = -1;
}

void buildInfoMessage(Request* request)
{
	char hostbuffer[256];
	struct hostent *host_entry;

	if(gethostname(hostbuffer, sizeof(hostbuffer)) == -1)
		x_exit(EXIT_FAILURE, "gethostname");

	if((host_entry = gethostbyname(hostbuffer)) == NULL)
		x_exit(EXIT_FAILURE, "gethostbyname");

	String* str = String_build();

	String_addInt(str, PID);
	String_addChar(str, ' ');
	String_addCharArr(str, inet_ntoa(*((struct in_addr*)host_entry->h_addr_list[0])));
	String_addChar(str, ' ');
	String_addInt(str, ntohs(ADDRESS.sin_port));
	String_addChar(str, ' ');
	String_addCharArr(str, Dataset_getFirstDirName(DATASET));
	String_addChar(str, ' ');
	String_addCharArr(str, Dataset_getLastDirName(DATASET));

	strcpy(request->content, String_getCharArr(str));
	String_free(str);
}

void initThreadVector()
{
	THREAD = Vector_init();
}

int acceptSocket()
{
	return x_accept(SOCKET_TO_LISTEN, (struct sockaddr*)&ADDRESS, (socklen_t*)&ADDRESS_LENGTH);
}

void createDetachedThread(void* (*threadFunc)(void*), int arg)
{
	ThreadAttr* newThread = x_calloc(1, sizeof(ThreadAttr));
	
	Vector_add(THREAD, newThread);
	newThread->arg = arg;
	x_pthread_create(&newThread->threadId, NULL, threadFunc, &newThread->arg);
	x_pthread_detach(newThread->threadId);
}

int query(char* message)
{
	if(DATASET == NULL || message == NULL)
		return 0;

	char type[TYPE_NAME_SIZE], startDate[DATE_NAME_SIZE], endDate[DATE_NAME_SIZE], city[DIRECTORY_NAME_SIZE];

	memset(type,0, TYPE_NAME_SIZE);
	memset(startDate, 0, DATE_NAME_SIZE);
	memset(endDate, 0, DATE_NAME_SIZE);
	memset(city, 0, DIRECTORY_NAME_SIZE);

	if(sscanf(message, "%s %s %s %s %s", TEMP_BUFFER_128, type, startDate, endDate, city) < 4)
		return 0;

	if(sscanf(startDate, "%d-%d-%d", &TEMP_INT, &TEMP_INT, &TEMP_INT) != 3)
		return 0;

	if(sscanf(endDate, "%d-%d-%d", &TEMP_INT, &TEMP_INT, &TEMP_INT) != 3)
		return 0;

	if(*city != '\0' && Dataset_contains(DATASET, city) == 0)
		return -1;

	return Dataset_searchByCriteria(DATASET, city, startDate, endDate, type);
}

void increaseTotalHandledRequest()
{
	++TOTAL_HANDLED_REQUEST;
}