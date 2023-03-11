#include <GLBase/math/Matrix.hpp>
#include <type_traits>

template<size_t N>
static inline constexpr bool eq(const GLBase::float_type a[N], const GLBase::float_type b[N])
{
    for(unsigned long long i = 0; i < N; ++i)
        if(a[i] != b[i]) return false;
    return true;
}

static inline constexpr size_t index(size_t i, size_t j, size_t cols)
{
    return cols * i + j;
}
template<size_t N>
static inline constexpr void transpose(const GLBase::float_type in[N], GLBase::float_type out[N])
{
    for(size_t i = 0; i < N; ++i)
        for(size_t j = 0; j < N; ++j)
            out[index(j, i, N)] = in[index(i, j, N)];
}
template<class Array>
static inline constexpr void add(const GLBase::float_type *a, const GLBase::float_type *b, Array& out){
    for(float& x: out)
        x = *a++ + *b++;
}
template<class Array>
static inline constexpr void sub(const GLBase::float_type *a, const GLBase::float_type *b, Array& out){
    for(float& x: out)
        x = *a++ - *b++;
}
template<size_t N>
static inline constexpr void mul(const GLBase::float_type *a, const GLBase::float_type *b, GLBase::float_type *out){
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            float s = 0;
            for(size_t k = 0; k < N; ++k)
                s += a[index(i, k, N)] * b[index(k, j, N)];
            out[index(i, j, N)] = s;
        }
    }
}
template<class Array>
static inline constexpr void mul(const float* in, Array& out, float x)
{
    for(float &v: out) v = x * *in++;
}

namespace GLBase
{
    float& Matrix33::operator[](size_t i) { return _data[i]; }
    const float& Matrix33::operator[](size_t i) const { return _data[i]; }
    float& Matrix33::operator()(size_t i, size_t j){ return _data[index(i, j, 3)]; }
    const float& Matrix33::operator()(size_t i, size_t j) const{ return _data[index(i, j, 3)]; }


    Matrix33& Matrix33::transpose(Matrix33& out) const {
        ::transpose<3>(_data, out._data);
        return out;
    }
    bool Matrix33::operator==(const Matrix33& other) const {
        return eq<std::extent_v<decltype(_data)>>(_data, other._data);
    }
    bool Matrix33::operator!=(const Matrix33& other) const {
        return !(*this == other);
    }

    Matrix33& Matrix33::add(const Matrix33& other, Matrix33& out) const{
        ::add(_data, other._data, out._data);
        return out;
    }
    Matrix33& Matrix33::sub(const Matrix33& other, Matrix33& out) const{
        ::sub(_data, other._data, out._data);
        return out;
    }
    Matrix33& Matrix33::mul(const Matrix33& other, Matrix33& out) const{
        ::mul<3>(_data, other._data, out._data);
        return out;
    }
    Matrix33& Matrix33::operator*=(const Matrix33& other) { 
        Matrix33 res;
        ::mul<3>(_data, other._data, res._data);
        return *this = res;
    }
    Matrix33& Matrix33::operator*=(float x){
        for(float& y: _data) y *= x;
        return *this;
    }
    Matrix33& Matrix33::operator/=(float x){
        for(float& y: _data) y /= x;
        return *this;
    }
    float Matrix33::det() const {
        return _data[0] * (_data[4] * _data[8] - _data[5] * _data[7]) - _data[1] * (_data[3] * _data[8] - _data[5] * _data[6]) + _data[2] * (_data[3] * _data[7] - _data[4] * _data[6]);
    };
    Matrix33& Matrix33::invert(Matrix33& out) const{
        float d = det();
        out._data[0] = (_data[4] * _data[8] - _data[5] * _data[7]) / d;
        out._data[1] = (_data[2] * _data[7] - _data[1] * _data[8]) / d;
        out._data[2] = (_data[1] * _data[5] - _data[2] * _data[4]) / d;
        out._data[3] = (_data[5] * _data[6] - _data[3] * _data[8]) / d;
        out._data[4] = (_data[0] * _data[8] - _data[2] * _data[6]) / d;
        out._data[5] = (_data[2] * _data[3] - _data[0] * _data[5]) / d;
        out._data[6] = (_data[3] * _data[7] - _data[4] * _data[6]) / d;
        out._data[7] = (_data[1] * _data[6] - _data[0] * _data[7]) / d;
        out._data[8] = (_data[0] * _data[4] - _data[1] * _data[3]) / d;
        return out;
    }
    Matrix33 Matrix33::inverse() const{
        Matrix33 inv;
        return invert(inv);
    }

