#include <stdio.h>

void add_binary(const char*,const char*,char*);
void convertToBinary(int,char*);
int convertToDecimal(const char*);
void reverseString(char*);
int strLen(const char*);

int main(void)
{
	char bin1[] = "1111111";
	char bin2[] = "11111";
	char result[100];

	add_binary(bin1,bin2,result);
	printf("%s + %s : %s",bin1,bin2,result);

	return 0;
}

void add_binary(const char* b1, const char* b2, char* result)
{
	convertToBinary(convertToDecimal(b1) + convertToDecimal(b2),result);
}

void convertToBinary(int dec, char* str)
{
    int index=0;
    
	while(dec)
	{
	    str[index] = dec%2 + '0';
	    dec /= 2;
	    ++index;
	}
	
	str[index] = '\0';
	reverseString(str);
}

void reverseString(char* str)
{
    int len = strLen(str);
    char temp = 0;
    
    for(int i=0 ; i < len/2 ; ++i)
    {
        char temp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = temp;
    }
}

int convertToDecimal(const char* bin)
{
	int len = strLen(bin) - 1;
	int dec = 0;

	for(int digit = 1 ; len >= 0 ; --len , digit *= 2)
	    dec += (bin[len] - '0') * digit;

	return dec;
}

int strLen(const char* str)
{
	int len=0;
	
	while(str[len])
		++len;

	return len;
}