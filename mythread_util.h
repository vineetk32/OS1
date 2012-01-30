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
	NONE = 0,
	VINFO = 1,
	VWARNING = 2,
	VERROR = 4,
	VSEVERE = 8,
	VDEBUG = 16
};

int writeLog(const char *sourceFunction,enum VLOGLEVEL loglevel,char *logStr);
enum MERRORSTATE mythread_helper_init(mythread_helper_t *helper);
void mythread_helper_destroy(mythread_helper_t *helper);

#endif
