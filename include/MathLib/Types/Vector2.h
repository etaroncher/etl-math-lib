///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector2.h
///----------------------------------------------------------------------------
#pragma once

#include <concepts>

namespace ETL::Math
{

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

        Type& operator[](int index);
        Type  operator[](int index) const;

        /// Operators
        Vector2  operator+(const Vector2& other) const;
        Vector2  operator-(const Vector2& other) const;
        Vector2  operator*(Type scalar) const;
        Vector2  operator/(Type scalar) const;
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(Type scalar);
        Vector2& operator/=(Type scalar);
        bool     operator==(const Vector2& other) const;
        bool     operator!=(const Vector2& other) const;

        /// Vector methods
        Type length() const;
        Type lengthSquared() const;

        Vector2  normalize() const requires std::floating_point<Type>;
        Vector2& makeNormalize() requires std::floating_point<Type>;

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
    };


    /// Deduction guide
    template<typename Type> Vector2(Type)       -> Vector2<Type>;
    template<typename Type> Vector2(Type, Type) -> Vector2<Type>;


    /// Helpful aliases
    using Vec2 = Vector2<float>;
    using Vec2d = Vector2<double>;
    using Vec2i = Vector2<int>;


    /// Scalar * matrix operator (commutative property)
    template<typename Type>
    Vector2<Type> operator*(Type scalar, const Vector2<Type>& vector);

    /// Cross prod
    template<typename Type>
    Type cross(const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Dot prod
    template<typename Type>
    Type dot(const Vector2<Type>& v1, const Vector2<Type>& v2);


    /// Explicit template instantiation (precompiled declaration)
    extern template class Vector2<float>;
    extern template class Vector2<double>;
    extern template class Vector2<int>;

    extern template Vector2<float>  operator*(float  scalar, const Vector2<float>&  vector);
    extern template Vector2<double> operator*(double scalar, const Vector2<double>& vector);
    extern template Vector2<int>    operator*(int    scalar, const Vector2<int>&    vector);

    extern template float  cross(const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template double cross(const Vector2<double>& v1, const Vector2<double>& v2);
    extern template int    cross(const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template float  dot(const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template double dot(const Vector2<double>& v1, const Vector2<double>& v2);
    extern template int    dot(const Vector2<int>&    v1, const Vector2<int>&    v2);


} /// namespace ETL::Math

#include "inline/Vector2.inl"
