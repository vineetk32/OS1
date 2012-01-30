#include "mythread.h"
#include "mythread_util.h"

void *helloClone(void *test)
{
	int myPid;

	myPid = mythread_self();

	printf("\n%d:Hello, %s\n",myPid,(char *) test);
	sleep(2);
	printf("\n%d:Yielding..\n",myPid);
	mythread_yield();
	printf("\n%d:Exiting.\n",myPid);
	mythread_exit(NULL);
	return 0;
}


int main()
{
	mythread_t testThreads[5];
	int i;

	//mythread_set_loglevel(VDEBUG);
	for(i = 0; i < 5; i++)
	{
		if (mythread_create(&testThreads[i],NULL,helloClone,"World") != MNOERR)
		{
			writeLog(__func__,VSEVERE,"Create Failed!");
		}
		else writeLog(__func__,VINFO,"Created.");
	}

	sleep(2);
	for (i = 0; i< 5; i++)
	{
		printf("\nWaiting on threads %d..",testThreads[i]);
		mythread_join(testThreads[i],NULL);
		printf("\ndone");
	}
	return 0;
}
