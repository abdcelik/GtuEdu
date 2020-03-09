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
bool print_stack(Stack*);
bool push(Stack*,int);
int pop(Stack*);
void freeStack(Stack*);
int getInt(const char*);

int main(void)
{
    Stack* stack = newStack();
    int choice=0,var=0;
    bool exit = false;

    printf("Stack Operations :\n");
    printf("1. Print Stack\n");
    printf("2. Push Stack\n");
    printf("3. Pop Stack\n");
    printf("9. Exit\n");

    while(!exit)
    {
        choice = getInt("Choice : ");

        switch(choice)
        {
            case 1:
                if(!print_stack(stack))
                    printf("(empty)\n");
                break;
            case 2:
                if(push(stack,getInt("Input : ")))
                    printf("Successful!\n");
                else
                    printf("Invalid input(<= 0) or stack has not initialized!\n");
                break;
            case 3:
                if((var = pop(stack)) == -1)
                    printf("(empty)\n");
                else
                    printf("Output : %d\n",var);
                break;
            case 9:
                exit = true;
                break;
            default:
                printf("Invalid choice! Try again!\n");
                break;
        }
    }

    freeStack(stack);
    return 0;
}

Stack* newStack(void)
{
    return (Stack*)calloc(1,sizeof(Stack));
}

bool print_stack(Stack* stack)
{
    if(!stack || stack->length == 0)
        return false;

    struct Node* iter = stack->head;

    for(; iter ; iter = iter->next)
        printf("%d ",iter->var);
    printf("\n");

    return true;
}

bool push(Stack* stack, int var)
{
    if(!stack || var <= 0)
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
    
    struct Node* temp = stack->head;
    int var = temp->var;

    stack->head = temp->next;
    stack->length--;

    free(temp);
    return var;
}

void freeStack(Stack* stack)
{
    if(stack)
    {
        for(; pop(stack) != -1 ;);
        free(stack);
    }
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}