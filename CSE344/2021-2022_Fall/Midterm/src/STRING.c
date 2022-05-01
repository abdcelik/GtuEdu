#include "STRING.h"

struct STRING
{
	char* arr;
	int size;
};

STRING* STRING_build()
{
	STRING* str = x_malloc(sizeof(STRING));

	str->size = 0;
	str->arr = x_calloc(1, sizeof(char));

	return str;
}

STRING* STRING_buildWithSize(int size)
{
	if(size <= 0)
		return NULL;

	STRING* str = x_malloc(sizeof(STRING));

	str->size = size;
	str->arr = x_calloc(str->size + 1, sizeof(char));

	return str;
}

void STRING_free(STRING* str)
{
	if(str)
	{
		if(str->arr)
			free(str->arr);
		free(str);
	}
}

int STRING_length(STRING* str)
{
	if(!str)
		return 0;
	return str->size;
}

char* STRING_getCharArr(STRING* str)
{
	return str == NULL ? NULL : str->arr;
}

int STRING_addChar(STRING* str, char chr)
{
	if(!str)
		return 0;

	str->arr = x_realloc(str->arr, sizeof(char) * (++str->size + 1));
	str->arr[str->size - 1] = chr;
	str->arr[str->size] = '\0';

	return 1;
}

int STRING_addCharArr(STRING* str, char* chrs)
{
	if(!str || !chrs)
		return 0;

	int len = strlen(chrs);
	int temp = str->size;
	
	str->size += len;
	str->arr = x_realloc(str->arr, sizeof(char) * (str->size + 1));

	for(int i=0 ; i < len ; ++i)
		str->arr[temp + i] = chrs[i];
	str->arr[str->size] = '\0';

	return 1;
}

int STRING_addInt(STRING* str, int var)
{
	if(!str)
		return 0;

	char buffer[256];

	sprintf(buffer, "%d", var);

	int len = strlen(buffer);
	int temp = str->size;

	str->size += len;
	str->arr = x_realloc(str->arr, sizeof(char) * (str->size + 1));

	for(int i=0 ; i < len ; ++i)
		str->arr[temp + i] = buffer[i];
	str->arr[str->size] = '\0';

	return 1;
}

int STRING_addDouble(STRING* str, double var, int precise)
{
	if(!str || precise > 5 || precise < 1)
		return 0;

	char buffer[256];
	char buffer2[256];

	sprintf(buffer2, "%%.%d", precise);
	strcat(buffer2, "lf");
	sprintf(buffer, buffer2, var);

	int len = strlen(buffer);
	int temp = str->size;

	str->size += len;
	str->arr = x_realloc(str->arr, sizeof(char) * (str->size + 1));

	for(int i=0 ; i < len ; ++i)
		str->arr[temp + i] = buffer[i];
	str->arr[str->size] = '\0';

	return 1;
}

void STRING_cpy(char* s1, char* s2)
{
	while((*s1++ = *s2++));
}

void STRING_ncpy(char* s1, const char* s2, int n)
{
	for(int i=0 ; i < n ; ++i)
		*s1++ = *s2++;
}

int STRING_len(char* s)
{
	int len = 0;

	while(s[len])
		++len;

	return len;
}