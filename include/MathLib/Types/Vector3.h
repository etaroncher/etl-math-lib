///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector3.h
///----------------------------------------------------------------------------
#pragma once

namespace ETL::Math
{

    template<typename Type>
    class Vector3
    {
    public:

        /// Constructors
        constexpr Vector3();
        constexpr Vector3(Type val);
        constexpr Vector3(Type x, Type y, Type z);

        /// Copy, Move & Destructor (default)
        Vector3(const Vector3&) = default;
        Vector3(Vector3&&) noexcept = default;
        Vector3& operator=(const Vector3&) = default;
        Vector3& operator=(Vector3&&) noexcept = default;
        ~Vector3() = default;

        /// Access methods
        Type x() const;
        Type y() const;
        Type z() const;

        void x(Type x);
        void y(Type y);
        void z(Type z);

        Type& operator[](int index);
        Type  operator[](int index) const;

        /// Operators
        Vector3  operator+(const Vector3& other) const;
        Vector3  operator-(const Vector3& other) const;
        Vector3  operator*(Type scalar) const;
        Vector3  operator/(Type scalar) const;
        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);
        Vector3& operator*=(Type scalar);
        Vector3& operator/=(Type scalar);
        bool     operator==(const Vector3& other) const;
        bool     operator!=(const Vector3& other) const;

        /// Vector methods 
        Type     length() const;
        Type     lengthSquared() const;
        Vector3  normalize() const;
        Vector3& makeNormalize();

        /// Common constants
        static constexpr Vector3<Type> zero()  { return { Type(0), Type(0), Type(0) }; }
        static constexpr Vector3<Type> one()   { return { Type(1), Type(1), Type(1) }; }
        static constexpr Vector3<Type> unitX() { return { Type(1), Type(0), Type(0) }; }
        static constexpr Vector3<Type> unitY() { return { Type(0), Type(1), Type(0) }; }
        static constexpr Vector3<Type> unitZ() { return { Type(0), Type(0), Type(1) }; }

        /// Semantic aliases
        static constexpr Vector3<Type> up()      { return unitY(); }
        static constexpr Vector3<Type> down()    { return { Type(0), Type(-1), Type(0) }; }
        static constexpr Vector3<Type> left()    { return { Type(-1), Type(0), Type(0) }; }
        static constexpr Vector3<Type> right()   { return unitX(); }
        static constexpr Vector3<Type> forward() { return { Type(0), Type(0), Type(-1) }; }
        static constexpr Vector3<Type> back()    { return unitZ(); }

    private:

        union {
            struct { Type mX, mY, mZ; };
            Type mData[3];
        };
        
    };


    /// Scalar * matrix operator (commutative property)
    template<typename VectorType, typename ScalarType>
    Vector3<VectorType> operator*(ScalarType scalar, const Vector3<VectorType>& v2);


    /// Common Vector opperations
    template<typename Type>
    Vector3<Type> cross     (const Vector3<Type>& v1, const Vector3<Type>& v2);

    template<typename Type>
    Type          dot       (const Vector3<Type>& v1, const Vector3<Type>& v2);


    /// Helpful aliases
    using Vec3  = Vector3<float>;
    using Vec3d = Vector3<double>;


    /// Explicit template instantiatio (precompiled declaration)
    extern template class Vector3<float>;
    extern template class Vector3<double>;

    extern template Vector3<float>  operator*(float  scalar, const Vector3<float>&  v2);
    extern template Vector3<double> operator*(double scalar, const Vector3<double>& v2);

} /// namespace ETL::Math
