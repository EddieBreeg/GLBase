#pragma once
#include "Matrix.hpp"

namespace GLBase
{
    struct Matrix33;
    struct Vector3;
    struct Vector4;

    struct Vector2
    {
        union {
            struct {float_type x, y;};
            float_type _data[2]{0};
        };
        Vector2 operator+(const Vector2& other) const;
        Vector2 operator*(const Vector2& other) const;
        Vector2 operator/(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator-() const;

         Vector2& operator+=(const Vector2& other);
         Vector2& operator-=(const Vector2& other);
         Vector2& operator*=(const Vector2& other);
         Vector2& operator/=(const Vector2& other);

         Vector2 operator*(const float_type x) const;
         Vector2 operator/(const float_type x) const;
         Vector2& operator*=(const float_type x);
         Vector2& operator/=(const float_type x);

         float_type dotProduct(const Vector2& other) const;
         float_type squaredDistance(const Vector2& other) const;
         float_type length() const;

         bool operator==(const Vector2& other) const;
         bool operator!=(const Vector2& other) const;

         operator Vector3() const;
         operator Vector4() const;
    };
    struct Vector3
    {
        union {
            struct { float_type x, y , z; };
            struct { float_type r, g , b; };
            float_type _data[3]{0};
        };

         Vector3 operator+(const Vector3& other) const;
         Vector3 operator*(const Vector3& other) const;
         Vector3 operator/(const Vector3& other) const;
         Vector3 operator-(const Vector3& other) const;
         Vector3 operator-() const;

         Vector3& operator+=(const Vector3& other);
         Vector3& operator-=(const Vector3& other);
         Vector3& operator*=(const Vector3& other);
         Vector3& operator/=(const Vector3& other);

         Vector3 operator*(const float_type x) const;
         Vector3 operator/(const float_type x) const;
         Vector3& operator*=(const float_type x);
         Vector3& operator/=(const float_type x);

         float_type dotProduct(const Vector3& other) const;
         Vector3 crossProduct(const Vector3& other) const;
         float_type squaredDistance(const Vector3& other) const;
         float_type length() const;
         Vector4 homogeneous() const;

         bool operator==(const Vector3& other) const;
         bool operator!=(const Vector3& other) const;

         operator Vector2() const;
         operator Vector4() const;
    };
    struct Vector4
    {
        union {
            struct{float_type x, y, z, w; };
            struct{float_type r, g, b, a; };
            float_type _data[4]{0};
        };

         Vector4 operator+(const Vector4& other) const;
         Vector4 operator*(const Vector4& other) const;
         Vector4 operator/(const Vector4& other) const;
         Vector4 operator-(const Vector4& other) const;
         Vector4 operator-() const;

         Vector4& operator+=(const Vector4& other);
         Vector4& operator-=(const Vector4& other);
         Vector4& operator*=(const Vector4& other);
         Vector4& operator/=(const Vector4& other);

         Vector4 operator*(const float_type x) const;
         Vector4 operator/(const float_type x) const;
         Vector4& operator*=(const float_type x);
         Vector4& operator/=(const float_type x);

         float_type dotProduct(const Vector4& other) const;
         float_type squaredDistance(const Vector4& other) const;
         float_type length() const;

         bool operator==(const Vector4& other) const;
         bool operator!=(const Vector4& other) const;

         operator Vector2() const;
         operator Vector3() const;
    };

    Vector2 operator*(float_type x, const Vector2& v);
    Vector3 operator*(float_type x, const Vector3& v);
    Vector4 operator*(float_type x, const Vector4& v);

    Vector3 operator*(const Matrix33& m, const Vector3& v);
    Vector3 operator*(const Matrix34& m, const Vector4& v);
    Vector4 operator*(const Matrix44& m, const Vector4& v);
    
} // namespace dddm
