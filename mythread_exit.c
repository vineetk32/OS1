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

	mythread_q_remove_specific(mythread_queue,mythread_queue->currThread->pid);
	mythread_helper_destroy(mythread_queue->currThread);
	//TODO: what should mythread_tcb.currThread be set to?
	return;
}
