///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector3.inl
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
    /// X component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::x() const
    {
        return mX;
    }


    /// <summary>
    /// Y component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::y() const
    {
        return mY;
    }


    /// <summary>
    /// Z component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::z() const
    {
        return mZ;
    }


    /// <summary>
    /// X component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    template<typename Type>
    inline void Vector3<Type>::x(Type x)
    {
        mX = x;
    }


    /// <summary>
    /// Y component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="y"></param>
    template<typename Type>
    inline void Vector3<Type>::y(Type y)
    {
        mY = y;
    }


    /// <summary>
    /// Z component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="z"></param>
    template<typename Type>
    inline void Vector3<Type>::z(Type z)
    {
        mZ = z;
    }


    /// <summary>
    /// Vector length squared
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::lengthSquared() const
    {
        return mX * mX + mY * mY + mZ * mZ;
    }


    /// <summary>
    /// Subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type& Vector3<Type>::operator[](int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < 3, "Vector3 out of bounds access");
        return mData[index];
    }


    /// <summary>
    /// Const subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::operator[](int index) const
    {
        ETLMATH_ASSERT(index >= 0 && index < 3, "Vector3 out of bounds access");
        return mData[index];
    }


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::operator+(const Vector3& other) const
    {
        return Vector3<Type>{ mX + other.mX, mY + other.mY, mZ + other.mZ };
    }


    /// <summary>
    /// Subtraction operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::operator-(const Vector3& other) const
    {
        return Vector3<Type>{ mX - other.mX, mY - other.mY, mZ - other.mZ };
    }


    /// <summary>
    /// Multiplication operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::operator*(Type scalar) const
    {
        return Vector3<Type>{ mX * scalar, mY * scalar, mZ * scalar };
    }


    /// <summary>
    /// Division operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::operator/(Type scalar) const
    {
        ETLMATH_ASSERT(!isZero(scalar), "Vector3 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            return Vector3<Type>{ mX / scalar, mY / scalar, mZ / scalar };
        }
        else
        {
            const Type inv = Type(1) / scalar;
            return Vector3<Type>{ mX * inv, mY * inv, mZ * inv };
        }
    }


    /// <summary>
    /// Addition assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type>& Vector3<Type>::operator+=(const Vector3& other)
    {
        mX += other.mX;
        mY += other.mY;
        mZ += other.mZ;
        return *this;
    }


    /// <summary>
    /// Subtraction assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type>& Vector3<Type>::operator-=(const Vector3& other)
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
    inline Vector3<Type>& Vector3<Type>::operator*=(Type scalar)
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
    inline Vector3<Type>& Vector3<Type>::operator/=(Type scalar)
    {
        ETLMATH_ASSERT(!isZero(scalar), "Vector3 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            mX /= scalar;
            mY /= scalar;
            mZ /= scalar;
        }
        else
        {
            const Type inv = Type(1) / scalar;
            mX *= inv;
            mY *= inv;
            mZ *= inv;
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
    inline bool Vector3<Type>::operator==(const Vector3<Type>& other) const
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
    inline bool Vector3<Type>::operator!=(const Vector3<Type>& other) const
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
    inline Vector3<Type> operator*(Type scalar, const Vector3<Type>& vector)
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
    inline Vector3<Type> cross(const Vector3<Type>& v1, const Vector3<Type>& v2)
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
    inline Type dot(const Vector3<Type>& v1, const Vector3<Type>& v2)
    {
        return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
    }

} /// namespace ETL::Math
