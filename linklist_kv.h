/* linklist_kv.h */

#ifndef __LINKLIST_KV
#define __LINKLIST_KV

#include "mythread_defines.h"

//Forward declarations
struct mythread_keyval;
struct mythread_keyval_helper;

typedef struct mythread_key_t
  {
	struct mythread_keyval *keyval;
	//mythread_helper_t *thread;	
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
	
#endif
