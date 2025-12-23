///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix4x4.h
///---------------------------------------------------------------------------- 
#pragma once

#include "MathLib/Common/ElementProxy.h"
#include "MathLib/Common/RawTag.h"
#include "MathLib/Types/Vector4.h"

namespace ETL::Math
{

    /// When using Matrix4x4<int> integral types, values are stored
    /// internally in 16.16 fixed-point format (FIXED_SHIFT = 16).
    /// Normal accessors like operator[] and operator() automatically 
    /// convert to user-expected types.
    /// Use getRawValue()/setRawValue for explicit control storage.

    template<typename Type>
    class Matrix4x4
    {
    public:

        static constexpr int COL_SIZE = 4;
        static constexpr int NUM_ELEM = 16;

        /// Static 2D Transform Factories
        static constexpr Matrix4x4 Zero() { return Matrix4x4{ Type(0) }; }
        static constexpr Matrix4x4 Identity() { return Matrix4x4{ Type(1) }; }
        static Matrix4x4 CreateScale(double sX, double sY, double sZ);
        static Matrix4x4 CreateRotation(double rX, double rY, double rZ);
        static Matrix4x4 CreateTranslation(Type tX, Type tY, Type tZ);

        /// Constructors
        constexpr Matrix4x4() = default;
        explicit constexpr Matrix4x4(Type val);
        constexpr Matrix4x4(Type v00, Type v11, Type v22, Type v33);
        constexpr Matrix4x4(Type v00, Type v01, Type v02, Type v03,
                            Type v10, Type v11, Type v12, Type v13,
                            Type v20, Type v21, Type v22, Type v23,
                            Type v30, Type v31, Type v32, Type v33);
        constexpr Matrix4x4(double v00, double v01, double v02, double v03,
                            double v10, double v11, double v12, double v13,
                            double v20, double v21, double v22, double v23,
                            double v30, double v31, double v32, double v33) requires (!std::same_as<Type, double>);

        /// Copy, Move & Destructor (default)
        Matrix4x4(const Matrix4x4&) = default;
        Matrix4x4(Matrix4x4&&) noexcept = default;
        Matrix4x4& operator=(const Matrix4x4&) = default;
        Matrix4x4& operator=(Matrix4x4&&) noexcept = default;
        ~Matrix4x4() = default;

        /// Access methods
        Type               operator()(int row, int col) const;
        ElementProxy<Type> operator()(int row, int col);
        Type               operator[](int index) const;
        ElementProxy<Type> operator[](int index);

        Vector4<Type> getCol(int colIndex) const;
        Vector4<Type> getRow(int rowIndex) const;
        void getColTo(Vector4<Type>& outCol, int colIndex) const;
        void getRowTo(Vector4<Type>& outRow, int rowIndex) const;

        void setCol(int col, const Vector4<Type>& value);
        void setRow(int row, const Vector4<Type>& value);
        void setCol(int col, Type c0, Type c1, Type c2, Type c3);
        void setRow(int row, Type r0, Type r1, Type r2, Type r3);

        /// Operators
        Matrix4x4     operator+(const Matrix4x4& other) const;
        Matrix4x4     operator-(const Matrix4x4& other) const;
        Matrix4x4     operator*(const Matrix4x4& other) const;
        Vector4<Type> operator*(const Vector4<Type>& vector) const;
        Matrix4x4     operator*(Type scalar) const;
        Matrix4x4     operator/(Type scalar) const;
        Matrix4x4&    operator+=(const Matrix4x4& other);
        Matrix4x4&    operator-=(const Matrix4x4& other);
        Matrix4x4&    operator*=(const Matrix4x4& other);
        Matrix4x4&    operator*=(Type scalar);
        Matrix4x4&    operator/=(Type scalar);
        bool          operator==(const Matrix4x4& other) const;
        bool          operator!=(const Matrix4x4& other) const;

