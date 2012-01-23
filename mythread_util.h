#ifndef __UTIL_H
#define __UTIL_H

#include "string.h"
#include "mythread_defines.h"
#include <time.h>
#include <stdlib.h>

#define MAX_WORDS 20
#define MAX_WORD_LENGTH 256
#define BUFFER_SIZE 1024
#define MAX_PROCESSES 12


enum VLOGLEVEL
{
	VINFO = 0,
	VWARNING,
	VERROR,
	VSEVERE
};

int splitLine(const char *in, char **out,const char *delim);
int arrayContains(const char **array, const char *element, int arrayLen);
int writeLog(char *sourceFunction,enum VLOGLEVEL loglevel,char *logStr);
int mythread_helper_init(mythread_helper_t *helper);
void mythread_helper_destroy(mythread_helper_t *helper);

#endif
