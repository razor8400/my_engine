#include "vector4d.h"

namespace math
{
	const vector4d vector4d::zero = vector4d();
	const vector4d vector4d::one = vector4d(1, 1, 1, 1);
    
    vector4d::vector4d() : x(0), y(0), z(0), w(0)
    {

    }

    vector4d::vector4d(float x1, float y1, float z1, float w1) : x(x1), y(y1), z(z1), w(w1)
    {

    }
        
	vector4d vector4d::operator+(const vector4d& v4) const
	{
		return vector4d(x + v4.x, y + v4.y, z + v4.z, w + v4.w);
	}

	vector4d vector4d::operator-(const vector4d& v4) const
	{
		return vector4d(x - v4.x, y - v4.y, z - v4.z, w - v4.w);
	}
	
	vector4d vector4d::operator*(const vector4d& v4) const
	{
		return vector4d(x * v4.x, y * v4.y, z * v4.z, w * v4.w);
	}
	
	vector4d vector4d::operator*(float number) const
	{
		return vector4d(x * number, y * number, z * number, w * number);
	}

	vector4d vector4d::operator/(float number) const
	{
		return vector4d(x / number, y / number, z / number, w / number);
	}

    vector4d vector4d::operator*(const mat4& m4) const
    {
        vector4d result;
        
		result.x = x * m4[0] + y * m4[4] + z * m4[8] + w * m4[12];
		result.y = x * m4[1] + y * m4[5] + z * m4[9] + w * m4[13];
		result.z = x * m4[2] + y * m4[6] + z * m4[10] + w * m4[14];
		result.w = x * m4[3] + y * m4[7] + z * m4[11] + w * m4[15];
        
        return result;
    }
}

