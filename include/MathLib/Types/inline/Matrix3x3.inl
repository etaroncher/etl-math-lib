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
    inline Matrix3x3<Type> Matrix3x3<Type>::CreateScale(double sX, double sY)
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
    inline Matrix3x3<Type> Matrix3x3<Type>::CreateRotation(double angleRadians)
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
    inline Matrix3x3<Type> Matrix3x3<Type>::CreateTranslation(Type tX, Type tY)
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
    /// Matrix multiplication operator (Post multiply -> This * Other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    inline Matrix3x3<Type> Matrix3x3<Type>::operator*(const Matrix3x3& other) const
    {
        Matrix3x3<Type> result;
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
    inline Vector3<Type> Matrix3x3<Type>::operator*(const Vector3<Type>& vector) const
    {
        Vector3<Type> result;
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
    inline Matrix3x3<Type>& Matrix3x3<Type>::operator*=(const Matrix3x3& other)
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
    /// Computes matrix determinant
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Matrix3x3<Type>::determinant(bool bFixedPoint /*= false*/) const
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
    inline void Matrix3x3<Type>::determinantTo(Type& outResult, bool bFixedPoint /*= false*/) const
    {
        Determinant(outResult, *this, bFixedPoint);
    }


    /// <summary>
    /// Compute the inverse of this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type> Matrix3x3<Type>::inverse() const
    {
        Matrix3x3<Type> result;
        Inverse(result, *this);
        return result;
    }


    /// <summary>
    /// Compute the inverse of this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::inverseTo(Matrix3x3<Type>& outResult) const
    {
        Inverse(outResult, *this);
    }


    /// <summary>
    /// Invert this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::makeInverse()
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
    inline Matrix3x3<Type> Matrix3x3<Type>::transpose() const
    {
        Matrix3x3<Type> result;
        Transpose(result, *this);
        return result;
    }


    /// <summary>
    /// Compute the transpose
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::transposeTo(Matrix3x3<Type>& outResult) const
    {
        Transpose(outResult, *this);
    };


    /// <summary>
    /// Transpose this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::makeTranspose()
    {
        Transpose(*this, *this);

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
    inline Matrix3x3<Type>& Matrix3x3<Type>::scale(double sX, double sY)
    {
        Scale(*this, *this, Vector2<double>{sX, sY});
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
    inline Matrix3x3<Type>& Matrix3x3<Type>::scale(const Vector2<double>& scaleVec)
    {
        Scale(*this, *this, scaleVec);
        return *this;
    }


    /// <summary>
    /// 2D Transform - Rotate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="angleRad"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::rotate(double angleRad)
    {
        Rotate(*this, *this, angleRad);
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
    inline Matrix3x3<Type>& Matrix3x3<Type>::translate(Type tX, Type tY)
    {
        Translate(*this, *this, Vector2<Type>{tX, tY});
        return *this;
    }


    /// <summary>
    /// 2D Transform - Translate this matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="pos"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::translate(const Vector2<Type>& translation)
    {
        Translate(*this, *this, translation);
        return *this;
    }


    /// <summary>
    /// Set Scale, overwriting current scale values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newScaleX"></param>
    /// <param name="newScaleY"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::setScale(double newSX, double newSY)
    {
        SetScaling(*this, *this, Vector2<double>{newSX, newSY});
        return *this;
    }


    /// <summary>
    /// Set Scale, overwriting current scale values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newScaleY"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::setScale(const Vector2<double>& newScale)
    {
        SetScaling(*this, *this, newScale);
        return *this;
    }


    /// <summary>
    /// Set Rotation, overwriting current rotation values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newAngleRad"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::setRotation(double newAngleRad)
    {
        SetRotation(*this, *this, newAngleRad);
        return *this;
    }


    /// <summary>
    /// Set Translation, overwriting current translation values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newTX"></param>
    /// <param name="newTY"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::setTranslation(Type newTX, Type newTY)
    {
        SetTranslation(*this, *this, Vector2<Type>{newTX, newTY});
        return *this;
    }


    /// <summary>
    /// Set Translation, overwriting current translation values
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="newTranslation"></param>
    /// <returns></returns>
    template<typename Type>
    inline Matrix3x3<Type>& Matrix3x3<Type>::setTranslation(const Vector2<Type>& newTranslation)
    {
        SetTranslation(*this, *this, newTranslation);
        return *this;
    }


    /// <summary>
    /// 2D Transform decomposition - get scale
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<double> Matrix3x3<Type>::getScale() const
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
    inline double Matrix3x3<Type>::getRotation() const
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
    inline Vector2<Type> Matrix3x3<Type>::getTranslation() const
    {
        return Vector2<Type>{ DecodeValue<Type>(m02), DecodeValue<Type>(m12) };
    }


    /// <summary>
    /// 2D Transform decomposition - get scale
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outScale"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::getScaleTo(Vector2<double>& outScale) const
    {
        /// Extract scale from length of basis vectors (column 0 and column 1)
        outScale[0] = Vector2<double>{ DecodeValue<double>(m00), DecodeValue<double>(m10) }.length();
        outScale[1] = Vector2<double>{ DecodeValue<double>(m01), DecodeValue<double>(m11) }.length();
    }


    /// <summary>
    /// 2D Transform decomposition - get rotation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outAngleRad"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::getRotationTo(double& outAngleRad) const
    {
        /// Extract angle from column 0 (normalized)
        Vector2<double> firstCol{ DecodeValue<double>(m00), DecodeValue<double>(m10) };
        firstCol.makeNormalize();

        outAngleRad = std::atan2(firstCol.y(), firstCol.x());
    }


    /// <summary>
    /// 2D Transform decomposition - get translation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outTranslation"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::getTranslationTo(Vector2<Type>& outTranslation) const
    {
        outTranslation[0] = DecodeValue<Type>(m02);
        outTranslation[1] = DecodeValue<Type>(m12);
    }


    /// <summary>
    /// Column getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="colIndex"></param>
    /// <returns>Column as Vector3</returns>
    template<typename Type>
    inline Vector3<Type> Matrix3x3<Type>::getCol(int colIndex) const
    {
        ETLMATH_ASSERT(colIndex >= 0 && colIndex < COL_SIZE, "Matrix3x3 out of bounds COL access");

        return Vector3<Type>{ DecodeValue<Type>(m[colIndex][0]), DecodeValue<Type>(m[colIndex][1]), DecodeValue<Type>(m[colIndex][2]) };
    }


    /// <summary>
    /// Row getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="rowIndex"></param>
    /// <returns>Row as Vector3</returns>
    template<typename Type>
    inline Vector3<Type> Matrix3x3<Type>::getRow(int rowIndex) const
    {
        ETLMATH_ASSERT(rowIndex >= 0 && rowIndex < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        return Vector3<Type>{ DecodeValue<Type>(m[0][rowIndex]), DecodeValue<Type>(m[1][rowIndex]), DecodeValue<Type>(m[2][rowIndex]) };
    }


    /// <summary>
    /// Column getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outValue"></param>
    /// <param name="colIndex"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::getColTo(Vector3<Type>& outValue, int colIndex) const
    {
        ETLMATH_ASSERT(colIndex >= 0 && colIndex < COL_SIZE, "Matrix3x3 out of bounds COL access");

        outValue[0] = DecodeValue<Type>(m[colIndex][0]);
        outValue[1] = DecodeValue<Type>(m[colIndex][1]);
        outValue[2] = DecodeValue<Type>(m[colIndex][2]);
    }


    /// <summary>
    /// Row getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outValue"></param>
    /// <param name="rowIndex"></param>
    template<typename Type>
    inline void Matrix3x3<Type>::getRowTo(Vector3<Type>& outValue, int rowIndex) const
    {
        ETLMATH_ASSERT(rowIndex >= 0 && rowIndex < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        outValue[0] = DecodeValue<Type>(m[0][rowIndex]);
        outValue[1] = DecodeValue<Type>(m[1][rowIndex]);
        outValue[2] = DecodeValue<Type>(m[2][rowIndex]);
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


    /// <summary>
    /// Translate - Add a 'translation' translation to 'mat', store result in 'outResult'
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="translation"></param>
    template<typename Type>
    inline void Translate(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector2<Type>& translation)
    {
        outResult.setRawValue(0, 2, mat.getRawValue(0, 2) + EncodeValue<Type>(translation.x()));
        outResult.setRawValue(1, 2, mat.getRawValue(1, 2) + EncodeValue<Type>(translation.y()));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 0, mat.getRawValue(0, 0));
            outResult.setRawValue(1, 0, mat.getRawValue(1, 0));
            outResult.setRawValue(0, 1, mat.getRawValue(0, 1));
            outResult.setRawValue(1, 1, mat.getRawValue(1, 1));
            outResult.setRawValue(2, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 2, EncodeValue<Type>(Type(1)));
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
    inline void SetTranslation(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector2<Type>& translation)
    {
        outResult.setRawValue(0, 2, EncodeValue<Type>(translation.x()));
        outResult.setRawValue(1, 2, EncodeValue<Type>(translation.y()));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 0, mat.getRawValue(0, 0));
            outResult.setRawValue(1, 0, mat.getRawValue(1, 0));
            outResult.setRawValue(0, 1, mat.getRawValue(0, 1));
            outResult.setRawValue(1, 1, mat.getRawValue(1, 1));
            outResult.setRawValue(2, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 2, EncodeValue<Type>(Type(1)));
        }
    }


    /// <summary>
    /// Rotate - Add an 'angleRad' rotation to 'mat', store result in 'outResult'
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="angleRad"></param>
    template<typename Type>
    inline void Rotate(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, double angleRad)
    {
        /// Direct approach: rotate affects only the basis vectors
        /// Translation column (m[2][0], m[2][1]) is NOT scaled
        const Type xBasis[2]{ mat.getRawValue(0,0), mat.getRawValue(1,0) };  /// X-axis basis vector -> COL 0
        const Type yBasis[2]{ mat.getRawValue(0,1), mat.getRawValue(1,1) };  /// Y-axis basis vector -> COL 1

        const double c = std::cos(angleRad);
        const double s = std::sin(angleRad);

        outResult.setRawValue(0, 0, static_cast<Type>(xBasis[0] * c - xBasis[1] * s));  /// New X-basis x-component
        outResult.setRawValue(1, 0, static_cast<Type>(xBasis[0] * s + xBasis[1] * c));  /// New X-basis y-component
        outResult.setRawValue(0, 1, static_cast<Type>(yBasis[0] * c - yBasis[1] * s));  /// New Y-basis x-component
        outResult.setRawValue(1, 1, static_cast<Type>(yBasis[0] * s + yBasis[1] * c));  /// New Y-basis y-component

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 2, mat.getRawValue(0, 2));
            outResult.setRawValue(1, 2, mat.getRawValue(1, 2));
            outResult.setRawValue(2, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 2, EncodeValue<Type>(Type(1)));
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
    inline void SetRotation(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, double angleRad)
    {
        Vector2<double> scale;
        mat.getScaleTo(scale);

        const double c = std::cos(angleRad);
        const double s = std::sin(angleRad);

        outResult.setRawValue(0, 0, EncodeValue<Type>( c * scale.x()));
        outResult.setRawValue(1, 0, EncodeValue<Type>( s * scale.x()));
        outResult.setRawValue(0, 1, EncodeValue<Type>(-s * scale.y()));
        outResult.setRawValue(1, 1, EncodeValue<Type>( c * scale.y()));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 2, mat.getRawValue(0, 2));
            outResult.setRawValue(1, 2, mat.getRawValue(1, 2));
            outResult.setRawValue(2, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 2, EncodeValue<Type>(Type(1)));
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
    inline void Scale(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector2<double>& scale)
    {
        outResult.setRawValue(0, 0, static_cast<Type>(mat.getRawValue(0, 0) * scale.x()));
        outResult.setRawValue(1, 0, static_cast<Type>(mat.getRawValue(1, 0) * scale.x()));
        outResult.setRawValue(0, 1, static_cast<Type>(mat.getRawValue(0, 1) * scale.y()));
        outResult.setRawValue(1, 1, static_cast<Type>(mat.getRawValue(1, 1) * scale.y()));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 2, mat.getRawValue(0, 2));
            outResult.setRawValue(1, 2, mat.getRawValue(1, 2));
            outResult.setRawValue(2, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 2, EncodeValue<Type>(Type(1)));
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
    inline void SetScaling(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector2<double>& scale)
    {
        double rotation{ 0.0 };
        mat.getRotationTo(rotation);

        const double c = std::cos(rotation);
        const double s = std::sin(rotation);

        outResult.setRawValue(0, 0, EncodeValue<Type>( c * scale.x()));
        outResult.setRawValue(1, 0, EncodeValue<Type>( s * scale.x()));
        outResult.setRawValue(0, 1, EncodeValue<Type>(-s * scale.y()));
        outResult.setRawValue(1, 1, EncodeValue<Type>( c * scale.y()));

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 2, mat.getRawValue(0, 2));
            outResult.setRawValue(1, 2, mat.getRawValue(1, 2));
            outResult.setRawValue(2, 0, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 1, EncodeValue<Type>(Type(0)));
            outResult.setRawValue(2, 2, EncodeValue<Type>(Type(1)));
        }
    }


} /// namespace ETL::Math
