#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true}bool;
typedef enum{HEAD,REGULAR,PROPERNOUN}Word_Type;

typedef struct
{
    char* word;
    Word_Type type;
    int numOfVowels;
    int len;
}Specification;

void parse_string(char*);
int numOfWord(char*);
char* getStr(const char*,int);
char* eliminator(char*,char*,char);
void calcNumOfVowels(Specification*);
void strCpy(char*,char*);
int strLen(char*);

int main(void)
{
    char* text = getStr("Text : ",64);

    parse_string(text);
    free(text);

    return 0;
}

void parse_string(char* text)
{
    int len = numOfWord(text);
    Specification* word = (Specification*)calloc(len,sizeof(Specification));
    char* temp = NULL;

    for(int i=0 ; i < len ; ++i)
    {
        temp = eliminator(text,temp,' ');
        word[i].len = strLen(temp);
        word[i].word = (char*)calloc(word[i].len+1,sizeof(char));
        strCpy(word[i].word,temp);

        if(i == 0)
            word[0].type = PROPERNOUN;
        else if(word[i].word[0] >= 'A' && word[i].word[0] <= 'Z')
             word[i].type = PROPERNOUN;
        else
            word[i].type = REGULAR;

        calcNumOfVowels(&word[i]);
    }

    for(int i=0 ; i < len ; ++i)
    {
        printf("-----------------------------\n");
        printf("Word : %s\n",word[i].word);
        printf("Type : ");

        switch(word[i].type)
        {
            case HEAD:          printf("Head\n");           break;
            case REGULAR:       printf("Regular\n");        break;
            case PROPERNOUN:    printf("Proper noun\n");    break;
        }

        printf("# of vowels : %d\n",word[i].numOfVowels);
        printf("Length : %d\n",word[i].len);
    }

    for(int i=0 ; i < len ; ++i)
        free(word[i].word);
    free(word);
}

void calcNumOfVowels(Specification* word)
{
    word->numOfVowels = 0;

    for(int i=0 ; i < word->len ; ++i)
        if(word->word[i] == 'a' || word->word[i] == 'e' || word->word[i] == 'i' || word->word[i] == 'o' || word->word[i] == 'u')
            ++word->numOfVowels;
}

char* eliminator(char* str, char* adress, char token)
{
    static char* storageAdress = NULL;
    char* temp = NULL;
    int i=0;
    bool exit = false;

    if(adress == NULL)
        storageAdress = str;
    
    for(i=0 ; storageAdress[i] && !exit ; ++i)
        if(storageAdress[i] == token)
        {
            storageAdress[i] = '\0';
            exit = true;
        }
    
    temp = storageAdress;

    if(storageAdress[i] != '\0')
        storageAdress = storageAdress + i;

    return temp;
}

int numOfWord(char* str)
{
    int count=0;

    for(int i=0 ; str[i] ; ++i)
        if(str[i] == ' ')
            ++count;
    
    return count+1;
}

char* getStr(const char* text, int len)
{
    char* var = (char*)calloc(len,sizeof(char));

    printf("%s",text);
    scanf("%[^\n]s",var);

    return var;
}

void strCpy(char* s1, char* s2)
{
    while(*s1++ = *s2++);
}

int strLen(char* str)
{
    int len=0;

    while(str[len])
        ++len;

    return len;
}