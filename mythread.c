#include "mythread.h"

int writeLog(char *sourceFunction,MLOGLEVEL loglevel,char *logStr)
{
	char *text;
	text = (char *) malloc (sizeof(char) * (strlen(logStr) + 32));
	
	//TODO: add date and then move to util
	
	//LogFormat - Date LOGLEVEL|SourceFunction|LogString
	if (loglevel == MERROR)
	{
		strcpy(text,"\nERROR|");
	}
	else if (loglevel == MWARNING)
	{
		strcpy(text,"\nWARNING|");
	}
	else if (loglevel == MSEVERE)
	{
		strcpy(text,"\nSEVERE|");
	}
	else if (loglevel == MINFO)
	{
		strcpy(text,"\nINFO|");
	}
	
	strcat(text,sourceFunction);
	strcat(text,"|");

	strcat(text,logStr);
	return write(stdout,text,strlen(text));
}

int helloClone(void *test)
{
	char *text;
	int myPid;
	
	text = (char *) malloc (sizeof(char) * (strlen(test) + 16));
	myPid = getpid();

	sprintf(text,"\n%d:Hello, %s\n",myPid,(char *) test);
	return write(stdout,text,strlen(text));
}

int mythread_create(mythread_t *new_thread_ID, mythread_attr_t *attr,void * (*start_func)(void *),void *arg)
{
	mythread_t pid;
	int clone_flags
	char *threadStack;

	threadStack = (char *) malloc(MYTHREAD_STACK_SIZE * sizeof (char *));
	//TODO: Handle failed malloc

	//Stack grows downwards, so clone needs to be given the highest mem address.
	threadStack = threadStack + MYTHREAD_STACK_SIZE;

	
	/* From libpthread::createthread.c
	
	CLONE_VM, CLONE_FS, CLONE_FILES
	These flags select semantics with shared address space and
	file descriptors according to what POSIX requires.

     CLONE_SIGNAL
	This flag selects the POSIX signal semantics.

     CLONE_SETTLS
	The sixth parameter to CLONE determines the TLS (Thread Local Storage) area for the
	new thread.

     CLONE_PARENT_SETTID
	The kernels writes the thread ID of the newly created thread
	into the location pointed to by the fifth parameters to CLONE.

	Note that it would be semantically equivalent to use
	CLONE_CHILD_SETTID but it is be more expensive in the kernel.

     CLONE_CHILD_CLEARTID
	The kernels clears the thread ID of a thread that has called
	sys_exit() in the location pointed to by the seventh parameter
	to CLONE.
	
	If CLONE_SYSVSEM is set, then the child and the calling process share a single list of System V semaphore undo values.
	If this flag is not set, then the child has a separate undo list, which is initially empty.
	
	*/

	int clone_flags = (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGNAL
		     | CLONE_SETTLS | CLONE_PARENT_SETTID
		     | CLONE_CHILD_CLEARTID | CLONE_SYSVSEM | 0);

	pid = clone(&writeLog, threadStack,clone_flags,"Vineet");
	if ( pid == -1)
	{
		free(threadStack);
		writeLog(__func__,MSEVERE,"Clone Failed");
	}
	return (int) MNOERR;
}

int main()
{
	mythread_t testThreads[5];
	int i;

	for(i = 0; i < 5; i++)
	{
		if (mythread_create(&testThreads[i],NULL,NULL,NULL) != MNOERR)
		{
			writeLog(__func__,MINFO,"Exiting");
		}
	}
	return 0;
}
