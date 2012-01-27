/*
 * mythread_getspecific - thread-specific data management
 * The mythread_getspecific() function shall  return  the  value  currently
 * bound to the specified key on behalf of the calling thread.
 */
#include "linklist_kv.h" 
#include "mythread_defines.h"

extern mythread_queue_t *mythread_queue;

void *mythread_getspecific(mythread_key_t key)
{
  //get the id of the current thread and return the value of that specific key val
	//find the current thread
	mythread_keyval_t *currKeyVal;
	currKeyVal= (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
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
	
	return(currKeyVal->value);
/* Handle error conditions*/


}



