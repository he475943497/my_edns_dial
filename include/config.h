#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct dial_server_config 
{
	bool allowed[3];
	int health;
	int delay_weight;
	int lost_weight;
	int count;
	int timeout;
	int interval;
	char* dname;	

}dial_srv_cfg_t;

typedef struct dial_config 
{
	dial_srv_cfg_t srv_cfg;
	int log_level;
	int agent_port;
	int dial_port;
	char* agent_ip;
	char* log_path;
	char* certificate_file;	

}dial_cfg_t;


int config_init();
int config_exit();

#endif
