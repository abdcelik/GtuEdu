#ifndef _GPP_ADDITIONAL_H_
#define _GPP_ADDITIONAL_H_

extern FILE* yyin;			/* defined by lex; lex reads from this file */
extern FILE* yyout;			/* defined by lex; lex writes to this file */
extern int yyparse();		/* defined by yacc; yacc starts to parse */

typedef struct
{
	int* arr;
	int size;
	int capacity;
}Vector;

void* vectorInit()
{
	Vector* vec = (Vector*)malloc(sizeof(Vector));

	vec->size = 0;
	vec->capacity = 1;
	vec->arr = (int*)malloc(sizeof(int));

	return vec;
}

void vectorUpdate(void* vec)
{
	Vector* v = vec;

	v->capacity *= 2;
	v->arr = (int*)realloc(v->arr, sizeof(int) * v->capacity);
}

void* vectorAddItem(void* vec, int item)
{
	if(vec == NULL)
		vec = vectorInit();

	Vector* v = vec;

	if(v->size == v->capacity)
		vectorUpdate(v);

	v->arr[v->size] = item;
	++v->size;

	return v;
}

void* vectorAppendItem(void* vec, int item)
{
	Vector* v = vectorInit();
	Vector* v2 = vec;

	vectorAddItem(v, item);

	if(v2)
		for(int i=0 ; i < v2->size ; ++i)
			vectorAddItem(v, v2->arr[i]);

	return v;
}

void* vectorConcat(void* vec1, void* vec2)
{
	Vector* v = vectorInit();

	if(vec1 != NULL)
	{
		Vector* v1 = vec1;

		for(int i=0 ; i < v1->size ; ++i)
			vectorAddItem(v, v1->arr[i]);
	}

	if(vec2 != NULL)
	{
		Vector* v2 = vec2;

		for(int i=0 ; i < v2->size ; ++i)
			vectorAddItem(v, v2->arr[i]);
	}

	return v;
}

void vectorPrint(void* vec)
{
	if(vec == NULL)
	{
		printf("NULL\n");
		return;
	}

	Vector* vecc = (Vector*)vec;

	if(vecc->size == 0)
	{
		printf("()\n");
		return;
	}

	printf("(");
	for(int i=0 ; i < vecc->size ; ++i)
	{
		printf("%d",vecc->arr[i]);
		if(i < vecc->size - 1)
			printf(" ");
	}
	printf(")\n");
}

void setIOAndStart(FILE* in, FILE* out)
{
	yyin = in;
	yyout = out;
	yyparse();
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

#endif