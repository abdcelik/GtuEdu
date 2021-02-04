%{
	#include "gpp_interpreter.h"
	int isOpenQuote = 0;
%}

KW_AND			"and"
KW_OR			"or"
KW_NOT			"not"
KW_EQUAL		"equal"
KW_LESS			"less"
KW_NIL			"nil"
KW_LIST			"list"
KW_APPEND		"append"
KW_CONCAT		"concat"
KW_SET			"set"
KW_DEFFUN		"deffun"
KW_FOR			"for"
KW_IF			"if"
KW_EXIT			"exit"
KW_LOAD			"load"
KW_DISP			"disp"
KW_TRUE			"true"
KW_FALSE		"false"
OP_PLUS			"+"
OP_MINUS		"-"
OP_DIV			"/"
OP_MULT			"*"
OP_OP			"("
OP_CP			")"
OP_DBLMULT		"**"
OP_OC_CC		"\""
OP_COMMA		","
COMMENT			";;".*
VALUE			[[:digit:]]|[1-9][[:digit:]]+
IDENTIFIER		[[:alpha:]][[:alnum:]]*
SPACE			[[:space:]]
SYN_ERR_1		[0][[:digit:]]+
SYN_ERR_2		[[:digit:]]+[[:alpha:]]+
SYN_ERR_3		[[:alnum:]]*[[:alnum:][:punct:]]{-}[()"]+

%%
{KW_AND}		return KW_AND;
{KW_OR}			return KW_OR;
{KW_NOT}		return KW_NOT;
{KW_EQUAL}		return KW_EQUAL;
{KW_LESS}		return KW_LESS;
{KW_NIL}		return KW_NIL;
{KW_LIST}		return KW_LIST;
{KW_APPEND}		return KW_APPEND;
{KW_CONCAT}		return KW_CONCAT;
{KW_SET}		return KW_SET;
{KW_DEFFUN}		return KW_DEFFUN;
{KW_FOR}		return KW_FOR;
{KW_IF}			return KW_IF;
{KW_EXIT}		return KW_EXIT;
{KW_LOAD}		return KW_LOAD;
{KW_DISP}		return KW_DISP;
{KW_TRUE}		return KW_TRUE;
{KW_FALSE}		return KW_FALSE;
{OP_PLUS}		return OP_PLUS;
{OP_MINUS}		return OP_MINUS;
{OP_DIV}		return OP_DIV;
{OP_MULT}		return OP_MULT;
{OP_OP}			return OP_OP;
{OP_CP}			return OP_CP;
{OP_DBLMULT}	return OP_DBLMULT;
{OP_OC_CC}		{ if(isOpenQuote = !isOpenQuote) return OP_CC; return OP_OC; }
{OP_COMMA}		return OP_COMMA;
{COMMENT}		return COMMENT;
{VALUE}			{ yylval.value = atoi(yytext); return VALUE; }
{IDENTIFIER}	{ strcpy(yylval.id, yytext); return IDENTIFIER; }
^\n				{ if(yyin == stdin) return 0; }
<<EOF>>			return 0;
{SPACE}			/* Initially is ignored	*/
{SYN_ERR_1}		return 0;
{SYN_ERR_2}		return 0;
{SYN_ERR_3}		return 0;
.				return 0;
%%

int yywrap(){}