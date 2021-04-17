#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <errno.h>
#include "Srch_Basis.h"
#include "FILESYS.h"

int ARG_PERMISSIONS = -1, ARG_FILESIZE = -1, ARG_NUMBEROFLINKS = -1;
char* ARG_PATH = NULL, *ARG_FILENAME = NULL, *ARG_FILETYPE = NULL;

int find(FILESYS*, char*);
int checkFile(char*, struct stat*);
int isnum(char*);
int isValidFileType(char*);
int isValidPermissions(char*);
int str_cmp(char*, char*);
int in_cmp(char, char);	// case insensitive compare
int convert_permissions_to_int(char*);
int power(int, int);

char* set_arguments(int argc, char* argv[])
{
	for(int opt = 0 ; (opt = getopt(argc, argv, ":w:f:b:t:p:l:")) != -1 ;)
		switch(opt)
		{
			case 'w':
				ARG_PATH = optarg;
				break;
			case 'f':
				if(strlen(optarg) > 255)
					return "Error! The length of the file name cannot be greater than 255.";
				ARG_FILENAME = optarg;
				break;
			case 'b':
				if(isnum(optarg) != 0)
					return "Error! The file size must be integer.";
				ARG_FILESIZE = atoi(optarg);
				break;
			case 't':
				if(isValidFileType(optarg) != 0)
					return "Error! Wrong file type.";
				ARG_FILETYPE = optarg;
				break;
			case 'p':
				if(isValidPermissions(optarg) != 0)
					return "Error! Incorrect permission.";
				ARG_PERMISSIONS = convert_permissions_to_int(optarg);
				break;
			case 'l':
				if(isnum(optarg) != 0)
					return "Error! Incorrect number of links.";
				ARG_NUMBEROFLINKS = atoi(optarg);
				break;
			default:
				return "Error! Undefined operation.";
		}

	if(!ARG_PATH)
		return "Error! The -w parameter is mandatory.";

	if(!ARG_FILENAME && ARG_FILESIZE == -1 && !ARG_FILETYPE && ARG_PERMISSIONS == -1 && ARG_NUMBEROFLINKS == -1)
		return "Error! An operator must be used.";

	if(optind < argc)
		return "Error! Additional parameter is founded.";

	if(ARG_FILENAME && *ARG_FILENAME == '+')
		return "Error! Incorrect usage of regexp.";

	return NULL;
}

int findByCriteria(FILESYS* fsys) { return find(fsys, ARG_PATH); }

int find(FILESYS* fsys, char* path)
{
	DIR* dir;
	struct dirent* entry;
	char* newPath;
	int errnoSave;

	if(!(dir = opendir(path)))
	{
		if(errno == EACCES)
			return 0;
		
		perror("opendir");
		return -1;
	}

	for(errnoSave = errno ; (entry = readdir(dir)) ; errnoSave = errno)
	{
		if(sigint_val)
		{
			fprintf(stderr, "\nCNTRL+C: All resources were given to memory and the program was terminated.\n");

			if(closedir(dir) != 0)
				perror("closedir");

			return -1;
		}

		if(str_cmp(entry->d_name, ".") == 0 || str_cmp(entry->d_name, "..") == 0)
			continue;

		char* tmpPath = (char*)calloc(strlen(path) + strlen(entry->d_name) + 2, sizeof(char));

		if(!tmpPath)
		{
			fprintf(stderr, "Error! Out of memory!\n");
			return -1;
		}

		newPath = tmpPath;
		sprintf(newPath, "%s/%s", path, entry->d_name);

		struct stat fileStat;

		if(lstat(newPath, &fileStat) < 0)
		{
			perror("lstat");

			if(closedir(dir) != 0)
				perror("closedir");

			free(newPath);
			return -1;
		}

		if(checkFile(entry->d_name, &fileStat) == 0 && FILESYS_add_path(fsys, newPath) != 0)
		{
			if(closedir(dir) != 0)
				perror("closedir");

			free(newPath);
			return -1;
		}

		if(entry->d_type == DT_DIR && find(fsys, newPath) == -1)
		{
			if(closedir(dir) != 0)
				perror("closedir");

			free(newPath);
			return -1;
		}
		
		free(newPath);
	}

	if(errnoSave != errno)
	{
		perror("readdir");

		if(closedir(dir) != 0)
			perror("closedir");

		return -1;
	}

	if(closedir(dir) != 0)
	{
		perror("closedir");
		return -1;
	}

	return 0;
}

