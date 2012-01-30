/* 
Single Author Info:
vineet Vineet Krishnan

Group info:
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */


#include "mythread.h"

extern mythread_queue_t *mythread_queue;

int mythread_join(mythread_t target_thread, void **status)
{
	char logStr[128] = {'\0'};
	mythread_helper_t *joinee_thread;
	if (target_thread > 0)
	{
		joinee_thread = mythread_q_find(mythread_queue,target_thread);

		if (joinee_thread != NULL )
		{
			//If thread is terminated or is already party to another join, exit.
			if (joinee_thread->currState == TERMINATED || joinee_thread->joiner_thread != 0)
			{
				sprintf(logStr,"Thread %d has joiner_thread %d",target_thread, joinee_thread->joiner_thread);
				writeLog(__func__,VDEBUG,logStr);
				return MNOERR;
			}

			joinee_thread->joiner_thread = mythread_queue->currThread->pid;
			mythread_queue->currThread->currState = WAITING;
			mythread_swapcontext(mythread_queue->currThread);
			//TODO: Should state be set as TERMINATED here or in mythread_exit()?
			return MNOERR;
		}
		else
		{
			sprintf(logStr,"Couldnt find thread %d in the queue",target_thread);
			writeLog(__func__,VSEVERE,logStr);
			return MERR_INVALIDTID;
		}
	}
	else
	{
		return MERR_INVALIDTID;
	}
}
