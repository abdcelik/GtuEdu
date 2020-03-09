#include <stdio.h>

void reverse_print(const char*);

int main(void)
{
    reverse_print("c-lab");
    return 0;
}

void reverse_print(const char* str)
{
    if(*str != '\0')
        reverse_print(str+1);
    printf("%c",*str);
}