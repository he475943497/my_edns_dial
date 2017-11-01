#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include "atomic.h"

typedef struct threadpool 
{
	int hope_num;		//设置工作线程池线程数
	atomic_t act_num;	//实际运行的线程数
	atomic_t used_num;	//已在运行的线程数
	bool run_flag;		//工作线程运行标志
	pthread_t *pthreads;
	pthread_mutex_t mutex,lock;
	pthread_cond_t cond;

}threadpool_t;




void thread_init();
void thread_exit();

#endif
