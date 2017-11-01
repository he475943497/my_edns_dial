#include <pthread.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/time.h>
#include <time.h>
#include "thread.h"
#include "log.h"
#include "list.h"
#include "queue.h"
#include "hash.h"
#include "common.h"
#include "main.h"

#define THREADPOOL_NUM 20

bool monitor_thread_flag;
threadpool_t g_threadpool;
pthread_t g_thread1;
pthread_t g_thread2;
pthread_t g_thread3;

void* work_thread(void*arg)
{

}


void threadpool_init()
{
	g_threadpool.hope_num = THREADPOOL_NUM;
	atomic_set(&(g_threadpool.act_num),0);
	atomic_set(&(g_threadpool.used_num),0);
	g_threadpool.run_flag = true;

	if(0 != pthread_mutex_init(&(g_threadpool.mutex),NULL))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"threadpool mutex init failed\n");
		exit(1);
	}	
	if(0 != pthread_mutex_init(&(g_threadpool.lock),NULL))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"threadpool mutex init failed\n");
		exit(1);
	}	
	if(0 != pthread_cond_init(&(g_threadpool.cond),NULL))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"threadpool cond init failed\n");
		exit(1);
	}
	
	if(NULL == (g_threadpool.pthreads = (pthread_t*)calloc(g_threadpool.hope_num,sizeof(pthread_t))))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"threadpool calloc pthrad_t failed\n");
		exit(1);
	}

	for(int i = 0 ; i < g_threadpool.hope_num ; i++)
	{
		if(0 != pthread_create(&(g_threadpool.pthreads)[i],NULL,work_thread,(void*)&g_threadpool))
		{
			LOG(LEVEL_ERROR,LOG_ERROR,"threadpool create work thrad failed\n");
			exit(1);
		}
	}

	atomic_set(&(g_threadpool.act_num),g_threadpool.hope_num);

}

void add_task_to_queue(healthgroup_t*hg,policy_node_t*pc)
{
}

#define TIME_CMPARE(a,b) (((a)->tv_sec * 1000*1000 + (a)->tv_usec) - ((b)->tv_sec * 1000*1000 + (b)->tv_usec))

void* monitor_thread1(void* arg)
{
	extern hash_t g_hash_healthgroup;
	extern head_node_t g_queue;
	int i = 0;
	struct list_head* pos = NULL;
	struct list_head* cur = NULL;
	healthgroup_t* hg = NULL;
	policy_node_t* pc = NULL;
	struct timeval t_now;
	bzero(&t_now,sizeof(struct timeval));

	while(monitor_thread_flag)
	{
		for(i = 0 ; i < g_hash_healthgroup.size ; i++)
		{
			pthread_mutex_lock(&g_hash_healthgroup.hash_node[i].mutex);
			
			list_for_each(pos,&g_hash_healthgroup.hash_node[i].head)
			{
				hg = (healthgroup_t*)pos;
				list_for_each(cur,&hg->policy_head.head)
				{
					pc = (policy_node_t*)cur;
					gettimeofday(&t_now,NULL);
					if(TIME_CMPARE(&t_now,&pc->t_insert) >= 0)
					{
						add_task_to_queue(hg,pc);
					}
					pc->t_insert = t_now;
					pc->t_insert.tv_sec += pc->policy->freq;
				}

			}

			pthread_mutex_unlock(&g_hash_healthgroup.hash_node[i].mutex);
		}
	}
}

void* monitor_thread2(void* arg)
{
	extern head_node_t g_server_list;
	extern head_node_t g_queue;

}

void* monitor_thread3(void* arg)
{
	extern hash_t g_hash_nginxgroup;
	extern head_node_t g_queue;

}

void* monitor_queue_thread(void* arg)
{
	extern hash_t g_hash_nginxgroup;
	extern head_node_t g_queue;

}

void thread_init()
{
	threadpool_init();
	monitor_thread_flag = true;

	if(0 != pthread_create(&g_thread1,NULL,monitor_thread1,NULL))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"threadpool create monitor work thrad1 failed\n");
		exit(1);
	}
	if(0 != pthread_create(&g_thread2,NULL,monitor_thread2,NULL))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"threadpool create monitor work thrad2 failed\n");
		exit(1);
	}
	if(0 != pthread_create(&g_thread3,NULL,monitor_thread3,NULL))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"threadpool create monitor work thrad3 failed\n");
		exit(1);
	}
	if(0 != pthread_create(&g_thread3,NULL,monitor_queue_thread,NULL))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"threadpool create monitor queue thrad failed\n");
		exit(1);
	}
}


void thread_exit()
{
	pthread_mutex_destroy(&(g_threadpool.mutex));
	pthread_mutex_destroy(&(g_threadpool.lock));
	pthread_cond_destroy(&(g_threadpool.cond));
	
	free(g_threadpool.pthreads);
}

