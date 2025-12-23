///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix4x4.inl
///----------------------------------------------------------------------------

#include "MathLib/Common/Asserts.h"
#include "MathLib/Common/Constants.h"
#include "MathLib/Common/TypeComparisons.h"
#include <algorithm>
#include <cmath>

namespace ETL::Math
{

    /// <summary>
    /// 3D Transform Factory - Scale Matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="sX"></param>
    /// <param name="sY"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::CreateScale(double sX, double sY, double sZ)
    {
        return Matrix4x4<Type>{ Raw,
            EncodeValue<Type>(sX), Type(0),               Type(0),               Type(0),
            Type(0),               EncodeValue<Type>(sY), Type(0),               Type(0),
            Type(0),               Type(0),               EncodeValue<Type>(sZ), Type(0),
            Type(0),               Type(0),               Type(0),               EncodeValue<Type>(Type(1)),
        };
    }


    /// <summary>
    /// 3D Transform Factory -  Rotation Matrix
    /// Combined rotation matrix using ZYX Euler order
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="angleRadians"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::CreateRotation(double rX, double rY, double rZ)
    {
        const double cosX = std::cos(rX);
        const double sinX = std::sin(rX);
        const double cosY = std::cos(rY);
        const double sinY = std::sin(rY);
        const double cosZ = std::cos(rZ);
        const double sinZ = std::sin(rZ);

        return Matrix4x4<Type>{ Raw,
            EncodeValue<Type>(cosY * cosZ),
            EncodeValue<Type>(-cosY * sinZ),
            EncodeValue<Type>(sinY),
            Type(0),
            EncodeValue<Type>(sinX * sinY * cosZ + cosX * sinZ),
            EncodeValue<Type>(-sinX * sinY * sinZ + cosX * cosZ),
            EncodeValue<Type>(-sinX * cosY),
            Type(0),
            EncodeValue<Type>(-cosX * sinY * cosZ + sinX * sinZ),
            EncodeValue<Type>(cosX * sinY * sinZ + sinX * cosZ),
            EncodeValue<Type>(cosX * cosY),
            Type(0),
            Type(0), Type(0), Type(0), EncodeValue<Type>(Type(1))
        };
    }


    /// <summary>
    /// 3D Transform Factory - Translation Matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="tX"></param>
    /// <param name="tY"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::CreateTranslation(Type tX, Type tY, Type tZ)
    {
        return Matrix4x4<Type>{ Raw,
            EncodeValue<Type>(Type(1)), Type(0),                    Type(0),                    EncodeValue<Type>(tX),
            Type(0),                    EncodeValue<Type>(Type(1)), Type(0),                    EncodeValue<Type>(tY),
            Type(0),                    Type(0),                    EncodeValue<Type>(Type(1)), EncodeValue<Type>(tZ),
            Type(0),                    Type(0),                    Type(0),                    EncodeValue<Type>(Type(1)),
        };
    }


    /// <summary>
    /// Matrix diagonal constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="val"></param>
    template<typename Type>
    constexpr Matrix4x4<Type>::Matrix4x4(Type val)
        : mData{ EncodeValue<Type>(val), Type(0),                Type(0),                Type(0),
                 Type(0),                EncodeValue<Type>(val), Type(0),                Type(0),
                 Type(0),                Type(0),                EncodeValue<Type>(val), Type(0),
                 Type(0),                Type(0),                Type(0),                EncodeValue<Type>(val) }
    {
    }


    /// <summary>
    /// Matrix diagonal constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="val"></param>
    template<typename Type>
    constexpr Matrix4x4<Type>::Matrix4x4(Type v00, Type v11, Type v22, Type v33)
        :mData{ EncodeValue<Type>(v00), Type(0),                Type(0),                Type(0),
                Type(0),                EncodeValue<Type>(v11), Type(0),                Type(0),
                Type(0),                Type(0),                EncodeValue<Type>(v22), Type(0),
                Type(0),                Type(0),                Type(0),                EncodeValue<Type>(v33) }
    {
    }


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="v00"></param>
    /// <param name="v01"></param>
    /// <param name="v02"></param>
    /// <param name="v03"></param>
    /// <param name="v10"></param>
    /// <param name="v11"></param>
    /// <param name="v12"></param>
    /// <param name="v13"></param>
    /// <param name="v20"></param>
    /// <param name="v21"></param>
    /// <param name="v22"></param>
    /// <param name="v23"></param>
    /// <param name="v30"></param>
    /// <param name="v31"></param>
    /// <param name="v32"></param>
    /// <param name="v33"></param>
    template<typename Type>
    constexpr Matrix4x4<Type>::Matrix4x4(Type v00, Type v01, Type v02, Type v03,
                                         Type v10, Type v11, Type v12, Type v13,
                                         Type v20, Type v21, Type v22, Type v23,
                                         Type v30, Type v31, Type v32, Type v33 )
        : mData{ EncodeValue<Type>(v00), EncodeValue<Type>(v10), EncodeValue<Type>(v20), EncodeValue<Type>(v30),
                 EncodeValue<Type>(v01), EncodeValue<Type>(v11), EncodeValue<Type>(v21), EncodeValue<Type>(v31),
                 EncodeValue<Type>(v02), EncodeValue<Type>(v12), EncodeValue<Type>(v22), EncodeValue<Type>(v32),
                 EncodeValue<Type>(v03), EncodeValue<Type>(v13), EncodeValue<Type>(v23), EncodeValue<Type>(v33) }
    {
    }

