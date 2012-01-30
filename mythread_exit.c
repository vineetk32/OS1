/* 
Single Author Info:
vineet Vineet Krishnan

Group info:
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */


#include "mythread.h"

extern mythread_queue_t *mythread_queue;

//Clean up all data structures, and set appropriate states.
//TODO: Lots
void mythread_exit(void *retval)
{
	mythread_helper_t *joiner_thread;

	mythread_queue->currThread->currState = TERMINATED;
	//The thread waiting on the join shouldn't be blocked anymore.
	if (mythread_queue->currThread->joiner_thread > 0)
	{
		joiner_thread = mythread_q_find(mythread_queue,mythread_queue->currThread->joiner_thread);
		if (joiner_thread != NULL)
		{
			joiner_thread->currState = READY;
		}
	}
	if (mythread_q_remove_specific(mythread_queue,mythread_queue->currThread->pid) != 0)
	{
		writeLog(__func__,VSEVERE,"Error removing thread from queue");
	}
	//TODO: Clean out the whole thread queue at final exit.
	//mythread_helper_destroy(mythread_queue->currThread);
	__run_next_thread();
	return;
}
