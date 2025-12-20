///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector4.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Vector4.h"

namespace ETL::Math
{

    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    template class Vector4<float>;
    template class Vector4<double>;
    template class Vector4<int>;

    template void ComponentMul(Vector4<float>&  outResult, const Vector4<float>&  v1, const Vector4<float>&  v2);
    template void ComponentMul(Vector4<double>& outResult, const Vector4<double>& v1, const Vector4<double>& v2);
    template void ComponentMul(Vector4<int>&    outResult, const Vector4<int>&    v1, const Vector4<int>&    v2);

    template void ComponentDiv(Vector4<float>&  outResult, const Vector4<float>&  v1, const Vector4<float>&  v2);
    template void ComponentDiv(Vector4<double>& outResult, const Vector4<double>& v1, const Vector4<double>& v2);
    template void ComponentDiv(Vector4<int>&    outResult, const Vector4<int>&    v1, const Vector4<int>&    v2);

    template void Dot(double& outResult, const Vector4<float>&  v1, const Vector4<float>&  v2);
    template void Dot(double& outResult, const Vector4<double>& v1, const Vector4<double>& v2);
    template void Dot(double& outResult, const Vector4<int>&    v1, const Vector4<int>&    v2);

    template void Length(double& outResult, const Vector4<float>&  vec);
    template void Length(double& outResult, const Vector4<double>& vec);
    template void Length(double& outResult, const Vector4<int>&    vec);

    template void LengthSquared(double& outResult, const Vector4<float>&  vec);
    template void LengthSquared(double& outResult, const Vector4<double>& vec);
    template void LengthSquared(double& outResult, const Vector4<int>&    vec);

    template bool Normalize(Vector4<float>&  outResult, const Vector4<float>&  vec);
    template bool Normalize(Vector4<double>& outResult, const Vector4<double>& vec);
    template bool Normalize(Vector4<int>&    outResult, const Vector4<int>&    vec);

    template void ToVector3(Vector3<float>&  outResult, const Vector4<float>&  vec);
    template void ToVector3(Vector3<double>& outResult, const Vector4<double>& vec);
    template void ToVector3(Vector3<int>&    outResult, const Vector4<int>&    vec);

    template void PerspectiveDivide(Vector3<float>&  outResult, const Vector4<float>&  vec);
    template void PerspectiveDivide(Vector3<double>& outResult, const Vector4<double>& vec);
    template void PerspectiveDivide(Vector3<int>&    outResult, const Vector4<int>&    vec);

    template Vector4<float>  operator*(float  scalar, const Vector4<float>&  vector);
    template Vector4<double> operator*(double scalar, const Vector4<double>& vector);
    template Vector4<int>    operator*(int    scalar, const Vector4<int>&    vector);

} /// namespace ETL::Math
