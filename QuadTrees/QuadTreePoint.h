
#pragma once

#include "php.h"

class QuadTreePoint
{
private:
    float x;
    float y;

public:
    QuadTreePoint(float x = 0.0, float y = 0.0)
            : x(x), y(y)
    {
        php_printf("Creating point on %f - %f\n", x, y);
    }

    float getX() const
    {
        return x;
    }

    float getY() const
    {
        return y;
    }

    void dump()
    {
        php_printf("Point info [X: %f] [Y: %f]\n", x, y);
    }
};
