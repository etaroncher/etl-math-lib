///----------------------------------------------------------------------------
/// ETL - MathLib
/// TypeComparisons.h
///---------------------------------------------------------------------------- 
#pragma once

#include "MathLib/Common/FixedPointHelpers.h"

namespace ETL::Math
{
    ///------------------------------------------------------------------------------------------
    /// Default Epsilon Values

    template<typename T>
    struct Epsilon
    {
        static constexpr double value = 1e-6;  /// Default for general use
    };

    template<>
    struct Epsilon<int>
    {
        static constexpr double value = 0.0001;  /// min value in fixed point 16
    };

    template<>
    struct Epsilon<float>
    {
        static constexpr double value = 1e-5;  /// Looser for float
    };

    template<>
    struct Epsilon<double>
    {
        static constexpr double value = 1e-10;  /// Tighter for double
    };


    ///------------------------------------------------------------------------------------------
    /// Internal helper

    namespace helpers
    {
        /// Absolute value for signed types
        template<typename T>
        inline constexpr T abs(T value)
        {
            return value < T(0) ? -value : value;
        }

        /// Max of two values
        template<typename T>
        inline constexpr T max(T a, T b)
        {
            return a > b ? a : b;
        }

        template<typename T>
        inline bool zeroElement(T value, double epsilon)
        {
            return abs<T>(value) < EncodeValue<T>(epsilon);
        }

        template<typename Cont, typename T, int SIZE>
        inline bool zeroContainer(const Cont& container, double epsilon)
        {
            bool bIsZero = true;
            for (int i = 0; i < SIZE; ++i)
                bIsZero = bIsZero && zeroElement<T>(container.getRawValue(i), epsilon);

            return bIsZero;
        }
    }


    ///------------------------------------------------------------------------------------------
    /// Forward declarations

    template<typename T> class Vector2;
    template<typename T> class Vector3;
    template<typename T> class Vector4;
    template<typename T> class Matrix3x3;
    template<typename T> class Matrix4x4;


    ///------------------------------------------------------------------------------------------
    /// Type Comparison API - integers are interpreted as fixed point 16.16

    /// Element comparison
    template<typename T>
    inline bool isZeroRaw(T value, T epsilon = static_cast<T>(Epsilon<T>::value))
    {
        return helpers::abs<T>(value) < epsilon;
    }


    template<typename T>
    inline bool isZero(T value, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroElement<T>(value, epsilon);
    }

    template<typename T>
    inline bool isEqual(T a, T b, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroElement<T>(a - b, epsilon);
    }

    /// Vector2 Comparisons

    template<typename T>
    inline bool isZero(const Vector2<T>& vec, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Vector2<T>, T, 2>(vec, epsilon);
    }

    template<typename T>
    inline bool isEqual(const Vector2<T>& a, const Vector2<T>& b, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Vector2<T>, T, 2>(a - b, epsilon);
    }

    /// Vector3 Comparisons

    template<typename T>
    inline bool isZero(const Vector3<T>& vec, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Vector3<T>, T, 3>(vec, epsilon);
    }

    template<typename T>
    inline bool isEqual(const Vector3<T>& a, const Vector3<T>& b, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Vector3<T>, T, 3>(a - b, epsilon);
    }

    /// Vector4 Comparisons

    template<typename T>
    inline bool isZero(const Vector4<T>& vec, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Vector4<T>, T, 4>(vec, epsilon);
    }

    template<typename T>
    inline bool isEqual(const Vector4<T>& a, const Vector4<T>& b, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Vector4<T>, T, 4>(a - b, epsilon);
    }

    /// Matrix3x3 Comparisons

    template<typename T>
    inline bool isZero(const Matrix3x3<T>& vec, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Matrix3x3<T>, T, 9>(vec, epsilon);
    }

    template<typename T>
    inline bool isEqual(const Matrix3x3<T>& a, const Matrix3x3<T>& b, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Matrix3x3<T>, T, 9>(a - b, epsilon);
    }

    /// Matrix4x4 Comparisons

    template<typename T>
    inline bool isZero(const Matrix4x4<T>& vec, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Matrix4x4<T>, T, 16>(vec, epsilon);
    }

    template<typename T>
    inline bool isEqual(const Matrix4x4<T>& a, const Matrix4x4<T>& b, double epsilon = Epsilon<T>::value)
    {
        return helpers::zeroContainer<Matrix4x4<T>, T, 16>(a - b, epsilon);
    }


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    /// Vector2
    extern template bool isZero(const Vector2<int>&,    double);
    extern template bool isZero(const Vector2<float>&,  double);
    extern template bool isZero(const Vector2<double>&, double);

    extern template bool isEqual(const Vector2<int>&,    const Vector2<int>&,    double);
    extern template bool isEqual(const Vector2<float>&,  const Vector2<float>&,  double);
    extern template bool isEqual(const Vector2<double>&, const Vector2<double>&, double);

    /// Vector3
    extern template bool isZero(const Vector3<int>&,    double);
    extern template bool isZero(const Vector3<float>&,  double);
    extern template bool isZero(const Vector3<double>&, double);

    extern template bool isEqual(const Vector3<int>&,    const Vector3<int>&,    double);
    extern template bool isEqual(const Vector3<float>&,  const Vector3<float>&,  double);
    extern template bool isEqual(const Vector3<double>&, const Vector3<double>&, double);

    /// Vector4
    extern template bool isZero(const Vector4<int>&,    double);
    extern template bool isZero(const Vector4<float>&,  double);
    extern template bool isZero(const Vector4<double>&, double);

    extern template bool isEqual(const Vector4<int>&,    const Vector4<int>&,    double);
    extern template bool isEqual(const Vector4<float>&,  const Vector4<float>&,  double);
    extern template bool isEqual(const Vector4<double>&, const Vector4<double>&, double);

    /// Matrix3x3
    extern template bool isZero(const Matrix3x3<int>&,    double);
    extern template bool isZero(const Matrix3x3<float>&,  double);
    extern template bool isZero(const Matrix3x3<double>&, double);

    extern template bool isEqual(const Matrix3x3<int>&,    const Matrix3x3<int>&,    double);
    extern template bool isEqual(const Matrix3x3<float>&,  const Matrix3x3<float>&,  double);
    extern template bool isEqual(const Matrix3x3<double>&, const Matrix3x3<double>&, double);

    /// Matrix4x4
    extern template bool isZero(const Matrix4x4<int>&, double);
    extern template bool isZero(const Matrix4x4<float>&, double);
    extern template bool isZero(const Matrix4x4<double>&, double);

    extern template bool isEqual(const Matrix4x4<int>&, const Matrix4x4<int>&, double);
    extern template bool isEqual(const Matrix4x4<float>&, const Matrix4x4<float>&, double);
    extern template bool isEqual(const Matrix4x4<double>&, const Matrix4x4<double>&, double);

} /// namespace ETL::Math
