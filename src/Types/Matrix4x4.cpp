///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix4x4.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Matrix4x4.h"
#include "MathLib/Types/Matrix3x3.h"

namespace ETL::Math
{

    ///------------------------------------------------------------------------------------------
    /// Free functions and common helpers

    /// <summary>
    /// Matrix * Vector
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    /// <param name="vec"></param>
    template<typename Type>
    void Multiply(Vector4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector4<Type>& vec)
    {
        /// --- SAFETY CHECK FOR ALIASING ---
        /// If outResult is the same object as vec, we must use a temporary buffer.
        if (&outResult == &vec)
        {
            Vector4<Type> temp;
            Multiply(temp, mat, vec);

            outResult = temp;
            return;
        }

        if constexpr (std::integral<Type>)
        {
            /// Use 64-bit to prevent overflow
            /// vector getters return normal values, mXX is fixed-point ->
            /// Product is fixed-point -> sum (x, y, z) are fixed-point
            const int64_t x = static_cast<int64_t>(mat.getRawValue(0,0)) * vec.getRawValue(0)
                            + static_cast<int64_t>(mat.getRawValue(0,1)) * vec.getRawValue(1)
                            + static_cast<int64_t>(mat.getRawValue(0,2)) * vec.getRawValue(2)
                            + static_cast<int64_t>(mat.getRawValue(0,3)) * vec.getRawValue(3);
            const int64_t y = static_cast<int64_t>(mat.getRawValue(1,0)) * vec.getRawValue(0)
                            + static_cast<int64_t>(mat.getRawValue(1,1)) * vec.getRawValue(1)
                            + static_cast<int64_t>(mat.getRawValue(1,2)) * vec.getRawValue(2)
                            + static_cast<int64_t>(mat.getRawValue(1,3)) * vec.getRawValue(3);
            const int64_t z = static_cast<int64_t>(mat.getRawValue(2,0)) * vec.getRawValue(0)
                            + static_cast<int64_t>(mat.getRawValue(2,1)) * vec.getRawValue(1)
                            + static_cast<int64_t>(mat.getRawValue(2,2)) * vec.getRawValue(2)
                            + static_cast<int64_t>(mat.getRawValue(2,3)) * vec.getRawValue(3);
            const int64_t w = static_cast<int64_t>(mat.getRawValue(3,0)) * vec.getRawValue(0)
                            + static_cast<int64_t>(mat.getRawValue(3,1)) * vec.getRawValue(1)
                            + static_cast<int64_t>(mat.getRawValue(3,2)) * vec.getRawValue(2)
                            + static_cast<int64_t>(mat.getRawValue(3,3)) * vec.getRawValue(3);

            outResult.setRawValue(0, x >> FIXED_SHIFT);
            outResult.setRawValue(1, y >> FIXED_SHIFT);
            outResult.setRawValue(2, z >> FIXED_SHIFT);
            outResult.setRawValue(3, w >> FIXED_SHIFT);
        }
        else
        {
            outResult.setRawValue(0, mat(0,0) * vec[0] + mat(0,1) * vec[1] + mat(0,2) * vec[2] + mat(0,3) * vec[3]);
            outResult.setRawValue(1, mat(1,0) * vec[0] + mat(1,1) * vec[1] + mat(1,2) * vec[2] + mat(1,3) * vec[3]);
            outResult.setRawValue(2, mat(2,0) * vec[0] + mat(2,1) * vec[1] + mat(2,2) * vec[2] + mat(2,3) * vec[3]);
            outResult.setRawValue(3, mat(3,0) * vec[0] + mat(3,1) * vec[1] + mat(3,2) * vec[2] + mat(3,3) * vec[3]);
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
    void Multiply(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mA, const Matrix4x4<Type>& mB)
    {
        /// --- SAFETY CHECK FOR ALIASING ---
        /// If outResult is the same object as mA OR mB, we must use a temporary buffer.
        if (&outResult == &mA || &outResult == &mB)
        {
            Matrix4x4<Type> temp;
            Multiply(temp, mA, mB);

            outResult = temp;
            return;
        }

        for (int col = 0; col < Matrix4x4<Type>::COL_SIZE; ++col)
        {
            for (int row = 0; row < Matrix4x4<Type>::COL_SIZE; ++row)
            {
                if constexpr (std::integral<Type>)
                {
                    const int64_t sum = static_cast<int64_t>(mA.getRawValue(row, 0)) * mB.getRawValue(0, col)
                                      + static_cast<int64_t>(mA.getRawValue(row, 1)) * mB.getRawValue(1, col)
                                      + static_cast<int64_t>(mA.getRawValue(row, 2)) * mB.getRawValue(2, col)
                                      + static_cast<int64_t>(mA.getRawValue(row, 3)) * mB.getRawValue(3, col);

                    /// Bitshift result back to Fixed Point
                    outResult.setRawValue(row, col, static_cast<Type>(sum >> FIXED_SHIFT));
                }
                else
                {
                    outResult.setRawValue(row, col, mA(row,0) * mB(0,col) + mA(row,1) * mB(1,col) + mA(row,2) * mB(2,col) + mA(row, 3) * mB(3, col));
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
    void Determinant(Type& outResult, const Matrix4x4<Type>& mat, bool bFixedPoint /*= false*/)
    {

        const Matrix3x3<Type> adj00{ Raw, mat.getRawValue(1,1), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                          mat.getRawValue(2,1), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                          mat.getRawValue(3,1), mat.getRawValue(3,2), mat.getRawValue(3,3) };

        const Matrix3x3<Type> adj01{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                          mat.getRawValue(2,0), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                          mat.getRawValue(3,0), mat.getRawValue(3,2), mat.getRawValue(3,3) };

        const Matrix3x3<Type> adj02{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,3),
                                          mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,3),
                                          mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,3) };

        const Matrix3x3<Type> adj03{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,2),
                                          mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,2),
                                          mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,2) };

        if constexpr (std::integral<Type>)
        {
            int64_t fixedPointDet = ((static_cast<int64_t>(mat.getRawValue(0, 0)) * adj00.determinant(true)) >> FIXED_SHIFT)
                                  - ((static_cast<int64_t>(mat.getRawValue(0, 1)) * adj01.determinant(true)) >> FIXED_SHIFT)
                                  + ((static_cast<int64_t>(mat.getRawValue(0, 2)) * adj02.determinant(true)) >> FIXED_SHIFT)
                                  - ((static_cast<int64_t>(mat.getRawValue(0, 3)) * adj03.determinant(true)) >> FIXED_SHIFT);

            outResult = static_cast<Type>(bFixedPoint ? fixedPointDet : fixedPointDet >> FIXED_SHIFT);
        }
        else
        {
            outResult = mat.getRawValue(0, 0) * adj00.determinant()
                      - mat.getRawValue(0, 1) * adj01.determinant()
                      + mat.getRawValue(0, 2) * adj02.determinant()
                      - mat.getRawValue(0, 3) * adj03.determinant();
        }
    }


