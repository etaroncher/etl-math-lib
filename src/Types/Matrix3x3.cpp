///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Matrix3x3.h"

namespace ETL::Math
{

    /// <summary>
    /// 2D Transformations - Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="point"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Matrix3x3<Type>::transformPoint(const Vector2<Type>& point) const
    {
        Vector2<Type> result;
        transformPointTo(result, point);
        return result;
    }


    /// <summary>
    /// 2D Transformations - Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="point"></param>
    template<typename Type>
    void Matrix3x3<Type>::transformPointTo(Vector2<Type>& outResult, const Vector2<Type>& point) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(point.x());
            const int64_t y = static_cast<int64_t>(point.y());
            const int64_t resX = x * m00 + y * m01 + m02;
            const int64_t resY = x * m10 + y * m11 + m12;

            outResult[0] = DecodeValue<Type>(resX);
            outResult[1] = DecodeValue<Type>(resY);
        }
        else
        {
            outResult[0] = m00 * point.x() + m01 * point.y() + m02;
            outResult[1] = m10 * point.x() + m11 * point.y() + m12;
        }
    }


    /// <summary>
    /// 2D Transformations - Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="point"></param>
    template<typename Type>
    void Matrix3x3<Type>::transformPointInPlace(Vector2<Type>& point) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(point.x());
            const int64_t y = static_cast<int64_t>(point.y());
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
    /// 2D Transformations - Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="point"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Matrix3x3<Type>::transformDirection(const Vector2<Type>& direction) const
    {
        Vector2<Type> result;
        transformDirectionTo(result, direction);
        return result;
    }


    /// <summary>
    /// 2D Transformations - Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="direction"></param>
    template<typename Type>
    void Matrix3x3<Type>::transformDirectionTo(Vector2<Type>& outResult, const Vector2<Type>& direction) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(direction.x());
            const int64_t y = static_cast<int64_t>(direction.y());
            const int64_t resX = x * m00 + y * m01;
            const int64_t resY = x * m10 + y * m11;

            outResult[0] = DecodeValue<Type>(resX);
            outResult[1] = DecodeValue<Type>(resY);
        }
        else
        {
            outResult[0] = m00 * direction.x() + m01 * direction.y();
            outResult[1] = m10 * direction.x() + m11 * direction.y();
        }
    }


    /// <summary>
    /// 2D Transformations - Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="direction"></param>
    template<typename Type>
    void Matrix3x3<Type>::transformDirectionInPlace(Vector2<Type>& direction) const
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(direction.x());
            const int64_t y = static_cast<int64_t>(direction.y());
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


    ///------------------------------------------------------------------------------------------
    /// Free functions and common helpers (also present as class member functions.

    /// <summary>
    /// Matrix * Vector
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="vec"></param>
    template<typename Type>
    void MultiplyTo(Vector3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector3<Type>& vec)
    {
        /// --- SAFETY CHECK FOR ALIASING ---
        /// If outResult is the same object as vec, we must use a temporary buffer.
        if (&outResult == &vec)
        {
            Vector3<Type> temp;
            MultiplyTo(temp, mat, vec);

            outResult = temp;
            return;
        }

        if constexpr (std::integral<Type>)
        {
            /// Use 64-bit to prevent overflow
            /// vector getters return normal values, mXX is fixed-point ->
            /// Product is fixed-point -> sum (x, y, z) are fixed-point
            const int64_t x = static_cast<int64_t>(mat.getRawValue(0,0)) * vec[0]
                            + static_cast<int64_t>(mat.getRawValue(0,1)) * vec[1]
                            + static_cast<int64_t>(mat.getRawValue(0,2)) * vec[2];
            const int64_t y = static_cast<int64_t>(mat.getRawValue(1,0)) * vec[0]
                            + static_cast<int64_t>(mat.getRawValue(1,1)) * vec[1]
                            + static_cast<int64_t>(mat.getRawValue(1,2)) * vec[2];
            const int64_t z = static_cast<int64_t>(mat.getRawValue(2,0)) * vec[0]
                            + static_cast<int64_t>(mat.getRawValue(2,1)) * vec[1]
                            + static_cast<int64_t>(mat.getRawValue(2,2)) * vec[2];

            outResult[0] = DecodeValue<Type>(x);
            outResult[1] = DecodeValue<Type>(y);
            outResult[2] = DecodeValue<Type>(z);
        }
        else
        {
            outResult[0] = mat(0,0) * vec[0] + mat(0,1) * vec[1] + mat(0,2) * vec[2];
            outResult[1] = mat(1,0) * vec[0] + mat(1,1) * vec[1] + mat(1,2) * vec[2];
            outResult[2] = mat(2,0) * vec[0] + mat(2,1) * vec[1] + mat(2,2) * vec[2];
        }
    }

    /// <summary>
    /// Matrix * Matrix
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mA"></param>
    /// <param name="mB"></param>
    template<typename Type>
    void MultiplyTo(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mA, const Matrix3x3<Type>& mB)
    {
        /// --- SAFETY CHECK FOR ALIASING ---
        /// If outResult is the same object as mA OR mB, we must use a temporary buffer.
        if (&outResult == &mA || &outResult == &mB)
        {
            Matrix3x3<Type> temp;
            MultiplyTo(temp, mA, mB);

            outResult = temp;
            return;
        }

        for (int col = 0; col < Matrix3x3<Type>::COL_SIZE; ++col)
        {
            for (int row = 0; row < Matrix3x3<Type>::COL_SIZE; ++row)
            {
                if constexpr (std::integral<Type>)
                {
                    const int64_t sum = static_cast<int64_t>(mA.getRawValue(row, 0)) * mB.getRawValue(0, col)
                                      + static_cast<int64_t>(mA.getRawValue(row, 1)) * mB.getRawValue(1, col)
                                      + static_cast<int64_t>(mA.getRawValue(row, 2)) * mB.getRawValue(2, col);

                    /// Bitshift result back to Fixed Point
                    outResult.setRawValue(row, col, static_cast<Type>(sum >> FIXED_SHIFT));
                }
                else
                {
                    outResult(row, col) = mA(row,0) * mB(0,col) + mA(row,1) * mB(1,col) + mA(row,2) * mB(2,col);
                }
            }
        }
    }


    /// <summary>
    /// Compute Determinant
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    void DeterminantTo(Type& outResult, const Matrix3x3<Type>& mat, bool bFixedPoint /*= false*/)
    {
        if constexpr (std::integral<Type>)
        {
            /// 1. Calculate the determinant components using 64-bit integers.
            /// Each term is scaled by FIXED_ONE, so the determinant ->
            /// (FIXED_ONE * FIXED_ONE * FIXED_ONE) = FIXED_ONE^3. -> is scaled thrice.
            const int64_t det_cubed = static_cast<int64_t>(mat.getRawValue(0,0)) * mat.getRawValue(1,1) * mat.getRawValue(2,2)
                                    + static_cast<int64_t>(mat.getRawValue(0,1)) * mat.getRawValue(1,2) * mat.getRawValue(2,0)
                                    + static_cast<int64_t>(mat.getRawValue(0,2)) * mat.getRawValue(1,0) * mat.getRawValue(2,1)
                                    - static_cast<int64_t>(mat.getRawValue(0,2)) * mat.getRawValue(1,1) * mat.getRawValue(2,0)
                                    - static_cast<int64_t>(mat.getRawValue(0,0)) * mat.getRawValue(1,2) * mat.getRawValue(2,1)
                                    - static_cast<int64_t>(mat.getRawValue(0,1)) * mat.getRawValue(1,0) * mat.getRawValue(2,2);


            /// if bFixedPoint, return fixed-point determinant (de-scale twice),
            /// otherwise return raw value (de-scale thrice)
            const int det_shift = (bFixedPoint ? 2 : 3) * FIXED_SHIFT;

            outResult = static_cast<Type>(det_cubed >> det_shift);
        }
        else
        {
            outResult = mat(0,0) * mat(1,1) * mat(2,2) 
                      + mat(0,1) * mat(1,2) * mat(2,0)
                      + mat(0,2) * mat(1,0) * mat(2,1)
                      - mat(0,2) * mat(1,1) * mat(2,0)
                      - mat(0,0) * mat(1,2) * mat(2,1)
                      - mat(0,1) * mat(1,0) * mat(2,2);
        }
    }


    /// <summary>
    /// Compute Inverse
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    void InverseTo(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat)
    {
        if constexpr (std::integral<Type>)
        {
            static constexpr bool bFixedPoint = true;
            Type det{ Type(0) };
            DeterminantTo(det, mat, bFixedPoint);

            /// Use epsilon of 0.001 in fixed-point terms
            constexpr Type fixedEpsilon = EncodeValue<Type>(0.001);
            if (isZero(det, fixedEpsilon))
            {
                outResult = Matrix3x3<Type>::Zero();
                return;
            }

            /// Calculate Adjugate elements safely using 64-bit integers.
            /// This array of int64 is ESSENTIAL to prevent overflow (FX * FX = FX^2) due to double scale
            const int64_t adjugate_64[Matrix3x3<Type>::NUM_ELEM]{
                static_cast<int64_t>(mat.getRawValue(1,1)) * mat.getRawValue(2,2) - static_cast<int64_t>(mat.getRawValue(1,2)) * mat.getRawValue(2,1),
                static_cast<int64_t>(mat.getRawValue(0,2)) * mat.getRawValue(2,1) - static_cast<int64_t>(mat.getRawValue(0,1)) * mat.getRawValue(2,2),
                static_cast<int64_t>(mat.getRawValue(0,1)) * mat.getRawValue(1,2) - static_cast<int64_t>(mat.getRawValue(0,2)) * mat.getRawValue(1,1),
                static_cast<int64_t>(mat.getRawValue(1,2)) * mat.getRawValue(2,0) - static_cast<int64_t>(mat.getRawValue(1,0)) * mat.getRawValue(2,2),
                static_cast<int64_t>(mat.getRawValue(0,0)) * mat.getRawValue(2,2) - static_cast<int64_t>(mat.getRawValue(0,2)) * mat.getRawValue(2,0),
                static_cast<int64_t>(mat.getRawValue(0,2)) * mat.getRawValue(1,0) - static_cast<int64_t>(mat.getRawValue(0,0)) * mat.getRawValue(1,2),
                static_cast<int64_t>(mat.getRawValue(1,0)) * mat.getRawValue(2,1) - static_cast<int64_t>(mat.getRawValue(1,1)) * mat.getRawValue(2,0),
                static_cast<int64_t>(mat.getRawValue(0,1)) * mat.getRawValue(2,0) - static_cast<int64_t>(mat.getRawValue(0,0)) * mat.getRawValue(2,1),
                static_cast<int64_t>(mat.getRawValue(0,0)) * mat.getRawValue(1,1) - static_cast<int64_t>(mat.getRawValue(0,1)) * mat.getRawValue(1,0)
            };

            /// Cast back to Type only after dividing by "det".
            /// Adj(FX^2) / Det(FX) = Result(FX) -> result scaled only once, as expected
            outResult.setRawValue(0, 0, static_cast<Type>(adjugate_64[0] / det));
            outResult.setRawValue(0, 1, static_cast<Type>(adjugate_64[1] / det));
            outResult.setRawValue(0, 2, static_cast<Type>(adjugate_64[2] / det));
            outResult.setRawValue(1, 0, static_cast<Type>(adjugate_64[3] / det));
            outResult.setRawValue(1, 1, static_cast<Type>(adjugate_64[4] / det));
            outResult.setRawValue(1, 2, static_cast<Type>(adjugate_64[5] / det));
            outResult.setRawValue(2, 0, static_cast<Type>(adjugate_64[6] / det));
            outResult.setRawValue(2, 1, static_cast<Type>(adjugate_64[7] / det));
            outResult.setRawValue(2, 2, static_cast<Type>(adjugate_64[8] / det));
        }
        else
        {
            Type det{ Type(0) };
            DeterminantTo(det, mat);

            if (isZero(det))
            {
                outResult = Matrix3x3<Type>::Zero();
                return;
            }

            /// adjugate
            outResult(0, 0) = mat(1,1) * mat(2,2) - mat(1,2) * mat(2,1);
            outResult(0, 1) = mat(0,2) * mat(2,1) - mat(0,1) * mat(2,2);
            outResult(0, 2) = mat(0,1) * mat(1,2) - mat(0,2) * mat(1,1);
            outResult(1, 0) = mat(1,2) * mat(2,0) - mat(1,0) * mat(2,2);
            outResult(1, 1) = mat(0,0) * mat(2,2) - mat(0,2) * mat(2,0);
            outResult(1, 2) = mat(0,2) * mat(1,0) - mat(0,0) * mat(1,2);
            outResult(2, 0) = mat(1,0) * mat(2,1) - mat(1,1) * mat(2,0);
            outResult(2, 1) = mat(0,1) * mat(2,0) - mat(0,0) * mat(2,1);
            outResult(2, 2) = mat(0,0) * mat(1,1) - mat(0,1) * mat(1,0);

            /// apply det
            outResult /= det;
        }
    }


    /// <summary>
    /// Compute Transpose
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    void TransposeTo(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat)
    {
        outResult.setRawValue(0, 0, mat.getRawValue(0, 0));
        outResult.setRawValue(1, 0, mat.getRawValue(0, 1));
        outResult.setRawValue(2, 0, mat.getRawValue(0, 2));
        outResult.setRawValue(0, 1, mat.getRawValue(1, 0));
        outResult.setRawValue(1, 1, mat.getRawValue(1, 1));
        outResult.setRawValue(2, 1, mat.getRawValue(1, 2));
        outResult.setRawValue(0, 2, mat.getRawValue(2, 0));
        outResult.setRawValue(1, 2, mat.getRawValue(2, 1));
        outResult.setRawValue(2, 2, mat.getRawValue(2, 2));
    }


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)
 
    template class Matrix3x3<float>;
    template class Matrix3x3<double>;
    template class Matrix3x3<int>;

    template void MultiplyTo(Matrix3x3<float>& outResult, const Matrix3x3<float>& mA, const Matrix3x3<float>& mB);
    template void MultiplyTo(Matrix3x3<double>& outResult, const Matrix3x3<double>& mA, const Matrix3x3<double>& mB);
    template void MultiplyTo(Matrix3x3<int>& outResult, const Matrix3x3<int>& mA, const Matrix3x3<int>& mB);

    template void MultiplyTo(Vector3<float>& outResult, const Matrix3x3<float>& mat, const Vector3<float>& vec);
    template void MultiplyTo(Vector3<double>& outResult, const Matrix3x3<double>& mat, const Vector3<double>& vec);
    template void MultiplyTo(Vector3<int>& outResult, const Matrix3x3<int>& mat, const Vector3<int>& vec);

    template Matrix3x3<float>  operator*(float  scalar, const Matrix3x3<float>&  matrix);
    template Matrix3x3<double> operator*(double scalar, const Matrix3x3<double>& matrix);
    template Matrix3x3<int>    operator*(int    scalar, const Matrix3x3<int>&    matrix);

} /// namespace ETL::Math
