#include "Vector2.h"

Vector2::Vector2() : x_(0), y_(0)
{
}

Vector2::Vector2(float x, float y) : x_(x), y_(y)
{
}

Vector2::Vector2(int x, int y) : x_((float)x), y_((float)y)
{
}
