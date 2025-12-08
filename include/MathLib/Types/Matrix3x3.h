///----------------------------------------------------------------------------
/// ETL - MathLib
/// Matrix3x3.h
///---------------------------------------------------------------------------- 
#pragma once

#include <MathLib/Types/Vector3.h>

namespace ETL::Math
{

    template<typename Type>
    class Matrix3x3
    {
    public:

        /// Constructors
        constexpr Matrix3x3();
        constexpr Matrix3x3(Type val);
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
        Type  operator()(int row, int col) const;
        Type& operator()(int row, int col);
        Type  operator[](int index) const;
        Type& operator[](int index);

        Vector3<Type> getCol(int col) const;
        Vector3<Type> getRow(int row) const;

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
        Matrix3x3&    operator+=(const Matrix3x3& other);
        Matrix3x3&    operator-=(const Matrix3x3& other);
        Matrix3x3&    operator*=(const Matrix3x3& other);
        Matrix3x3&    operator*=(Type scalar);
        bool          operator==(const Matrix3x3& other) const;
        bool          operator!=(const Matrix3x3& other) const;

        /// Matrix methods
        Type       determinant() const;
        Matrix3x3  transpose() const;
        Matrix3x3& makeTranspose();
        Matrix3x3  inverse() const;
        Matrix3x3& makeInverse();

        /// Common constants
        static constexpr Matrix3x3 zero()     { return {}; }
        static constexpr Matrix3x3 identity() { return { Type(1) }; }

        /// Scale Matrices
        static Matrix3x3 scale(Type s);
        static Matrix3x3 scale(Type sx, Type sy, Type sz);
        static Matrix3x3 scale(const Vector3<Type>& s);

        /// Rotation Matrices
        static Matrix3x3 rotationX(Type angleRadians);
        static Matrix3x3 rotationY(Type angleRadians);
        static Matrix3x3 rotationZ(Type angleRadians);
        static Matrix3x3 rotation (Type angleRadians, const Vector3<Type>& axis);
        static Matrix3x3 rotationEuler(Type pitch, Type yaw, Type roll);

    protected:
        const Type* const getRawData() const { return mData; }

    private:
        union {
            struct { Type m00, m10, m20, m01, m11, m21, m02, m12, m22; }; /// 1D access
            Type m[3][3];                                                 /// 2D access
            Type mData[9];                                                /// Named access
        };
    };


    /// Scalar * matrix operator 
    template<typename MatrixType, typename ScalarType>
    Matrix3x3<MatrixType> operator*(ScalarType scalar, const Matrix3x3<MatrixType>& matrix);


    /// Helpful aliases
    using Mat3  = Matrix3x3<float>;
    using Mat3d = Matrix3x3<double>;


    /// Explicit template instantiatio (precompiled declaration)
    extern template class Matrix3x3<float>;
    extern template class Matrix3x3<double>;

    extern template Matrix3x3<float>  operator*(float  scalar, const Matrix3x3<float>&  matrix);
    extern template Matrix3x3<double> operator*(double scalar, const Matrix3x3<double>& matrix);


} /// namespace ETL::Math
