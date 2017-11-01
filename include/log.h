#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <pthread.h>
#include "list.h"

enum log_type
{
	LOG_CONFIG,
	LOG_ERROR,
	LOG_DEBUG,
	LOG_INFO,
};

enum lo_level 
{
	LEVEL_CONFIG,
	LEVEL_ERROR,
	LEVEL_DEBUG,
	LEVEL_INFO,
};


typedef struct g_log_config
{
	FILE* log_fp;
	pthread_mutex_t log_lock;

}g_log_config_t;

int log_write(int level,int type,const char * fmt,...);
int log_init();
int log_exit();

#define	LOG(level,type,fmt,...)  log_write(level,type,fmt,##__VA_ARGS__)




#endif
