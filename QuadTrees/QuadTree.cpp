
#include "QuadTree.h"

QuadTree::QuadTree(QuadTreeBoundingBox *boundingBox, int maxPoints)
    : boundingBox(boundingBox), maxPoints(maxPoints)
{
}

bool QuadTree::insert(QuadTreePoint *point)
{
    pointList.push_back(point);

    return true;
}

void QuadTree::subdivide()
{

}

bool QuadTree::search(QuadTreeBoundingBox *boundary)
{

}