    Matrix33::operator Matrix34() const {
        return Matrix34{
            _data[0], _data[1], _data[2], 0,
            _data[3], _data[4], _data[5], 0,
            _data[6], _data[7], _data[8], 0,
        };
    }


    float& Matrix34::operator[](size_t i) { return _data[i]; }
    const float& Matrix34::operator[](size_t i) const { return _data[i]; }
    float& Matrix34::operator()(size_t i, size_t j){ return _data[index(i, j, 4)]; }
    const float& Matrix34::operator()(size_t i, size_t j) const{ return _data[index(i, j, 4)]; }

    bool Matrix34::operator==(const Matrix34& other) const{
        return eq<12>(_data, other._data);
    }
    bool Matrix34::operator!=(const Matrix34& other) const{
        return !(*this==other);
    }
    float Matrix34::det() const{
       return _data[0] * (_data[5] * _data[10] - _data[6] * _data[9]) - _data[1] * (_data[4] * _data[10] - _data[6] * _data[8]) + _data[2] * (_data[4] * _data[9] - _data[5] * _data[8]);
    }
    Matrix34& Matrix34::invertTranformation(Matrix34& out) const{
        float d = det();
        out._data[0] = (_data[5] * _data[10] - _data[6] * _data[9]) / d;
        out._data[1] = (_data[2] * _data[9] - _data[1] * _data[10]) / d;
        out._data[2] = (_data[1] * _data[6] - _data[2] * _data[5]) / d;
        out._data[4] = (_data[6] * _data[8] - _data[4] * _data[10]) / d;
        out._data[5] = (_data[0] * _data[10] - _data[2] * _data[8]) / d;
        out._data[6] = (_data[2] * _data[4] - _data[0] * _data[6]) / d;
        out._data[8] = (_data[4] * _data[9] - _data[5] * _data[8]) / d;
        out._data[9] = (_data[1] * _data[8] - _data[0] * _data[9]) / d;
        out._data[10] = (_data[0] * _data[5] - _data[1] * _data[4]) / d;
        float V[] = {
            -(out._data[0] * _data[3] + out._data[1] * _data[7] + out._data[2] * _data[11]),
            -(out._data[4] * _data[3] + out._data[5] * _data[7] + out._data[6] * _data[11]),
            -(out._data[8] * _data[3] + out._data[9] * _data[7] + out._data[10] * _data[11]),
        };
        out._data[3] =  V[0];
        out._data[7] =  V[1];
        out._data[11] = V[2];

        return out;
    }
    Matrix34 Matrix34::inverseTranformation() const{
        Matrix34 res;
        return invertTranformation(res);
    }

    Matrix34& Matrix34::add(const Matrix34& other, Matrix34& out) const{
        ::add(_data, other._data, out._data);
        return out;
    }
    Matrix34& Matrix34::sub(const Matrix34& other, Matrix34& out) const{
        ::sub(_data, other._data, out._data);
        return out;
    }
    Matrix44& Matrix44::operator*=(const Matrix44& other) {
        return *this = *this * other;
    }

    Matrix34& Matrix34::operator*=(float x){
        for(float& y: _data) y *= x;
        return *this;
    }
    Matrix34& Matrix34::operator/=(float x){
        for(float& y: _data) y *= x;
        return *this;
    }

