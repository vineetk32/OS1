#include "util.h"

int splitLine(const char *in, char **out,const char *delim)
{
	int i = 0;
	char *ptr, *saveptr;
	char tempBuff[BUFFER_SIZE] = {'\0'};
	strcpy(tempBuff,in);

	ptr = strtok_r(tempBuff,delim,&saveptr);
	while (ptr != NULL)
	{
		out[i][0] = '\0';
		strcpy(out[i],ptr);
		i++;
		ptr = strtok_r(NULL,delim,&saveptr);

	}
	return i;

}

int arrayContains(const char **array, const char *element, int arrayLen)
{
	int i;
	for (i = 0; i < arrayLen; i++)
	{
		if (strcmp(array[i],element) == 0)
		{
			return i;
		}
	}
	return -1;
}

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
