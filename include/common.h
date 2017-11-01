#ifndef _COMMON_H_
#define _COMMON_H_

#include <pthread.h>
#include "list.h"

typedef struct queue_info
{
	struct list_head head;
	int num;
	pthread_mutex_t lock;

}head_node_t;

int common_init();

#endif
