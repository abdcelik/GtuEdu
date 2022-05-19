#include "BASIS.h"

int main(int argc, char *argv[])
{
	clock_t t = clock();

	x_setvbuf(stdout, NULL, _IONBF, 0);
	handleArguments(argc, argv);
	changeSignalAction(SIGINT_handler, SIGINT);
	x_atexit(terminateProgram);

	checkSIGINT();

	MATRIXA = readFromFile(FILEPATH1ARGUMENT);
	MATRIXB = readFromFile(FILEPATH2ARGUMENT);

	printWithTimeStamp(stdout, "Two matrices of size %dx%d have been read. The number of thread is %d\n", power(2, ARGUMENT_N), power(2, ARGUMENT_N), ARGUMENT_M);
	checkSIGINT();
	
	buildHelperVariable();
	buildMutexAndConditionalVariable();
	THREADS = x_calloc(ARGUMENT_M, sizeof(MyThread));

	checkSIGINT();

	buildThreads(THREADS, ThreadFunc);
	void** res = joinThreads(THREADS);
	writeToFile(OUTPUTFILEARGUMENT, res);

	printWithTimeStamp(stdout, "The process has written the output file. The total time spent is %.3lf seconds.\n", ((double)(clock() - t))/CLOCKS_PER_SEC);
	return 0;
}