#ifndef _FILESYS_H_
#define _FILESYS_H_

struct VECTOR
{
	void** item;
	unsigned int size;
	unsigned int capacity;
};

typedef struct VECTOR VECTOR;

struct FILESYS
{
	char data[256];
	VECTOR* sub;
};

typedef struct FILESYS FILESYS;

FILESYS* FILESYS_init(char*);
int FILESYS_add_path(FILESYS*, char*);
void FILESYS_print(FILESYS*);
void FILESYS_free(void*);

#endif