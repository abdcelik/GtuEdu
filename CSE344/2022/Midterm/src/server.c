#include "SERVERBASIS.h"

sig_atomic_t sigint_count = 0;

void serverY_child(int indexOfChild);

int main(int argc, char* argv[])
{
	int sharedMemFd = 0;

	if(handleArguments(argc, argv) != 0)
	{
		printArgumentError();
		exit(EXIT_FAILURE);
	}

	if(becomeDeamon(0) == -1)
		exit(EXIT_FAILURE);

	logFd = x_openm(LOGFILEPATH, O_WRONLY | O_CREAT | O_TRUNC, 0777, "Opening log fifo:x_open");

	takeMeasureAgainstDoubleInitiation();
	changeAction(SIGINT_handler, SIGINT);

	serverZ_create();

	sharedMemFd = x_shm_open(SHARED_MEMORY_FILENAME, O_RDWR | O_CREAT, 0, logFd);
	shm_unlink(SHARED_MEMORY_FILENAME);

	sharedMemLen = (poolSizeOfServerY + 1) * sizeof(int); // +1 for isInverible
	x_mftruncate(sharedMemFd, sharedMemLen);

	sharedMemAddr = x_mmap(NULL, sharedMemLen, PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemFd, 0, logFd);
	memset(sharedMemAddr, 0, sharedMemLen);

	child = createChild(poolSizeOfServerY);
	buildAndSetChildPipe(child);

	for(int i=0 ; i < poolSizeOfServerY ; ++i)
		switch(child[i].id = x_fork())
		{
			case  0: serverY_child(i);
			default: x_close(child[i].filedes[PIPE_READ_END]); break;
		}

	x_atexit(serverY_bye);
	serverY_checkSIGINT();

	serverY_makeServerFifo();
	serverFd = x_open(SERVERFIFOPATH, O_RDONLY, "Opening server fifo:x_open");
	dummyFd = x_open(SERVERFIFOPATH, O_WRONLY, "Opening dummy file:x_open");

	mydprint(logFd, TEMPLATE_SERVERY_START, LOGFILEPATH, poolSizeOfServerY, sleepDuration);

	do
	{
		char* message;

		if((message = getMessage(serverFd)) == NULL)
		{
			serverY_checkSIGINT();
			continue;
		}

		int availableIndex;

		++totalRequest;

		if((availableIndex = serverY_findAvailableWorkerIndex()) == -1)
		{
			++totalForwardedRequest;
			x_write(pipeYZ[PIPE_WRITE_END], message, STRING_len(message));
		}
		else
			x_write(child[availableIndex].filedes[PIPE_WRITE_END], message, STRING_len(message));

		free(message);
		serverY_checkSIGINT();

	} while(TRUE);

	for(int i=0 ; i < poolSizeOfServerY + 1 ; ++i)
		wait(NULL);

	serverY_checkSIGINT();
	return 0;
}