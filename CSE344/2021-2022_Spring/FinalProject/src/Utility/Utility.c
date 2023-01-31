#include "Utility.h"

int TEMP_INT = 0;
char TEMP_BUFFER_128[BUFFER_128];

int stringToPositiveInt(const char* string)
{
	if(string == NULL)
		return -1;

	int num = 0;

	for(int i=0 ; string[i] != '\0' ; ++i)
	{
		if(!isDigit(string[i]))
			return -1;

		num = (num * 10) + string[i] - '0';
	}

	return num;
}

int isDigit(char var)
{
	return var >= '0' && var <= '9';
}