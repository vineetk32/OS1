/* This file has been edited and contributed to by everyone, so it doesn't have any single author info.

Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */

#ifndef __MYTHREAD_DEFINES
#define __MYTHREAD_DEFINES

typedef unsigned long int pthread_t;
typedef unsigned long int mythread_t;

//This is used only to hold the stacksize
typedef unsigned long mythread_attr_t;


enum MERRORSTATES
{
	MNOERR = 0,
	MERR_MALLOC,
	MERR_LOG,
	MERR_CLONE
};

enum MTHREADSTATE
{
	NEW = 0,
	READY,
	RUNNING,
	WAITING,
	TERMINATED
};

typedef struct wrapper_package
{
	void * (*start_func)(void *);
	void *arg;
} wrapper_package_t;

typedef struct mythread_helper
{
	mythread_t pid;
	char *threadStack;
	struct mythread_helper_t *prev,*next;
	enum MTHREADSTATE currState;
	//Add more variables here.
} mythread_helper_t;

typedef struct mythread_tcb
{
	mythread_helper_t *head,*tail;
	mythread_helper_t *currThread;
	//Add more later
} mythread_tcb_t;

#endif
