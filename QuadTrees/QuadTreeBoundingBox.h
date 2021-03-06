
#pragma once

#include "QuadTreePoint.h"
#include "../point.h"

class QuadTreeBoundingBox
{
private:
    QuadTreePoint *centerPoint;
    float width;
    float height;

public:
    QuadTreeBoundingBox(QuadTreePoint *centerPoint, float width, float height);

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

    void dump()
    {
        php_printf("Box information [X: %f] [Y: %f] [W: %f] [H: %f]\n",
                   centerPoint->getX(), centerPoint->getY(),
                    width, height);
    }

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
