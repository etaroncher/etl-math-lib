///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.cpp
///----------------------------------------------------------------------------

#include <MathLib/Types/Matrix3x3.h>
#include <MathLib/Common/Common.h>
#include <MathLib/Common/TypeComparisons.h>
#include <cmath>

namespace ETL { namespace Math
{


    /// <summary>
    /// Default Constructor Identity matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    template<typename Type>
    Matrix3x3<Type>::Matrix3x3()
        : mData{ Type(1), Type(0), Type(0), Type(0), Type(1), Type(0), Type(0), Type(0), Type(1) } {}


    /// <summary>
    /// Matrix diagonal constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="val"></param>
    template<typename Type>
    Matrix3x3<Type>::Matrix3x3(Type val)
        : mData{ val, Type(0), Type(0), Type(0), val, Type(0), Type(0), Type(0), val } {}


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    Matrix3x3<Type>::Matrix3x3(Type v00, Type v01, Type v02,
                               Type v10, Type v11, Type v12,
                               Type v20, Type v21, Type v22)
        : mData{ v00, v10, v20, v01, v11, v21, v02, v12, v22 } {}


    /// <summary>
    /// Const application operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    Type Matrix3x3<Type>::operator()(int row, int col) const
    {
        ETLMATH_ASSERT(row >= 0 && row < 3, "Matrix3x3 out of bounds ROW acces");
        ETLMATH_ASSERT(col >= 0 && col < 3, "Matrix3x3 out of bounds COL acces");

        return mData[row*3+col];
    }


    /// <summary>
    /// Application operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    Type& Matrix3x3<Type>::operator()(int row, int col)
    {
        ETLMATH_ASSERT(row >= 0 && row < 3, "Matrix3x3 out of bounds ROW acces");
        ETLMATH_ASSERT(col >= 0 && col < 3, "Matrix3x3 out of bounds COL acces");

        return mData[row * 3 + col];
    }


    /// <summary>
    /// Const subscription operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    Type Matrix3x3<Type>::operator[](int elem) const
    {
        ETLMATH_ASSERT(elem >= 0 && elem < 9, "Matrix3x3 out of bounds ELEM acces");

        return mData[elem];
    }


    /// <summary>
    /// Subscription operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    Type& Matrix3x3<Type>::operator[](int elem)
    {
        ETLMATH_ASSERT(elem >= 0 && elem < 9, "Matrix3x3 out of bounds ELEM acces");

        return mData[elem];
    }


    /// <summary>
    /// Column getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <returns>Column as Vector3</returns>
    template<typename Type>
    Vector3<Type> Matrix3x3<Type>::getCol(int col) const
    {
        ETLMATH_ASSERT(col >= 0 && col < 3, "Matrix3x3 out of bounds COL acces");

        return { mData[col*3], mData[col*3 + 1], mData[col*3 + 2] };
    }


    /// <summary>
    /// Row getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <returns>Row as Vector3</returns>
    template<typename Type>
    Vector3<Type> Matrix3x3<Type>::getRow(int row) const
    {
        ETLMATH_ASSERT(row >= 0 && row < 3, "Matrix3x3 out of bounds ROW acces");

        return { mData[row], mData[3 + row], mData[6 + row] };
    }


    /// <summary>
    /// Column setter by Vector3
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <param name="value"></param>
    template<typename Type>
    void Matrix3x3<Type>::setCol(int col, const Vector3<Type>& value)
    {
        ETLMATH_ASSERT(col >= 0 && col < 3, "Matrix3x3 out of bounds COL acces");

        mData[col * 3]     = value.x();
        mData[col * 3 + 1] = value.y();
        mData[col * 3 + 2] = value.z();
    }


    /// <summary>
    /// Row setter by Vector3
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="value"></param>
    template<typename Type>
    void Matrix3x3<Type>::setRow(int row, const Vector3<Type>& value)
    {
        ETLMATH_ASSERT(row >= 0 && row < 3, "Matrix3x3 out of bounds ROW acces");

        mData[row]     = value.x();
        mData[3 + row] = value.y();
        mData[6 + row] = value.z();
    }


    /// <summary>
    /// Column setter by element
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <param name="c0"></param>
    /// <param name="c1"></param>
    /// <param name="c2"></param>
    template<typename Type>
    void Matrix3x3<Type>::setCol(int col, Type c0, Type c1, Type c2)
    {
        ETLMATH_ASSERT(col >= 0 && col < 3, "Matrix3x3 out of bounds COL acces");

        mData[col * 3]     = c0;
        mData[col * 3 + 1] = c1;
        mData[col * 3 + 2] = c2;
    }


    /// <summary>
    /// Row setter by element
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="r0"></param>
    /// <param name="r1"></param>
    /// <param name="r2"></param>
    template<typename Type>
    void Matrix3x3<Type>::setRow(int row, Type r0, Type r1, Type r2)
    {
        ETLMATH_ASSERT(row >= 0 && row < 3, "Matrix3x3 out of bounds ROW acces");

        mData[row]     = r0;
        mData[3 + row] = r1;
        mData[6 + row] = r2;
    }


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::operator+(const Matrix3x3& other) const
    {
        return Matrix3x3<Type>{ m00 + other.m00, m01 + other.m01, m02 + other.m02,
                                m10 + other.m10, m11 + other.m11, m12 + other.m12,
                                m20 + other.m20, m21 + other.m21, m22 + other.m22 };
    }


