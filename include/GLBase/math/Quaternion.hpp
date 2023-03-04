#pragma once

#include "Matrix.hpp"

namespace GLBase
{
    struct Matrix33;
    struct Vector3;

    class Quaternion
    {
    public:
        float_type w, x, y, z;
        Quaternion(float_type w, float_type x, float_type y, float_type z);
        Quaternion(const Vector3 &axis, float_type angle);
        Quaternion operator*(const Quaternion &other) const;
        Quaternion& operator*=(const Quaternion &other);
        Quaternion operator+(const Quaternion &other) const;
        Quaternion& operator+=(const Quaternion &other);
        Quaternion &normalize();
        Quaternion invert() const;
        Vector3 operator*(const Vector3 &v) const;
        Quaternion operator*(float_type v) const;
        static float_type deg2rad(float_type angle);
        static float_type rad2deg(float_type angle);
        operator Matrix33() const;
        operator Matrix44() const;
        static constexpr float_type Pi = 3.1415926535898f;
    };
} // namespace dddm
