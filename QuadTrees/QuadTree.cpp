
#include "QuadTree.h"
#include <string>

QuadTree::QuadTree(QuadTreeBoundingBox *boundingBox, int maxPoints)
    : boundingBox(boundingBox), maxPoints(maxPoints),
      northWest(NULL), northEast(NULL),
      southWest(NULL), southEast(NULL)
{
}

bool QuadTree::insert(QuadTreePoint *point)
{
    if ( ! boundingBox->containsPoint(*point))
    {
        php_printf("[insert] not contains false\n");
        return false;
    }

    if (pointList.size() < maxPoints)
    {
        pointList.push_back(point);
        php_printf("[insert] added true\n");
        return true;
    }

    if (northWest == NULL)
    {
        subdivide();
        php_printf("[insert] divided\n");
    }

    if (northWest->insert(point) || northEast->insert(point) || southWest->insert(point) || southEast->insert(point))
    {
        php_printf("[insert] put in child true\n");
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


std::list<QuadTreePoint*> *QuadTree::search(QuadTreeBoundingBox *boundary)
{
    std::list<QuadTreePoint*> *resultList = new std::list<QuadTreePoint*>;

    return QuadTree::search(boundary, resultList);
}

std::list<QuadTreePoint*> *QuadTree::search(QuadTreeBoundingBox *boundary, std::list<QuadTreePoint*> *resultList)
{
    php_printf("[Box info] %f : %f\n", boundingBox->getCenterPoint()->getX(), boundingBox->getCenterPoint()->getY());
    php_printf("[Search] Points found: %d\n", static_cast<int>(pointList.size()));

    if (boundingBox->encompasses(*boundary) || boundingBox->intersects(*boundary))
    {
        for(std::list<QuadTreePoint*>::iterator iterator = pointList.begin(); iterator != pointList.end(); iterator++)
        {
            if (boundary->containsPoint(*(*iterator)))
            {
                resultList->push_back(*iterator);
            }

            if (northWest != NULL)
            {
                php_printf("\n[NorthWest]\n");
                northWest->search(boundary, resultList);

                php_printf("\n[NorthEast]\n");
                northEast->search(boundary, resultList);

                php_printf("\n[SouthWest]\n");
                southWest->search(boundary, resultList);

                php_printf("\n[SouthEast]\n");
                southEast->search(boundary, resultList);
            }
        }
    }

    return resultList;
}


QuadTree::~QuadTree()
{
    if (northWest != NULL) delete northWest;
    if (northEast != NULL) delete northEast;
    if (southWest != NULL) delete southWest;
    if (southEast != NULL) delete southEast;
}

void QuadTree::dump(int depth)
{
    php_printf(std::string(depth, '.').c_str());
    php_printf(" [Points: %d] [X: %f] [Y: %f]\n",
               static_cast<int>(pointList.size()),
               boundingBox->getCenterPoint()->getX(),
               boundingBox->getCenterPoint()->getY());

    if (northWest != NULL)
    {
        depth += 1;

        northWest->dump(depth);
        northEast->dump(depth);
        southWest->dump(depth);
        southEast->dump(depth);
    }
}

