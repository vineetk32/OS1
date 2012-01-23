#include "mythread_defines.h"
#include <stdio.h>

#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

//Initializes the queue
void mythread_q_init();

//Add to head of queue
void mythread_q_append(mythread_helper_t *newElement);

//Remove from tail of queue
void mythread_q_remove();

//Get a particular thread in the queue by its threadID
mythread_helper_t *mythread_q_find(mythread_t tid);

int mythread_q_remove_specific(mythread_t tid);

#endif