        /// 2D Vector Transformations
        Vector3<Type> transformPoint(const Vector3<Type>& point) const;
        void          transformPointTo(Vector3<Type>& outResult, const Vector3<Type>& inPoint) const;
        void          transformPointInPlace(Vector3<Type>& inOutPoint) const;
        Vector3<Type> transformDirection(const Vector3<Type>& direction) const;
        void          transformDirectionTo(Vector3<Type>& outResult, const Vector3<Type>& inDirection) const;
        void          transformDirectionInPlace(Vector3<Type>& inOutDirection) const;

        /// 2D Transformation modifiers (post multiply: this *= other)
        Matrix4x4&    scale(double sX, double sY, double sZ);
        Matrix4x4&    scale(const Vector3<double>& scale);
        Matrix4x4&    rotate(double rX, double rY, double rZ);
        Matrix4x4&    rotate(const Vector3<double>& rotation);
        Matrix4x4&    translate(Type tX, Type tY, Type tZ);
        Matrix4x4&    translate(const Vector3<Type>& translation);

        /// 2D Transformation setters (override current, leaving rest untouched)
        Matrix4x4&    setScale(double newSX, double newSY, double newSZ);
        Matrix4x4&    setScale(const Vector3<double>& newScale);
        Matrix4x4&    setRotation(double newRX, double newRY, double newRZ);
        Matrix4x4&    setRotation(const Vector3<double>& newRotation);
        Matrix4x4&    setTranslation(Type newTX, Type newTY, Type newTZ);
        Matrix4x4&    setTranslation(const Vector3<Type>& newTranslation);

        /// 2D Transformations Decomposition
        Vector3<double> getScale() const;
        void            getScaleTo(Vector3<double>& outScale) const;
        Vector3<double> getRotation() const;
        void            getRotationTo(Vector3<double>& outRotation) const;
        Vector3<Type>   getTranslation() const;
        void            getTranslationTo(Vector3<Type>& outTranslation) const;

        /// Matrix methods
        Type       determinant(bool bFixedPoint = false) const;
        void       determinantTo(Type& outResult, bool bFixedPoint = false) const;
        Matrix4x4  transpose() const;
        void       transposeTo(Matrix4x4& outResult) const;
        Matrix4x4& makeTranspose();
        Matrix4x4  inverse() const;
        void       inverseTo(Matrix4x4& outResult) const;
        Matrix4x4& makeInverse();

        /// Direct access to internal storage - no conversions applied (use with caution for integral types)
        Type getRawValue(int row, int col) const;
        Type getRawValue(int elem) const;
        void setRawValue(int row, int col, Type value);
        void setRawValue(int elem, Type value);

    protected:
        const Type* const getRawData() const { return mData; }

    private:
        union {
            struct { Type m00, m10, m20, m30, m01, m11, m21, m31,
                          m02, m12, m22, m32, m03, m13, m23, m33; }; /// Named access
            Type m[COL_SIZE][COL_SIZE];                              /// 2D access [COL][ROW]
            Type mData[NUM_ELEM];                                    /// 1D access
        };


        /// Raw constructor
        constexpr Matrix4x4(RawTag, Type v00, Type v01, Type v02, Type v03,
                                    Type v10, Type v11, Type v12, Type v13,
                                    Type v20, Type v21, Type v22, Type v23,
                                    Type v30, Type v31, Type v32, Type v33);
    };


    /// Deduction guide
    template<typename Type>
    Matrix4x4(Type) -> Matrix4x4<Type>;

    template<typename Type>
    Matrix4x4(Type, Type, Type, Type) -> Matrix4x4<Type>;

    template<typename Type>
    Matrix4x4(Type, Type, Type, Type, Type, Type, Type, Type,
              Type, Type, Type, Type, Type, Type, Type, Type) -> Matrix4x4<Type>;


    /// Helpful aliases
    using Mat4 = Matrix4x4<float>;
    using Mat4d = Matrix4x4<double>;
    using Mat4i = Matrix4x4<int>;


