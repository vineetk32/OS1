#include "mythread.h"

mythread_helper_t threads[10];
mythread_tcb_t mythread_tcb;

int helloClone(void *test)
{
	char *text;
	int myPid;
	
	text = (char *) malloc (sizeof(char) * (strlen(test) + 16));
	myPid = getpid();

	sprintf(text,"\n%d:Hello, %s\n",myPid,(char *) test);
	write(1,text,strlen(text));
	free(text);
	return 0;
}

int mythread_create(mythread_t *new_thread_ID, mythread_attr_t *attr,void * (*start_func)(void *),void *arg)
{
	int clone_flags;

	threads[mythread_tcb.currThread].threadStack = (char *) malloc(MYTHREAD_STACK_SIZE * sizeof (char *));
	if (threads[mythread_tcb.currThread].threadStack == NULL)
	{
		printf("\nERROR: Failed malloc!");
		return (int) MERR_MALLOC;
	}

	//Stack grows downwards, so clone needs to be given the highest mem address.
	 threads[mythread_tcb.currThread].threadStack += MYTHREAD_STACK_SIZE;

	
	/* From libpthread::createthread.c
	
	CLONE_VM, CLONE_FS, CLONE_FILES
	These flags select semantics with shared address space and
	file descriptors according to what POSIX requires.
	
	*/

	clone_flags = (CLONE_FS | CLONE_FILES |  CLONE_VM);

	threads[mythread_tcb.currThread].pid = clone(&helloClone,(char *) threads[mythread_tcb.currThread].threadStack,clone_flags,"Vineet");
	if ( threads[mythread_tcb.currThread].pid == -1)
	{
		free(threads[mythread_tcb.currThread].threadStack);
		writeLog(__func__,VSEVERE,"Clone Failed");
	}
	mythread_tcb.currThread++;
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
