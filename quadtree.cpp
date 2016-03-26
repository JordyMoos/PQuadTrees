
#include "main.h"
#include "quadtree.h"
#include "QuadTrees/QuadTree.h"
#include "box.h"

zend_object_handlers quadtree_object_handlers;

struct quadtree_object {
    zend_object std;
    QuadTree *quadTree;
};

void quadtree_free_storage(void *object TSRMLS_DC)
{
    quadtree_object *obj = static_cast<quadtree_object*>(object);

    assert(obj->quadTree != NULL);
    delete obj->quadTree;

    zend_hash_destroy(obj->std.properties);
    FREE_HASHTABLE(obj->std.properties);

    efree(obj);
}

zend_object_value quadtree_create_handler(zend_class_entry *type TSRMLS_DC)
{
    zend_object_value retval;

    quadtree_object *obj = static_cast<quadtree_object*>(emalloc(sizeof(quadtree_object)));
    memset(obj, 0, sizeof(quadtree_object));
    obj->std.ce = type;

    ALLOC_HASHTABLE(obj->std.properties);
    zend_hash_init(obj->std.properties, 0, NULL, ZVAL_PTR_DTOR, 0);
    object_properties_init(&obj->std, type);

    retval.handle = zend_objects_store_put(obj, NULL, quadtree_free_storage, NULL TSRMLS_CC);
    retval.handlers = &quadtree_object_handlers;

    return retval;
}

zend_class_entry * quadtree_ce;

PHP_METHOD(QuadTree, __construct)
{
    zval *zbox;
    long maxPoints;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O|l", &zbox, box_ce, &maxPoints) == FAILURE)
    {
        php_printf("Fetching arguments failed");
        RETURN_NULL();
    }

    box_object *box = static_cast<box_object*>(zend_object_store_get_object(zbox));
    if (box->box == NULL)
    {
        php_printf("Box is null\n");
        RETURN_NULL();
    }

    QuadTree *quadTree = NULL;
    if (ZEND_NUM_ARGS() TSRMLS_CC == 2)
        quadTree = new QuadTree(box->box, static_cast<int>(maxPoints));
    else
        quadTree = new QuadTree(box->box);

    quadtree_object *obj = static_cast<quadtree_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    obj->quadTree = quadTree;
}

zend_function_entry quadtree_methods[] = {
    PHP_ME(QuadTree, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    {NULL, NULL, NULL}
};

void init_quadtree(INIT_FUNC_ARGS)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "QuadTree", quadtree_methods);
    quadtree_ce = zend_register_internal_class(&ce TSRMLS_CC);
    quadtree_ce->create_object = quadtree_create_handler;
    memcpy(&quadtree_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    quadtree_object_handlers.clone_obj = NULL;
}
