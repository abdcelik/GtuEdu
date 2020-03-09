#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

struct Node
{
    int var;
    struct Node* next;
};

void create(struct Node**);
int winner(struct Node**,int);
void add(struct Node**,int);
bool erase(struct Node**,int);
int size(struct Node**);
void print(struct Node**);
void delete(struct Node**);
int getInt(const char*);

int main(void)
{
    struct Node* node = NULL;
    int deleteNum=0,status=0;
    bool exit = false;

    create(&node);
    print(&node);

    while(!exit)
    {
        deleteNum = getInt("Delete number : ");
        if((status = winner(&node,deleteNum)) == -1)
            printf("%d is eliminated\n",deleteNum);
        else
        {
            exit = true;
            printf("%d is winner!\n",status);
        }

        print(&node);
    }

    delete(&node);
    return 0;
}

void create(struct Node** head)
{
    for(int i=0 ; i < 10 ; ++i)
        add(head,10-i);
}

int winner(struct Node** node, int delete)
{
    if(!(*node))
        return -1;

    if(!erase(node,delete))
        return -1;

    if(size(node) == 1)
        return (*node)->var;

    return -1;
}

bool erase(struct Node** node, int delete)
{
    if(!(*node))
        return false;
    
    struct Node* temp = *node;

    if((*node)->var == delete)
        *node = (*node)->next;
    else
    {
        struct Node* iter = *node;

        for(; iter->next && iter->next->var != delete ; iter = iter->next);

        temp = iter->next;
        iter->next = temp->next;
    }

    free(temp);
    return true;
}

int size(struct Node** node)
{
    if(!(*node))
        return 0;

    struct Node* iter = *node;
    int len=0;

    for(; iter ; ++len , iter = iter->next);

    return len;
}

void add(struct Node** node, int var)
{
    if(!(*node))
    {
        *node = (struct Node*)calloc(1,sizeof(struct Node));
        (*node)->var = var;
    }
    else
    {
        struct Node* newNode = (struct Node*)calloc(1,sizeof(struct Node));
        newNode->var = var;
        newNode->next = *node;
        *node = newNode;
    }
}

void print(struct Node** node)
{
    if(!(*node))
        return;

    struct Node* iter = *node;

    for(; iter ; iter = iter->next)
        printf("%d ",iter->var);
    printf("\n");
}

void delete(struct Node** node)
{
    if(!(*node))
    {
        delete(&(*node)->next);
        free(*node);
    }
}

int getInt(const char* text)
{
    int var=0;

    printf("%s",text);
    scanf("%d",&var);

    return var;
}