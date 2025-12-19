///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector3.inl
///----------------------------------------------------------------------------

#include "MathLib/Common/Asserts.h"
#include "MathLib/Common/TypeComparisons.h"
#include <algorithm>
#include <cmath>

namespace ETL::Math
{

    /// <summary>
    /// Same value constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="val"></param>
    template<typename Type>
    constexpr Vector3<Type>::Vector3(Type val)
        : mData{ EncodeValue<Type>(val), EncodeValue<Type>(val), EncodeValue<Type>(val) }
    {
    }


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="z"></param>
    template<typename Type>
    constexpr Vector3<Type>::Vector3(Type x, Type y, Type z)
        : mData{ EncodeValue<Type>(x), EncodeValue<Type>(y), EncodeValue<Type>(z) }
    {
    }


    /// <summary>
    /// Explicit Raw constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name=""></param>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="z"></param>
    template<typename Type>
    constexpr Vector3<Type>::Vector3(RawTag, Type x, Type y, Type z)
        : mData{ x, y, z }
    {
    }


    /// <summary>
    /// X component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::x() const
    {
        return DecodeValue<Type>(mX);
    }


    /// <summary>
    /// Y component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::y() const
    {
        return DecodeValue<Type>(mY);
    }


    /// <summary>
    /// Z component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::z() const
    {
        return DecodeValue<Type>(mZ);
    }


    /// <summary>
    /// X component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    template<typename Type>
    inline void Vector3<Type>::x(Type x)
    {
        mX = EncodeValue<Type>(x);
    }


    /// <summary>
    /// Y component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="y"></param>
    template<typename Type>
    inline void Vector3<Type>::y(Type y)
    {
        mY = EncodeValue<Type>(y);
    }


    /// <summary>
    /// Z component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="z"></param>
    template<typename Type>
    inline void Vector3<Type>::z(Type z)
    {
        mZ = EncodeValue<Type>(z);
    }


