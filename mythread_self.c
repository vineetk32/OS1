/*
Single Author Info:
vgumash Vaibhav Gumashta

Group info:
vineet Vineet Krishnan
mkotyad Munawira Kotyad */


#include "mythread.h"

/*
	mythread_self - thread id of running thread
*/
// Assuming mythread_queue is the pointer to the queue that has all the thread nodes

extern mythread_queue_t *mythread_queue;

mythread_t mythread_self(void) 
{
	mythread_helper_t *currNode = mythread_queue->currThread;
	return currNode->pid;
}