    /// <summary>
    /// Substraction operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::operator-(const Matrix3x3& other) const
    {
        return Matrix3x3<Type>{ m00 - other.m00, m01 - other.m01, m02 - other.m02,
                                m10 - other.m10, m11 - other.m11, m12 - other.m12,
                                m20 - other.m20, m21 - other.m21, m22 - other.m22 };
    }


    /// <summary>
    /// Matrix multiplication operator (This * Other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::operator*(const Matrix3x3& other) const
    {
        return Matrix3x3<Type>{ m00*other.m00 + m01*other.m10 + m02*other.m20,   //m00
                                m00*other.m01 + m01*other.m11 + m02*other.m21,   //m01
                                m00*other.m02 + m01*other.m12 + m02*other.m22,   //m02
                                m10*other.m00 + m11*other.m10 + m12*other.m20,   //m10
                                m10*other.m01 + m11*other.m11 + m12*other.m21,   //m11
                                m10*other.m02 + m11*other.m12 + m12*other.m22,   //m12
                                m20*other.m00 + m21*other.m10 + m22*other.m20,   //m20
                                m20*other.m01 + m21*other.m11 + m22*other.m21,   //m21
                                m20*other.m02 + m21*other.m12 + m22*other.m22 }; //m22
    }


    /// <summary>
    /// Vector multiplication operator (This * Vector)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="vector"></param>
    /// <returns>Resulting vector</returns>
    template<typename Type>
    Vector3<Type> Matrix3x3<Type>::operator*(const Vector3<Type>& vector) const
    {
        return Vector3<Type>{ m00 * vector.x() + m01 * vector.y() + m02 * vector.z(),
                              m10 * vector.x() + m11 * vector.y() + m12 * vector.z(),
                              m20 * vector.x() + m21 * vector.y() + m22 * vector.z() };
    }


    /// <summary>
    /// Scalar multiplication operator (This * scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::operator*(Type scalar) const
    {
        return Matrix3x3<Type>{ m00 * scalar, m01 * scalar, m02 * scalar,
                                m10 * scalar, m11 * scalar, m12 * scalar,
                                m20 * scalar, m21 * scalar, m22 * scalar };
    }


    /// <summary>
    /// Addition assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator+=(const Matrix3x3& other)
    {
        for (int i = 0; i < 9; ++i)
            mData[i] += other.mData[i];

        return *this;
    }


    /// <summary>
    /// Substraction assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator-=(const Matrix3x3& other)
    {
        for (int i = 0; i < 9; ++i)
            mData[i] -= other.mData[i];

        return *this;
    }


    /// <summary>
    /// Matrix multiplication operator (This * Other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator*=(const Matrix3x3& other)
    {
        *this = *this * other;

        return *this;
    }


    /// <summary>
    /// Scalar multiplication assignment operator (This * scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator*=(Type scalar)
    {
        for (int i = 0; i < 9; ++i)
            mData[i] *= scalar;

        return *this;
    }


    /// <summary>
    /// Computes matrix determinant
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Matrix3x3<Type>::determinant() const
    {
        return m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m02*m11*m20 - m00*m12*m21 - m01*m10*m22;
    }


    /// <summary>
    /// Compute the transpose
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::transpose() const
    {
        return Matrix3x3<Type>{ m00, m10, m20, m01, m11, m21, m02, m12, m22 };
    }


    /// <summary>
    /// Transpose this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::makeTranspose()
    {
        std::swap(m01, m10);
        std::swap(m02, m20);
        std::swap(m12, m21);

        return *this;
    }


    /// <summary>
    /// Compute the inverse of this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::inverse() const
    {
        const Type det = determinant();

        if (det == Type(0))
            return *this;

        const Type invDet = Type(1) / det;

        Matrix3x3<Type> cofactorTransposed{
            m11*m22-m12*m21, m02*m21-m01*m22, m01*m12-m02*m11,
            m12*m20-m10*m22, m00*m22-m02*m20, m02*m10-m00*m12,
            m10*m21-m11*m20, m01*m20-m00*m21, m00*m11-m01*m10
        };

        return cofactorTransposed * invDet;
    }


    /// <summary>
    /// Invert this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::makeInverse()
    {
        *this = inverse();

        return *this;
    }


    /// <summary>
    /// Scalar * Matrix multiplication operator, for commutative
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <param name="matrix"></param>
    /// <returns></returns>
    template<typename MatrixType, typename ScalarType>
    Matrix3x3<MatrixType> operator*(ScalarType scalar, const Matrix3x3<MatrixType>& matrix)
    {
        return matrix * scalar;
    }


    /// Explicit template instantiation (precompiled declaration)
    template class Matrix3x3<float>;
    template class Matrix3x3<double>;

    template Matrix3x3<float>  operator*(float  scalar, const Matrix3x3<float>& v2);
    template Matrix3x3<double> operator*(double scalar, const Matrix3x3<double>& v2);

}} /// namespace ETL::Math
