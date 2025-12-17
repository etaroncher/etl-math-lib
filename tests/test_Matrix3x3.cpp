///----------------------------------------------------------------------------
/// ETL - MathLib Unit Test
/// test_Matrix3x3.h
///----------------------------------------------------------------------------
#include <catch_amalgamated.hpp>
#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Matrix3x3.h>

#define MATRIX3x3_TYPES int, float, double

TEMPLATE_TEST_CASE("Matrix3x3 Construction & Access", "[Matrix3x3][core]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec3 = ETL::Math::Vector3<TestType>;

    SECTION("Default constructor")
    {
        Matrix m;
        // Default constructor behavior - uninitialized or zero?
        // Add checks based on your implementation
    }

    SECTION("Diagonal matrix constructor")
    {
        const Matrix m{ TestType(5) };
        REQUIRE(m[0] == TestType(5));
        REQUIRE(m[1] == TestType(0));
        REQUIRE(m[2] == TestType(0));
        REQUIRE(m[3] == TestType(0));
        REQUIRE(m[4] == TestType(5));
        REQUIRE(m[5] == TestType(0));
        REQUIRE(m[6] == TestType(0));
        REQUIRE(m[7] == TestType(0));
        REQUIRE(m[8] == TestType(5));
    }

    SECTION("Variable Diagonal matrix constructor")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3) };
        REQUIRE(m[0] == TestType(1));
        REQUIRE(m[1] == TestType(0));
        REQUIRE(m[2] == TestType(0));
        REQUIRE(m[3] == TestType(0));
        REQUIRE(m[4] == TestType(2));
        REQUIRE(m[5] == TestType(0));
        REQUIRE(m[6] == TestType(0));
        REQUIRE(m[7] == TestType(0));
        REQUIRE(m[8] == TestType(3));
    }

    SECTION("Component constructor")
    {
        const Matrix m{ TestType(0), TestType(1), TestType(2),
                        TestType(3), TestType(4), TestType(5), 
                        TestType(6), TestType(7), TestType(8) };

        /// Column major storage
        REQUIRE(m[0] == TestType(0));
        REQUIRE(m[1] == TestType(3));
        REQUIRE(m[2] == TestType(6));
        REQUIRE(m[3] == TestType(1));
        REQUIRE(m[4] == TestType(4));
        REQUIRE(m[5] == TestType(7));
        REQUIRE(m[6] == TestType(2));
        REQUIRE(m[7] == TestType(5));
        REQUIRE(m[8] == TestType(8));
    }

    SECTION("Accessors and Mutators") {
        /// () setter [] getter
        Matrix mA; 

        mA(0, 0) = TestType(0);
        mA(1, 0) = TestType(1);
        mA(2, 0) = TestType(2);
        mA(0, 1) = TestType(3);
        mA(1, 1) = TestType(4);
        mA(2, 1) = TestType(5);
        mA(0, 2) = TestType(6);
        mA(1, 2) = TestType(7);
        mA(2, 2) = TestType(8);

        REQUIRE(mA[0] == TestType(0));
        REQUIRE(mA[1] == TestType(1));
        REQUIRE(mA[2] == TestType(2));
        REQUIRE(mA[3] == TestType(3));
        REQUIRE(mA[4] == TestType(4));
        REQUIRE(mA[5] == TestType(5));
        REQUIRE(mA[6] == TestType(6));
        REQUIRE(mA[7] == TestType(7));
        REQUIRE(mA[8] == TestType(8));

        /// [] setter () getter
        Matrix mB;

        mB[0] = TestType(0);
        mB[1] = TestType(1);
        mB[2] = TestType(2);
        mB[3] = TestType(3);
        mB[4] = TestType(4);
        mB[5] = TestType(5);
        mB[6] = TestType(6);
        mB[7] = TestType(7);
        mB[8] = TestType(8);

        REQUIRE(mB(0, 0) == TestType(0));
        REQUIRE(mB(1, 0) == TestType(1));
        REQUIRE(mB(2, 0) == TestType(2));
        REQUIRE(mB(0, 1) == TestType(3));
        REQUIRE(mB(1, 1) == TestType(4));
        REQUIRE(mB(2, 1) == TestType(5));
        REQUIRE(mB(0, 2) == TestType(6));
        REQUIRE(mB(1, 2) == TestType(7));
        REQUIRE(mB(2, 2) == TestType(8));

        /// GetRow & GetCol (return type and reference argument)
        const Vec3 A_row0 = mA.getRow(0);
        const Vec3 A_row1 = mA.getRow(1);
        const Vec3 A_row2 = mA.getRow(2);
        const Vec3 A_col0 = mA.getCol(0);
        const Vec3 A_col1 = mA.getCol(1);
        const Vec3 A_col2 = mA.getCol(2);

        Vec3 B_row0, B_row1, B_row2, B_col0, B_col1, B_col2;
        mB.getRowTo(B_row0, 0);
        mB.getRowTo(B_row1, 1);
        mB.getRowTo(B_row2, 2);
        mB.getColTo(B_col0, 0);
        mB.getColTo(B_col1, 1);
        mB.getColTo(B_col2, 2);

        REQUIRE(A_row0 == B_row0);
        REQUIRE(A_row1 == B_row1);
        REQUIRE(A_row2 == B_row2);
        REQUIRE(A_col0 == B_col0);
        REQUIRE(A_col1 == B_col1);
        REQUIRE(A_col2 == B_col2);

        /// SetRow & SetCol (return type and reference argument)
        mA.setRow(0, Vec3{ TestType(10) });
        mA.setRow(1, Vec3{ TestType(20) });
        mA.setRow(2, TestType(30), TestType(40), TestType(50));

        REQUIRE(mA(0, 0) == TestType(10));
        REQUIRE(mA(0, 1) == TestType(10));
        REQUIRE(mA(0, 2) == TestType(10));
        REQUIRE(mA(1, 0) == TestType(20));
        REQUIRE(mA(1, 1) == TestType(20));
        REQUIRE(mA(1, 2) == TestType(20));
        REQUIRE(mA(2, 0) == TestType(30));
        REQUIRE(mA(2, 1) == TestType(40));
        REQUIRE(mA(2, 2) == TestType(50));

        mB.setCol(0, Vec3{ TestType(10) });
        mB.setCol(1, Vec3{ TestType(20) });
        mB.setCol(2, TestType(30), TestType(40), TestType(50));

        REQUIRE(mB(0, 0) == TestType(10));
        REQUIRE(mB(1, 0) == TestType(10));
        REQUIRE(mB(2, 0) == TestType(10));
        REQUIRE(mB(0, 1) == TestType(20));
        REQUIRE(mB(1, 1) == TestType(20));
        REQUIRE(mB(2, 1) == TestType(20));
        REQUIRE(mB(0, 2) == TestType(30));
        REQUIRE(mB(1, 2) == TestType(40));
        REQUIRE(mB(2, 2) == TestType(50));
    }

    SECTION("Equality and inequality operators")
    {
        const Matrix mA{ TestType(3) };
        const Matrix mB{ TestType(3) };
        const Matrix mC{ TestType(4) };
        REQUIRE(mA == mB);
        REQUIRE(mA != mC);
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Static Factories", "[Matrix3x3][factories]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    SECTION("Zero matrix")
    {
        const Matrix m = Matrix::Zero();
        for (int i = 0; i < 9; ++i)
            REQUIRE(m[i] == TestType(0));
    }

    SECTION("Identity matrix")
    {
        const Matrix m = Matrix::Identity();
        REQUIRE(m(0, 0) == TestType(1));
        REQUIRE(m(1, 1) == TestType(1));
        REQUIRE(m(2, 2) == TestType(1));
        REQUIRE(m(0, 1) == TestType(0));
        REQUIRE(m(0, 2) == TestType(0));
        REQUIRE(m(1, 0) == TestType(0));
        REQUIRE(m(1, 2) == TestType(0));
        REQUIRE(m(2, 0) == TestType(0));
        REQUIRE(m(2, 1) == TestType(0));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Arithmetic", "[Matrix3x3][math]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    const Matrix mA{ TestType(6) };
    const Matrix mB{ TestType(3) };


    SECTION("Equality and inequality operators")
    {
        const Matrix mA{ TestType(3) };
        const Matrix mB{ TestType(3) };
        const Matrix mC{ TestType(4) };
        REQUIRE(mA == mB);
        REQUIRE(mA != mC);
    }

    SECTION("Addition")
    {
        const Matrix mResult = mA + mB;
        REQUIRE(mResult(0, 0) == TestType(9));
        REQUIRE(mResult(1, 1) == TestType(9));
        REQUIRE(mResult(2, 2) == TestType(9));

        Matrix mResult2 = mA;
        mResult2 += mB;
        REQUIRE(mResult2 == mResult);
    }

    SECTION("Subtraction")
    {
        const Matrix mResult = mA - mB;
        REQUIRE(mResult(0, 0) == TestType(3));
        REQUIRE(mResult(1, 1) == TestType(3));
        REQUIRE(mResult(2, 2) == TestType(3));

        Matrix mResult2 = mA;
        mResult2 -= mB;
        REQUIRE(mResult2 == mResult);
    }

    SECTION("Scalar Multiplication")
    {
        const Matrix mResult = mA * TestType(2);
        REQUIRE(mResult(0, 0) == TestType(12));
        REQUIRE(mResult(1, 1) == TestType(12));
        REQUIRE(mResult(2, 2) == TestType(12));

        Matrix mResult2 = mA;
        mResult2 *= TestType(2);
        REQUIRE(mResult2 == mResult);

        /// Test Commutative Property (s * v)
        const Matrix mResult3 = TestType(2) * mA;
        REQUIRE(mResult3 == mResult);
    }

    SECTION("Scalar Division")
    {
        const Matrix mResult = mA / TestType(2);
        REQUIRE(mResult(0, 0) == TestType(3));
        REQUIRE(mResult(1, 1) == TestType(3));
        REQUIRE(mResult(2, 2) == TestType(3));

        Matrix mResult2 = mA;
        mResult2 /= TestType(2);
        REQUIRE(mResult2 == mResult);
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 isEqual with epsilon - floating", "[Matrix3x3][utils]", float, double)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    const Matrix mA{ TestType(1) };
    const Matrix mB{ TestType(1.0001) };
    const Matrix mC{ TestType(1.1) };

    REQUIRE(ETL::Math::isEqual(mA, mB, TestType(0.001)));
    REQUIRE_FALSE(ETL::Math::isEqual(mA, mC, TestType(0.001)));
    REQUIRE(ETL::Math::isEqual(mA, mC, TestType(0.15)));
}


TEMPLATE_TEST_CASE("Matrix3x3 isEqual with epsilon - integers", "[Matrix3x3][utils]", int)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    const Matrix mA{ TestType(1) };
    const Matrix mB{ TestType(1) };
    const Matrix mC{ TestType(2) };

    REQUIRE(ETL::Math::isEqual(mA, mB, TestType(1)));
    REQUIRE_FALSE(ETL::Math::isEqual(mA, mC, TestType(1)));
    //REQUIRE(ETL::Math::isEqual(mA, mC, TestType(3)));
}


TEMPLATE_TEST_CASE("Matrix3x3 Matrix Multiplication", "[Matrix3x3][math]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    SECTION("Identity multiplication")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(4), TestType(5), TestType(6),
                        TestType(7), TestType(8), TestType(9) };
        const Matrix mIdentity = Matrix::Identity();

        const Matrix mResult1 = m * mIdentity;
        const Matrix mResult2 = mIdentity * m;

        REQUIRE(mResult1 == m);
        REQUIRE(mResult2 == m);
    }

    SECTION("General matrix multiplication")
    {
        // | 1 2 3 |   | 9  8  7 |   | 30  24  18 |
        // | 4 5 6 | * | 6  5  4 | = | 84  69  54 |
        // | 7 8 9 |   | 3  2  1 |   | 138 114 90 |

        const Matrix mA{ TestType(1), TestType(2), TestType(3),
                         TestType(4), TestType(5), TestType(6),
                         TestType(7), TestType(8), TestType(9) };

        const Matrix mB{ TestType(9), TestType(8), TestType(7),
                         TestType(6), TestType(5), TestType(4),
                         TestType(3), TestType(2), TestType(1) };

        const Matrix mExpected{ TestType(30),  TestType(24),  TestType(18),
                                TestType(84),  TestType(69),  TestType(54),
                                TestType(138), TestType(114), TestType(90) };

        const Matrix mResult = mA * mB;

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("Compound assignment")
    {
        Matrix mA{ TestType(2) };
        const Matrix mB{ TestType(3) };
        const Matrix mExpected = mA * mB;

        mA *= mB;
        REQUIRE(mA == mExpected);
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Vector Multiplication", "[Matrix3x3][math]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec3 = ETL::Math::Vector3<TestType>;

    SECTION("Identity matrix vector multiplication")
    {
        const Matrix mIdentity = Matrix::Identity();
        const Vec3 v{ TestType(1), TestType(2), TestType(3) };

        const Vec3 vResult = mIdentity * v;

        REQUIRE(vResult == v);
    }

    SECTION("General matrix vector multiplication")
    {
        // | 1 2 3 |   | 1 |   | 14 |
        // | 4 5 6 | * | 2 | = | 32 |
        // | 7 8 9 |   | 3 |   | 50 |

        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(4), TestType(5), TestType(6),
                        TestType(7), TestType(8), TestType(9) };

        const Vec3 v{ TestType(1), TestType(2), TestType(3) };
        const Vec3 vExpected{ TestType(14), TestType(32), TestType(50) };
        const Vec3 vResult = m * v;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Diagonal matrix vector multiplication")
    {
        const Matrix m{ TestType(2) };
        const Vec3 v{ TestType(3), TestType(4), TestType(5) };
        const Vec3 vExpected{ TestType(6), TestType(8), TestType(10) };

        const Vec3 vResult = m * v;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Determinant", "[Matrix3x3][math]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    SECTION("Identity determinant")
    {
        const Matrix m = Matrix::Identity();
        REQUIRE(ETL::Math::isEqual(m.determinant(), TestType(1)));

        TestType det;
        m.determinantTo(det);
        REQUIRE(ETL::Math::isEqual(det, TestType(1)));
    }

    SECTION("Zero determinant (singular matrix)")
    {
        // Rows are linearly dependent
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(2), TestType(4), TestType(6),
                        TestType(3), TestType(6), TestType(9) };

        REQUIRE(ETL::Math::isEqual(m.determinant(), TestType(0)));

        TestType det;
        m.determinantTo(det);
        REQUIRE(ETL::Math::isEqual(det, TestType(0)));
    }

    SECTION("Non-zero determinant")
    {
        // | 1 2 3 |
        // | 0 1 4 | det = 1*(1*8 - 4*5) - 2*(0*8 - 4*0) + 3*(0*5 - 1*0) = 1*(-12) = -12
        // | 0 5 8 |

        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(0), TestType(1), TestType(4),
                        TestType(0), TestType(5), TestType(8) };

        REQUIRE(ETL::Math::isEqual(m.determinant(), TestType(-12)));

        TestType det;
        m.determinantTo(det);
        REQUIRE(ETL::Math::isEqual(det, TestType(-12)));
    }

    SECTION("Diagonal matrix determinant")
    {
        const Matrix m{ TestType(2), TestType(0), TestType(0),
                        TestType(0), TestType(3), TestType(0),
                        TestType(0), TestType(0), TestType(4) };

        REQUIRE(ETL::Math::isEqual(m.determinant(), TestType(24)));

        TestType det;
        m.determinantTo(det);
        REQUIRE(ETL::Math::isEqual(det, TestType(24)));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Transpose", "[Matrix3x3][math]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    SECTION("Transpose - output arg")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(4), TestType(5), TestType(6),
                        TestType(7), TestType(8), TestType(9) };

        const Matrix mExpected{ TestType(1), TestType(4), TestType(7),
                                TestType(2), TestType(5), TestType(8),
                                TestType(3), TestType(6), TestType(9) };

        Matrix mResult;
        m.transposeTo(mResult);

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("Transpose - return value")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(4), TestType(5), TestType(6),
                        TestType(7), TestType(8), TestType(9) };

        const Matrix mExpected{ TestType(1), TestType(4), TestType(7),
                                TestType(2), TestType(5), TestType(8),
                                TestType(3), TestType(6), TestType(9) };

        const Matrix mResult = m.transpose();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("MakeTranspose - in-place")
    {
        Matrix m{ TestType(1), TestType(2), TestType(3),
                  TestType(4), TestType(5), TestType(6),
                  TestType(7), TestType(8), TestType(9) };

        const Matrix mExpected{ TestType(1), TestType(4), TestType(7),
                                TestType(2), TestType(5), TestType(8),
                                TestType(3), TestType(6), TestType(9) };

        m.makeTranspose();

        REQUIRE(ETL::Math::isEqual(m, mExpected));
    }

    SECTION("Double transpose returns original")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(4), TestType(5), TestType(6),
                        TestType(7), TestType(8), TestType(9) };

        const Matrix mResult = m.transpose().transpose();

        REQUIRE(mResult == m);
    }

    SECTION("Symmetric matrix transpose")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(2), TestType(4), TestType(5),
                        TestType(3), TestType(5), TestType(6) };

        const Matrix mResult = m.transpose();

        REQUIRE(mResult == m);
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Inverse", "[Matrix3x3][math]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    SECTION("Identity inverse")
    {
        const Matrix m = Matrix::Identity();
        Matrix mInverse;
        m.inverseTo(mInverse);

        REQUIRE(mInverse == m);
        REQUIRE(ETL::Math::isEqual(mInverse, m));
    }

    SECTION("Inverse - output arg")
    {
        const Matrix original{ TestType(1), TestType(2), TestType(3),
                               TestType(0), TestType(1), TestType(4),
                               TestType(5), TestType(6), TestType(0) };

        Matrix m;
        original.inverseTo(m);
        const Matrix mResult = m * original;
        const Matrix mExpected = Matrix::Identity();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("Inverse property: M * M^-1 = I")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(0), TestType(1), TestType(4),
                        TestType(5), TestType(6), TestType(0) };

        const Matrix mInverse = m.inverse();
        const Matrix mResult = m * mInverse;
        const Matrix mExpected = Matrix::Identity();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("MakeInverse - in-place")
    {
        const Matrix original{ TestType(1), TestType(2), TestType(3),
                  TestType(0), TestType(1), TestType(4),
                  TestType(5), TestType(6), TestType(0) };

        Matrix m = original;
        m.makeInverse();
        const Matrix mResult = m * original;
        const Matrix mExpected = Matrix::Identity();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("Double inverse returns original")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(0), TestType(1), TestType(4),
                        TestType(5), TestType(6), TestType(0) };

        const Matrix mResult = m.inverse().inverse();

        REQUIRE(ETL::Math::isEqual(mResult, m));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 2D Transformations Factories", "[Matrix3x3][transform]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;
    constexpr double PI_HALF = 3.14159265358979323846 / 2.0;

    SECTION("Scale static factory")
    {
        const Matrix mScale = Matrix::CreateScale(TestType(2), TestType(3));
        const Matrix mExpected{ TestType(2), TestType(0), TestType(0),
                                TestType(0), TestType(3), TestType(0),
                                TestType(0), TestType(0), TestType(1) };

        REQUIRE(ETL::Math::isEqual(mScale, mExpected));
    }

    SECTION("Rotation static factory")
    {
        const Matrix mRot = Matrix::CreateRotation(PI_HALF); // 90 degrees
        const Matrix mExpected{ TestType(0), TestType(-1), TestType(0),
                                TestType(1), TestType(0),  TestType(0),
                                TestType(0), TestType(0),  TestType(1) };

        REQUIRE(ETL::Math::isEqual(mRot, mExpected));
    }

    SECTION("Translation static factory")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20));
        const Matrix mExpected{ TestType(1), TestType(0), TestType(10),
                                TestType(0), TestType(1), TestType(20),
                                TestType(0), TestType(0), TestType(1) };

        REQUIRE(ETL::Math::isEqual(mTrans, mExpected));;
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 2D Transform Point & Direction", "[Matrix3x3][transform]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;
    constexpr double PI_HALF = 3.14159265358979323846 / 2.0;

    SECTION("TransformPoint - output arg")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20));
        const Vec2 vPoint{ TestType(5), TestType(3) };
        const Vec2 vExpected{ TestType(15), TestType(23) };

        Vec2 vResult;
        mTrans.transformPointTo(vResult, vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformPoint - return value")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20));
        const Vec2 vPoint{ TestType(5), TestType(3) };
        const Vec2 vExpected{ TestType(15), TestType(23) };

        const Vec2 vResult = mTrans.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformPoint - in-place")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20));
        Vec2 vPoint{ TestType(5), TestType(3) };
        const Vec2 vExpected{ TestType(15), TestType(23) };

        mTrans.transformPointInPlace(vPoint);

        REQUIRE(ETL::Math::isEqual(vPoint, vExpected));
    }

    SECTION("TransformDirection - output arg")
    {
        const Matrix mRot = Matrix::CreateRotation(PI_HALF);
        const Vec2 vDirection{ TestType(1), TestType(0) };
        const Vec2 vExpected{ TestType(0), TestType(1) };

        Vec2 vResult;
        mRot.transformDirectionTo(vResult, vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformDirection - return value")
    {
        const Matrix mRot = Matrix::CreateRotation(PI_HALF);
        const Vec2 vDirection{ TestType(1), TestType(0) };
        const Vec2 vExpected{ TestType(0), TestType(1) };

        const Vec2 vResult = mRot.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformDirection - in-place")
    {
        const Matrix mRot = Matrix::CreateRotation(PI_HALF);
        Vec2 vDirection{ TestType(1), TestType(0) };
        const Vec2 vExpected{ TestType(0), TestType(1) };

        mRot.transformDirectionInPlace(vDirection);

        REQUIRE(ETL::Math::isEqual(vDirection, vExpected));
    }

    SECTION("TransformDirection ignores translation")
    {
        /// Translation should not affect directions
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20));
        const Vec2 vDirection{ TestType(1), TestType(0) };

        const Vec2 vResult = mTrans.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vDirection));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 2D Transform - Rotation uncommon angle", "[Matrix3x3][transform]", int)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;

    SECTION("Rotation weird angle - return value")
    {
        const Matrix mRot = Matrix::CreateRotation(0.3948);
        const Vec2 vDirection{ TestType(13), TestType(0) };
        const Vec2 vExpected{ TestType(12), TestType(5) };

        const Vec2 vResult = mRot.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected, 2));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 2D Transform - Rotation uncommon angle", "[Matrix3x3][transform]", float, double)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;

    SECTION("Rotation weird angle - return value")
    {
        const Matrix mRot = Matrix::CreateRotation(0.3948);
        const Vec2 vDirection{ TestType(13), TestType(0) };
        const Vec2 vExpected{ TestType(12), TestType(5) };

        const Vec2 vResult = mRot.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected, TestType(0.001)));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 2D Transform Methods", "[Matrix3x3][transform]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;
    constexpr double PI_HALF = 3.14159265358979323846 / 2.0;

    SECTION("Scale method (post-multiply)")
    {
        const Matrix mScale = Matrix::Identity().scale(2.0, 3.0);
        const Vec2 vPoint{ TestType(4), TestType(5) };
        const Vec2 vExpected{ TestType(8), TestType(15) };
        const Vec2 vResult = mScale.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Rotate method (post-multiply)")
    {
        const Matrix mRot = Matrix::Identity().rotate(PI_HALF); // 90 degrees
        const Vec2 vPoint{ TestType(1), TestType(0) };
        const Vec2 vExpected{ TestType(0), TestType(1) };
        const Vec2 vResult = mRot.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Translate method (post-multiply)")
    {
        const Matrix mTrans = Matrix::Identity().translate(TestType(10), TestType(20));
        const Vec2 vPoint{ TestType(5), TestType(3) };
        const Vec2 vExpected{ TestType(15), TestType(23) };
        const Vec2 vResult = mTrans.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Combined transformations & TRS order)")
    {
        const ETL::Math::Vector2<double> scale{ 2.0, 2.0 };
        const ETL::Math::Vector2<TestType> translation{ TestType(10), TestType(0) };

        /// Translate, then Rotate, then Scale
        Matrix mA = Matrix::Identity();
        mA.translate(translation);
        mA.rotate(PI_HALF); // 90 degrees
        mA.scale(scale);

        const Vec2 vPoint{ TestType(1), TestType(0) }; /// Point (1,0) -> scale<2> -> (2, 0) -> rotate<90°> -> (0, 2) -> translate<10,0> -> (10, 2)
        const Vec2 vExpected{ TestType(10), TestType(2) };
        const Vec2 vResult = mA.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));

        /// Order of chained method calls does not matter
        const Matrix mB = Matrix::Identity().translate(translation).rotate(PI_HALF).scale(scale); /// T*R*S -> TRS
        const Matrix mC = Matrix::Identity().translate(translation).scale(scale).rotate(PI_HALF); /// T*S*R -> TRS
        const Matrix mD = Matrix::Identity().rotate(PI_HALF).translate(translation).scale(scale); /// R*T*S -> TRS
        const Matrix mE = Matrix::Identity().rotate(PI_HALF).scale(scale).translate(translation); /// R*S*T -> TRS 
        const Matrix mF = Matrix::Identity().scale(scale).translate(translation).rotate(PI_HALF); /// S*T*R -> TRS
        const Matrix mG = Matrix::Identity().scale(scale).rotate(PI_HALF).translate(translation); /// S*R*T -> TRS

        REQUIRE(ETL::Math::isEqual(mA, mB));
        REQUIRE(ETL::Math::isEqual(mA, mC));
        REQUIRE(ETL::Math::isEqual(mA, mD));
        REQUIRE(ETL::Math::isEqual(mA, mE));
        REQUIRE(ETL::Math::isEqual(mA, mF));
        REQUIRE(ETL::Math::isEqual(mA, mG));

        /// Order of chained Mat * Mat does matter
        const Matrix mH = Matrix::CreateTranslation(translation.x(), translation.y()) * Matrix::CreateRotation(PI_HALF) * Matrix::CreateScale(scale.x(), scale.y());
        const Matrix mI = Matrix::CreateScale(scale.x(), scale.y()) * Matrix::CreateRotation(PI_HALF) * Matrix::CreateTranslation(translation.x(), translation.y());
        REQUIRE(ETL::Math::isEqual(mA, mH));
        REQUIRE_FALSE(ETL::Math::isEqual(mA, mI));
    }

    SECTION("Transform setters - overwrite current values")
    {
        const ETL::Math::Vector2<double>   newScale{ 6.0, 6.0 };
        const double                       newRotation{ PI_HALF*2 };
        const ETL::Math::Vector2<TestType> newTranslation{ TestType(5), TestType(15) };

        const Matrix mExpected = Matrix::Identity().translate(newTranslation).rotate(newRotation).scale(newScale);

        /// Resulting should be same as mExpected
        Matrix mA = Matrix::Identity().translate(TestType(10), TestType(0)).rotate(PI_HALF).scale(2.0, 2.0);
        mA.setTranslation(newTranslation);
        mA.setRotation(newRotation);
        mA.setScale(newScale);

        ///  Check order does not matter
        const Matrix mB = Matrix::Identity().setTranslation(newTranslation).setRotation(newRotation).setScale(newScale); /// T*R*S -> TRS
        const Matrix mC = Matrix::Identity().setTranslation(newTranslation).setScale(newScale).setRotation(newRotation); /// T*S*R -> TRS
        const Matrix mD = Matrix::Identity().setRotation(newRotation).setTranslation(newTranslation).setScale(newScale); /// R*T*S -> TRS
        const Matrix mE = Matrix::Identity().setRotation(newRotation).setScale(newScale).setTranslation(newTranslation); /// R*S*T -> TRS
        const Matrix mF = Matrix::Identity().setScale(newScale).setTranslation(newTranslation).setRotation(newRotation); /// S*T*R -> TRS
        const Matrix mG = Matrix::Identity().setScale(newScale).setRotation(newRotation).setTranslation(newTranslation); /// S*R*T -> TRS

        REQUIRE(ETL::Math::isEqual(mA, mExpected));
        REQUIRE(ETL::Math::isEqual(mB, mExpected));
        REQUIRE(ETL::Math::isEqual(mC, mExpected));
        REQUIRE(ETL::Math::isEqual(mD, mExpected));
        REQUIRE(ETL::Math::isEqual(mE, mExpected));
        REQUIRE(ETL::Math::isEqual(mF, mExpected));
        REQUIRE(ETL::Math::isEqual(mG, mExpected));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Transform Decomposition", "[Matrix3x3][transform]", MATRIX3x3_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;
    constexpr double PI = 3.14159265358979323846;

    SECTION("GetScale from scale matrix")
    {
        const ETL::Math::Vector2<double> vExpected{ 2.0, 3.0 };
        const Matrix mScale = Matrix::CreateScale(vExpected.x(), vExpected.y());

        const ETL::Math::Vector2<double> vScale1 = mScale.getScale();
        REQUIRE(ETL::Math::isEqual(vScale1, vExpected, 0.001));

        ETL::Math::Vector2<double> vScale2;
        mScale.getScaleTo(vScale2);
        REQUIRE(ETL::Math::isEqual(vScale2, vExpected, 0.001));
    }

    SECTION("GetRotation from rotation matrix")
    {
        const double angle = PI / 4.0; /// 45 degrees
        const Matrix mRot = Matrix::CreateRotation(angle);

        const double extractedAngle1 = mRot.getRotation();
        REQUIRE(ETL::Math::isEqual(extractedAngle1, angle, 0.001));

        double extractedAngle2;
        mRot.getRotationTo(extractedAngle2);
        REQUIRE(ETL::Math::isEqual(extractedAngle2, angle, 0.001));
    }

    SECTION("GetTranslation from translation matrix")
    {
        const Vec2 vExpected{ TestType(10), TestType(20) };
        const Matrix mTrans = Matrix::CreateTranslation(vExpected.x(), vExpected.y());

        const Vec2 vTranslation1 = mTrans.getTranslation();
        REQUIRE(ETL::Math::isEqual(vTranslation1, vExpected));

        Vec2 vTranslation2;
        mTrans.getTranslationTo(vTranslation2);
        REQUIRE(ETL::Math::isEqual(vTranslation2, vExpected));
    }

    SECTION("Decompose combined transformation")
    {
        constexpr double angle = PI / 6.0; /// 30 degrees
        Matrix mA = Matrix::Identity();
        mA.translate(TestType(5), TestType(10));
        mA.rotate(angle); 
        mA.scale(2.0, 3.0);

        const auto vScale = mA.getScale();
        const double rotation = mA.getRotation();
        const Vec2 vTranslation = mA.getTranslation();
        const Vec2 vExpectedTrans{ TestType(5), TestType(10) };
        const auto vExpectedScale = ETL::Math::Vector2{ 2.0, 3.0 };

        /// Note: Decomposition may not be exact due to combined transforms, 
        /// Just check that values are reasonable enough
        REQUIRE(ETL::Math::isEqual(vScale, vExpectedScale, 0.001));
        REQUIRE(ETL::Math::isEqual(rotation, angle, 0.001));
        REQUIRE(ETL::Math::isEqual(vTranslation, vExpectedTrans));
    }
}
