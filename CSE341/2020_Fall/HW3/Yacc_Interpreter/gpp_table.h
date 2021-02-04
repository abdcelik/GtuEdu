#ifndef _GPP_TABLE_H_
#define _GPP_TABLE_H_

#include <stdlib.h>
#include <string.h>

int yyerror(char* s);
int yylex();

typedef struct
{
	char id[16];
	int val;
}Entry;

typedef struct
{
	Entry* entry;
	int size;
	int capacity;
}SymbolTable;

SymbolTable* table;

void tableCreate()
{
	table = (SymbolTable*)malloc(sizeof(SymbolTable));

	table->size = 0;
	table->capacity = 1;
	table->entry = (Entry*)malloc(sizeof(Entry));
}

void tableUpdate()
{
	table->capacity *= 2;
	table->entry = (Entry*)realloc(table->entry, sizeof(Entry) * table->capacity);
}

int tableContains(char* id)
{
	for(int i=0 ; i < table->size ; ++i)
		if(strcmp(table->entry[i].id, id) == 0)
			return i;
	return -1;
}

void tablePut(char* id, int val)
{
	int i;

	if((i = tableContains(id)) != -1)
	{
		table->entry[i].val = val;
		return;
	}

	if(table->size == table->capacity)
		tableUpdate();

	strcpy(table->entry[table->size].id, id);
	table->entry[table->size].val = val;
	++(table->size);
}

Entry* tableGet(char* id)
{
	int i;

	if((i = tableContains(id)) == -1)
		return NULL;
	return &table->entry[i];
}

void tableFree()
{
	if(table != NULL)
	{
		if(table->entry != NULL)
			free(table->entry);
		free(table);
	}
}

#endif