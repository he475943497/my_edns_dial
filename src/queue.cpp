#include <pthread.h>
#include "list.h"
#include "queue.h"
#include "common.h"

head_node_t g_queue;
head_node_t g_server_list;

void queue_push(struct list_head *node)
{
	pthread_mutex_lock(&(g_queue.lock));
	list_add(node,&(g_queue.head));
	g_queue.num++;
	pthread_mutex_unlock(&(g_queue.lock));	
}

struct list_head* queue_pop()
{
	pthread_mutex_lock(&(g_queue.lock));
	if(list_empty(&(g_queue.head)))
		return NULL;
	struct list_head* node = g_queue.head.prev;
	list_del(node);	
	g_queue.num--;
	pthread_mutex_unlock(&(g_queue.lock));	

	return node;	
}

void server_list_init()
{
	list_init(&(g_queue.head));
	g_queue.num = 0;
	pthread_mutex_init(&(g_queue.lock),NULL);
}

void queue_init()
{
	list_init(&(g_server_list.head));
	g_server_list.num = 0;
	pthread_mutex_init(&(g_server_list.lock),NULL);
}




