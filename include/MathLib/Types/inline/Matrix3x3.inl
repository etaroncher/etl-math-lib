///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.inl
///----------------------------------------------------------------------------

#include "MathLib/Common/Asserts.h"
#include "MathLib/Common/TypeComparisons.h"
#include <algorithm>
#include <cmath>

namespace ETL::Math
{

    /// <summary>
    /// 2D Transform Factory - Scale Matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="sX"></param>
    /// <param name="sY"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::Scale(double sX, double sY)
    {
        return Matrix3x3<Type>{ Raw,
            EncodeValue<Type>(sX), Type(0),               Type(0),
            Type(0),               EncodeValue<Type>(sY), Type(0),
            Type(0),               Type(0),               EncodeValue<Type>(Type(1))
        };
    }


    /// <summary>
    /// 2D Transform Factory -  Rotation Matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="angleRadians"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::Rotation(double angleRadians)
    {
        const Type cos = EncodeValue<Type>(std::cos(angleRadians));
        const Type sin = EncodeValue<Type>(std::sin(angleRadians));

        return Matrix3x3<Type>{ Raw,
            cos,    -sin,     Type(0),
            sin,     cos,     Type(0),
            Type(0), Type(0), EncodeValue<Type>(Type(1))
        };
    }


    /// <summary>
    /// 2D Transform Factory - Translation Matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="tX"></param>
    /// <param name="tY"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::Translation(Type tX, Type tY)
    {
        return Matrix3x3<Type>{ Raw,
            EncodeValue<Type>(Type(1)), Type(0),                    EncodeValue<Type>(tX),
            Type(0),                    EncodeValue<Type>(Type(1)), EncodeValue<Type>(tY),
            Type(0),                    Type(0),                    EncodeValue<Type>(Type(1))
        };
    }


    /// <summary>
    /// Matrix diagonal constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="val"></param>
    template<typename Type>
    constexpr Matrix3x3<Type>::Matrix3x3(Type val)
        : mData{ EncodeValue<Type>(val), Type(0),                Type(0),
                 Type(0),                EncodeValue<Type>(val), Type(0),
                 Type(0),                Type(0),                EncodeValue<Type>(val) }
    {
    }


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="v00"></param>
    /// <param name="v01"></param>
    /// <param name="v02"></param>
    /// <param name="v10"></param>
    /// <param name="v11"></param>
    /// <param name="v12"></param>
    /// <param name="v20"></param>
    /// <param name="v21"></param>
    /// <param name="v22"></param>
    template<typename Type>
    constexpr Matrix3x3<Type>::Matrix3x3(Type v00, Type v01, Type v02,
                                         Type v10, Type v11, Type v12,
                                         Type v20, Type v21, Type v22)
        : mData{ EncodeValue<Type>(v00), EncodeValue<Type>(v10), EncodeValue<Type>(v20),
                 EncodeValue<Type>(v01), EncodeValue<Type>(v11), EncodeValue<Type>(v21),
                 EncodeValue<Type>(v02), EncodeValue<Type>(v12), EncodeValue<Type>(v22) }
    {
    }


    /// <summary>
    /// Explicit Raw Constructor
    /// </summary>
    /// <param name=""></param>
    /// <param name="v00"></param>
    /// <param name="v01"></param>
    /// <param name="v02"></param>
    /// <param name="v10"></param>
    /// <param name="v11"></param>
    /// <param name="v12"></param>
    /// <param name="v20"></param>
    /// <param name="v21"></param>
    /// <param name="v22"></param>
    template<typename Type>
    constexpr Matrix3x3<Type>::Matrix3x3(RawTag, Type v00, Type v01, Type v02,
                                                 Type v10, Type v11, Type v12,
                                                 Type v20, Type v21, Type v22)
        : mData{ v00, v10, v20, v01, v11, v21, v02, v12, v22 }
    {
    }


