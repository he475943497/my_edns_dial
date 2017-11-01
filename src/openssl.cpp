#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include "openssl.h"


void openssl_init()                      
{
	SSL_load_error_strings();	// 载入所有ssl错误信息
	SSL_library_init(); 		// ssl库初始化

	ERR_load_BIO_strings();		// 载入所有BIO错误信息	
	OpenSSL_add_all_algorithms();	// 载入所有ssl 算法
}

