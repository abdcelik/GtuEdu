#include "Vector.h"

struct Vector
{
	void** item;
	unsigned int size;
	unsigned int capacity;
};

Vector* Vector_init()
{
	Vector* vector = calloc(1, sizeof(Vector));

	if(vector == NULL)
		return NULL;

	vector->capacity = 1;
	vector->item = calloc(vector->capacity, sizeof(void*));

	if(vector->item == NULL)
	{
		free(vector);
		return NULL;
	}

	return vector;
}

void Vector_free(Vector* vector, void (*freeVectorItem)(void*))
{
	if(vector == NULL)
		return;

	for(int i = 0 ; i < vector->size ; ++i)
		freeVectorItem(vector->item[i]);

	free(vector->item);
	free(vector);
}

int Vector_add(Vector* vector, void* item)
{
	if(vector == NULL)
		return -1;

	if(vector->size >= UINT_MAX)
		return -2;

	if(vector->size == vector->capacity)
	{
		int tempCapacity = vector->capacity > UINT_MAX / 2 ? UINT_MAX : vector->capacity * 2;
		void** tempItem = realloc(vector->item, sizeof(void*) * tempCapacity);

		if(tempItem == NULL)
			return -2;

		vector->capacity = tempCapacity;
		vector->item = tempItem;
	}

	vector->item[vector->size++] = item;
	return 0;
}

void* Vector_remove(Vector* vector, int index)
{
	if(vector == NULL)
		return NULL;

	if(index < 0 || index >= vector->size)
		return NULL;

	void* returnPtr = vector->item[index];

	for(int i = index ; i < vector->size - 1 ; ++i)
		vector->item[i] = vector->item[i + 1];

	--vector->size;
	return returnPtr; 
}

int Vector_size(Vector* vector)
{
	if(vector == NULL)
		return -1;

	return vector->size;
}

void* Vector_get(Vector* vector, int index)
{
	if(vector == NULL)
		return NULL;

	if(index < 0 || index >= vector->size)
		return NULL;

	return vector->item[index];
}

void Vector_print(Vector* vector, void (*printVectorItem)(void*))
{
	if(vector == NULL || printVectorItem == NULL)
		return;

	for(int i = 0 ; i < vector->size ; ++i)
	{
		printVectorItem(vector->item[i]);
		printf("\n");
	}
}