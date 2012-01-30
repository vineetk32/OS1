/* Single Author Info:
mkotyad Munawira Kotyad */

/* Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta*/

#include <stdio.h>
#include <stdlib.h>
#include "linklist_kv.h"

extern mythread_queue_t *mythread_queue;

int mythread_setspecific(mythread_key_t key, const void *val)

{
	int id;
	
	id = key.keyID;
	/*currKeyVal iterates through the values of all the threads*/
	mythread_keyval_t *currKeyVal;
	currKeyVal = (mythread_keyval_t *) malloc(sizeof(mythread_keyval_t));

	/*currKey iterayes through the values of all the keys */
	mythread_key_t *currKey;
	currKey = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
		
	/*Identifying the right key*/
	currKey = mythread_key_helper->headkey;	
	
	while(currKey != mythread_key_helper->tailkey)
	{	
		if(currKey->keyID == id)
		{
			break;
		}
		currKey = currKey->next;
	}
	currKeyVal = currKey->mythread_keyval_helper->headkeyval;
	/*Identifying the right thread */
	while(currKeyVal->next != currKey->mythread_keyval_helper->tailkeyval)
	{
		if(currKeyVal->thread->pid == mythread_queue->currThread->pid)
		 {			
			break;
		}
		else
		
		currKeyVal= currKeyVal->next;
	
	} 	

	currKeyVal->value = val;
 }

