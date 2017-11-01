#ifndef _LOG_H_
#define _LOG_H

enum log_type
{
	DIAL_LOG_ERROR;
	DIAL_LOG_CONFIG;
	DIAL_LOG_DEBUG;
	DIAL_LOG_INFO;
}

typedef struct dial_log
{
	enum log_type;
	char local_time[64];
	char data[512];

}dial_log_t

#define LOG_ERROR_FILE "dial_error.log"
#define LOG_CONFIG_FILE "dial_config.log"
#define LOG_DEBUG_FILE "dial_debug.log"

#define LOG_ERROR(level,fmt,...)  log_error(level,DIAL_LOG_ERROR,LOG_ERROR_FILE,fmt,##__VA_ARGS__)

log_error(int level,int type,const char *logfile,const char * fmt,...)
void * log_work_thread(void*arg);
int log_init();
int log_exit();

#endif
