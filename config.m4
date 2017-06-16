dnl
dnl $Id$
dnl

PHP_ARG_ENABLE(rijndael,whether to enable Rijndael support.,
[  --enable-rijndael          Enable Rijndael support])

if test "$PHP_RIJNDAEL" = "yes"; then
  AC_DEFINE(HAVE_RIJNDAEL,1,[Whether you want rijndael support])
  PHP_NEW_EXTENSION(rijndael, php_rijndael.c rijndael.c, $ext_shared)

  dnl Empty variable means 'no'
fi
