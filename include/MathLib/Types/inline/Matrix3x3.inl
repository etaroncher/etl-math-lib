///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.inl
///----------------------------------------------------------------------------

#include "MathLib/Common/Common.h"
#include "MathLib/Common/TypeComparisons.h"
#include <algorithm>

namespace ETL::Math
{

    /// <summary>
    /// Matrix diagonal constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="val"></param>
    template<typename Type>
    constexpr Matrix3x3<Type>::Matrix3x3(Type val)
        : mData{ ProcessValue<Type>(val), Type(0),                 Type(0),
                 Type(0),                 ProcessValue<Type>(val), Type(0),
                 Type(0),                 Type(0),                 ProcessValue<Type>(val) }
    {
    }


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    constexpr Matrix3x3<Type>::Matrix3x3(Type v00, Type v01, Type v02,
                                         Type v10, Type v11, Type v12,
                                         Type v20, Type v21, Type v22)
        : mData{ ProcessValue<Type>(v00), ProcessValue<Type>(v10), ProcessValue<Type>(v20),
                 ProcessValue<Type>(v01), ProcessValue<Type>(v11), ProcessValue<Type>(v21),
                 ProcessValue<Type>(v02), ProcessValue<Type>(v12), ProcessValue<Type>(v22) }
    {
    }


    /// <summary>
    /// Const application operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    Type Matrix3x3<Type>::operator()(int row, int col) const
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        return mData[col * COL_SIZE + row];
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
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        return mData[col * COL_SIZE + row];
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
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix3x3 out of bounds ELEM access");

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
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix3x3 out of bounds ELEM access");

        return mData[elem];
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
    /// Subtraction operator
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
    /// Scalar multiplication operator (Post multiply -> This * Scalar)
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
    /// Scalar division operator (This / scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::operator/(Type scalar) const
    {
        ETLMATH_ASSERT(!isZero(scalar), "Matrix3x3 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            return Matrix3x3<Type>{ m00 / scalar, m01 / scalar, m02 / scalar,
                                    m10 / scalar, m11 / scalar, m12 / scalar,
                                    m20 / scalar, m21 / scalar, m22 / scalar };
        }
        else
        {
            const Type inv = Type(1) / scalar;
            return Matrix3x3<Type>{ m00 * inv, m01 * inv, m02 * inv,
                                    m10 * inv, m11 * inv, m12 * inv,
                                    m20 * inv, m21 * inv, m22 * inv };
        }
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
        for (int i = 0; i < NUM_ELEM; ++i)
            mData[i] += other.mData[i];

        return *this;
    }


    /// <summary>
    /// Subtraction assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator-=(const Matrix3x3& other)
    {
        for (int i = 0; i < NUM_ELEM; ++i)
            mData[i] -= other.mData[i];

        return *this;
    }


    /// <summary>
    /// Scalar multiplication assignment operator (This *= scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator*=(Type scalar)
    {
        for (int i = 0; i < NUM_ELEM; ++i)
            mData[i] *= scalar;

        return *this;
    }


    /// <summary>
    /// Scalar division assignment operator (This /= scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::operator/=(Type scalar)
    {
        ETLMATH_ASSERT(!isZero(scalar), "Matrix3x3 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            for (int i = 0; i < NUM_ELEM; ++i)
                mData[i] /= scalar;
        }
        else
        {
            /// Compute inverse and multiply (avoids extra divisions)
            const Type inv = Type(1) / scalar;
            for (int i = 0; i < NUM_ELEM; ++i)
                mData[i] *= inv;
        }

        return *this;
    }


    /// <summary>
    /// Equality operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    bool Matrix3x3<Type>::operator==(const Matrix3x3<Type>& other) const
    {
        return std::equal(mData, mData + NUM_ELEM, other.mData);
    }


    /// <summary>
    /// Inequality operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    bool Matrix3x3<Type>::operator!=(const Matrix3x3<Type>& other) const
    {
        return !(*this == other);
    }


} /// namespace ETL::Math
