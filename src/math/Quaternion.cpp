#include <GLBase/math/Quaternion.hpp>
#include <GLBase/math/Vector.hpp>
#include <cmath>

namespace GLBase
{
    Quaternion::Quaternion(float_type w, float_type x, float_type y, float_type z) : w(w), x(x), y(y), z(z)
    {
    }

    Quaternion::Quaternion(const Vector3 &axis, float_type angle) : w(std::cos(angle / 2.0)),
                                                               x(axis.x * std::sin(angle / 2.0)),
                                                               y(axis.y * std::sin(angle / 2.0)),
                                                               z(axis.z * std::sin(angle / 2.0))
    {}
    Quaternion Quaternion::operator*(const Quaternion &other) const
    {
        return Quaternion(
                   w * other.w - x * other.x - y * other.y - z * other.z,
                   w * other.x + x * other.w + y * other.z - z * other.y,
                   w * other.y + y * other.w + z * other.x - x * other.z,
                   w * other.z + z * other.w + x * other.y - y * other.x);
    }
    Quaternion::operator Matrix33() const {
        return Matrix33{
            1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w),
            2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w),
            2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y),
        };
    }
    Quaternion::operator GLBase::Matrix44() const {
        return Matrix44{
            1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w), 0,
            2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w), 0,
            2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y), 0,
            0, 0, 0, 1
        };
    }
    Quaternion& Quaternion::operator*=(const Quaternion& other){ return  *this = other * *this; }
    Quaternion &Quaternion::normalize()
    {
        float_type s = sqrtf(w * w + x * x + y * y + z * z);
        if (s == 0)
            return *this;
        w /= s;
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }
    Quaternion Quaternion::operator+(const Quaternion &other) const
    {
        return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }
    Quaternion& Quaternion::operator+=(const Quaternion& other)
    {
        return *this = *this + other;
    }
    Vector3 Quaternion::operator*(const Vector3 &v) const
    {
        Quaternion r = *this * Quaternion(0, v.x, v.y, v.z) * invert();
        return Vector3{
            r.x, r.y, r.z
        };
    }
    Quaternion Quaternion::operator*(float_type v) const
    {
        return Quaternion(w * v, x * v, y * v, z * v);
    }

    float_type Quaternion::deg2rad(float_type angle)
    {
        return angle * Pi / 180.f;
    }
    float_type Quaternion::rad2deg(float_type angle)
    {
        return angle * 180.f / Pi;
    }
    Quaternion Quaternion::invert() const {
        return Quaternion(w, -x, -y, -z);
    }

} // namespace GLBase
