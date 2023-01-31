#include "FileSystem.h"

struct Record
{
	int transactionId;
	char type[TYPE_NAME_SIZE];
	char nameOfStreet[STREET_NAME_SIZE];
	double surface;
	double price;

	struct Record* next;
};

struct File
{
	int day, month, year;

	struct Record* head;
	struct File* next;
};

struct Directory
{
	char name[DIRECTORY_NAME_SIZE];

	struct File* head;
	struct Directory* next;
};

struct Dataset
{
	struct Directory* head;
};

int isBetween(File*, char*, char*);

Dataset* Dataset_init()
{
	return x_calloc(1, sizeof(Dataset));
}

int Dataset_add(Dataset* dataset, Directory* directory)
{
	if(dataset == NULL || directory == NULL)
		return -1;

	if(dataset->head == NULL)
	{
		dataset->head = directory;
		return 0;
	}

	Directory* iter = NULL;

	for(iter = dataset->head ; iter->next != NULL ; iter = iter->next);

	iter->next = directory;
	return 0;
}

char* Dataset_getFirstDirName(Dataset* dataset)
{
	if(dataset == NULL || dataset->head == NULL)
		return NULL;

	return dataset->head->name;
}

char* Dataset_getLastDirName(Dataset* dataset)
{
	if(dataset == NULL || dataset->head == NULL)
		return NULL;

	for(Directory* iter = dataset->head ; TRUE ; iter = iter->next)
		if(iter->next == NULL)
			return iter->name;
}

int Dataset_contains(Dataset* dataset, const char* directoryName)
{
	if(dataset == NULL || directoryName == NULL)
		return 0;
	
	for(Directory* iter = dataset->head ; iter != NULL ; iter = iter->next)
		if(strcmp(directoryName, iter->name) == 0)
			return 1;

	return 0;
}

int Dataset_searchByCriteria(Dataset* dataset, char* directoryName, char* startDate, char* endDate, char* type)
{
	if(dataset == NULL || directoryName == NULL)
		return 0;

	int searchAllFlag = 0, total = 0;

	if(*directoryName == '\0')
		searchAllFlag = 1;

	for(Directory* dirIter = dataset->head ; dirIter != NULL ; dirIter = dirIter->next)
	{
		if(!searchAllFlag && strcmp(dirIter->name, directoryName) != 0)
			continue;

		for(File* fileIter = dirIter->head ; fileIter != NULL ; fileIter = fileIter->next)
		{
			if(!isBetween(fileIter, startDate, endDate))
				continue;

			for(Record* recordIter = fileIter->head ; recordIter != NULL ; recordIter = recordIter->next)
				if(strcmp(type, recordIter->type) == 0)
					++total;
		}
	}

	return total;
}

void Dataset_free(Dataset* dataset)
{
	if(dataset == NULL)
		return;

	Directory_free(dataset->head);
	free(dataset);
}

Directory* Directory_init()
{
	return x_calloc(1, sizeof(Directory));
}

Directory* Directory_initWithName(const char* name)
{
	Directory* directory = Directory_init();

	strcpy(directory->name, name);

	return directory;
}

int Directory_add(Directory* directory, File* file)
{
	if(directory == NULL || file == NULL)
		return -1;

	if(directory->head == NULL)
	{
		directory->head = file;
		return 0;
	}

	File* iter = NULL;

	for(iter = directory->head ; iter->next != NULL ; iter = iter->next);

	iter->next = file;
	return 0;
}

void Directory_free(Directory* directory)
{
	if(directory == NULL)
		return;

	File_free(directory->head);
	Directory_free(directory->next);
	free(directory);
}

File* File_init()
{
	return x_calloc(1, sizeof(File));
}

File* File_initWithDate(const char* date)
{
	int day = 0, month = 0, year = 0, total = 0, res = 0;

	res = sscanf(date, "%d-%d-%d%n", &day, &month, &year, &total);

	if(res != 3 && total != strlen(date))
		return NULL;
	
	File* file = File_init();

	file->day = day;
	file->month = month;
	file->year = year;

	return file;	
}

int File_add(File* file, Record* record)
{
	if(file == NULL || record == NULL)
		return -1;

	if(file->head == NULL)
	{
		file->head = record;
		return 0;
	}

	Record* iter = NULL;

	for(iter = file->head ; iter->next != NULL ; iter = iter->next);

	iter->next = record;
	return 0;
}

void File_free(File* file)
{
	if(file == NULL)
		return;

	Record_free(file->head);
	File_free(file->next);
	free(file);
}

Record* Record_init()
{
	return x_calloc(1, sizeof(Record));
}

Record* Record_initWithContent(const char* content)
{
	int transactionId = 0, result = 0, total = 0;
	double surface = 0, price = 0;
	char type[TYPE_NAME_SIZE], nameOfStreet[STREET_NAME_SIZE];

	memset(type, 0, TYPE_NAME_SIZE);
	memset(nameOfStreet, 0, STREET_NAME_SIZE);

	result = sscanf(content, "%d %s %s %lf %lf%n", &transactionId, type, nameOfStreet, &surface, &price, &total);

	if(result != 5 || total != strlen(content))
		return NULL;

	Record* record = Record_init();

	record->transactionId = transactionId;
	strcpy(record->type, type);
	strcpy(record->nameOfStreet, nameOfStreet);
	record->surface = surface;
	record->price = price;
	return record;
}

void Record_free(Record* record)
{
	if(record == NULL)
		return;

	Record_free(record->next);
	free(record);
}

void print(Dataset* dataset)
{
	for(Directory* iter1 = dataset->head ; iter1 != NULL ; iter1 = iter1->next)
	{
		printf("--%s\n", iter1->name);

		for(File* iter2 = iter1->head ; iter2 != NULL ; iter2 = iter2->next)
		{
			printf("%d.%d.%d\n", iter2->day, iter2->month, iter2->year);

			for(Record* iter3 = iter2->head ; iter3 != NULL ; iter3 = iter3->next)
				printf("%d %s %s %lf %lf\n", iter3->transactionId, iter3->type, iter3->nameOfStreet, iter3->surface, iter3->price);
		}
	}
}

int isBetween(File* file, char* startDate, char* endDate)
{
	int sDay = 0 , sMonth = 0, sYear = 0, eDay = 0, eMonth = 0, eYear = 0;
	double startDateTotalDay = 0, endDateTotalDay = 0, totalDay = 0;

	sscanf(startDate, "%d-%d-%d", &sDay, &sMonth, &sYear);
	sscanf(endDate, "%d-%d-%d", &eDay, &eMonth, &eYear);

	totalDay = (file->year - 2000) * 365 + file->month * 30 + file->day;
	startDateTotalDay = (sYear - 2000) * 365 + sMonth * 30 + sDay;
	endDateTotalDay = (eYear - 2000) * 365 + eMonth * 30 + eDay;

	return totalDay >= startDateTotalDay && totalDay <= endDateTotalDay;
}