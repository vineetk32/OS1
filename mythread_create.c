/* This file has been edited and contributed to by everyone, so it doesn't have any single author info.

Single Author Info:
vineet Vineet Krishnan

Group info:
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */


#include "mythread.h"

mythread_tcb_t mythread_tcb;

void *helloClone(void *test)
{
	char *text;
	int myPid;
	
	text = (char *) malloc (sizeof(char) * (strlen((char *)test) + 16));
	myPid = getpid();

	sprintf(text,"\n%d:Hello, %s\n",myPid,(char *) test);
	write(1,text,strlen(text));
	free(text);
	return 0;
}

int functionWrapper(void *arg)
{
	wrapper_package_t *package = (wrapper_package_t *) arg;
	package->start_func();
	return 0;
}


int mythread_create(mythread_t *new_thread_ID, mythread_attr_t *attr,void * (*start_func)(void *),void *arg)
{
	int clone_flags;
	wrapper_package_t package;
	unsigned long stackSize;
	
	mythread_helper_t *newThread;
	mythread_helper_init(newThread);

	//Take the stack size of the thread from attr, if it exists.
	if (*attr != NULL)
	{
		stackSize = *attr;
	}
	else
	{
		stackSize = SIGSTKSZ;
	}

	newThread->threadStack = (char *) malloc(stackSize * sizeof (char *));
	if (newThread->threadStack == NULL)
	{
		printf("\nERROR: Failed malloc!");
		return (int) MERR_MALLOC;
	}

	//Stack grows downwards, so clone needs to be given the highest mem address.
	 newThread->threadStack += stackSize;

	/* From libpthread::createthread.c
	
	CLONE_VM, CLONE_FS, CLONE_FILES
	These flags select semantics with shared address space and
	file descriptors according to what POSIX requires.
	
	*/

	//Add the thread to the Queue
	 mythread_q_append(newThread);

	clone_flags = (CLONE_FS | CLONE_FILES |  CLONE_VM);


	// Call clone to start the thread and set its state as running.
	package.arg = arg;
	package.start_func = start_func;
	newThread->pid = clone(&functionWrapper,(char *) newThread->threadStack,clone_flags,package);

	newThread->currState = RUNNING;

	if (newThread->pid == -1)
	{
		free(newThread->threadStack);
		writeLog(__func__,VSEVERE,"Clone Failed");
	}

	return (int) MNOERR;
}

int main()
{
	mythread_t testThreads[5];
	int i;

	for(i = 0; i < 5; i++)
	{
		if (mythread_create(&testThreads[i],NULL,NULL,"World") != MNOERR)
		{
			writeLog(__func__,VINFO,"Exiting");
		}
		else writeLog(__func__,VINFO,"Creating.");
	}
	return 0;
}
