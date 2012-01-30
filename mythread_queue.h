#include "mythread_defines.h"
#include <stdio.h>

#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

//Initializes the queue
void mythread_q_init(mythread_queue_t *queue,mythread_helper_t *newElement);

//Add to head of queue
void mythread_q_append(mythread_queue_t *queue,mythread_helper_t *newElement);

//Remove from tail of queue
void mythread_q_remove(mythread_queue_t *queue);

//Get a particular thread in the queue by its threadID
mythread_helper_t *mythread_q_find(mythread_queue_t *queue,mythread_t tid);

int mythread_q_remove_specific(mythread_queue_t *queue,mythread_t tid);
unsigned int mythread_q_count(mythread_queue_t *queue);

void mythread_q_move_to_end(mythread_queue_t *queue,mythread_helper_t *currElement);
mythread_helper_t *mythread_q_get_highest_ready_thread(mythread_queue_t *queue);
unsigned int mythread_q_get_alive_count(mythread_queue_t *queue);
unsigned int mythread_q_get_ready_count(mythread_queue_t *queue);

#endif
