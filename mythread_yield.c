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
    // mythread_helper_t *nextReadyNode = mythread_q_get_highest_ready_thread(mythread_queue); 
    // Give processor control to the nextReadyNode (??? what all should we do here)
    // Change the currNode's state to READY
    currNode->currState = READY;
    // Place currNode at the end of the queue
    mythread_q_append(mythread_queue, currNode); 
    // Call the dispatcher to run the next highest ready element
    __dispatcher(); 
    return 0;
}
