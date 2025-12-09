///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector2.cpp
///----------------------------------------------------------------------------

#include <MathLib/Types/Vector2.h>
#include <Mathlib/Common/Common.h>
#include <Mathlib/Common/TypeComparisons.h>
#include <stdexcept>

namespace ETL::Math
{

    /// <summary>
    /// Same value constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="val"></param>
    template<typename Type>
    constexpr Vector2<Type>::Vector2(Type val) : mData{ val, val } {}


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    constexpr Vector2<Type>::Vector2(Type x, Type y) : mData{ x, y } {}


    /// <summary>
    /// X componenet getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Vector2<Type>::x() const
    {
        return mX;
    }


    /// <summary>
    /// Y component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Vector2<Type>::y() const
    {
        return mY;
    }


    /// <summary>
    /// X component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    template<typename Type>
    void Vector2<Type>::x(Type x)
    {
        mX = x;
    }


    /// <summary>
    /// Y component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="y"></param>
    template<typename Type>
    void Vector2<Type>::y(Type y)
    {
        mY = y;
    }


    /// <summary>
    /// Subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    Type& Vector2<Type>::operator[](int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < 2, "Vector2 out of bounds acces");
        return mData[index];
    }


    /// <summary>
    /// Const subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    Type Vector2<Type>::operator[](int index) const
    {
        ETLMATH_ASSERT(index >= 0 && index < 2, "Vector2 out of bounds acces");
        return mData[index];
    }


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
    /// Vector lenght squared
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    Type Vector2<Type>::lengthSquared() const
    {
        return mX * mX + mY * mY;
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


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Vector2<Type>::operator+(const Vector2& other) const
    {
        return Vector2<Type>{ mX + other.mX,
                              mY + other.mY };
    }


    /// <summary>
    /// Substraction operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Vector2<Type>::operator-(const Vector2& other) const
    {
        return Vector2<Type>{ mX - other.mX,
                              mY - other.mY };
    }


    /// <summary>
    /// Multiplication operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Vector2<Type>::operator*(Type scalar) const
    {
        return Vector2<Type>{ mX * scalar,
                              mY * scalar };
    }


    /// <summary>
    /// Division operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type> Vector2<Type>::operator/(Type scalar) const
    {
        ETLMATH_ASSERT(!isZero(scalar), "Vector2 division by 0");

        if constexpr (std::is_floating_point_v<Type>)
        {
            const Type inv = Type(1) / scalar;
            return Vector2<Type>{ mX * inv, mY * inv };
        }
        else
        {
            /// integer division, divide to avoid truncation errors
            return Vector2<Type>{ mX / scalar, mY / scalar };
        }
    }


    /// <summary>
    /// Addition assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type>& Vector2<Type>::operator+=(const Vector2& other)
    {
        mX += other.mX;
        mY += other.mY;
        return *this;
    }


    /// <summary>
    /// Substraction assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type>& Vector2<Type>::operator-=(const Vector2& other)
    {
        mX -= other.mX;
        mY -= other.mY;
        return *this;
    }


    /// <summary>
    /// Multiplication assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type>& Vector2<Type>::operator*=(Type scalar)
    {
        mX *= scalar;
        mY *= scalar;
        return *this;
    }


    /// <summary>
    /// Division assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    Vector2<Type>& Vector2<Type>::operator/=(Type scalar)
    {
        ETLMATH_ASSERT(!isZero(scalar), "Vector2 division by 0");

        if constexpr (std::is_floating_point_v<Type>)
        {
            const Type inv = Type(1) / scalar;
            mX *= inv;
            mY *= inv;
        }
        else
        {
            /// integer division, divide to avoid truncation errors
            mX /= scalar;
            mY /= scalar;
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
    bool Vector2<Type>::operator==(const Vector2<Type>& other) const
    {
        return std::equal(mData, mData + 2, other.mData);
    }


    /// <summary>
    /// Inequality operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    bool Vector2<Type>::operator!=(const Vector2<Type>& other) const
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
    Vector2<Type> operator*(Type scalar, const Vector2<Type>& vector)
    {
        return vector * scalar;
    }


    /// <summary>
    /// 2D "Cross product" of V1 x V2
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    /// <returns></returns>
    template<typename Type>
    Type cross(const Vector2<Type>& v1, const Vector2<Type>& v2)
    {
        return v1.x() * v2.y() - v1.y() * v2.x();
    }


    /// <summary>
    /// Dot product V1*V2
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    /// <returns></returns>
    template<typename Type>
    Type dot(const Vector2<Type>& v1, const Vector2<Type>& v2)
    {
        return v1.x() * v2.x() + v1.y() * v2.y();
    }


    /// Explicit template instantiation (precompiled declaration)
    template class Vector2<float>;
    template class Vector2<double>;
    template class Vector2<int>;

    template Vector2<float>  operator*(float  scalar, const Vector2<float>&  vector);
    template Vector2<double> operator*(double scalar, const Vector2<double>& vector);
    template Vector2<int>    operator*(int    scalar, const Vector2<int>&    vector);

    template float  cross(const Vector2<float>&  v1, const Vector2<float>&  v2);
    template double cross(const Vector2<double>& v1, const Vector2<double>& v2);
    template int    cross(const Vector2<int>&    v1, const Vector2<int>&    v2);

    template float  dot(const Vector2<float>&  v1, const Vector2<float>&  v2);
    template double dot(const Vector2<double>& v1, const Vector2<double>& v2);
    template int    dot(const Vector2<int>&    v1, const Vector2<int>&    v2);

} /// namespace ETL::Math
