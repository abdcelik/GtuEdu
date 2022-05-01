#ifndef _DEAMON_H_
#define _DEAMON_H_

#include "LIB.h"
#include <sys/stat.h>

#define D_NO_CHDIR				01
#define D_NO_CLOSE_FILES		02
#define D_NO_REOPEN_STD_FDS		04
#define D_NO_UMASK0				010
#define D_MAX_CLOSE				8192

int becomeDeamon(int flags);

#endif