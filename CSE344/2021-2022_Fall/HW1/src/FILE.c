#include "FILE.h"

struct flock _FILE_lock;

int openFile(const char* pathName, int flags)
{
	int fd = open(pathName, flags);

	if(fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

	return fd;
}

void closeFile(int fd)
{
	if(close(fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
}

void applyRule(int fromfd, int tofd, VECTOR* rule)
{
	unsigned char chr = 0;
	size_t bytes_read = 0;
	unsigned int capacity = 128, size = 0;
	char buffer[capacity];
	int isLineStart = 1, isLineEnd = 0;
	char* toBeWritten = NULL;

	memset(buffer, 0, sizeof(buffer));

	do
	{
		bytes_read = read(fromfd, &chr, 1);

		if(bytes_read == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		else if(bytes_read == 0)
			break;

		if(is_al_num(chr))
			buffer[size++] = chr;
		else
		{
			if(chr == '\n')
				isLineEnd = 1;

			buffer[size] = '\0';
			size = 0;
			isLineStart = 0;
			toBeWritten = buffer;

			for(int i=0 ; i < VECTOR_size(rule) ; ++i)
			{
				printf("%d %d   ", isLineStart, isLineEnd);

				if(isLineStart && ((RULE*)rule->item[i])->regex[0] != '^')
					continue;
				if(isLineEnd && ((RULE*)rule->item[i])->regex[str_len(((RULE*)rule->item[i])->regex) - 1] != '$')
					continue;

				printf("here   ");	

				if(isMatch(rule->item[i], buffer))
				{
					toBeWritten = ((RULE*)rule->item[i])->newStr;
				}
			}

			if(isLineEnd)
				isLineStart = 1;
			isLineEnd = 0;

			printf("%s.%s\n", buffer, toBeWritten);

			if(write(tofd, toBeWritten, strlen(toBeWritten)) == -1 || write(tofd, &chr, 1) == -1)
			{
				perror("write");
				exit(EXIT_FAILURE);
			}
		}
	}while(bytes_read > 0);
}

void lockFile(int fd, short l_type, int cmd)
{
	if(l_type != F_UNLCK)
		memset(&_FILE_lock, 0, sizeof(_FILE_lock));

	_FILE_lock.l_type = l_type;

	if(fcntl(fd, cmd, &_FILE_lock) == -1)
	{
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
}

void copyFile(int targetFd, int srcFd)
{
	if(lseek(srcFd, 0, SEEK_SET) == -1 || lseek(targetFd, 0, SEEK_SET) == -1)
	{
		perror("lseek");
		exit(EXIT_FAILURE);
	}

	char buffer = 0;
	int bytes_read = 0;

	do
	{
		bytes_read = read(srcFd, &buffer, 1);

		if(bytes_read == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		if(bytes_read > 0 && write(targetFd, &buffer, 1) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

	}while(bytes_read > 0);
}

void ftruncateFile(int fd, off_t length)
{
	if(ftruncate(fd, length) == -1)
	{
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}
}

int openTempFile()
{
	char fileName[] = "temp-XXXXXX";
	int tmpfd = mkstemp(fileName);

	if(tmpfd == -1)
	{
		perror("mkstemp");
		exit(EXIT_FAILURE);
	}

	if(unlink(fileName) == -1)
	{
		perror("unlink");
		exit(EXIT_FAILURE);
	}

	return tmpfd;
}