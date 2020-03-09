#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;

typedef struct Item
{
    char* itemName;
    struct Item* next;
}Item;

typedef struct Queue
{
    int length;
    struct Item* head;
}Queue;

typedef struct
{
    char* data[5];
}Lesson;

bool fill_queue(char*,Queue*);
bool add_queue(Queue*,Item*);
Lesson* generate_course(char*);
Item* generate_item(char*);
void print_queue(Queue*,int);
void print(Lesson*);
char* strTok(char*,const char*);
Queue* newQueue(void);
void freeQueue(Queue*);
void freeItem(Item*);
void strCpy(char*,char*);
int strLen(const char*);

int main(void)
{
    Queue* queue = newQueue();

    if(!fill_queue("text.txt",queue))
        printf("Filling could not be done!\n");
    print_queue(queue,0);

    freeQueue(queue);
    return 0;
}

bool fill_queue(char* fileName, Queue* course_queue)
{
    FILE *fp = fopen(fileName,"r+");
    char buffer[255] = {0};

    if(!fp)
        return false;

    while(!feof(fp))
    {
        fscanf(fp,"%[^;]s",buffer);

        if(!feof(fp))
            if(!add_queue(course_queue,generate_item(buffer)))
                printf("Adding queue could not successful!\n");

        fgetc(fp);
        fgetc(fp);
    }

    fclose(fp);
    return true;
}

bool add_queue(Queue* queue, Item* item)
{
    if(!queue || !item)
        return false;
    
    item->next = queue->head;
    queue->head = item;
    queue->length++;
    
    return true;
}

Lesson* generate_course(char* line)
{
    Lesson* lesson = (Lesson*)calloc(1,sizeof(Lesson));
    char* temp = NULL , *txt = line;
    
    for(int i=0 ; i < 5 ; ++i)
    {
        temp = strTok(txt,",");
        lesson->data[i] = (char*)calloc(strLen(temp)+1,sizeof(char));
        strCpy(lesson->data[i],temp);

        if(i == 0)
            txt = NULL;
    }
    
    return lesson;
}

Item* generate_item(char* itemName)
{
    Item* item = (Item*)calloc(1,sizeof(Item));

    item->itemName = (char*)calloc(strLen(itemName)+1,sizeof(char));
    strCpy(item->itemName,itemName);

    return item;
}

void print_queue(Queue* queue, int direction)
{
    Item* item = queue->head;
    Lesson* lesson = NULL;

    for(; item ; item = item->next)
    {
        lesson = generate_course(item->itemName);
        print(lesson);
        free(lesson);
    }
}

void print(Lesson* lesson)
{
    printf("Code : %s\n",lesson->data[0]);
    printf("Name : %s\n",lesson->data[1]);
    printf("Class : %s\n",lesson->data[2]);
    printf("C.city : %s\n",lesson->data[3]);
    printf("Credit : %s\n\n",lesson->data[4]);
}

char* strTok(char* str, const char* delim)
{
    static char* buff = NULL;

    if(str)
        buff = str;

    if(!buff || *buff == '\0')
        return NULL;

    char* ret = buff;

    for(char* i = buff ; *i ; ++i)
        for(const char* j = delim ; *j ; ++j)
            if(*i == *j)
            {
                *i = '\0';
                buff = i+1;

                if(i == ret)
                {
                    ++ret;
                    continue;
                }

                return ret;
            }
    
    for(; *buff ; ++buff);

    return ret;
}

Queue* newQueue(void)
{
    return (Queue*)calloc(1,sizeof(Queue));
}

void freeQueue(Queue* queue)
{
    if(queue)
    {
        freeItem(queue->head);
        free(queue);
    }
}

void freeItem(Item* item)
{
    if(item)
    {
        freeItem(item->next);
        free(item->itemName);
        free(item);
    }
}

void strCpy(char* s1, char* s2)
{
    while(*s1++ = *s2++);
}

int strLen(const char* str)
{
    int len=0;

    while(str[len])
        ++len;

    return len;
}