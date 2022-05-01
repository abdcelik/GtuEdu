#include "UNNAMED.h"

sig_atomic_t sigint_count = 0, sigusr1_count = 0;
char* INPUTFILEPATH = NULL;
int basisErrno = 0;
pid_t mainPID = 0, wholesalerPID = 0;
int shmFd = -1, inputFileFd = -1;
struct SHMCONTENT* shm = NULL;
pid_t* child = NULL;

int handle(int, char*[]);
void printArgumentError();
int chef0(int);
int chef1(int);
int chef2(int);
int chef3(int);
int chef4(int);
int chef5(int);
void pusher(char);
void pusherMilk();
void pusherFlour();
void pusherWalnuts();
void pusherSugar();
void copyIngredient(char*, char);
void printIngredientsArray();
void checkSignal();
void printWholesalerDeliver(char*, char*);
void printWholesalerWait();
void printWholesalerObtain();
void printWholesalerDone(int);
void printChefInitially(int, char*, char*);
void printChefObtain(int, char*);
void printChefPrepare(int);
void printChefDelivered(int);
void printChefExit(int);

void handleArguments(int argc, char* argv[])
{
	int returnedValue = handle(argc, argv);

	if(returnedValue != 0)
	{
		printArgumentError();
		exit(EXIT_FAILURE);
	}
}

int handle(int argc, char* argv[])
{
	if(argc != 3)
		return basisErrno = 1;

	for(int opt = 0 ; (opt = getopt(argc, argv, ":i:")) != -1 ;)
		switch(opt)
		{
			case 'i': INPUTFILEPATH = optarg; break;
			case ':': // option needs a value
				return basisErrno = 2;
			case '?': // unknown option
				return basisErrno = 3;
		}

	if(optind < argc) // extra arguments
		return basisErrno = 4;

	return 0;
}

void printArgumentError()
{
	switch(basisErrno)
	{
		case 1: fprintf(stderr, "ERROR! Usage: ./hw3unnamed -i inputFilePath\n"); break;
		case 2: fprintf(stderr, "ERROR! Option needs a value...\n"); break;
		case 3: fprintf(stderr, "ERROR! Unknown option...\n"); break;
		case 4: fprintf(stderr, "ERROR! Extra arguments detected...\n"); break;
	}
}

void initializeSharedMemory()
{
	shm->isThereIngredients = TRUE;

	x_sem_init(&shm->milk, 1, 0);
	x_sem_init(&shm->flour, 1, 0);
	x_sem_init(&shm->walnuts, 1, 0);
	x_sem_init(&shm->sugar, 1, 0);

	x_sem_init(&shm->milkAndFlour, 1, 0);
	x_sem_init(&shm->milkAndWalnuts, 1, 0);
	x_sem_init(&shm->milkAndSugar, 1, 0);
	x_sem_init(&shm->flourAndWalnuts, 1, 0);
	x_sem_init(&shm->flourAndSugar, 1, 0);
	x_sem_init(&shm->walnutsAndSugar, 1, 0);

	x_sem_init(&shm->lock, 1, 1);
	x_sem_init(&shm->parentSem, 1, 1);
	x_sem_init(&shm->wholesalerSem, 1, 0);
}

void terminateProgram()
{
	if(shm != NULL)
		x_munmap(shm, SHMFILELENGTH);

	if(shmFd != -1)
		xm_close(shmFd);

	if(inputFileFd != -1)
		xm_close(inputFileFd);

	if(mainPID == getpid())
	{
		x_sem_destroy(&shm->milk);
		x_sem_destroy(&shm->flour);
		x_sem_destroy(&shm->walnuts);
		x_sem_destroy(&shm->sugar);
		x_sem_destroy(&shm->milkAndFlour);
		x_sem_destroy(&shm->milkAndWalnuts);
		x_sem_destroy(&shm->milkAndSugar);
		x_sem_destroy(&shm->flourAndWalnuts);
		x_sem_destroy(&shm->flourAndSugar);
		x_sem_destroy(&shm->walnutsAndSugar);
		x_sem_destroy(&shm->lock);
		x_sem_destroy(&shm->parentSem);
		x_sem_destroy(&shm->wholesalerSem);

		if(shmFd != -1)
			x_shm_unlink(SHMFILENAME);

		return;
	}

	free(child);
}

