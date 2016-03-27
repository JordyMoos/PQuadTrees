
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

    QuadTree *northWest;
    QuadTree *northEast;
    QuadTree *southWest;
    QuadTree *southEast;

public:

    QuadTree(QuadTreeBoundingBox *boundingBox, int maxPoints = DEFAULT_CAPACITY);
    bool insert(QuadTreePoint *point);
    bool search(QuadTreeBoundingBox *boundary);
    ~QuadTree();

private:
    void subdivide();

};
