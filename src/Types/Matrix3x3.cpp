///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Matrix3x3.h"

namespace ETL::Math
{

    /// <summary>
    /// Matrix multiplication operator (Post multiply -> This * Other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns>Resulting matrix</returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::operator*(const Matrix3x3& other) const
    {
        if constexpr (std::integral<Type>)
        {
            Matrix3x3<Type> result;

            for (int row = 0; row < COL_SIZE; ++row)
            {
                for (int col = 0; col < COL_SIZE; ++col)
                {
                    const int64_t sum = static_cast<int64_t>(m[0][row]) * other.m[col][0]
                                      + static_cast<int64_t>(m[1][row]) * other.m[col][1]
                                      + static_cast<int64_t>(m[2][row]) * other.m[col][2];

                    /// Bitshift result back to Fixed Point
                    result.m[col][row] = static_cast<Type>(sum >> FIXED_SHIFT);
                }
            }

            return result;
        }
        else
        {
            return Matrix3x3<Type>{ Raw,
                                    m00*other.m00 + m01*other.m10 + m02*other.m20,   //m00
                                    m00*other.m01 + m01*other.m11 + m02*other.m21,   //m01
                                    m00*other.m02 + m01*other.m12 + m02*other.m22,   //m02
                                    m10*other.m00 + m11*other.m10 + m12*other.m20,   //m10
                                    m10*other.m01 + m11*other.m11 + m12*other.m21,   //m11
                                    m10*other.m02 + m11*other.m12 + m12*other.m22,   //m12
                                    m20*other.m00 + m21*other.m10 + m22*other.m20,   //m20
                                    m20*other.m01 + m21*other.m11 + m22*other.m21,   //m21
                                    m20*other.m02 + m21*other.m12 + m22*other.m22 }; //m22
        }
    }


    /// <summary>
    /// Vector multiplication operator (Post multiply -> This * Other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="vector"></param>
    /// <returns>Resulting vector</returns>
    template<typename Type>
    Vector3<Type> Matrix3x3<Type>::operator*(const Vector3<Type>& vector) const
    {
        if constexpr (std::integral<Type>)
        {
            /// Use 64-bit to prevent overflow
            /// vector getters return normal values, mXX is fixed-point ->
            /// Product is fixed-point -> sum (x, y, z) are fixed-point
            const int64_t x = static_cast<int64_t>(m00) * vector.x()
                            + static_cast<int64_t>(m01) * vector.y()
                            + static_cast<int64_t>(m02) * vector.z();
            const int64_t y = static_cast<int64_t>(m10) * vector.x()
                            + static_cast<int64_t>(m11) * vector.y()
                            + static_cast<int64_t>(m12) * vector.z();
            const int64_t z = static_cast<int64_t>(m20) * vector.x()
                            + static_cast<int64_t>(m21) * vector.y()
                            + static_cast<int64_t>(m22) * vector.z();

            return Vector3<Type>{ DecodeValue<Type>(x), DecodeValue<Type>(y), DecodeValue<Type>(z) };
        }
        else
        {
            return Vector3<Type>{ m00 * vector.x() + m01 * vector.y() + m02 * vector.z(),
                                  m10 * vector.x() + m11 * vector.y() + m12 * vector.z(),
                                  m20 * vector.x() + m21 * vector.y() + m22 * vector.z() };
        }
    }


    /// <summary>
    /// 2D Vector Transformations - Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="point"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Matrix3x3<Type>::transformPoint(const Vector2<Type>& point) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(point.x());
            const int64_t y = static_cast<int64_t>(point.y());
            const int64_t resX = x*m00 + y*m01 + m02;
            const int64_t resY = x*m10 + y*m11 + m12;

