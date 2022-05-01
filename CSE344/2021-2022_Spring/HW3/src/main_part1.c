#include "UNNAMED.h"

int main(int argc, char* argv[])
{
	handleArguments(argc, argv);

	mainPID = getpid();
	x_atexit(terminateProgram);
	changeSignalAction(SIGINT_handler, SIGINT);

	shmFd = x_shm_open(SHMFILENAME, O_RDWR | O_CREAT, 0);
	xm_ftruncate(shmFd, SHMFILELENGTH);
	shm = x_mmap(NULL, SHMFILELENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0);
	inputFileFd = xm_open(INPUTFILEPATH, O_RDONLY);

	initializeSharedMemory();
	checkParentSignal();

	switch(wholesalerPID = xm_fork())
	{
		case  0:
			changeSignalAction(SIGUSR1_handler, SIGUSR1);
			wholesaler();

		default:
			break;
	}

	checkParentSignal();
	readAndPlaceShm();

	xm_wait(NULL);
	return 0;
}