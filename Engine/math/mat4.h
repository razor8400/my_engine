#pragma once

#include "vector3d.h"

namespace math
{
    class mat4
    {
        float m[16] = {
            1, 0, 0, 0, // 0,  4,  8,  12
            0, 1, 0, 0, // 1,  5,  9,  13
            0, 0, 1, 0, // 2,  6,  10, 14
            0, 0, 0, 1  // 3,  7,  11, 15
        };
    public:
        float& operator[](int a) { return m[a]; }
        const float& operator[](int a) const { return m[a]; }
                    
        void operator*=(const mat4& m);
        mat4 operator*(const mat4& m) const;
        mat4 operator*(float s) const;

        static mat4 translate(float x, float y, float z);
        static mat4 scale(float x, float y, float z);
        static mat4 rotate(const vector3d& axis, float angle);
        static mat4 inverse(const math::mat4& m);

        static mat4 look_at(const vector3d& eye, const vector3d& target, const vector3d& up = vector3d::up);
        static mat4 perspective(float fow, float aspect_ratio, float near_plane, float far_plane);
        static mat4 ortographic(float width, float height, float near_plane, float far_plane);
    
        static const mat4 identity;
    };
}
