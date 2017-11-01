#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include "iniparser.h"
#include "list.h"
#include "log.h"
#include "config.h"
#include "version.h"
#include "main.h"
#include "hash.h"
#include "queue.h"
#include "openssl.h"
#include "common.h"
#include "thread.h"
#include "thrift.h"


int main(int argc,char*argv[])
{
	parse_args(argc,argv);

	log_init();
	config_init();
	hash_init();
	server_list_init();
	queue_init();
	openssl_init();
	common_init();
	thread_init();
	thrift_client_init();
	thrift_init();

	thread_exit();
	hash_exit();
	config_exit();
	log_exit();

	return 0;
}
