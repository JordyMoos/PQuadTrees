
#pragma once

#include "php.h"
#include "QuadTrees/QuadTreeBoundingBox.h"

extern zend_class_entry *box_ce;

struct box_object {
    zend_object std;
    QuadTreeBoundingBox *box;
};
