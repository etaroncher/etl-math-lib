///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector2.cpp
///----------------------------------------------------------------------------

#include "MathLib/Types/Vector2.h"
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
    Type Vector2<Type>::length() const
    {
        return Type(std::sqrt(lengthSquared()));
    }


    /// <summary>
    /// Get a normalized copy of this vector
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Vector2<Type>::normalize() const requires std::floating_point<Type>
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
    Vector2<Type>& Vector2<Type>::makeNormalize() requires std::floating_point<Type>
    {
        const Type lengthSq = lengthSquared();
        if (isZero(lengthSq))
            throw std::runtime_error("Cannot normalize zero vector");

        *this /= Type(std::sqrt(lengthSq));
        return *this;
    }


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    template class Vector2<float>;
    template class Vector2<double>;
    template class Vector2<int>;

    template Vector2<float>  operator*(float  scalar, const Vector2<float>&  vector);
    template Vector2<double> operator*(double scalar, const Vector2<double>& vector);
    template Vector2<int>    operator*(int    scalar, const Vector2<int>&    vector);

    template float  Cross(const Vector2<float>&  v1, const Vector2<float>&  v2);
    template double Cross(const Vector2<double>& v1, const Vector2<double>& v2);
    template int    Cross(const Vector2<int>&    v1, const Vector2<int>&    v2);

    template float  Dot(const Vector2<float>&  v1, const Vector2<float>&  v2);
    template double Dot(const Vector2<double>& v1, const Vector2<double>& v2);
    template int    Dot(const Vector2<int>&    v1, const Vector2<int>&    v2);

    template float  ComponentMul(const Vector2<float>&  v1, const Vector2<float>&  v2);
    template double ComponentMul(const Vector2<double>& v1, const Vector2<double>& v2);
    template int    ComponentMul(const Vector2<int>&    v1, const Vector2<int>&    v2);

    template float  ComponentDiv(const Vector2<float>&  v1, const Vector2<float>&  v2);
    template double ComponentDiv(const Vector2<double>& v1, const Vector2<double>& v2);
    template int    ComponentDiv(const Vector2<int>&    v1, const Vector2<int>&    v2);

} /// namespace ETL::Math
