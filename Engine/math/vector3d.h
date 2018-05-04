#pragma once

#include "vector2d.h"

namespace math
{
    struct vector3d
    {
        float x, y, z;
        
        vector3d();
        vector3d(float x1, float y1, float z1);
        vector3d(const vector2d& v2);

        vector3d operator+(const vector3d& v3) const;
        vector3d operator-(const vector3d& v3) const;
        vector3d operator*(const vector3d& v3) const;

        vector3d operator*(float number) const;
        vector3d operator/(float number) const;
        
        float lenght() const;

        static float dot(const vector3d& v1, const vector3d& v2);

        static vector3d normalize(const vector3d& v3);
        static vector3d cross(const vector3d& v1, const vector3d& v2);

        static const vector3d zero;
        static const vector3d one;
        static const vector3d up;
        static const vector3d left;
        static const vector3d down;
        static const vector3d right;
    };
}

