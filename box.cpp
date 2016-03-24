
#include "main.h"
#include "QuadTrees/QuadTreeBoundingBox.h"
#include "point.h"

zend_object_handlers box_object_handlers;

struct box_object {
    zend_object std;
    QuadTreeBoundingBox *box;
};

void box_free_storage(void *object TSRMLS_DC)
{
    box_object *obj = static_cast<box_object*>(object);
    delete obj->box;

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value box_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zend_object_value retval;

    box_object *obj = static_cast<box_object*>(emalloc(sizeof(box_object)));
    memset(obj, 0, sizeof(box_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    object_properties_init(&obj->std, type);

    retval.handle = zend_objects_store_put(obj, NULL, box_free_storage, NULL TSRMLS_CC);
    retval.handlers = &box_object_handlers;

    return retval;
}

zend_class_entry *box_ce;

PHP_METHOD(Box, __construct)
{
    zval *point;
    double width = 1.0;
    double height = 1.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|dd", &point, point_ce, &width, &height) == FAILURE)
    {
        php_printf("Failed\n");
        RETURN_NULL();
    }

    php_printf("Good\n");
    php_printf("Width: %f\n", width);
    php_printf("Height: %f\n", height);

    PRINT_ZVAL(point);

    RETURN_NULL();
}

zend_function_entry box_methods[] = {
    PHP_ME(Box, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    {NULL, NULL, NULL}
};

void init_box(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "QuadTreeBoundingBox", box_methods);
    box_ce = zend_register_internal_class(&ce TSRMLS_CC);
    box_ce->create_object = box_create_handler;
    memcpy(&box_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    box_object_handlers.clone_obj = NULL;
}


