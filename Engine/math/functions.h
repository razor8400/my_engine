#pragma once

#ifndef M_PI
#define M_PI       3.14159265358979323846f
#endif

#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"

namespace math
{
    static float deg_to_rad(float rotation)
    {
        return rotation * M_PI / 180;
    }
    
    static float line_equation(const vector2d& a, const vector2d& b, const vector2d& c)
    {
        vector2d ba = b - a;
        vector2d ca = c - a;
        
        return ca.x * ba.y - ca.y * ba.x;
    }
    
    static vector2d transform_point(const vector2d& v2, const mat4& transform)
    {
        auto point = vector4d(v2.x, v2.y, 0, 1) * transform;
        return vector2d(point.x, point.y);
    }
    
    static vector3d transform_point(const vector3d& v3, const mat4& transform)
    {
        auto point = vector4d(v3.x, v3.y, v3.z, 1) * transform;
        return vector3d(point.x, point.y, point.z);
    }
}
