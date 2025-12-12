///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Matrix3x3.h"
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
        return Matrix3x3<Type>{
            ProcessValue<Type>(sX), Type(0),                Type(0),
            Type(0),                ProcessValue<Type>(sY), Type(0),
            Type(0),                Type(0),                ProcessValue<Type>(Type(1))
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
        const Type cos = ProcessValue<Type>(std::cos(angleRadians));
        const Type sin = ProcessValue<Type>(std::sin(angleRadians));

        return Matrix3x3<Type>{
            cos,    -sin,     Type(0),
            sin,     cos,     Type(0),
            Type(0), Type(0), ProcessValue<Type>(Type(1))
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
        return Matrix3x3<Type>{
            ProcessValue<Type>(Type(1)), Type(0),                     ProcessValue<Type>(tX),
            Type(0),                     ProcessValue<Type>(Type(1)), ProcessValue<Type>(tY),
            Type(0),                     Type(0),                     ProcessValue<Type>(Type(1))
        };
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
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        return Vector3<Type>{ mData[col * COL_SIZE + 0], mData[col * COL_SIZE + 1], mData[col * COL_SIZE + 2] };
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
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        return Vector3<Type>{ mData[0 * COL_SIZE + row], mData[1 * COL_SIZE + row], mData[2 * COL_SIZE + row] };
    }


    /// <summary>
    /// Column getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="col"></param>
    /// <returns>Column as Vector3</returns>
    template<typename Type>
    void Matrix3x3<Type>::getCol(int col, Vector3<Type>& outValue) const
    {
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        outValue[0] = mData[col * COL_SIZE + 0];
        outValue[1] = mData[col * COL_SIZE + 1];
        outValue[2] = mData[col * COL_SIZE + 2];
    }


    /// <summary>
    /// Row getter by index
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="row"></param>
    /// <returns>Row as Vector3</returns>
    template<typename Type>
    void Matrix3x3<Type>::getRow(int row, Vector3<Type>& outValue) const
    {
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        outValue[0] = mData[0 * COL_SIZE + row];
        outValue[1] = mData[1 * COL_SIZE + row];
        outValue[2] = mData[2 * COL_SIZE + row];
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
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        mData[col * COL_SIZE + 0] = c0;
        mData[col * COL_SIZE + 1] = c1;
        mData[col * COL_SIZE + 2] = c2;
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
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        mData[0 * COL_SIZE + row] = r0;
        mData[1 * COL_SIZE + row] = r1;
        mData[2 * COL_SIZE + row] = r2;
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
        ETLMATH_ASSERT(col >= 0 && col < COL_SIZE, "Matrix3x3 out of bounds COL access");

        mData[col * COL_SIZE + 0] = value.x();
        mData[col * COL_SIZE + 1] = value.y();
        mData[col * COL_SIZE + 2] = value.z();
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
        ETLMATH_ASSERT(row >= 0 && row < COL_SIZE, "Matrix3x3 out of bounds ROW access");

        mData[0 * COL_SIZE + row] = value.x();
        mData[1 * COL_SIZE + row] = value.y();
        mData[2 * COL_SIZE + row] = value.z();
    }

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
                    const int64_t sum = static_cast<int64_t>(mData[0*COL_SIZE + row]) * other.mData[col*COL_SIZE + 0]
                                      + static_cast<int64_t>(mData[1*COL_SIZE + row]) * other.mData[col*COL_SIZE + 1]
                                      + static_cast<int64_t>(mData[2*COL_SIZE + row]) * other.mData[col*COL_SIZE + 2];

                    /// Bitshift result back to Fixed Point
                    result[col*COL_SIZE + row] = static_cast<Type>(sum >> FIXED_SHIFT);
                }
            }

            return result;
        }
        else
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
        return Vector3<Type>{ m00 * vector.x() + m01 * vector.y() + m02 * vector.z(),
                              m10 * vector.x() + m11 * vector.y() + m12 * vector.z(),
                              m20 * vector.x() + m21 * vector.y() + m22 * vector.z() };
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
            const int64_t x = point.x();
            const int64_t y = point.y();
            const int64_t resX = (x*m00 + y*m01 + m02) >> FIXED_SHIFT;
            const int64_t resY = (x*m10 + y*m11 + m12) >> FIXED_SHIFT;

            return Vector2<Type>{ static_cast<Type>(resX), static_cast<Type>(resY) };
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
    void Matrix3x3<Type>::transformPoint(Vector2<Type>& point) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = point.x();
            const int64_t y = point.y();
            const int64_t resX = (x*m00 + y*m01 + m02) >> FIXED_SHIFT;
            const int64_t resY = (x*m10 + y*m11 + m12) >> FIXED_SHIFT;

            point[0] = static_cast<Type>(resX);
            point[1] = static_cast<Type>(resY);
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
            const int64_t resX = (x*m00 + y*m01) >> FIXED_SHIFT;
            const int64_t resY = (x*m10 + y*m11) >> FIXED_SHIFT;

            return Vector2<Type>{ static_cast<Type>(resX), static_cast<Type>(resY) };
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
    void Matrix3x3<Type>::transformDirection(Vector2<Type>& direction) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = direction.x();
            const int64_t y = direction.y();
            const int64_t resX = (x*m00 + y*m01) >> FIXED_SHIFT;
            const int64_t resY = (x*m10 + y*m11) >> FIXED_SHIFT;

            direction[0] = static_cast<Type>(resX);
            direction[1] = static_cast<Type>(resY);
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
    /// 2D Transform - Trnaslate this matrix
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
    /// 2D Transform decomposition - get scale
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Vector2<double> Matrix3x3<Type>::getScale() const
    {
        /// Extract scale from length of basis vectors (column 0 and column 1)
        if constexpr (std::integral<Type>)
        {
            /// Length is calculated using double, then convert back to the required Type.
            /// The components are SCALED so length will be SCALED and thus it should be descaled.
            const double sx_scaled = Vector2<double>(m00, m10).length();
            const double sy_scaled = Vector2<double>(m01, m11).length();

            return Vector2<double>{sx_scaled / FIXED_ONE, sy_scaled / FIXED_ONE};
        }
        else
        {
            return Vector2<double>{ Vector2<Type>(m00, m10).length(), Vector2<Type>(m01, m11).length() };
        }
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
        if constexpr (std::integral<Type>)
        {
            /// De-scale fixed-point components to get raw cos/sin values (as double).
            const double cos = static_cast<double>(m00) / FIXED_ONE;
            const double sin = static_cast<double>(m10) / FIXED_ONE;

            /// Normalize and compute angle.
            Vector2<double> firstCol{ cos,sin };
            firstCol.makeNormalize();

            return std::atan2(firstCol.y(), firstCol.x());
        }
        else
        {
            Vector2<Type> firstCol(m00, m10);
            firstCol.makeNormalize();
            return std::atan2(firstCol.y(), firstCol.x());
        }
    }


    /// <summary>
    /// 2D Transform decomposition - get translation
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Matrix3x3<Type>::getTranslation() const
    {
        /// Extract translation from column 2 (normalized)
        if constexpr (std::integral<Type>)
        {
            return Vector2<Type>{ m02 >> FIXED_SHIFT, m12 >> FIXED_SHIFT };
        }
        else
        {
            return Vector2<Type>{ m02, m02 };
        }
    }


    /// <summary>
    /// Computes matrix determinant
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Matrix3x3<Type>::determinant() const
    {
        if constexpr (std::integral<Type>)
        {
            /// 1. Calculate the determinant components using 64-bit integers.
            /// Each term is scaled by (FIXED_ONE * FIXED_ONE * FIXED_ONE) = FIXED_ONE^3.
            const int64_t det_cubed = static_cast<int64_t>(m00) * m11 * m22
                                    + static_cast<int64_t>(m01) * m12 * m20
                                    + static_cast<int64_t>(m02) * m10 * m21
                                    - static_cast<int64_t>(m02) * m11 * m20
                                    - static_cast<int64_t>(m00) * m12 * m21
                                    - static_cast<int64_t>(m01) * m10 * m22;

            /// 2. De-scale the result by FIXED_ONE^2 (2 * FIXED_SHIFT = 32 bits) 
            /// to return a determinant scaled by FIXED_ONE.
            static constexpr int DET_SHIFT = 2 * FIXED_SHIFT;

            /// This value is the fixed-point determinant, ready for fixed-point division.
            return static_cast<Type>(det_cubed >> DET_SHIFT);
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
        const Type det = determinant(); /// Correctly scaled (FixedPoint) or raw (float/double)

        if (isZero(det))
            return *this;

        if constexpr (std::integral<Type>)
        {
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
            return Matrix3x3<Type>{ static_cast<Type>(adjugate_64[0] / det),
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
            const Matrix3x3<Type> adjugate{
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


    /// <summary>
    /// Scalar * Matrix multiplication operator, for commutative
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <param name="matrix"></param>
    /// <returns></returns>
    template<typename Type>
    Matrix3x3<Type> operator*(Type scalar, const Matrix3x3<Type>& matrix)
    {
        return matrix * scalar;
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
