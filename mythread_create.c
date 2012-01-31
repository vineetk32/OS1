/*
Single Author Info:
vineet Vineet Krishnan

Group info:
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */



#include "mythread.h"

mythread_queue_t *mythread_queue;
static int __isInit;
extern int _system_log_level;

//THE "idle" thread.
mythread_t idle_thread;

static pid_t gettid(void) 
{
	return (pid_t) syscall(SYS_gettid);
}

//Runs the next ready thread. Is called only from mythread_exit()
void __run_next_thread()
{
	char logStr[128] = {'\0'};
	mythread_queue->currThread = mythread_q_get_highest_ready_thread(mythread_queue);
	if (mythread_queue->currThread != NULL)
	{
		mythread_queue->currThread->currState = RUNNING;
		sprintf(logStr,"Running %u",mythread_queue->currThread->pid);
		writeLog(__func__,VDEBUG,logStr);
		futex_up(&mythread_queue->currThread->thread_futex);
	}
	else
	{
		writeLog(__func__,VDEBUG,"No more threads in the READY state.");
		return;
	}
}

enum MERRORSTATE mythread_swapcontext(mythread_helper_t *currThread)
{
	char logStr[128] = {'\0'};
	mythread_helper_t *tempThread;

	//Stop the current thread and move it to the back of the queue
	mythread_q_move_to_end(mythread_queue,currThread);

	tempThread = mythread_q_get_highest_ready_thread(mythread_queue);

	//This happens with the idle thread calls yield.
	if (tempThread->pid != mythread_queue->currThread->pid)
	{
		//TODO: when all the READY threads are done, how will the WAITING threads be woken up?
		if (tempThread != NULL)
		{
			mythread_queue->currThread = tempThread;
		
			//TODO: Is a check for idle_thread needed here?
			mythread_queue->currThread->currState = RUNNING;
	
			//mythread_join may have marked its state as WAITING
			if (currThread->currState == RUNNING)
			{
				currThread->currState = READY;
			}

			sprintf(logStr,"Swapping %u and %u",currThread->pid,mythread_queue->currThread->pid);
			writeLog(__func__,VDEBUG,logStr);
			//Stop the current guy, and wake up the new guy
			writeLog(__func__,VDEBUG,"Starting new thread");
			futex_up(&(mythread_queue->currThread->thread_futex));
			writeLog(__func__,VDEBUG,"Stopping current thread");
			futex_down(&(currThread->thread_futex));
		}
		else
		{
			writeLog(__func__,VDEBUG,"No ready threads!");
		}
	}
	return MNOERR;

}


//TODO: What about the idle threads futex??
void *idler_function(void *argument)
{
	//Yield to any *other* thread
	char logStr[128] = {'\0'};
	sprintf(logStr,"Spawned idle thread - %u",mythread_self());
	writeLog(__func__,VDEBUG,logStr);
	while (mythread_q_get_alive_count(mythread_queue) > 2)	//Main thread and idle thread
	{
		mythread_yield();
	}
	//TODO: Clean up and exit.
	writeLog(__func__,VDEBUG,"idler: Cleaning up and quitting.");
	//exit(0);
	return NULL;
}

// This wrapper is used as a workaround for the different signatures for clone and mythread_create.
// It also blocks the newly created thread until the dispatcher unblocks the futex.

int __functionWrapper(void *argument)
{
	char logStr[128] = {'\0'};
	wrapper_package_t *package = (wrapper_package_t *) argument;
	mythread_helper_t *joiner_thread;

	//We're in the queue. Sleep until its our turn
	sprintf(logStr,"%u is waiting on the futex.",gettid());
	writeLog(__func__,VDEBUG,logStr);
	futex_down(&package->thisThread->thread_futex);
	writeLog(__func__,VDEBUG,"Executing threadFunction");
	package->start_func(package->arg);
	writeLog(__func__,VDEBUG,"Finished threadFunction");
	//TODO: Should this be handled somewhere else?
	mythread_queue->currThread->currState = TERMINATED;

	//The thread waiting on the join shouldn't be blocked anymore.
	if (mythread_queue->currThread->joiner_thread > 0)
	{
		joiner_thread = mythread_q_find(mythread_queue,mythread_queue->currThread->joiner_thread);
		if (joiner_thread != NULL)
		{
			joiner_thread->currState = READY;
			sprintf(logStr,"%d is join-unblocking %d",mythread_queue->currThread->pid,joiner_thread->pid);
			write(__func__,VDEBUG,logStr);
		}
	}
	mythread_swapcontext(mythread_queue->currThread);
	return 0;
}


