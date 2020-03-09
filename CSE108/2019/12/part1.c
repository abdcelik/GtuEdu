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
}binarylist;

void bin2int_io(void);
int bin2int(binarylist*);
int convertDecimal(Node*,int);
binarylist* createBinaryList(void);
Node* newNode(int);
bool add(binarylist*,char);
char* getStr(const char*);
int power(int,int);
void freeBinaryList(binarylist*);
void freeNode(Node*);

int main(void)
{
    bin2int_io();
    return 0;
}

void bin2int_io(void)
{
    binarylist* binlist = createBinaryList();
    char* binary = getStr("Enter your binary number : ");

    for(int i=0 ; binary[i] && add(binlist,binary[i]) ; ++i);

    printf("Decimal : %d\n",bin2int(binlist));
    freeBinaryList(binlist);
}

int bin2int(binarylist* _bn)
{
    return convertDecimal(_bn->head,_bn->length);
}

int convertDecimal(Node* node, int digit)
{
    if(node)
        return power(2,digit-1) * node->var + convertDecimal(node->next,digit-1);
    return 0;
}

binarylist* createBinaryList(void)
{
    return (binarylist*)calloc(1,sizeof(binarylist));
}

Node* newNode(int var)
{
    Node* node = (Node*)calloc(1,sizeof(Node)); 

    node->var = var;
    return node;
}

bool add(binarylist* binlist, char var)
{
    if(!binlist || (var != '0' && var != '1'))
        return false;

    if(!binlist->head)
        binlist->head = newNode(var - '0');
    else
    {
        Node* temp = binlist->head;

        for(int i=0 ; i < binlist->length-1 ; ++i , temp = temp->next);

        temp->next = newNode(var - '0');
    }

    binlist->length++;
    return true;
}

char* getStr(const char* text)
{
    char* var = (char*)calloc(32,sizeof(char));

    printf("%s",text);
    scanf("%s",var);

    return var;
}

int power(int base, int exponential)
{
    int res = 1;

    for(int i=0 ; i < exponential ; ++i , res *= base);

    return res;
}

void freeBinaryList(binarylist* binlist)
{
    if(binlist)
    {
        freeNode(binlist->head);
        free(binlist);
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