///----------------------------------------------------------------------------
/// ETL - MathLib
/// Vector3.h
///----------------------------------------------------------------------------
#pragma once

#include "MathLib/Common/ElementProxy.h"
#include "MathLib/Common/RawTag.h"
#include "MathLib/Types/Vector2.h"

namespace ETL::Math
{
    /// When using Vector3<int> integral types, values are stored
    /// internally in 16.16 fixed-point format (FIXED_SHIFT = 16).
    /// Normal accessors like operator[] and x() automatically 
    /// convert to user-expected types.
    /// Use getRawValue()/setRawValue for explicit control storage.

    template<typename Type>
    class Vector3
    {
    public:

        /// Constructors
        constexpr Vector3() = default;
        explicit constexpr Vector3(Type val);
        constexpr Vector3(Type x, Type y, Type z);
        constexpr Vector3(const Vector2<Type>& xy, Type z = Type(1));

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

        ElementProxy<Type> operator[](int index);
        Type               operator[](int index) const;

        /// Operators
        Vector3  operator+(const Vector3& other) const;
        Vector3  operator-(const Vector3& other) const;
        double   operator*(const Vector3& other) const;
        Vector3  operator^(const Vector3& other) const;
        Vector3  operator*(Type scalar) const;
        Vector3  operator/(Type scalar) const;
        Vector3  operator-() const;
        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);
        Vector3& operator*=(Type scalar);
        Vector3& operator/=(Type scalar);
        bool     operator==(const Vector3& other) const;
        bool     operator!=(const Vector3& other) const;

        Vector3  componentMul(const Vector3& other) const;
        Vector3  componentDiv(const Vector3& other) const;
        void     componentMulInPlace(const Vector3& other); 
        void     componentDivInPlace(const Vector3& other);

        /// Vector methods
        double  dot(const Vector3& other) const;
        Vector3 cross(const Vector3& other) const;

        double length() const;
        double lengthSquared() const;

        Vector3  normalize() const;
        Vector3& makeNormalize();

        /// 3D Transform helpers
        Vector2<Type> toVector2() const;
        Vector2<Type> perspectiveDivide() const;
        bool          isPoint() const;
        bool          isDirection() const;

        /// Direct access to internal storage - no conversions applied (use with caution for integral types)
        Type getRawValue(int index) const;
        void setRawValue(int index, Type value);

        /// Static 2D Transform Factories
        static constexpr Vector3 MakePoint(const Vector2<Type>& xy)     { return Vector3<Type>{ xy, Type(1) }; }
        static constexpr Vector3 MakeDirection(const Vector2<Type>& xy) { return Vector3<Type>{ xy, Type(0) }; }

        /// Common constants
        static constexpr Vector3<Type> Zero()  { return { Type(0), Type(0), Type(0) }; }
        static constexpr Vector3<Type> One()   { return { Type(1), Type(1), Type(1) }; }
        static constexpr Vector3<Type> UnitX() { return { Type(1), Type(0), Type(0) }; }
        static constexpr Vector3<Type> UnitY() { return { Type(0), Type(1), Type(0) }; }
        static constexpr Vector3<Type> UnitZ() { return { Type(0), Type(0), Type(1) }; }

        /// Semantic aliases
        static constexpr Vector3<Type> Up()      { return UnitY(); }
        static constexpr Vector3<Type> Down()    { return { Type(0), Type(-1), Type(0) }; }
        static constexpr Vector3<Type> Left()    { return { Type(-1), Type(0), Type(0) }; }
        static constexpr Vector3<Type> Right()   { return UnitX(); }
        static constexpr Vector3<Type> Forward() { return { Type(0), Type(0), Type(-1) }; }
        static constexpr Vector3<Type> Back()    { return UnitZ(); }

    private:
        union {
            struct { Type mX, mY, mZ; };
            Type mData[3];
        };