void readAndPlaceShm()
{
	char buffer[3];

	for(int loopExit = 0, bytesRead = 0 ; !loopExit ;)
	{
		checkParentSignal();
		x_sem_wait(&shm->parentSem);
		checkParentSignal();

		bytesRead = xm_read(inputFileFd, buffer, sizeof(buffer));

		switch(bytesRead)
		{
			case 0:
				shm->isThereIngredients = FALSE;
				loopExit = 1;
				break;
			default:
				shm->ingredients[0] = buffer[0];
				shm->ingredients[1] = buffer[1];
				break;
		}

		x_sem_post(&shm->wholesalerSem);
	}
}

void wholesaler()
{
	char ing1Buffer[8], ing2Buffer[8];
	int totalDesserts = 0;

	child = x_calloc(NUMBEROFCHEFS + NUMBEROFINGREDIENTS, sizeof(pid_t));
	int (*chefs[])(int) = {chef0, chef1, chef2, chef3, chef4, chef5};
	void (*pushers[])() = {pusherMilk, pusherFlour, pusherWalnuts, pusherSugar};

	for(int i=0 ; i < NUMBEROFCHEFS ; ++i)
		switch(child[i] = xm_fork())
		{
			case  0:
				chefs[i](i);
				exit(EXIT_SUCCESS);

			default: break;
		}

	for(int i = NUMBEROFCHEFS ; i < NUMBEROFCHEFS + NUMBEROFINGREDIENTS ; ++i)
		switch(child[i] = xm_fork())
		{
			case  0: pushers[i - NUMBEROFCHEFS]();
			default: break;
		}

	for(int loopExit = 0 ; !loopExit ;)
	{
		checkSignal();
		x_sem_wait(&shm->wholesalerSem);
		checkSignal();

		if(shm->isThereIngredients == FALSE)
		{
			for(int i = NUMBEROFCHEFS ; i < NUMBEROFCHEFS + NUMBEROFINGREDIENTS ; ++i)
				x_kill(child[i], SIGUSR1);

			shm->isFinish = TRUE;

			x_sem_post(&shm->milkAndFlour);
			x_sem_post(&shm->milkAndWalnuts);
			x_sem_post(&shm->milkAndSugar);
			x_sem_post(&shm->flourAndWalnuts);
			x_sem_post(&shm->flourAndSugar);
			x_sem_post(&shm->walnutsAndSugar);

			loopExit = TRUE;
			continue;
		}

		copyIngredient(ing1Buffer, shm->ingredients[0]);
		copyIngredient(ing2Buffer, shm->ingredients[1]);

		printWholesalerDeliver(ing1Buffer, ing2Buffer);
		printWholesalerWait();

		pusher(shm->ingredients[0]);
		pusher(shm->ingredients[1]);

		checkSignal();
		x_sem_wait(&shm->wholesalerSem);
		checkSignal();

		printWholesalerObtain();
		x_sem_post(&shm->parentSem);
	}

	for(int i=0 , status=0 ; i < NUMBEROFCHEFS ; ++i)
	{
		xm_waitpid(child[i], &status, 0);
		totalDesserts += WEXITSTATUS(status);
	}

	for(int i=0 ; i < NUMBEROFINGREDIENTS ; ++i)
		xm_wait(NULL);

	printWholesalerDone(totalDesserts);
	exit(EXIT_SUCCESS);
}