    ///------------------------------------------------------------------------------------------
    /// Free functions and common helpers (also present as class member functions.

    /// Matrix * vector
    template<typename Type>
    void Multiply(Vector4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector4<Type>& vec);

    /// Matrix1 * Matrix2
    template<typename Type>
    void Multiply(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& m1, const Matrix4x4<Type>& m2);

    /// GetCol
    template<typename Type>
    void GetCol(Vector4<Type>& outResult, const Matrix4x4<Type>& mat, int index);

    /// GetRow
    template<typename Type>
    void GetRow(Vector4<Type>& outResult, const Matrix4x4<Type>& mat, int index);

    /// SetCol
    template<typename Type>
    void SetCol(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, int index, const Vector4<Type>& col);

    /// SetRow
    template<typename Type>
    void SetRow(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, int index, const Vector4<Type>& row);

    /// TransformPoint
    template<typename Type>
    void TransformPoint(Vector3<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<Type>& point);

    /// TransformDirection
    template<typename Type>
    void TransformDirection(Vector3<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<Type>& direction);

    /// Translate
    template<typename Type>
    void Translate(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<Type>& translation);

    /// SetTranslation
    template<typename Type>
    void SetTranslation(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<Type>& translation);

    /// GetTranslation
    template<typename Type>
    void GetTranslation(Vector3<Type>& outResult, const Matrix4x4<Type>& mat);

    /// Rotate
    template<typename Type>
    void Rotate(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<double>& rotation);

    /// SetRotation
    template<typename Type>
    void SetRotation(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<double>& rotation);

    /// SetRotation
    template<typename Type>
    void GetRotation(Vector3<double>& outResult, const Matrix4x4<Type>& mat);

    /// Scale
    template<typename Type>
    void Scale(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<double>& scale);

    /// SetScaling
    template<typename Type>
    void SetScaling(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat, const Vector3<double>& scale);

    /// SetScaling
    template<typename Type>
    void GetScaling(Vector3<double>& outResult, const Matrix4x4<Type>& mat);

    /// Determinant
    template<typename Type>
    void Determinant(Type& outResult, const Matrix4x4<Type>& mat, bool bFixedPoint = false);

    /// Inverse
    template<typename Type>
    bool Inverse(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat);

    /// Transpose
    template<typename Type>
    void Transpose(Matrix4x4<Type>& outResult, const Matrix4x4<Type>& mat);

    /// Scalar * matrix operator (completeness product commutative)
    template<typename Type>
    Matrix4x4<Type> operator*(Type scalar, const Matrix4x4<Type>& matrix);


    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    extern template class Matrix4x4<float>;
    extern template class Matrix4x4<double>;
    extern template class Matrix4x4<int>;

    extern template void Multiply(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mA, const Matrix4x4<float>&  mB);
    extern template void Multiply(Matrix4x4<double>& outResult, const Matrix4x4<double>& mA, const Matrix4x4<double>& mB);
    extern template void Multiply(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mA, const Matrix4x4<int>&    mB);

    extern template void Multiply(Vector4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector4<float>&  vec);
    extern template void Multiply(Vector4<double>& outResult, const Matrix4x4<double>& mat, const Vector4<double>& vec);
    extern template void Multiply(Vector4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector4<int>&    vec);

    extern template void GetCol(Vector4<float>&  outResult, const Matrix4x4<float>&  mat, int index);
    extern template void GetCol(Vector4<double>& outResult, const Matrix4x4<double>& mat, int index);
    extern template void GetCol(Vector4<int>&    outResult, const Matrix4x4<int>&    mat, int index);

    extern template void GetRow(Vector4<float>&  outResult, const Matrix4x4<float>&  mat, int index);
    extern template void GetRow(Vector4<double>& outResult, const Matrix4x4<double>& mat, int index);
    extern template void GetRow(Vector4<int>&    outResult, const Matrix4x4<int>&    mat, int index);

