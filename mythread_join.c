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
	mythread_helper_t *joinee_thread;
	if (target_thread > 0)
	{
		joinee_thread = mythread_q_find(mythread_queue,target_thread);

		if (joinee_thread != NULL)
		{
			if (joinee_thread->currState == TERMINATED)
			{
				return MNOERR;
			}
			//TODO: Is there any point in storing the count of joiners?
			joinee_thread->hasJoiners++;
			mythread_queue->currThread->currState = WAITING;
			mythread_swapcontext(mythread_queue->currThread);
			//TODO: Should state be set as TERMINATED here or in mythread_exit()?
			return MNOERR;
		}
		else
		{
			return MERR_INVALIDTID;
		}
	}
	else
	{
		return MERR_INVALIDTID;
	}
}