            return Vector2<Type>{ DecodeValue<Type>(resX), DecodeValue<Type>(resY) };
        }
        else
        {
            return Vector2<Type>{ m00*point.x() + m01*point.y() + m02, m10*point.x() + m11*point.y() + m12 };
        }
    }


    /// <summary>
    /// 2D Vector Transformations - Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="point"></param>
    template<typename Type>
    void Matrix3x3<Type>::transformPointInPlace(Vector2<Type>& point) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = point.x();
            const int64_t y = point.y();
            const int64_t resX = x*m00 + y*m01 + m02;
            const int64_t resY = x*m10 + y*m11 + m12;

            point[0] = DecodeValue<Type>(resX);
            point[1] = DecodeValue<Type>(resY);
        }
        else
        {
            Type x = point.x();
            Type y = point.y();
            point[0] = m00*x + m01*y + m02;
            point[1] = m10*x + m11*y + m12;
        }
    }


    /// <summary>
    /// 2D Vector Transformations - Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="point"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Matrix3x3<Type>::transformDirection(const Vector2<Type>& direction) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = direction.x();
            const int64_t y = direction.y();
            const int64_t resX = x*m00 + y*m01;
            const int64_t resY = x*m10 + y*m11;

            return Vector2<Type>{ DecodeValue<Type>(resX), DecodeValue<Type>(resY) };
        }
        else
        {
            return Vector2<Type>{ m00*direction.x() + m01*direction.y(), m10*direction.x() + m11*direction.y() };
        }
    }


    /// <summary>
    /// 2D Vector Transformations - Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="direction"></param>
    template<typename Type>
    void Matrix3x3<Type>::transformDirectionInPlace(Vector2<Type>& direction) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = direction.x();
            const int64_t y = direction.y();
            const int64_t resX = x*m00 + y*m01;
            const int64_t resY = x*m10 + y*m11;

            direction[0] = DecodeValue<Type>(resX);
            direction[1] = DecodeValue<Type>(resY);
        }
        else
        {
            Type x = direction.x();
            Type y = direction.y();
            direction[0] = m00*x + m01*y;
            direction[1] = m10*x + m11*y;
        }
    }


    /// <summary>
    /// Computes matrix determinant
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Matrix3x3<Type>::determinant(bool bFixedPoint /*= false*/) const
    {
        if constexpr (std::integral<Type>)
        {
            /// 1. Calculate the determinant components using 64-bit integers.
            /// Each term is scaled by FIXED_ONE, so the determinant ->
            /// (FIXED_ONE * FIXED_ONE * FIXED_ONE) = FIXED_ONE^3. -> is scaled thrice.
            const int64_t det_cubed = static_cast<int64_t>(m00) * m11 * m22
                                    + static_cast<int64_t>(m01) * m12 * m20
                                    + static_cast<int64_t>(m02) * m10 * m21
                                    - static_cast<int64_t>(m02) * m11 * m20
                                    - static_cast<int64_t>(m00) * m12 * m21
                                    - static_cast<int64_t>(m01) * m10 * m22;


            /// if bFixedPoint, return fixed-point determinant (de-scale twice),
            /// otherwise return raw value (de-scale thrice)
            const int det_shift = (bFixedPoint ? 2 : 3) * FIXED_SHIFT;

            return static_cast<Type>(det_cubed >> det_shift);
        }
        else
        {
            return m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m02*m11*m20 - m00*m12*m21 - m01*m10*m22;
        }
    }


    /// <summary>
    /// Compute the transpose
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> Matrix3x3<Type>::transpose() const
    {
        return Matrix3x3<Type>{ Raw, m00, m10, m20, m01, m11, m21, m02, m12, m22 };
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
        if constexpr (std::integral<Type>)
        {
            static constexpr bool bFixedPoint = true;
            const Type det = determinant(bFixedPoint);

            /// Use epsilon of 0.001 in fixed-point terms
            constexpr Type fixedEpsilon = EncodeValue<Type>(0.001);
            if (isZero(det, fixedEpsilon))
                return *this;

            /// Calculate Adjugate elements safely using 64-bit integers.
            /// This array of int64 is ESSENTIAL to prevent overflow (FX * FX = FX^2) due to double scale
            const int64_t adjugate_64[NUM_ELEM]{
                static_cast<int64_t>(m11) * m22 - static_cast<int64_t>(m12) * m21,
                static_cast<int64_t>(m02) * m21 - static_cast<int64_t>(m01) * m22,
                static_cast<int64_t>(m01) * m12 - static_cast<int64_t>(m02) * m11,
                static_cast<int64_t>(m12) * m20 - static_cast<int64_t>(m10) * m22,
                static_cast<int64_t>(m00) * m22 - static_cast<int64_t>(m02) * m20,
                static_cast<int64_t>(m02) * m10 - static_cast<int64_t>(m00) * m12,
                static_cast<int64_t>(m10) * m21 - static_cast<int64_t>(m11) * m20,
                static_cast<int64_t>(m01) * m20 - static_cast<int64_t>(m00) * m21,
                static_cast<int64_t>(m00) * m11 - static_cast<int64_t>(m01) * m10
            };

            /// Cast back to Type only after dividing by "det".
            /// Adj(FX^2) / Det(FX) = Result(FX) (result scaled only once, as expected)
            return Matrix3x3<Type>{ Raw,
                                    static_cast<Type>(adjugate_64[0] / det),
                                    static_cast<Type>(adjugate_64[1] / det),
                                    static_cast<Type>(adjugate_64[2] / det),
                                    static_cast<Type>(adjugate_64[3] / det),
                                    static_cast<Type>(adjugate_64[4] / det),
                                    static_cast<Type>(adjugate_64[5] / det),
                                    static_cast<Type>(adjugate_64[6] / det),
                                    static_cast<Type>(adjugate_64[7] / det),
                                    static_cast<Type>(adjugate_64[8] / det) };
        }
        else
        {
            const Type det = determinant(); /// Raw (float/double)

            if (isZero(det))
                return *this;

            const Matrix3x3<Type> adjugate{ Raw,
                m11*m22 - m12*m21, m02*m21 - m01*m22, m01*m12 - m02*m11,
                m12*m20 - m10*m22, m00*m22 - m02*m20, m02*m10 - m00*m12,
                m10*m21 - m11*m20, m01*m20 - m00*m21, m00*m11 - m01*m10
            };

            return adjugate / det;
        }
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


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)
 
    template class Matrix3x3<float>;
    template class Matrix3x3<double>;
    template class Matrix3x3<int>;

    template Matrix3x3<float>  operator*(float  scalar, const Matrix3x3<float>&  matrix);
    template Matrix3x3<double> operator*(double scalar, const Matrix3x3<double>& matrix);
    template Matrix3x3<int>    operator*(int    scalar, const Matrix3x3<int>&    matrix);

} /// namespace ETL::Math
