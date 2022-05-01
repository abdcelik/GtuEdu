#include "VECTOR.h"

VECTOR* VECTOR_init()
{
	VECTOR* v = x_malloc(sizeof(VECTOR));

	v->size = 0;
	v->capacity = 1;
	v->item = x_malloc(sizeof(void*));

	return v;
}

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

int VECTOR_size(VECTOR* v)
{
	if(v == NULL)
		return -1;

	return v->size;
}

void VECTOR_print(VECTOR* v, void (*f)(void*))
{
	if(!v)
		return;

	for(int i=0 ; i < v->size ; ++i)
	{
		f(v->item[i]);
		printf("\n");
	}
}

void VECTOR_print_str(void* s)
{
	printf("%s", (char*)s);
}

void VECTOR_free(VECTOR* v, void (*f)(void*))
{
	if(!v)
		return;

	for(int i = 0 ; i < v->size ; ++i)
		f(v->item[i]);

	free(v->item);
	free(v);
}

void VECTOR_free_str(void* s)
{
	free(s);
}