#include "mythread.h"
#include "mythread_util.h"

void *helloClone(void *test)
{
	int myPid;

	myPid = mythread_self();

	printf("\n%d:Hello, %s\n",myPid,(char *) test);
	sleep(10);
	printf("\n%d:Yielding..\n",myPid);
	mythread_yield();
	printf("\n%d:Exiting.\n",myPid);
	mythread_exit(NULL);
	return 0;
}


int main()
{
	mythread_t testThreads[2];
	int i;

	mythread_set_loglevel(VDEBUG | VINFO);
	for(i = 0; i < 2; i++)
	{
		if (mythread_create(&testThreads[i],NULL,helloClone,"World") != MNOERR)
		{
			writeLog(__func__,VSEVERE,"Create Failed!");
		}
		else writeLog(__func__,VINFO,"Created.");
	}

	for (i = 0; i< 2; i++)
	{
		printf("\nWaiting on threads %d..",testThreads[i]);
		mythread_join(testThreads[i],NULL);
		printf("\ndone");
	}
	return 0;
}
