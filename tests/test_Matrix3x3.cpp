///----------------------------------------------------------------------------
/// ETL - MathLib Unit Test
/// test_Matrix3x3.h
///----------------------------------------------------------------------------
#include <catch_amalgamated.hpp>
#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Matrix3x3.h>

#define ALL_TYPES /*int,*/ float, double

TEMPLATE_TEST_CASE("Matrix3x3 Construction & Access", "[Matrix3x3][core]", ALL_TYPES)
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
        mB.getRow(0, B_row0);
        mB.getRow(1, B_row1);
        mB.getRow(2, B_row2);
        mB.getCol(0, B_col0);
        mB.getCol(1, B_col1);
        mB.getCol(2, B_col2);

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


TEMPLATE_TEST_CASE("Matrix3x3 Static Factories", "[Matrix3x3][factories]", ALL_TYPES)
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


TEMPLATE_TEST_CASE("Matrix3x3 Arithmetic", "[Matrix3x3][math]", ALL_TYPES)
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


TEMPLATE_TEST_CASE("Matrix3x3 Matrix Multiplication", "[Matrix3x3][math]", ALL_TYPES)
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


TEMPLATE_TEST_CASE("Matrix3x3 Vector Multiplication", "[Matrix3x3][math]", ALL_TYPES)
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


TEMPLATE_TEST_CASE("Matrix3x3 Determinant", "[Matrix3x3][math]", ALL_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    SECTION("Identity determinant")
    {
        const Matrix m = Matrix::Identity();
        REQUIRE(ETL::Math::isEqual(m.determinant(), TestType(1)));
    }

    SECTION("Zero determinant (singular matrix)")
    {
        // Rows are linearly dependent
        const Matrix m{ TestType(1), TestType(2), TestType(3),
                        TestType(2), TestType(4), TestType(6),
                        TestType(3), TestType(6), TestType(9) };

        REQUIRE(ETL::Math::isEqual(m.determinant(), TestType(0)));
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
    }

    SECTION("Diagonal matrix determinant")
    {
        const Matrix m{ TestType(2), TestType(0), TestType(0),
                        TestType(0), TestType(3), TestType(0),
                        TestType(0), TestType(0), TestType(4) };

        REQUIRE(ETL::Math::isEqual(m.determinant(), TestType(24)));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Transpose", "[Matrix3x3][math]", ALL_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

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


TEMPLATE_TEST_CASE("Matrix3x3 Inverse", "[Matrix3x3][math]", ALL_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;

    SECTION("Identity inverse")
    {
        const Matrix m = Matrix::Identity();
        const Matrix mInverse = m.inverse();

        REQUIRE(mInverse == m);
        REQUIRE(ETL::Math::isEqual(mInverse, m));
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


TEMPLATE_TEST_CASE("Matrix3x3 2D Transformations Factories", "[Matrix3x3][transform]", ALL_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;
    constexpr double PI_HALF = 3.14159265358979323846 / 2.0;

    SECTION("Scale static factory")
    {
        const Matrix mScale = Matrix::Scale(2.0, 3.0);
        const Matrix mExpected{ TestType(2), TestType(0), TestType(0),
                                TestType(0), TestType(3), TestType(0),
                                TestType(0), TestType(0), TestType(1) };

        REQUIRE(ETL::Math::isEqual(mScale, mExpected));
    }

    SECTION("Rotation static factory")
    {
        const Matrix mRot = Matrix::Rotation(PI_HALF); // 90 degrees
        const Matrix mExpected{ TestType(0), TestType(-1), TestType(0),
                                TestType(1), TestType(0),  TestType(0),
                                TestType(0), TestType(0),  TestType(1) };

        REQUIRE(ETL::Math::isEqual(mRot, mExpected));
    }

    SECTION("Translation static factory")
    {
        const Matrix mTrans = Matrix::Translation(TestType(10), TestType(20));
        const Matrix mExpected{ TestType(1), TestType(0), TestType(10),
                                TestType(0), TestType(1), TestType(20),
                                TestType(0), TestType(0), TestType(1) };

        REQUIRE(ETL::Math::isEqual(mTrans, mExpected));;
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 2D Transformations", "[Matrix3x3][transform]", ALL_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;
    constexpr double PI_HALF = 3.14159265358979323846 / 2.0;

    SECTION("TransformPoint - return value")
    {
        // Translation matrix: move by (10, 20)
        const Matrix mTrans = Matrix::Translation(TestType(10), TestType(20));
        const Vec2 vPoint{ TestType(5), TestType(3) };
        const Vec2 vExpected{ TestType(15), TestType(23) };

        const Vec2 vResult = mTrans.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformPoint - in-place")
    {
        const Matrix mTrans = Matrix::Translation(TestType(10), TestType(20));
        Vec2 vPoint{ TestType(5), TestType(3) };
        const Vec2 vExpected{ TestType(15), TestType(23) };

        mTrans.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vPoint, vExpected));
    }

    SECTION("TransformDirection - return value")
    {
        // Rotation 90 degrees: (1, 0) -> (0, 1)
        const Matrix mRot = Matrix::Rotation(PI_HALF);
        const Vec2 vDirection{ TestType(1), TestType(0) };
        const Vec2 vExpected{ TestType(0), TestType(1) };

        const Vec2 vResult = mRot.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformDirection - in-place")
    {
        const Matrix mRot = Matrix::Rotation(PI_HALF);
        Vec2 vDirection{ TestType(1), TestType(0) };
        const Vec2 vExpected{ TestType(0), TestType(1) };

        mRot.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vDirection, vExpected));
    }

    SECTION("TransformDirection ignores translation")
    {
        // Translation should not affect directions
        const Matrix mTrans = Matrix::Translation(TestType(10), TestType(20));
        const Vec2 vDirection{ TestType(1), TestType(0) };

        const Vec2 vResult = mTrans.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vDirection));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 2D Transform Methods", "[Matrix3x3][transform]", ALL_TYPES)
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

    SECTION("Combined transformations (TRS order)")
    {
        /// Translate, then Rotate, then Scale
        Matrix mA = Matrix::Identity();
        mA.translate(TestType(10), TestType(0));
        mA.rotate(PI_HALF); // 90 degrees
        mA.scale(2.0, 2.0);

        const Vec2 vPoint{ TestType(1), TestType(0) }; /// Point (1,0) -> translate -> (11, 0) -> rotate 90° -> (0, 11) -> scale 2x -> (0, 22)
        const Vec2 vExpected{ TestType(0), TestType(22) };
        const Vec2 vResult = mA.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));

        /// Chained function calls and chained Mat * Mat
        const Matrix mB = Matrix::Identity().translate(TestType(10), TestType(0)).rotate(PI_HALF).scale(2.0, 2.0);
        const Matrix mC = Matrix::Translation(TestType(10), TestType(0)).rotate(PI_HALF).scale(2.0, 2.0);
        const Matrix mD = Matrix::Translation(TestType(10), TestType(0)) * Matrix::Rotation(PI_HALF) * Matrix::Scale(2.0, 2.0);

        REQUIRE(ETL::Math::isEqual(mA, mB));
        REQUIRE(ETL::Math::isEqual(mA, mC));
        REQUIRE(ETL::Math::isEqual(mA, mD));
    }
}