        constexpr Vector3(RawTag, Type x, Type y, Type z);
    };


    /// Deduction guide
    template<typename Type> Vector3(Type)             -> Vector3<Type>;
    template<typename Type> Vector3(Type, Type, Type) -> Vector3<Type>;


    /// Helpful aliases
    using Vec3 = Vector3<float>;
    using Vec3d = Vector3<double>;
    using Vec3i = Vector3<int>;


    ///------------------------------------------------------------------------------------------
    /// Free functions and common helpers (also present as class member functions.

    /// Component-wise mul
    template<typename Type>
    void ComponentMul(Vector3<Type>& outResult, const Vector3<Type>& v1, const Vector3<Type>& v2);

    /// Component-wise div
    template<typename Type>
    void ComponentDiv(Vector3<Type>& outResult, const Vector3<Type>& v1, const Vector3<Type>& v2);

    /// Dot prod
    template<typename Type>
    void Dot(double& outResult, const Vector3<Type>& v1, const Vector3<Type>& v2);

    /// Cross prod
    template<typename Type>
    void Cross(Vector3<Type>& outResult, const Vector3<Type>& v1, const Vector3<Type>& v2);

    /// Length
    template<typename Type>
    void Length(double& outResult, const Vector3<Type>& vec);

    /// Length Squared
    template<typename Type>
    void LengthSquared(double& outResult, const Vector3<Type>& vec);

    /// Normalize
    template<typename Type>
    bool Normalize(Vector3<Type>& outResult, const Vector3<Type>& vec);

    /// Extract vector3
    template<typename Type>
    void ToVector2(Vector2<Type>& outResult, const Vector3<Type>& vec);

    /// Perspective divide
    template<typename Type>
    void PerspectiveDivide(Vector2<Type>& outResult, const Vector3<Type>& vec);

    /// Scalar * matrix operator (commutative property)
    template<typename Type>
    Vector3<Type> operator*(Type scalar, const Vector3<Type>& vector);


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    extern template class Vector3<float>;
    extern template class Vector3<double>;
    extern template class Vector3<int>;

    extern template void ComponentMul(Vector3<float>&  outResult, const Vector3<float>&  v1, const Vector3<float>&  v2);
    extern template void ComponentMul(Vector3<double>& outResult, const Vector3<double>& v1, const Vector3<double>& v2);
    extern template void ComponentMul(Vector3<int>&    outResult, const Vector3<int>&    v1, const Vector3<int>&    v2);

    extern template void ComponentDiv(Vector3<float>&  outResult, const Vector3<float>&  v1, const Vector3<float>&  v2);
    extern template void ComponentDiv(Vector3<double>& outResult, const Vector3<double>& v1, const Vector3<double>& v2);
    extern template void ComponentDiv(Vector3<int>&    outResult, const Vector3<int>&    v1, const Vector3<int>&    v2);

    extern template void Dot(double& outResult, const Vector3<float>&  v1, const Vector3<float>&  v2);
    extern template void Dot(double& outResult, const Vector3<double>& v1, const Vector3<double>& v2);
    extern template void Dot(double& outResult, const Vector3<int>&    v1, const Vector3<int>&    v2);

    extern template void Cross(Vector3<float>&  outResult, const Vector3<float>&  v1, const Vector3<float>&  v2);
    extern template void Cross(Vector3<double>& outResult, const Vector3<double>& v1, const Vector3<double>& v2);
    extern template void Cross(Vector3<int>&    outResult, const Vector3<int>&    v1, const Vector3<int>&    v2);

    extern template void Length(double& outResult, const Vector3<float>&  vec);
    extern template void Length(double& outResult, const Vector3<double>& vec);
    extern template void Length(double& outResult, const Vector3<int>&    vec);

    extern template void LengthSquared(double& outResult, const Vector3<float>&  vec);
    extern template void LengthSquared(double& outResult, const Vector3<double>& vec);
    extern template void LengthSquared(double& outResult, const Vector3<int>&    vec);

    extern template bool Normalize(Vector3<float>&  outResult, const Vector3<float>&  vec);
    extern template bool Normalize(Vector3<double>& outResult, const Vector3<double>& vec);
    extern template bool Normalize(Vector3<int>&    outResult, const Vector3<int>&    vec);

    extern template void ToVector2(Vector2<float>&  outResult, const Vector3<float>&  vec);
    extern template void ToVector2(Vector2<double>& outResult, const Vector3<double>& vec);
    extern template void ToVector2(Vector2<int>&    outResult, const Vector3<int>&    vec);

    extern template void PerspectiveDivide(Vector2<float>&  outResult, const Vector3<float>&  vec);
    extern template void PerspectiveDivide(Vector2<double>& outResult, const Vector3<double>& vec);
    extern template void PerspectiveDivide(Vector2<int>&    outResult, const Vector3<int>&    vec);

    extern template Vector3<float>  operator*(float  scalar, const Vector3<float>&  vector);
    extern template Vector3<double> operator*(double scalar, const Vector3<double>& vector);
    extern template Vector3<int>    operator*(int    scalar, const Vector3<int>&    vector);


} /// namespace ETL::Math

#include "inline/Vector3.inl"
