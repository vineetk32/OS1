/*
Single Author Info:
vineet Vineet Krishnan

Group info:
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */


#include "mythread.h"

mythread_queue_t *mythread_queue;
static int __isInit;

//THE "idle" thread.
mythread_t idle_thread;

//Main thread.
mythread_helper_t *main_thread;


enum MERRORSTATE mythread_swapcontext(mythread_helper_t *currThread)
{
	//Stop the current thread and move it to the back of the queue
	mythread_q_move_to_end(mythread_queue,currThread);
	futex_down(&currThread->thread_futex);
	currThread->currState = READY;
	
	//Start the next thread
	__dispatcher();
}


//Dispatcher get the topmost ready thread in the queue and runs it.
void __dispatcher()
{
	mythread_queue->currThread = mythread_q_get_highest_ready_thread(mythread_queue);

	//Hopefully, this wont happen.
	if (mythread_queue->currThread->pid != idle_thread)
	{
		mythread_queue->currThread->currState = RUNNING;
		futex_up(&mythread_queue->currThread->thread_futex);
	}
	return;
}


//TODO: What about the idle threads futex??
void *idler_function(void *argument)
{
	//TODO: Replace this with a mythread_yield().
	//Just call the dispatcher
	__dispatcher();
	//TODO - replace this call with a better "mythread_swapcontext
}

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

// This wrapper is used as a workaround for the different signatures for clone and mythread_create.
// It also blocks the newly created thread until the dispatcher unblocks the futex.

int __functionWrapper(void *argument)
{
	wrapper_package_t *package = (wrapper_package_t *) argument;

	//Dispatcher will set this futex.
	futex_up(&package->thisThread->thread_futex);
	package->start_func(package->arg);
	
	return 0;
}


int mythread_create(mythread_t *new_thread_ID, mythread_attr_t *attr,void * (*start_func)(void *),void *arg)
{
	int clone_flags;
	wrapper_package_t package;
	unsigned long stackSize;

	mythread_helper_t *newThread = (mythread_helper_t *) malloc (sizeof(mythread_helper_t));

	//First call to mythread_create should init the idle thread.
	if (__isInit == 0)
	{
		//Allocate the thread queue first.
		mythread_queue = (mythread_queue_t *) malloc (sizeof(mythread_queue_t));
		//Add the main thread to it
		//TODO: Does the main_thread really need to be global var?
		__add_main_thread();
		__isInit = 1;
		mythread_create(&idle_thread,NULL,idler_function,NULL);
	}

	mythread_helper_init(newThread);

	//Take the stack size of the thread from attr, if it exists.
	/*if (attr != NULL)
	{
		stackSize = *attr;
	}
	else
	{
		stackSize = SIGSTKSZ;
	}*/
	stackSize = SIGSTKSZ;

	newThread->threadStack = (char *) malloc(stackSize * sizeof (char));
	if (newThread->threadStack == NULL)
	{
		writeLog(__func__,VSEVERE,"\nERROR: Failed malloc!");
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

	clone_flags = (CLONE_FS | CLONE_FILES |  CLONE_VM);


	// Call clone to start the thread and set its state as ready.
	package.arg = arg;
	package.start_func = start_func;
	
	newThread->currState = READY;
	if (mythread_q_count(mythread_queue) == 0)
	{
		mythread_q_init(mythread_queue,newThread);
	}
	else
	{
		mythread_q_append(mythread_queue,newThread);
	}
	
	newThread->pid = clone(&__functionWrapper,(char *) newThread->threadStack,clone_flags,(void *)&package);

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


enum MERRORSTATE __add_main_thread()
{
	mythread_t tid;
	tid = getpid();
	main_thread = (mythread_helper_t *) malloc (sizeof(mythread_helper_t));
	if (mythread_helper_init(main_thread) != MNOERR)
	{
		main_thread->pid = tid;
		main_thread->currState = RUNNING;
	}
	else
	{
		return MERR_GENERIC;
	}
	//Main thread is running, so set its futex.
	futex_up(&main_thread->thread_futex);
	return MNOERR;
}
