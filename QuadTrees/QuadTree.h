
#pragma once

#include <list>
#include "QuadTreeBoundingBox.h"
#include "QuadTreePoint.h"

class QuadTree
{
private:
    static const int DEFAULT_CAPACITY = 4;

    QuadTreeBoundingBox *boundingBox;
    int maxPoints;
    std::list<QuadTreePoint*> pointList;

    QuadTreeBoundingBox *northWest = NULL;
    QuadTreeBoundingBox *northEast = NULL;
    QuadTreeBoundingBox *southWest = NULL;
    QuadTreeBoundingBox *southEast = NULL;

public:

    QuadTree(QuadTreeBoundingBox *boundingBox, int maxPoints = DEFAULT_CAPACITY);
    bool insert(QuadTreePoint *point);
    bool search(QuadTreeBoundingBox *boundary);

private:
    void subdivide();

};
