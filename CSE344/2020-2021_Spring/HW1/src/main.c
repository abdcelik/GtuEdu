#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "Srch_Basis.h"
#include "FILESYS.h"

sig_atomic_t sigint_val = 0;

void handler(int sig_num) { ++sigint_val; }

int main(int argc, char* argv[])
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handler;
	sigaction(SIGINT, &sa, NULL);

	char *args = set_arguments(argc, argv);

	if(args)
	{
		fprintf(stderr, "%s\n", args);
		return 1;
	}

	FILESYS* fsys = FILESYS_init(ARG_PATH);

	if(!fsys)
		exit(1);

	if(findByCriteria(fsys) != 0)
	{
		FILESYS_free(fsys);
		exit(1);
	}

	if(fsys->sub->size)
		FILESYS_print(fsys);
	else
		fprintf(stderr, "No file found.\n");

	FILESYS_free(fsys);
	return 0;
}