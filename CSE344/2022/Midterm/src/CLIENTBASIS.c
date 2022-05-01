#include "CLIENTBASIS.h"

char* SERVERFIFOPATH = NULL, *DATAFILEPATH = NULL;
int BASIS_ERRNO = 0;

void buildClientFifoNameHelper(pid_t, int);

void changeAction(void (*handler)(int), int signal)
{
	struct sigaction sa;
	int sigactreturn = 0;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;

	if(sigfillset(&sa.sa_mask) == -1)
	{
		perror("sigset");
		exit(EXIT_FAILURE);
	}

	NO_EINTR(sigactreturn = sigaction(signal, &sa, NULL));

	if(sigactreturn == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

char* readData()
{
	int fd = x_mopen(DATAFILEPATH, O_RDONLY, "Opening data file:x_open");
	STRING* data = STRING_build();
	char buffer = 0;

	for(int exit = 0, bytes_read = 0, flag = 0 ; !exit ;)
	{
		NO_EINTR(bytes_read = read(fd, &buffer, sizeof(char)));

		if(bytes_read != 0)
		{
			if(buffer == '\n')
				flag = 1;
			else
			{
				if(flag)
				{
					STRING_addChar(data, ',');	
					flag = 0;
				}

				STRING_addChar(data, buffer);
			}
		}
		else
			exit = 1;
	}

	char* returnedData = x_calloc(STRING_length(data) + 1, sizeof(char));

	STRING_cpy(returnedData, STRING_getCharArr(data));
	STRING_free(data);
	x_close(fd);

	return returnedData;
}

void buildClientFifoName(pid_t pid)
{
	memset(clientFifo, 0, sizeof(clientFifo));
	STRING_cpy(clientFifo, TEMPLATE_CLIENT_FIFO);

	int digitNum = countDigit(pid);
	buildClientFifoNameHelper(pid, STRING_len(clientFifo) + digitNum - 1);
}

void buildClientFifoNameHelper(pid_t pid, int i)
{
	if(pid != 0)
	{
		int temp = pid % 10;
		buildClientFifoNameHelper(pid / 10, i-1);
		clientFifo[i] = temp + '0';
	}
}

int handleArguments(int argc, char* argv[])
{
	if(argc != 5)
		return BASIS_ERRNO = 1;

	for(int opt = 0 ; (opt = getopt(argc, argv, ":s:o:")) != -1 ;)
		switch(opt)
		{
			case 's':	SERVERFIFOPATH	= optarg;	break;
			case 'o':	DATAFILEPATH	= optarg;	break;
			case ':': // option needs a value
				return BASIS_ERRNO = 2;
			case '?': // unknown option
				return BASIS_ERRNO = 3;
		}

	if(optind < argc) // extra arguments
		return BASIS_ERRNO = 4;

	return 0;
}

void printArgumentError()
{
	switch(BASIS_ERRNO)
	{
		case 1: fprintf(stderr, "ERROR! Usage: ./client -s pathToServerFifo -o pathToDataFile\n"); break;
		case 2: fprintf(stderr, "ERROR! Option needs a value...\n"); break;
		case 3: fprintf(stderr, "ERROR! Unknown option...\n"); break;
		case 4: fprintf(stderr, "ERROR! Extra arguments detected...\n"); break;
	}
}

int countDigit(int var)
{
	int count = 0;

	while(var != 0)
	{
		var /= 10;
		++count;
	}

	return count;
}