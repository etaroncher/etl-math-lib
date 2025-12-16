///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.h
///---------------------------------------------------------------------------- 
#pragma once

#include "MathLib/Common/ElementProxy.h"
#include "MathLib/Common/RawTag.h"
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
        static Matrix3x3 CreateScale(double sX, double sY);
        static Matrix3x3 CreateRotation(double angleRad);
        static Matrix3x3 CreateTranslation(Type tX, Type tY);

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

        Vector3<Type> getCol(int colIndex) const;
        Vector3<Type> getRow(int rowIndex) const;
        void getColTo(Vector3<Type>& outCol, int colIndex) const;
        void getRowTo(Vector3<Type>& outRow, int rowIndex) const;

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
        void          transformPointTo(Vector2<Type>& outResult, const Vector2<Type>& inPoint) const;
        void          transformPointInPlace(Vector2<Type>& inOutPoint) const;
        Vector2<Type> transformDirection(const Vector2<Type>& direction) const;
        void          transformDirectionTo(Vector2<Type>& outResult, const Vector2<Type>& inDirection) const;
        void          transformDirectionInPlace(Vector2<Type>& inOutDirection) const;

        /// 2D Transformation modifiers (post multiply: this *= other)
        Matrix3x3&    scale(double sX, double sY);
        Matrix3x3&    scale(const Vector2<double>& scale);
        Matrix3x3&    rotate(double angleRad);
        Matrix3x3&    translate(Type tX, Type tY);
        Matrix3x3&    translate(const Vector2<Type>& translation);

        /// 2D Transformation setters (override current, leaving rest untouched)
        Matrix3x3&    setScale(double newSX, double newSY);
        Matrix3x3&    setScale(const Vector2<double>& newScale);
        Matrix3x3&    setRotation(double newAngleRad);
        Matrix3x3&    setTranslation(Type newTX, Type newTY);
        Matrix3x3&    setTranslation(const Vector2<Type>& newTranslation);

        /// 2D Transformations Decomposition
        Vector2<double> getScale() const;
        void            getScaleTo(Vector2<double>& outScale) const;
        double          getRotation() const;
        void            getRotationTo(double& outAngleRad) const;
        Vector2<Type>   getTranslation() const;
        void            getTranslationTo(Vector2<Type>& outTranslation) const;

        /// Matrix methods
        Type       determinant(bool bFixedPoint = false) const;
        void       determinantTo(Type& outResult, bool bFixedPoint = false) const;
        Matrix3x3  transpose() const;
        void       transposeTo(Matrix3x3& outResult) const;
        Matrix3x3& makeTranspose();
        Matrix3x3  inverse() const;
        void       inverseTo(Matrix3x3& outResult) const;
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


    ///------------------------------------------------------------------------------------------
    /// Free functions and common helpers (also present as class member functions.

    /// Matrix * vector
    template<typename Type>
    void Multiply(Vector3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector3<Type>& vec);

    /// Matrix1 * Matrix2
    template<typename Type>
    void Multiply(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& m1, const Matrix3x3<Type>& m2);

    /// Determinant
    template<typename Type>
    void Determinant(Type& outResult, const Matrix3x3<Type>& mat, bool bFixedPoint = false);

    /// Inverse
    template<typename Type>
    void Inverse(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat);

    /// Transpose
    template<typename Type>
    void Transpose(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat);

    /// Translate
    template<typename Type>
    void Translate(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector2<Type>& translation);

    /// SetTranslation
    template<typename Type>
    void SetTranslation(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector2<Type>& translation);

    /// GetTranslation
    template<typename Type>
    void GetTranslation(Vector2<Type>& outResult, const Matrix3x3<Type>& mat);

    /// Rotate
    template<typename Type>
    void Rotate(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, double angleRad);

    /// SetRotation
    template<typename Type>
    void SetRotation(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, double angleRad);

    /// SetRotation
    template<typename Type>
    void GetRotation(double& outResult, const Matrix3x3<Type>& mat);

    /// Scale
    template<typename Type>
    void Scale(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector2<double>& scale);

    /// SetScaling
    template<typename Type>
    void SetScaling(Matrix3x3<Type>& outResult, const Matrix3x3<Type>& mat, const Vector2<double>& scale);

    /// SetScaling
    template<typename Type>
    void GetScaling(Vector2<double>& outResult, const Matrix3x3<Type>& mat);

    /// Scalar * matrix operator (completeness product commutative)
    template<typename Type>
    Matrix3x3<Type> operator*(Type scalar, const Matrix3x3<Type>& matrix);


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    extern template class Matrix3x3<float>;
    extern template class Matrix3x3<double>;
    extern template class Matrix3x3<int>;

    extern template void Multiply(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mA, const Matrix3x3<float>&  mB);
    extern template void Multiply(Matrix3x3<double>& outResult, const Matrix3x3<double>& mA, const Matrix3x3<double>& mB);
    extern template void Multiply(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mA, const Matrix3x3<int>&    mB);

    extern template void Multiply(Vector3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector3<float>&  vec);
    extern template void Multiply(Vector3<double>& outResult, const Matrix3x3<double>& mat, const Vector3<double>& vec);
    extern template void Multiply(Vector3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector3<int>&    vec);

    extern template void Determinant(float&  outResult, const Matrix3x3<float>&  mat, bool bFixedPoint);
    extern template void Determinant(double& outResult, const Matrix3x3<double>& mat, bool bFixedPoint);
    extern template void Determinant(int&    outResult, const Matrix3x3<int>&    mat, bool bFixedPoint);

    extern template void Inverse(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat);
    extern template void Inverse(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat);
    extern template void Inverse(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat);

    extern template void Transpose(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat);
    extern template void Transpose(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat);
    extern template void Transpose(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat);

    extern template void Translate(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<float>&  translation);
    extern template void Translate(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& translation);
    extern template void Translate(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<int>&    translation);

    extern template void SetTranslation(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<float>&  translation);
    extern template void SetTranslation(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& translation);
    extern template void SetTranslation(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<int>&    translation);

    extern template void GetTranslation(Vector2<float>&  outResult, const Matrix3x3<float>&  mat);
    extern template void GetTranslation(Vector2<double>& outResult, const Matrix3x3<double>& mat);
    extern template void GetTranslation(Vector2<int>&    outResult, const Matrix3x3<int>&    mat);

    extern template void Rotate(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, double angleRad);
    extern template void Rotate(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, double angleRad);
    extern template void Rotate(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, double angleRad);

    extern template void SetRotation(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, double angleRad);
    extern template void SetRotation(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, double angleRad);
    extern template void SetRotation(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, double angleRad);

    extern template void GetRotation(double& outResult, const Matrix3x3<float>&  mat);
    extern template void GetRotation(double& outResult, const Matrix3x3<double>& mat);
    extern template void GetRotation(double& outResult, const Matrix3x3<int>&    mat);

    extern template void Scale(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<double>& scale);
    extern template void Scale(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& scale);
    extern template void Scale(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<double>& scale);

    extern template void SetScaling(Matrix3x3<float>&  outResult, const Matrix3x3<float>&  mat, const Vector2<double>& scale);
    extern template void SetScaling(Matrix3x3<double>& outResult, const Matrix3x3<double>& mat, const Vector2<double>& scale);
    extern template void SetScaling(Matrix3x3<int>&    outResult, const Matrix3x3<int>&    mat, const Vector2<double>& scale);

    extern template void GetScaling(Vector2<double>& outResult, const Matrix3x3<float>&  mat);
    extern template void GetScaling(Vector2<double>& outResult, const Matrix3x3<double>& mat);
    extern template void GetScaling(Vector2<double>& outResult, const Matrix3x3<int>&    mat);

    extern template Matrix3x3<float>  operator*(float  scalar, const Matrix3x3<float>&  matrix);
    extern template Matrix3x3<double> operator*(double scalar, const Matrix3x3<double>& matrix);
    extern template Matrix3x3<int>    operator*(int    scalar, const Matrix3x3<int>&    matrix);


} /// namespace ETL::Math

#include "inline/Matrix3x3.inl"
