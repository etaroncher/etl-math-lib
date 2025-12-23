///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector4.h
///----------------------------------------------------------------------------
#pragma once

#include "MathLib/Common/ElementProxy.h"
#include "MathLib/Common/RawTag.h"
#include "MathLib/Types/Vector3.h"

namespace ETL::Math
{
    /// When using Vector4<int> integral types, values are stored
    /// internally in 16.16 fixed-point format (FIXED_SHIFT = 16).
    /// Normal accessors like operator[] and x() automatically 
    /// convert to user-expected types.
    /// Use getRawValue()/setRawValue for explicit control storage.

    template<typename Type>
    class Vector4
    {
    public:

        /// Constructors
        constexpr Vector4() = default;
        explicit constexpr Vector4(Type val);
        constexpr Vector4(Type x, Type y, Type z, Type w);
        constexpr Vector4(double x, double y, double z, double w) requires (!std::same_as<Type, double>);
        constexpr Vector4(const Vector3<Type>& xyz, Type w = Type(1));

        /// Copy, Move & Destructor (default)
        Vector4(const Vector4&) = default;
        Vector4(Vector4&&) noexcept = default;
        Vector4& operator=(const Vector4&) = default;
        Vector4& operator=(Vector4&&) noexcept = default;
        ~Vector4() = default;

        /// Access methods
        Type x() const;
        Type y() const;
        Type z() const;
        Type w() const;

        void x(Type x);
        void y(Type y);
        void z(Type z);
        void w(Type w);

        ElementProxy<Type> operator[](int index);
        Type               operator[](int index) const;

        /// Operators
        Vector4  operator+(const Vector4& other) const;
        Vector4  operator-(const Vector4& other) const;
        double   operator*(const Vector4& other) const;
        Vector4  operator*(Type scalar) const;
        Vector4  operator/(Type scalar) const;
        Vector4  operator-() const;
        Vector4& operator+=(const Vector4& other);
        Vector4& operator-=(const Vector4& other);
        Vector4& operator*=(Type scalar);
        Vector4& operator/=(Type scalar);
        bool     operator==(const Vector4& other) const;
        bool     operator!=(const Vector4& other) const;

        Vector4  componentMul(const Vector4& other) const;
        Vector4  componentDiv(const Vector4& other) const;
        void     componentMulInPlace(const Vector4& other); 
        void     componentDivInPlace(const Vector4& other);

        /// Vector methods
        double dot(const Vector4& other) const;

        double length() const;
        double lengthSquared() const;

        Vector4  normalize() const;
        Vector4& makeNormalize();

        /// 3D Transform helpers
        Vector3<Type> toVector3() const;
        Vector3<Type> perspectiveDivide() const;
        bool          isPoint() const;
        bool          isDirection() const;

        /// Direct access to internal storage - no conversions applied (use with caution for integral types)
        Type getRawValue(int index) const;
        void setRawValue(int index, Type value);

        /// Static 3D Transform Factories
        static constexpr Vector4 MakePoint(const Vector3<Type>& xyz)     { return Vector4<Type>{ xyz, Type(1) }; }
        static constexpr Vector4 MakeDirection(const Vector3<Type>& xyz) { return Vector4<Type>{ xyz, Type(0) }; }

        /// Common constants
        static constexpr Vector4<Type> Zero() { return { Type(0), Type(0), Type(0), Type(0) }; }
        static constexpr Vector4<Type> One()  { return { Type(1), Type(1), Type(1), Type(1) }; }
        static constexpr Vector4<Type> DirX() { return { Type(1), Type(0), Type(0), Type(0) }; }
        static constexpr Vector4<Type> DirY() { return { Type(0), Type(1), Type(0), Type(0) }; }
        static constexpr Vector4<Type> DirZ() { return { Type(0), Type(0), Type(1), Type(0) }; }

    private:
        union {
            struct { Type mX, mY, mZ, mW; };
            Type mData[4];
        };

        constexpr Vector4(RawTag, Type x, Type y, Type z, Type w);
    };


    /// Deduction guide
    template<typename Type> Vector4(Type)                   -> Vector4<Type>;
    template<typename Type> Vector4(Type, Type, Type, Type) -> Vector4<Type>;


    /// Helpful aliases
    using Vec4  = Vector4<float>;
    using Vec4d = Vector4<double>;
    using Vec4i = Vector4<int>;


