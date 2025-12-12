///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector2.inl
///----------------------------------------------------------------------------

#include "MathLib/Common/Common.h"
#include "MathLib/Common/TypeComparisons.h"
#include <algorithm>

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
    /// X component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector2<Type>::x() const
    {
        return mX;
    }


    /// <summary>
    /// Y component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector2<Type>::y() const
    {
        return mY;
    }


    /// <summary>
    /// X component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    template<typename Type>
    inline void Vector2<Type>::x(Type x)
    {
        mX = x;
    }


    /// <summary>
    /// Y component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="y"></param>
    template<typename Type>
    inline void Vector2<Type>::y(Type y)
    {
        mY = y;
    }


    /// <summary>
    /// Vector length squared
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector2<Type>::lengthSquared() const
    {
        return mX * mX + mY * mY;
    }


    /// <summary>
    /// Subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type& Vector2<Type>::operator[](int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < 2, "Vector2 out of bounds access");
        return mData[index];
    }


    /// <summary>
    /// Const subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector2<Type>::operator[](int index) const
    {
        ETLMATH_ASSERT(index >= 0 && index < 2, "Vector2 out of bounds access");
        return mData[index];
    }


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type> Vector2<Type>::operator+(const Vector2& other) const
    {
        return Vector2<Type>{ mX + other.mX, mY + other.mY };
    }


    /// <summary>
    /// Subtraction operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type> Vector2<Type>::operator-(const Vector2& other) const
    {
        return Vector2<Type>{ mX - other.mX, mY - other.mY };
    }


    /// <summary>
    /// Multiplication operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type> Vector2<Type>::operator*(Type scalar) const
    {
        return Vector2<Type>{ mX * scalar, mY * scalar };
    }


    /// <summary>
    /// Division operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type> Vector2<Type>::operator/(Type scalar) const
    {
        ETLMATH_ASSERT(!isZero(scalar), "Vector2 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            return Vector2<Type>{ mX / scalar, mY / scalar };
        }
        else
        {
            const Type inv = Type(1) / scalar;
            return Vector2<Type>{ mX * inv, mY * inv };
        }
    }


    /// <summary>
    /// Addition assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type>& Vector2<Type>::operator+=(const Vector2& other)
    {
        mX += other.mX;
        mY += other.mY;
        return *this;
    }


    /// <summary>
    /// Subtraction assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type>& Vector2<Type>::operator-=(const Vector2& other)
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
    inline Vector2<Type>& Vector2<Type>::operator*=(Type scalar)
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
    inline Vector2<Type>& Vector2<Type>::operator/=(Type scalar)
    {
        ETLMATH_ASSERT(!isZero(scalar), "Vector2 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            mX /= scalar;
            mY /= scalar;
        }
        else
        {
            const Type inv = Type(1) / scalar;
            mX *= inv;
            mY *= inv;
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
    inline bool Vector2<Type>::operator==(const Vector2<Type>& other) const
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
    inline bool Vector2<Type>::operator!=(const Vector2<Type>& other) const
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
    inline Vector2<Type> operator*(Type scalar, const Vector2<Type>& vector)
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
    inline Type cross(const Vector2<Type>& v1, const Vector2<Type>& v2)
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
    inline Type dot(const Vector2<Type>& v1, const Vector2<Type>& v2)
    {
        return v1.x() * v2.x() + v1.y() * v2.y();
    }

} /// namespace ETL::Math
