#include <GLBase/core/Vertex.hpp>
#include <cmath>

namespace GLBase
{
    vec3 vec3::operator+(const vec3& other) const {
        return {x+other.x, y+other.y, z+other.z};
    }
    vec3 vec3::operator-(const vec3& other) const {
        return {x-other.x, y-other.y, z-other.z};
    }
    vec3 vec3::operator-() const {
        return {-x, -y, -z};
    }
    vec3 vec3::operator*(float v) const { return {
        v*x, v*y, v*z
    };}
    vec3 vec3::operator/(float v) const { return {
        x/v, y/v, z/v
    };}
    vec3& vec3::operator/=(float v) {
        return *this = *this / v;
    }
    float vec3::dot(const vec3& other) const {
        return x*other.x + y*other.y + z*other.z;
    }
    float vec3::squaredLength() const { return dot(*this); }
    float vec3::length() const { return sqrt(dot(*this)); }
    vec3 vec3::cross(const vec3& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
        };
    }
    vec3 vec3::normalized() const {
        return *this / length();
    }
} // namespace GLBase
