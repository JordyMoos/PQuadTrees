
#include "main.h"
#include "box.h"
#include "point.h"
#include "QuadTrees/QuadTreeBoundingBox.h"
#include "QuadTrees/QuadTreePoint.h"

zend_object_handlers box_object_handlers;

void box_free_storage(void *object TSRMLS_DC)
{
    box_object *obj = static_cast<box_object*>(object);

    assert(obj->box != NULL);
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
    zval *zpoint;
    double width = 1.0;
    double height = 1.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|dd", &zpoint, point_ce, &width, &height) == FAILURE)
    {
        RETURN_NULL();
    }

    point_object *point = static_cast<point_object*>(zend_object_store_get_object(zpoint));
    if (point->point == NULL)
    {
        php_printf("Point is null\n");
        RETURN_NULL();
    }

    QuadTreeBoundingBox *box = new QuadTreeBoundingBox(
        point->point,
        static_cast<float>(width),
        static_cast<float>(height)
    );

    box_object *obj = static_cast<box_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    obj->box = box;
}

PHP_METHOD(Box, getWidth)
{
    box_object *obj = static_cast<box_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreeBoundingBox *box = obj->box;

    RETURN_DOUBLE(box->getWidth());
}

PHP_METHOD(Box, getHeight)
{
    box_object *obj = static_cast<box_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreeBoundingBox *box = obj->box;

    RETURN_DOUBLE(box->getHeight());
}

PHP_METHOD(Box, getCenterPoint)
{
    box_object *obj = static_cast<box_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreeBoundingBox *box = obj->box;

    if (object_init_ex(return_value, point_ce) != SUCCESS) {
        RETURN_NULL();
    }

    point_object *po = static_cast<point_object*>(zend_object_store_get_object(return_value TSRMLS_CC));
    po->point = box->getCenterPoint();
}

PHP_METHOD(Box, containsPoint)
{
    zval *zpoint;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &zpoint, point_ce) == FAILURE)
    {
        php_printf("\n\nArgument is not a point\n\n");
        RETURN_NULL();
    }

    point_object *point = static_cast<point_object*>(zend_object_store_get_object(zpoint));
    if (point->point == NULL) {
        php_printf("Point is null\n");
        RETURN_NULL();
    }

    box_object *obj = static_cast<box_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreeBoundingBox *box = obj->box;

    bool contains = obj->box->containsPoint(*point->point);
    RETURN_BOOL(contains);
}

PHP_METHOD(Box, intersects)
{
    zval *zotherBox;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &zotherBox, box_ce) == FAILURE)
    {
        php_printf("\n\nArgument is not a box\n\n");
        RETURN_NULL();
    }

    box_object *otherBox = static_cast<box_object*>(zend_object_store_get_object(zotherBox));
    if (otherBox->box == NULL)
    {
        php_printf("Box is null\n");
        RETURN_NULL();
    }

    box_object *obj = static_cast<box_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreeBoundingBox *box = obj->box;

    bool intersects = obj->box->intersects(*otherBox->box);
    RETURN_BOOL(intersects);
}

PHP_METHOD(Box, encompasses)
{
    zval *zotherBox;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &zotherBox, box_ce) == FAILURE)
    {
        php_printf("\n\nArgument is not a box\n\n");
        RETURN_NULL();
    }

    box_object *otherBox = static_cast<box_object*>(zend_object_store_get_object(zotherBox));
    if (otherBox->box == NULL) {
        php_printf("Box is null\n");
        RETURN_NULL();
    }

    box_object *obj = static_cast<box_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreeBoundingBox *box = obj->box;

    bool encompasses = obj->box->encompasses(*otherBox->box);
    RETURN_BOOL(encompasses);
}

PHP_METHOD(Box, dump)
{
    box_object *obj = static_cast<box_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTreeBoundingBox *box = obj->box;

    box->dump();

    RETURN_NULL();
}

zend_function_entry box_methods[] = {
    PHP_ME(Box, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Box, getWidth, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Box, getHeight, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Box, getCenterPoint, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Box, containsPoint, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Box, intersects, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Box, encompasses, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(Box, dump, NULL, ZEND_ACC_PUBLIC)
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