int chef0(int index)
{
	char ing1Buffer[8], ing2Buffer[8];
	int totalDessert = 0;

	printChefInitially(index, "milk", "flour");

	for(int loopExit = FALSE ; !loopExit ;)
	{
		checkSignal();
		x_sem_wait(&shm->milkAndFlour);
		checkSignal();

		if(shm->isFinish)
		{
			loopExit = TRUE;
			continue;
		}

		copyIngredient(ing1Buffer, shm->ingredients[0]);
		copyIngredient(ing2Buffer, shm->ingredients[1]);

		shm->ingredients[0] = 0;
		printChefObtain(index, ing1Buffer);
		shm->ingredients[1] = 0;
		printChefObtain(index, ing2Buffer);

		printChefPrepare(index);
		++totalDessert;

		printChefDelivered(index);
		x_sem_post(&shm->wholesalerSem);
	}

	printChefExit(index);
	exit(totalDessert);
}

int chef1(int index)
{
	char ing1Buffer[8], ing2Buffer[8];
	int totalDessert = 0;

	printChefInitially(index, "milk", "sugar");

	for(int loopExit = FALSE ; !loopExit ;)
	{
		checkSignal();
		x_sem_wait(&shm->milkAndSugar);
		checkSignal();

		if(shm->isFinish)
		{
			loopExit = TRUE;
			continue;
		}

		copyIngredient(ing1Buffer, shm->ingredients[0]);
		copyIngredient(ing2Buffer, shm->ingredients[1]);

		shm->ingredients[0] = 0;
		printChefObtain(index, ing1Buffer);
		shm->ingredients[1] = 0;
		printChefObtain(index, ing2Buffer);

		printChefPrepare(index);
		++totalDessert;

		printChefDelivered(index);
		x_sem_post(&shm->wholesalerSem);
	}

	printChefExit(index);
	exit(totalDessert);
}

int chef2(int index)
{
	char ing1Buffer[8], ing2Buffer[8];
	int totalDessert = 0;

	printChefInitially(index, "milk", "walnuts");

	for(int loopExit = FALSE ; !loopExit ;)
	{
		checkSignal();
		x_sem_wait(&shm->milkAndWalnuts);
		checkSignal();

		if(shm->isFinish)
		{
			loopExit = TRUE;
			continue;
		}

		copyIngredient(ing1Buffer, shm->ingredients[0]);
		copyIngredient(ing2Buffer, shm->ingredients[1]);

		shm->ingredients[0] = 0;
		printChefObtain(index, ing1Buffer);
		shm->ingredients[1] = 0;
		printChefObtain(index, ing2Buffer);

		printChefPrepare(index);
		++totalDessert;

		printChefDelivered(index);
		x_sem_post(&shm->wholesalerSem);
	}

	printChefExit(index);
	exit(totalDessert);
}

int chef3(int index)
{
	char ing1Buffer[8], ing2Buffer[8];
	int totalDessert = 0;

	printChefInitially(index, "sugar", "walnuts");

	for(int loopExit = FALSE ; !loopExit ;)
	{
		checkSignal();
		x_sem_wait(&shm->walnutsAndSugar);
		checkSignal();

		if(shm->isFinish)
		{
			loopExit = TRUE;
			continue;
		}

		copyIngredient(ing1Buffer, shm->ingredients[0]);
		copyIngredient(ing2Buffer, shm->ingredients[1]);

		shm->ingredients[0] = 0;
		printChefObtain(index, ing1Buffer);
		shm->ingredients[1] = 0;
		printChefObtain(index, ing2Buffer);

		printChefPrepare(index);
		++totalDessert;

		printChefDelivered(index);
		x_sem_post(&shm->wholesalerSem);
	}

	printChefExit(index);
	exit(totalDessert);
}

