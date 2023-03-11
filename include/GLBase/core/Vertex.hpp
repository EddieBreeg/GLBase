#pragma once

#include "VertexBufferLayout.hpp"

namespace GLBase
{
    struct vec3{
        float x, y, z;
        vec3(float x=0, float y=0, float z=0): x(x), y(y), z(z){}
        vec3 operator+(const vec3& other) const;
        vec3 operator-(const vec3& other) const;
        vec3 operator-() const;
        vec3 operator*(float v) const;
        vec3 operator/(float v) const;
        vec3& operator/=(float v);
        float dot(const vec3& other) const;
        float squaredLength() const;
        float length() const;
        vec3 cross(const vec3& other) const;
        vec3 normalized() const;
    };

    // A very basic 3D vertex structure
    struct Vertex3d
    {
        vec3 position, normal;
        
        struct UV_coord {float u, v;} uv;
        Vertex3d(const vec3& position, const vec3& normal, const UV_coord& uv):
            position(position), normal(normal), uv(uv)
        {}
        static VertexLayout<3> layout()
        {
            return VertexLayout<3>(
                VertexLayoutElement::create<decltype(vec3::x)>(3),
                VertexLayoutElement::create<decltype(vec3::x)>(3),
                VertexLayoutElement::create<float>(2)
            );
        }
    };
} // namespace GLBase

