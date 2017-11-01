#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "iniparser.h"
#include "config.h"
#include "log.h"

#define CONFIG_FILE "config/dial.ini"

dial_cfg_t g_cfg;
dictionary *ini = NULL;

int config_init()
{
	bzero(&g_cfg,sizeof(dial_cfg_t));

	if(!(ini = iniparser_load(CONFIG_FILE)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to load config\n");
		return -1;	
	}

	if(-1 == (g_cfg.dial_port = iniparser_getint(ini,"dial:port",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read dial port from config\n");
		return -1;	
	}

	if(-1 == (g_cfg.agent_port = iniparser_getint(ini,"agent:port",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(!(g_cfg.agent_ip = iniparser_getstring(ini,"agent:ip",NULL)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(-1 == (g_cfg.srv_cfg.health = iniparser_getint(ini,"server:health",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(-1 == (g_cfg.srv_cfg.delay_weight = iniparser_getint(ini,"server:delay_weight",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(-1 == (g_cfg.srv_cfg.lost_weight = iniparser_getint(ini,"server:lost_weight",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(-1 == (g_cfg.srv_cfg.count = iniparser_getint(ini,"server:count",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(-1 == (g_cfg.srv_cfg.timeout = iniparser_getint(ini,"server:timeout",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(-1 == (g_cfg.srv_cfg.interval = iniparser_getint(ini,"server:interval",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(!(g_cfg.srv_cfg.dname = iniparser_getstring(ini,"server:dname",NULL)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(!(g_cfg.log_path = iniparser_getstring(ini,"log:path",NULL)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(-1 == (g_cfg.log_level = iniparser_getint(ini,"log:level",-1)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	if(!(g_cfg.certificate_file = iniparser_getstring(ini,"certificate:path",NULL)))
	{
		LOG(LEVEL_ERROR,LOG_ERROR,"Failed to read the port from config\n");
		return -1;	
	}

	g_cfg.srv_cfg.allowed[0] = true;
	g_cfg.srv_cfg.allowed[1] = true;
	g_cfg.srv_cfg.allowed[2] = true;

	LOG(LEVEL_CONFIG,LOG_CONFIG,": dial_port = %d,agent_port = %d,agent_ip = %s\n",g_cfg.dial_port,g_cfg.agent_port,g_cfg.agent_ip);
	LOG(LEVEL_CONFIG,LOG_CONFIG,": dial_port = %d,agent_port = %d,agent_ip = %s\n",g_cfg.dial_port,g_cfg.agent_port,g_cfg.agent_ip);


	return 0;

}

int config_exit()
{
	iniparser_freedict(ini);
}