int chef4(int index)
{
	char ing1Buffer[8], ing2Buffer[8];
	int totalDessert = 0;

	printChefInitially(index, "sugar", "flour");

	for(int loopExit = FALSE ; !loopExit ;)
	{
		checkSignal();
		x_sem_wait(&shm->flourAndSugar);
		checkSignal();

		if(shm->isFinish)
		{
			loopExit = TRUE;
			continue;
		}

		copyIngredient(ing1Buffer, shm->ingredients[0]);
		copyIngredient(ing2Buffer, shm->ingredients[1]);

		shm->ingredients[0] = 0;
		printChefObtain(index, ing1Buffer);
		shm->ingredients[1] = 0;
		printChefObtain(index, ing2Buffer);

		printChefPrepare(index);
		++totalDessert;

		printChefDelivered(index);
		x_sem_post(&shm->wholesalerSem);
	}

	printChefExit(index);
	exit(totalDessert);
}

int chef5(int index)
{
	char ing1Buffer[8], ing2Buffer[8];
	int totalDessert = 0;

	printChefInitially(index, "flour", "walnuts");

	for(int loopExit = FALSE ; !loopExit ;)
	{
		checkSignal();
		x_sem_wait(&shm->flourAndWalnuts);
		checkSignal();

		if(shm->isFinish)
		{
			loopExit = TRUE;
			continue;
		}

		copyIngredient(ing1Buffer, shm->ingredients[0]);
		copyIngredient(ing2Buffer, shm->ingredients[1]);

		shm->ingredients[0] = 0;
		printChefObtain(index, ing1Buffer);
		shm->ingredients[1] = 0;
		printChefObtain(index, ing2Buffer);

		printChefPrepare(index);
		++totalDessert;

		printChefDelivered(index);
		x_sem_post(&shm->wholesalerSem);
	}

	printChefExit(index);
	exit(totalDessert);
}

void pusher(char ingredient)
{
	switch(ingredient)
	{
		case 'M': x_sem_post(&shm->milk);		break;
		case 'F': x_sem_post(&shm->flour);		break;
		case 'W': x_sem_post(&shm->walnuts);	break;
		case 'S': x_sem_post(&shm->sugar);		break;
	}
}

void pusherMilk()
{
	while(TRUE)
	{
		checkSignal();
		x_sem_wait(&shm->milk);
		checkSignal();
		x_sem_wait(&shm->lock);
		checkSignal();

		if(shm->isFlour)
		{
			shm->isFlour = FALSE;
			x_sem_post(&shm->milkAndFlour);
		}
		else if(shm->isWalnuts)
		{
			shm->isWalnuts = FALSE;
			x_sem_post(&shm->milkAndWalnuts);
		}
		else if(shm->isSugar)
		{
			shm->isSugar = FALSE;
			x_sem_post(&shm->milkAndSugar);
		}
		else
			shm->isMilk = TRUE;

		x_sem_post(&shm->lock);
	}
}

void pusherFlour()
{
	while(TRUE)
	{
		checkSignal();
		x_sem_wait(&shm->flour);
		checkSignal();
		x_sem_wait(&shm->lock);
		checkSignal();

		if(shm->isMilk)
		{
			shm->isMilk = FALSE;
			x_sem_post(&shm->milkAndFlour);
		}
		else if(shm->isWalnuts)
		{
			shm->isWalnuts = FALSE;
			x_sem_post(&shm->flourAndWalnuts);
		}
		else if(shm->isSugar)
		{
			shm->isSugar = FALSE;
			x_sem_post(&shm->flourAndSugar);
		}
		else
			shm->isFlour = TRUE;

		x_sem_post(&shm->lock);
	}
}

void pusherWalnuts()
{
	while(TRUE)
	{
		checkSignal();
		x_sem_wait(&shm->walnuts);
		checkSignal();
		x_sem_wait(&shm->lock);
		checkSignal();

		if(shm->isMilk)
		{
			shm->isMilk = FALSE;
			x_sem_post(&shm->milkAndWalnuts);
		}
		else if(shm->isFlour)
		{
			shm->isFlour = FALSE;
			x_sem_post(&shm->flourAndWalnuts);
		}
		else if(shm->isSugar)
		{
			shm->isSugar = FALSE;
			x_sem_post(&shm->walnutsAndSugar);
		}
		else
			shm->isWalnuts = TRUE;

		x_sem_post(&shm->lock);
	}
}

