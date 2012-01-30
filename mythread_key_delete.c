/*Single Author Info:
mkotyad Munawira Kotyad */

/* Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta */

#include "linklist_kv.h"


extern mythread_queue_t *mythread_queue;

int mythread_key_delete(mythread_key_t key)
{
 
	int id;
	id = key.keyID;

	mythread_keyval_t *currKeyVal;
	currKeyVal= (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
	
	mythread_key_t *currKey;
	currKey = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
		
	currKey = mythread_key_helper->headkey;	
	
	/*Identifying the right key*/	
	while(currKey != mythread_key_helper->tailkey)
	{
		if(currKey->keyID == id)
		{
			break;
		}
		currKey = currKey->next;
	}
	
	/*Free the Key memory*/
	free(currKey->mythread_keyval_helper);
	return(0);
}

