#include "myqueue.h"

extern mythread_tcb_t mythread_tcb;

//Probably not needed. Remove.
void mythread_helper_q_init()
{
	mythread_tcb.head = NULL;
	mythread_tcb.tail = NULL;
	mythread_tcb.currThread = NULL;
}

//Add to head of queue
void mythread_q_append(mythread_helper_t *newElement)
{
	newElement->prev = mythread_tcb.head;
	newElement->next = NULL;
	mythread_tcb.head = newElement;
}

//Remove from tail of queue
void mythread_q_remove_end()
{
	mythread_tcb.tail = mythread_tcb.tail->next;
}

int mythread_q_remove_specific(mythread_t tid)
{
	mythread_helper_t *nodeToRemove = mythread_q_find(tid);

	if (nodeToRemove != NULL)
	{
		nodeToRemove->prev->next = nodeToRemove->next;
		nodeToRemove->next->prev = nodeToRemove->prev;

		nodeToRemove->next = NULL;
		nodeToRemove->prev = NULL;
	}
	else
	{
		return -1;
	}
}

//Get a particular thread in the queue by its threadID
mythread_helper_t *mythread_q_find(mythread_t tid)
{
	//Start at the tail and keep going ahead.
	mythread_helper_t *currNode;
	currNode = mythread_tcb.tail;
	while (currNode->next != NULL)
	{
		if (currNode->pid = tid)
		{
			break;
		}
		currNode = currNode->next;
	}
	return currNode;
}
