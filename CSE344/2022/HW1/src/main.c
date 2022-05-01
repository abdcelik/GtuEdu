#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "BASIS.h"
#include "VECTOR.h"
#include "FILE.h"

int main(int argc, char* argv[])
{
	if(checkArgument(argc, argv) != 0)
	{
		printArgumentError();
		return 0;
	}

	VECTOR* parsedRule;

	if(!(parsedRule = parseRule(argv)))
	{
		fprintf(stderr, "Error! Out of memory.\n");
		return EXIT_FAILURE;
	}

	int fd = openFile(argv[2], O_RDWR);
	int tmpfd = openTempFile();

	lockFile(fd, F_WRLCK, F_SETLKW);

	applyRule(fd, tmpfd, parsedRule);
	ftruncateFile(fd, 0);
	copyFile(fd, tmpfd);

	lockFile(fd, F_UNLCK, F_SETLKW);

	closeFile(fd);
	closeFile(tmpfd);
	VECTOR_free(parsedRule, freeRule);

	return 0;
}