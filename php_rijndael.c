/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2017 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Vincent Rijmen <vincent.rijmen@esat.kuleuven.ac.be>         |
   |          Antoon Bosselaers <antoon.bosselaers@esat.kuleuven.ac.be>   |
   |          Paulo Barreto <paulo.barreto@terra.com.br>                  |
   |          Hect0r Xorius <staticpi.net@gmail.com> (Extension builder)  |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#if HAVE_RIJNDAEL

#include "ext/standard/info.h"
#include "ext/standard/file.h"

#include "php_rijndael.h"
#include "rijndael.h"

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(arginfo_rijndael_encrypt, 0,0,1)
	ZEND_ARG_INFO(0, inData)
	ZEND_ARG_INFO(0, key)
        ZEND_ARG_INFO(0, keyBits)
ZEND_END_ARG_INFO()
        
ZEND_BEGIN_ARG_INFO_EX(arginfo_rijndael_decrypt, 0,0,1)
	ZEND_ARG_INFO(0, inData)
	ZEND_ARG_INFO(0, key)
        ZEND_ARG_INFO(0, keyBits)
ZEND_END_ARG_INFO()

/* }}} */

const zend_function_entry php_rijndael_functions[] = {
	PHP_FE(rijndael_encrypt,			arginfo_rijndael_encrypt)
	PHP_FE(rijndael_decrypt,			arginfo_rijndael_decrypt)
	PHP_FE_END
};

zend_module_entry php_rijndael_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	"rijndael",
	php_rijndael_functions,
	PHP_MINIT(rijndael),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(rijndael),
	PHP_RIJNDAEL_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#if COMPILE_DL_RIJNDAEL
ZEND_GET_MODULE(php_rijndael)
#endif

PHP_MINIT_FUNCTION(rijndael)
{
	return SUCCESS;
}

PHP_MINFO_FUNCTION(rijndael)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Rijndael 128/192/256 support", "enabled");
	php_info_print_table_end();
}
/* {{{ proto resource rijndael_encrypt(string inData, string key)
   encrypts a string with rijndael */
PHP_FUNCTION(rijndael_encrypt)
{
    /* Inputs */
    char *inData; // Data Ptr.
    size_t inDataLen; // Data Length.
    char *key; // Key Ptr.
    size_t keyLen; // Key Length.
    zend_ulong keyBits; // Bits, between 128/192/256.

    
    /* Get Parameters from Zend */
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|s|l", &inData, &inDataLen, &key, &keyLen, &keyBits) == FAILURE) {
	return;
    }
    
    /* Since rijndael takes what it needs via key bits, then we just allow the overflow of the key. */
    switch(keyBits) {
        case 128:
            if(keyLen < 16) { php_error_docref(NULL, E_WARNING, "Key length must be 16 characters long."); RETURN_FALSE; }
            break;
        case 192:
            if(keyLen < 24) { php_error_docref(NULL, E_WARNING, "Key length must be 24 characters long."); RETURN_FALSE; }
            break;
        case 256:
            if(keyLen < 32) { php_error_docref(NULL, E_WARNING, "Key length must be 32 characters long."); RETURN_FALSE; }
            break;
    }
    
    /* Convert from original pointers to uin8_t arrays */
    uint8_t dataU8[16];
    uint8_t keyU8[16];
    uint8_t output[16],  i = 0;
    do {
        dataU8[i] = (uint8_t)inData[i];
        keyU8[i] = (uint8_t)key[i];
        i++;
    }
    while(i < 16);

    /* Setup Rijndael stack */
    uint32_t rk[4 * (MAXNR + 1)];
    int32_t Nr = rijndaelKeySetupEnc(rk, keyU8, keyBits);

    /* Decrypt Buffer. */
    rijndaelEncrypt(rk, Nr, dataU8, output);
    
    /* Now return data back into a char array*/
    char outChar[16], *ptr = outChar;
    i = 0;
    do {
        ptr[i] = (char)output[i];
        i++;
    }
    while(i < 16);
    
    RETURN_STRING(outChar);
}
/* }}} */

/* {{{ proto resource rijndael_decrypt(string inData, string key)
   decrypts a string with rijndael */
PHP_FUNCTION(rijndael_decrypt)
{
    /* Inputs */
    char *inData; // Data Ptr.
    size_t inDataLen; // Data Length.
    char *key; // Key Ptr.
    size_t keyLen; // Key Length.
    zend_ulong keyBits; // Bits, between 128/192/256.

    /* Get Parameters from Zend */
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|s|l", &inData, &inDataLen, &key, &keyLen, &keyBits) == FAILURE) {
	return;
    }
    
    /* Since rijndael takes what it needs via key bits, then we just allow the overflow of the key. */
    switch(keyBits) {
        case 128:
            if(keyLen < 16) { php_error_docref(NULL, E_WARNING, "Key length must be 16 characters long."); RETURN_FALSE; }
            break;
        case 192:
            if(keyLen < 24) { php_error_docref(NULL, E_WARNING, "Key length must be 24 characters long."); RETURN_FALSE; }
            break;
        case 256:
            if(keyLen < 32) { php_error_docref(NULL, E_WARNING, "Key length must be 32 characters long."); RETURN_FALSE; }
            break;
    }
    
    /* Convert from original pointers to uin8_t arrays */
    uint8_t dataU8[16];
    uint8_t keyU8[16];
    uint8_t output[16],  i = 0;
    do {
        dataU8[i] = (uint8_t)inData[i];
        keyU8[i] = (uint8_t)key[i];
        i++;
    }
    while(i < 16);

    /* Setup Rijndael Stack */
    uint32_t rk[4 * (MAXNR + 1)];
    int32_t Nr = rijndaelKeySetupDec(rk, keyU8, keyBits);

    /* Decrypt input uint8_t array */
    rijndaelDecrypt(rk, Nr, dataU8, output);
    
    /* Convert data back to a char */
    char outChar[16], *ptr = outChar;
    i = 0;
    do {
        ptr[i] = (char)output[i];
        i++;
    }
    while(i < 16);
    RETURN_STRING(ptr);
}
/* }}} */

#endif /* HAVE_RIJNDAEL */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
