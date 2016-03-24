
#pragma once

class QuadTreePoint
{
private:
    float x;
    float y;

public:
    QuadTreePoint(float x = 0.0, float y = 0.0)
            : x(x), y(y)
    {
    }

    float getX() const
    {
        return x;
    }

    float getY() const
    {
        return y;
    }
};
