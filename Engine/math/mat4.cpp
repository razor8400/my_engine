#include <math.h>
#include <cmath>

#include "mat4.h"
#include "functions.h"

namespace math
{
    const mat4 mat4::identity;
    static const int size = 4;
    
    void mat4::operator*=(const mat4& m4)
    {
        *this = *this * m4;
    }
    
    mat4 mat4::operator*(const mat4& m4) const
    {
        mat4 mat;
        
        mat[0] = m[0] * m4[0] + m[4] * m4[1] + m[8] * m4[2] + m[12] * m4[3];
        mat[1] = m[1] * m4[0] + m[5] * m4[1] + m[9] * m4[2] + m[13] * m4[3];
        mat[2] = m[2] * m4[0] + m[6] * m4[1] + m[10] * m4[2] + m[14] * m4[3];
        mat[3] = m[3] * m4[0] + m[7] * m4[1] + m[11] * m4[2] + m[15] * m4[3];
        
        mat[4] = m[0] * m4[4] + m[4] * m4[5] + m[8] * m4[6] + m[12] * m4[7];
        mat[5] = m[1] * m4[4] + m[5] * m4[5] + m[9] * m4[6] + m[13] * m4[7];
        mat[6] = m[2] * m4[4] + m[6] * m4[5] + m[10] * m4[6] + m[14] * m4[7];
        mat[7] = m[3] * m4[4] + m[7] * m4[5] + m[11] * m4[6] + m[15] * m4[7];
        
        mat[8] = m[0] * m4[8] + m[4] * m4[9] + m[8] * m4[10] + m[12] * m4[11];
        mat[9] = m[1] * m4[8] + m[5] * m4[9] + m[9] * m4[10] + m[13] * m4[11];
        mat[10] = m[2] * m4[8] + m[6] * m4[9] + m[10] * m4[10] + m[14] * m4[11];
        mat[11] = m[3] * m4[8] + m[7] * m4[9] + m[11] * m4[10] + m[15] * m4[11];
        
        mat[12] = m[0] * m4[12] + m[4] * m4[13] + m[8] * m4[14] + m[12] * m4[15];
        mat[13] = m[1] * m4[12] + m[5] * m4[13] + m[9] * m4[14] + m[13] * m4[15];
        mat[14] = m[2] * m4[12] + m[6] * m4[13] + m[10] * m4[14] + m[14] * m4[15];
        mat[15] = m[3] * m4[12] + m[7] * m4[13] + m[11] * m4[14] + m[15] * m4[15];
        
        return mat;
    }
    
    mat4 mat4::operator*(float s) const
    {
        mat4 mat;
        
        for (int i = 0; i < size * size; ++i)
            mat[i] = m[i] * s;
        
        return mat;
    }

    mat4 mat4::translate(float x, float y, float z)
    {
        mat4 mat;

        mat[12] = x;
        mat[13] = y;
        mat[14] = z;

        return mat;
    }

    mat4 mat4::scale(float x, float y, float z)
    {
        mat4 mat;

        mat[0] = x;
        mat[5] = y;
        mat[10] = z;
        
        return mat;
    }

    mat4 mat4::rotate(const vector3d & axis, float angle)
    {
        mat4 mat;

        auto normalized_axis = vector3d::normalize(axis);
        auto rad = deg_to_rad(angle);

        float c = cos(rad);
        float s = sin(rad);

        float t = 1.0f - c;

        float tx = t * normalized_axis.x;
        float ty = t * normalized_axis.y;
        float tz = t * normalized_axis.z;

        float txy = tx * normalized_axis.y;
        float txz = tx * normalized_axis.z;
        float tyz = ty * normalized_axis.z;

        float sx = s * normalized_axis.x;
        float sy = s * normalized_axis.y;
        float sz = s * normalized_axis.z;
                    
        mat[0] = c + tx * normalized_axis.x;
        mat[1] = txy + sz;
        mat[2] = txz - sy;
        mat[3] = 0.0f;

        mat[4] = txy - sz;
        mat[5] = c + ty * normalized_axis.y;
        mat[6] = tyz + sx;

        mat[8] = txz + sy;
        mat[9] = tyz - sx;
        mat[10] = c + tz * normalized_axis.z;

        return mat;
    }
    
