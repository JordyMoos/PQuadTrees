
#pragma once

#include "QuadTrees/QuadTreePoint.h"

extern zend_class_entry *point_ce;

struct point_object {
    zend_object std;
    QuadTreePoint *point;
};