    /// <summary>
    /// Compute Inverse
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    bool Inverse(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat)
    {
        Type det;
        Determinant(det, mat, true);
        if (isZero(det))
            return false;

        /// --- SAFETY CHECK FOR ALIASING ---
        /// If outResult is the same object as mat, we must use a temporary buffer.
        if (&outResult == &mat)
        {
            Matrix4x4<Type> temp;
            bool result = Inverse(temp, mat);

            if (result)
                outResult = temp;

            return result;
        }

        if constexpr (std::integral<Type>)
        {

            /// Compute all 16 cofactors using Matrix3x3
            /// Row 0 cofactors (signs: +, -, +, -)
            const int64_t cof00 = +Matrix3x3<Type>{ Raw, mat.getRawValue(1,1), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                         mat.getRawValue(2,1), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                                         mat.getRawValue(3,1), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof01 = -Matrix3x3<Type>{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof02 = +Matrix3x3<Type>{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,3),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,3),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof03 = -Matrix3x3<Type>{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,2),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,2),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,2)}.determinant(true);

            /// Row 1 cofactors (signs: -, +, -, +)
            const int64_t cof10 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,1), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                         mat.getRawValue(2,1), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                                         mat.getRawValue(3,1), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof11 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof12 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,3),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,3),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof13 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,2),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,2),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,2)}.determinant(true);

            /// Row 2 cofactors (signs: +, -, +, -)
            const int64_t cof20 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,1), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                         mat.getRawValue(1,1), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                         mat.getRawValue(3,1), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof21 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                         mat.getRawValue(1,0), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof22 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,3),
                                                         mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,3),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,3)}.determinant(true);

            const int64_t cof23 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,2),
                                                         mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,2),
                                                         mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,2)}.determinant(true);

            /// Row 3 cofactors (signs: -, +, -, +)
            const int64_t cof30 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,1), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                         mat.getRawValue(1,1), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                         mat.getRawValue(2,1), mat.getRawValue(2,2), mat.getRawValue(2,3)}.determinant(true);

            const int64_t cof31 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                         mat.getRawValue(1,0), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,2), mat.getRawValue(2,3)}.determinant(true);

            const int64_t cof32 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,3),
                                                         mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,3),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,3)}.determinant(true);

            const int64_t cof33 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,2),
                                                         mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,2),
                                                         mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,2)}.determinant(true);

            /// Transpose cofactors and divide by determinant
            outResult.setRawValue(0, 0, static_cast<Type>((cof00 << FIXED_SHIFT) / det));
            outResult.setRawValue(0, 1, static_cast<Type>((cof10 << FIXED_SHIFT) / det));
            outResult.setRawValue(0, 2, static_cast<Type>((cof20 << FIXED_SHIFT) / det));
            outResult.setRawValue(0, 3, static_cast<Type>((cof30 << FIXED_SHIFT) / det));
            outResult.setRawValue(1, 0, static_cast<Type>((cof01 << FIXED_SHIFT) / det));
            outResult.setRawValue(1, 1, static_cast<Type>((cof11 << FIXED_SHIFT) / det));
            outResult.setRawValue(1, 2, static_cast<Type>((cof21 << FIXED_SHIFT) / det));
            outResult.setRawValue(1, 3, static_cast<Type>((cof31 << FIXED_SHIFT) / det));
            outResult.setRawValue(2, 0, static_cast<Type>((cof02 << FIXED_SHIFT) / det));
            outResult.setRawValue(2, 1, static_cast<Type>((cof12 << FIXED_SHIFT) / det));
            outResult.setRawValue(2, 2, static_cast<Type>((cof22 << FIXED_SHIFT) / det));
            outResult.setRawValue(2, 3, static_cast<Type>((cof32 << FIXED_SHIFT) / det));
            outResult.setRawValue(3, 0, static_cast<Type>((cof03 << FIXED_SHIFT) / det));
            outResult.setRawValue(3, 1, static_cast<Type>((cof13 << FIXED_SHIFT) / det));
            outResult.setRawValue(3, 2, static_cast<Type>((cof23 << FIXED_SHIFT) / det));
            outResult.setRawValue(3, 3, static_cast<Type>((cof33 << FIXED_SHIFT) / det));
        }
        else
        {
            /// Compute all 16 cofactors using Matrix3x3
            /// Row 0 cofactors (signs: +, -, +, -)
            const Type cof00 = +Matrix3x3<Type>{ Raw, mat.getRawValue(1,1), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                      mat.getRawValue(2,1), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                                      mat.getRawValue(3,1), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant();

            const Type cof01 = -Matrix3x3<Type>{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant();

            const Type cof02 = +Matrix3x3<Type>{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,3),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,3),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,3)}.determinant();

            const Type cof03 = -Matrix3x3<Type>{ Raw, mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,2),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,2),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,2)}.determinant();

            /// Row 1 cofactors (signs: -, +, -, +)
            const Type cof10 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,1), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                      mat.getRawValue(2,1), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                                      mat.getRawValue(3,1), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant();

            const Type cof11 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,2), mat.getRawValue(2,3),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant();

            const Type cof12 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,3),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,3),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,3)}.determinant();

            const Type cof13 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,2),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,2),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,2)}.determinant();

            /// Row 2 cofactors (signs: +, -, +, -)
            const Type cof20 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,1), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                      mat.getRawValue(1,1), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                      mat.getRawValue(3,1), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant();

            const Type cof21 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                      mat.getRawValue(1,0), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,2), mat.getRawValue(3,3)}.determinant();

            const Type cof22 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,3),
                                                      mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,3),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,3)}.determinant();

            const Type cof23 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,2),
                                                      mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,2),
                                                      mat.getRawValue(3,0), mat.getRawValue(3,1), mat.getRawValue(3,2)}.determinant();

            /// Row 3 cofactors (signs: -, +, -, +)
            const Type cof30 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,1), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                      mat.getRawValue(1,1), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                      mat.getRawValue(2,1), mat.getRawValue(2,2), mat.getRawValue(2,3)}.determinant();

            const Type cof31 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,2), mat.getRawValue(0,3),
                                                      mat.getRawValue(1,0), mat.getRawValue(1,2), mat.getRawValue(1,3),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,2), mat.getRawValue(2,3)}.determinant();

            const Type cof32 = -Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,3),
                                                      mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,3),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,3)}.determinant();

            const Type cof33 = +Matrix3x3<Type>{ Raw, mat.getRawValue(0,0), mat.getRawValue(0,1), mat.getRawValue(0,2),
                                                      mat.getRawValue(1,0), mat.getRawValue(1,1), mat.getRawValue(1,2),
                                                      mat.getRawValue(2,0), mat.getRawValue(2,1), mat.getRawValue(2,2)}.determinant();

            const Type invDet = Type(1) / det;

            /// Transpose cofactors and multiply by invDet
            outResult.setRawValue(0, 0, cof00 * invDet);
            outResult.setRawValue(0, 1, cof10 * invDet);
            outResult.setRawValue(0, 2, cof20 * invDet);
            outResult.setRawValue(0, 3, cof30 * invDet);
            outResult.setRawValue(1, 0, cof01 * invDet);
            outResult.setRawValue(1, 1, cof11 * invDet);
            outResult.setRawValue(1, 2, cof21 * invDet);
            outResult.setRawValue(1, 3, cof31 * invDet);
            outResult.setRawValue(2, 0, cof02 * invDet);
            outResult.setRawValue(2, 1, cof12 * invDet);
            outResult.setRawValue(2, 2, cof22 * invDet);
            outResult.setRawValue(2, 3, cof32 * invDet);
            outResult.setRawValue(3, 0, cof03 * invDet);
            outResult.setRawValue(3, 1, cof13 * invDet);
            outResult.setRawValue(3, 2, cof23 * invDet);
            outResult.setRawValue(3, 3, cof33 * invDet);
        }

        return true;
    }


    /// <summary>
    /// Compute Transpose
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    void Transpose(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat)
    {
        const Type elem01 = mat.getRawValue(0, 1);
        const Type elem02 = mat.getRawValue(0, 2);
        const Type elem03 = mat.getRawValue(0, 3);
        const Type elem10 = mat.getRawValue(1, 0);
        const Type elem12 = mat.getRawValue(1, 2);
        const Type elem13 = mat.getRawValue(1, 3);
        const Type elem20 = mat.getRawValue(2, 0);
        const Type elem21 = mat.getRawValue(2, 1);
        const Type elem23 = mat.getRawValue(2, 3);
        const Type elem30 = mat.getRawValue(3, 0);
        const Type elem31 = mat.getRawValue(3, 1);
        const Type elem32 = mat.getRawValue(3, 2);

        outResult.setRawValue(0, 1, elem10);
        outResult.setRawValue(0, 2, elem20);
        outResult.setRawValue(0, 3, elem30);
        outResult.setRawValue(1, 0, elem01);
        outResult.setRawValue(1, 2, elem21);
        outResult.setRawValue(1, 3, elem31);
        outResult.setRawValue(2, 0, elem02);
        outResult.setRawValue(2, 1, elem12);
        outResult.setRawValue(2, 3, elem32);
        outResult.setRawValue(3, 0, elem03);
        outResult.setRawValue(3, 1, elem13);
        outResult.setRawValue(3, 2, elem23);

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 0, mat.getRawValue(0, 0));
            outResult.setRawValue(1, 1, mat.getRawValue(1, 1));
            outResult.setRawValue(2, 2, mat.getRawValue(2, 2));
            outResult.setRawValue(3, 3, mat.getRawValue(3, 3));
        }
    }


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)
 
    template class Matrix4x4<float>;
    template class Matrix4x4<double>;
    template class Matrix4x4<int>;

    template void Multiply(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mA, const Matrix4x4<float>&  mB);
    template void Multiply(Matrix4x4<double>& outResult, const Matrix4x4<double>& mA, const Matrix4x4<double>& mB);
    template void Multiply(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mA, const Matrix4x4<int>&    mB);

    template void Multiply(Vector4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector4<float>&  vec);
    template void Multiply(Vector4<double>& outResult, const Matrix4x4<double>& mat, const Vector4<double>& vec);
    template void Multiply(Vector4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector4<int>&    vec);

    template void GetCol(Vector4<float>&  outResult, const Matrix4x4<float>&  mat, int index);
    template void GetCol(Vector4<double>& outResult, const Matrix4x4<double>& mat, int index);
    template void GetCol(Vector4<int>&    outResult, const Matrix4x4<int>&    mat, int index);

    template void GetRow(Vector4<float>&  outResult, const Matrix4x4<float>&  mat, int index);
    template void GetRow(Vector4<double>& outResult, const Matrix4x4<double>& mat, int index);
    template void GetRow(Vector4<int>&    outResult, const Matrix4x4<int>&    mat, int index);

    template void SetCol(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, int index, const Vector4<float>&  col);
    template void SetCol(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, int index, const Vector4<double>& col);
    template void SetCol(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, int index, const Vector4<int>&    col);

    template void SetRow(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, int index, const Vector4<float>&  row);
    template void SetRow(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, int index, const Vector4<double>& row);
    template void SetRow(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, int index, const Vector4<int>&    row);

    template void TransformPoint(Vector3<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<float>&  point);
    template void TransformPoint(Vector3<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& point);
    template void TransformPoint(Vector3<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<int>&    point);

    template void TransformDirection(Vector3<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<float>&  direction);
    template void TransformDirection(Vector3<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& direction);
    template void TransformDirection(Vector3<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<int>&    direction);

    template void Translate(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<float>&  translation);
    template void Translate(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& translation);
    template void Translate(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<int>&    translation);

    template void SetTranslation(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<float>&  translation);
    template void SetTranslation(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& translation);
    template void SetTranslation(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<int>&    translation);

    template void GetTranslation(Vector3<float>&  outResult, const Matrix4x4<float>&  mat);
    template void GetTranslation(Vector3<double>& outResult, const Matrix4x4<double>& mat);
    template void GetTranslation(Vector3<int>&    outResult, const Matrix4x4<int>&    mat);

    template void Rotate(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<double>& rotation);
    template void Rotate(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& rotation);
    template void Rotate(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<double>& rotation);

    template void SetRotation(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<double>& rotation);
    template void SetRotation(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& rotation);
    template void SetRotation(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<double>& rotation);

    template void GetRotation(Vector3<double>& outResult, const Matrix4x4<float>&  mat);
    template void GetRotation(Vector3<double>& outResult, const Matrix4x4<double>& mat);
    template void GetRotation(Vector3<double>& outResult, const Matrix4x4<int>&    mat);

    template void Scale(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<double>& scale);
    template void Scale(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& scale);
    template void Scale(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<double>& scale);

    template void SetScaling(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<double>& scale);
    template void SetScaling(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& scale);
    template void SetScaling(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<double>& scale);

    template void GetScaling(Vector3<double>& outResult, const Matrix4x4<float>&  mat);
    template void GetScaling(Vector3<double>& outResult, const Matrix4x4<double>& mat);
    template void GetScaling(Vector3<double>& outResult, const Matrix4x4<int>&    mat);

    template void Determinant(float&  outResult, const Matrix4x4<float>&  mat, bool bFixedPoint);
    template void Determinant(double& outResult, const Matrix4x4<double>& mat, bool bFixedPoint);
    template void Determinant(int&    outResult, const Matrix4x4<int>&    mat, bool bFixedPoint);

    template bool Inverse(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat);
    template bool Inverse(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat);
    template bool Inverse(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat);

    template void Transpose(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat);
    template void Transpose(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat);
    template void Transpose(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat);

    template Matrix4x4<float>  operator*(float  scalar, const Matrix4x4<float>&  matrix);
    template Matrix4x4<double> operator*(double scalar, const Matrix4x4<double>& matrix);
    template Matrix4x4<int>    operator*(int    scalar, const Matrix4x4<int>&    matrix);

} /// namespace ETL::Math
