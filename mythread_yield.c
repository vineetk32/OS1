/*
Single Author Info:
vgumash Vaibhav Gumashta

Group info:
vineet Vineet Krishnan
mkotyad Munawira Kotyad */

/*
mythread_yield - switch from running thread to the next ready one
*/

#include "mythread.h"

extern mythread_queue_t *mythread_queue;

int mythread_yield(void) 
{
    mythread_helper_t *currNode = mythread_queue->currThread;
    // Give processor control to the nextReadyNode
    // Change the currNode's state to READY
    currNode->currState = READY;
    //Run the next read-to-run thread.
    mythread_swapcontext(currNode);
    return 0;
}
