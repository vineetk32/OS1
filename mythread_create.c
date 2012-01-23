/* This file has been edited and contributed to by everyone, so it doesn't have any single author info.

Single Author Info:
vineet Vineet Krishnan

Group info:
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */


#include "mythread.h"

mythread_tcb_t mythread_tcb;

int helloClone(void *test)
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

int mythread_create(mythread_t *new_thread_ID, mythread_attr_t *attr,void * (*start_func)(void *),void *arg)
{
	int clone_flags;
	
	//TODO: Write a helper_init() function.
	mythread_helper_t *newThread = (mythread_helper_t *) malloc (sizeof(mythread_helper_t));

	newThread->threadStack = (char *) malloc(MYTHREAD_STACK_SIZE * sizeof (char *));
	if (newThread->threadStack == NULL)
	{
		printf("\nERROR: Failed malloc!");
		return (int) MERR_MALLOC;
	}

	//Stack grows downwards, so clone needs to be given the highest mem address.
	 newThread->threadStack += MYTHREAD_STACK_SIZE;

	/* From libpthread::createthread.c
	
	CLONE_VM, CLONE_FS, CLONE_FILES
	These flags select semantics with shared address space and
	file descriptors according to what POSIX requires.
	
	*/

	//Add the thread to the Queue
	 mythread_q_append(newThread);

	clone_flags = (CLONE_FS | CLONE_FILES |  CLONE_VM);

	// Call clone to start the thread and set its state as running.
	newThread->pid = clone(&helloClone,(char *) newThread->threadStack,clone_flags,"Vineet");

	newThread->currState = RUNNING;

	if ( newThread->pid == -1)
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

	mythread_tcb.currThread = 0;
	for(i = 0; i < 5; i++)
	{
		if (mythread_create(&testThreads[i],NULL,NULL,NULL) != MNOERR)
		{
			writeLog(__func__,VINFO,"Exiting");
		}
		else writeLog(__func__,VINFO,"Creating.");
	}
	return 0;
}
