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

#ifndef	_INCLUDED_RIJNDAEL_H
#define	_INCLUDED_RIJNDAEL_H

#if HAVE_RIJNDAEL

extern zend_module_entry php_rijndael_module_entry;
#define php_ftp_module_ptr &php_rijndael_module_entry

#include "php_version.h"
#define PHP_RIJNDAEL_VERSION PHP_VERSION

PHP_MINIT_FUNCTION(rijndael);
PHP_MINFO_FUNCTION(rijndael);

PHP_FUNCTION(rijndael_encrypt);
PHP_FUNCTION(rijndael_decrypt);

#define phpext_rijndael_ptr php_rijndael_module_ptr

#else
#define php_rijndael_module_ptr NULL
#endif	/* HAVE_FTP */

#endif
