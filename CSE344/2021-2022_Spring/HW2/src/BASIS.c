#include "BASIS.h"

char* ARG_INPUT = NULL, *ARG_OUTPUT = NULL;
int _BASIS_ERRNO = 0;
char* ChildArgv[] = {CHLD_PROCESS_EXEC, NULL, NULL};

int setArguments(int argc, char* argv[])
{
	if(argc != 5) // prog_name in_opt in_file_name out_opt out_file_name
		return _BASIS_ERRNO = 1;

	for(int opt = 0 ; (opt = getopt(argc, argv, ":i:o:")) != -1 ;)
		switch(opt)
		{
			case 'i':	ARG_INPUT = optarg;		break;
			case 'o':	ARG_OUTPUT = ChildArgv[1] = optarg;	break;
			case ':': // option needs a value
				return _BASIS_ERRNO = 2;
			case '?': // unknown option
				return _BASIS_ERRNO = 3;
		}

	if(optind < argc) // extra arguments
		return _BASIS_ERRNO = 4;

	return 0;
}

void printArgumentError()
{
	switch(_BASIS_ERRNO)
	{
		case 1: fprintf(stderr, "ERROR! Usage: ./progName -i inputFilePath -o outputFilePath\n"); break;
		case 2: fprintf(stderr, "ERROR! Option needs a value...\n"); break;
		case 3: fprintf(stderr, "ERROR! Unknown option...\n"); break;
		case 4: fprintf(stderr, "ERROR! Extra arguments detected...\n"); break;
	}
}

void printEnvironmentVariables(char** environ, int num)
{
	fprintf(stdout, "Created R_%d with ", num);

	while(*environ)
	{
		fprintf(stdout, "%s", *environ++);

		if(*environ)
			fprintf(stdout, ",");
	}

	fprintf(stdout, "\n");
}