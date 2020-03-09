#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

struct Node
{
    int var;
    struct Node* next;
};

typedef struct
{
    int length;
    struct Node* head;
}Queue;

Queue* newQueue(void);
bool print_queue(Queue*);
bool enqueue(Queue*,int);
int dequeue(Queue*);
void freeQueue(Queue*);
int getInt(const char*);

int main(void)
{
    Queue* queue = newQueue();
    int choice=0,var=0;
    bool exit = false;

    printf("Queue Operations :\n");
    printf("1. Print Queue\n");
    printf("2. Enqueue\n");
    printf("3. Dequeue\n");
    printf("9. Exit\n");

    while(!exit)
    {
        choice = getInt("Choice : ");

        switch(choice)
        {
            case 1:
                if(!print_queue(queue))
                    printf("(empty)\n");
                break;
            case 2:
                if(enqueue(queue,getInt("Input : ")))
                    printf("Successful!\n");
                else
                    printf("Invalid input(<= 0) or queue has not initialized!\n");
                break;
            case 3:
                if((var = dequeue(queue)) == -1)
                    printf("(empty)\n");
                else
                    printf("Output : %d\n",var);
                break;
            case 9:
                exit = true;
                break;
            default:
                printf("Invalid choice! Try Again!\n");
        }
    }
    
    return 0;
}

bool print_queue(Queue* queue)
{
    if(!queue || queue->length == 0)
        return false;

    struct Node* iter = queue->head;

    for(; iter ; iter = iter->next)
        printf("%d ",iter->var);
    printf("\n");

    return true;
}

bool enqueue(Queue* queue, int var)
{
    if(!queue || var <= 0)
        return false;

    struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
    node->var = var;
    node->next = queue->head;

    queue->head = node;
    queue->length++;

    return true;
}

int dequeue(Queue* queue)
{
    if(!queue || queue->length == 0)
        return -1;
    
    struct Node* iter = queue->head;
    int var=0;

    for(int i=0 ; i < queue->length-1 ; ++i , iter = iter->next);

    var = iter->var;
    queue->length--;
    free(iter);

    if(queue->length == 0)
        queue->head = NULL;
    else
    {
        iter = queue->head;
        for(int i=0 ; i < queue->length-1  ; ++i , iter = iter->next);
        iter->next = NULL;
    }

    return var;
}

Queue* newQueue(void)
{
    return (Queue*)calloc(1,sizeof(Queue));
}

void freeQueue(Queue* queue)
{
    if(queue)
    {
        for(; dequeue(queue) != -1 ;);
        free(queue);
    }
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}