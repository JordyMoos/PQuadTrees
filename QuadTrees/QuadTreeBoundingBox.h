
#pragma once

#include "QuadTreePoint.h"
#include "../point.h"

class QuadTreeBoundingBox
{
private:
    point_object *pointObject;

    QuadTreePoint *centerPoint;
    float width;
    float height;

public:
    QuadTreeBoundingBox(point_object *pointObject, float width, float height);

    QuadTreePoint* getCenterPoint() const
    {
        return centerPoint;
    }

    const float getWidth() const
    {
        return width;
    }

    const float getHeight() const
    {
        return height;
    }

    bool containsPoint(const QuadTreePoint &point) const;

    bool intersects(const QuadTreeBoundingBox &box) const;

    bool encompasses(const QuadTreeBoundingBox &box) const;

private:
    float startX() const
    {
        return centerPoint->getX() - width / 2;
    }

    float endX() const
    {
        return centerPoint->getX() + width / 2;
    }

    float startY() const
    {
        return centerPoint->getY() - height / 2;
    }

    float endY() const
    {
        return centerPoint->getY() + height / 2;
    }

    bool isXinRange(float x) const;
    bool isYinRange(float y) const;
};
