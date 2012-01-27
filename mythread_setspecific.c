#include "mythread.h"
/*
 * mythread_setspecific - thread-specific data management
 * The  mythread_setspecific()  function  shall associate a thread-specific
 * value with a key obtained via a previous call to  mythread_key_create().
 * Different threads may bind different values to the same key. These val
 * ues are typically pointers to blocks of  dynamically  allocated  memory
 *that have been reserved for use by the calling thread.
 */
extern mythread_queue_t *mythread_queue;

int mythread_setspecific(mythread_key_t key, const void *value)
{
	mythread_keyval_t *currKeyVal;
	currKeyVal = (mythread_keyval_t *) malloc(sizeof(mythread_keyval_t));
  // get the id of the current thread and assign the value to that specific keyval
	//Iterate through Key -> Keyval to find the thread that matches with the currThread
	currKeyVal = key.mythread_keyval_helper->headkeyval;
	
	while(currKeyVal !=NULL)// or (currKeyVal != key.mythread_keyval_helper,tailkeyval)

	{
		if(currKeyVal->thread->pid = mythread_queue->currThread->pid)
		{			
			break;
		}
		else
		currKeyVal= currKeyVal->next;
	} 	
	currKeyVal->value = value;
 /*Handle error conditions and return value */
}

