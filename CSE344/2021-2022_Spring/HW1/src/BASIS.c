#include "BASIS.h"

int _BASIS_ERRNO_ = 0;

int splitBy(const char*, char, VECTOR*);
int countChar(const char*, char);
int isSpecChar(int);

int checkArgument(int argc, char* argv[])
{
	if(argc != 3)
		return _BASIS_ERRNO_ = 1;

	VECTOR* vec = VECTOR_init();

	if(splitBy(argv[1], ';', vec) != 0)
		return _BASIS_ERRNO_ = -1;

	for(int i=0 ; i < vec->size ; ++i)
		if(str_len((char*)vec->item[i]) != 0 && countChar((char*)vec->item[i], '/') != 3)
			return _BASIS_ERRNO_ = 2;

	for(int i=0 ; i < vec->size ; ++i)
	{
		VECTOR* rule = VECTOR_init();

		if(splitBy(vec->item[i], '/', rule) != 0)
			return _BASIS_ERRNO_ = -1;

		if(rule->size != 4 || str_len((char*)rule->item[0]) != 0 ||
			str_len((char*)rule->item[1]) == 0 || str_len((char*)rule->item[2]) == 0 ||
			(str_len((char*)rule->item[3]) != 0 && str_cmp((char*)rule->item[3], "i") != 0))
			return _BASIS_ERRNO_ = 2;

		if(!isValidRegex(rule->item[1]))
			return _BASIS_ERRNO_ = 3;

		for(int j=0 ; j < str_len((char*)rule->item[2]) ; ++j)
		{
			char* item = rule->item[2];

			if(is_al_num(item[j]) == 0)
				return _BASIS_ERRNO_ = 4;
		}

		VECTOR_free(rule, VECTOR_free_str);
	}

	VECTOR_free(vec, VECTOR_free_str);
	return 0;
}

void printArgumentError()
{
	switch(_BASIS_ERRNO_)
	{
		case -1:	fprintf(stderr, "ERROR! There is not enough memory. Could not work correctly!\n");	break;
		case 1:		fprintf(stderr, "ERROR! Usage: ./prog 'rule' inputFile\n");	break;
		case 2:		fprintf(stderr, "ERROR! A rule usage: '/str1/str2/(i)'\nRule usage: 'rule1;rule2;..'\n");	break;
		case 3:		fprintf(stderr, "ERROR! Wrong regex usage!\n");	break;
		case 4:		fprintf(stderr, "ERROR! Given string to be changed can contain only letters and digits!\n");	break;
	}
}

VECTOR* parseRule(char* argv[])
{
	VECTOR* rules = VECTOR_init();

	if(splitBy(argv[1], ';', rules) != 0)
		return NULL;

	VECTOR* parsedRule = VECTOR_init();

	for(int i=0 ; i < rules->size ; ++i)
	{
		VECTOR* rule = VECTOR_init();

		if(splitBy(rules->item[i], '/', rule) != 0)
			return NULL;

		RULE* r = createRule(rule->item[1], rule->item[2], str_len((char*)rule->item[3]) == 1);

		VECTOR_add(parsedRule, r);
		VECTOR_free(rule, VECTOR_free_str);		
	}

	VECTOR_free(rules, VECTOR_free_str);
	return parsedRule;
}

int splitBy(const char* str, char delimiter, VECTOR* vec)
{
	int len = str_len(str);
	int occur = -1;

	for(int i=0 ; i < len + 1 ; ++i)
		if(str[i] == delimiter || i == len)
		{
			char* s = x_calloc(i - occur + 1, sizeof(char));

			for(int j = occur + 1 ; j < i ; ++j)
				s[j - occur - 1] = str[j];

			if(VECTOR_add(vec, s) != 0)
				return -1;

			occur = i;
		}

	return 0;
}

int str_len(const char* s)
{
	if(!s)
		return 0;

	int len = 0;

	while(s[len] != '\0')
		++len;

	return len;
}

int str_cmp(const char* s1, const char* s2)
{
	while(*s1 && *s1 && *s1 == *s2)
		++s1, ++s2;

	return *s1 - *s2;
}

void str_cpy(char* s1, const char* s2)
{
	while((*s1++ = *s2++));
}

int countChar(const char* s, char chr)
{
	if(!s)
		return 0;

	int count = 0;

	for(int i=0 ; i < str_len(s); ++i)
		if(s[i] == chr)
			++count;

	return count;
}

int is_al_num(int arg)
{
	return (arg >= 48 && arg <= 57) || (arg >= 65 && arg <= 90) || (arg >= 97 && arg <= 122);
}

int isSpecChar(int arg)
{
	const int len = 7;
	char chrs[] = "/;[]^$*";

	for(int i=0 ; i < len ; ++i)
		if(chrs[i] == arg)
			return 1;
	return 0;
}