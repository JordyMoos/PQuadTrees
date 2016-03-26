
#pragma once

#include "debug.h"

#define PHP_PQUADTREES_EXTNAME      "PQuadTrees"
#define PHP_PQUADTREES_EXTVER       "0.1"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
#include "php.h"
};

extern zend_module_entry pquadtrees_module_entry;
#define phpext_pquadtrees_ptr &puadtrees_module_entry;

void init_point(INIT_FUNC_ARGS);
void init_box(INIT_FUNC_ARGS);
void init_quadtree(INIT_FUNC_ARGS);
