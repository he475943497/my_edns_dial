#ifndef _HASH_H_
#define _HASH_H_

#include <pthread.h>
#include "list.h"

#define HASH_POLICY_NUM 100
#define HASH_NGINXGROUP_NUM  500
#define HASH_HEALTHGROUP_NUM  1000

typedef struct hash_node
{
	struct list_head head;
	int num;
	pthread_mutex_t mutex;

}hash_node_t;

enum hash_type
{
	HASH_POLICY,
	HASH_HEALTHGROUP,
	HASH_NGINXGROUP,
};

typedef struct dial_hash 
{
	int (*hash_key)(const char*,const char*,int);
	void (*hash_add)(struct dial_hash*,const char*,const char*,struct list_head*); 
	void (*hash_del)(struct dial_hash*,const char*,const char*,struct list_head*); 
	void (*hash_clear)(struct dial_hash*); 
	struct list_head *(*hash_search)(struct dial_hash*,enum hash_type,void*); 
	int size;    
	hash_node_t* hash_node;

} hash_t;

static inline void hash_node_init(hash_t* hash,int num);
static inline void hash_node_free(hash_t* hash,int num);
int hash_key(const char*name,const char* view_name,int num);
void hash_add(hash_t*hash,const char*name,const char* view_name,struct list_head*node);
void hash_del(hash_t*hash,const char*name,const char* view_name,struct list_head*node);
void hash_init();
void hash_exit();

#endif
