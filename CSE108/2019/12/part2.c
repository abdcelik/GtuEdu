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
}LinkList;

bool reverse_nodes_between_n_to_m(LinkList*,int,int);
LinkList* newLinkList(void);
bool add(LinkList*,int);
void addHead(LinkList*,int);    // addHead func. is private. Do not use addHead function! Only use add function!
void addEnd(LinkList*,int);     // addEnd func. is private. Do not use addEnd function! Only use add function!
void printLinkList(LinkList*);
bool freeLinkList(LinkList*);
void freeNode(struct Node*);

int main(void)
{
    LinkList* linklist = newLinkList();

    for(int i=0 ; i < 10 ; ++i)
        add(linklist,i+1);

    printLinkList(linklist);

    if(!reverse_nodes_between_n_to_m(linklist,3,7))
        printf("Error!\n");

    printLinkList(linklist);
    freeLinkList(linklist);

    return 0;
}

bool reverse_nodes_between_n_to_m(LinkList* ll, int n, int m)
{
    if(!ll || ll->length == 0 || ll->length <= m || n >= m)
        return false;

    struct Node* start = NULL, *reverseStart = NULL , *reverseEnd = NULL , *end = NULL;
    struct Node* iter = ll->head;

    for(int i=0 ; iter ; ++i , iter = iter->next)
    {
        if(i == n-1)
            start = iter;
        if(i == m)
            reverseEnd = iter;
    }

    end = reverseEnd->next;
    iter = reverseEnd;

    for(int i=0 ; i < m-n ; ++i)
    {
        if(!start)
            reverseStart = ll->head;
        else
            reverseStart = start->next;

        reverseEnd = iter;

        for(int j=0 ; j < m-n-1-i ; ++j , reverseStart = reverseStart->next);
        for(int j=0 ; j < i ; ++j , reverseEnd = reverseEnd->next);

        reverseEnd->next = reverseStart;
    }

    if(!start)
        ll->head = iter;
    else
        start->next = iter;

    reverseStart->next = end;

    return true;
}

LinkList* newLinkList(void)
{
    return (LinkList*)calloc(1,sizeof(LinkList));
}

bool add(LinkList* ll, int var)
{
    if(!ll)
        return false;

    if(!ll->head)
        addHead(ll,var);
    else
        addEnd(ll,var);
    
    return true;
}

void addHead(LinkList* ll, int var)
{
    if(!ll || ll->head)
        return;

    ll->head = (struct Node*)calloc(1,sizeof(struct Node));
    ll->head->var = var;
    ll->length++;
}

void addEnd(LinkList* ll, int var)
{
    if(!ll || !ll->head)
        return;

    struct Node* iter = ll->head;

    for(int i=0 ; i < ll->length-1 ; ++i , iter = iter->next);

    iter->next = (struct Node*)calloc(1,sizeof(struct Node));
    iter->next->var = var;
    ll->length++;
}

void printLinkList(LinkList* ll)
{
    if(!ll)
        return;

    struct Node* iter = ll->head;

    printf("Length : %d\n",ll->length);
    
    if(!iter)
        return;

    for(int i=0 ; i < ll->length ; ++i , iter = iter->next)
        printf("%d ",iter->var);
    printf("\n");
}

bool freeLinkList(LinkList* ll)
{
    if(!ll)
        return false;

    freeNode(ll->head);
    free(ll);
    return true;
}

void freeNode(struct Node* node)
{
    if(node)
    {
        freeNode(node->next);
        free(node);
    }
}