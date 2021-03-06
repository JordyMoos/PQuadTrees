
#include "QuadTreeBoundingBox.h"

QuadTreeBoundingBox::QuadTreeBoundingBox(QuadTreePoint *centerPoint, float width, float height)
    : centerPoint(centerPoint), width(width), height(height)
{
    php_printf("Creating box with size: %f and %f\n", width, height);
}

bool QuadTreeBoundingBox::containsPoint(const QuadTreePoint &point) const
{
    return (isXinRange(point.getX())) && (isYinRange(point.getY()));
}

bool QuadTreeBoundingBox::intersects(const QuadTreeBoundingBox &box) const
{
    return (
        isXinRange(box.startX()) ||
        isXinRange(box.endX()) ||
        isYinRange(box.startY()) ||
        isYinRange(box.endY())
    );
}

bool QuadTreeBoundingBox::encompasses(const QuadTreeBoundingBox &box) const
{
    return (
        (box.startX() <= startX() && box.endX() >= endX()) &&
        (box.startY() <= startY() && box.endY() >= endY())
    );
}

bool QuadTreeBoundingBox::isXinRange(float x) const
{
    return (x >= startX()) && (x <= endX());
}

bool QuadTreeBoundingBox::isYinRange(float y) const
{
    return (y >= startY()) && (y <= endY());
}
