/*
Single Author Info:
mkotyad Munawira Kotyad
*/

/*
Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta
 */

#include <stdio.h>
#include <stdlib.h>

#include "linklist_kv.h"

void mythread_key_helper_init()
{
	if(mythread_key_helper.headkey == NULL)
	{	
	//mythread_key_helper = (mythread_key_helper_t*)malloc(sizeof(mythread_key_helper_t));
	mythread_key_helper.headkey = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	mythread_key_helper.tailkey = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	mythread_key_helper.headkey->next = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	mythread_key_helper.headkey->next = mythread_key_helper.tailkey;
	mythread_key_helper.tailkey->prev =mythread_key_helper.headkey;
	mythread_key_helper.currKey = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	mythread_key_helper.currKey = 	mythread_key_helper.headkey;
	}
}

extern mythread_key_helper_t mythread_key_helper;
extern mythread_queue_t *mythread_queue;

int mythread_key_create(mythread_key_t *key, void (*destructor)(void*))
{

	mythread_helper_t *currT;
	mythread_keyval_t *currV;
	
	//Initializing the key helper
	mythread_key_helper_init();
	
	//Adding the new key to the linkedlist
	mythread_key_helper.currKey->next = key;
	mythread_key_helper.currKey = mythread_key_helper.currKey->next;
	mythread_key_helper.tailkey->prev =mythread_key_helper.currKey;
	mythread_key_helper.currKey->next = mythread_key_helper.tailkey;
	key->next = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	mythread_key_helper.tailkey = key->next;
	mythread_key_helper.tailkey->prev = key;
	mythread_key_helper.tailkey->next = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	
	
	/*Assigning an ID to all the keys*/	
	key->keyID = ++numKeys;

	/*Initializing all the pointers in key->keyval*/
	key->keyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t *));
	key->mythread_keyval_helper = (mythread_keyval_helper_t *)malloc(sizeof(mythread_keyval_helper_t *));
	key->mythread_keyval_helper->headkeyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t *));
	key->mythread_keyval_helper->tailkeyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t *));	
	key->mythread_keyval_helper->currkeyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t *));
	key->mythread_keyval_helper->headkeyval->thread = (mythread_helper_t *)malloc(sizeof(mythread_helper_t *));
	key->mythread_keyval_helper->tailkeyval->thread = (mythread_helper_t *)malloc(sizeof(mythread_helper_t *));
	
	/* Create a KeyVal for every thread */
		
	key->mythread_keyval_helper->headkeyval->thread = mythread_queue->head;
	key->mythread_keyval_helper->tailkeyval = key->mythread_keyval_helper->headkeyval;

	currT = (mythread_helper_t *)malloc(sizeof(mythread_helper_t *));
	currT = key->mythread_keyval_helper->tailkeyval->thread;
	currV = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
	currV = key->mythread_keyval_helper->tailkeyval;
	

	while(currT != mythread_queue->tail->next)
	{	
		currV->next = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
		currV->next->prev = currV;		
		currV = currV->next;
		currV->thread = currT;	
		currT = currT->next;
		
	}
	
	currV->next = NULL;
	key->mythread_keyval_helper->tailkeyval = currV;	

}
