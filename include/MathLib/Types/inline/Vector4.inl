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
    constexpr Vector4<Type>::Vector4(Type val)
        : mData{ EncodeValue<Type>(val), EncodeValue<Type>(val), EncodeValue<Type>(val), EncodeValue<Type>(val) }
    {
    }


    /// <summary>
    /// Explicit constructor
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="z"></param>
    /// <param name="w"></param>
    template<typename Type>
    constexpr Vector4<Type>::Vector4(Type x, Type y, Type z, Type w)
        : mData{ EncodeValue<Type>(x), EncodeValue<Type>(y), EncodeValue<Type>(z), EncodeValue<Type>(w) }
    {
    }


    /// <summary>
    /// Explicit constructor from double (allows fixed point setup to non integral values)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="z"></param>
    /// <param name="w"></param>
    template<typename Type>
    constexpr Vector4<Type>::Vector4(double x, double y, double z, double w) requires (!std::same_as<Type, double>)
        : mData{ EncodeValue<Type>(x), EncodeValue<Type>(y), EncodeValue<Type>(z), EncodeValue<Type>(w) }
    {
    }


    /// <summary>
    /// Constructor from Vector3
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="xyz"></param>
    /// <param name="w"></param>
    template<typename Type>
    constexpr Vector4<Type>::Vector4(const Vector3<Type>& xyz, Type w /*= Type(1)*/)
        : mData{ xyz.getRawValue(0), xyz.getRawValue(1), xyz.getRawValue(2), EncodeValue<Type>(w) }
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
    /// <param name="w"></param>
    template<typename Type>
    constexpr Vector4<Type>::Vector4(RawTag, Type x, Type y, Type z, Type w)
        : mData{ x, y, z, w }
    {
    }


    /// <summary>
    /// X component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector4<Type>::x() const
    {
        return DecodeValue<Type>(mX);
    }


    /// <summary>
    /// Y component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector4<Type>::y() const
    {
        return DecodeValue<Type>(mY);
    }


    /// <summary>
    /// Z component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector4<Type>::z() const
    {
        return DecodeValue<Type>(mZ);
    }


    /// <summary>
    /// W component getter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector4<Type>::w() const
    {
        return DecodeValue<Type>(mW);
    }


    /// <summary>
    /// X component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="x"></param>
    template<typename Type>
    inline void Vector4<Type>::x(Type x)
    {
        mX = EncodeValue<Type>(x);
    }


    /// <summary>
    /// Y component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="y"></param>
    template<typename Type>
    inline void Vector4<Type>::y(Type y)
    {
        mY = EncodeValue<Type>(y);
    }


    /// <summary>
    /// Z component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="z"></param>
    template<typename Type>
    inline void Vector4<Type>::z(Type z)
    {
        mZ = EncodeValue<Type>(z);
    }


    /// <summary>
    /// W component setter
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="z"></param>
    template<typename Type>
    inline void Vector4<Type>::w(Type w)
    {
        mW = EncodeValue<Type>(w);
    }


    /// <summary>
    /// Subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline ElementProxy<Type> Vector4<Type>::operator[](int index)
    {
        ETLMATH_ASSERT(index >= 0 && index < 4, "Vector4 out of bounds access");
        return ElementProxy<Type>{ mData[index] };
    }


    /// <summary>
    /// Const subscript operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector4<Type>::operator[](int index) const
    {
        ETLMATH_ASSERT(index >= 0 && index < 4, "Vector4 out of bounds access");
        return DecodeValue<Type>(mData[index]);
    }


    /// <summary>
    /// Addition operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type> Vector4<Type>::operator+(const Vector4& other) const
    {
        return Vector4<Type>{ Raw, mX + other.mX, mY + other.mY, mZ + other.mZ, mW + other.mW };
    }


    /// <summary>
    /// Subtraction operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type> Vector4<Type>::operator-(const Vector4& other) const
    {
        return Vector4<Type>{ Raw, mX - other.mX, mY - other.mY, mZ - other.mZ, mW - other.mW  };
    }


    /// <summary>
    /// Dot Product operator (this * other)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline double Vector4<Type>::operator*(const Vector4<Type>& other) const
    {
        double result;
        Dot(result, *this, other);
        return result;
    }


    /// <summary>
    /// Multiplication operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type> Vector4<Type>::operator*(Type scalar) const
    {
        return Vector4<Type>{ Raw, mX * scalar, mY * scalar, mZ * scalar, mW* scalar };
    }


    /// <summary>
    /// Division operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type> Vector4<Type>::operator/(Type scalar) const
    {
        ETLMATH_ASSERT(!isZeroRaw(scalar), "Vector3 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            return Vector4<Type>{ Raw, mX / scalar, mY / scalar, mZ / scalar, mW / scalar };
        }
        else
        {
            const Type inv = Type(1) / scalar;
            return Vector4<Type>{ Raw, mX * inv, mY * inv, mZ * inv, mW * inv };
        }
    }


    /// <summary>
    /// Minus operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type> Vector4<Type>::operator-() const
    {
        return Vector4<Type>{ Raw, -mX, -mY, -mZ, -mW };
    }


    /// <summary>
    /// Addition assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type>& Vector4<Type>::operator+=(const Vector4& other)
    {
        mX += other.mX;
        mY += other.mY;
        mZ += other.mZ;
        mW += other.mW;
        return *this;
    }


    /// <summary>
    /// Subtraction assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type>& Vector4<Type>::operator-=(const Vector4& other)
    {
        mX -= other.mX;
        mY -= other.mY;
        mZ -= other.mZ;
        mW -= other.mW;
        return *this;
    }


    /// <summary>
    /// Multiplication assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type>& Vector4<Type>::operator*=(Type scalar)
    {
        mX *= scalar;
        mY *= scalar;
        mZ *= scalar;
        mW *= scalar;
        return *this;
    }


    /// <summary>
    /// Division assignment operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type>& Vector4<Type>::operator/=(Type scalar)
    {
        ETLMATH_ASSERT(!isZeroRaw(scalar), "Vector3 division by 0");

        if constexpr (std::integral<Type>)
        {
            /// integer division, divide to avoid truncation errors
            mX /= scalar;
            mY /= scalar;
            mZ /= scalar;
            mW /= scalar;
        }
        else
        {
            const Type inv = Type(1) / scalar;
            mX *= inv;
            mY *= inv;
            mZ *= inv;
            mW *= inv;
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
    inline bool Vector4<Type>::operator==(const Vector4<Type>& other) const
    {
        return std::equal(mData, mData + 4, other.mData);
    }


    /// <summary>
    /// Inequality operator
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    /// <returns></returns>
    template<typename Type>
    inline bool Vector4<Type>::operator!=(const Vector4<Type>& other) const
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
    inline Vector4<Type> Vector4<Type>::componentMul(const Vector4<Type>& other) const
    {
        Vector4<Type> result;
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
    inline Vector4<Type> Vector4<Type>::componentDiv(const Vector4<Type>& other) const
    {
        Vector4<Type> result;
        ComponentDiv(result, *this, other);
        return result;
    }


    /// <summary>
    /// In Place Component Multiplication
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    template<typename Type>
    inline void Vector4<Type>::componentMulInPlace(const Vector4<Type>& other)
    {
        ComponentMul(*this, *this, other);
    }


    /// <summary>
    /// In Place Component Division
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="other"></param>
    template<typename Type>
    inline void Vector4<Type>::componentDivInPlace(const Vector4<Type>& other)
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
    inline double Vector4<Type>::dot(const Vector4<Type>& other) const
    {
        double result;
        Dot(result, *this, other);
        return result;
    }


    /// <summary>
    /// Vector length
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline double Vector4<Type>::length() const
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
    inline double Vector4<Type>::lengthSquared() const
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
    inline Vector4<Type> Vector4<Type>::normalize() const
    {
        Vector4<Type> result;
        Normalize(result, *this);
        return result;
    }


    /// <summary>
    /// Normalize self
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type>& Vector4<Type>::makeNormalize()
    {
        Normalize(*this, *this);
        return *this;
    }


    /// <summary>
    /// Extract Vector3
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector4<Type>::toVector3() const
    {
        Vector3<Type> result;
        ToVector3(result, *this);
        return result;
    }


    /// <summary>
    /// Perspective divide
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline Vector3<Type> Vector4<Type>::perspectiveDivide() const
    {
        Vector3<Type> result;
        PerspectiveDivide(result, *this);
        return result;
    }


    /// <summary>
    /// Check if is Point
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline bool Vector4<Type>::isPoint() const
    {
        return isEqual(mW, EncodeValue<Type>(Type(1)));
    }


    /// <summary>
    /// Check if is Direction
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <returns></returns>
    template<typename Type>
    inline bool Vector4<Type>::isDirection() const
    {
        return isEqual(mW, EncodeValue<Type>(Type(0)));
    }


    /// <summary>
    /// Raw access to vector elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    inline Type Vector4<Type>::getRawValue(int index) const
    {
        ETLMATH_ASSERT(index >= 0 && index < 4, "Vector4 out of bounds raw access");
        return mData[index];
    }


    /// <summary>
    /// Raw access to vector elements (no fixed-point conversion)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="index"></param>
    /// <param name="value"></param>
    template<typename Type>
    inline void Vector4<Type>::setRawValue(int index, Type value)
    {
        ETLMATH_ASSERT(index >= 0 && index < 4, "Vector4 out of bounds raw access");
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
    inline void ComponentMul(Vector4<Type>& outResult, const Vector4<Type>& v1, const Vector4<Type>& v2)
    {
        if constexpr (std::integral<Type>)
        {
            const int64_t x = static_cast<int64_t>(v1.getRawValue(0)) * v2.getRawValue(0);
            const int64_t y = static_cast<int64_t>(v1.getRawValue(1)) * v2.getRawValue(1);
            const int64_t z = static_cast<int64_t>(v1.getRawValue(2)) * v2.getRawValue(2);
            const int64_t w = static_cast<int64_t>(v1.getRawValue(3)) * v2.getRawValue(3);
            outResult.setRawValue(0, static_cast<Type>(x >> FIXED_SHIFT));
            outResult.setRawValue(1, static_cast<Type>(y >> FIXED_SHIFT));
            outResult.setRawValue(2, static_cast<Type>(z >> FIXED_SHIFT));
            outResult.setRawValue(3, static_cast<Type>(w >> FIXED_SHIFT));
        }
        else
        {
            outResult.setRawValue(0, v1.getRawValue(0) * v2.getRawValue(0));
            outResult.setRawValue(1, v1.getRawValue(1) * v2.getRawValue(1));
            outResult.setRawValue(2, v1.getRawValue(2) * v2.getRawValue(2));
            outResult.setRawValue(3, v1.getRawValue(3) * v2.getRawValue(3));
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
    inline void ComponentDiv(Vector4<Type>& outResult, const Vector4<Type>& v1, const Vector4<Type>& v2)
    {
        ETLMATH_ASSERT(!isZero(v2.getRawValue(0)) && !isZero(v2.getRawValue(1)) &&
                       !isZero(v2.getRawValue(2)) && !isZero(v2.getRawValue(3)),
                       "Division by 0 in ComponentDiv (Vector4)");

        if constexpr (std::integral<Type>)
        {
            /// Scale dividend to avoid integer rounding. Result will be descaled to FX
            /// Dividend(FX^2) / Divisor(FX) = Result(FX)
            const int64_t x = (static_cast<int64_t>(v1.getRawValue(0)) << FIXED_SHIFT) / v2.getRawValue(0);
            const int64_t y = (static_cast<int64_t>(v1.getRawValue(1)) << FIXED_SHIFT) / v2.getRawValue(1);
            const int64_t z = (static_cast<int64_t>(v1.getRawValue(2)) << FIXED_SHIFT) / v2.getRawValue(2);
            const int64_t w = (static_cast<int64_t>(v1.getRawValue(3)) << FIXED_SHIFT) / v2.getRawValue(3);
            outResult.setRawValue(0, static_cast<Type>(x));
            outResult.setRawValue(1, static_cast<Type>(y));
            outResult.setRawValue(2, static_cast<Type>(z));
            outResult.setRawValue(3, static_cast<Type>(w));
        }
        else
        {
            outResult.setRawValue(0, v1.getRawValue(0) / v2.getRawValue(0));
            outResult.setRawValue(1, v1.getRawValue(1) / v2.getRawValue(1));
            outResult.setRawValue(2, v1.getRawValue(2) / v2.getRawValue(2));
            outResult.setRawValue(3, v1.getRawValue(3) / v2.getRawValue(3));
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
    inline void Dot(double& outResult, const Vector4<Type>& v1, const Vector4<Type>& v2)
    {
        if constexpr (std::integral<Type>)
        {
            const double x1 = static_cast<double>(v1.getRawValue(0)) / FIXED_ONE;
            const double y1 = static_cast<double>(v1.getRawValue(1)) / FIXED_ONE;
            const double z1 = static_cast<double>(v1.getRawValue(2)) / FIXED_ONE;
            const double w1 = static_cast<double>(v1.getRawValue(3)) / FIXED_ONE;
            const double x2 = static_cast<double>(v2.getRawValue(0)) / FIXED_ONE;
            const double y2 = static_cast<double>(v2.getRawValue(1)) / FIXED_ONE;
            const double z2 = static_cast<double>(v2.getRawValue(2)) / FIXED_ONE;
            const double w2 = static_cast<double>(v2.getRawValue(3)) / FIXED_ONE;
            outResult = x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2;
        }
        else
        {
            const double x1 = static_cast<double>(v1.getRawValue(0));
            const double y1 = static_cast<double>(v1.getRawValue(1));
            const double z1 = static_cast<double>(v1.getRawValue(2));
            const double w1 = static_cast<double>(v1.getRawValue(3));
            const double x2 = static_cast<double>(v2.getRawValue(0));
            const double y2 = static_cast<double>(v2.getRawValue(1));
            const double z2 = static_cast<double>(v2.getRawValue(2));
            const double w2 = static_cast<double>(v2.getRawValue(3));
            outResult = x1 * x2 + y1 * y2 + z1 * z2 + w1 * w2;
        }
    }


    /// <summary>
    /// Return length
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="vec"></param>
    template<typename Type>
    inline void Length(double& outResult, const Vector4<Type>& vec)
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
    inline void LengthSquared(double& outResult, const Vector4<Type>& vec)
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
    inline bool Normalize(Vector4<Type>& outResult, const Vector4<Type>& vec)
    {
        double lengthSq;
        LengthSquared(lengthSq, vec);
        if (isZero(lengthSq))
            return false;

        const double invLength = 1.0 / std::sqrt(lengthSq);

        outResult.setRawValue(0, static_cast<Type>(vec.getRawValue(0) * invLength));
        outResult.setRawValue(1, static_cast<Type>(vec.getRawValue(1) * invLength));
        outResult.setRawValue(2, static_cast<Type>(vec.getRawValue(2) * invLength));
        outResult.setRawValue(3, static_cast<Type>(vec.getRawValue(3) * invLength));

        return true;
    }


    /// <summary>
    /// Extract Vector3
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="vec"></param>
    template<typename Type>
    void ToVector3(Vector3<Type>& outResult, const Vector4<Type>& vec)
    {
        outResult.setRawValue(0, vec.getRawValue(0));
        outResult.setRawValue(1, vec.getRawValue(1));
        outResult.setRawValue(2, vec.getRawValue(2));
    }


    /// <summary>
    /// Pespective Divide (xyz / w)
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="outResult"></param>
    /// <param name="vec"></param>
    template<typename Type>
    void PerspectiveDivide(Vector3<Type>& outResult, const Vector4<Type>& vec)
    {
        ETLMATH_ASSERT(!isZero(vec.getRawValue(3)), "Division by 0 in PerspectiveDivide (Vector4 to Vector3)");

        if constexpr (std::integral<Type>)
        {
            const int64_t w = static_cast<int64_t>(vec.getRawValue(3));
            const int64_t x = (static_cast<int64_t>(vec.getRawValue(0)) << FIXED_SHIFT) / w;
            const int64_t y = (static_cast<int64_t>(vec.getRawValue(1)) << FIXED_SHIFT) / w;
            const int64_t z = (static_cast<int64_t>(vec.getRawValue(2)) << FIXED_SHIFT) / w;
            outResult.setRawValue(0, static_cast<Type>(x));
            outResult.setRawValue(1, static_cast<Type>(y));
            outResult.setRawValue(2, static_cast<Type>(z));
        }
        else
        {
            const Type invW = Type(1) / vec.getRawValue(3);
            outResult.setRawValue(0, vec.getRawValue(0) * invW);
            outResult.setRawValue(1, vec.getRawValue(1) * invW);
            outResult.setRawValue(2, vec.getRawValue(2) * invW);
        }
    }


    /// <summary>
    /// Scalar * Vector multiplication operator, for commutative
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="scalar"></param>
    /// <param name="vector"></param>
    /// <returns></returns>
    template<typename Type>
    inline Vector4<Type> operator*(Type scalar, const Vector4<Type>& vector)
    {
        return vector * scalar;
    }


} /// namespace ETL::Math