int mythread_create(mythread_t *new_thread_ID, mythread_attr_t *attr,void * (*start_func)(void *),void *arg)
{
	int clone_flags;
	wrapper_package_t *package;
	unsigned long stackSize;
	mythread_helper_t *tempThread;
	char logBuffer[128] = {'\0'};

	mythread_helper_t *newThread = (mythread_helper_t *) malloc (sizeof(mythread_helper_t));

	//First call to mythread_create should init the idle thread.
	if (__isInit == 0)
	{
		//By default, print no messages
		_system_log_level = NONE;
		//Main thread.
		mythread_helper_t *main_thread;

		//Allocate the thread queue first.
		mythread_queue = (mythread_queue_t *) malloc (sizeof(mythread_queue_t));
		if (mythread_queue == NULL)
		{
			writeLog(__func__,VSEVERE,"Error creating thread queue!");
			return MERR_QUEUECREATE;
		}

		main_thread = (mythread_helper_t *) malloc (sizeof(mythread_helper_t));
		//Init the thread queue and add the main_thread to it.
		if (__add_main_thread(main_thread) != MNOERR)
		{
			writeLog(__func__,VSEVERE,"Error creating main thread!");
		}

		mythread_q_init(mythread_queue,main_thread);
		mythread_queue->currThread = main_thread;

		__isInit = 1;
		if (mythread_create(&idle_thread,NULL,idler_function,NULL) != MNOERR)
		{
			writeLog(__func__,VSEVERE,"Error creating idle thread!");
		}
	}

	if (mythread_helper_init(newThread) != MNOERR)
	{
		writeLog(__func__,VSEVERE,"Error initing new thread!");
		return MERR_THREADINIT;
	}

	//If the thread which calls mythread_create is currently in the thread queue,
	//increment its number of children. Ignore the idle thread.
	//TODO: Check this logic
	if (new_thread_ID != idle_thread)
	{
		tempThread = mythread_q_find(mythread_queue,(mythread_t) gettid());
		if (tempThread != NULL)
		{
			tempThread->hasChildren++;
		}
	}
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
	package = (wrapper_package_t *) malloc (sizeof(wrapper_package_t));
	if (package != NULL)
	{
		package->arg = arg;
		package->start_func = start_func;
		package->thisThread = newThread;
	}
	else
	{
		writeLog(__func__,VSEVERE,"Failed to allocate memory for wrapper package");
		return MERR_MALLOC;
	}
	
	newThread->currState = READY;

	mythread_q_append(mythread_queue,newThread);
	
	newThread->pid = clone(&__functionWrapper,(char *) newThread->threadStack,clone_flags,(void *)package);

	if (newThread->pid == -1)
	{
		free(newThread->threadStack);
		free(newThread);
		free(package);
		writeLog(__func__,VSEVERE,"Clone Failed");
		return MERR_CLONE;
	}
	else
	{
		sprintf(logBuffer,"Created thread %u",newThread->pid);
		writeLog(__func__,VDEBUG,logBuffer);
		
		*new_thread_ID = newThread->pid;
		return (int) MNOERR;
	}
}

enum MERRORSTATE __add_main_thread(mythread_helper_t *main_thread)
{
	mythread_t tid;
	tid = getpid();
	char logStr[128] = {'\0'};

	if (main_thread == NULL)
	{
		writeLog(__func__,VSEVERE,"Error allocating memory for main thread!");
		return MERR_MALLOC;
	}
	if (mythread_helper_init(main_thread) == MNOERR)
	{
		main_thread->pid = tid;
		main_thread->currState = RUNNING;
		sprintf(logStr,"Added main thread to the queue - %u",gettid());
		writeLog(__func__,VDEBUG,logStr);
	}
	else
	{
		return MERR_GENERIC;
	}
	//Main thread is running, so set its futex.
	//futex_up(&main_thread->thread_futex);
	return MNOERR;
}

int mythread_set_loglevel(int log_level)
{
	_system_log_level = log_level;
}
