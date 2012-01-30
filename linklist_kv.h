/* linklist_kv.h */

#ifndef __LINKLIST_KV
#define __LINKLIST_KV


#include <stdlib.h>
#include "mythread_defines.h"

static int numKeys = 0;

mythread_queue_t *mythread_queue;
struct mythread_key_t key;

//Forward declarations
struct mythread_keyval;
struct mythread_keyval_helper;

typedef struct mythread_key_t
  {	
	int keyID;	
	struct mythread_keyval *keyval;	
	struct mythread_key_t *next;
	struct mythread_key_t *prev;
	struct mythread_keyval_helper *mythread_keyval_helper;
	  
  }mythread_key_t;

typedef struct mythread_keyval
  {
	void *value;
	struct mythread_keyval *next;
	struct mythread_keyval *prev;
	mythread_helper_t *thread;

  }mythread_keyval_t;
typedef struct mythread_key_helper
  
{
	mythread_key_t *headkey,*tailkey,*currKey;

}mythread_key_helper_t;


typedef struct mythread_keyval_helper
{
	mythread_keyval_t *headkeyval,*tailkeyval,*currkeyval;

}mythread_keyval_helper_t;

mythread_key_helper_t mythread_key_helper;
	
#endif
