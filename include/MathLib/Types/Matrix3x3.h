///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.h
///---------------------------------------------------------------------------- 
#pragma once

#include <MathLib/Types/Vector3.h>

namespace ETL { namespace Math
{

    template<typename Type>
    class Matrix3x3
    {
    public:

        Matrix3x3();
        Matrix3x3(Type val);
        Matrix3x3(Type v00, Type v01, Type v02,
                  Type v10, Type v11, Type v12,
                  Type v20, Type v21, Type v22);

        Type  operator()(int row, int col) const;
        Type& operator()(int row, int col);
        Type  operator[](int index) const;
        Type& operator[](int index);

        Vector3<Type> getCol(int col) const;
        Vector3<Type> getRow(int row) const;

        void setCol(int col, const Vector3<Type>& value);
        void setRow(int row, const Vector3<Type>& value);

        void setCol(int col, Type c0, Type c1, Type c2);
        void setRow(int row, Type r0, Type r1, Type r2);

        Matrix3x3     operator+(const Matrix3x3& other) const;
        Matrix3x3     operator-(const Matrix3x3& other) const;
        Matrix3x3     operator*(const Matrix3x3& other) const;
        Vector3<Type> operator*(const Vector3<Type>& vector) const;
        Matrix3x3     operator*(Type scalar) const;

        Matrix3x3& operator+=(const Matrix3x3& other);
        Matrix3x3& operator-=(const Matrix3x3& other);
        Matrix3x3& operator*=(const Matrix3x3& other);
        Matrix3x3& operator*=(Type scalar);

        Type determinant() const;

        Matrix3x3 transpose() const;
        Matrix3x3& makeTranspose();

        Matrix3x3 inverse() const;
        Matrix3x3& makeInverse();

        static const Matrix3x3 Identity = Matrix3x3(Type(1));

    protected:
        const Type* const getRawData() const { return mData; }

    private:
        union {
            struct { Type m00, m10, m20, m01, m11, m21, m02, m12, m22; }; /// 1D access
            Type m[3][3];                                                 /// 2D access
            Type mData[9];                                                /// Named access
        };
    };


    /// Scalar * matrix operator 
    template<typename Type>
    Matrix3x3<Type> operator*(Type scalar, const Matrix3x3<Type>& v2);


    /// Helpful aliases
    using Mat3  = Matrix3x3<float>;
    using Mat3d = Matrix3x3<double>;


    /// Explicit template instantiatio (precompiled declaration)
    extern template class Matrix3x3<float>;
    extern template class Matrix3x3<double>;


}} /// namespace ETL::Math
