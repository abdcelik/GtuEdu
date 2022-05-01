#ifndef _RULE_H_
#define _RULE_H_

#include "BASIS.h"
#include <stdio.h>
#include <stdlib.h>

/*
	Structure representing a rule for string replacement
	Do not access field directly. Use functions only. Otherwise errors can occur
*/
struct RULE
{
	/*	Address of regex	*/
	char* regex;

	/*	Address of new string to be replace	*/
	char* newStr;

	/*	Case sensitive or not
		0 means that case insensitive. Otherwise case sensitive	*/
	int isC;
};

typedef struct RULE RULE;

/*
	Creates rule structre with given parameters
	Validates given regex
*/
RULE* createRule(const char*, const char*, int);

/*	Frees a rule structure	*/
void freeRule(void*);

/*
	Checks whether given rule and given regex is match or not
	Return 1 if there is a match. Otherwise returns 0 
*/
int isMatch(RULE*, const char*);

/*
	Checks whether given string is valid regex or not
	Rules:
		- Regex should include letter, digits and special characters(^$[]*)
		- Regex should include at least one isAlNum(letter, digit)
		- Line start character ('^') can only be the first character
		- Line end character ('$') can only be the last character
		- Checks open and close brackets '[', ']' usage
		- Checks repetetion charater '*' usage
	Returns 1 if it is valid. Otherwise returns 0
*/
int isValidRegex(const char*);

/*
	Sets given rule's new string with given string
	Given string can only includes letters and digits
	Return 1 if operation is successfull. Otherwise returns 0
*/
int setNewStr(RULE*, const char*);

/*	Returns regex from given rule	*/
char* getRegex(RULE*);

/*	Returns new string from given rule	*/
char* getNewString(RULE*);

/*	Returns isC from give rule	*/
int getIsC(RULE*);

#endif