#include "BASIS.h"

sig_atomic_t sigint_count = 0;

char *FILEPATH1ARGUMENT = NULL, *FILEPATH2ARGUMENT = NULL, *OUTPUTFILEARGUMENT = NULL;
int ARGUMENT_N = 0, ARGUMENT_M = 0;
MATRIX* MATRIXA = NULL, *MATRIXB = NULL, *MATRIXC = NULL;
MyThread* THREADS = NULL;

pthread_mutex_t mutex;
pthread_cond_t condVar;
int arrived = 0;

int handle(int, char*[]);
void printArgumentError(int);
int stringToPositiveInt(const char*);
int isDigit(char);
int checkFile(const char*);
void syncronizationBarrier();
ComplexMatrix* calculateDFM(int);

void handleArguments(int argc, char* argv[])
{
	int returnedValue = handle(argc, argv);

	if(returnedValue != 0)
	{
		printArgumentError(returnedValue);
		exit(EXIT_FAILURE);
	}
}

int handle(int argc, char* argv[])
{
	if(argc != 11)
		return 1;

	for(int opt = 0 ; (opt = getopt(argc, argv, ":i:j:o:n:m:")) != -1 ;)
		switch(opt)
		{
			case 'i': FILEPATH1ARGUMENT = optarg; break;
			case 'j': FILEPATH2ARGUMENT = optarg; break;
			case 'o': OUTPUTFILEARGUMENT = optarg; break;
			case 'n':
				if((ARGUMENT_N = stringToPositiveInt(optarg)) < 0 || ARGUMENT_N <= 2)
			 		return 5;
			 	break;
			case 'm':
				if((ARGUMENT_M = stringToPositiveInt(optarg)) < 0 || ARGUMENT_M < 2 || ARGUMENT_M % 2 != 0)
					return 6;
				break;
			case ':': // option needs a value
				return 2;
			case '?': // unknown option
				return 3;
		}

	if(optind < argc) // extra arguments
		return 4;

	if(power(2, ARGUMENT_N) % ARGUMENT_M != 0)
		return 7;

	return 0;
}

void printArgumentError(int argumentErrorNo)
{
	switch(argumentErrorNo)
	{
		case 1: fprintf(stderr, "ERROR! Usage: ./hw5 -i filePath1 -j filePath2 -o output -n 4 -m 2\n"); break;
		case 2: fprintf(stderr, "ERROR! Option needs a value...\n"); break;
		case 3: fprintf(stderr, "ERROR! Unknown option...\n"); break;
		case 4: fprintf(stderr, "ERROR! Extra arguments detected...\n"); break;
		case 5: fprintf(stderr, "ERROR! n must be n > 2\n"); break;
		case 6: fprintf(stderr, "ERROR! m must be m >= 2k, k >= 1\n"); break;
		case 7: fprintf(stderr, "ERROR! 2^n %% m must be equal 0\n"); break;
	}
}

int stringToPositiveInt(const char* string)
{
	if(string == NULL)
		return -1;

	int num = 0;

	for(int i=0 ; string[i] != '\0' ; ++i)
	{
		if(!isDigit(string[i]))
			return -1;

		num = (num * 10) + string[i] - '0';
	}

	return num;
}

int isDigit(char var) { return var >= '0' && var <= '9'; }

void changeSignalAction(void (*handler)(int), int signal)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = handler;

	x_sigfillset(&sa.sa_mask);
	x_sigaction(signal, &sa, NULL);
}

void SIGINT_handler(int signal_number) { ++sigint_count; }

void checkSIGINT()
{
	if(sigint_count)
		exit(EXIT_FAILURE);
}

void terminateProgram()
{
	if(MATRIXA != NULL)
		MATRIX_free(MATRIXA);

	if(MATRIXB != NULL)
		MATRIX_free(MATRIXB);

	if(MATRIXC != NULL)
		MATRIX_free(MATRIXC);

	if(THREADS != NULL)
	{
		free(THREADS);
		x_pthread_mutex_destroy(&mutex);
		x_pthread_cond_destroy(&condVar);
	}
}

MATRIX* readFromFile(const char* filePath)
{
	if(checkFile(filePath) != 0)
	{
		fprintf(stderr, "%s content size must be 2^n * 2^n\n", filePath);
		exit(EXIT_FAILURE);
	}

	int fd = xm_open(filePath, O_RDONLY);
	int bound = power(2, ARGUMENT_N);
	MATRIX* matrix = MATRIX_build(bound, bound);
	char* buffer = x_calloc(bound + 1, sizeof(char));

	for(int i=0 ; i < bound ; ++i)
	{
		xm_read(fd, buffer, bound);
		MATRIX_setRow(matrix, i, buffer);
	}

	free(buffer);
	xm_close(fd);
	return matrix;
}

