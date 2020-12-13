%{
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
{KW_AND}		fprintf(yyout,"KW_AND\n");
{KW_OR}			fprintf(yyout,"KW_OR\n");
{KW_NOT}		fprintf(yyout,"KW_NOT\n");
{KW_EQUAL}		fprintf(yyout,"KW_EQUAL\n");
{KW_LESS}		fprintf(yyout,"KW_LESS\n");
{KW_NIL}		fprintf(yyout,"KW_NIL\n");
{KW_LIST}		fprintf(yyout,"KW_LIST\n");
{KW_APPEND}		fprintf(yyout,"KW_APPEND\n");
{KW_CONCAT}		fprintf(yyout,"KW_CONCAT\n");
{KW_SET}		fprintf(yyout,"KW_SET\n");
{KW_DEFFUN}		fprintf(yyout,"KW_DEFFUN\n");
{KW_FOR}		fprintf(yyout,"KW_FOR\n");
{KW_IF}			fprintf(yyout,"KW_IF\n");
{KW_EXIT}		fprintf(yyout,"KW_EXIT\n");
{KW_LOAD}		fprintf(yyout,"KW_LOAD\n");
{KW_DISP}		fprintf(yyout,"KW_DISP\n");
{KW_TRUE}		fprintf(yyout,"KW_TRUE\n");
{KW_FALSE}		fprintf(yyout,"KW_FALSE\n");
{OP_PLUS}		fprintf(yyout,"OP_PLUS\n");
{OP_MINUS}		fprintf(yyout,"OP_MINUS\n");
{OP_DIV}		fprintf(yyout,"OP_DIV\n");
{OP_MULT}		fprintf(yyout,"OP_MULT\n");
{OP_OP}			fprintf(yyout,"OP_OP\n");
{OP_CP}			fprintf(yyout,"OP_CP\n");
{OP_DBLMULT}	fprintf(yyout,"OP_DBLMULT\n");
{OP_OC_CC}		{ isOpenQuote == 0 ? fprintf(yyout,"OP_OC\n") : fprintf(yyout,"OP_CC\n"); isOpenQuote = !isOpenQuote; }
{OP_COMMA}		fprintf(yyout,"OP_COMMA\n");
{COMMENT}		fprintf(yyout,"COMMENT\n");
{VALUE}			fprintf(yyout,"VALUE\n");
{IDENTIFIER}	fprintf(yyout,"IDENTIFIER\n");
^\n				{ if(yyin == stdin) return 0; }
<<EOF>>			return 0;
{SPACE}			/* Initially is ignored	*/
{SYN_ERR_1}		fprintf(yyout,"SYNTAX ERROR %s cannot be tokenized\n",yytext);
{SYN_ERR_2}		fprintf(yyout,"SYNTAX ERROR %s cannot be tokenized\n",yytext);
{SYN_ERR_3}		fprintf(yyout,"SYNTAX ERROR %s cannot be tokenized\n",yytext);
.				fprintf(yyout,"SYNTAX ERROR %s cannot bo tekonized\n",yytext);
%%

int yywrap(){}
void setIOAndStartFlex(FILE* in, FILE* out);
FILE* openFileToRead(int,char**);
FILE* openFileToWrite(char*);

int main(int argc, char** argv)
{
	FILE* in = openFileToRead(argc,argv);
	FILE* out = openFileToWrite("parsed_cpp.txt");

	if(in && out)
		setIOAndStartFlex(in,out);

	return 0;
}

void setIOAndStartFlex(FILE* in, FILE* out)
{
	yyin = in;
	yyout = out;
	yylex();
}

FILE* openFileToRead(int argc, char** argv)
{
	FILE* in = NULL;

	if(argc == 1)
		in = stdin;
	else if(!(in = fopen(argv[1],"r")))
		fprintf(stderr,"ERROR: File couldn't be opened: %s\n",argv[1]);	

	return in;
}

FILE* openFileToWrite(char* fileName)
{
	FILE* out = NULL;

	if(!(out = fopen(fileName,"w")))
		fprintf(stderr,"ERROR: No such file: %s",fileName);

	return out;
}