    /// <summary>
    /// Explicit constructor from double
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="v00"></param>
    /// <param name="v01"></param>
    /// <param name="v02"></param>
    /// <param name="v03"></param>
    /// <param name="v10"></param>
    /// <param name="v11"></param>
    /// <param name="v12"></param>
    /// <param name="v13"></param>
    /// <param name="v20"></param>
    /// <param name="v21"></param>
    /// <param name="v22"></param>
    /// <param name="v23"></param>
    /// <param name="v30"></param>
    /// <param name="v31"></param>
    /// <param name="v32"></param>
    /// <param name="v33"></param>
    template<typename Type>
    constexpr Matrix4x4<Type>::Matrix4x4(double v00, double v01, double v02, double v03,
                                         double v10, double v11, double v12, double v13,
                                         double v20, double v21, double v22, double v23,
                                         double v30, double v31, double v32, double v33) requires (!std::same_as<Type, double>)
        : mData{ EncodeValue<Type>(v00), EncodeValue<Type>(v10), EncodeValue<Type>(v20), EncodeValue<Type>(v30),
                 EncodeValue<Type>(v01), EncodeValue<Type>(v11), EncodeValue<Type>(v21), EncodeValue<Type>(v31),
                 EncodeValue<Type>(v02), EncodeValue<Type>(v12), EncodeValue<Type>(v22), EncodeValue<Type>(v32),
                 EncodeValue<Type>(v03), EncodeValue<Type>(v13), EncodeValue<Type>(v23), EncodeValue<Type>(v33) }
    {
    }

    /// <summary>
    /// Explicit Raw Constructor
    /// </summary>
    /// <param name=""></param>
    /// <param name="v00"></param>
    /// <param name="v01"></param>
    /// <param name="v02"></param>
    /// <param name="v03"></param>
    /// <param name="v10"></param>
    /// <param name="v11"></param>
    /// <param name="v12"></param>
    /// <param name="v13"></param>
    /// <param name="v20"></param>
    /// <param name="v21"></param>
    /// <param name="v22"></param>
    /// <param name="v23"></param>
    /// <param name="v30"></param>
    /// <param name="v31"></param>
    /// <param name="v32"></param>
    /// <param name="v33"></param>
    template<typename Type>
    constexpr Matrix4x4<Type>::Matrix4x4(RawTag, Type v00, Type v01, Type v02, Type v03,
                                                 Type v10, Type v11, Type v12, Type v13,
                                                 Type v20, Type v21, Type v22, Type v23,
                                                 Type v30, Type v31, Type v32, Type v33 )
        : mData{ v00, v10, v20, v30, v01, v11, v21, v31, v02, v12, v22, v32, v03, v13, v23, v33 }
    {
    }


    /// <summary>
    /// Const application operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    inline Type Matrix4x4<Type>::operator()(int row, int col) const
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix4x4 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix4x4 out of bounds COL access");

