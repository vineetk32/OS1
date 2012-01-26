/* This file has been edited and contributed to by everyone, so it doesn't have any single author info.

Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */


#include "mythread_util.h"

int writeLog(char *sourceFunction,enum VLOGLEVEL loglevel,char *logStr)
{
	char *text;
	struct tm *timeVal;
	time_t currTime;
	char *timeBuff;

	text = (char *) malloc (sizeof(char) * (strlen(logStr) + strlen(sourceFunction) + (strlen("YYYYMMDD HH:MM:SS") + 8)));
	timeBuff = (char *) malloc (sizeof(char) * (strlen("YYYYMMDD HH:MM:SS") + 5));
	
	currTime = time(NULL);
	timeVal = localtime(&currTime);
	strftime(timeBuff,64,"\n%Y%m%d %H:%M:%S|",timeVal);
	strcpy(text,timeBuff);

	
	//LogFormat - Date|LOGLEVEL|SourceFunction|LogString
	if (loglevel == VERROR)
	{
		strcat(text,"ERROR|");
	}
	else if (loglevel == VWARNING)
	{
		strcat(text,"WARNING|");
	}
	else if (loglevel == VSEVERE)
	{
		strcat(text,"SEVERE|");
	}
	else if (loglevel == VINFO)
	{
		strcat(text,"INFO|");
	}
	
	strcat(text,sourceFunction);
	strcat(text,"|");

	strcat(text,logStr);
	return write(1,text,strlen(text));
}

enum MERRORSTATE mythread_helper_init(mythread_helper_t *helper)
{
	if ( helper == NULL)
	{
		//TODO: Change return code
		return MERR_MALLOC;
	}
	else
	{
		helper->currState = NEW;
		helper->next = NULL;
		helper->prev = NULL;
		helper->pid = -1;
		helper->hasJoiners = 0;
		futex_init(&helper->thread_futex,1);
	}
}

void mythread_helper_destroy(mythread_helper_t *helper)
{
	helper->currState = TERMINATED;
	helper->next = NULL;
	helper->prev = NULL;
	helper->pid = -1;
	helper->threadStack = NULL;
	free(helper);
}
