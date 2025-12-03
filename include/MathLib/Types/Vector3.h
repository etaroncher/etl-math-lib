///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector3.h
///----------------------------------------------------------------------------
#pragma once

namespace ETL { namespace Math
{

    template<typename Type>
    class Vector3
    {
    public:

        Vector3();
        Vector3(Type val);
        Vector3(Type x, Type y, Type z);

        Type x() const;
        Type y() const;
        Type z() const;

        void x(Type x);
        void y(Type y);
        void z(Type z);

        Type& operator[](int index);
        Type  operator[](int index) const;

        Type length() const;
        Type lengthSquared() const;

        Vector3  normalize() const;
        Vector3& makeNormalize();

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(Type scalar) const;
        Vector3 operator/(Type scalar) const;

        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);
        Vector3& operator*=(Type scalar);
        Vector3& operator/=(Type scalar);

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

}} /// namespace ETL::Math
