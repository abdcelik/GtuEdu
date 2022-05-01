#include "FILE.h"

void lockFile(struct flock* lock, int fd, short l_type, int cmd)
{
	if(l_type != F_UNLCK)
		memset(lock, 0, sizeof(*lock));

	lock->l_type = l_type;

	if(fcntl(fd, cmd, lock) == -1)
	{
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
}

void writeFile(int fd, MATRIX* m)
{
	if(!m || fd < 0)
	{
		fprintf(stderr, "writeFile: Invalid parameters\n");
		exit(EXIT_FAILURE);
	}

	STRING* s = MATRIX_toString(m);
	STRING_addChar(s, '\n');
	char* str = STRING_getCharArr(s);

	if(write(fd, str, strlen(str)) == -1)
	{
		perror("writeFile - write:");
		exit(EXIT_FAILURE);
	}

	STRING_free(s);
}