void pusherSugar()
{
	while(TRUE)
	{
		checkSignal();
		x_sem_wait(&shm->sugar);
		checkSignal();
		x_sem_wait(&shm->lock);
		checkSignal();

		if(shm->isMilk)
		{
			shm->isMilk = FALSE;
			x_sem_post(&shm->milkAndSugar);
		}
		else if(shm->isFlour)
		{
			shm->isFlour = FALSE;
			x_sem_post(&shm->flourAndSugar);
		}
		else if(shm->isWalnuts)
		{
			shm->isWalnuts = FALSE;
			x_sem_post(&shm->walnutsAndSugar);
		}
		else
			shm->isSugar = TRUE;

		x_sem_post(&shm->lock);
	}
}

void copyIngredient(char* s1, char s2)
{
	memset(s1, 0, sizeof(*s1));

	switch(s2)
	{
		case 'M': strcpy(s1, "milk");		break;
		case 'F': strcpy(s1, "flour");		break;
		case 'W': strcpy(s1, "walnuts");	break;
		case 'S': strcpy(s1, "sugar");		break;
	}
}

void printIngredientsArray()
{
	char ing1 = shm->ingredients[0] == 0 ? ' ' : shm->ingredients[0];
	char ing2 = shm->ingredients[1] == 0 ? ' ' : shm->ingredients[1];

	fprintf(stdout, " Ingredients: [%c, %c]\n", ing1, ing2);
}

void changeSignalAction(void (*handler)(int), int signal)
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

void SIGINT_handler(int signal_number) { ++sigint_count; }

void SIGUSR1_handler(int signal_number) { ++sigusr1_count; }

void checkParentSignal()
{
	if(sigint_count != 0)
	{
		x_kill(wholesalerPID, SIGUSR1);
		exit(EXIT_FAILURE);
	}
}

void checkSignal()
{
	if(sigint_count != 0)
		x_kill(mainPID, SIGINT);
	if(sigusr1_count != 0)
		exit(EXIT_FAILURE);
}

void printWholesalerDeliver(char* ingredient1, char* ingredient2)
{
	fprintf(stdout, TEMPLATE_WHOLESALER_DELIVER, getpid(), ingredient1, ingredient2);
	printIngredientsArray();
}

void printWholesalerWait()
{
	fprintf(stdout, TEMPLATE_WHOLESALER_WAIT, getpid());
	printIngredientsArray();
}

void printWholesalerObtain()
{
	fprintf(stdout, TEMPLATE_WHOLESALER_OBTAIN, getpid());
	printIngredientsArray();
}

void printWholesalerDone(int totalDesserts)
{
	fprintf(stdout, TEMPLATE_WHOLESALER_DONE, getpid(), totalDesserts);
	printIngredientsArray();
}

void printChefInitially(int index, char* ingredient1, char* ingredient2)
{
	fprintf(stdout, TEMPLATE_CHEF_INITIALLY, index, getpid(), ingredient1, ingredient2);
	fprintf(stdout, " Ingredients: [ , ]\n");
}

void printChefObtain(int index, char* ingredient)
{
	fprintf(stdout, TEMPLATE_CHEF_OBTAIN_INGREDIENTS, index, getpid(), ingredient);
	printIngredientsArray();
}

void printChefPrepare(int index)
{
	fprintf(stdout, TEMPLATE_CHEF_PREPARE, index, getpid());
	printIngredientsArray();
}

void printChefDelivered(int index)
{
	fprintf(stdout, TEMPLATE_CHEF_DELIVER, index, getpid());
	printIngredientsArray();
}

void printChefExit(int index)
{
	fprintf(stdout, TEMPLATE_CHEF_EXIT, index, getpid());
	printIngredientsArray();
}