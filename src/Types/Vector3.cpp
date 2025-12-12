///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector3.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Vector3.h"
#include <cmath>
#include <stdexcept>

namespace ETL::Math
{

    /// <summary>
    /// Vector length
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Vector3<Type>::length() const
    {
        return Type(std::sqrt(lengthSquared()));
    }


    /// <summary>
    /// Get a normalized copy of this vector
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type> Vector3<Type>::normalize() const requires std::floating_point<Type>
    {
        const Type lengthSq = lengthSquared();
        if (isZero(lengthSq))
            throw std::runtime_error("Cannot normalize zero vector");

        return *this / Type(std::sqrt(lengthSq));
    }


    /// <summary>
    /// Get a normalized copy of this vector
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type>& Vector3<Type>::makeNormalize() requires std::floating_point<Type>
    {
        const Type lengthSq = lengthSquared();
        if (isZero(lengthSq))
            throw std::runtime_error("Cannot normalize zero vector");

        *this /= Type(std::sqrt(lengthSq));
        return *this;
    }


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    template class Vector3<float>;
    template class Vector3<double>;
    template class Vector3<int>;

    template Vector3<float>  operator*(float  scalar, const Vector3<float>&  vector);
    template Vector3<double> operator*(double scalar, const Vector3<double>& vector);
    template Vector3<int>    operator*(int    scalar, const Vector3<int>&    vector);

    template Vector3<float>  cross(const Vector3<float>&  v1, const Vector3<float>&   v2);
    template Vector3<double> cross(const Vector3<double>& v1, const Vector3<double>& v2);
    template Vector3<int>    cross(const Vector3<int>&    v1, const Vector3<int>&       v2);

    template float  dot(const Vector3<float>&  v1, const Vector3<float>&  v2);
    template double dot(const Vector3<double>& v1, const Vector3<double>& v2);
    template int    dot(const Vector3<int>&    v1, const Vector3<int>&    v2);

} /// namespace ETL::Math
