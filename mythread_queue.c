/*
Single Author Info:
vineet Vineet Krishnan

Group info:
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */

#include "mythread_queue.h"

//Structure of queue - HEAD --prev---> 1 ---> 2 ... --prev---> TAIL
//                     TAIL --next---> 2----> 1 ... --next---> HEAD

//Same as mythread_q_append, only used first time because head and tail need to be setup properly.
void mythread_q_init(mythread_queue_t *queue,mythread_helper_t *newElement)
{
	newElement->prev = NULL;
	newElement->next = NULL;
	queue->head = newElement;
	queue->tail = newElement;
}

//Add to head of queue
void mythread_q_append(mythread_queue_t *queue,mythread_helper_t *newElement)
{
	newElement->prev = queue->head;
	queue->head->next = newElement;
	newElement->next = NULL;
	queue->head = newElement;
}

//Remove from tail of queue
void mythread_q_remove_end(mythread_queue_t *queue)
{
	queue->tail = queue->tail->next;
}

int mythread_q_remove_specific(mythread_queue_t *queue,mythread_t tid)
{
	mythread_helper_t *nodeToRemove = mythread_q_find(queue,tid);

	if (nodeToRemove != NULL)
	{
		if (nodeToRemove != queue->head)
		{
			nodeToRemove->next->prev = nodeToRemove->prev;
		}
		else
		{
			queue->head = nodeToRemove->prev;
		}
		if (nodeToRemove != queue->tail)
		{
			nodeToRemove->prev->next = nodeToRemove->next;
		}
		else
		{
			queue->tail = nodeToRemove->next;
		}

		nodeToRemove->next = NULL;
		nodeToRemove->prev = NULL;
	}
	else
	{
		return -1;
	}
	return 0;
}

//Get a particular thread in the queue by its threadID
mythread_helper_t *mythread_q_find(mythread_queue_t *queue,mythread_t tid)
{
	//Start at the tail and keep going ahead.
	mythread_helper_t *currNode;
	currNode = queue->tail;
	while (currNode != NULL)
	{
		if (currNode->pid == tid)
		{
			break;
		}
		currNode = currNode->next;
	}
	return currNode;
}

unsigned int mythread_q_count(mythread_queue_t *queue)
{
	unsigned int count = 0;
	mythread_helper_t *currNode;
	currNode = queue->tail;
	if (currNode == NULL)
	{
		return 0;
	}
	while (currNode->next != NULL)
	{
		currNode = currNode->next;
		count++;
	}
	return count;
}

//Get the total count of threads in the non-dead state.
unsigned int mythread_q_get_alive_count(mythread_queue_t *queue)
{
	unsigned int count = 0;
	mythread_helper_t *currNode;
	currNode = queue->tail;
	if (currNode == NULL)
	{
		return 0;
	}
	while (currNode->next != NULL)
	{
		currNode = currNode->next;
		if (currNode->currState != TERMINATED)
		{
			count++;
		}
	}
	return count;
}

//Get the total count of threads in the ready state.
unsigned int mythread_q_get_ready_count(mythread_queue_t *queue)
{
	unsigned int count = 0;
	mythread_helper_t *currNode;
	currNode = queue->tail;
	if (currNode == NULL)
	{
		return 0;
	}
	while (currNode->next != NULL)
	{
		currNode = currNode->next;
		if (currNode->currState == READY)
		{
			count++;
		}
	}
	return count;
}
//Moves an element to the head of the queue (which is the "end" of the queue)
void mythread_q_move_to_end(mythread_queue_t *queue,mythread_helper_t *currElement)
{
	if (currElement != queue->head)
	{
		currElement->next->prev = currElement->prev;

		if (currElement != queue->tail)
		{
			currElement->prev->next = currElement->next;
		}
		else
		{
			queue->tail = currElement->next;
		}
		currElement->prev = queue->head;
		queue->head->next = currElement;

		currElement->next = NULL;
		queue->head = currElement;
	}
}

//Get the highest ready element in the queue
mythread_helper_t *mythread_q_get_highest_ready_thread(mythread_queue_t *queue)
{
	//Start at the tail and keep going ahead.
	mythread_helper_t *currNode;
	currNode = queue->tail;
	while (currNode != NULL)
	{
		if (currNode->currState == READY)
		{
			return currNode;
		}
		currNode = currNode->next;
	}
	return currNode;
}
