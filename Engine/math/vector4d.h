#pragma once

#include "mat4.h"

namespace math
{
    struct vector4d
    {
        float x, y, z, w;
    
        vector4d();
        vector4d(float x1, float y1, float z1, float w1);
        
		vector4d operator+(const vector4d& v3) const;
		vector4d operator-(const vector4d& v3) const;
		vector4d operator*(const vector4d& v3) const;

		vector4d operator*(float number) const;
		vector4d operator/(float number) const;
        vector4d operator*(const mat4& m4) const;

		static const vector4d one;
		static const vector4d zero;
	};
}
