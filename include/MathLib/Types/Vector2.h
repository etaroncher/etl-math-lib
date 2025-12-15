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
        Type     operator*(const Vector2& other) const; /// Dot prod
        Type     operator^(const Vector2& other) const; /// Cross prod
        Vector2  operator*(Type scalar) const;
        Vector2  operator/(Type scalar) const;

        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(Type scalar);
        Vector2& operator/=(Type scalar);

        bool     operator==(const Vector2& other) const;
        bool     operator!=(const Vector2& other) const;

        Vector2& operator*=(const Vector2& other); /// In-place Component Multiplication (Element-wise Multiplication Assignment)
        Vector2& operator/=(const Vector2& other); /// In-place Component Division (Element-wise Division Assignment)
        Vector2  componentMul(const Vector2& other) const; /// Component Multiplication
        Vector2  componentDiv(const Vector2& other) const; /// Component Division

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


    ///------------------------------------------------------------------------------------------
    /// Free functions and common helpers (also present as class member functions.

    /// Length
    template<typename Type>
    Type Length(const Vector2<Type>& vec);

    /// Length Squared
    template<typename Type>
    Type LengthSquared(const Vector2<Type>& vec);

    /// Normalize
    template<typename Type> requires std::floating_point<Type>
    Vector2<Type> Normalize(const Vector2<Type>& vec);

    /// Cross prod
    template<typename Type>
    Type Cross(const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Dot prod
    template<typename Type>
    Type Dot(const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Component-wise mul
    template<typename Type>
    Vector2<Type> ComponentMul(const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Component-wise div
    template<typename Type>
    Vector2<Type> ComponentDiv(const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Scalar * matrix operator (commutative property)
    template<typename Type>
    Vector2<Type> operator*(Type scalar, const Vector2<Type>& vector);


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    extern template class Vector2<float>;
    extern template class Vector2<double>;
    extern template class Vector2<int>;

    extern template float  Length(const Vector2<float>&  vec);
    extern template double Length(const Vector2<double>& vec);
    extern template int    Length(const Vector2<int>&    vec);

    extern template float  LengthSquared(const Vector2<float>& vec);
    extern template double LengthSquared(const Vector2<double>& vec);
    extern template int    LengthSquared(const Vector2<int>& vec);

    extern template Vector2<float>  Normalize(const Vector2<float>&  vec);
    extern template Vector2<double> Normalize(const Vector2<double>& vec);

    extern template float  Cross(const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template double Cross(const Vector2<double>& v1, const Vector2<double>& v2);
    extern template int    Cross(const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template float  Dot(const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template double Dot(const Vector2<double>& v1, const Vector2<double>& v2);
    extern template int    Dot(const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template Vector2<float>  ComponentMul(const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template Vector2<double> ComponentMul(const Vector2<double>& v1, const Vector2<double>& v2);
    extern template Vector2<int>    ComponentMul(const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template Vector2<float>  ComponentDiv(const Vector2<float>&  v1, const Vector2<float>&  v2);
    extern template Vector2<double> ComponentDiv(const Vector2<double>& v1, const Vector2<double>& v2);
    extern template Vector2<int>    ComponentDiv(const Vector2<int>&    v1, const Vector2<int>&    v2);

    extern template Vector2<float>  operator*(float  scalar, const Vector2<float>& vector);
    extern template Vector2<double> operator*(double scalar, const Vector2<double>& vector);
    extern template Vector2<int>    operator*(int    scalar, const Vector2<int>& vector);


} /// namespace ETL::Math

#include "inline/Vector2.inl"
