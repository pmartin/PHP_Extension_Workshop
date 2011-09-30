#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_myext.h"


/* {{{ myext_module_entry
 */
zend_module_entry myext_module_entry = {
    STANDARD_MODULE_HEADER,
    "myext",
    NULL, /* Function entries */
    PHP_MINIT(myext), /* Module init */
    NULL, /* Module shutdown */
    NULL, /* Request init */
    NULL, /* Request shutdown */
    NULL, /* Module information */
    "0.1", /* Replace with version number for your extension */
    STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYEXT
ZEND_GET_MODULE(myext)
#endif

zend_class_entry *ce_MyClass;

ZEND_BEGIN_ARG_INFO_EX(arginfo_myclass_foo, 0, 0, 1)
    ZEND_ARG_INFO(0, number)
    ZEND_ARG_INFO(1, string)
ZEND_END_ARG_INFO()

static zend_function_entry myclass_class_functions[] = {
    PHP_ME( MyClass, foo, arginfo_myclass_foo, ZEND_ACC_PUBLIC )
};

PHP_MINIT_FUNCTION(myext)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "MyClass", myclass_class_functions);
    ce.create_object = NULL;
    ce_MyClass = zend_register_internal_class(&ce TSRMLS_CC);
}

PHP_METHOD(MyClass, foo)
{
    long number;
    zval *string;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &number, &string) == FAILURE)
    {
        return;
    }

    php_printf( "Number: %ld, String: %s\n", number, Z_STRVAL_P(string));
}
