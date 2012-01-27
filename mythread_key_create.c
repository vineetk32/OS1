/*
Single Author Info:
mkotyad Munawira Kotyad

Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta
 */


#include "linklist_kv.h"

//extern mythread_keyval_helper_t mythread_keyval_helper;
extern mythread_key_helper_t key_helper;
extern mythread_queue_t *mythread_queue;

int mythread_key_create(mythread_key_t *key, void (*destructor)(void*))
{
	mythread_helper_t *currT;
	mythread_keyval_t *currV;

	key = (mythread_key_t*)malloc(sizeof(mythread_key_t));
	if (key== NULL)
	{
		//error in key creation
		return MERR_MALLOC;
	}

	//Adding the new key to the linkedlist
	key = key_helper.tailkey;
	key_helper.tailkey = key->next;
	key_helper.tailkey->prev  = key;

	/*Initializing all the pointers *///Dunno if necessary
	key->keyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
	//(key->keyval)->value = (mythread_key_t *)malloc(sizeof(mythread_key_t));
	(key->keyval)->thread = (mythread_helper_t *)malloc(sizeof(mythread_helper_t));
	
	//(key->keyval)->thread = mythread_tcb.currThread;
	/* Create a KeyVal for every thread */
	key->mythread_keyval_helper->headkeyval->thread = mythread_queue->head;
	key->mythread_keyval_helper->tailkeyval->thread = mythread_queue->tail;
	
	currT = (mythread_helper_t *)malloc(sizeof(mythread_helper_t *));
	currT = key->mythread_keyval_helper->tailkeyval->thread;

	currV = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
	currV = key->mythread_keyval_helper->tailkeyval;
	
	
	while(currT != NULL)
	{
		currT = currT->next;
		currV->next = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
		currV->next->prev = currV;
		currV = currV->next;
		currV->thread = currT;		
	}
	currV->next = NULL;

/* Handle maximum key count */	

/* Handle invalid key */
	return MNOERR;
}