    Matrix34::operator Matrix44() const {
        return Matrix44{
            _data[0], _data[1], _data[2], _data[3],
            _data[4], _data[5], _data[6], _data[7],
            _data[8], _data[9], _data[10], _data[11],
            0, 0, 0, 1
        };
    }
    Matrix34::operator Matrix33() const {
        return Matrix33{
            _data[0], _data[1], _data[2],
            _data[4], _data[5], _data[6],
            _data[8], _data[9], _data[10],
        };
    }

    float_type& Matrix44::operator[](size_t i){
        return _data[i];        
    }
    const float_type& Matrix44::operator[](size_t i) const{
        return _data[i];
    }
    float_type& Matrix44::operator()(size_t i, size_t j){
        return _data[index(i, j, 4)];
    }
    const float_type& Matrix44::operator()(size_t i, size_t j) const{
        return _data[index(i, j, 4)];
    }
    bool Matrix44::operator==(const Matrix44& other) const{
        return ::eq<16>(_data, other._data);
    }
    bool Matrix44::operator!=(const Matrix44& other) const{
        return !(*this == other);
    }
    Matrix44& Matrix44::add(const Matrix44& other, Matrix44& out) const{
        ::add(_data, other._data, out._data);
        return out;
    }
    Matrix44& Matrix44::mul(const Matrix44& other, Matrix44& out) const{
        ::mul<4>(_data, other._data, out._data);
        return out;
    }
    Matrix44& Matrix44::sub(const Matrix44& other, Matrix44& out) const{
        ::sub(_data, other._data, out._data);
        return out;
    }
    Matrix44& Matrix44::operator*=(float_type x){
        for(auto& y: _data) y*=x;
        return *this;
    }
    Matrix44& Matrix44::operator/=(float_type x){
        for(auto& y: _data) y/=x;
        return *this;
    }
    Matrix44::operator Matrix33() const{
        return Matrix33{
            _data[0], _data[1], _data[2],
            _data[4], _data[5], _data[6],
            _data[8], _data[9], _data[10],
        };
    }
    Matrix44::operator Matrix34() const{
        return Matrix34{
            _data[0], _data[1], _data[2], _data[3],
            _data[4], _data[5], _data[6], _data[7],
            _data[8], _data[9], _data[10], _data[11],
        };
    }
    Matrix44& Matrix44::invertTranformation(Matrix44& out) const{
        float d = _data[0] * (_data[5] * _data[10] - _data[6] * _data[9]) - _data[1] * (_data[4] * _data[10] - _data[6] * _data[8]) + _data[2] * (_data[4] * _data[9] - _data[5] * _data[8]);

        out._data[0] = (_data[5] * _data[10] - _data[6] * _data[9]) / d;
        out._data[1] = (_data[2] * _data[9] - _data[1] * _data[10]) / d;
        out._data[2] = (_data[1] * _data[6] - _data[2] * _data[5]) / d;
        out._data[4] = (_data[6] * _data[8] - _data[4] * _data[10]) / d;
        out._data[5] = (_data[0] * _data[10] - _data[2] * _data[8]) / d;
        out._data[6] = (_data[2] * _data[4] - _data[0] * _data[6]) / d;
        out._data[8] = (_data[4] * _data[9] - _data[5] * _data[8]) / d;
        out._data[9] = (_data[1] * _data[8] - _data[0] * _data[9]) / d;
        out._data[10] = (_data[0] * _data[5] - _data[1] * _data[4]) / d;

        float V[] = {
            -(out._data[0] * _data[3] + out._data[1] * _data[7] + out._data[2] * _data[11]),
            -(out._data[4] * _data[3] + out._data[5] * _data[7] + out._data[6] * _data[11]),
            -(out._data[8] * _data[3] + out._data[9] * _data[7] + out._data[10] * _data[11]),
        };
        out._data[3] =  V[0];
        out._data[7] =  V[1];
        out._data[11] = V[2];

        out._data[15] = 1;
        return out;
    }
    Matrix44 Matrix44::inverseTranformation() const{
        Matrix44 res;
        return invertTranformation(res);
    }


