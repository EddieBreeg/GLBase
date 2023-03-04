#pragma once

namespace GLBase
{
    struct vec3{
        double x, y, z;
        vec3(double x=0, double y=0, double z=0): x(x), y(y), z(z){}
        vec3 operator+(const vec3& other) const;
        vec3 operator-(const vec3& other) const;
        vec3 operator-() const;
        vec3 operator*(double v) const;
        vec3 operator/(double v) const;
        vec3& operator/=(double v);
        double dot(const vec3& other) const;
        double squaredLength() const;
        double length() const;
        vec3 cross(const vec3& other) const;
        vec3 normalized() const;
    };

    struct Vertex3d
    {
        vec3 position, normal;
        
        struct UV_coord {float u, v;} uv;
        Vertex3d(const vec3& position, const vec3& normal, const UV_coord& uv):
            position(position), normal(normal), uv(uv)
        {}
    };
} // namespace GLBase

