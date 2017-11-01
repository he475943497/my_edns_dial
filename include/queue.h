#ifndef _QUEUE_H_
#define _QUEUE_H_


void queue_push(struct list_head *node);
struct list_head* queue_pop();
void queue_init();
void server_list_init();

#endif
