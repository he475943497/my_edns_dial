#ifndef _MAIN_H_
#define _MAIN_H_

#include <time.h>
#include "list.h"
#include "main.h"
#include "common.h"




typedef struct healthpolicy_node_info
{
	struct list_head node;
	char policy_name[50];
	unsigned short method;
	unsigned short port;
	unsigned int freq;
	unsigned int times;
	unsigned int passed;
	//dial_option_t dial_option;

}healthpolicy_t;

typedef struct pPolicy_node_struct 
{
	struct list_head node;
	struct timeval t_insert;
	healthpolicy_t *policy;

}policy_node_t;

typedef struct healthgroup_node_info 
{
	struct list_head node;
	char zone_name[200];
	char view_name[50];
	char name[200];
	healthpolicy_t *p_policy;
	head_node_t policy_head;
	head_node_t record_head;
	head_node_t *p_record_head;

}healthgroup_t;


typedef struct nginxgroup_node_info 
{
	struct list_head node;
	char name[200];
	bool enable;
	healthpolicy_t *p_policy;
	head_node_t pPolicy_head;
	head_node_t srv_head;
	head_node_t *psrv_head;

}nginxgroup_t;




#endif