TEMPLATE_TEST_CASE("Matrix3x3 Transform Decomposition", "[Matrix3x3][transform]", ALL_TYPES)
{
    using Matrix = ETL::Math::Matrix3x3<TestType>;
    using Vec2 = ETL::Math::Vector2<TestType>;
    constexpr double PI = 3.14159265358979323846;

    SECTION("GetScale from scale matrix")
    {
        const Matrix mScale = Matrix::Scale(2.0, 3.0);
        const ETL::Math::Vector2<double> vScale = mScale.getScale();
        const ETL::Math::Vector2<double> vExpected{ 2.0, 3.0 };

        REQUIRE(ETL::Math::isEqual(vScale, vExpected));
    }

    SECTION("GetRotation from rotation matrix")
    {
        const double angle = PI / 4.0; /// 45 degrees
        const Matrix mRot = Matrix::Rotation(angle);
        const double extractedAngle = mRot.getRotation();

        REQUIRE(ETL::Math::isEqual(extractedAngle, angle));
    }

    SECTION("GetTranslation from translation matrix")
    {
        const Matrix mTrans = Matrix::Translation(TestType(10), TestType(20));
        const Vec2 vTranslation = mTrans.getTranslation();
        const Vec2 vExpected{ TestType(10), TestType(20) };

        REQUIRE(ETL::Math::isEqual(vTranslation, vExpected));
    }

    SECTION("Decompose combined transformation")
    {
        Matrix mA = Matrix::Identity();
        mA.translate(TestType(5), TestType(10));
        mA.rotate(PI / 6.0); /// 30 degrees
        mA.scale(2.0, 3.0);

        const auto vScale = mA.getScale();
        const double rotation = mA.getRotation();
        const Vec2 vTranslation = mA.getTranslation();
        const Vec2 vExpectedTrans{ TestType(5), TestType(10) };
        const auto vExpectedScale = ETL::Math::Vector2{ 2.0, 3.0 };

        // Note: Decomposition may not be exact due to combined transforms
        // Just check that values are reasonable
        REQUIRE(vScale.x() > 0);
        REQUIRE(vScale.y() > 0);
        REQUIRE(std::abs(rotation) < PI);
        REQUIRE(ETL::Math::isEqual(vScale, vExpectedScale));
        REQUIRE(ETL::Math::isEqual(std::abs(rotation), PI / 6.0));
        REQUIRE(ETL::Math::isEqual(vTranslation, vExpectedTrans));
    }
}
