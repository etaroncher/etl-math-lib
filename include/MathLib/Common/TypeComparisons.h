///----------------------------------------------------------------------------
/// ETL - MathLib
/// TypeComparisons.h
///---------------------------------------------------------------------------- 
#pragma once

#include <concepts>

namespace ETL::Math
{

    /// Internal helper namespace
    namespace helpers
    {
        /// Absolute value for signed types
        template<typename T>
        requires (std::signed_integral<T> || std::floating_point<T>)
        constexpr T abs(T value)
        {
            return value < T(0) ? -value : value;
        }

        /// "Absolute value" for unsigned types (just return as-is)
        template<typename T>
        requires (std::unsigned_integral<T>)
        constexpr T abs(T value)
        {
            return value;  // Already non-negative!
        }

        /// Max of two values
        template<typename T>
        constexpr T max(T a, T b)
        {
            return a > b ? a : b;
        }
    }

    /// Forward declarations

    template<typename T> class Vector2;
    template<typename T> class Vector3;
    template<typename T> class Matrix3x3;


    /// Default Epsilon Values

    template<typename T>
    struct Epsilon
    {
        static constexpr T value = T(1e-6);  /// Default for general use
    };

    template<>
    struct Epsilon<int>
    {
        static constexpr int value = 1;  /// Epsilon = 1 for ints
    };

    template<>
    struct Epsilon<unsigned int>
    {
        static constexpr unsigned int value = 1;  /// Epsilon = 1 for unsigned ints
    };

    template<>
    struct Epsilon<float>
    {
        static constexpr float value = 1e-5f;  /// Looser for float
    };

    template<>
    struct Epsilon<double>
    {
        static constexpr double value = 1e-10;  /// Tighter for double
    };

    /// Scalar Comparisons

    template<typename T>
    inline bool isZero(T value, T epsilon = Epsilon<T>::value)
    {
        return helpers::abs<T>(value) < epsilon;
    }

    template<typename T>
    inline bool isEqual(T a, T b, T epsilon = Epsilon<T>::value)
    {
        return helpers::abs<T>(a - b) < epsilon;
    }


    /// Vector Comparisons

    template<typename T>
    bool isZero(const Vector2<T>& vec, T epsilon = Epsilon<T>::value);

    template<typename T>
    bool isZero(const Vector3<T>& vec, T epsilon = Epsilon<T>::value);

    template<typename T>
    bool isEqual(const Vector2<T>& a, const Vector2<T>& b, T epsilon = Epsilon<T>::value);

    template<typename T>
    bool isEqual(const Vector3<T>& a, const Vector3<T>& b, T epsilon = Epsilon<T>::value);


    /// Matrix Comparisons

    template<typename T>
    bool isZero(const Matrix3x3<T>& vec, T epsilon = Epsilon<T>::value);

    template<typename T>
    bool isEqual(const Matrix3x3<T>& a, const Matrix3x3<T>& b, T epsilon = Epsilon<T>::value);


    /// Explicit template instatiation declaration
    /// Vector2
    extern template bool isZero(const Vector2<int>&, int);
    extern template bool isZero(const Vector2<double>&, double);
    extern template bool isZero(const Vector2<float>&, float);

    extern template bool isEqual(const Vector2<int>&, const Vector2<int>&, int);
    extern template bool isEqual(const Vector2<double>&, const Vector2<double>&, double);
    extern template bool isEqual(const Vector2<float>&, const Vector2<float>&, float);

    /// Vector3
    extern template bool isZero(const Vector3<float>&, float);
    extern template bool isZero(const Vector3<double>&, double);

    extern template bool isEqual(const Vector3<float>&, const Vector3<float>&, float);
    extern template bool isEqual(const Vector3<double>&, const Vector3<double>&, double);

    /// Matrix3x3
    extern template bool isZero(const Matrix3x3<float>&, float);
    extern template bool isZero(const Matrix3x3<double>&, double);

    extern template bool isEqual(const Matrix3x3<float>&, const Matrix3x3<float>&, float);
    extern template bool isEqual(const Matrix3x3<double>&, const Matrix3x3<double>&, double);

} /// namespace ETL::Math
