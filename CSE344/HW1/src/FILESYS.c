#include "FILESYS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int FILESYS_add_path_helper(FILESYS*, char*);
void FILESYS_print_helper(FILESYS*, int);
int FILESYS_cmp(void*, void*);
VECTOR* VECTOR_init();
int VECTOR_add(VECTOR*, void*);
int VECTOR_find(VECTOR*, void*, int (*cmp)(void*, void*));
void VECTOR_free(VECTOR*, void (*f)(void*));
void str_cpy(char* s1, char* s2);

// If an error occurs, prints error message to stderr and returns NULL. Otherwise returns FILESYS*.
FILESYS* FILESYS_init(char* data)
{
	FILESYS* f = (FILESYS*)calloc(1, sizeof(FILESYS));

	if(!f)
	{
		fprintf(stderr, "Error! Out of memory.\n");
		return NULL;
	}

	str_cpy(f->data, data);
	f->sub = VECTOR_init();

	if(!f->sub)
	{
		free(f);
		return NULL;
	}

	return f;
}

// If adding path is successfully, returns 0. Otherwise error message printed and returns -1.
int FILESYS_add_path(FILESYS* f, char* path)
{
	if(f == NULL || path == NULL)
		return -1;

	int len = strlen(f->data);

	if(strncmp(f->data, path, len) != 0 || (path[len-1] != '/' && path[len] != '/'))
		return -1;

	return FILESYS_add_path_helper(f, path + len);
}

int FILESYS_add_path_helper(FILESYS* f, char* path)
{
	VECTOR* iter = f->sub;
	char* p = (char*)calloc(strlen(path) + 1, sizeof(char));

	if(!p)
	{
		fprintf(stderr, "Out of memory\n");
		return -1;
	}

	strcpy(p, path);

	for(char* delim = "/", *token = strtok(p, delim) ; token ; token = strtok(NULL, delim))
	{
		int i = VECTOR_find(iter, token, FILESYS_cmp);
		
		if(i != -1)
			iter = ((FILESYS*)iter->item[i])->sub;
		else
		{
			FILESYS* fNew = FILESYS_init(token);

			if(!fNew)
				return -1;

			if(VECTOR_add(iter, fNew) != 0)
				return -1;

			iter = ((FILESYS*)iter->item[iter->size - 1])->sub;
		}
	}

	free(p);
	return 0;
}

void FILESYS_print(FILESYS* f)
{
	if(f == NULL)
		return;

	FILESYS_print_helper(f, 0);
}

void FILESYS_print_helper(FILESYS* f, int indent)
{
	if(indent)
		printf("|");

	for(int i = 0 ; i < indent ; ++i)
		printf("--");

	printf("%s\n", f->data);

	for(int i=0 ; i < f->sub->size ; ++i)
		FILESYS_print_helper(f->sub->item[i], indent + 1);
}

int FILESYS_cmp(void* v1, void* v2)
{
	if(v1 == NULL || v2 == NULL)
		return -1;

	return strcmp(((FILESYS*)v1)->data, ((FILESYS*)v2)->data);
}

void FILESYS_free(void* f)
{
	if(f == NULL)
		return;

	VECTOR_free(((FILESYS*)f)->sub, FILESYS_free);
	free(f);
}

// If an error occurs, prints error message to stderr and returns NULL. Otherwise returns VECTOR*.
VECTOR* VECTOR_init()
{
	VECTOR* v = (VECTOR*) malloc(sizeof(VECTOR));

	if(!v)
	{
		fprintf(stderr, "Error! Out of memory.\n");
		return NULL;
	}

	v->size = 0;
	v->capacity = 1;
	v->item = malloc(sizeof(void*));

	if(!v->item)
	{
		fprintf(stderr, "Error! Out of memory.\n");
		free(v);
		return NULL;
	}

	return v;
}

// If an error occurs, prints error message to stderr and returns -1. Otherwise returns 0.
int VECTOR_add(VECTOR* v, void* item)
{
	if(!v)
		return -1;

	if(v->size > UINT_MAX)
	{
		fprintf(stderr, "Error! Vector size has reached its maximum size.\n");
		return -1;
	}

	if(v->size == v->capacity)
	{
		int tmpCap = v->capacity > UINT_MAX / 2 ? UINT_MAX : v->capacity * 2 ;
		void** tmp = realloc(v->item, sizeof(void*) * tmpCap);

		if(!tmp)
		{
			fprintf(stderr, "Error! Out of memory.\n");
			return -1;
		}

		v->capacity = tmpCap;
		v->item = tmp;
	}

	v->item[v->size++] = item;
	return 0;
}

// cmp function must return 0 if parameters are equal.
// If vector contains the item, returns its index. Otherwise -1.
int VECTOR_find(VECTOR* v, void* item, int (*cmp)(void*, void*))
{
	if(v == NULL || cmp == NULL)
		return -1;

	for(int i = 0 ; i < v->size ; ++i)
		if(cmp(v->item[i], item) == 0)
			return i;

	return -1;
}

void VECTOR_free(VECTOR* v, void (*f)(void*))
{
	if(v == NULL)
		return;

	for(int i = 0 ; i < v->size ; ++i)
		f(v->item[i]);

	free(v->item);
	free(v);
}

void str_cpy(char* s1, char* s2)
{
	while(s1 && s2 && (*s1++ = *s2++));
}