    Matrix33 operator*(const Matrix33& M, float x){
        Matrix33 res;
        ::mul(M._data, res._data, x);
        return res;
    }
    Matrix33 operator*(float x, const Matrix33& M){
        return (M * x);
    }
    Matrix33 operator*(const Matrix33& A, const Matrix33& B){
        Matrix33 res;
        return A.mul(B, res);
    }

    Matrix34 operator*(const Matrix34& M, float x){
        Matrix34 res;
        ::mul(M._data, res._data, x);
        return res;
    }
    Matrix34 operator*(float x, const Matrix34& M){
        return (M * x);
    }

    Matrix44 operator*(const Matrix44& M, float_type x)
    {
        Matrix44 res;
        ::mul(M._data, res._data, x);
        return res;
    }
    Matrix44 operator*(float_type x, const Matrix44& M)
    {
        return (M * x);
    }
    Matrix33 operator/(const Matrix33& M, float_type x)
    {
        Matrix44 res;
        ::mul(M._data, res._data, 1.0f / x);
        return res;
    }
    Matrix34 operator/(const Matrix34& M, float_type x)
    {
        Matrix44 res;
        ::mul(M._data, res._data, 1.0f / x);
        return res;
    }
    Matrix44 operator/(const Matrix44& M, float_type x)
    {
        Matrix44 res;
        ::mul(M._data, res._data, 1.0f / x);
        return res;
    }
    Matrix44 operator*(const Matrix44& A, const Matrix44 &B)
    {
       Matrix44 res;
       ::mul<4>(A._data, B._data, res._data);
       return res; 
    }

    MatrixView::MatrixView(float_type *start, size_t rows, size_t cols, size_t stride):
        _start(start), _rows(rows), _cols(cols), _stride(stride)
    {}
    float_type& MatrixView::operator()(size_t i, size_t j){
        return _start[i * _stride + j];
    }
    const float_type& MatrixView::operator()(size_t i, size_t j) const {
        return _start[i * _stride + j];
    }
    float_type& MatrixView::operator[](size_t i){
        return _start[_stride * (i/_cols) + (i%_cols)];
    }
    const float_type& MatrixView::operator[](size_t i) const {
        return _start[_stride * (i/_cols) + (i%_cols)];
    }

    MatrixView Matrix33::subMatrix(size_t i, size_t j, size_t r, size_t c){
        return MatrixView(_data + index(i, j, 3), r, c, 3);
    }
    MatrixView Matrix34::subMatrix(size_t i, size_t j, size_t r, size_t c){
        return MatrixView(_data + index(i, j, 4), r, c, 4);
    }
    MatrixView Matrix44::subMatrix(size_t i, size_t j, size_t r, size_t c){
        return MatrixView(_data + index(i, j, 4), r, c, 4);
    }

    bool Matrix33::operator==(MatrixView v) const {
        if(v._rows != 3 ||v._cols != 3) return false;
        for(size_t i = 0; i < 9; ++i)
            if(_data[i] != v[i]) return false;
        return true;
    }
    bool Matrix34::operator==(MatrixView v) const {
        if(v._rows != 3 || v._cols != 4) return false;
        for(size_t i = 0; i < 12; ++i)
            if(_data[i] != v[i]) return false;
        return true;
    }

    Matrix44 orthographic(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
        return Matrix44{
            2.0f / (xMax - xMin), 0, 0, -(xMax + xMin) / (xMax - xMin),
            0, 2.0f / (yMax - yMin), 0, -(yMax + yMin) / (yMax - yMin),
            0, 0, 2.0f / (zMin - zMax), -(zMax + zMin) / (zMax - zMin),
            0, 0, 0, 1
        };
    } 

} // namespace GLBase
