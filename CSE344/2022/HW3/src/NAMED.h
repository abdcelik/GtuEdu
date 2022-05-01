#ifndef _NAMED_H_
#define _NAMED_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "LIB.h"

#define FALSE 0
#define TRUE 1

#define SHMFILENAME "shmfile_for_named_part"
#define SHMFILELENGTH 4096	//byte

#define NUMBEROFINGREDIENTS 4
#define NUMBEROFCHEFS 6
#define NUMBEROFSEMAPHORE 13
#define SIZE 256

#define TEMPLATE_CHEF_INITIALLY "chef%d (pid %d) is waiting for %s and %s."
#define TEMPLATE_CHEF_OBTAIN_INGREDIENTS "chef%d (pid %d) has taken the %s."
#define TEMPLATE_CHEF_PREPARE "chef%d (pid %d) is preparing the dessert."
#define TEMPLATE_CHEF_DELIVER "chef%d (pid %d) has delivered the dessert."
#define TEMPLATE_CHEF_EXIT "chef%d (pid %d) is exiting."

#define TEMPLATE_WHOLESALER_DELIVER "the wholesaler (pid %d) delivers %s and %s."
#define TEMPLATE_WHOLESALER_WAIT "the wholesaler (pid %d) is waiting for the dessert."
#define TEMPLATE_WHOLESALER_OBTAIN "the wholesaler (pid %d) has obtained the dessert and left."
#define TEMPLATE_WHOLESALER_DONE "the wholesaler (pid %d) is done (total desserts: %d)."

struct SHMCONTENT
{
	char ingredients[2];
	int isMilk, isFlour, isWalnuts, isSugar;
	int isThereIngredients;
	int isFinish;
};

extern char* INPUTFILEPATH;

extern int mainPID, wholesalerPID;
extern pid_t* child;

extern int shmFd, inputFileFd;
extern struct SHMCONTENT* shm;

void handleArguments(int argc, char* argv[]);
void initializeSharedMemory();
void initializeSemaphores();
void terminateProgram();
void readAndPlaceShm();
void wholesaler();

void changeSignalAction(void (*handler)(int), int signal);
void checkParentSignal();
void SIGINT_handler(int signal_number);
void SIGUSR1_handler(int);

#endif