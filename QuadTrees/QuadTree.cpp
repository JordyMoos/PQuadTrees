
#include "QuadTree.h"

QuadTree::QuadTree(QuadTreeBoundingBox *boundingBox, int maxPoints)
    : boundingBox(boundingBox), maxPoints(maxPoints)
{
}

bool QuadTree::insert(QuadTreePoint *point)
{
    if ( ! boundingBox->containsPoint(*point))
    {
        return false;
    }

    if (pointList.size() < maxPoints)
    {
        pointList.push_back(point);
        return true;
    }

    if (northWest == NULL)
    {
        subdivide();
    }

    if (northWest->insert(point) || northEast->insert(point) || southWest->insert(point) || southEast->insert(point))
    {
        return true;
    }

    php_printf("\n\nPoint is out of bound\n\n");

    return false;
}

void QuadTree::subdivide()
{
    float width = boundingBox->getWidth() / 2;
    float height = boundingBox->getHeight() / 2;
    float centerPointX = boundingBox->getCenterPoint()->getX();
    float centerPointY = boundingBox->getCenterPoint()->getY();

    northWest = new QuadTree(
        new QuadTreeBoundingBox(
            new QuadTreePoint(
                centerPointX - width / 2,
                centerPointY + height / 2
            ),
            width,
            height
        ),
        maxPoints
    );
    northEast = new QuadTree(
        new QuadTreeBoundingBox(
            new QuadTreePoint(
                centerPointX + width / 2,
                centerPointY + height / 2
            ),
            width,
            height
        ),
        maxPoints
    );
    southWest = new QuadTree(
        new QuadTreeBoundingBox(
            new QuadTreePoint(
                centerPointX - width / 2,
                centerPointY - height / 2
            ),
            width,
            height
        ),
        maxPoints
    );
    southEast = new QuadTree(
        new QuadTreeBoundingBox(
            new QuadTreePoint(
                centerPointX + width / 2,
                centerPointY - height / 2
            ),
            width,
            height
        ),
        maxPoints
    );
}

bool QuadTree::search(QuadTreeBoundingBox *boundary)
{

}

// @todo Add destructor to clean op the 4 created trees

