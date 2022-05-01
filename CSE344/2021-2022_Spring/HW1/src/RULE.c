#include "RULE.h"

int checkChr(const char*);
int isThereChr(const char*);
int checkLineStartChr(const char*);
int checkLineEndChr(const char*, int);
int checkOpenCloseBracket(const char*);
int checkRepetetionChr(const char*);
int checkOnlyLetterAndDigit(const char*);
int compChar(char, char, int);
int compCharWBracket(const char*, char, int, int, int);

RULE* createRule(const char* r, const char* newStr, int isC)
{
	if(!isValidRegex(r))
		return NULL;

	RULE* rule = x_calloc(1, sizeof(RULE));

	rule->regex = x_calloc(str_len(r) + 1, sizeof(char));
	str_cpy(rule->regex, r);
	setNewStr(rule, newStr);
	rule->isC = isC;

	return rule;
}

void freeRule(void* v)
{
	RULE* r = (RULE*)v;

	if(!r)
		return;

	if(r->regex)
		free(r->regex);
	if(r->newStr)
		free(r->newStr);
	free(r);
}

int isMatch(RULE* r, const char* s)
{
	if(!r || !s)
		return 0;

	int len = str_len(r->regex);
	int cur = r->regex[0] == '^' ? 1 : 0;
	int last = r->regex[len - 1] == '$' ? len - 2 : len - 1;

	int next;
	int bracketFlag = 0, bracketStartIndex = -1, bracketEndIndex = -1;

	while(cur <= last)
	{
		next = cur < last ? cur + 1 : 0;

		if(bracketFlag && r->regex[cur] == ']')
		{
			bracketEndIndex = cur;

			int res = compCharWBracket(r->regex, *s , bracketStartIndex, bracketEndIndex, r->isC);
			
			if(next && r->regex[next] == '*' && res)
				++s;
			else if(next && r->regex[next] == '*')
				cur = cur + 2, bracketFlag = 0;
			else if(res)
			{
				++cur;
				++s;
				bracketFlag = 0;
			}
			else
				return 0;
		}
		else if(bracketFlag)
			++cur;
		else if(r->regex[cur] == '[')
		{
			bracketFlag = 1;
			bracketStartIndex = cur++;
		}
		else
		{
			int res = compChar(r->regex[cur], *s, r->isC);

			if(next && r->regex[next] == '*' && res)
				++s;
			else if(next && r->regex[next] == '*')
				cur = cur + 2;
			else if(res)
				++cur, ++s;
			else
				return 0;
		}
	}

	if(!*s && cur > last)
		return 1;
	return 0;
}

int isValidRegex(const char* s)
{
	int len;

	if(s == NULL || !(len = str_len(s)))
		return 0;

	if(!checkChr(s) || !isThereChr(s))
		return 0;

	if(!checkLineStartChr(s) || !checkLineEndChr(s, len))
		return 0;

	if(*s == '^' && s[len - 1] == '$')
		return 0;

	if(!checkOpenCloseBracket(s))
		return 0;

	if(!checkRepetetionChr(s))
		return 0;

	return 1;
}

int setNewStr(RULE* r, const char* s)
{
	if(!r || !s || !checkOnlyLetterAndDigit(s))
		return 0;

	if(r->newStr)
		free(r->newStr);

	r->newStr = x_calloc(str_len(s) + 1, sizeof(char));
	str_cpy(r->newStr, s);

	return 1;
}

char* getRegex(RULE* r)
{
	return r == NULL ? NULL : r->regex;
}

char* getNewString(RULE* r)
{
	return r == NULL ? NULL : r->newStr;
}

int getIsC(RULE* r)
{
	if(!r)
		return 0;
	return r->isC;
}

/*
	Checks wheter given regex includes wrong charater or not
	WARNING: Does not check error
*/
int checkChr(const char* r)
{
	for(int i=0; r[i] ; ++i)
		if(!is_al_num(r[i]) &&
			r[i] != '^' && r[i] != '$' && r[i] != '[' && r[i] != ']' && r[i] != '*')
			return 0;
	return 1;
}

/*
	Checks whether regex has at least one charater (letter and digit) or not
	WARNING: Does not check error
*/
int isThereChr(const char* r)
{
	for(int i=0 ; r[i] ; ++i)
		if(is_al_num(r[i]))
			return 1;
	return 0;
}

/*
	Checks is the line start character ('^') used correctly in the given regex
	WARNING: Does not check error
*/
int checkLineStartChr(const char* r)
{
	for(int i=1; r[i] ; ++i)
		if(r[i] == '^')
			return 0;
	return 1;
}

/*
	Checks is the line end character ('$') used correctly in the given regex
	WARNING: Does not check error
*/
int checkLineEndChr(const char* r, int len)
{
	for(int i=0 ; i < len-1 ; ++i)
		if(r[i] == '$')
			return 0;
	return 1;
}

/*
	Checks whether open and close brackets usage is correct or not
	WARNING: Does not check error
*/
int checkOpenCloseBracket(const char* r)
{
	int open = 0, close = 0;

	for(int i=0 ; r[i] ; ++i)
	{
		if(open && close)
			open = close = 0;

		if(r[i] == '[')
		{
			if(open)
				return 0;
			open = 1;
		}

		if(r[i] == ']')
		{
			if(!open || close)
				return 0;
			close = 1;
		}
	}

	if(open + close == 1)
		return 0;
	return 1;
}

/*
	Checks whether repetetion character '*' usage is correct or not
	WARNING: Does not check error
*/
int checkRepetetionChr(const char* r)
{
	char saved = 0;

	for(int i=0 ; r[i] ; ++i)
	{
		if(r[i] == ']')
			continue;
		else if(r[i] == '*' && !is_al_num(saved))
			return 0;

		saved = r[i];
	}

	return 1;
}

/*
	Checks whether given string contains letters and digits
	WARNING: Does not check error
*/
int checkOnlyLetterAndDigit(const char* s)
{
	for(int i=0 ; s[i] ; ++i)
		if(!is_al_num(s[i]))
			return 0;
	return 1;
}

/*
	Compares two character with given case sensitive parameter
	If case sensitive parameter is 1, it makes case sensitive. Otherwise case insensitive
	Returns 1 if they are equal. Otherwise returns 0
*/
int compChar(char c1, char c2, int caseSensitive)
{
	if(caseSensitive)
		return c1 == c2;

	char tmp = 0;

	if(c1 >= 'A' && c1 <= 'Z')
		tmp = c1 + 32;
	else if(c1 >= 'a' && c1 <= 'z')
		tmp = c1 - 32;

	return c1 == c2 || tmp == c2;
}

/*
	Compares the character with the characters of the string in the given range (start, end)
	If case sensitive parameter 1, it makes case sensitive. Otherwise case insensitive
	Returns 1 if there is at least one equality. Otherwise returns 0
	WARNING: Does not check index validty
*/
int compCharWBracket(const char* s, char c, int start, int end, int caseSensitive)
{
	for(int i = start + 1 ; i < end ; ++i)
		if(compChar(s[i], c, caseSensitive))
			return 1;
	return 0;
}