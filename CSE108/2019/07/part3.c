#include <stdio.h>

typedef enum{false,true}bool;

int find_longest_word(char[]);
char* strTok(char*,const char*);
int strLen(const char*);

int main(void)
{
    char str[] = "The Silmarillion is a collection of mythopoeic works by English write J. R. R. Tolkien, edited and published posthumously by his son, Christopher Tolkien, in 1977, with assistance from Guy Gavriel Kay. The Silmarillion, incomplete, narrative that describes the universe of Ea in which are found the lands of Valinor, Beleriand, Numenor, and Middle-earth, within which The Hobbit and The Lord of the Rings take place.";

    find_longest_word(str);
    return 0;
}

int find_longest_word(char text[])
{
    int len=0,maxLen=0;
    char* word = NULL , *theLongestWord = NULL , *txt = text;
    bool exit = false;

    for(int i=0 ; (word = strTok(txt," .,")) ;)
    {
        if(word && (len = strLen(word)) > maxLen)
        {
            theLongestWord = word;
            maxLen = len;
        }

        if(i == 0)
            txt = NULL , ++i;
    }

    printf("The longest word is %s with the number of %d letters.\n",theLongestWord,maxLen);

    return maxLen;
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

int strLen(const char* str)
{
    int len=0;

    while(str[len])
        ++len;
    
    return len;
}