    ///------------------------------------------------------------------------------------------
    /// Free functions and common helpers (also present as class member functions.

    /// Component-wise mul
    template<typename Type>
    void ComponentMul(Vector4<Type>& outResult, const Vector4<Type>& v1, const Vector4<Type>& v2);

    /// Component-wise div
    template<typename Type>
    void ComponentDiv(Vector4<Type>& outResult, const Vector4<Type>& v1, const Vector4<Type>& v2);

    /// Dot prod
    template<typename Type>
    void Dot(double& outResult, const Vector4<Type>& v1, const Vector4<Type>& v2);

    /// Length
    template<typename Type>
    void Length(double& outResult, const Vector4<Type>& vec);

    /// Length Squared
    template<typename Type>
    void LengthSquared(double& outResult, const Vector4<Type>& vec);

    /// Normalize
    template<typename Type>
    bool Normalize(Vector4<Type>& outResult, const Vector4<Type>& vec);

    /// Extract vector3
    template<typename Type>
    void ToVector3(Vector3<Type>& outResult, const Vector4<Type>& vec);

    /// Perspective divide
    template<typename Type>
    void PerspectiveDivide(Vector3<Type>& outResult, const Vector4<Type>& vec);

    /// Scalar * matrix operator (commutative property)
    template<typename Type>
    Vector4<Type> operator*(Type scalar, const Vector4<Type>& vector);


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    extern template class Vector4<float>;
    extern template class Vector4<double>;
    extern template class Vector4<int>;

    extern template void ComponentMul(Vector4<float>&  outResult, const Vector4<float>&  v1, const Vector4<float>&  v2);
    extern template void ComponentMul(Vector4<double>& outResult, const Vector4<double>& v1, const Vector4<double>& v2);
    extern template void ComponentMul(Vector4<int>&    outResult, const Vector4<int>&    v1, const Vector4<int>&    v2);

    extern template void ComponentDiv(Vector4<float>&  outResult, const Vector4<float>&  v1, const Vector4<float>&  v2);
    extern template void ComponentDiv(Vector4<double>& outResult, const Vector4<double>& v1, const Vector4<double>& v2);
    extern template void ComponentDiv(Vector4<int>&    outResult, const Vector4<int>&    v1, const Vector4<int>&    v2);

    extern template void Dot(double& outResult, const Vector4<float>&  v1, const Vector4<float>&  v2);
    extern template void Dot(double& outResult, const Vector4<double>& v1, const Vector4<double>& v2);
    extern template void Dot(double& outResult, const Vector4<int>&    v1, const Vector4<int>&    v2);

    extern template void Length(double& outResult, const Vector4<float>&  vec);
    extern template void Length(double& outResult, const Vector4<double>& vec);
    extern template void Length(double& outResult, const Vector4<int>&    vec);

    extern template void LengthSquared(double& outResult, const Vector4<float>&  vec);
    extern template void LengthSquared(double& outResult, const Vector4<double>& vec);
    extern template void LengthSquared(double& outResult, const Vector4<int>&    vec);

    extern template bool Normalize(Vector4<float>&  outResult, const Vector4<float>&  vec);
    extern template bool Normalize(Vector4<double>& outResult, const Vector4<double>& vec);
    extern template bool Normalize(Vector4<int>&    outResult, const Vector4<int>&    vec);

    extern template void ToVector3(Vector3<float>&  outResult, const Vector4<float>&  vec);
    extern template void ToVector3(Vector3<double>& outResult, const Vector4<double>& vec);
    extern template void ToVector3(Vector3<int>&    outResult, const Vector4<int>&    vec);

    extern template void PerspectiveDivide(Vector3<float>&  outResult, const Vector4<float>&  vec);
    extern template void PerspectiveDivide(Vector3<double>& outResult, const Vector4<double>& vec);
    extern template void PerspectiveDivide(Vector3<int>&    outResult, const Vector4<int>&    vec);

    extern template Vector4<float>  operator*(float  scalar, const Vector4<float>&  vector);
    extern template Vector4<double> operator*(double scalar, const Vector4<double>& vector);
    extern template Vector4<int>    operator*(int    scalar, const Vector4<int>&    vector);

} /// namespace ETL::Math

#include "inline/Vector4.inl"
