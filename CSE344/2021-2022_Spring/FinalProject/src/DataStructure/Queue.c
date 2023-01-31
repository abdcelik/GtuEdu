#include "Queue.h"

struct Queue
{
	int* item;
	unsigned int size;
	unsigned int capacity;
};

Queue* Queue_init()
{
	Queue* queue = calloc(1, sizeof(Queue));

	if(queue == NULL)
		return NULL;

	queue->capacity = 1;
	queue->item = calloc(queue->capacity, sizeof(int));

	if(queue->item == NULL)
	{
		free(queue);
		return NULL;
	}

	return queue;
}

void Queue_free(Queue* queue)
{
	if(queue == NULL)
		return;

	free(queue->item);
	free(queue);
}

int Queue_offer(Queue* queue, int item)
{
	if(queue == NULL)
		return -1;

	if(queue->size >= UINT_MAX)
		return -2;

	if(queue->size == queue->capacity)
	{
		int tempCapacity = queue->capacity > UINT_MAX / 2 ? UINT_MAX : queue->capacity * 2;
		int* tempItem = realloc(queue->item, sizeof(int) * tempCapacity);

		if(tempItem == NULL)
			return -2;

		queue->capacity = tempCapacity;
		queue->item = tempItem;
	}

	queue->item[queue->size++] = item;
	return 0;
}

int Queue_poll(Queue* queue)
{
	if(queue == NULL || queue->size == 0)
		return -1;

	int returnedItem = queue->item[0];

	for(int i = 0 ; i < queue->size - 1 ; ++i)
		queue->item[i] = queue->item[i + 1];

	--queue->size;
	return returnedItem;
}

int Queue_size(Queue* queue)
{
	return queue == NULL ? -1 : queue->size;
}