#pragma once

#include <stddef.h>

namespace GLBase{
    struct Matrix34;
    struct Matrix44;
    using float_type = float;

    struct MatrixView{
        private:
            float_type *_start;
            size_t _stride;
        public:
            size_t _rows, _cols;
            MatrixView(float_type *start, size_t rows, size_t cols, size_t stride);
            float_type& operator()(size_t i, size_t j);
            const float_type& operator()(size_t i, size_t j) const;
            float_type& operator[](size_t i);
            const float_type& operator[](size_t i) const;
    };

    struct Matrix33{
        float_type _data[9];
        float_type& operator[](size_t i);
        const float_type& operator[](size_t i) const;
        float_type& operator()(size_t i, size_t j);
        const float_type& operator()(size_t i, size_t j) const;
        
        static constexpr Matrix33 Identity() 
        {
            return Matrix33{1, 0, 0, 0, 1, 0, 0, 0, 1};
        }

        bool operator==(const Matrix33& other) const;
        bool operator!=(const Matrix33& other) const;
        bool operator==(MatrixView v) const;

        Matrix33& transpose(Matrix33& out) const;
        
        float_type det() const;
        Matrix33& invert(Matrix33& out) const;
        Matrix33 inverse() const;

        Matrix33& add(const Matrix33& other, Matrix33& out) const;
        Matrix33& sub(const Matrix33& other, Matrix33& out) const;
        Matrix33& mul(const Matrix33& other, Matrix33& out) const;

        Matrix33& operator*=(const Matrix33& other);
        Matrix33& operator*=(float_type x);
        Matrix33& operator/=(float_type x);
        MatrixView subMatrix(size_t i, size_t j, size_t r, size_t c);
        
        operator Matrix44() const;
        operator Matrix34() const;
    };

    struct Matrix34{
        float_type _data[12];
        float_type& operator[](size_t i);
        const float_type& operator[](size_t i) const;
        float_type& operator()(size_t i, size_t j);
        const float_type& operator()(size_t i, size_t j) const;
        
        static inline constexpr Matrix34 Identity() 
        {
            return Matrix34{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
        }

        bool operator==(const Matrix34& other) const;
        bool operator==(MatrixView v) const;
        bool operator!=(const Matrix34& other) const;

        Matrix34& invertTranformation(Matrix34& out) const;
        Matrix34 inverseTranformation() const;

        MatrixView subMatrix(size_t i, size_t j, size_t r, size_t c);
        Matrix34& add(const Matrix34& other, Matrix34& out) const;
        Matrix34& sub(const Matrix34& other, Matrix34& out) const;

        Matrix34& operator*=(float_type x);
        Matrix34& operator/=(float_type x);

        operator Matrix33() const;
        operator Matrix44() const;
        private:
        float_type det() const;
    };
    struct Matrix44{
        float_type _data[16];
        float_type& operator[](size_t i);
        const float_type& operator[](size_t i) const;
        float_type& operator()(size_t i, size_t j);
        const float_type& operator()(size_t i, size_t j) const;
        
        static inline constexpr Matrix44 Identity() 
        {
            return Matrix44{
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
        }
        Matrix44& transpose(Matrix44& out) const;
        
        Matrix44& add(const Matrix44& other, Matrix44& out) const;
        Matrix44& sub(const Matrix44& other, Matrix44& out) const;
        Matrix44& mul(const Matrix44& other, Matrix44& out) const;

        Matrix44& operator*=(const Matrix44& other);

        bool operator==(const Matrix44& other) const;
        bool operator!=(const Matrix44& other) const;

        Matrix44& invertTranformation(Matrix44& out) const;
        Matrix44 inverseTranformation() const;


        Matrix44& operator*=(float_type x);
        Matrix44& operator/=(float_type x);

        MatrixView subMatrix(size_t i, size_t j, size_t r, size_t c);

        operator Matrix33() const;
        operator Matrix34() const;
    };

    Matrix33 operator*(const Matrix33& M, float_type x);
    Matrix33 operator*(float_type x, const Matrix33& M);
    Matrix33 operator*(const Matrix33& A, const Matrix33& B);
    Matrix34 operator*(const Matrix34& M, float_type x);
    Matrix34 operator*(float_type x, const Matrix34& M);
    Matrix44 operator*(const Matrix44& M, float_type x);
    Matrix44 operator*(float_type x, const Matrix44& M);
    Matrix44 operator*(const Matrix44& A, const Matrix44& B);
    inline bool operator==(MatrixView v, const Matrix33& m){
        return m == v;
    }
    inline bool operator==(MatrixView v, const Matrix34& m){
        return m == v;
    }
    inline bool operator!=(MatrixView v, const Matrix33& m){
        return !(m == v);
    }
    inline bool operator!=(MatrixView v, const Matrix34& m){
        return !(m == v);
    }
}