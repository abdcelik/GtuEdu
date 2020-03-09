#include <stdio.h>

typedef enum{false,true}bool;
typedef enum{LEFT,RIGHT}Direction;

void check_typos(char[]);
bool isLetter(char);
bool isUpperLetter(char);
bool isPunctuation(char);
bool isPoint(char);
bool isBlankSpace(char);
void shift(char[],int,Direction);
int strLen(const char*);

int main(void)
{
    char plain_text[512] = "this IS A tExt which has some typos.    you should correct tHe text,because you will use the Text to test your check_typos function.therefore, try to correct all typos iN the best. This part of the the text is correct, so no correction should be done on this part.";

    check_typos(plain_text);
    printf("%s\n",plain_text);

    return 0;
}

void check_typos(char plain_text[])
{
    bool upperCase = true;

    for(int i=0 ; plain_text[i] ; ++i)
    {
        if(isBlankSpace(plain_text[i]) && plain_text[i+1] && isBlankSpace(plain_text[i+1]))
            shift(plain_text,i--,LEFT);

        if(isPunctuation(plain_text[i]) && plain_text[i+1] && !isBlankSpace(plain_text[i+1]))
            shift(plain_text,i,RIGHT);

        if(upperCase && isLetter(plain_text[i]))
        {
            if(!isUpperLetter(plain_text[i]))
                plain_text[i] -= 32;
            upperCase = false;
        }
        else if(!upperCase && isUpperLetter(plain_text[i]))
            plain_text[i] += 32;

        if(isPoint(plain_text[i]))
            upperCase = true;
    }
}

bool isLetter(char letter)
{
    return (letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z');
}

bool isUpperLetter(char letter)
{
    return letter >= 'A' && letter <= 'Z';
}

bool isPunctuation(char letter)
{
    return isPoint(letter) || letter == ',';
}

bool isPoint(char letter)
{
    return letter == '.';
}

bool isBlankSpace(char letter)
{
    return letter == ' ';
}

void shift(char text[], int index, Direction dir)
{
    int len = strLen(text);

    if(dir == LEFT)
        for(int i = index ; i < len ; ++i)
            text[i] = text[i+1];
    else if(dir == RIGHT)
    {
        for(int i = len ; i > index ; --i)
            text[i+1] = text[i];
        text[index+1] = ' ';
    }
}

int strLen(const char* str)
{
    int len=0;

    while(str[len])
        ++len;
    
    return len;
}