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
}Stack;

Stack* newStack(void);
void insertAtEnd(Stack*,int);
bool push(Stack*,int);
int pop(Stack*);
void reverseStack(Stack*);
void printStack(Stack*);
void freeStack(Stack*);

int main(void)
{
    Stack* stack = newStack();

    for(int i=0 ; i < 3 ; ++i)
        push(stack,i+1);

    printStack(stack);
    
    reverseStack(stack);
    printStack(stack);

    freeStack(stack);
    return 0;
}

Stack* newStack(void)
{
    return (Stack*)calloc(1,sizeof(Stack));
}

bool push(Stack* stack, int var)
{
    if(!stack)
        return false;
    
    struct Node* node = (struct Node*)calloc(1,sizeof(struct Node));
    node->var = var;
    node->next = stack->head;

    stack->head = node;
    stack->length++;
    
    return true;
}

int pop(Stack* stack)
{
    if(!stack || stack->length == 0)
        return -1;
    
    struct Node* node = stack->head;
    int var = node->var;

    stack->head = stack->head->next;
    free(node);
    stack->length--;

    return var;
}

void reverseStack(Stack* stack)
{
    if(stack->length != 0)
    {
        int var = pop(stack);
        reverseStack(stack);
        insertAtEnd(stack,var);
    }
}

void insertAtEnd(Stack* stack, int var)
{
    if (stack->length == 0)
        push(stack,var);
    else
    {
        int temp = pop(stack);
        insertAtEnd(stack,var);
        push(stack,temp);
    }
}

void printStack(Stack* stack)
{
    if(!stack || stack->length == 0)
        return;

    struct Node* iter = stack->head;

    for(; iter ; iter = iter->next)
        printf("%d ",iter->var);
    printf("\n");
}

void freeStack(Stack* stack)
{
    if(stack)
    {
        for(; pop(stack) != -1 ;);
        free(stack);
    }
}