#include "DEAMON.h"

int becomeDeamon(int flags)
{
	switch(fork())
	{
		case -1:	return -1;
		case  0:	break;
		default:	exit(EXIT_SUCCESS);
	}

	if(setsid() == -1)
		return -1;

	switch(fork())
	{
		case -1:	return -1;
		case  0:	break;
		default:	exit(EXIT_SUCCESS);
	}

	if(!(flags & D_NO_UMASK0))
		umask(0);

	if(!(flags & D_NO_CLOSE_FILES))
	{
		int maxfd = 3;

		for(int fd = 0; fd < maxfd ; ++fd)
			x_close(fd);
	}

	return getpid();
}