/* This file has been edited and contributed to by everyone, so it doesn't have any single author info.

Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */

#ifndef __MYTHREAD_DEFINES
#define __MYTHREAD_DEFINES

//Max stack size per-thread
//TODO: use this as upper boundary for mmap later.
#define MYTHREAD_STACK_SIZE 1024

typedef unsigned long int pthread_t;
typedef unsigned long int mythread_t;

//This is unused anyway, so assign anything to it.
typedef int mythread_attr_t;

enum MLOGLEVEL
{
	MINFO = 0,
	MWARNING,
	MERROR,
	MSEVERE
};

enum MERRORSTATES
{
	MNOERR = 0,
	MERR_MALLOC,
	MERR_LOG,
	MERR_CLONE
};

enum MTHREADSTATE
{
	NONE = 0,
	RUNNING,
	BLOCKED
};

typedef struct mythread_helper_t
{
	mythread_t pid;
	char *threadStack;
	//Will be used later when the thread Q is implemented as a doubly-linked list.
	struct mythread_helper_t *prev,*next;
	enum MTHREADSTATE currState;
	//Add more variables here.
} mythread_helper_t;

#endif
