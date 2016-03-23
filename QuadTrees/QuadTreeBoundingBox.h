
#pragma once

#include "QuadTreePoint.h"

class QuadTreeBoundingBox
{
private:
    QuadTreePoint *point;
    float width;
    float height;

public:
    QuadTreeBoundingBox(QuadTreePoint *point, float width, float height);

    const QuadTreePoint& getCenterPoint() const
    {
        return point;
    }

    const getWidth() const
    {
        return width;
    }

    const getHeight() const
    {
        return height;
    }

    bool containsPoint(const QuadTreePoint &point) const;

    bool intersects(const QuadTreeBoundingBox &box) const;

    bool encompasses(const QuadTreeBoundingBox &box) const;

private:
    float startX() const
    {
        return point->getX() - width / 2;
    }

    float endX() const
    {
        return point->getX() + width / 2;
    }

    float startY() const
    {
        return point->getY() - height / 2;
    }

    float endY() const
    {
        return point->getY() + height / 2;
    }

    bool isXinRange(float x);
    bool isYinRange(float y);
};
