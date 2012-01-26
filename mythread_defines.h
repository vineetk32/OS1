/* This file has been edited and contributed to by everyone, so it doesn't have any single author info.

Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */

#ifndef __MYTHREAD_DEFINES
#define __MYTHREAD_DEFINES

#include "futex.h"

typedef unsigned long int pthread_t;
typedef unsigned long int mythread_t;

//This is used only to hold the stacksize
typedef unsigned long mythread_attr_t;


enum MERRORSTATE
{
	MNOERR = 0,
	MERR_MALLOC,
	MERR_LOG,
	MERR_CLONE,
	MERR_GENERIC
};

enum MTHREADSTATE
{
	//State when first inited
	NEW = 0,
	//State when first created
	READY,
	//Obvious
	RUNNING,
	//State when mythread_join is called
	WAITING,
	//After mythread_exit
	TERMINATED
};

typedef struct mythread_helper
{
	mythread_t pid;
	char *threadStack;
	struct mythread_helper *prev,*next;
	enum MTHREADSTATE currState;
	//Add more variables here.
	struct futex thread_futex;
	//No idea where i'm going to use this.
	int hasJoiners;
} mythread_helper_t;

typedef struct mythread_queue
{
	mythread_helper_t *head,*tail;
	//Convenience data structure.
	mythread_helper_t *currThread;
	//Add more later
} mythread_queue_t;

typedef struct wrapper_package
{
	void * (*start_func)(void *);
	void *arg;
	mythread_helper_t *thisThread;
} wrapper_package_t;

#endif
