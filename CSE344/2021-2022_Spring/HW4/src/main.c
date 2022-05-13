#include "BASIS.h"

pthread_t supplier = -1;
struct ThreadAttr* consumers = NULL;

void* supplierFunc(void* arg);
void* consumerFunc(void* arg);
void terminateProgram();

int main(int argc, char* argv[])
{
	x_setvbuf(stdout, NULL, _IONBF, 0);
	handleArguments(argc, argv);
	changeSignalAction(SIGINT_handler, SIGINT);
	x_atexit(terminateProgram);

	checkSIGINT();

	buildSystemVSemaphores();
	buildDetachedSupplierThread(supplierFunc, &supplier);

	checkSIGINT();

	consumers = x_calloc(NUMBEROFCONSUMER, sizeof(struct ThreadAttr));
	buildConsumerThreads(consumerFunc, consumers);
	joinConsumerThreads(consumers);

	return 0;
}

void* supplierFunc(void* arg)
{
	char buffer = 0;
	struct sembuf sops;
	
	inputFd = xm_open(INPUTFILEPATH, O_RDONLY);

	sops.sem_op = 1;
	sops.sem_flg = 0;

	for(int loopExit = 0, bytesRead = 0 ; !loopExit ;)
	{
		bytesRead = xm_read(inputFd, &buffer, sizeof(char));

		if(bytesRead == 0)
		{
			loopExit = 1;
			continue;
		}
		
		printWithTimeStamp("Supplier: read from input a '%c'. Current amounts: %d x '1', %d x '2'.\n", buffer, x_semctl(semId, 0, GETVAL), x_semctl(semId, 1, GETVAL));
		sops.sem_num = buffer - '1';
		x_semop(semId, &sops, 1);
		printWithTimeStamp("Supplier: delivered a '%c'. Post-delivery amounts: %d x '1', %d x '2'.\n", buffer, x_semctl(semId, 0, GETVAL), x_semctl(semId, 1, GETVAL));
	}

	printWithTimeStamp("The supplier has left.\n");
	pthread_exit(EXIT_SUCCESS);
}

void* consumerFunc(void* arg)
{
	int nsops = 2;
	struct sembuf sops[nsops];

	sops[0].sem_num = 0; // Item '1'
	sops[0].sem_op = -1;
	sops[0].sem_flg = 0;

	sops[1].sem_num = 1; // Item '2'
	sops[1].sem_op = -1;
	sops[1].sem_flg = 0;

	for(int i=0 ; i < N ; ++i)
	{
		printWithTimeStamp("Consumer-%d at iteration %d (waiting). Current amounts: %d x '1', %d x '2'.\n", *(int*)arg, i, x_semctl(semId, 0, GETVAL), x_semctl(semId, 1, GETVAL));
		x_semop(semId, sops, nsops);
		printWithTimeStamp("Consumer-%d at iteration %d (consumed). Post-consumption amounts: %d x '1', %d x '2'.\n", *(int*)arg, i, x_semctl(semId, 0, GETVAL), x_semctl(semId, 1, GETVAL));
	}

	printWithTimeStamp("Consumer-%d has left.\n", *(int*)arg);
	pthread_exit(EXIT_SUCCESS);
}

void terminateProgram()
{
	if(inputFd != -1)
		xm_close(inputFd);

	if(consumers != NULL)
		free(consumers);

	destroySystemVSemaphores();
}