void writeToFile(const char* filePath, void** items)
{
	int fd = xm_openm(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	char comma = ',', enter = '\n';

	for(int i=0 ; i < power(2, ARGUMENT_N) ; ++i)
	{
		for(int j=0 ; j < ARGUMENT_M ; ++j)
		{
			ComplexMatrix* item = (ComplexMatrix*)items[j];
			String* str = ComplexMatrix_rowToString(item, i, 3);

			xm_write(fd, String_getCharArr(str), String_length(str));

			if(j != ARGUMENT_M - 1)
				xm_write(fd, &comma, sizeof(char));

			String_free(str);
		}

		xm_write(fd, &enter, sizeof(char));
	}

	for(int i=0 ; i < ARGUMENT_M ; ++i)
		ComplexMatrix_free((ComplexMatrix*)items[i]);

	free(items);
	xm_close(fd);
}

int checkFile(const char* filePath)
{
	int fd = xm_open(filePath, O_RDONLY);
	int totalReadBytes = 0;
	int limit = power(power(2, ARGUMENT_N), 2);

	for(char buffer = 0 ; xm_read(fd, &buffer, sizeof(char)) ;)
		if(++totalReadBytes >= limit)
		{
			xm_close(fd);
			return 0;
		}

	return -1;
}

int power(int base, int exponent)
{
	int res = 1;

	for(int i=0 ; i < exponent ; ++i)
		res *= base;

	return res;
}

void buildHelperVariable()
{
	MATRIXC = MATRIX_build(power(2, ARGUMENT_N), power(2, ARGUMENT_N));
}

void buildMutexAndConditionalVariable()
{
	x_pthread_mutex_init(&mutex, NULL);
	x_pthread_cond_init(&condVar, NULL);
}

void buildThreads(MyThread* threads, void* (*func)(void*))
{
	for(int i=0 ; i < ARGUMENT_M ; ++i)
	{
		threads[i].i = i;
		x_pthread_create(&threads[i].thread, NULL, func, &threads[i].i);
	}
}

void** joinThreads(MyThread* threads)
{
	void** res = x_calloc(ARGUMENT_M, sizeof(void*));

	for(int i=0 ; i < ARGUMENT_M ; ++i)
		x_pthread_join(threads[i].thread, &res[i]);

	return res;
}

void* ThreadFunc(void* arg)
{
	clock_t t = clock();
	int param = *(int*)arg;
	int rowNum = power(2, ARGUMENT_N);
	int columnNum = rowNum / ARGUMENT_M;
	int targetColStart = columnNum * param, targetColEnd = columnNum * (param + 1);

	for(int i = 0 ; i < rowNum ; ++i)
		for(int j = targetColStart ; j < targetColEnd ; ++j)
			MATRIXC->m[i][j] = MATRIX_productForOneUnit(MATRIXA, MATRIXB, i, j);

	printWithTimeStamp(stdout, "Thread %d has reached the rendezvous point in %.4lf seconds.\n", param, ((double)(clock() - t))/CLOCKS_PER_SEC);
	syncronizationBarrier();

	printWithTimeStamp(stdout, "Thread %d is advancing to the second part\n", param);
	t = clock();
	ComplexMatrix* dfm = calculateDFM(param);
	printWithTimeStamp(stdout, "Thread %d has finished the second part in %.4lf seconds.\n", param, ((double)(clock() - t))/CLOCKS_PER_SEC);
	pthread_exit((void*)dfm);
}

void syncronizationBarrier()
{
	x_pthread_mutex_lock(&mutex);

	if(++arrived < ARGUMENT_M)
		x_pthread_cond_wait(&condVar, &mutex);
	else
		x_pthread_cond_broadcast(&condVar);

	x_pthread_mutex_unlock(&mutex);
}

void printWithTimeStamp(FILE* fd, const char* format, ...)
{
	va_list args;
	int timeBufferSize = BUFFER_SIZE/4;
	char timeBuffer[timeBufferSize];
	char buffer[BUFFER_SIZE];
	time_t t = x_time(NULL);
	struct tm* ptm = localtime(&t);

	if(ptm == NULL)
		return;

	strftime(timeBuffer, timeBufferSize, "[%d/%m/%Y - %T]", ptm);
	sprintf(buffer, "%s%s", timeBuffer, format);

	va_start(args, format);
	vfprintf(fd, buffer, args);
	va_end(args);
}

ComplexMatrix* calculateDFM(int i)
{
	int rowNum = power(2, ARGUMENT_N);
	int columnNum = rowNum / ARGUMENT_M;
	int targetColStart = columnNum * i, targetColEnd = columnNum * (i + 1);

	ComplexMatrix* dfm = ComplexMatrix_build(rowNum, columnNum);

	for(int i = 0 ; i < dfm->real->row ; ++i)
		for(int j = targetColStart ; j < targetColEnd ; ++j)
		{
			double ak = 0, bk = 0;

			for(int k = 0; k < MATRIXC->row ; ++k)
				for(int l = 0 ; l < MATRIXC->column ; ++l)
				{
					double x = -2.0 * M_PI * i * k / (double)MATRIXC->column;
					double y = -2.0 * M_PI * j * l / (double)MATRIXC->row;

					ak += MATRIXC->m[k][l] * cos(x + y);
					bk += MATRIXC->m[k][l] * 1.0 * sin(x + y);
				}

			dfm->real->m[i][j - targetColStart] = ak;
			dfm->complex->m[i][j - targetColStart] = bk;
		}

	return dfm;
}