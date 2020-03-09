#include <stdio.h>

typedef enum{false,true}bool;

bool isPalindrome(const char*);
bool checkPalindrome(const char*,int,int);
int strLen(const char*);

int main(void)
{
    char str[] = "kavak";
  
    if(isPalindrome(str))
        printf("%s is palindrome!\n",str); 
    else
        printf("%s is not palindrome!\n",str); 

    return 0;
}

bool isPalindrome(const char* text)
{
    int size = strLen(text);

    if(size == 0)
        return true;
    return checkPalindrome(text,0,size-1);
}

bool checkPalindrome(const char *text, int start, int end)
{
    if(start == end)
        return true;

    if(text[start] != text[end])
        return false;

    if(start < end + 1)
        return checkPalindrome(text,start+1,end-1);

    return true;
}

int strLen(const char* str)
{
    int len=0;

    while(str[len])
        ++len;
    return len;
}