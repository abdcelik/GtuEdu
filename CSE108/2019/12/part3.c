#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

typedef struct Node
{
    int var;
    struct Node* next;
}Node;

typedef struct
{
    int length;
    Node* head;
}LinkList;

LinkList* createLinkList(void);
bool add(LinkList*,int);
int calculateSum(LinkList*);
void freeLinkList(LinkList*);
void freeNode(Node*);

int main(void)
{
    LinkList* linkList = createLinkList();

    for(int i=0 ; i < 10 ; ++i)
        add(linkList,i+1);

    printf("%d\n",calculateSum(linkList));
    
    freeLinkList(linkList);
    return 0;
}

LinkList* createLinkList(void)
{
    return (LinkList*)calloc(1,sizeof(LinkList));
}

bool add(LinkList* ll, int var)
{
    if(!ll)
        return false;

    Node* temp = NULL;

    if(!ll->head)
    {
        ll->head = (Node*)calloc(1,sizeof(Node));
        temp = ll->head;
    }
    else
    {
        temp = ll->head;

        for(int i=0 ; i < ll->length-1 ; ++i , temp = temp->next);

        temp->next = (Node*)calloc(1,sizeof(Node));
        temp = temp->next;
    }
   
    temp->var = var;
    ll->length++;

    return true;
}

int calculateSum(LinkList* ll)
{
    if(!ll || !ll->head)
        return false;
    
    Node* temp = ll->head;
    int sum=0;

    for(int i=0 ; i < ll->length ; ++i , temp = temp->next)
        sum += temp->var;

    return sum;
}

void freeLinkList(LinkList* ll)
{
    if(ll)
    {
        free(ll->head);
        free(ll);
    }
}

void freeNode(Node* node)
{
    if(node)
    {
        freeNode(node->next);
        free(node);
    }
}