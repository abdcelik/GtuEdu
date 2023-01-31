#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <limits.h>

typedef struct Queue Queue;

Queue* Queue_init();
void Queue_free(Queue* queue);
int Queue_offer(Queue* queue, int item);
int Queue_poll(Queue* queue);
int Queue_size(Queue* queue);

#endif