        return DecodeValue<Type>(m[col][row]);
    }


    /// <summary>
    /// Application operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    inline ElementProxy<Type> Matrix4x4<Type>::operator()(int row, int col)
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix4x4 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix4x4 out of bounds COL access");

        return ElementProxy<Type>{ m[col][row] };
    }


    /// <summary>
    /// Const subscription operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    inline Type Matrix4x4<Type>::operator[](int elem) const
    {
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix4x4 out of bounds ELEM access");

        return DecodeValue<Type>(mData[elem]);
    }


    /// <summary>
    /// Subscription operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    inline ElementProxy<Type> Matrix4x4<Type>::operator[](int elem)
    {
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix4x4 out of bounds ELEM access");

        return ElementProxy<Type>{ mData[elem] };
    }


    /// <summary>
    /// Column getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="colIndex"></param>
    /// <returns>Column as Vector4</returns>
    template<typename Type>
    inline Vector4<Type> Matrix4x4<Type>::getCol(int colIndex) const
    {
        Vector4<Type> result;
        GetCol(result, *this, colIndex);
        return result;
    }


    /// <summary>
    /// Row getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="rowIndex"></param>
    /// <returns>Row as Vector4</returns>
    template<typename Type>
    inline Vector4<Type> Matrix4x4<Type>::getRow(int rowIndex) const
    {
        Vector4<Type> result;
        GetRow(result, *this, rowIndex);
        return result;
    }


    /// <summary>
    /// Column getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outValue"></param>
    /// <param name="colIndex"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::getColTo(Vector4<Type>& outValue, int colIndex) const
    {
        GetCol(outValue, *this, colIndex);
    }


    /// <summary>
    /// Row getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outValue"></param>
    /// <param name="rowIndex"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::getRowTo(Vector4<Type>& outValue, int rowIndex) const
    {
        GetRow(outValue, *this, rowIndex);
    }


    /// <summary>
    /// Column setter by element
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <param name="c0"></param>
    /// <param name="c1"></param>
    /// <param name="c2"></param>
    /// <param name="c3"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::setCol(int col, Type c0, Type c1, Type c2, Type c3)
    {
        SetCol(*this, *this, col, Vector4<Type>{c0, c1, c2, c3});
    }


    /// <summary>
    /// Row setter by element
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="r0"></param>
    /// <param name="r1"></param>
    /// <param name="r2"></param>
    /// <param name="r3"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::setRow(int row, Type r0, Type r1, Type r2, Type r3)
    {
        SetRow(*this, *this, row, Vector4<Type>{r0, r1, r2, r3});
    }


    /// <summary>
    /// Column setter by Vector4
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::setCol(int col, const Vector4<Type>& value)
    {
        SetCol(*this, *this, col, value);
    }


    /// <summary>
    /// Row setter by Vector4
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::setRow(int row, const Vector4<Type>& value)
    {
        SetRow(*this, *this, row, value);
    }


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::operator+(const Matrix4x4& other) const
    {
        return Matrix4x4<Type>{ Raw, m00 + other.m00, m01 + other.m01, m02 + other.m02, m03 + other.m03,
                                     m10 + other.m10, m11 + other.m11, m12 + other.m12, m13 + other.m13,
                                     m20 + other.m20, m21 + other.m21, m22 + other.m22, m23 + other.m23,
                                     m30 + other.m30, m31 + other.m31, m32 + other.m32, m33 + other.m33 };
    }


    /// <summary>
    /// Subtraction operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::operator-(const Matrix4x4& other) const
    {
        return Matrix4x4<Type>{ Raw, m00 - other.m00, m01 - other.m01, m02 - other.m02, m03 - other.m03,
                                     m10 - other.m10, m11 - other.m11, m12 - other.m12, m13 - other.m13,
                                     m20 - other.m20, m21 - other.m21, m22 - other.m22, m23 - other.m23,
                                     m30 - other.m30, m31 - other.m31, m32 - other.m32, m33 - other.m33 };
    }


    /// <summary>
    /// Matrix multiplication operator (Post multiply -> This * Other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::operator*(const Matrix4x4& other) const
    {
        Matrix4x4<Type> result;
        Multiply(result, *this, other);
        return result;
    }


    /// <summary>
    /// Vector multiplication operator (Post multiply -> This * Other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="vector"></param>
    /// <returns>Resulting vector</returns>
    template<typename Type>
    inline Vector4<Type> Matrix4x4<Type>::operator*(const Vector4<Type>& vector) const
    {
        Vector4<Type> result;
        Multiply(result, *this, vector);
        return result;
    }


    /// <summary>
    /// Scalar multiplication operator (Post multiply -> This * Scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::operator*(Type scalar) const
    {
        return Matrix4x4<Type>{ Raw, m00 * scalar, m01 * scalar, m02 * scalar, m03 * scalar,
                                     m10 * scalar, m11 * scalar, m12 * scalar, m13 * scalar,
                                     m20 * scalar, m21 * scalar, m22 * scalar, m23 * scalar,
                                     m30 * scalar, m31 * scalar, m32 * scalar, m33 * scalar };
    }


    /// <summary>
    /// Scalar division operator (This / scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::operator/(Type scalar) const
    {
        ETLMATH_ASSERT(!isZeroRaw(scalar), "Matrix4x4 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            return Matrix4x4<Type>{ Raw, m00 / scalar, m01 / scalar, m02 / scalar, m03 / scalar,
                                         m10 / scalar, m11 / scalar, m12 / scalar, m13 / scalar,
                                         m20 / scalar, m21 / scalar, m22 / scalar, m23 / scalar,
                                         m30 / scalar, m31 / scalar, m32 / scalar, m33 / scalar };
        }
        else
        {
            const Type inv = Type(1) / scalar;
            return Matrix4x4<Type>{ Raw, m00 * inv, m01 * inv, m02 * inv, m03 * inv,
                                         m10 * inv, m11 * inv, m12 * inv, m13 * inv,
                                         m20 * inv, m21 * inv, m22 * inv, m23 * inv,
                                         m30 * inv, m31 * inv, m32 * inv, m33 * inv };
        }
    }


    /// <summary>
    /// Addition assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::operator+=(const Matrix4x4& other)
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
    inline Matrix4x4<Type>& Matrix4x4<Type>::operator-=(const Matrix4x4& other)
    {
        for (int i = 0; i < NUM_ELEM; ++i)
            mData[i] -= other.mData[i];

        return *this;
    }


    /// <summary>
    /// Matrix multiplication operator (This *= Other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::operator*=(const Matrix4x4& other)
    {
        Multiply(*this, *this, other);

        return *this;
    }


    /// <summary>
    /// Scalar multiplication assignment operator (This *= scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::operator*=(Type scalar)
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
    inline Matrix4x4<Type>& Matrix4x4<Type>::operator/=(Type scalar)
    {
        ETLMATH_ASSERT(!isZeroRaw(scalar), "Matrix4x4 division by 0");

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
    inline bool Matrix4x4<Type>::operator==(const Matrix4x4<Type>& other) const
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
    inline bool Matrix4x4<Type>::operator!=(const Matrix4x4<Type>& other) const
    {
        return !(*this == other);
    }


    /// <summary>
    /// 3D Transformations - Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="point"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Matrix4x4<Type>::transformPoint(const Vector3<Type>& point) const
    {
        Vector3<Type> result;
        TransformPoint(result, *this, point);
        return result;
    }


    /// <summary>
    /// 3D Transformations - Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="point"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::transformPointTo(Vector3<Type>& outResult, const Vector3<Type>& point) const
    {
        TransformPoint(outResult, *this, point);
    }


    /// <summary>
    /// 3D Transformations - Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="inOutPoint"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::transformPointInPlace(Vector3<Type>& inOutPoint) const
    {
        TransformPoint(inOutPoint, *this, inOutPoint);
    }


    /// <summary>
    /// 3D Transformations - Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="point"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Matrix4x4<Type>::transformDirection(const Vector3<Type>& direction) const
    {
        Vector3<Type> result;
        TransformDirection(result, *this, direction);
        return result;
    }


    /// <summary>
    /// 3D Transformations - Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="direction"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::transformDirectionTo(Vector3<Type>& outResult, const Vector3<Type>& direction) const
    {
        TransformDirection(outResult, *this, direction);
    }


    /// <summary>
    /// 3D Transformations - Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="direction"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::transformDirectionInPlace(Vector3<Type>& inOutDirection) const
    {
        TransformDirection(inOutDirection, *this, inOutDirection);
    }


    /// <summary>
    /// 3D Transform - Scale this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="sX"></param>
    /// <param name="sY"></param>
    /// <param name="sZ"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::scale(double sX, double sY, double sZ)
    {
        Scale(*this, *this, Vector3<double>{sX, sY, sZ});
        return *this;
    }


    /// <summary>
    /// 3D Transform - Scale this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scaleVec"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::scale(const Vector3<double>& scaleVec)
    {
        Scale(*this, *this, scaleVec);
        return *this;
    }


    /// <summary>
    /// 3D Transform - Rotate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="rX"></param>
    /// <param name="rY"></param>
    /// <param name="rZ"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::rotate(double rX, double rY, double rZ)
    {
        Rotate(*this, *this, Vector3<double>{rX, rY, rZ});
        return *this;
    }


    /// <summary>
    /// 3D Transform - Rotate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="rotateVec"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::rotate(const Vector3<double>& rotation)
    {
        Rotate(*this, *this, rotation);
        return *this;
    }


    /// <summary>
    /// 3D Transform - Translate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="tX"></param>
    /// <param name="tY"></param>
    /// <param name="tZ"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::translate(Type tX, Type tY, Type tZ)
    {
        Translate(*this, *this, Vector3<Type>{tX, tY, tZ});
        return *this;
    }


    /// <summary>
    /// 3D Transform - Translate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="translation"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::translate(const Vector3<Type>& translation)
    {
        Translate(*this, *this, translation);
        return *this;
    }


    /// <summary>
    /// Set Scale, overwriting current scale values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newSX"></param>
    /// <param name="newSY"></param>
    /// <param name="newSZ"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::setScale(double newSX, double newSY, double newSZ)
    {
        SetScaling(*this, *this, Vector3<double>{newSX, newSY, newSZ});
        return *this;
    }


    /// <summary>
    /// Set Scale, overwriting current scale values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newScale"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::setScale(const Vector3<double>& newScale)
    {
        SetScaling(*this, *this, newScale);
        return *this;
    }


    /// <summary>
    /// Set Rotation, overwriting current rotation values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newRX"></param>
    /// <param name="newRY"></param>
    /// <param name="newRZ"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::setRotation(double newRX, double newRY, double newRZ)
    {
        SetRotation(*this, *this, Vector3<double>{newRX, newRY, newRZ});
        return *this;
    }


    /// <summary>
    /// Set Rotation, overwriting current rotation values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newRotation"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::setRotation(const Vector3<double>& newRotation)
    {
        SetRotation(*this, *this, newRotation);
        return *this;
    }


    /// <summary>
    /// Set Translation, overwriting current translation values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newTX"></param>
    /// <param name="newTY"></param>
    /// <param name="newTZ"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::setTranslation(Type newTX, Type newTY, Type newTZ)
    {
        SetTranslation(*this, *this, Vector3<Type>{newTX, newTY, newTZ});
        return *this;
    }


    /// <summary>
    /// Set Translation, overwriting current translation values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newTranslation"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::setTranslation(const Vector3<Type>& newTranslation)
    {
        SetTranslation(*this, *this, newTranslation);
        return *this;
    }


    /// <summary>
    /// 3D Transform decomposition - get scale
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<double> Matrix4x4<Type>::getScale() const
    {
        Vector3<double> result;
        GetScaling(result, *this);
        return result;
    }


    /// <summary>
    /// 3D Transform decomposition - get rotation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<double> Matrix4x4<Type>::getRotation() const
    {
        Vector3<double> result;
        GetRotation(result, *this);
        return result;
    }


    /// <summary>
    /// 3D Transform decomposition - get translation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Matrix4x4<Type>::getTranslation() const
    {
        Vector3<Type> result;
        GetTranslation(result, *this);
        return result;
    }


    /// <summary>
    /// 3D Transform decomposition - get scale
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outScale"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::getScaleTo(Vector3<double>& outScale) const
    {
        GetScaling(outScale, *this);
    }


    /// <summary>
    /// 3D Transform decomposition - get rotation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outRotation"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::getRotationTo(Vector3<double>& outRotation) const
    {
        GetRotation(outRotation, *this);
    }


    /// <summary>
    /// 3D Transform decomposition - get translation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outTranslation"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::getTranslationTo(Vector3<Type>& outTranslation) const
    {
        GetTranslation(outTranslation, *this);
    }


    /// <summary>
    /// Computes matrix determinant
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Matrix4x4<Type>::determinant(bool bFixedPoint /*= false*/) const
    {
        Type result;
        Determinant(result, *this, bFixedPoint);
        return result;
    }


    /// <summary>
    /// Computes matrix determinant
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="bFixedPoint"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::determinantTo(Type& outResult, bool bFixedPoint /*= false*/) const
    {
        Determinant(outResult, *this, bFixedPoint);
    }


    /// <summary>
    /// Compute the inverse of this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::inverse() const
    {
        Matrix4x4<Type> result;
        Inverse(result, *this);
        return result;
    }


    /// <summary>
    /// Compute the inverse of this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::inverseTo(Matrix4x4<Type>& outResult) const
    {
        Inverse(outResult, *this);
    }


    /// <summary>
    /// Invert this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::makeInverse()
    {
        Inverse(*this, *this);
        return *this;
    }


    /// <summary>
    /// Compute the transpose
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type> Matrix4x4<Type>::transpose() const
    {
        Matrix4x4<Type> result;
        Transpose(result, *this);
        return result;
    }


    /// <summary>
    /// Compute the transpose
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::transposeTo(Matrix4x4<Type>& outResult) const
    {
        Transpose(outResult, *this);
    };


    /// <summary>
    /// Transpose this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type>& Matrix4x4<Type>::makeTranspose()
    {
        Transpose(*this, *this);
        return *this;
    }


    /// <summary>
    /// Raw access to matrix elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="col"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Matrix4x4<Type>::getRawValue(int row, int col) const
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix4x4 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix4x4 out of bounds COL access");
        return m[col][row];
    }


    /// <summary>
    /// Raw access to matrix elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="elem"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Matrix4x4<Type>::getRawValue(int elem) const
    {
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix4x4 out of bounds ELEM access");
        return mData[elem];
    }


    /// <summary>
    /// Raw access to matrix elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="col"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::setRawValue(int row, int col, Type value)
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix4x4 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix4x4 out of bounds COL access");
        m[col][row] = value;
    }


    /// <summary>
    /// Raw access to matrix elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="elem"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Matrix4x4<Type>::setRawValue(int elem, Type value)
    {
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix4x4 out of bounds ELEM access");
        mData[elem] = value;
    }


    ///------------------------------------------------------------------------------------------
    /// Free functions - implement logic

    /// <summary>
    /// Column getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="index"></param>
    template<typename Type>
    inline void GetCol(Vector4<Type>& outResult, const Matrix4x4<Type>& mat, int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < Matrix4x4<Type>::COL_SIZE, "Matrix4x4 out of bounds ROW access");

        outResult.setRawValue(0, mat.getRawValue(0, index));
        outResult.setRawValue(1, mat.getRawValue(1, index));
        outResult.setRawValue(2, mat.getRawValue(2, index));
        outResult.setRawValue(3, mat.getRawValue(3, index));
    }


    /// <summary>
    /// Row getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="index"></param>
    template<typename Type>
    inline void GetRow(Vector4<Type>& outResult, const Matrix4x4<Type>& mat, int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < Matrix4x4<Type>::COL_SIZE, "Matrix4x4 out of bounds ROW access");

        outResult.setRawValue(0, mat.getRawValue(index, 0));
        outResult.setRawValue(1, mat.getRawValue(index, 1));
        outResult.setRawValue(2, mat.getRawValue(index, 2));
        outResult.setRawValue(3, mat.getRawValue(index, 3));
    }


    /// <summary>
    /// Column setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="index"></param>
    /// <param name="col"></param>
    template<typename Type>
    inline void SetCol(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, int index, const Vector4<Type>& col)
    {
        ETLMATH_ASSERT(index >= 0 && index < Matrix4x4<Type>::COL_SIZE, "Matrix4x4 out of bounds ROW access");

        if (&outResult != &mat)
        {
            outResult = mat;
        }

        outResult.setRawValue(0, index, col.getRawValue(0));
        outResult.setRawValue(1, index, col.getRawValue(1));
        outResult.setRawValue(2, index, col.getRawValue(2));
        outResult.setRawValue(3, index, col.getRawValue(3));
    }


    /// <summary>
    /// Row setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="index"></param>
    /// <param name="row"></param>
    template<typename Type>
    inline void SetRow(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, int index, const Vector4<Type>& row)
    {
        ETLMATH_ASSERT(index >= 0 && index < Matrix4x4<Type>::COL_SIZE, "Matrix4x4 out of bounds ROW access");

        if (&outResult != &mat)
        {
            outResult = mat;
        }

        outResult.setRawValue(index, 0, row.getRawValue(0));
        outResult.setRawValue(index, 1, row.getRawValue(1));
        outResult.setRawValue(index, 2, row.getRawValue(2));
        outResult.setRawValue(index, 3, row.getRawValue(3));
    }


    /// <summary>
    /// Transform Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="point"></param>
    template<typename Type>
    inline void TransformPoint(Vector3<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<Type>& point)
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(point.getRawValue(0));
            const int64_t y = static_cast<int64_t>(point.getRawValue(1));
            const int64_t z = static_cast<int64_t>(point.getRawValue(2));
            const int64_t outX = ((mat.getRawValue(0, 0) * x + mat.getRawValue(0, 1) * y + mat.getRawValue(0, 2) * z) >> FIXED_SHIFT) + mat.getRawValue(0, 3);
            const int64_t outY = ((mat.getRawValue(1, 0) * x + mat.getRawValue(1, 1) * y + mat.getRawValue(1, 2) * z) >> FIXED_SHIFT) + mat.getRawValue(1, 3);
            const int64_t outZ = ((mat.getRawValue(2, 0) * x + mat.getRawValue(2, 1) * y + mat.getRawValue(2, 2) * z) >> FIXED_SHIFT) + mat.getRawValue(2, 3);
            outResult.setRawValue(0, static_cast<Type>(outX));
            outResult.setRawValue(1, static_cast<Type>(outY));
            outResult.setRawValue(2, static_cast<Type>(outZ));
        }
        else
        {
            const Type x = point.getRawValue(0);
            const Type y = point.getRawValue(1);
            const Type z = point.getRawValue(2);
            outResult.setRawValue(0, mat.getRawValue(0, 0) * x + mat.getRawValue(0, 1) * y + mat.getRawValue(0, 2) * z + mat.getRawValue(0, 3));
            outResult.setRawValue(1, mat.getRawValue(1, 0) * x + mat.getRawValue(1, 1) * y + mat.getRawValue(1, 2) * z + mat.getRawValue(1, 3));
            outResult.setRawValue(2, mat.getRawValue(2, 0) * x + mat.getRawValue(2, 1) * y + mat.getRawValue(2, 2) * z + mat.getRawValue(2, 3));
        }
    }


    /// <summary>
    /// Transform Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="direction"></param>
    template<typename Type>
    inline void TransformDirection(Vector3<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<Type>& direction)
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(direction.getRawValue(0));
            const int64_t y = static_cast<int64_t>(direction.getRawValue(1));
            const int64_t z = static_cast<int64_t>(direction.getRawValue(2));
            const int64_t outX = (mat.getRawValue(0, 0) * x + mat.getRawValue(0, 1) * y + mat.getRawValue(0, 2) * z) >> FIXED_SHIFT;
            const int64_t outY = (mat.getRawValue(1, 0) * x + mat.getRawValue(1, 1) * y + mat.getRawValue(1, 2) * z) >> FIXED_SHIFT;
            const int64_t outZ = (mat.getRawValue(2, 0) * x + mat.getRawValue(2, 1) * y + mat.getRawValue(2, 2) * z) >> FIXED_SHIFT;
            outResult.setRawValue(0, static_cast<Type>(outX));
            outResult.setRawValue(1, static_cast<Type>(outY));
            outResult.setRawValue(2, static_cast<Type>(outZ));
        }
        else
        {
            const Type x = direction.getRawValue(0);
            const Type y = direction.getRawValue(1);
            const Type z = direction.getRawValue(2);
            outResult.setRawValue(0, mat.getRawValue(0, 0) * x + mat.getRawValue(0, 1) * y + mat.getRawValue(0, 2) * z);
            outResult.setRawValue(1, mat.getRawValue(1, 0) * x + mat.getRawValue(1, 1) * y + mat.getRawValue(1, 2) * z);
            outResult.setRawValue(2, mat.getRawValue(2, 0) * x + mat.getRawValue(2, 1) * y + mat.getRawValue(2, 2) * z);
        }
    }


    /// <summary>
    /// Translate - Add a 'translation' translation to 'mat', store result in 'outResult'
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="translation"></param>
    template<typename Type>
    inline void Translate(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<Type>& translation)
    {
        outResult.setRawValue(0, 3, mat.getRawValue(0, 3) + translation.getRawValue(0));
        outResult.setRawValue(1, 3, mat.getRawValue(1, 3) + translation.getRawValue(1));
        outResult.setRawValue(2, 3, mat.getRawValue(2, 3) + translation.getRawValue(2));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 0, mat.getRawValue(0, 0));
            outResult.setRawValue(1, 0, mat.getRawValue(1, 0));
            outResult.setRawValue(2, 0, mat.getRawValue(2, 0));
            outResult.setRawValue(0, 1, mat.getRawValue(0, 1));
            outResult.setRawValue(1, 1, mat.getRawValue(1, 1));
            outResult.setRawValue(2, 1, mat.getRawValue(2, 1));
            outResult.setRawValue(0, 2, mat.getRawValue(0, 2));
            outResult.setRawValue(1, 2, mat.getRawValue(1, 2));
            outResult.setRawValue(2, 2, mat.getRawValue(2, 2));
            outResult.setRawValue(3, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 2, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 3, EncodeValue<Type>(Type(1)));
        }
    }


    /// <summary>
    /// SetTranslation - Overwrite current translation in 'mat' with 'translation', store result in 'outResult'
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="translation"></param>
    template<typename Type>
    inline void SetTranslation(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<Type>& translation)
    {
        outResult.setRawValue(0, 3, translation.getRawValue(0));
        outResult.setRawValue(1, 3, translation.getRawValue(1));
        outResult.setRawValue(2, 3, translation.getRawValue(2));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 0, mat.getRawValue(0, 0));
            outResult.setRawValue(1, 0, mat.getRawValue(1, 0));
            outResult.setRawValue(2, 0, mat.getRawValue(2, 0));
            outResult.setRawValue(0, 1, mat.getRawValue(0, 1));
            outResult.setRawValue(1, 1, mat.getRawValue(1, 1));
            outResult.setRawValue(2, 1, mat.getRawValue(2, 1));
            outResult.setRawValue(0, 2, mat.getRawValue(0, 2));
            outResult.setRawValue(1, 2, mat.getRawValue(1, 2));
            outResult.setRawValue(2, 2, mat.getRawValue(2, 2));
            outResult.setRawValue(3, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 2, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 3, EncodeValue<Type>(Type(1)));
        }
    }


    /// <summary>
    /// Retrieve translation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    inline void GetTranslation(Vector3<Type>& outResult, const Matrix4x4<Type>& mat)
    {
        outResult.setRawValue(0, mat.getRawValue(0, 3));
        outResult.setRawValue(1, mat.getRawValue(1, 3));
        outResult.setRawValue(2, mat.getRawValue(2, 3));
    }


    /// <summary>
    /// Rotate - Add an 'angleRad' rotation to 'mat', store result in 'outResult'
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="angleRad"></param>
    template<typename Type>
    inline void Rotate(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<double>& rotation)
    {
        /// Create rotation matrix
        const Matrix4x4<Type> rotMat = Matrix4x4<Type>::CreateRotation(rotation.x(), rotation.y(), rotation.z());

        /// Extract the 3 basis vectors (columns 0, 1, 2) - they contain scale + rotation
        const Vector4<Type> basisX = mat.getCol(0);
        const Vector4<Type> basisY = mat.getCol(1);
        const Vector4<Type> basisZ = mat.getCol(2);

        /// Rotate each basis vector (transformDirection uses only the 3x3 rotation part, ignoring translation)
        const Vector4<Type> newBasisX = rotMat * basisX;
        const Vector4<Type> newBasisY = rotMat * basisY;
        const Vector4<Type> newBasisZ = rotMat * basisZ;

        /// Dump results into matrix
        outResult.setCol(0, newBasisX);
        outResult.setCol(1, newBasisY);
        outResult.setCol(2, newBasisZ);

        if (&outResult != &mat)
        {
            outResult.setCol(3, mat.getCol(3));
        }
    }


    /// <summary>
    /// SetRotation - Overwrite current rotation in 'mat' with 'angleRad' rotation, store result in 'outResult'
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="angleRad"></param>
    template<typename Type>
    inline void SetRotation(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<double>& rotation)
    {
        const double cosX = std::cos(rotation.x());
        const double sinX = std::sin(rotation.x());
        const double cosY = std::cos(rotation.y());
        const double sinY = std::sin(rotation.y());
        const double cosZ = std::cos(rotation.z());
        const double sinZ = std::sin(rotation.z());

        const double v00 = cosY * cosZ;
        const double v01 = -cosY * sinZ;
        const double v02 = sinY;
        const double v10 = sinX * sinY * cosZ + cosX * sinZ;
        const double v11 = -sinX * sinY * sinZ + cosX * cosZ;
        const double v12 = -sinX * cosY;
        const double v20 = -cosX * sinY * cosZ + sinX * sinZ;
        const double v21 = cosX * sinY * sinZ + sinX * cosZ;
        const double v22 = cosX * cosY;

        Vector3<double> scale;
        GetScaling(scale, mat);

        outResult.setRawValue(0, 0, EncodeValue<Type>(v00 * scale.x()));
        outResult.setRawValue(1, 0, EncodeValue<Type>(v10 * scale.x()));
        outResult.setRawValue(2, 0, EncodeValue<Type>(v20 * scale.x()));
        outResult.setRawValue(0, 1, EncodeValue<Type>(v01 * scale.y()));
        outResult.setRawValue(1, 1, EncodeValue<Type>(v11 * scale.y()));
        outResult.setRawValue(2, 1, EncodeValue<Type>(v21 * scale.y()));
        outResult.setRawValue(0, 2, EncodeValue<Type>(v02 * scale.z()));
        outResult.setRawValue(1, 2, EncodeValue<Type>(v12 * scale.z()));
        outResult.setRawValue(2, 2, EncodeValue<Type>(v22 * scale.z()));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 3, mat.getRawValue(0, 3));
            outResult.setRawValue(1, 3, mat.getRawValue(1, 3));
            outResult.setRawValue(2, 3, mat.getRawValue(2, 3));
            outResult.setRawValue(3, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 2, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 3, EncodeValue<Type>(Type(1)));
        }
    }


    /// <summary>
    /// Retrieve rotation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    inline void GetRotation(Vector3<double>& outResult, const Matrix4x4<Type>& mat)
    {
        Vector3<double> scale;
        GetScaling(scale, mat);

        if (isZero(scale.x()) || isZero(scale.y()) || isZero(scale.z()))
        {
            outResult = Vector3<double>::Zero();
            return;
        }

        /// Normalized basis vectors
        double r00 = DecodeValue<double>(mat.getRawValue(0, 0)) / scale.x();
        double r10 = DecodeValue<double>(mat.getRawValue(1, 0)) / scale.x();
        double r20 = DecodeValue<double>(mat.getRawValue(2, 0)) / scale.x();
        double r01 = DecodeValue<double>(mat.getRawValue(0, 1)) / scale.y();
        double r11 = DecodeValue<double>(mat.getRawValue(1, 1)) / scale.y();
        double r21 = DecodeValue<double>(mat.getRawValue(2, 1)) / scale.y();
        double r02 = DecodeValue<double>(mat.getRawValue(0, 2)) / scale.z();
        double r12 = DecodeValue<double>(mat.getRawValue(1, 2)) / scale.z();
        double r22 = DecodeValue<double>(mat.getRawValue(2, 2)) / scale.z();

        /// Extract Euler angles (ZYX order)
        /// Check for gimbal lock
        const double threshold = 0.99999;

        if (r02 < threshold)
        {
            if (r02 > -threshold)
            {
                /// Normal case
                outResult.setRawValue(1, std::asin(r02));
                outResult.setRawValue(0, std::atan2(-r12, r22));
                outResult.setRawValue(2, std::atan2(-r01, r00));
            }
            else
            {
                /// Gimbal lock: r02 = -1 (pitch = -90 degrees)
                outResult.setRawValue(1, -PI / 2.0);
                outResult.setRawValue(0, -std::atan2(r10, r11));
                outResult.setRawValue(2, 0.0);
            }
        }
        else
        {
            /// Gimbal lock: r02 = 1 (pitch = 90 degrees)
            outResult.setRawValue(1, PI / 2.0);
            outResult.setRawValue(0, std::atan2(r10, r11));
            outResult.setRawValue(2, 0.0);
        }
    }


    /// <summary>
    /// Scale - Add a 'scale' scaling to 'mat', store result in 'outResult'
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="scale"></param>
    template<typename Type>
    inline void Scale(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<double>& scale)
    {
        outResult.setRawValue(0, 0, static_cast<Type>(mat.getRawValue(0, 0) * scale.x()));
        outResult.setRawValue(1, 0, static_cast<Type>(mat.getRawValue(1, 0) * scale.x()));
        outResult.setRawValue(2, 0, static_cast<Type>(mat.getRawValue(2, 0) * scale.x()));
        outResult.setRawValue(0, 1, static_cast<Type>(mat.getRawValue(0, 1) * scale.y()));
        outResult.setRawValue(1, 1, static_cast<Type>(mat.getRawValue(1, 1) * scale.y()));
        outResult.setRawValue(2, 1, static_cast<Type>(mat.getRawValue(2, 1) * scale.y()));
        outResult.setRawValue(0, 2, static_cast<Type>(mat.getRawValue(0, 2) * scale.z()));
        outResult.setRawValue(1, 2, static_cast<Type>(mat.getRawValue(1, 2) * scale.z()));
        outResult.setRawValue(2, 2, static_cast<Type>(mat.getRawValue(2, 2) * scale.z()));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 3, mat.getRawValue(0, 3));
            outResult.setRawValue(1, 3, mat.getRawValue(1, 3));
            outResult.setRawValue(2, 3, mat.getRawValue(2, 3));
            outResult.setRawValue(3, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 2, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 3, EncodeValue<Type>(Type(1)));
        }
    }


    /// <summary>
    /// SetScaling - Overwrite current scaling in 'mat' with 'scale', store result in 'outResult'
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="scale"></param>
    template<typename Type>
    inline void SetScaling(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<double>& scale)
    {
        Vector3<double> currentScale;
        GetScaling(currentScale, mat);

        for (int col = 0; col < 3; ++col)
        {
            if (!isZero(currentScale.getRawValue(col)))
            {
                const double scaleFactor = scale.getRawValue(col) / currentScale.getRawValue(col);
                outResult.setRawValue(0, col, static_cast<Type>(mat.getRawValue(0, col) * scaleFactor));
                outResult.setRawValue(1, col, static_cast<Type>(mat.getRawValue(1, col) * scaleFactor));
                outResult.setRawValue(2, col, static_cast<Type>(mat.getRawValue(2, col) * scaleFactor));
            }
        }

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 3, mat.getRawValue(0, 3));
            outResult.setRawValue(1, 3, mat.getRawValue(1, 3));
            outResult.setRawValue(2, 3, mat.getRawValue(2, 3));
            outResult.setRawValue(3, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 2, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(3, 3, EncodeValue<Type>(Type(1)));
        }
    }


    /// <summary>
    /// Retrieve scale
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    inline void GetScaling(Vector3<double>& outResult, const Matrix4x4<Type>& mat)
    {
        /// Extract scale from length of basis vectors (column0, column1 and column2)
        const double xBasis_x = DecodeValue<double>(mat.getRawValue(0, 0));
        const double xBasis_y = DecodeValue<double>(mat.getRawValue(1, 0));
        const double xBasis_z = DecodeValue<double>(mat.getRawValue(2, 0));
        const double yBasis_x = DecodeValue<double>(mat.getRawValue(0, 1));
        const double yBasis_y = DecodeValue<double>(mat.getRawValue(1, 1));
        const double yBasis_z = DecodeValue<double>(mat.getRawValue(2, 1));
        const double zBasis_x = DecodeValue<double>(mat.getRawValue(0, 2));
        const double zBasis_y = DecodeValue<double>(mat.getRawValue(1, 2));
        const double zBasis_z = DecodeValue<double>(mat.getRawValue(2, 2));

        const double lengthX = Vector3<double>{ xBasis_x, xBasis_y, xBasis_z }.length();
        const double lengthY = Vector3<double>{ yBasis_x, yBasis_y, yBasis_z }.length();
        const double lengthZ = Vector3<double>{ zBasis_x, zBasis_y, zBasis_z }.length();

        /// Detect reflection by checking if determinant is negative
        /// Using cross product: (X × Y) · Z
        /// If negative, we have an odd number of negative scales
        const double crossX = DecodeValue<double>(mat.getRawValue(1,0)) * DecodeValue<double>(mat.getRawValue(2,1)) -
                              DecodeValue<double>(mat.getRawValue(2,0)) * DecodeValue<double>(mat.getRawValue(1,1));
        const double crossY = DecodeValue<double>(mat.getRawValue(2,0)) * DecodeValue<double>(mat.getRawValue(0,1)) -
                              DecodeValue<double>(mat.getRawValue(0,0)) * DecodeValue<double>(mat.getRawValue(2,1));
        const double crossZ = DecodeValue<double>(mat.getRawValue(0,0)) * DecodeValue<double>(mat.getRawValue(1,1)) -
                              DecodeValue<double>(mat.getRawValue(1,0)) * DecodeValue<double>(mat.getRawValue(0,1));

        const double dotProduct = crossX * DecodeValue<double>(mat.getRawValue(0, 2)) +
                                  crossY * DecodeValue<double>(mat.getRawValue(1, 2)) +
                                  crossZ * DecodeValue<double>(mat.getRawValue(2, 2));

        outResult.setRawValue(0, lengthX);
        outResult.setRawValue(1, lengthY);
        outResult.setRawValue(2, (dotProduct < 0.0) ? -lengthZ : lengthZ); /// Negate Z if reflected
    }


    /// <summary>
    /// Scalar * Matrix multiplication operator, for commutative
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <param name="matrix"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix4x4<Type> operator*(Type scalar, const Matrix4x4<Type>& matrix)
    {
        return matrix * scalar;
    }


} /// namespace ETL::Math
