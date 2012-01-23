/* This file has been edited and contributed to by everyone, so it doesn't have any single author info.

Single Author Info:
vineet Vineet Krishnan

Group info:
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */


#include "mythread.h"
#include "myqueue.h"

mythread_tcb_t mythread_tcb;

//Clean up all data structures, and set appropriate states.
//TODO: Lots
void mythread_exit(void *retval)
{
	mythread_q_remove_specific(mythread_tcb.currThread->pid);
	
	mythread_tcb.currThread->currState = TERMINATED;
	mythread_tcb.currThread->next = NULL;
	mythread_tcb.currThread->prev = NULL;

	free(mythread_tcb.currThread->threadStack);
}
