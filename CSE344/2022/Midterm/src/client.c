#include "CLIENTBASIS.h"

sig_atomic_t sigint_count = 0;
STRING* message = NULL;
char* matrix = NULL;
int serverFd = -1, clientFd = -1;

void SIGINT_handler(int signal_number) { ++sigint_count; }
void checkSIGINT();
void byeClient();

int main(int argc, char* argv[])
{
	int returnVal = 0, matrixSize = 0, messageLength = 0, temp = 0;
	char buffer[BUFFER_SIZE];
	char chrBuffer = 0;
	time_t t0, t1;
	struct tm* ptm = NULL;

	if(handleArguments(argc, argv) != 0)
	{
		printArgumentError();
		exit(EXIT_FAILURE);
	}

	changeAction(SIGINT_handler, SIGINT);
	buildClientFifoName(getpid());
	umask(0);

	NO_EINTR(returnVal = mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP));

	if(returnVal == -1 && errno != EEXIST)
	{
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	if(atexit(byeClient) != 0)
	{
		fprintf(stderr, "Cannot set exit function...\n");
		exit(EXIT_FAILURE);
	}

	checkSIGINT();

	matrix = readData();
	matrixSize = mySqrt((countComma(matrix) + 1));
	temp = STRING_len(clientFifo) + STRING_len(matrix) + 2;
	messageLength = temp + countDigit(temp);
	message = STRING_build(); // totallength.pid.matrix
	
	STRING_addInt(message, messageLength);
	STRING_addChar(message, '.');
	STRING_addCharArr(message, clientFifo);
	STRING_addChar(message, '.');
	STRING_addCharArr(message, matrix);

	t0 = time(NULL);
	ptm = localtime(&t0);
	strftime(buffer, BUFFER_SIZE, "%d/%m/%Y - %T", ptm);

	checkSIGINT();

	serverFd = x_open(SERVERFIFOPATH, O_WRONLY, "Opening server fifo:x_open");
	t0 = time(NULL);
	fprintf(stdout, TEMPLATE_SUBMIT_OUTPUT, buffer, getpid(), DATAFILEPATH, matrixSize, matrixSize);
	x_write(serverFd, STRING_getCharArr(message), STRING_length(message) * sizeof(char));
	clientFd = x_open(clientFifo, O_RDONLY, "Opening cliend fifo:x_open");
	x_read(clientFd, &chrBuffer, sizeof(char));

	t1 = time(NULL);
	fprintf(stdout, TEMPLATE_RECEIVE_OUTPUT, t1, getpid(), chrBuffer == '0' ? "not invertible" : "invertible", difftime(t1, t0));

	checkSIGINT();
	return 0;
}

void checkSIGINT()
{
	if(sigint_count != 0)
	{
		fprintf(stderr, "SIGINT signal is arrived. Cleaning and exiting...\n");
		exit(EXIT_FAILURE);
	}
}

void byeClient()
{
	unlink(clientFifo);

	if(serverFd != -1)
		x_close(serverFd);
	if(clientFd != -1)
		x_close(clientFd);
	if(matrix != NULL)
		free(matrix);
	if(message != NULL)
		STRING_free(message);
}