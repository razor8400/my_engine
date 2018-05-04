#pragma once

namespace math
{
    struct vector2d
    {
        float x;
        float y;
        
        vector2d();
        vector2d(float x, float y);

        bool operator==(const vector2d& other) const;
        bool operator!=(const vector2d& other) const;

		vector2d operator-(const vector2d& other) const;
		vector2d operator+(const vector2d& other) const;
        
		vector2d operator*(const vector2d& other) const;
        vector2d operator*(float s) const;
        vector2d operator/(float s) const;
        
        static const vector2d zero;
    };
}
