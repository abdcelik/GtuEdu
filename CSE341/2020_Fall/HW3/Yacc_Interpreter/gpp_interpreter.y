%{
	#include <stdio.h>
	#include "gpp_table.h"
	#include "gpp_additional.h"
%}

%union
{
	int value;
	void* values;
	char id[16];
}

%start INPUT

%token	KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS KW_NIL KW_LIST KW_APPEND KW_CONCAT KW_SET
		KW_DEFFUN KW_FOR KW_IF KW_EXIT KW_LOAD KW_DISP KW_TRUE KW_FALSE
		OP_PLUS OP_MINUS OP_DIV OP_MULT OP_OP OP_CP OP_DBLMULT OP_OC OP_CC OP_COMMA
		COMMENT
%token <value> VALUE
%token <id> IDENTIFIER

%type <value> INPUT
%type <value> EXPI
%type <value> EXPB
%type <values> EXPLISTI
%type <values> LISTVALUE
%type <values> VALUES

%%
INPUT:
	EXPI { fprintf(yyout, "Syntax OK.\nResult: %d\n", $1); }
	|
	EXPLISTI { fprintf(yyout, "Syntax OK.\nResult: "); vectorPrint($1); };
	|
	INPUT EXPI { fprintf(yyout, "Syntax OK.\nResult: %d\n", $2); }
	|
	INPUT EXPLISTI { fprintf(yyout, "Syntax OK.\nResult: "); vectorPrint($2); }
	;

EXPI:
	OP_OP OP_PLUS EXPI EXPI OP_CP {$$ = $3 + $4;}
	|
	OP_OP OP_MINUS EXPI EXPI OP_CP {$$ = $3 - $4;}
	|
	OP_OP OP_MULT EXPI EXPI OP_CP {$$ = $3 * $4;}
	|
	OP_OP OP_DIV EXPI EXPI OP_CP {$$ = $3 / $4;}
	|
	IDENTIFIER { Entry* entry = tableGet($1); if(entry == NULL) $$ = 1; else $$ = entry->val; }
	|
	VALUE {$$ = $1;}
	|
	OP_OP KW_SET IDENTIFIER EXPI OP_CP { $$ = $4; tablePut($3, $4); } // (set Id EXPI)
	|
	OP_OP KW_IF EXPB EXPI OP_CP { $$ = $3 == 1 ? $4 : 0; } // (if EXPB EXPI)
	|
	OP_OP KW_IF EXPB EXPI EXPI OP_CP { $$ = $3 == 1 ? $4 : $5; } // (if EXPB EXPI EXPI)
	;

EXPB:
	OP_OP KW_AND EXPB EXPB OP_CP { $$ = $3 && $4; }
	|	
	OP_OP KW_OR EXPB EXPB OP_CP { $$ = $3 || $4; }
	|
	OP_OP KW_NOT EXPB OP_CP { $$ = !$3;}
	|
	OP_OP KW_EQUAL EXPB EXPB OP_CP { $$ = $3 == $4 ? 1 : 0; }
	|
	OP_OP KW_EQUAL EXPI EXPI OP_CP { $$ = $3 == $4 ? 1 : 0; }
	|
	KW_TRUE { $$ = 1; }
	|
	KW_FALSE { $$ = 0; }
	;

EXPLISTI:
	OP_OP KW_CONCAT EXPLISTI EXPLISTI OP_CP { $$ = vectorConcat($3, $4); }
	|
	OP_OP KW_APPEND EXPI EXPLISTI OP_CP { $$ = vectorAppendItem($4, $3); }
	|
	LISTVALUE { $$ = $1; }
	;

LISTVALUE:
	OP_OP VALUES OP_CP { $$ = $2; }
	|
	OP_OP OP_CP { $$ = vectorInit(); }
	|
	KW_NIL { $$ = NULL; }
	;

VALUES:
	VALUES VALUE { $$ = vectorAddItem($1, $2); }
	|
	VALUE { $$ = vectorAddItem(NULL, $1); }
	;
%%

int yyerror(char* str) 
{ 
	printf("SYNTAX_ERROR Expression not recognized\n");
	return 0; 
}

int main(int argc, char* argv[])
{
	FILE* in = openFileToRead(argc,argv);
	FILE* out = openFileToWrite("output.txt");

	tableCreate();

	if(in && out)
		setIOAndStart(in,out);

	tableFree();

	return 0;
}