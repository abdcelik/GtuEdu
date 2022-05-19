#include "String.h"

struct String
{
	char* arr;
	int size;
};

struct StringArray
{
	String** arr;
	int size;
};

int String_compareWithGivenIndex(const String*, const char*, int, int);
String* String_buildWithGivenStringAndRange(const String*, int, int);

String* String_build()
{
	String* s = malloc(sizeof(String));

	if(!s)
		return NULL;

	s->size = 0;
	s->arr = NULL;

	return s;
}

void String_free(String* s)
{
	if(!s)
		return;

	if(s->arr)
		free(s->arr);
	free(s);
}

void String_print(const String* s)
{
	if(!s)
		return;

	printf("%s", s->arr);
}

int String_length(const String* s)
{
	if(!s)
		return 0;
	return s->size;
}

char* String_getCharArr(const String* s)
{
	return s == NULL ? NULL : s->arr;
}

int String_addChar(String* s, char chr)
{
	if(!s)
		return 0;

	s->arr = realloc(s->arr, sizeof(char) * (s->size + 2));

	if(!s->arr)
		return -1;

	s->arr[s->size] = chr;
	s->arr[++s->size] = '\0';

	return 1;
}

int String_addCharArr(String* s, const char* chars)
{
	if(!s)
		return 0;

	int len = String_len(chars);

	if(len == 0)
		return 1;

	int temp = s->size;
	
	if(!(s->arr = realloc(s->arr, sizeof(char) * ((s->size += len) + 1))))
		return -1;

	for(int i=0 ; i < len ; ++i)
		s->arr[temp + i] = chars[i];
	s->arr[s->size] = '\0';

	return 1;
}

int String_addInt(String* s, int var)
{
	if(!s)
		return 0;

	char buffer[256];
	sprintf(buffer, "%d", var);

	return String_addCharArr(s, buffer);
}

int String_addDouble(String* s, double var)
{
	if(!s)
		return 0;

	char buffer[256];
	sprintf(buffer, "%f", var);

	return String_addCharArr(s, buffer);
}

int String_addDoubleWithPrecision(String* s, double var, int precision)
{
	if(!s)
		return 0;

	char buffer[256], in[256];

	sprintf(in, "%%.%df", precision);
	sprintf(buffer, in, var);

	return String_addCharArr(s, buffer);
}

int String_len(const char* chars)
{
	if(!chars)
		return 0;

	int len = 0;

	while(chars[len])
		++len;

	return len;
}

int String_cmp(const char* s1, const char* s2)
{
	while(*s1 && *s2 && *s1 == *s2)
		++s1, ++s2;
	return *s1 - *s2;
}

StringArray* String_split(const String* str, const char* delimeter)
{
	if(str == NULL || delimeter == NULL)
		return NULL;

	StringArray* stringArray = calloc(1, sizeof(StringArray));

	if(stringArray == NULL)
		return NULL;

	int endIndex = 1, savedStart = 0;

	for(int startIndex = 0, res = 0 ; endIndex < str->size ;)
	{
		res = String_compareWithGivenIndex(str, delimeter, startIndex, endIndex);

		switch(res)
		{
			case -1:
				++startIndex;
				++endIndex;
				break;
			case  0:
				++endIndex;
				break;
			case  1:
				stringArray->size++;
				stringArray->arr = realloc(stringArray->arr, sizeof(String*) * stringArray->size);
				stringArray->arr[stringArray->size - 1] = String_buildWithGivenStringAndRange(str, savedStart, endIndex);
				savedStart = startIndex = endIndex++;
				break;
		}
	}

	stringArray->size++;
	stringArray->arr = realloc(stringArray->arr, sizeof(String*) * stringArray->size);
	stringArray->arr[stringArray->size - 1] = String_buildWithGivenStringAndRange(str, savedStart, endIndex);

	return stringArray;
}

int String_compareWithGivenIndex(const String* str, const char* delimeter, int startIndex, int endIndex)
{
	int delimStartIndex = 0, delimEndIndex = String_len(delimeter);

	for(int loopExit = 0 ; !loopExit ;)
	{
		if(startIndex >= endIndex || delimStartIndex >= delimEndIndex)
		{
			loopExit = 1;
			continue;
		}

		if(str->arr[startIndex] != delimeter[delimStartIndex])
			return -1;

		++startIndex;
		++delimStartIndex;
	}

	if(startIndex == endIndex && delimStartIndex == delimEndIndex)
		return 1;

	return 0;
}

String* String_buildWithGivenStringAndRange(const String* str, int startIndex, int endIndex)
{
	String* newString = String_build();

	for(int i = startIndex ; i < endIndex ; ++i)
		String_addChar(newString, str->arr[i]);

	return newString;
}

String* StringArray_get(const StringArray* arr, int index)
{
	if(arr == NULL || index >= arr->size)
		return NULL;
	return arr->arr[index];
}

int StringArray_size(const StringArray* arr)
{
	if(arr == NULL) 
		return -1;
	return arr->size;
}

void StringArray_free(StringArray* strArr)
{
	if(strArr == NULL)
		return;

	for(int i=0 ; i < strArr->size ; ++i)
		String_free(strArr->arr[i]);

	free(strArr->arr);
	free(strArr);
}