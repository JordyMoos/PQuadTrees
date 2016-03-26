
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

    QuadTree *northWest = NULL;
    QuadTree *northEast = NULL;
    QuadTree *southWest = NULL;
    QuadTree *southEast = NULL;

public:

    QuadTree(QuadTreeBoundingBox *boundingBox, int maxPoints = DEFAULT_CAPACITY);
    bool insert(QuadTreePoint *point);
    bool search(QuadTreeBoundingBox *boundary);

private:
    void subdivide();

};
