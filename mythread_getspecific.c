/*Single Author Info:
mkotyad Munawira Kotyad */

/* Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta */


#include "linklist_kv.h"

extern mythread_queue_t *mythread_queue;

void *mythread_getspecific(mythread_key_t key)
{
	int id;
	id = key.keyID;	

	mythread_keyval_t *currKeyVal;
	currKeyVal= (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
	
	mythread_key_t *currKey;
	currKey = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
		
	currKey = mythread_key_helper.headkey;	
	/*Identifying the right key*/	
	while(currKey != mythread_key_helper.tailkey)
	{	
		
		if(currKey->keyID == id)
		{
			break;
		}
		currKey = currKey->next;
		

	}

	currKeyVal = currKey->mythread_keyval_helper->headkeyval;
	/*Identifying the right thread*/
	while(currKeyVal->next != currKey->mythread_keyval_helper->tailkeyval)
	{	
		
		if(currKeyVal->thread->pid == mythread_queue->currThread->pid)
		{			
			break;
		}
		else
		currKeyVal= currKeyVal->next;
	} 
	
	return(currKeyVal->value);

}



