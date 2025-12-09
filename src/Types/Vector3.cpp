///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector3.cpp
///----------------------------------------------------------------------------

#include <MathLib/Types/Vector3.h>
#include <Mathlib/Common/Common.h>
#include <Mathlib/Common/TypeComparisons.h>
#include <cmath>
#include <stdexcept>

namespace ETL::Math
{

    /// <summary>
    /// Default Constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    template<typename Type>
    constexpr Vector3<Type>::Vector3() : mData{ Type(0), Type(0), Type(0) } {}


    /// <summary>
    /// Same value constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="val"></param>
    template<typename Type>
    constexpr Vector3<Type>::Vector3(Type val) : mData{ val, val, val } {}


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="z"></param>
    template<typename Type>
    constexpr Vector3<Type>::Vector3(Type x, Type y, Type z) : mData{ x,   y,   z } {}


    /// <summary>
    /// X componenet getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Vector3<Type>::x() const
    {
        return mX;
    }


    /// <summary>
    /// Y component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Vector3<Type>::y() const
    {
        return mY;
    }


    /// <summary>
    /// Z componenet setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Vector3<Type>::z() const
    {
        return (mZ);
    }


    /// <summary>
    /// X component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    template<typename Type>
    void Vector3<Type>::x(Type x)
    {
        mX = x;
    }


    /// <summary>
    /// Y component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="y"></param>
    template<typename Type>
    void Vector3<Type>::y(Type y)
    {
        mY = y;
    }


    /// <summary>
    /// Z component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="z"></param>
    template<typename Type>
    void Vector3<Type>::z(Type z)
    {
        mZ = z;
    }


    /// <summary>
    /// Subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    Type& Vector3<Type>::operator[](int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < 3, "Vector3 out of bounds acces");
        return mData[index];
    }


    /// <summary>
    /// Const subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    Type Vector3<Type>::operator[](int index) const
    {
        ETLMATH_ASSERT(index >= 0 && index < 3, "Vector3 out of bounds acces");
        return mData[index];
    }


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
    /// Vector lenght squared
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Vector3<Type>::lengthSquared() const
    {
        return mX*mX + mY*mY + mZ*mZ;
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


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type> Vector3<Type>::operator+(const Vector3& other) const
    {
        return Vector3<Type>{ mX + other.mX,
                              mY + other.mY,
                              mZ + other.mZ };
    }


    /// <summary>
    /// Substraction operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type> Vector3<Type>::operator-(const Vector3& other) const
    {
        return Vector3<Type>{ mX - other.mX,
                              mY - other.mY,
                              mZ - other.mZ };
    }


    /// <summary>
    /// Multiplication operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type> Vector3<Type>::operator*(Type scalar) const
    {
        return Vector3<Type>{ mX * scalar,
                              mY * scalar,
                              mZ * scalar };
    }


    /// <summary>
    /// Division operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type> Vector3<Type>::operator/(Type scalar) const
    {
        ETLMATH_ASSERT(!isZero(scalar), "Vector3 division by 0");

        if constexpr (std::is_floating_point_v<Type>)
        {
            const Type inv = Type(1) / scalar;
            return Vector3<Type>{ mX * inv, mY * inv, mZ * inv };
        }
        else
        {
            /// integer division, divide to avoid truncation errors
            return Vector3<Type>{ mX / scalar, mY / scalar, mZ / scalar };
        }
    }


    /// <summary>
    /// Addition assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type>& Vector3<Type>::operator+=(const Vector3& other)
    {
        mX += other.mX;
        mY += other.mY;
        mZ += other.mZ;
        return *this;
    }


    /// <summary>
    /// Substraction assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type>& Vector3<Type>::operator-=(const Vector3& other)
    {
        mX -= other.mX;
        mY -= other.mY;
        mZ -= other.mZ;
        return *this;
    }


    /// <summary>
    /// Multiplication assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type>& Vector3<Type>::operator*=(Type scalar)
    {
        mX *= scalar;
        mY *= scalar;
        mZ *= scalar;
        return *this;
    }


    /// <summary>
    /// Division assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type>& Vector3<Type>::operator/=(Type scalar)
    {
        ETLMATH_ASSERT(!isZero(scalar), "Vector3 division by 0");

        if constexpr (std::is_floating_point_v<Type>)
        {
            const Type inv = Type(1) / scalar;
            mX *= inv;
            mY *= inv;
            mZ *= inv;
        }
        else
        {
            /// integer division, divide to avoid truncation errors
            mX /= scalar;
            mY /= scalar;
            mZ /= scalar;
        }

        return *this;
    }


    /// <summary>
    /// Equality operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    bool Vector3<Type>::operator==(const Vector3<Type>& other) const
    {
        return std::equal(mData, mData + 3, other.mData);
    }


    /// <summary>
    /// Inequality operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    bool Vector3<Type>::operator!=(const Vector3<Type>& other) const
    {
        return !(*this == other);
    }


    /// <summary>
    /// Scalar * Vector multiplication operator, for commutative
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <param name="vector"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type> operator*(Type scalar, const Vector3<Type>& vector)
    {
        return vector * scalar;
    }


    /// <summary>
    /// Cross product of V1 x V2
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    /// <returns></returns>
    template<typename Type>
    Vector3<Type> cross(const Vector3<Type>& v1, const Vector3<Type>& v2)
    {
        return Vector3<Type>{ v1.y() * v2.z() - v1.z() * v2.y(),
                              v1.z() * v2.x() - v1.x() * v2.z(),
                              v1.x() * v2.y() - v1.y() * v2.x() };
    }


    /// <summary>
    /// Dot product V1*V2
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    /// <returns></returns>
    template<typename Type>
    Type dot(const Vector3<Type>& v1, const Vector3<Type>& v2)
    {
        return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
    }


    /// Explicit template instantiatio (precompiled declaration)
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
