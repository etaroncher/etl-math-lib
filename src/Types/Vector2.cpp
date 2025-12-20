///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector2.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Vector2.h"

namespace ETL::Math
{

    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    template class Vector2<float>;
    template class Vector2<double>;
    template class Vector2<int>;

    template void ComponentMul(Vector2<float>&  outResult, const Vector2<float>&  v1, const Vector2<float>&  v2);
    template void ComponentMul(Vector2<double>& outResult, const Vector2<double>& v1, const Vector2<double>& v2);
    template void ComponentMul(Vector2<int>&    outResult, const Vector2<int>&    v1, const Vector2<int>&    v2);

    template void ComponentDiv(Vector2<float>&  outResult, const Vector2<float>&  v1, const Vector2<float>&  v2);
    template void ComponentDiv(Vector2<double>& outResult, const Vector2<double>& v1, const Vector2<double>& v2);
    template void ComponentDiv(Vector2<int>&    outResult, const Vector2<int>&    v1, const Vector2<int>&    v2);

    template void Dot(double& outResult, const Vector2<float>&  v1, const Vector2<float>&  v2);
    template void Dot(double& outResult, const Vector2<double>& v1, const Vector2<double>& v2);
    template void Dot(double& outResult, const Vector2<int>&    v1, const Vector2<int>&    v2);

    template void Cross(double& outResult, const Vector2<float>&  v1, const Vector2<float>&  v2);
    template void Cross(double& outResult, const Vector2<double>& v1, const Vector2<double>& v2);
    template void Cross(double& outResult, const Vector2<int>&    v1, const Vector2<int>&    v2);

    template void Length(double& outResult, const Vector2<float>&  vec);
    template void Length(double& outResult, const Vector2<double>& vec);
    template void Length(double& outResult, const Vector2<int>&    vec);

    template void LengthSquared(double& outResult, const Vector2<float>&  vec);
    template void LengthSquared(double& outResult, const Vector2<double>& vec);
    template void LengthSquared(double& outResult, const Vector2<int>&    vec);

    template bool Normalize(Vector2<float>&  outResult, const Vector2<float>&  vec);
    template bool Normalize(Vector2<double>& outResult, const Vector2<double>& vec);
    template bool Normalize(Vector2<int>&    outResult, const Vector2<int>&    vec);

    template Vector2<float>  operator*(float  scalar, const Vector2<float>&  vector);
    template Vector2<double> operator*(double scalar, const Vector2<double>& vector);
    template Vector2<int>    operator*(int    scalar, const Vector2<int>&    vector);

} /// namespace ETL::Math
