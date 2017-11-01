#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "hash.h"
#include "main.h"


hash_t g_hash_healthpolicy;
hash_t g_hash_healthgroup;
hash_t g_hash_nginxgroup;


int hash_key(const char*name,const char* view_name,int num)
{
	int rtn = 0;  
	int lenth = strlen(name) + strlen(view_name);

	while(*name) 
		rtn += *name++;

	while(*view_name) 
		rtn += *view_name++;

	return ((rtn*lenth)%(num-1));
}

void hash_add(hash_t*hash,const char*name,const char* view_name,struct list_head*node)
{
	int key = hash->hash_key(name,view_name,hash->size);
	pthread_mutex_lock(&(hash->hash_node[key].mutex));
	list_add(node,&(hash->hash_node[key].head));
	hash->hash_node[key].num++;
	pthread_mutex_unlock(&(hash->hash_node[key].mutex));
}

void hash_del(hash_t*hash,const char*name,const char* view_name,struct list_head*node)
{
	struct list_head* pos = NULL;
	int key = hash->hash_key(name,view_name,hash->size);
	pthread_mutex_lock(&(hash->hash_node[key].mutex));
	list_for_each(pos,&(hash->hash_node[key].head))
	{
		if(pos == node)
		{
			list_del(node);
			hash->hash_node[key].num--;
		}
	}
	pthread_mutex_unlock(&(hash->hash_node[key].mutex));
}


struct list_head* hash_search(hash_t* hash,enum hash_type flag,void* src)
{
	int key = 0;
	struct list_head* pos = NULL;

	switch(flag)
	{
		case HASH_POLICY:
		{
			healthpolicy_t* tmp = NULL;
			char* name = ((healthpolicy_t*)src)->policy_name;
			key = hash->hash_key(name,NULL,hash->size);

			pthread_mutex_lock(&(hash->hash_node[key].mutex));
			list_for_each(pos,&(hash->hash_node[key].head))
			{
				tmp = (healthpolicy_t*)pos;
				if(!strcmp(name,tmp->policy_name))
					break;	
			}
			pthread_mutex_unlock(&(hash->hash_node[key].mutex));

			break;
		}
		case HASH_HEALTHGROUP:
		{
			healthgroup_t* tmp = NULL;
			char* name = ((healthgroup_t*)src)->name;
			char* view_name = ((healthgroup_t*)src)->view_name;
			char* zone_name = ((healthgroup_t*)src)->zone_name;
			key = hash->hash_key(name,view_name,hash->size);

			pthread_mutex_lock(&(hash->hash_node[key].mutex));
			list_for_each(pos,&(hash->hash_node[key].head))
			{
				tmp = (healthgroup_t*)pos;
				if(!strcmp(name,tmp->name) && !strcmp(view_name,tmp->view_name) && !strcmp(zone_name,tmp->zone_name))
					break;	
			}
			pthread_mutex_unlock(&(hash->hash_node[key].mutex));

			break;
		}
		case HASH_NGINXGROUP:
		{
			nginxgroup_t* tmp = NULL;
			char* name = ((nginxgroup_t*)src)->name;
			key = hash->hash_key(name,NULL,hash->size);

			pthread_mutex_lock(&(hash->hash_node[key].mutex));
			list_for_each(pos,&(hash->hash_node[key].head))
			{
				tmp = (nginxgroup_t*)pos;
				if(!strcmp(name,tmp->name))
					break;	
			}
			pthread_mutex_unlock(&(hash->hash_node[key].mutex));

			break;
		}
	}

	if(pos == &(hash->hash_node[key].head))
		return NULL;
	return pos;
}

void hash_node_init(hash_t* hash,int num)
{
	hash->hash_key = hash_key;
	hash->hash_add = hash_add;
	hash->hash_del = hash_del;
	hash->hash_search = hash_search;
	hash->size = num;
	hash->hash_node = (hash_node_t*)calloc(num,sizeof(hash_node_t));
	if(NULL == hash->hash_node)
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"calloc failed\n");
		exit(1);
	}
	for(int i = 0 ; i < num ; i++)
	{
		pthread_mutex_init(&(hash->hash_node[i].mutex),NULL);
	}
}

void hash_init()
{
	hash_node_init(&g_hash_healthpolicy,HASH_POLICY_NUM);		
	hash_node_init(&g_hash_healthgroup,HASH_HEALTHGROUP_NUM);		
	hash_node_init(&g_hash_nginxgroup,HASH_NGINXGROUP_NUM);		
}

void hash_node_free(hash_t* hash,int num)
{
	for(int i = 0 ; i < num ; i++)
	{
		pthread_mutex_destroy(&(hash->hash_node[i].mutex));
	}
	free(hash->hash_node);
}

void hash_exit()
{
	hash_node_free(&g_hash_healthpolicy,HASH_POLICY_NUM);		
	hash_node_free(&g_hash_healthgroup,HASH_HEALTHGROUP_NUM);		
	hash_node_free(&g_hash_nginxgroup,HASH_NGINXGROUP_NUM);		
}
