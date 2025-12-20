///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector3.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Vector3.h"

namespace ETL::Math
{

    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    template class Vector3<float>;
    template class Vector3<double>;
    template class Vector3<int>;

    template void ComponentMul(Vector3<float>&  outResult, const Vector3<float>&  v1, const Vector3<float>&  v2);
    template void ComponentMul(Vector3<double>& outResult, const Vector3<double>& v1, const Vector3<double>& v2);
    template void ComponentMul(Vector3<int>&    outResult, const Vector3<int>&    v1, const Vector3<int>&    v2);

    template void ComponentDiv(Vector3<float>&  outResult, const Vector3<float>&  v1, const Vector3<float>&  v2);
    template void ComponentDiv(Vector3<double>& outResult, const Vector3<double>& v1, const Vector3<double>& v2);
    template void ComponentDiv(Vector3<int>&    outResult, const Vector3<int>&    v1, const Vector3<int>&    v2);

    template void Dot(double& outResult, const Vector3<float>&  v1, const Vector3<float>&  v2);
    template void Dot(double& outResult, const Vector3<double>& v1, const Vector3<double>& v2);
    template void Dot(double& outResult, const Vector3<int>&    v1, const Vector3<int>&    v2);

    template void Cross(Vector3<float>&  outResult, const Vector3<float>&  v1, const Vector3<float>&  v2);
    template void Cross(Vector3<double>& outResult, const Vector3<double>& v1, const Vector3<double>& v2);
    template void Cross(Vector3<int>&    outResult, const Vector3<int>&    v1, const Vector3<int>&    v2);

    template void Length(double& outResult, const Vector3<float>&  vec);
    template void Length(double& outResult, const Vector3<double>& vec);
    template void Length(double& outResult, const Vector3<int>&    vec);

    template void LengthSquared(double& outResult, const Vector3<float>&  vec);
    template void LengthSquared(double& outResult, const Vector3<double>& vec);
    template void LengthSquared(double& outResult, const Vector3<int>&    vec);

    template bool Normalize(Vector3<float>&  outResult, const Vector3<float>&  vec);
    template bool Normalize(Vector3<double>& outResult, const Vector3<double>& vec);
    template bool Normalize(Vector3<int>&    outResult, const Vector3<int>&    vec);

    template void ToVector2(Vector2<float>&  outResult, const Vector3<float>&  vec);
    template void ToVector2(Vector2<double>& outResult, const Vector3<double>& vec);
    template void ToVector2(Vector2<int>&    outResult, const Vector3<int>&    vec);

    template void PerspectiveDivide(Vector2<float>&  outResult, const Vector3<float>&  vec);
    template void PerspectiveDivide(Vector2<double>& outResult, const Vector3<double>& vec);
    template void PerspectiveDivide(Vector2<int>&    outResult, const Vector3<int>&    vec);

    template Vector3<float>  operator*(float  scalar, const Vector3<float>&  vector);
    template Vector3<double> operator*(double scalar, const Vector3<double>& vector);
    template Vector3<int>    operator*(int    scalar, const Vector3<int>&    vector);

} /// namespace ETL::Math
