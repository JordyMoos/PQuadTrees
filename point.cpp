
#include "main.h"
#include "QuadTrees/QuadTreePoint.h"

zend_object_handlers point_object_handlers;

struct point_object {
    zend_object std;
    QuadTreePoint *point;
};

void point_free_storage(void *object TSRMLS_DC)
{
    point_object *obj = static_cast<point_object*>(object);
    delete obj->point;

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value point_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zend_object_value retval;

    point_object *obj = static_cast<point_object*>(emalloc(sizeof(point_object)));
    memset(obj, 0, sizeof(point_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    object_properties_init(&obj->std, type);

    retval.handle = zend_objects_store_put(obj, NULL, point_free_storage, NULL TSRMLS_CC);
    retval.handlers = &point_object_handlers;

    return retval;
}

zend_class_entry *point_ce;

PHP_METHOD(Point, __construct)
{
    double x = 0.0;
    double y = 0.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|dd", &x, &y) == FAILURE)
    {
        RETURN_NULL();
    }

    QuadTreePoint *point = new QuadTreePoint(
        static_cast<float>(x),
        static_cast<float>(y)
    );
    point_object *obj = static_cast<point_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    obj->point = point;
}

PHP_METHOD(Point, getX)
{
    point_object *obj = static_cast<point_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreePoint *point = obj->point;

    RETURN_DOUBLE(point->getX());
}

PHP_METHOD(Point, getY)
{
    point_object *obj = static_cast<point_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreePoint *point = obj->point;

    RETURN_DOUBLE(point->getY());
}

zend_function_entry point_methods[] = {
    PHP_ME(Point, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Point, getX, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Point, getY, NULL, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

void init_point(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "QuadTreePoint", point_methods);
    point_ce = zend_register_internal_class(&ce TSRMLS_CC);
    point_ce->create_object = point_create_handler;
    memcpy(&point_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    point_object_handlers.clone_obj = NULL;
}


