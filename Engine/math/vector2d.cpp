#include "vector2d.h"

namespace math
{
	const vector2d vector2d::zero;

	vector2d::vector2d() : x(0), y(0)
	{

	}

	vector2d::vector2d(float x1, float y1) : x(x1), y(y1)
	{

	}

	bool vector2d::operator==(const vector2d& other) const
	{
		return other.x == x && other.y == y;
	}

	bool vector2d::operator!=(const vector2d& other) const
	{
		return !(*this == other);
	}

	vector2d vector2d::operator-(const vector2d& other) const
	{
		return vector2d(x - other.x, y - other.y);
	}

	vector2d vector2d::operator+(const vector2d& other) const
	{
		return vector2d(x + other.x, y + other.y);
	}
    
    vector2d vector2d::operator*(float s) const
    {
        return vector2d(x * s, y * s);
    }
    
	vector2d vector2d::operator*(const vector2d& other) const
	{
		return vector2d(x * other.x, y * other.y);
	}

	vector2d vector2d::operator/(float s) const
    {
        return vector2d(x / s, y / s);
    }
}

