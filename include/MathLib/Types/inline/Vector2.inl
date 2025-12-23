///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector2.inl
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
    constexpr Vector2<Type>::Vector2(Type val)
        : mData{ EncodeValue<Type>(val), EncodeValue<Type>(val) }
    {
    }


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    constexpr Vector2<Type>::Vector2(Type x, Type y)
        : mData{ EncodeValue<Type>(x), EncodeValue<Type>(y) }
    {
    }


    /// <summary>
    /// Explicit constructor from double (allows fixed point setup to non integral values)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    constexpr Vector2<Type>::Vector2(double x, double y) requires (!std::same_as<Type, double>)
        : mData{ EncodeValue<Type>(x), EncodeValue<Type>(y) }
    {
    }


    /// <summary>
    /// Explicit Raw Constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name=""></param>
    /// <param name="x"></param>
    /// <param name="y"></param>
    template<typename Type>
    constexpr Vector2<Type>::Vector2(RawTag, Type x, Type y)
        : mData{ x, y }
    {
    }


    /// <summary>
    /// X component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector2<Type>::x() const
    {
        return DecodeValue<Type>(mX);
    }


    /// <summary>
    /// Y component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector2<Type>::y() const
    {
        return DecodeValue<Type>(mY);
    }


    /// <summary>
    /// X component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    template<typename Type>
    inline void Vector2<Type>::x(Type x)
    {
        mX = EncodeValue<Type>(x);
    }


    /// <summary>
    /// Y component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="y"></param>
    template<typename Type>
    inline void Vector2<Type>::y(Type y)
    {
        mY = EncodeValue<Type>(y);
    }


    /// <summary>
    /// Subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline ElementProxy<Type> Vector2<Type>::operator[](int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < 2, "Vector2 out of bounds access");
        return ElementProxy<Type>{ mData[index] };
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
        return DecodeValue<Type>(mData[index]);
    }


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type> Vector2<Type>::operator+(const Vector2<Type>& other) const
    {
        return Vector2<Type>{ Raw, mX + other.mX, mY + other.mY };
    }


    /// <summary>
    /// Subtraction operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type> Vector2<Type>::operator-(const Vector2<Type>& other) const
    {
        return Vector2<Type>{ Raw, mX - other.mX, mY - other.mY };
    }


    /// <summary>
    /// Dot Product operator (this * other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline double Vector2<Type>::operator*(const Vector2<Type>& other) const
    {
        double result;
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
    inline double Vector2<Type>::operator^(const Vector2<Type>& other) const
    {
        double result;
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
    inline Vector2<Type> Vector2<Type>::operator*(Type scalar) const
    {
        return Vector2<Type>{ Raw, mX * scalar, mY * scalar };
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
        ETLMATH_ASSERT(!isZeroRaw(scalar), "Vector2 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            return Vector2<Type>{ Raw, mX / scalar, mY / scalar };
        }
        else
        {
            const Type inv = Type(1) / scalar;
            return Vector2<Type>{ Raw, mX * inv, mY * inv };
        }
    }


    /// <summary>
    /// Minus operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type> Vector2<Type>::operator-() const
    {
        return Vector2<Type>{ Raw, -mX, -mY };
    }


    /// <summary>
    /// Addition assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type>& Vector2<Type>::operator+=(const Vector2<Type>& other)
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
    inline Vector2<Type>& Vector2<Type>::operator-=(const Vector2<Type>& other)
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
        ETLMATH_ASSERT(!isZeroRaw(scalar), "Vector2 division by 0");

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
    /// Component Multiplication
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type> Vector2<Type>::componentMul(const Vector2<Type>& other) const
    {
        Vector2<Type> result;
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
    inline Vector2<Type> Vector2<Type>::componentDiv(const Vector2<Type>& other) const
    {
        Vector2<Type> result;
        ComponentDiv(result, *this, other);
        return result;
    }


    /// <summary>
    /// In Place Component Multiplication
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    template<typename Type>
    inline void Vector2<Type>::componentMulInPlace(const Vector2<Type>& other)
    {
        ComponentMul(*this, *this, other);
    }


    /// <summary>
    /// In Place Component Division
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    template<typename Type>
    inline void Vector2<Type>::componentDivInPlace(const Vector2<Type>& other)
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
    inline double Vector2<Type>::dot(const Vector2<Type>& other) const
    {
        double result;
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
    inline double Vector2<Type>::cross(const Vector2<Type>& other) const
    {
        double result;
        Cross(result, *this, other);
        return result;
    }


    /// <summary>
    /// Vector length
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline double Vector2<Type>::length() const
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
    inline double Vector2<Type>::lengthSquared() const
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
    inline Vector2<Type> Vector2<Type>::normalize() const
    {
        Vector2<Type> result;
        Normalize(result, *this);
        return result;
    }


    /// <summary>
    /// Normalize self
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector2<Type>& Vector2<Type>::makeNormalize()
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
    inline Type Vector2<Type>::getRawValue(int index) const
    {
        ETLMATH_ASSERT(index >= 0 && index < 2, "Vector2 out of bounds raw access");
        return mData[index];
    }


    /// <summary>
    /// Raw access to vector elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Vector2<Type>::setRawValue(int index, Type value)
    {
        ETLMATH_ASSERT(index >= 0 && index < 2, "Vector2 out of bounds raw access");
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
    inline void ComponentMul(Vector2<Type>& outResult, const Vector2<Type>& v1, const Vector2<Type>& v2)
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(v1.getRawValue(0)) * v2.getRawValue(0);
            const int64_t y = static_cast<int64_t>(v1.getRawValue(1)) * v2.getRawValue(1);
            outResult.setRawValue(0, static_cast<Type>(x >> FIXED_SHIFT));
            outResult.setRawValue(1, static_cast<Type>(y >> FIXED_SHIFT));
        }
        else
        {
            outResult.setRawValue(0, v1.getRawValue(0) * v2.getRawValue(0));
            outResult.setRawValue(1, v1.getRawValue(1) * v2.getRawValue(1));
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
    inline void ComponentDiv(Vector2<Type>& outResult, const Vector2<Type>& v1, const Vector2<Type>& v2)
    {
        ETLMATH_ASSERT(!isZero(v2.getRawValue(0)) && !isZero(v2.getRawValue(1)), "Division by 0 in ComponentDiv (Vector2)");

        if constexpr (std::integral<Type>)
        {
            /// Scale dividend to avoid integer rounding. Result will be descaled to FX
            /// Dividend(FX^2) / Divisor(FX) = Result(FX)
            const int64_t x = (static_cast<int64_t>(v1.getRawValue(0)) << FIXED_SHIFT) / v2.getRawValue(0);
            const int64_t y = (static_cast<int64_t>(v1.getRawValue(1)) << FIXED_SHIFT) / v2.getRawValue(1);
            outResult.setRawValue(0, static_cast<Type>(x));
            outResult.setRawValue(1, static_cast<Type>(y));
        }
        else
        {
            outResult.setRawValue(0, v1.getRawValue(0) / v2.getRawValue(0));
            outResult.setRawValue(1, v1.getRawValue(1) / v2.getRawValue(1));
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
    inline void Dot(double& outResult, const Vector2<Type>& v1, const Vector2<Type>& v2)
    {
        //constexpr int fixedPointScale = std::integral<Type> ? FIXED_ONE : 1;
        //const double x1 = static_cast<double>(v1.getRawValue(0)) / fixedPointScale;
        //const double y1 = static_cast<double>(v1.getRawValue(1)) / fixedPointScale;
        //const double x2 = static_cast<double>(v2.getRawValue(0)) / fixedPointScale;
        //const double y2 = static_cast<double>(v2.getRawValue(1)) / fixedPointScale;
        //outResult = x1 * x2 + y1 * y2;

        if constexpr (std::integral<Type>)
        {
            const double x1 = static_cast<double>(v1.getRawValue(0)) / FIXED_ONE;
            const double y1 = static_cast<double>(v1.getRawValue(1)) / FIXED_ONE;
            const double x2 = static_cast<double>(v2.getRawValue(0)) / FIXED_ONE;
            const double y2 = static_cast<double>(v2.getRawValue(1)) / FIXED_ONE;
            outResult = x1 * x2 + y1 * y2;
        }
        else
        {
            const double x1 = static_cast<double>(v1.getRawValue(0));
            const double y1 = static_cast<double>(v1.getRawValue(1));
            const double x2 = static_cast<double>(v2.getRawValue(0));
            const double y2 = static_cast<double>(v2.getRawValue(1));
            outResult = x1 * x2 + y1 * y2;
        }
    }


    /// <summary>
    /// 2D "Cross product" of V1 x V2
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="v1"></param>
    /// <param name="v2"></param>
    template<typename Type>
    inline void Cross(double& outResult, const Vector2<Type>& v1, const Vector2<Type>& v2)
    {
        if constexpr (std::integral<Type>)
        {
            const double x1 = static_cast<double>(v1.getRawValue(0)) / FIXED_ONE;
            const double y1 = static_cast<double>(v1.getRawValue(1)) / FIXED_ONE;
            const double x2 = static_cast<double>(v2.getRawValue(0)) / FIXED_ONE;
            const double y2 = static_cast<double>(v2.getRawValue(1)) / FIXED_ONE;
            outResult = x1 * y2 - y1 * x2;
        }
        else
        {
            const double x1 = static_cast<double>(v1.getRawValue(0));
            const double y1 = static_cast<double>(v1.getRawValue(1));
            const double x2 = static_cast<double>(v2.getRawValue(0));
            const double y2 = static_cast<double>(v2.getRawValue(1));
            outResult = x1 * y2 - y1 * x2;
        }
    }


    /// <summary>
    /// Return length
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="vec"></param>
    template<typename Type>
    inline void Length(double& outResult, const Vector2<Type>& vec)
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
    inline void LengthSquared(double& outResult, const Vector2<Type>& vec)
    {
        Dot(outResult, vec, vec);
    }


    /// <summary>
    /// Normalize vec
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="vec"></param>
    template<typename Type>
    inline bool Normalize(Vector2<Type>& outResult, const Vector2<Type>& vec)
    {
        double lengthSq;
        LengthSquared(lengthSq, vec);
        if (isZero(lengthSq))
            return false;

        const double invLength = 1.0 / std::sqrt(lengthSq);

        outResult.setRawValue(0, static_cast<Type>(vec.getRawValue(0) * invLength));
        outResult.setRawValue(1, static_cast<Type>(vec.getRawValue(1) * invLength));

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
    inline Vector2<Type> operator*(Type scalar, const Vector2<Type>& vector)
    {
        return vector * scalar;
    }


} /// namespace ETL::Math
