#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

#include <string.h>
#include "../Utility/Lib.h"

#define DATE_NAME_SIZE 16
#define TYPE_NAME_SIZE 32
#define STREET_NAME_SIZE 128
#define DIRECTORY_NAME_SIZE 256

typedef struct Record Record;
typedef struct File File;
typedef struct Directory Directory;
typedef struct Dataset Dataset;

Dataset* Dataset_init();
int Dataset_add(Dataset*, Directory*);
char* Dataset_getFirstDirName(Dataset*);
char* Dataset_getLastDirName(Dataset*);
int Dataset_contains(Dataset*, const char*);
int Dataset_searchByCriteria(Dataset*, char*, char*, char*, char*);
void Dataset_free(Dataset*);

Directory* Directory_init();
Directory* Directory_initWithName(const char*);
int Directory_add(Directory*, File*);
void Directory_free(Directory*);

File* File_init();
File* File_initWithDate(const char*);
int File_add(File*, Record*);
void File_free(File*);

Record* Record_init();
Record* Record_initWithContent(const char*);
void Record_free(Record*);

void print(Dataset*);

#endif