    /// <summary>
    /// Subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline ElementProxy<Type> Vector3<Type>::operator[](int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < 3, "Vector3 out of bounds access");
        return ElementProxy<Type>{ mData[index] };
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
        return DecodeValue<Type>(mData[index]);
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
        return Vector3<Type>{ Raw, mX + other.mX, mY + other.mY, mZ + other.mZ };
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
        return Vector3<Type>{ Raw, mX - other.mX, mY - other.mY, mZ - other.mZ };
    }


    /// <summary>
    /// Dot Product operator (this * other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::operator*(const Vector3<Type>& other) const
    {
        Type result;
        Dot(result, *this, other);
        return result;
    }


    /// <summary>
    /// Cross product operator (this ^ other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::operator^(const Vector3<Type>& other) const
    {
        Vector3<Type> result;
        Cross(result, *this, other);
        return result;
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
        return Vector3<Type>{ Raw, mX * scalar, mY * scalar, mZ * scalar };
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
            return Vector3<Type>{ Raw, mX / scalar, mY / scalar, mZ / scalar };
        }
        else
        {
            const Type inv = Type(1) / scalar;
            return Vector3<Type>{ Raw, mX * inv, mY * inv, mZ * inv };
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
    /// Component Multiplication
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::componentMul(const Vector3<Type>& other) const
    {
        Vector3<Type> result;
        ComponentMul(result, *this, other);
        return result;
    }


    /// <summary>
    /// Component Division
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::componentDiv(const Vector3<Type>& other) const
    {
        Vector3<Type> result;
        ComponentDiv(result, *this, other);
        return result;
    }


    /// <summary>
    /// In Place Component Multiplication
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    template<typename Type>
    inline void Vector3<Type>::componentMulInPlace(const Vector3<Type>& other)
    {
        ComponentMul(*this, *this, other);
    }


    /// <summary>
    /// In Place Component Division
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    template<typename Type>
    inline void Vector3<Type>::componentDivInPlace(const Vector3<Type>& other)
    {
        ComponentDiv(*this, *this, other);
    }


    /// <summary>
    /// Dot product (this * other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::dot(const Vector3<Type>& other) const
    {
        Type result;
        Dot(result, *this, other);
        return result;
    }


    /// <summary>
    /// Cross product (this ^ other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::cross(const Vector3<Type>& other) const
    {
        Vector3<Type> result;
        Cross(result, *this, other);
        return result;
    }


    /// <summary>
    /// Vector length
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline double Vector3<Type>::length() const
    {
        double result;
        Length(result, *this);
        return result;
    }


    /// <summary>
    /// Vector length squared
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline double Vector3<Type>::lengthSquared() const
    {
        double result;
        LengthSquared(result, *this);
        return result;
    }


    /// <summary>
    /// Get a normalized copy of this vector
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector3<Type>::normalize() const
    {
        Vector3<Type> result;
        Normalize(result, *this);
        return result;
    }


    /// <summary>
    /// Normalize self
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type>& Vector3<Type>::makeNormalize()
    {
        Normalize(*this, *this);
        return *this;
    }


    /// <summary>
    /// Raw access to vector elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector3<Type>::getRawValue(int index) const
    {
        ETLMATH_ASSERT(index >= 0 && index < 3, "Vector3 out of bounds raw access");
        return mData[index];
    }


    /// <summary>
    /// Raw access to vector elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Vector3<Type>::setRawValue(int index, Type value)
    {
        ETLMATH_ASSERT(index >= 0 && index < 3, "Vector3 out of bounds raw access");
        mData[index] = value;
    }


    ///------------------------------------------------------------------------------------------
    /// Free functions - implement logic

    /// <summary>
    /// Component-wise multiplication
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    template<typename Type>
    inline void ComponentMul(Vector3<Type>& outResult, const Vector3<Type>& v1, const Vector3<Type>& v2)
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(v1.getRawValue(0)) * v2.getRawValue(0);
            const int64_t y = static_cast<int64_t>(v1.getRawValue(1)) * v2.getRawValue(1);
            const int64_t z = static_cast<int64_t>(v1.getRawValue(2)) * v2.getRawValue(2);
            outResult.setRawValue(0, static_cast<Type>(x >> FIXED_SHIFT));
            outResult.setRawValue(1, static_cast<Type>(y >> FIXED_SHIFT));
            outResult.setRawValue(2, static_cast<Type>(z >> FIXED_SHIFT));
        }
        else
        {
            outResult.setRawValue(0, v1.getRawValue(0) * v2.getRawValue(0));
            outResult.setRawValue(1, v1.getRawValue(1) * v2.getRawValue(1));
            outResult.setRawValue(2, v1.getRawValue(2) * v2.getRawValue(2));
        }
    }


    /// <summary>
    /// Component-wise division
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    template<typename Type>
    inline void ComponentDiv(Vector3<Type>& outResult, const Vector3<Type>& v1, const Vector3<Type>& v2)
    {
        ETLMATH_ASSERT(!isZero(v2.getRawValue(0)) && !isZero(v2.getRawValue(1)) && !isZero(v2.getRawValue(2)),
                       "Division by 0 in ComponentDiv (Vector2)");

        if constexpr (std::integral<Type>)
        {
            /// Scale dividend to avoid integer rounding. Result will be descaled to FX
            /// Dividend(FX^2) / Divisor(FX) = Result(FX)
            const int64_t x = (static_cast<int64_t>(v1.getRawValue(0)) << FIXED_SHIFT) / v2.getRawValue(0);
            const int64_t y = (static_cast<int64_t>(v1.getRawValue(1)) << FIXED_SHIFT) / v2.getRawValue(1);
            const int64_t z = (static_cast<int64_t>(v1.getRawValue(2)) << FIXED_SHIFT) / v2.getRawValue(2);
            outResult.setRawValue(0, static_cast<Type>(x));
            outResult.setRawValue(1, static_cast<Type>(y));
            outResult.setRawValue(2, static_cast<Type>(z));
        }
        else
        {
            outResult.setRawValue(0, v1.getRawValue(0) / v2.getRawValue(0));
            outResult.setRawValue(1, v1.getRawValue(1) / v2.getRawValue(1));
            outResult.setRawValue(2, v1.getRawValue(2) / v2.getRawValue(2));
        }
    }


    /// <summary>
    /// Dot product V1*V2
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    template<typename Type>
    inline void Dot(Type& outResult, const Vector3<Type>& v1, const Vector3<Type>& v2)
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t dot = static_cast<int64_t>(v1.getRawValue(0)) * v2.getRawValue(0)
                              + static_cast<int64_t>(v1.getRawValue(1)) * v2.getRawValue(1)
                              + static_cast<int64_t>(v1.getRawValue(2)) * v2.getRawValue(2);
            outResult = static_cast<Type>(dot >> (2 * FIXED_SHIFT));
        }
        else
        {
            outResult = v1.getRawValue(0) * v2.getRawValue(0)
                      + v1.getRawValue(1) * v2.getRawValue(1)
                      + v1.getRawValue(2) * v2.getRawValue(2);
        }
    }


    /// <summary>
    /// Cross product V1xV2
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    template<typename Type>
    inline void Cross(Vector3<Type>& outResult, const Vector3<Type>& v1, const Vector3<Type>& v2)
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(v1.getRawValue(1)) * v2.getRawValue(2)
                            - static_cast<int64_t>(v1.getRawValue(2)) * v2.getRawValue(1);
            const int64_t y = static_cast<int64_t>(v1.getRawValue(2)) * v2.getRawValue(0)
                            - static_cast<int64_t>(v1.getRawValue(0)) * v2.getRawValue(2);
            const int64_t z = static_cast<int64_t>(v1.getRawValue(0)) * v2.getRawValue(1)
                            - static_cast<int64_t>(v1.getRawValue(1)) * v2.getRawValue(0);

            outResult.setRawValue(0, static_cast<Type>(x >> FIXED_SHIFT));
            outResult.setRawValue(1, static_cast<Type>(y >> FIXED_SHIFT));
            outResult.setRawValue(2, static_cast<Type>(z >> FIXED_SHIFT));
        }
        else
        {
            const Type x = v1.getRawValue(1) * v2.getRawValue(2) - v1.getRawValue(2) * v2.getRawValue(1);
            const Type y = v1.getRawValue(2) * v2.getRawValue(0) - v1.getRawValue(0) * v2.getRawValue(2);
            const Type z = v1.getRawValue(0) * v2.getRawValue(1) - v1.getRawValue(1) * v2.getRawValue(0);

            outResult.setRawValue(0, x);
            outResult.setRawValue(1, y);
            outResult.setRawValue(2, z);
        }
    }


    /// <summary>
    /// Return length
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="vec"></param>
    template<typename Type>
    inline void Length(double& outResult, const Vector3<Type>& vec)
    {
        double lengthSq;
        LengthSquared(lengthSq, vec);
        outResult = std::sqrt(lengthSq);
    }


    /// <summary>
    /// Return length squared
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="vec"></param>
    template<typename Type>
    inline void LengthSquared(double& outResult, const Vector3<Type>& vec)
    {
        if constexpr (std::integral<Type>)
        {
            const double x = static_cast<double>(vec.getRawValue(0)) / FIXED_ONE;
            const double y = static_cast<double>(vec.getRawValue(1)) / FIXED_ONE;
            const double z = static_cast<double>(vec.getRawValue(2)) / FIXED_ONE;
            outResult = x * x + y * y + z * z;
        }
        else
        {
            const double x = static_cast<double>(vec.getRawValue(0));
            const double y = static_cast<double>(vec.getRawValue(1));
            const double z = static_cast<double>(vec.getRawValue(2));
            outResult = x * x + y * y + z * z;
        }
    }


    /// <summary>
    /// Normalize vec
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="vec"></param>
    template<typename Type>
    inline bool Normalize(Vector3<Type>& outResult, const Vector3<Type>& vec)
    {
        double lengthSq;
        LengthSquared(lengthSq, vec);
        if (isZero(lengthSq))
            return false;

        const double invLength = 1.0 / std::sqrt(lengthSq);

        outResult.setRawValue(0, static_cast<Type>(vec.getRawValue(0) * invLength));
        outResult.setRawValue(1, static_cast<Type>(vec.getRawValue(1) * invLength));
        outResult.setRawValue(2, static_cast<Type>(vec.getRawValue(2) * invLength));

        return true;
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


} /// namespace ETL::Math
