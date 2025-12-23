///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.cpp
///----------------------------------------------------------------------------

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
    void Multiply(Vector3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector3<Type>& vec)
    {
        /// --- SAFETY CHECK FOR ALIASING ---
        /// If outResult is the same object as vec, we must use a temporary buffer.
        if (&outResult == &vec)
        {
            Vector3<Type> temp;
            Multiply(temp, mat, vec);

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
    void Multiply(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mA, const Matrix3x3<Type>& mB)
    {
        /// --- SAFETY CHECK FOR ALIASING ---
        /// If outResult is the same object as mA OR mB, we must use a temporary buffer.
        if (&outResult == &mA || &outResult == &mB)
        {
            Matrix3x3<Type> temp;
            Multiply(temp, mA, mB);

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
                    outResult.setRawValue(row, col, mA(row,0) * mB(0,col) + mA(row,1) * mB(1,col) + mA(row,2) * mB(2,col));
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
    void Determinant(Type& outResult, const Matrix3x3<Type>& mat, bool bFixedPoint /*= false*/)
    {
        if constexpr (std::integral<Type>)
        {
            /// 1. Calculate the determinant components using 64-bit integers.
            /// Each term is scaled by FIXED_ONE, so the determinant ->
            /// (FIXED_ONE * FIXED_ONE * FIXED_ONE) = FIXED_ONE^3. -> is scaled thrice, but 
            /// we de-scale after each multiply to avoid overflows
            const int64_t det_fixed = ((((static_cast<int64_t>(mat.getRawValue(0,0)) * mat.getRawValue(1,1)) >> FIXED_SHIFT) * mat.getRawValue(2,2)) >> FIXED_SHIFT)
                                    + ((((static_cast<int64_t>(mat.getRawValue(0,1)) * mat.getRawValue(1,2)) >> FIXED_SHIFT) * mat.getRawValue(2,0)) >> FIXED_SHIFT)
                                    + ((((static_cast<int64_t>(mat.getRawValue(0,2)) * mat.getRawValue(1,0)) >> FIXED_SHIFT) * mat.getRawValue(2,1)) >> FIXED_SHIFT)
                                    - ((((static_cast<int64_t>(mat.getRawValue(0,2)) * mat.getRawValue(1,1)) >> FIXED_SHIFT) * mat.getRawValue(2,0)) >> FIXED_SHIFT)
                                    - ((((static_cast<int64_t>(mat.getRawValue(0,0)) * mat.getRawValue(1,2)) >> FIXED_SHIFT) * mat.getRawValue(2,1)) >> FIXED_SHIFT)
                                    - ((((static_cast<int64_t>(mat.getRawValue(0,1)) * mat.getRawValue(1,0)) >> FIXED_SHIFT) * mat.getRawValue(2,2)) >> FIXED_SHIFT);

            outResult = static_cast<Type>(bFixedPoint ? det_fixed : det_fixed >> FIXED_SHIFT);
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
    bool Inverse(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat)
    {
        Type det;
        Determinant(det, mat, true);
        if (isZero(det))
            return false;

        /// --- SAFETY CHECK FOR ALIASING ---
        /// If outResult is the same object as mat, we must use a temporary buffer.
        if (&outResult == &mat)
        {
            Matrix3x3<Type> temp;
            bool ok = Inverse(temp, mat);

            if (ok)
                outResult = temp;

            return ok;
        }

        if constexpr (std::integral<Type>)
        {
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

        return true;
    }


    /// <summary>
    /// Compute Transpose
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="mat"></param>
    template<typename Type>
    void Transpose(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat)
    {
        const Type elem01 = mat.getRawValue(0, 1);
        const Type elem02 = mat.getRawValue(0, 2);
        const Type elem10 = mat.getRawValue(1, 0);
        const Type elem12 = mat.getRawValue(1, 2);
        const Type elem20 = mat.getRawValue(2, 0);
        const Type elem21 = mat.getRawValue(2, 1);

        outResult.setRawValue(0, 1, elem10);
        outResult.setRawValue(0, 2, elem20);
        outResult.setRawValue(1, 0, elem01);
        outResult.setRawValue(1, 2, elem21);
        outResult.setRawValue(2, 0, elem02);
        outResult.setRawValue(2, 1, elem12);

        if (&outResult != &mat)
        {
            outResult.setRawValue(0, 0, mat.getRawValue(0, 0));
            outResult.setRawValue(1, 1, mat.getRawValue(1, 1));
            outResult.setRawValue(2, 2, mat.getRawValue(2, 2));
        }
    }


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)
 
    template class Matrix3x3<float>;
    template class Matrix3x3<double>;
    template class Matrix3x3<int>;

    template void Multiply(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mA, const Matrix3x3<float>&  mB);
    template void Multiply(Matrix3x3<double>& outResult, const Matrix3x3<double>& mA, const Matrix3x3<double>& mB);
    template void Multiply(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mA, const Matrix3x3<int>&    mB);

    template void Multiply(Vector3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector3<float>&  vec);
    template void Multiply(Vector3<double>& outResult, const Matrix3x3<double>& mat, const Vector3<double>& vec);
    template void Multiply(Vector3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector3<int>&    vec);

    template void GetCol(Vector3<float>&  outResult, const Matrix3x3<float>&  mat, int index);
    template void GetCol(Vector3<double>& outResult, const Matrix3x3<double>& mat, int index);
    template void GetCol(Vector3<int>&    outResult, const Matrix3x3<int>&    mat, int index);

    template void GetRow(Vector3<float>&  outResult, const Matrix3x3<float>&  mat, int index);
    template void GetRow(Vector3<double>& outResult, const Matrix3x3<double>& mat, int index);
    template void GetRow(Vector3<int>&    outResult, const Matrix3x3<int>&    mat, int index);

    template void SetCol(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, int index, const Vector3<float>&  col);
    template void SetCol(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, int index, const Vector3<double>& col);
    template void SetCol(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, int index, const Vector3<int>&    col);

    template void SetRow(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, int index, const Vector3<float>&  row);
    template void SetRow(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, int index, const Vector3<double>& row);
    template void SetRow(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, int index, const Vector3<int>&    row);

    template void TransformPoint(Vector2<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<float>&  point);
    template void TransformPoint(Vector2<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& point);
    template void TransformPoint(Vector2<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<int>&    point);

    template void TransformDirection(Vector2<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<float>&  direction);
    template void TransformDirection(Vector2<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& direction);
    template void TransformDirection(Vector2<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<int>&    direction);

    template void Translate(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<float>&  translation);
    template void Translate(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& translation);
    template void Translate(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<int>&    translation);

    template void SetTranslation(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<float>&  translation);
    template void SetTranslation(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& translation);
    template void SetTranslation(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<int>&    translation);

    template void GetTranslation(Vector2<float>&  outResult, const Matrix3x3<float>&  mat);
    template void GetTranslation(Vector2<double>& outResult, const Matrix3x3<double>& mat);
    template void GetTranslation(Vector2<int>&    outResult, const Matrix3x3<int>&    mat);

    template void Rotate(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, double angleRad);
    template void Rotate(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, double angleRad);
    template void Rotate(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, double angleRad);

    template void SetRotation(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, double angleRad);
    template void SetRotation(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, double angleRad);
    template void SetRotation(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, double angleRad);

    template void GetRotation(double& outResult, const Matrix3x3<float>&  mat);
    template void GetRotation(double& outResult, const Matrix3x3<double>& mat);
    template void GetRotation(double& outResult, const Matrix3x3<int>&    mat);

    template void Scale(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<double>& scale);
    template void Scale(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& scale);
    template void Scale(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<double>& scale);

    template void SetScaling(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<double>& scale);
    template void SetScaling(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& scale);
    template void SetScaling(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<double>& scale);

    template void GetScaling(Vector2<double>& outResult, const Matrix3x3<float>&  mat);
    template void GetScaling(Vector2<double>& outResult, const Matrix3x3<double>& mat);
    template void GetScaling(Vector2<double>& outResult, const Matrix3x3<int>&    mat);

    template void Determinant(float&  outResult, const Matrix3x3<float>&  mat, bool bFixedPoint);
    template void Determinant(double& outResult, const Matrix3x3<double>& mat, bool bFixedPoint);
    template void Determinant(int&    outResult, const Matrix3x3<int>&    mat, bool bFixedPoint);

    template bool Inverse(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat);
    template bool Inverse(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat);
    template bool Inverse(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat);

    template void Transpose(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat);
    template void Transpose(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat);
    template void Transpose(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat);

    template Matrix3x3<float>  operator*(float  scalar, const Matrix3x3<float>&  matrix);
    template Matrix3x3<double> operator*(double scalar, const Matrix3x3<double>& matrix);
    template Matrix3x3<int>    operator*(int    scalar, const Matrix3x3<int>&    matrix);

} /// namespace ETL::Math
