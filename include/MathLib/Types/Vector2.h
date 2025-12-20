///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector2.h
///----------------------------------------------------------------------------
#pragma once

#include "MathLib/Common/ElementProxy.h"
#include "MathLib/Common/RawTag.h"

namespace ETL::Math
{

    /// When using Vector2<int> integral types, values are stored
    /// internally in 16.16 fixed-point format (FIXED_SHIFT = 16).
    /// Normal accessors like operator[] and x() automatically 
    /// convert to user-expected types.
    /// Use getRawValue()/setRawValue for explicit control storage.

    template<typename Type>
    class Vector2
    {
    public:

        /// Constructors
        constexpr Vector2() = default;
        explicit constexpr Vector2(Type val);
        constexpr Vector2(Type x, Type y);

        /// Copy, Move & Destructor (default)
        Vector2(const Vector2&) = default;
        Vector2(Vector2&&) noexcept = default;
        Vector2& operator=(const Vector2&) = default;
        Vector2& operator=(Vector2&&) noexcept = default;
        ~Vector2() = default;

        /// Access methods
        Type x() const;
        Type y() const;

        void x(Type x);
        void y(Type y);

        ElementProxy<Type> operator[](int index);
        Type               operator[](int index) const;

        /// Operators
        Vector2  operator+(const Vector2& other) const;
        Vector2  operator-(const Vector2& other) const;
        double   operator*(const Vector2& other) const;
        double   operator^(const Vector2& other) const;
        Vector2  operator*(Type scalar) const;
        Vector2  operator/(Type scalar) const;
        Vector2  operator-() const;
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(Type scalar);
        Vector2& operator/=(Type scalar);
        bool     operator==(const Vector2& other) const;
        bool     operator!=(const Vector2& other) const;

        Vector2  componentMul(const Vector2& other) const;
        Vector2  componentDiv(const Vector2& other) const;
        void     componentMulInPlace(const Vector2& other);
        void     componentDivInPlace(const Vector2& other);

        /// Vector methods
        double dot(const Vector2& other) const;
        double cross(const Vector2& other) const;

        double length() const;
        double lengthSquared() const;

        Vector2  normalize() const;
        Vector2& makeNormalize();

        /// Direct access to internal storage - no conversions applied (use with caution for integral types)
        Type getRawValue(int index) const;
        void setRawValue(int index, Type value);

        /// Common constants
        static constexpr Vector2<Type> zero()  { return { Type(0), Type(0) }; }
        static constexpr Vector2<Type> one()   { return { Type(1), Type(1) }; }
        static constexpr Vector2<Type> unitX() { return { Type(1), Type(0) }; }
        static constexpr Vector2<Type> unitY() { return { Type(0), Type(1) }; }

        /// Semantic aliases
        static constexpr Vector2<Type> up()      { return unitY(); }
        static constexpr Vector2<Type> down()    { return { Type(0), Type(-1) }; }
        static constexpr Vector2<Type> left()    { return { Type(-1), Type(0) }; }
        static constexpr Vector2<Type> right()   { return unitX(); }

    private:
        union {
            struct { Type mX, mY; };
            Type mData[2];
        };

        constexpr Vector2(RawTag, Type x, Type y);
    };


    /// Deduction guide
    template<typename Type> Vector2(Type)       -> Vector2<Type>;
    template<typename Type> Vector2(Type, Type) -> Vector2<Type>;


    /// Helpful aliases
    using Vec2 = Vector2<float>;
    using Vec2d = Vector2<double>;
    using Vec2i = Vector2<int>;


    ///------------------------------------------------------------------------------------------
    /// Free functions and common helpers (also present as class member functions.

    /// Component-wise mul
    template<typename Type>
    void ComponentMul(Vector2<Type>& outResult, const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Component-wise div
    template<typename Type>
    void ComponentDiv(Vector2<Type>& outResult, const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Dot prod
    template<typename Type>
    void Dot(double& outResult, const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Cross prod
    template<typename Type>
    void Cross(double& outResult, const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Length
    template<typename Type>
    void Length(double& outResult, const Vector2<Type>& vec);

    /// Length Squared
    template<typename Type>
    void LengthSquared(double& outResult, const Vector2<Type>& vec);

    /// Normalize
    template<typename Type>
    bool Normalize(Vector2<Type>& outResult, const Vector2<Type>& vec);

    /// Scalar * matrix operator (commutative property)
    template<typename Type>
    Vector2<Type> operator*(Type scalar, const Vector2<Type>& vector);


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    extern template class Vector2<float>;
    extern template class Vector2<double>;
    extern template class Vector2<int>;

    extern template void ComponentMul(Vector2<float>&  outResult, const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template void ComponentMul(Vector2<double>& outResult, const Vector2<double>& v1, const Vector2<double>& v2);
    extern template void ComponentMul(Vector2<int>&    outResult, const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template void ComponentDiv(Vector2<float>&  outResult, const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template void ComponentDiv(Vector2<double>& outResult, const Vector2<double>& v1, const Vector2<double>& v2);
    extern template void ComponentDiv(Vector2<int>&    outResult, const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template void Dot(double& outResult, const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template void Dot(double& outResult, const Vector2<double>& v1, const Vector2<double>& v2);
    extern template void Dot(double& outResult, const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template void Cross(double& outResult, const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template void Cross(double& outResult, const Vector2<double>& v1, const Vector2<double>& v2);
    extern template void Cross(double& outResult, const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template void Length(double& outResult, const Vector2<float>&  vec);
    extern template void Length(double& outResult, const Vector2<double>& vec);
    extern template void Length(double& outResult, const Vector2<int>&    vec);

    extern template void LengthSquared(double& outResult, const Vector2<float>&  vec);
    extern template void LengthSquared(double& outResult, const Vector2<double>& vec);
    extern template void LengthSquared(double& outResult, const Vector2<int>&    vec);

    extern template bool Normalize(Vector2<float>&  outResult, const Vector2<float>&  vec);
    extern template bool Normalize(Vector2<double>& outResult, const Vector2<double>& vec);
    extern template bool Normalize(Vector2<int>&    outResult, const Vector2<int>&    vec);

    extern template Vector2<float>  operator*(float  scalar, const Vector2<float>&  vector);
    extern template Vector2<double> operator*(double scalar, const Vector2<double>& vector);
    extern template Vector2<int>    operator*(int    scalar, const Vector2<int>&    vector);


} /// namespace ETL::Math

#include "inline/Vector2.inl"
