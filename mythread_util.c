/* This file has been edited and contributed to by everyone, so it doesn't have any single author info.

Group info:
vineet Vineet Krishnan
vgumash Vaibhav Gumashta
mkotyad Munawira Kotyad */


#include "mythread_util.h"

int _system_log_level;

int writeLog(const char *sourceFunction,enum VLOGLEVEL loglevel,char *logStr)
{
	if (_system_log_level != NONE)
	{
		char text[512];
		struct tm *timeVal;
		time_t currTime;
		char timeBuff[64];

		currTime = time(NULL);
		timeVal = localtime(&currTime);
		strftime(timeBuff,64,"%Y%m%d %H:%M:%S|",timeVal);
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
		else if (loglevel == VDEBUG)
		{
			strcat(text,"DEBUG|");
		}
		strcat(text,sourceFunction);
		strcat(text,"|");

		strcat(text,logStr);
		strcat(text,"\n");
		if ( (_system_log_level & (int) loglevel) == (int) loglevel)
		{
			write(1,text,strlen(text));
		}
	}
	return 0;
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
		helper->joiner_thread = 0;
		futex_init(&helper->thread_futex,0);
	}
	return MNOERR;
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
