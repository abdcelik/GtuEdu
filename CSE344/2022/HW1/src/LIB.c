#include "LIB.h"

void* x_malloc(size_t size)
{
	void* v = malloc(size);

	if(!v)
		x_error(__func__, "Malloc could not allocate space properly");

	return v;
}

void* x_calloc(size_t nmemb, size_t size)
{
	void* v = calloc(nmemb, size);

	if(!v)
		x_error(__func__, "Calloc could not allocate space properly");

	return v;
}

void x_error(const char* f, char *msg)
{
	fprintf(stderr, "Error, %s: %s with [errno:%s]\n", f, msg, strerror(errno));
	exit(EXIT_FAILURE);
}