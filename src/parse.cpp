#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <signal.h>
#include "version.h"
#include "clib/array.h"
#include "clib/daemon.h"
#include "clib/signal.h"
#include "clib/process_info.h"

bool g_log_out = false;

void parse_args(int argc,char* argv[])
{
	bool need_daemon = false;

	if(2 == argc)
	{
		if (!strcmp("start", argv[1])) 
		{
			need_daemon = true;
		} 
		else if (!strcmp("stop", argv[1])) 
		{
			daemon_stop();
			exit(0);
		}
		else if (!strcmp("restart", argv[1])) 
		{
			daemon_stop();
			need_daemon = true;
		}
		else if(!strcmp("-g",argv[1]))
		{
			g_log_out = true;
		}
		else if(!strcmp("-v",argv[1]))
		{
			printf("%s\n",VERSION);
			exit(0);
		}
		else 
		{
			printf("unkown parameters:%s\n",argv[1]);
			exit(0);
		}
	}
	else
	{
		printf("edns_dial:start|stop|restart|-g|-v\n");
		exit(0);
	}

	if(need_daemon)
	{
		daemon_start(1);
	}

}

