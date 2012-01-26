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
	joinee_thread = mythread_q_find(mythread_queue,target_thread);

	//TODO: Is there any point in storing the count of joiners?
	joinee_thread->hasJoiners++;
	mythread_swapcontext(mythread_queue->currThread);
}

mythread_t mythread_self(void)
{
	return (mythread_queue->currThread->pid);

}
