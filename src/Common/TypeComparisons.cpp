///----------------------------------------------------------------------------
/// ETL - MathLib
/// FloatComparisons.cpp
///---------------------------------------------------------------------------- 

#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Vector2.h>
#include <MathLib/Types/Vector3.h>
#include <MathLib/Types/Matrix3x3.h>


namespace ETL { namespace Math
{

    /// Vector2

    template<typename T>
    bool isZero(const Vector2<T>& vec, T epsilon) {
        return isZero(vec.x(), epsilon) &&
               isZero(vec.y(), epsilon);
    }

    template<typename T>
    bool isEqual(const Vector2<T>& a, const Vector2<T>& b, T epsilon) {
        return isEqual(a.x(), b.x(), epsilon) &&
            isEqual(a.y(), b.y(), epsilon);
    }

    /// Vector3

    template<typename T>
    bool isZero(const Vector3<T>& vec, T epsilon) {
        return isZero(vec.x(), epsilon) &&
               isZero(vec.y(), epsilon) &&
               isZero(vec.z(), epsilon);
    }

    template<typename T>
    bool isEqual(const Vector3<T>& a, const Vector3<T>& b, T epsilon) {
        return isEqual(a.x(), b.x(), epsilon) &&
               isEqual(a.y(), b.y(), epsilon) &&
               isEqual(a.z(), b.z(), epsilon);
    }

    /// Matrix3x3

    template<typename T>
    bool isZero(const Matrix3x3<T>& mat, T epsilon) {
        for (int i = 0; i < 9; ++i) {
            if (!isZero<T>(mat[i], epsilon)) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    bool isEqual(const Matrix3x3<T>& a, const Matrix3x3<T>& b, T epsilon) {
        for (int i = 0; i < 9; ++i) {
            if (!isEqual(a[i], b[i], epsilon)) {
                return false;
            }
        }
        return true;
    }


    /// Explicit template instantiation definitions

    template bool isZero(const Vector2<int>&, int);
    template bool isZero(const Vector2<unsigned int>&, unsigned int);
    template bool isZero(const Vector3<float>&, float);
    template bool isZero(const Vector3<double>&, double);
    template bool isZero(const Matrix3x3<float>&, float);
    template bool isZero(const Matrix3x3<double>&, double);

    template bool isEqual(const Vector2<int>&, const Vector2<int>&, int);
    template bool isEqual(const Vector2<unsigned int>&, const Vector2<unsigned int>&, unsigned int);
    template bool isEqual(const Vector3<float>&, const Vector3<float>&, float);
    template bool isEqual(const Vector3<double>&, const Vector3<double>&, double);
    template bool isEqual(const Matrix3x3<float>&, const Matrix3x3<float>&, float);
    template bool isEqual(const Matrix3x3<double>&, const Matrix3x3<double>&, double);



}} /// namespace ETL::Math