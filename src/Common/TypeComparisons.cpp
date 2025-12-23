///----------------------------------------------------------------------------
/// ETL - MathLib
/// FloatComparisons.cpp
///---------------------------------------------------------------------------- 

#include "MathLib/Common/TypeComparisons.h"
#include "MathLib/Types/Vector2.h"
#include "MathLib/Types/Vector3.h"
#include "MathLib/Types/Vector4.h"
#include "MathLib/Types/Matrix3x3.h"

namespace ETL::Math
{
    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    /// Vector2
    template bool isZero(const Vector2<int>&,    double);
    template bool isZero(const Vector2<float>&,  double);
    template bool isZero(const Vector2<double>&, double);

    template bool isEqual(const Vector2<int>&,    const Vector2<int>&,    double);
    template bool isEqual(const Vector2<float>&,  const Vector2<float>&,  double);
    template bool isEqual(const Vector2<double>&, const Vector2<double>&, double);

    /// Vector3
    template bool isZero(const Vector3<int>&,    double);
    template bool isZero(const Vector3<float>&,  double);
    template bool isZero(const Vector3<double>&, double);

    template bool isEqual(const Vector3<int>&,    const Vector3<int>&,    double);
    template bool isEqual(const Vector3<float>&,  const Vector3<float>&,  double);
    template bool isEqual(const Vector3<double>&, const Vector3<double>&, double);

    /// Vector4
    template bool isZero(const Vector4<int>&,    double);
    template bool isZero(const Vector4<float>&,  double);
    template bool isZero(const Vector4<double>&, double);

    template bool isEqual(const Vector4<int>&,    const Vector4<int>&,    double);
    template bool isEqual(const Vector4<float>&,  const Vector4<float>&,  double);
    template bool isEqual(const Vector4<double>&, const Vector4<double>&, double);

    /// Matrix3x3
    template bool isZero(const Matrix3x3<int>&,    double);
    template bool isZero(const Matrix3x3<float>&,  double);
    template bool isZero(const Matrix3x3<double>&, double);

    template bool isEqual(const Matrix3x3<int>&,    const Matrix3x3<int>&,    double);
    template bool isEqual(const Matrix3x3<float>&,  const Matrix3x3<float>&,  double);
    template bool isEqual(const Matrix3x3<double>&, const Matrix3x3<double>&, double);

} /// namespace ETL::Math
