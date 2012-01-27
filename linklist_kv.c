#include"linklist_kv.h"

mythread_keyval_helper_t keyval_helper;
mythread_key_helper_t key_helper;

void mythread_key_helper_init()
{
	mythread_key_t *head,*tail,*currKey;
	//mythread_keyval_t *currThreadKey;
	key_helper.headkey = NULL;
	key_helper.tailkey = key_helper.headkey;
	key_helper.currKey = NULL;
	//key_helper.currkeyval = NULL;
}

void mythread_key_init(mythread_key_t *key)
{
	key = (mythread_key_t *)malloc(sizeof(mythread_key_t *));
	key_helper.headkey = key;
	key_helper.tailkey = key;
}