int checkFile(char* fileName, struct stat* fileStat)
{
	if(ARG_FILENAME && str_cmp(ARG_FILENAME, fileName) != 0)
		return -1;

	if(ARG_FILESIZE != -1 && ((long long) ARG_FILESIZE) != ((long long)fileStat->st_size))
		return -1;

	if(ARG_FILETYPE)
	{
		if(*ARG_FILETYPE == 'd' && !S_ISDIR(fileStat->st_mode))
			return -1;
		if(*ARG_FILETYPE == 's' && !S_ISSOCK(fileStat->st_mode))
			return -1;
		if(*ARG_FILETYPE == 'b' && !S_ISBLK(fileStat->st_mode))
			return -1;
		if(*ARG_FILETYPE == 'c' && !S_ISCHR(fileStat->st_mode))
			return -1;
		if(*ARG_FILETYPE == 'f' && !S_ISREG(fileStat->st_mode))
			return -1;
		if(*ARG_FILETYPE == 'p' && !S_ISFIFO(fileStat->st_mode))
			return -1;
		if(*ARG_FILETYPE == 'l' && !S_ISLNK(fileStat->st_mode))
			return -1;
	}

	if(ARG_PERMISSIONS != -1 && ARG_PERMISSIONS != (fileStat->st_mode & 0xFFF))
		return -1;

	if(ARG_NUMBEROFLINKS != -1 && ARG_NUMBEROFLINKS != fileStat->st_nlink)
		return -1;

	return 0;
}

int isnum(char* str)
{
	if(str == NULL)
		return -1;

	for(int i = 0, len = strlen(str); i < len ; ++i)
		if(!isdigit(str[i]))
			return -1;
	return 0;
}

int isValidFileType(char* s)
{
	if(s == NULL || strlen(s) != 1)
		return -1;

	if(*s == 'd' || *s == 's' || *s == 'b' || *s == 'c' || *s == 'f' || *s == 'p' || *s == 'l')
		return 0;

	return -1;
}

int isValidPermissions(char* s)
{
	if(s == NULL || strlen(s) != 9)
		return -1;

	for(int i = 0 ; i < 9 ; ++i)
		if(s[i] != '-' && s[i] != 'r' && s[i] != 'w' && s[i] != 'x')
			return -1;
	
	return 0;
}

int str_cmp(char* s1, char* s2)
{
	if(s1 == NULL || s2 == NULL || *s1 == '+')
		return -1;

	for(int r = 0 ; *s1 && *s2 ;)
	{
		if(*s1 == '+')
			r = *(s1 - 1);

		if(r && in_cmp(r, *s2))
		{
			r = 0;
			++s1;
		}
		else if(r)
			++s2;
		else if(!in_cmp(*s1, *s2))
			++s1, ++s2;
		else
			break;
	}

	if(*s1 && !*s2 && *s1 == '+')
		return 0;

	return *s1 - *s2;
}

int in_cmp(char s1, char s2)
{
	if(isalpha(s1) && isalpha(s2) && (s1 == s2 || s1 - 32 == s2 || s1 + 32 == s2))
		return 0;
	return s1 - s2;
}

int convert_permissions_to_int(char* permissions)
{
	int len = strlen(permissions);
	int r = 0;

	for(int i = len-1 ; i >= 0 ; --i)
		if(permissions[i] != '-')
		{
			if(permissions[i] == 'r' || permissions[i] == 'w' || permissions[i] == 'x')
				r += power(2, len - 1 - i);
			else
				return -1;
		}

	return r;
}

int power(int base, int exp)
{
	if(exp > 0)
		return base * power(base, exp-1);
	return 1;
}