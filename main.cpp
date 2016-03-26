
#include "main.h"

PHP_MINIT_FUNCTION(PQuadTrees)
{
    init_point(INIT_FUNC_ARGS_PASSTHRU);
    init_box(INIT_FUNC_ARGS_PASSTHRU);
    init_quadtree(INIT_FUNC_ARGS_PASSTHRU);

    return SUCCESS;
}

zend_module_entry PQuadTrees_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_PQUADTREES_EXTNAME,
    NULL, // Functions
    PHP_MINIT(PQuadTrees),
    NULL, // MSHUTDOWN
    NULL, // RINIT
    NULL, // RSHUTDOWN
    NULL, // MINFO
#if ZEND_MODULE_API_NO >= 20010901
    PHP_PQUADTREES_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PQUADTREES
extern "C" {
    ZEND_GET_MODULE(PQuadTrees)
};
#endif
