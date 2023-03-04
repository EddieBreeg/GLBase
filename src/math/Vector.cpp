#include <GLBase/math/Vector.hpp>
#include <type_traits>
#include <cmath>

template<class VecType>
static inline constexpr VecType add(const VecType& a, const VecType& b)
{
    VecType result;
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    result._data[i] = a._data[i] + b._data[i];
    return result;
}
template<class VecType>
static inline constexpr VecType mul(const VecType& a, const VecType& b)
{
    VecType result;
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    result._data[i] = a._data[i] * b._data[i];
    return result;
}
template<class VecType>
static inline constexpr VecType div(const VecType& a, const VecType& b)
{
    VecType result;
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    result._data[i] = a._data[i] / b._data[i];
    return result;
}
template<class VecType>
static inline constexpr VecType sub(const VecType& a, const VecType& b)
{
    VecType result;
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    result._data[i] = a._data[i] - b._data[i];
    return result;
}
template<class VecType>
static inline constexpr VecType neg(const VecType& v)
{
    VecType result;
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    result._data[i] = -v._data[i];
    return result;
}
template<class VecType>
static inline constexpr bool eq(const VecType& a, const VecType& b)
{
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    if(a._data[i] != b._data[i]) return false;
    return true;
}
template<class VecType>
static inline constexpr float dotProduct(const VecType& a, const VecType& b)
{
    float s = 0;
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    s += a._data[i] * b._data[i];
    return s;
}
template<class VecType>
static inline constexpr VecType mul(float x, const VecType& v)
{
    VecType r;
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    r._data[i] = x * v._data[i];
    return r;
}
template<class VecType>
static inline constexpr VecType div(const VecType& v, float x)
{
    VecType r;
    for(size_t i = 0; i < std::extent_v<decltype(VecType::_data)>; ++i)
	    r._data[i] = v._data[i] / x;
    return r;
}

namespace GLBase
{
	Vector2 Vector2::operator+(const Vector2& other) const{
	   return add(*this, other);
    }
	Vector2 Vector2::operator*(const Vector2& other) const{
	   return mul(*this, other);
    }
	Vector2 Vector2::operator/(const Vector2& other) const{
	   return div(*this, other);
    }
	Vector2 Vector2::operator-(const Vector2& other) const{
	   return sub(*this, other);
    }
	Vector2 Vector2::operator-() const{
	   return neg(*this);
    }

	Vector2& Vector2::operator+=(const Vector2& other){
	   return (*this = *this + other);
    }
	Vector2& Vector2::operator-=(const Vector2& other){
	   return (*this = *this - other);
    }
	Vector2& Vector2::operator*=(const Vector2& other){
	   return (*this = *this * other);
    }
	Vector2& Vector2::operator/=(const Vector2& other){
	   return (*this = *this / other);
    }

	Vector2 Vector2::operator*(const float x) const{
	   return mul(x, *this);
    }
	Vector2 Vector2::operator/(const float x) const{
	   return div(*this, x);
    }
	Vector2& Vector2::operator*=(const float x){
	   return (*this = x * *this);
    }
	Vector2& Vector2::operator/=(const float x){
	   return (*this = *this / x);
    }

	float Vector2::dotProduct(const Vector2& other) const{
	   return ::dotProduct(*this, other);
    }
	float Vector2::squaredDistance(const Vector2& other) const{
	   auto r = other - *this;
	   return r.dotProduct(r);
    }
	float Vector2::length() const{
	   return sqrtf(dotProduct(*this));
    }

	bool Vector2::operator==(const Vector2& other) const{
	   return eq(*this, other);
    }
	bool Vector2::operator!=(const Vector2& other) const{
	   return !(*this == other);
    }
	Vector2::operator Vector3() const{
	   return Vector3{x, y, 0};
    }
	Vector2::operator Vector4() const{
	   return Vector4{x, y, 0, 0};
    }

	Vector3 Vector3::operator+(const Vector3& other) const{
	   return add(*this, other);
    }
	Vector3 Vector3::operator*(const Vector3& other) const{
	   return mul(*this, other);
    }
	Vector3 Vector3::operator/(const Vector3& other) const{
	   return div(*this, other);
    }
	Vector3 Vector3::operator-(const Vector3& other) const{
	   return sub(*this, other);
    }
	Vector3 Vector3::operator-() const{
	   return neg(*this);
    }

