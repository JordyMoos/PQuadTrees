
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

    if (obj->quadTree != NULL)
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

PHP_METHOD(QuadTree, insert)
{
    zval *zpoint;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &zpoint, point_ce) == FAILURE)
    {
        php_printf("\n\nArgument is not a point\n\n");
        RETURN_NULL();
    }

    point_object *point = static_cast<point_object*>(zend_object_store_get_object(zpoint));
    if (point->point == NULL)
    {
        php_printf("Point is null\n");
        RETURN_NULL();
    }

    quadtree_object *obj = static_cast<quadtree_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTree *quadTree = obj->quadTree;

    bool isSuccess = quadTree->insert(point->point);
    RETURN_BOOL(isSuccess);
}

PHP_METHOD(QuadTree, search)
{
    zval *zboundary;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "O", &zboundary, box_ce) == FAILURE)
    {
        php_printf("\n\nArgument is not a box\n\n");
        RETURN_NULL();
    }

    box_object *boundary = static_cast<box_object*>(zend_object_store_get_object(zboundary));
    if (boundary->box == NULL)
    {
        php_printf("Boundary is null\n");
        RETURN_NULL();
    }

    quadtree_object *obj = static_cast<quadtree_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTree *quadTree = obj->quadTree;

    std::list<QuadTreePoint*> *pointList = quadTree->search(boundary->box);
    php_printf("%d points found for your box\n", static_cast<int>(pointList->size()));

    array_init(return_value);

    for (std::list<QuadTreePoint*>::iterator iter = pointList->begin(); iter != pointList->end(); iter++)
    {
        zval *row;
        MAKE_STD_ZVAL(row);
        object_init_ex(row, point_ce);

        point_object *po = static_cast<point_object*>(zend_object_store_get_object(row TSRMLS_CC));
        po->point = *iter;
        add_next_index_zval(return_value, row);
    }
}

PHP_METHOD(QuadTree, dump)
{
    quadtree_object *obj = static_cast<quadtree_object*>(zend_object_store_get_object(getThis() TSRMLS_CC));
    QuadTree *quadTree = obj->quadTree;

    quadTree->dump();

    RETURN_NULL();
}

zend_function_entry quadtree_methods[] = {
    PHP_ME(QuadTree, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(QuadTree, insert, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(QuadTree, search, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(QuadTree, dump, NULL, ZEND_ACC_PUBLIC)
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
