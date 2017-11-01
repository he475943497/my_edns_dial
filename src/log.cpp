#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include "log.h"
#include "config.h"

#define LOG_FILE "dial.log"
#define LOG_BUF_LEN 1024
g_log_config_t g_log_config;


int log_write(int level,int type,const char * fmt,...)
{
	extern dial_cfg_t g_cfg;
	if(level > g_cfg.log_level)
		return 0;

	extern bool g_log_out;
	int size = 0,len = 0 ;
	va_list args;
	time_t          timep;
	struct tm       st_tm;
	char buf[LOG_BUF_LEN] = {0};

	time(&timep);
	localtime_r(&timep, &st_tm);
	sprintf((char *)buf, "[%02d-%02d-%02d %02d:%02d:%02d]",
			(1900 + st_tm.tm_year),
			(1 + st_tm.tm_mon),
			st_tm.tm_mday,
			st_tm.tm_hour,
			st_tm.tm_min,
			st_tm.tm_sec);

	len = strlen(buf);
	va_start(args,fmt);
	size = vsnprintf(buf+len,LOG_BUF_LEN-len-1,(char *)fmt,args);
	va_end(args);

	if(size > 0) 
	{
		if(g_log_out)
			printf("%s",buf);	

		pthread_mutex_lock(&(g_log_config.log_lock));
		fwrite(buf,strlen(buf),1,g_log_config.log_fp);
		pthread_mutex_unlock(&(g_log_config.log_lock));
	}

	return 0;
}

int log_init()
{
	bzero(&g_log_config,sizeof(g_log_config_t));

	pthread_mutex_init(&(g_log_config.log_lock),NULL);

	g_log_config.log_fp = fopen(LOG_FILE,"a+");
	if(NULL == g_log_config.log_fp)
	{	
		printf("open log file failed\n");
		return -1;
	}
	
	return 0;
}

int log_exit()
{
	pthread_mutex_destroy(&(g_log_config.log_lock));
	fclose(g_log_config.log_fp);
	return 0;
}

