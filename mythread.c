#include "mythread.h"

mythread_helper_t threads[10];

int helloClone(void *test)
{
	char *text;
	int myPid;
	
	text = (char *) malloc (sizeof(char) * (strlen(test) + 16));
	myPid = getpid();

	sprintf(text,"\n%d:Hello, %s\n",myPid,(char *) test);
	//printf(text);
	write(1,text,strlen(text));
	free(text);
}

int mythread_create(mythread_t *new_thread_ID, mythread_attr_t *attr,void * (*start_func)(void *),void *arg)
{
	int clone_flags;
	static int currThread = 0;

	threads[currThread].threadStack = (char *) malloc(MYTHREAD_STACK_SIZE * sizeof (char *));
	if (threads[currThread].threadStack == NULL)
	{
		printf("\nERROR: Failed malloc!");
		return (int) MERR_MALLOC;
	}

	//Stack grows downwards, so clone needs to be given the highest mem address.
	 threads[currThread].threadStack += MYTHREAD_STACK_SIZE;

	
	/* From libpthread::createthread.c
	
	CLONE_VM, CLONE_FS, CLONE_FILES
	These flags select semantics with shared address space and
	file descriptors according to what POSIX requires.
	
	*/

	clone_flags = ( CLONE_FS | CLONE_FILES |  CLONE_VM);

	threads[currThread].pid = clone(&helloClone,(char *) threads[currThread].threadStack,clone_flags,"Vineet");
	if ( threads[currThread].pid == -1)
	{
		free(threads[currThread].threadStack);
		//writeLog(__func__,MSEVERE,"Clone Failed");
	}
	currThread++;
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
			//writeLog(__func__,MINFO,"Exiting");
		}
		else printf("\nCreated!");
	}
	return 0;
}

int writeLog(char *sourceFunction,enum MLOGLEVEL loglevel,char *logStr)
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
	return write(1,text,strlen(text));
}
