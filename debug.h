
#pragma once

#define PRINT_ZVAL(value) { \
    php_printf("["); \
    switch (Z_TYPE_P(value)) { \
        case IS_NULL: \
            php_printf("NULL"); \
            break; \
        case IS_BOOL: \
            php_printf("Boolean: %s", Z_LVAL_P(value) ? "TRUE" : "FALSE"); \
            break; \
        case IS_LONG: \
            php_printf("Long: %ld", Z_LVAL_P(value)); \
            break; \
        case IS_DOUBLE: \
            php_printf("Double: %f", Z_DVAL_P(value)); \
            break; \
        case IS_STRING: \
            php_printf("String: "); \
            PHPWRITE(Z_STRVAL_P(value), Z_STRLEN_P(value)); \
            php_printf(""); \
            break; \
        case IS_RESOURCE: \
            php_printf("Resource"); \
            break; \
        case IS_ARRAY: \
            php_printf("Array"); \
            break; \
        case IS_OBJECT: \
            php_printf("Object"); \
            break; \
        default: \
            php_printf("Unknown"); \
    } \
    php_printf("]\n"); \
}

