#ifndef _SRCH_BASIS_H_
#define _SRCH_BASIS_H_

#include "FILESYS.h"
#include <signal.h>

extern char* ARG_PATH, *ARG_FILENAME, *ARG_FILETYPE;
extern int ARG_PERMISSIONS, ARG_FILESIZE, ARG_NUMBEROFLINKS;
extern sig_atomic_t sigint_val;

char* set_arguments(int, char*[]);
int findByCriteria(FILESYS*);

#endif