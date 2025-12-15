///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.h
///---------------------------------------------------------------------------- 
#pragma once

#include "MathLib/Common/ElementProxy.h"
#include "MathLib/Types/Vector3.h"
#include "MathLib/Types/Vector2.h"

namespace ETL::Math
{

    /// When using Matrix3x3<int> integral types, values are stored
    /// internally in 16.16 fixed-point format (FIXED_SHIFT = 16).
    /// Normal accessors like operator[] and operator() automatically 
    /// convert to user-expected types.
    /// Use getRawValue()/setRawValue for explicit control storage.

    template<typename Type>
    class Matrix3x3
    {
    public:

        static constexpr int COL_SIZE = 3;
        static constexpr int NUM_ELEM = 9;

        /// Static 2D Transform Factories
        static constexpr Matrix3x3 Zero() { return Matrix3x3{ Type(0) }; }
        static constexpr Matrix3x3 Identity() { return Matrix3x3{ Type(1) }; }
        static Matrix3x3 Scale(double sX, double sY);
        static Matrix3x3 Rotation(double angleRad);
        static Matrix3x3 Translation(Type tX, Type tY);

        /// Constructors
        constexpr Matrix3x3() = default;
        explicit constexpr Matrix3x3(Type val);
        constexpr Matrix3x3(Type v00, Type v01, Type v02,
                            Type v10, Type v11, Type v12,
                            Type v20, Type v21, Type v22);

        /// Copy, Move & Destructor (default)
        Matrix3x3(const Matrix3x3&) = default;
        Matrix3x3(Matrix3x3&&) noexcept = default;
        Matrix3x3& operator=(const Matrix3x3&) = default;
        Matrix3x3& operator=(Matrix3x3&&) noexcept = default;
        ~Matrix3x3() = default;

        /// Access methods
        Type               operator()(int row, int col) const;
        ElementProxy<Type> operator()(int row, int col);
        Type               operator[](int index) const;
        ElementProxy<Type> operator[](int index);

        Vector3<Type> getCol(int col) const;
        Vector3<Type> getRow(int row) const;
        void getCol(int col, Vector3<Type>& outValue) const;
        void getRow(int row, Vector3<Type>& outValue) const;

        void setCol(int col, const Vector3<Type>& value);
        void setRow(int row, const Vector3<Type>& value);
        void setCol(int col, Type c0, Type c1, Type c2);
        void setRow(int row, Type r0, Type r1, Type r2);

        /// Operators
        Matrix3x3     operator+(const Matrix3x3& other) const;
        Matrix3x3     operator-(const Matrix3x3& other) const;
        Matrix3x3     operator*(const Matrix3x3& other) const;
        Vector3<Type> operator*(const Vector3<Type>& vector) const;
        Matrix3x3     operator*(Type scalar) const;
        Matrix3x3     operator/(Type scalar) const;
        Matrix3x3&    operator+=(const Matrix3x3& other);
        Matrix3x3&    operator-=(const Matrix3x3& other);
        Matrix3x3&    operator*=(const Matrix3x3& other);
        Matrix3x3&    operator*=(Type scalar);
        Matrix3x3&    operator/=(Type scalar);
        bool          operator==(const Matrix3x3& other) const;
        bool          operator!=(const Matrix3x3& other) const;

        /// 2D Vector Transformations
        Vector2<Type> transformPoint(const Vector2<Type>& point) const;
        void          transformPointInPlace(Vector2<Type>& inOutPoint) const;
        Vector2<Type> transformDirection(const Vector2<Type>& direction) const;
        void          transformDirectionInPlace(Vector2<Type>& inOutDirection) const;

        /// 2D Transformation modifiers (post multiply: this *= other)
        Matrix3x3&    scale(double sX, double sY);
        Matrix3x3&    scale(const Vector2<double>& scale);
        Matrix3x3&    rotate(double angleRad);
        Matrix3x3&    translate(Type tX, Type tY);
        Matrix3x3&    translate(const Vector2<Type>& pos);

        /// 2D Transformation setters (override current, leaving rest untouched)
        //Matrix3x3&    setScale(double newScaleX, double newScaleY);
        //Matrix3x3&    setRotation(double newAngleRad);
        //Matrix3x3&    setTranslation(Type newTX, Type newTY);
        //Matrix3x3&    setTranslation(const Vector2<Type>& newTranslation);

        /// 2D Transformations Decomposition
        Vector2<double> getScale() const;
        double          getRotation() const;
        Vector2<Type>   getTranslation() const;

        void            getScale(Vector2<double>& scale) const;
        void            getRotation(double& angleRad) const;
        void            getTranslation(Vector2<Type>& pos) const;

        /// Matrix methods
        Type       determinant(bool bFixedPoint = false) const;
        Matrix3x3  transpose() const;
        Matrix3x3& makeTranspose();
        Matrix3x3  inverse() const;
        Matrix3x3& makeInverse();

        /// Direct access to internal storage - no conversions applied (use with caution for integral types)
        Type getRawValue(int row, int col) const;
        Type getRawValue(int elem) const;
        void setRawValue(int row, int col, Type value);
        void setRawValue(int elem, Type value);

    protected:
        const Type* const getRawData() const { return mData; }

    private:
        union {
            struct { Type m00, m10, m20, m01, m11, m21, m02, m12, m22; }; /// Named access
            Type m[3][3];                                                 /// 2D access
            Type mData[9];                                                /// 1D access
        };


        /// Raw constructor
        struct RawTag {};
        static constexpr RawTag Raw{};
        constexpr Matrix3x3(RawTag, Type v00, Type v01, Type v02,
                            Type v10, Type v11, Type v12,
                            Type v20, Type v21, Type v22);
    };


    /// Deduction guide
    template<typename Type>
    Matrix3x3(Type) -> Matrix3x3<Type>;

    template<typename Type>
    Matrix3x3(Type, Type, Type, Type, Type, Type, Type, Type, Type) -> Matrix3x3<Type>;


    /// Helpful aliases
    using Mat3 = Matrix3x3<float>;
    using Mat3d = Matrix3x3<double>;
    using Mat3i = Matrix3x3<int>;


    /// Scalar * matrix operator 
    template<typename Type>
    Matrix3x3<Type> operator*(Type scalar, const Matrix3x3<Type>& matrix);


    /// Explicit template instantiation (precompiled declaration)
    extern template class Matrix3x3<float>;
    extern template class Matrix3x3<double>;
    extern template class Matrix3x3<int>;

    extern template Matrix3x3<float>  operator*(float  scalar, const Matrix3x3<float>&  matrix);
    extern template Matrix3x3<double> operator*(double scalar, const Matrix3x3<double>& matrix);
    extern template Matrix3x3<int>    operator*(int    scalar, const Matrix3x3<int>&    matrix);


} /// namespace ETL::Math

#include "inline/Matrix3x3.inl"
