/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xspy.h"

#include "xspyimpl.h"

/* If you declare any globals in php_xspy.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(xspy)
*/

/* True global resources - no need for thread safety here */
static int le_xspy;

#define PHP_XSPY_HANDLER    "xspy handler"

/* {{{ xspy_functions[]
 *
 * Every user visible function must have an entry in xspy_functions[].
 */
const zend_function_entry xspy_functions[] = {
    PHP_FE(xspy_init, NULL)
    PHP_FE(xspy_hanzi_to_pinyin, NULL)
    PHP_FE(xspy_deinit, NULL)
	PHP_FE_END	/* Must be the last line in xspy_functions[] */
};
/* }}} */

/* {{{ xspy_module_entry
 */
zend_module_entry xspy_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"xspy",
	xspy_functions,
	PHP_MINIT(xspy),
	PHP_MSHUTDOWN(xspy),
	PHP_RINIT(xspy),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(xspy),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(xspy),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_XSPY_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_XSPY
ZEND_GET_MODULE(xspy)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("xspy.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_xspy_globals, xspy_globals)
    STD_PHP_INI_ENTRY("xspy.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_xspy_globals, xspy_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_xspy_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_xspy_init_globals(zend_xspy_globals *xspy_globals)
{
	xspy_globals->global_value = 0;
	xspy_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(xspy)
{
    le_xspy = zend_register_list_destructors_ex(NULL, NULL, PHP_XSPY_HANDLER, module_number);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(xspy)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(xspy)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(xspy)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(xspy)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xspy support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_xspy_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(xspy_init)
{
    char *pinyin_db_path;
    int pinyin_db_path_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &pinyin_db_path, &pinyin_db_path_len) == FAILURE) {
		return;
	}
    int rv = pinyin_init(pinyin_db_path);
    if (rv) {
        RETURN_FALSE;
    }
    RETURN_TRUE;
}

PHP_FUNCTION(xspy_hanzi_to_pinyin)
{
    char *hanzi;
    int hanzi_len;
    long fuzzy, abbr;
    char *pinyin = NULL;
    size_t pinyin_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sll",
        &hanzi,
        &hanzi_len,
        &fuzzy,
        &abbr) == FAILURE) {
        return;
    }
    int r = hanzi_to_pinyin(hanzi, (size_t)hanzi_len, &pinyin, &pinyin_len, fuzzy, abbr);
    if (r) {
        RETURN_FALSE;
    }
    RETURN_STRINGL(pinyin, pinyin_len, 0);
}

PHP_FUNCTION(xspy_deinit)
{
    pinyin_deinit();
    RETURN_TRUE;
}

/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