    extern template void SetCol(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, int index, const Vector4<float>&  col);
    extern template void SetCol(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, int index, const Vector4<double>& col);
    extern template void SetCol(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, int index, const Vector4<int>&    col);

    extern template void SetRow(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, int index, const Vector4<float>&  row);
    extern template void SetRow(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, int index, const Vector4<double>& row);
    extern template void SetRow(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, int index, const Vector4<int>&    row);

    extern template void TransformPoint(Vector3<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<float>&  point);
    extern template void TransformPoint(Vector3<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& point);
    extern template void TransformPoint(Vector3<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<int>&    point);

    extern template void TransformDirection(Vector3<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<float>&  direction);
    extern template void TransformDirection(Vector3<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& direction);
    extern template void TransformDirection(Vector3<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<int>&    direction);

    extern template void Translate(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<float>&  translation);
    extern template void Translate(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& translation);
    extern template void Translate(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<int>&    translation);

    extern template void SetTranslation(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<float>&  translation);
    extern template void SetTranslation(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& translation);
    extern template void SetTranslation(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<int>&    translation);

    extern template void GetTranslation(Vector3<float>&  outResult, const Matrix4x4<float>&  mat);
    extern template void GetTranslation(Vector3<double>& outResult, const Matrix4x4<double>& mat);
    extern template void GetTranslation(Vector3<int>&    outResult, const Matrix4x4<int>&    mat);

    extern template void Rotate(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<double>& rotation);
    extern template void Rotate(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& rotation);
    extern template void Rotate(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<double>& rotation);

    extern template void SetRotation(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<double>& rotation);
    extern template void SetRotation(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& rotation);
    extern template void SetRotation(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<double>& rotation);

    extern template void GetRotation(Vector3<double>& outResult, const Matrix4x4<float>&  mat);
    extern template void GetRotation(Vector3<double>& outResult, const Matrix4x4<double>& mat);
    extern template void GetRotation(Vector3<double>& outResult, const Matrix4x4<int>&    mat);

    extern template void Scale(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<double>& scale);
    extern template void Scale(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& scale);
    extern template void Scale(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<double>& scale);

    extern template void SetScaling(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat, const Vector3<double>& scale);
    extern template void SetScaling(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat, const Vector3<double>& scale);
    extern template void SetScaling(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat, const Vector3<double>& scale);

    extern template void GetScaling(Vector3<double>& outResult, const Matrix4x4<float>&  mat);
    extern template void GetScaling(Vector3<double>& outResult, const Matrix4x4<double>& mat);
    extern template void GetScaling(Vector3<double>& outResult, const Matrix4x4<int>&    mat);

    extern template void Determinant(float&  outResult, const Matrix4x4<float>&  mat, bool bFixedPoint);
    extern template void Determinant(double& outResult, const Matrix4x4<double>& mat, bool bFixedPoint);
    extern template void Determinant(int&    outResult, const Matrix4x4<int>&    mat, bool bFixedPoint);

    extern template bool Inverse(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat);
    extern template bool Inverse(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat);
    extern template bool Inverse(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat);

    extern template void Transpose(Matrix4x4<float>&  outResult, const Matrix4x4<float>&  mat);
    extern template void Transpose(Matrix4x4<double>& outResult, const Matrix4x4<double>& mat);
    extern template void Transpose(Matrix4x4<int>&    outResult, const Matrix4x4<int>&    mat);

    extern template Matrix4x4<float>  operator*(float  scalar, const Matrix4x4<float>&  matrix);
    extern template Matrix4x4<double> operator*(double scalar, const Matrix4x4<double>& matrix);
    extern template Matrix4x4<int>    operator*(int    scalar, const Matrix4x4<int>&    matrix);


} /// namespace ETL::Math

#include "inline/Matrix4x4.inl"
