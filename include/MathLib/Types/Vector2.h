///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector2.h
///----------------------------------------------------------------------------
#pragma once

namespace ETL { namespace Math
{

    template<typename Type>
    class Vector2
    {
    public:

        Vector2();
        Vector2(Type val);
        Vector2(Type x, Type y);

        Type x() const;
        Type y() const;

        void x(Type x);
        void y(Type y);

        Type& operator[](int index);
        Type  operator[](int index) const;

        Type length() const;
        Type lengthSquared() const;

        Vector2  normalize() const;
        Vector2& makeNormalize();

        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(Type scalar) const;
        Vector2 operator/(Type scalar) const;

        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(Type scalar);
        Vector2& operator/=(Type scalar);

        //static Vector2<Type> zero();

    private:

        union {
            struct { Type mX, mY; };
            Type mData[2];
        };
    };


    /// Scalar * matrix operator (commutative property)
    template<typename VectorType, typename ScalarType>
    Vector2<VectorType> operator*(ScalarType scalar, const Vector2<VectorType>& v2);


    /// Cross prod
    template<typename Type>
    Type cross(const Vector2<Type>& v1, const Vector2<Type>& v2);

    /// Dot prod
    template<typename Type>
    Type dot(const Vector2<Type>& v1, const Vector2<Type>& v2);


    /// Helpful aliases
    using Vec2  = Vector2<float>;
    using Vec2i = Vector2<int>;


    /// Explicit template instantiatio (precompiled declaration)
    extern template class Vector2<float>;
    extern template class Vector2<double>;
    extern template class Vector2<int>;
    extern template class Vector2<unsigned int>;

    extern template Vector2<float>        operator*(float  scalar, const Vector2<float>&        v2);
    extern template Vector2<double>       operator*(double scalar, const Vector2<double>&       v2);
    extern template Vector2<int>          operator*(float  scalar, const Vector2<int>&          v2);
    extern template Vector2<int>          operator*(double scalar, const Vector2<int>&          v2);
    extern template Vector2<unsigned int> operator*(float  scalar, const Vector2<unsigned int>& v2);
    extern template Vector2<unsigned int> operator*(double scalar, const Vector2<unsigned int>& v2);

}} /// namespace ETL::Math
