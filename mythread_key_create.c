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
//#include "linklist_kv.h"
#include "mythread.h"


void mythread_key_helper_init()
{
	if(mythread_key_helper.headkey == NULL)
	{	
		mythread_key_helper.headkey = NULL;
		mythread_key_helper.tailkey = NULL;
		mythread_key_helper.headkey->next = NULL;
		mythread_key_helper.tailkey->prev = NULL;
		mythread_key_helper.currKey = 	mythread_key_helper.headkey;
	}
}

extern mythread_key_helper_t mythread_key_helper;
extern mythread_queue_t *mythread_queue;

int mythread_key_create(mythread_key_t *key, void (*destructor)(void*))
{
	printf("In set specific \n");
	mythread_helper_t *currT;
	mythread_keyval_t *currV;
	
	//Initializing the key helper
	mythread_key_helper_init();
	printf("In set specific1 \n");

	//Adding the new key to the linkedlist
	mythread_key_helper.currKey->next = key;
	mythread_key_helper.currKey = mythread_key_helper.currKey->next;
	

	mythread_key_helper.tailkey->prev =mythread_key_helper.currKey;
	mythread_key_helper.currKey->next = mythread_key_helper.tailkey;
	//key->next = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	mythread_key_helper.tailkey = key->next;
	mythread_key_helper.tailkey->prev = key;
	mythread_key_helper.tailkey->next = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	
	printf("In set specific3 \n");
	/*Assigning an ID to all the keys*/	
	key->keyID = ++numKeys;
	printf("In set specific4 \n");
	/*Initializing all the pointers in key->keyval*/
	key->keyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t *));
	key->mythread_keyval_helper = (mythread_keyval_helper_t *)malloc(sizeof(mythread_keyval_helper_t *));
	key->mythread_keyval_helper->headkeyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t *));
	//key->mythread_keyval_helper->tailkeyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t *));	
	//key->mythread_keyval_helper->currkeyval = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t *));
	//key->mythread_keyval_helper->headkeyval->thread = (mythread_helper_t *)malloc(sizeof(mythread_helper_t *));
	//key->mythread_keyval_helper->tailkeyval->thread = (mythread_helper_t *)malloc(sizeof(mythread_helper_t *));
	
	/* Create a KeyVal for every thread */
	printf("In set specific5 \n");	
	key->mythread_keyval_helper->headkeyval->thread = mythread_queue->tail;
	key->mythread_keyval_helper->tailkeyval = key->mythread_keyval_helper->headkeyval;
	key->mythread_keyval_helper->tailkeyval->thread = key->mythread_keyval_helper->headkeyval->thread;

	currT = (mythread_helper_t *)malloc(sizeof(mythread_helper_t *));
	currT = key->mythread_keyval_helper->tailkeyval->thread;
	//currV = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
	currV = key->mythread_keyval_helper->tailkeyval;
	printf("In set specific 6\n");

	while(currT != mythread_queue->tail)
	{	
		//currV->next = (mythread_keyval_t *)malloc(sizeof(mythread_keyval_t));
		currV->next->prev = currV;
		currV->thread = currT;		
		currV = currV->next;	
		currT = currT->next;
		
	}
	printf("In set specific 7\n");
	currV->next = NULL;
	key->mythread_keyval_helper->tailkeyval = currV;	

}
