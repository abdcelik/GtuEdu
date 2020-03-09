#include <stdio.h>

typedef enum{false,true}bool;

void word_counter(char[],int[],char[][20]);
int strCmp(char*,char*);
void strCpy(char*,char*);
char* strTok(char*,const char*);

int main(void)
{
    char text[] = "There are red car. This is a red car.";
    int counters[150] = {0};
    char word[150][20];

    word_counter(text,counters,word);

    for(int i=0 ; counters[i] ; ++i)
        printf("There are %d '%s' in the text\n",counters[i],word[i]);

    return 0;
}

void word_counter(char text[], int counters[], char words[][20])
{
    char* token = NULL , *txt = text;
    int count=0;
    bool flag = true;

    for(int i=0 ; (token = strTok(txt," .,")) ; flag = true)
    {
        for(int j=0 ; j < count ; ++j)
            if(strCmp(token,words[j]) == 0)
                ++counters[j] , flag = false;

        if(flag)
        {
            ++counters[count];
            strCpy(words[count++],token);
        }

        if(i == 0)
            txt = NULL , ++i;
    }
}

int strCmp(char* s1, char* s2)
{
    while(*s1 && *s2 && *s1 == *s2)
        ++s1,++s2;
    return *s1 - *s2;
}

void strCpy(char* s1, char* s2)
{
    while(*s1++ = *s2++);
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