	Vector3& Vector3::operator+=(const Vector3& other){
	   return (*this = *this + other);
    }
	Vector3& Vector3::operator-=(const Vector3& other){
	   return (*this = *this - other);
    }
	Vector3& Vector3::operator*=(const Vector3& other){
	   return (*this = *this * other);
    }
	Vector3& Vector3::operator/=(const Vector3& other){
	   return (*this = *this / other);
    }

	Vector3 Vector3::operator*(const float x) const{
	   return mul(x, *this);
    }
	Vector3 Vector3::operator/(const float x) const{
	   return div(*this, x);
    }
	Vector3& Vector3::operator*=(const float x){
	   return (*this = x * *this);
    }
	Vector3& Vector3::operator/=(const float x){
	   return (*this = *this / x);
    }

	float Vector3::dotProduct(const Vector3& other) const{
	   return ::dotProduct(*this, other);
    }
	float Vector3::squaredDistance(const Vector3& other) const{
	   auto r = other - *this;
	   return r.dotProduct(r);
    }
	float Vector3::length() const{
	   return sqrtf(dotProduct(*this));
    }
	Vector4 Vector3::homogeneous() const{
		return Vector4{x, y, z, 1};
	}
	bool Vector3::operator==(const Vector3& other) const{
	   return eq(*this, other);
    }
	bool Vector3::operator!=(const Vector3& other) const{
	   return !(*this == other);
    }
	Vector3::operator Vector2() const{
	   return Vector2{x, y};
    }
	Vector3::operator Vector4() const{
	   return Vector4{x, y, z, 0};
    }

	Vector4 Vector4::operator+(const Vector4& other) const{
	   return add(*this, other);
    }
	Vector4 Vector4::operator*(const Vector4& other) const{
	   return mul(*this, other);
    }
	Vector4 Vector4::operator/(const Vector4& other) const{
	   return div(*this, other);
    }
	Vector4 Vector4::operator-(const Vector4& other) const{
	   return sub(*this, other);
    }
	Vector4 Vector4::operator-() const{
	   return neg(*this);
    }

	Vector4& Vector4::operator+=(const Vector4& other){
	   return (*this = *this + other);
    }
	Vector4& Vector4::operator-=(const Vector4& other){
	   return (*this = *this - other);
    }
	Vector4& Vector4::operator*=(const Vector4& other){
	   return (*this = *this * other);
    }
	Vector4& Vector4::operator/=(const Vector4& other){
	   return (*this = *this / other);
    }

	Vector4 Vector4::operator*(const float x) const{
	   return mul(x, *this);
    }
	Vector4 Vector4::operator/(const float x) const{
	   return div(*this, x);
    }
	Vector4& Vector4::operator*=(const float x){
	   return (*this = x * *this);
    }
	Vector4& Vector4::operator/=(const float x){
	   return (*this = *this / x);
    }

	float Vector4::dotProduct(const Vector4& other) const{
	   return ::dotProduct(*this, other);
    }
	float Vector4::squaredDistance(const Vector4& other) const{
	   auto r = other - *this;
	   return r.dotProduct(r);
    }
	float Vector4::length() const{
	   return sqrtf(dotProduct(*this));
    }

	bool Vector4::operator==(const Vector4& other) const{
	   return eq(*this, other);
    }
	bool Vector4::operator!=(const Vector4& other) const{
	   return !(*this == other);
    }
	Vector4::operator Vector2() const{
	   return Vector2{x, y};
    }
	Vector4::operator Vector3() const{
	   return Vector3{x, y, z};
    }

    Vector2 operator*(float x, const Vector2& v){
	   return mul(x, v);
    }
    Vector3 operator*(float x, const Vector3& v){
	   return mul(x, v);
    }
    Vector4 operator*(float x, const Vector4& v){
	   return mul(x, v);
    }

	Vector3 operator*(const Matrix33& m, const Vector3& v){
		return Vector3{
			m[0] * v.x + m[1] * v.y + m[2] * v.z,
			m[3] * v.x + m[4] * v.y + m[5] * v.z,
			m[6] * v.x + m[7] * v.y + m[8] * v.z,
		};
	}
    Vector3 operator*(const Matrix34& m, const Vector4& v){
		return Vector3{
			m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3] * v.w,
			m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7] * v.w,
			m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11] * v.w,
		};
	}
    Vector4 operator*(const Matrix44& m, const Vector4& v){
		return Vector4{
			m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3] * v.w,
			m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7] * v.w,
			m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11] * v.w,
			m[12] * v.x + m[13] * v.y + m[14] * v.z + m[15] * v.w,
		};
	}

    
} // namespace dddm