    /// <summary>
    /// Const application operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    inline Type Matrix3x3<Type>::operator()(int row, int col) const
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        return DecodeValue<Type>(m[col][row]);
    }


    /// <summary>
    /// Application operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    inline ElementProxy<Type> Matrix3x3<Type>::operator()(int row, int col)
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        return ElementProxy<Type>{ m[col][row] };
    }


    /// <summary>
    /// Const subscription operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    inline Type Matrix3x3<Type>::operator[](int elem) const
    {
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix3x3 out of bounds ELEM access");

        return DecodeValue<Type>(mData[elem]);
    }


    /// <summary>
    /// Subscription operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    inline ElementProxy<Type> Matrix3x3<Type>::operator[](int elem)
    {
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix3x3 out of bounds ELEM access");

        return ElementProxy<Type>{ mData[elem] };
    }


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    inline Matrix3x3<Type> Matrix3x3<Type>::operator+(const Matrix3x3& other) const
    {
        return Matrix3x3<Type>{ Raw, m00 + other.m00, m01 + other.m01, m02 + other.m02,
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
    inline Matrix3x3<Type> Matrix3x3<Type>::operator-(const Matrix3x3& other) const
    {
        return Matrix3x3<Type>{ Raw, m00 - other.m00, m01 - other.m01, m02 - other.m02,
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
    inline Matrix3x3<Type> Matrix3x3<Type>::operator*(Type scalar) const
    {
        return Matrix3x3<Type>{ Raw, m00 * scalar, m01 * scalar, m02 * scalar,
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
    inline Matrix3x3<Type> Matrix3x3<Type>::operator/(Type scalar) const
    {
        ETLMATH_ASSERT(!isZero(scalar), "Matrix3x3 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            return Matrix3x3<Type>{ Raw, m00 / scalar, m01 / scalar, m02 / scalar,
                                         m10 / scalar, m11 / scalar, m12 / scalar,
                                         m20 / scalar, m21 / scalar, m22 / scalar };
        }
        else
        {
            const Type inv = Type(1) / scalar;
            return Matrix3x3<Type>{ Raw, m00 * inv, m01 * inv, m02 * inv,
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
    inline Matrix3x3<Type>& Matrix3x3<Type>::operator+=(const Matrix3x3& other)
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
    inline Matrix3x3<Type>& Matrix3x3<Type>::operator-=(const Matrix3x3& other)
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
    Matrix3x3<Type>& Matrix3x3<Type>::operator*=(const Matrix3x3& other)
    {
        *this = *this * other;

        return *this;
    }


    /// <summary>
    /// Scalar multiplication assignment operator (This *= scalar)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::operator*=(Type scalar)
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
    inline Matrix3x3<Type>& Matrix3x3<Type>::operator/=(Type scalar)
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
    inline bool Matrix3x3<Type>::operator==(const Matrix3x3<Type>& other) const
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
    inline bool Matrix3x3<Type>::operator!=(const Matrix3x3<Type>& other) const
    {
        return !(*this == other);
    }


    /// <summary>
    /// 2D Transform - Scale this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="sX"></param>
    /// <param name="sY"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::scale(double sX, double sY)
    {
        *this = (*this) * Matrix3x3<Type>::Scale(sX, sY);
        return *this;
    }


    /// <summary>
    /// 2D Transform - Scale this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="sX"></param>
    /// <param name="sY"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::scale(const Vector2<double>& scale)
    {
        *this = (*this) * Matrix3x3<Type>::Scale(scale.x(), scale.y());
        return *this;
    }


    /// <summary>
    /// 2D Transform - Rotate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="angleRad"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::rotate(double angleRad)
    {
        *this = (*this) * Matrix3x3<Type>::Rotation(angleRad);
        return *this;
    }


    /// <summary>
    /// 2D Transform - Translate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="tX"></param>
    /// <param name="tY"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::translate(Type tX, Type tY)
    {
        *this = (*this) * Matrix3x3<Type>::Translation(tX, tY);
        return *this;
    }


    /// <summary>
    /// 2D Transform - Translate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="pos"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type>& Matrix3x3<Type>::translate(const Vector2<Type>& pos)
    {
        *this = (*this) * Matrix3x3<Type>::Translation(pos.x(), pos.y());
        return *this;
    }


    /// <summary>
    /// 2D Transform decomposition - get scale
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Vector2<double> Matrix3x3<Type>::getScale() const
    {
        /// Extract scale from length of basis vectors (column 0 and column 1)
        const double sx = Vector2<double>{ DecodeValue<double>(m00), DecodeValue<double>(m10) }.length();
        const double sy = Vector2<double>{ DecodeValue<double>(m01), DecodeValue<double>(m11) }.length();

        return Vector2<double>{ sx, sy };
    }


    /// <summary>
    /// 2D Transform decomposition - get rotation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    double Matrix3x3<Type>::getRotation() const
    {
        /// Extract angle from column 0 (normalized)
        Vector2<double> firstCol{ DecodeValue<double>(m00), DecodeValue<double>(m10) };
        firstCol.makeNormalize();

        return std::atan2(firstCol.y(), firstCol.x());
    }


    /// <summary>
    /// 2D Transform decomposition - get translation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Matrix3x3<Type>::getTranslation() const
    {
        return Vector2<Type>{ DecodeValue<Type>(m02), DecodeValue<Type>(m12) };
    }


    /// <summary>
    /// 2D Transform decomposition - get scale
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scale"></param>
    template<typename Type>
    void Matrix3x3<Type>::getScale(Vector2<double>& scale) const
    {
        /// Extract scale from length of basis vectors (column 0 and column 1)
        scale[0] = Vector2<double>{ DecodeValue<double>(m00), DecodeValue<double>(m10) }.length();
        scale[1] = Vector2<double>{ DecodeValue<double>(m01), DecodeValue<double>(m11) }.length();
    }


    /// <summary>
    /// 2D Transform decomposition - get rotation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="angle"></param>
    template<typename Type>
    void Matrix3x3<Type>::getRotation(double& angle) const
    {
        /// Extract angle from column 0 (normalized)
        Vector2<double> firstCol{ DecodeValue<double>(m00), DecodeValue<double>(m10) };
        firstCol.makeNormalize();

        angle = std::atan2(firstCol.y(), firstCol.x());
    }


    /// <summary>
    /// 2D Transform decomposition - get translation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="pos"></param>
    template<typename Type>
    void Matrix3x3<Type>::getTranslation(Vector2<Type>& pos) const
    {
        pos[0] = DecodeValue<Type>(m02);
        pos[1] = DecodeValue<Type>(m12);
    }


    /// <summary>
    /// Column getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <returns>Column as Vector3</returns>
    template<typename Type>
    inline Vector3<Type> Matrix3x3<Type>::getCol(int col) const
    {
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        return Vector3<Type>{ DecodeValue<Type>(m[col][0]), DecodeValue<Type>(m[col][1]), DecodeValue<Type>(m[col][2]) };
    }


    /// <summary>
    /// Row getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <returns>Row as Vector3</returns>
    template<typename Type>
    inline Vector3<Type> Matrix3x3<Type>::getRow(int row) const
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        return Vector3<Type>{ DecodeValue<Type>(m[0][row]), DecodeValue<Type>(m[1][row]), DecodeValue<Type>(m[2][row]) };
    }


    /// <summary>
    /// Column getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <returns>Column as Vector3</returns>
    template<typename Type>
    inline void Matrix3x3<Type>::getCol(int col, Vector3<Type>& outValue) const
    {
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        outValue[0] = DecodeValue<Type>(m[col][0]);
        outValue[1] = DecodeValue<Type>(m[col][1]);
        outValue[2] = DecodeValue<Type>(m[col][2]);
    }


    /// <summary>
    /// Row getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <returns>Row as Vector3</returns>
    template<typename Type>
    inline void Matrix3x3<Type>::getRow(int row, Vector3<Type>& outValue) const
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        outValue[0] = DecodeValue<Type>(m[0][row]);
        outValue[1] = DecodeValue<Type>(m[1][row]);
        outValue[2] = DecodeValue<Type>(m[2][row]);
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
    inline void Matrix3x3<Type>::setCol(int col, Type c0, Type c1, Type c2)
    {
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        m[col][0] = EncodeValue<Type>(c0);
        m[col][1] = EncodeValue<Type>(c1);
        m[col][2] = EncodeValue<Type>(c2);
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
    inline void Matrix3x3<Type>::setRow(int row, Type r0, Type r1, Type r2)
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        m[0][row] = EncodeValue<Type>(r0);
        m[1][row] = EncodeValue<Type>(r1);
        m[2][row] = EncodeValue<Type>(r2);
    }


    /// <summary>
    /// Column setter by Vector3
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::setCol(int col, const Vector3<Type>& value)
    {
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        m[col][0] = EncodeValue<Type>(value.x());
        m[col][1] = EncodeValue<Type>(value.y());
        m[col][2] = EncodeValue<Type>(value.z());
    }


    /// <summary>
    /// Row setter by Vector3
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::setRow(int row, const Vector3<Type>& value)
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        m[0][row] = EncodeValue<Type>(value.x());
        m[1][row] = EncodeValue<Type>(value.y());
        m[2][row] = EncodeValue<Type>(value.z());
    }


    /// <summary>
    /// Raw access to matrix elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="col"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Matrix3x3<Type>::getRawValue(int row, int col) const
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        return m[col][row];
    }


    /// <summary>
    /// Raw access to matrix elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="elem"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Matrix3x3<Type>::getRawValue(int elem) const
    {
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix3x3 out of bounds ELEM access");

        return mData[elem];
    }


    /// <summary>
    /// Raw access to matrix elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <param name="col"></param>
    /// <returns></returns>
    template<typename Type>
    inline void Matrix3x3<Type>::setRawValue(int row, int col, Type value)
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        m[col][row] = value;
    }


    /// <summary>
    /// Raw access to matrix elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="elem"></param>
    /// <returns></returns>
    template<typename Type>
    inline void Matrix3x3<Type>::setRawValue(int elem, Type value)
    {
        ETLMATH_ASSERT(elem >= 0 && elem < NUM_ELEM, "Matrix3x3 out of bounds ELEM access");

        mData[elem] = value;
    }


    /// <summary>
    /// Scalar * Matrix multiplication operator, for commutative
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <param name="matrix"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type> operator*(Type scalar, const Matrix3x3<Type>& matrix)
    {
        return matrix * scalar;
    }


} /// namespace ETL::Math