    mat4 mat4::inverse(const mat4& m)
    {
        float a0 = m[0] * m[5] - m[1] * m[4];
        float a1 = m[0] * m[6] - m[2] * m[4];
        float a2 = m[0] * m[7] - m[3] * m[4];
        float a3 = m[1] * m[6] - m[2] * m[5];
        float a4 = m[1] * m[7] - m[3] * m[5];
        float a5 = m[2] * m[7] - m[3] * m[6];
        float b0 = m[8] * m[13] - m[9] * m[12];
        float b1 = m[8] * m[14] - m[10] * m[12];
        float b2 = m[8] * m[15] - m[11] * m[12];
        float b3 = m[9] * m[14] - m[10] * m[13];
        float b4 = m[9] * m[15] - m[11] * m[13];
        float b5 = m[10] * m[15] - m[11] * m[14];
        
        // Calculate the determinant.
        float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
        
        // Close to zero, can't invert.
        if (std::abs(det) <= 0)
            return identity;
        
        // Support the case where m == dst.
        mat4 inverse;
        inverse.m[0]  = m[5] * b5 - m[6] * b4 + m[7] * b3;
        inverse.m[1]  = -m[1] * b5 + m[2] * b4 - m[3] * b3;
        inverse.m[2]  = m[13] * a5 - m[14] * a4 + m[15] * a3;
        inverse.m[3]  = -m[9] * a5 + m[10] * a4 - m[11] * a3;
        
        inverse.m[4]  = -m[4] * b5 + m[6] * b2 - m[7] * b1;
        inverse.m[5]  = m[0] * b5 - m[2] * b2 + m[3] * b1;
        inverse.m[6]  = -m[12] * a5 + m[14] * a2 - m[15] * a1;
        inverse.m[7]  = m[8] * a5 - m[10] * a2 + m[11] * a1;
        
        inverse.m[8]  = m[4] * b4 - m[5] * b2 + m[7] * b0;
        inverse.m[9]  = -m[0] * b4 + m[1] * b2 - m[3] * b0;
        inverse.m[10] = m[12] * a4 - m[13] * a2 + m[15] * a0;
        inverse.m[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;
        
        inverse.m[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
        inverse.m[13] = m[0] * b3 - m[1] * b1 + m[2] * b0;
        inverse.m[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
        inverse.m[15] = m[8] * a3 - m[9] * a1 + m[10] * a0;
        
        return inverse * (1.0f / det);
    }

    mat4 mat4::look_at(const vector3d& eye, const vector3d& target, const vector3d& up)
    {
        mat4 mat;

        auto normalized_eye = vector3d::normalize(eye);

        auto zaxis = vector3d::normalize(target - eye);
        auto xaxis = vector3d::normalize(vector3d::cross(up, zaxis));
        auto yaxis = vector3d::normalize(vector3d::cross(zaxis, xaxis));
        
        mat[0] = xaxis.x;
        mat[1] = yaxis.x;
        mat[2] = zaxis.x;

        mat[4] = xaxis.y;
        mat[5] = yaxis.y;
        mat[6] = zaxis.y;

        mat[8] = xaxis.z;
        mat[9] = yaxis.z;
        mat[10] = zaxis.z;

        mat[12] = -vector3d::dot(xaxis, normalized_eye);
        mat[13] = -vector3d::dot(yaxis, normalized_eye);
        mat[14] = -vector3d::dot(zaxis, normalized_eye);

        return mat;
    }

    mat4 mat4::perspective(float fow, float aspect_ratio, float near_plane, float far_plane)
    {
        mat4 mat;

        float tangent = tan(deg_to_rad(fow) * 0.5f);

        mat[0] = 1.0f / (aspect_ratio * tangent);
        mat[5] = 1.0f / tangent;
        mat[10] = (far_plane + near_plane) / (far_plane - near_plane);
        
        mat[11] = 1.0f;
        mat[14] = -(2.0f * far_plane * near_plane) / (far_plane - near_plane);

        return mat;
    }
    
    mat4 mat4::ortographic(float width, float height, float near_plane, float far_plane)
    {
        mat4 mat;
        
        float half_width = width / 2.0f;
        float half_height = height / 2.0f;
        
        float left = -half_width;
        float right = half_width;
        float bottom = -half_height;
        float top = half_height;
        
        mat[0] = 2 / (right - left);
        mat[5] = 2 / (top - bottom);
        mat[10] = 2 / (near_plane - far_plane);
        
        mat[3] = (left + right) / (left - right);
        mat[7] = (top + bottom) / (bottom - top);
        mat[11] = (near_plane + far_plane) / (near_plane - far_plane);
        
        return mat;
    }
}
