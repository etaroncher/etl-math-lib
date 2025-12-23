///----------------------------------------------------------------------------
/// ETL - MathLib Unit Test
/// test_Matrix4x4.cpp
///----------------------------------------------------------------------------
#include <catch_amalgamated.hpp>
#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Matrix4x4.h>

#define MATRIX4x4_TYPES int, float, double
constexpr double PI = 3.14159265358979323846;

TEMPLATE_TEST_CASE("Matrix4x4 Construction & Access", "[Matrix4x4][core]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec4 = ETL::Math::Vector4<TestType>;

    SECTION("Default constructor")
    {
        Matrix m;
        // Default constructor behavior - uninitialized, no checks needed
    }

    SECTION("Diagonal matrix constructor")
    {
        const Matrix m{ TestType(5) };
        REQUIRE(m[0] == TestType(5));
        REQUIRE(m[1] == TestType(0));
        REQUIRE(m[2] == TestType(0));
        REQUIRE(m[3] == TestType(0));
        REQUIRE(m[4] == TestType(0));
        REQUIRE(m[5] == TestType(5));
        REQUIRE(m[6] == TestType(0));
        REQUIRE(m[7] == TestType(0));
        REQUIRE(m[8] == TestType(0));
        REQUIRE(m[9] == TestType(0));
        REQUIRE(m[10] == TestType(5));
        REQUIRE(m[11] == TestType(0));
        REQUIRE(m[12] == TestType(0));
        REQUIRE(m[13] == TestType(0));
        REQUIRE(m[14] == TestType(0));
        REQUIRE(m[15] == TestType(5));
    }

    SECTION("Variable diagonal constructor")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4) };
        REQUIRE(m[0] == TestType(1));
        REQUIRE(m[1] == TestType(0));
        REQUIRE(m[2] == TestType(0));
        REQUIRE(m[3] == TestType(0));
        REQUIRE(m[4] == TestType(0));
        REQUIRE(m[5] == TestType(2));
        REQUIRE(m[6] == TestType(0));
        REQUIRE(m[7] == TestType(0));
        REQUIRE(m[8] == TestType(0));
        REQUIRE(m[9] == TestType(0));
        REQUIRE(m[10] == TestType(3));
        REQUIRE(m[11] == TestType(0));
        REQUIRE(m[12] == TestType(0));
        REQUIRE(m[13] == TestType(0));
        REQUIRE(m[14] == TestType(0));
        REQUIRE(m[15] == TestType(4));
    }

    SECTION("Component constructor")
    {
        const Matrix m{ TestType(0),  TestType(1),  TestType(2),  TestType(3),
                        TestType(4),  TestType(5),  TestType(6),  TestType(7),
                        TestType(8),  TestType(9),  TestType(10), TestType(11),
                        TestType(12), TestType(13), TestType(14), TestType(15) };

        /// Column major storage, row-major constructor
        REQUIRE(m[0] == TestType(0));
        REQUIRE(m[1] == TestType(4));
        REQUIRE(m[2] == TestType(8));
        REQUIRE(m[3] == TestType(12));
        REQUIRE(m[4] == TestType(1));
        REQUIRE(m[5] == TestType(5));
        REQUIRE(m[6] == TestType(9));
        REQUIRE(m[7] == TestType(13));
        REQUIRE(m[8] == TestType(2));
        REQUIRE(m[9] == TestType(6));
        REQUIRE(m[10] == TestType(10));
        REQUIRE(m[11] == TestType(14));
        REQUIRE(m[12] == TestType(3));
        REQUIRE(m[13] == TestType(7));
        REQUIRE(m[14] == TestType(11));
        REQUIRE(m[15] == TestType(15));
    }

    SECTION("Accessors and Mutators")
    {
        /// () setter [] getter
        Matrix mA;

        mA(0, 0) = TestType(0);
        mA(1, 0) = TestType(1);
        mA(2, 0) = TestType(2);
        mA(3, 0) = TestType(3);
        mA(0, 1) = TestType(4);
        mA(1, 1) = TestType(5);
        mA(2, 1) = TestType(6);
        mA(3, 1) = TestType(7);
        mA(0, 2) = TestType(8);
        mA(1, 2) = TestType(9);
        mA(2, 2) = TestType(10);
        mA(3, 2) = TestType(11);
        mA(0, 3) = TestType(12);
        mA(1, 3) = TestType(13);
        mA(2, 3) = TestType(14);
        mA(3, 3) = TestType(15);

        REQUIRE(mA[0] == TestType(0));
        REQUIRE(mA[1] == TestType(1));
        REQUIRE(mA[2] == TestType(2));
        REQUIRE(mA[3] == TestType(3));
        REQUIRE(mA[4] == TestType(4));
        REQUIRE(mA[5] == TestType(5));
        REQUIRE(mA[6] == TestType(6));
        REQUIRE(mA[7] == TestType(7));
        REQUIRE(mA[8] == TestType(8));
        REQUIRE(mA[9] == TestType(9));
        REQUIRE(mA[10] == TestType(10));
        REQUIRE(mA[11] == TestType(11));
        REQUIRE(mA[12] == TestType(12));
        REQUIRE(mA[13] == TestType(13));
        REQUIRE(mA[14] == TestType(14));
        REQUIRE(mA[15] == TestType(15));

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
        mB[9] = TestType(9);
        mB[10] = TestType(10);
        mB[11] = TestType(11);
        mB[12] = TestType(12);
        mB[13] = TestType(13);
        mB[14] = TestType(14);
        mB[15] = TestType(15);

        REQUIRE(mB(0, 0) == TestType(0));
        REQUIRE(mB(1, 0) == TestType(1));
        REQUIRE(mB(2, 0) == TestType(2));
        REQUIRE(mB(3, 0) == TestType(3));
        REQUIRE(mB(0, 1) == TestType(4));
        REQUIRE(mB(1, 1) == TestType(5));
        REQUIRE(mB(2, 1) == TestType(6));
        REQUIRE(mB(3, 1) == TestType(7));
        REQUIRE(mB(0, 2) == TestType(8));
        REQUIRE(mB(1, 2) == TestType(9));
        REQUIRE(mB(2, 2) == TestType(10));
        REQUIRE(mB(3, 2) == TestType(11));
        REQUIRE(mB(0, 3) == TestType(12));
        REQUIRE(mB(1, 3) == TestType(13));
        REQUIRE(mB(2, 3) == TestType(14));
        REQUIRE(mB(3, 3) == TestType(15));

        /// GetRow & GetCol (return type and reference argument)
        const Vec4 A_row0 = mA.getRow(0);
        const Vec4 A_row1 = mA.getRow(1);
        const Vec4 A_row2 = mA.getRow(2);
        const Vec4 A_row3 = mA.getRow(3);
        const Vec4 A_col0 = mA.getCol(0);
        const Vec4 A_col1 = mA.getCol(1);
        const Vec4 A_col2 = mA.getCol(2);
        const Vec4 A_col3 = mA.getCol(3);

        Vec4 B_row0, B_row1, B_row2, B_row3, B_col0, B_col1, B_col2, B_col3;
        mB.getRowTo(B_row0, 0);
        mB.getRowTo(B_row1, 1);
        mB.getRowTo(B_row2, 2);
        mB.getRowTo(B_row3, 3);
        mB.getColTo(B_col0, 0);
        mB.getColTo(B_col1, 1);
        mB.getColTo(B_col2, 2);
        mB.getColTo(B_col3, 3);

        REQUIRE(A_row0 == B_row0);
        REQUIRE(A_row1 == B_row1);
        REQUIRE(A_row2 == B_row2);
        REQUIRE(A_row3 == B_row3);
        REQUIRE(A_col0 == B_col0);
        REQUIRE(A_col1 == B_col1);
        REQUIRE(A_col2 == B_col2);
        REQUIRE(A_col3 == B_col3);

        /// SetRow & SetCol
        mA.setRow(0, Vec4{ TestType(10) });
        mA.setRow(1, Vec4{ TestType(20) });
        mA.setRow(2, TestType(30), TestType(40), TestType(50), TestType(60));
        mA.setRow(3, TestType(300), TestType(400), TestType(500), TestType(600));

        REQUIRE(mA(0, 0) == TestType(10));
        REQUIRE(mA(0, 1) == TestType(10));
        REQUIRE(mA(0, 2) == TestType(10));
        REQUIRE(mA(0, 3) == TestType(10));
        REQUIRE(mA(1, 0) == TestType(20));
        REQUIRE(mA(1, 1) == TestType(20));
        REQUIRE(mA(1, 2) == TestType(20));
        REQUIRE(mA(1, 3) == TestType(20));
        REQUIRE(mA(2, 0) == TestType(30));
        REQUIRE(mA(2, 1) == TestType(40));
        REQUIRE(mA(2, 2) == TestType(50));
        REQUIRE(mA(2, 3) == TestType(60));
        REQUIRE(mA(3, 0) == TestType(300));
        REQUIRE(mA(3, 1) == TestType(400));
        REQUIRE(mA(3, 2) == TestType(500));
        REQUIRE(mA(3, 3) == TestType(600));

        mB.setCol(0, Vec4{ TestType(10) });
        mB.setCol(1, Vec4{ TestType(20) });
        mB.setCol(2, TestType(30), TestType(40), TestType(50), TestType(60));
        mB.setCol(3, TestType(300), TestType(400), TestType(500), TestType(600));

        REQUIRE(mB(0, 0) == TestType(10));
        REQUIRE(mB(1, 0) == TestType(10));
        REQUIRE(mB(2, 0) == TestType(10));
        REQUIRE(mB(3, 0) == TestType(10));
        REQUIRE(mB(0, 1) == TestType(20));
        REQUIRE(mB(1, 1) == TestType(20));
        REQUIRE(mB(2, 1) == TestType(20));
        REQUIRE(mB(3, 1) == TestType(20));
        REQUIRE(mB(0, 2) == TestType(30));
        REQUIRE(mB(1, 2) == TestType(40));
        REQUIRE(mB(2, 2) == TestType(50));
        REQUIRE(mB(3, 2) == TestType(60));
        REQUIRE(mB(0, 3) == TestType(300));
        REQUIRE(mB(1, 3) == TestType(400));
        REQUIRE(mB(2, 3) == TestType(500));
        REQUIRE(mB(3, 3) == TestType(600));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Static Factories", "[Matrix4x4][factories]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;

    SECTION("Zero matrix")
    {
        const Matrix m = Matrix::Zero();
        for (int i = 0; i < 16; ++i)
            REQUIRE(m[i] == TestType(0));
    }

    SECTION("Identity matrix")
    {
        const Matrix m = Matrix::Identity();
        REQUIRE(m(0, 0) == TestType(1));
        REQUIRE(m(1, 1) == TestType(1));
        REQUIRE(m(2, 2) == TestType(1));
        REQUIRE(m(3, 3) == TestType(1));
        REQUIRE(m(0, 1) == TestType(0));
        REQUIRE(m(0, 2) == TestType(0));
        REQUIRE(m(0, 3) == TestType(0));
        REQUIRE(m(1, 0) == TestType(0));
        REQUIRE(m(1, 2) == TestType(0));
        REQUIRE(m(1, 3) == TestType(0));
        REQUIRE(m(2, 0) == TestType(0));
        REQUIRE(m(2, 1) == TestType(0));
        REQUIRE(m(2, 3) == TestType(0));
        REQUIRE(m(3, 0) == TestType(0));
        REQUIRE(m(3, 1) == TestType(0));
        REQUIRE(m(3, 2) == TestType(0));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Arithmetic", "[Matrix4x4][math]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;

    SECTION("Addition - diagonal matrices")
    {
        const Matrix mA{ TestType(6) };
        const Matrix mB{ TestType(3) };
        const Matrix mResult = mA + mB;

        REQUIRE(mResult(0, 0) == TestType(9));
        REQUIRE(mResult(1, 1) == TestType(9));
        REQUIRE(mResult(2, 2) == TestType(9));
        REQUIRE(mResult(3, 3) == TestType(9));

        Matrix mResult2 = mA;
        mResult2 += mB;
        REQUIRE(mResult2 == mResult);
    }

    SECTION("Addition - general matrices")
    {
        const Matrix mA{ TestType(1), TestType(2), TestType(3), TestType(4),
                         TestType(5), TestType(6), TestType(7), TestType(8),
                         TestType(9), TestType(10), TestType(11), TestType(12),
                         TestType(13), TestType(14), TestType(15), TestType(16) };

        const Matrix mB{ TestType(16), TestType(15), TestType(14), TestType(13),
                         TestType(12), TestType(11), TestType(10), TestType(9),
                         TestType(8), TestType(7), TestType(6), TestType(5),
                         TestType(4), TestType(3), TestType(2), TestType(1) };

        const Matrix mResult = mA + mB;

        // All elements should be 17
        for (int i = 0; i < 16; ++i)
            REQUIRE(mResult[i] == TestType(17));
    }

    SECTION("Subtraction - diagonal matrices")
    {
        const Matrix mA{ TestType(6) };
        const Matrix mB{ TestType(3) };
        const Matrix mResult = mA - mB;

        REQUIRE(mResult(0, 0) == TestType(3));
        REQUIRE(mResult(1, 1) == TestType(3));
        REQUIRE(mResult(2, 2) == TestType(3));
        REQUIRE(mResult(3, 3) == TestType(3));

        Matrix mResult2 = mA;
        mResult2 -= mB;
        REQUIRE(mResult2 == mResult);
    }

    SECTION("Subtraction - general matrices")
    {
        const Matrix mA{ TestType(10), TestType(20), TestType(30), TestType(40),
                         TestType(50), TestType(60), TestType(70), TestType(80),
                         TestType(90), TestType(100), TestType(110), TestType(120),
                         TestType(130), TestType(140), TestType(150), TestType(160) };

        const Matrix mB{ TestType(1), TestType(2), TestType(3), TestType(4),
                         TestType(5), TestType(6), TestType(7), TestType(8),
                         TestType(9), TestType(10), TestType(11), TestType(12),
                         TestType(13), TestType(14), TestType(15), TestType(16) };

        const Matrix mResult = mA - mB;

        REQUIRE(mResult(0, 0) == TestType(9));
        REQUIRE(mResult(0, 1) == TestType(18));
        REQUIRE(mResult(1, 2) == TestType(63));
        REQUIRE(mResult(3, 3) == TestType(144));
    }

    SECTION("Scalar Multiplication")
    {
        const Matrix mA{ TestType(6) };
        const Matrix mResult = mA * TestType(2);

        REQUIRE(mResult(0, 0) == TestType(12));
        REQUIRE(mResult(1, 1) == TestType(12));
        REQUIRE(mResult(2, 2) == TestType(12));
        REQUIRE(mResult(3, 3) == TestType(12));

        Matrix mResult2 = mA;
        mResult2 *= TestType(2);
        REQUIRE(mResult2 == mResult);

        /// Test Commutative Property (s * m)
        const Matrix mResult3 = TestType(2) * mA;
        REQUIRE(mResult3 == mResult);
    }

    SECTION("Scalar Division")
    {
        const Matrix mA{ TestType(6) };
        const Matrix mResult = mA / TestType(2);

        REQUIRE(mResult(0, 0) == TestType(3));
        REQUIRE(mResult(1, 1) == TestType(3));
        REQUIRE(mResult(2, 2) == TestType(3));
        REQUIRE(mResult(3, 3) == TestType(3));

        Matrix mResult2 = mA;
        mResult2 /= TestType(2);
        REQUIRE(mResult2 == mResult);
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


TEMPLATE_TEST_CASE("Matrix4x4 isEqual with epsilon", "[Matrix4x4][utils]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;

    SECTION("Diagonal matrices")
    {
        const Matrix mA{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
        const Matrix mB{ 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001, 1.0001 };
        const Matrix mC{ 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1, 1.1 };

        REQUIRE(ETL::Math::isEqual(mA, mB, 0.001));
        REQUIRE_FALSE(ETL::Math::isEqual(mA, mC, 0.001));
        REQUIRE(ETL::Math::isEqual(mA, mC, 0.15));
    }

    SECTION("General matrices")
    {
        const Matrix mA{ 1.0,  2.0,  3.0,  4.0,
                         5.0,  6.0,  7.0,  8.0,
                         9.0,  10.0, 11.0, 12.0,
                         13.0, 14.0, 15.0, 16.0 };

        const Matrix mB{ 1.00001,  2.00001,  3.00001,  4.00001,
                         5.00001,  6.00001,  7.00001,  8.00001,
                         9.00001,  10.00001, 11.00001, 12.00001,
                         13.00001, 14.00001, 15.00001, 16.00001 };

        REQUIRE(ETL::Math::isEqual(mA, mB, 0.0001));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Matrix Multiplication", "[Matrix4x4][math]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;

    SECTION("Identity multiplication")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(5), TestType(6), TestType(7), TestType(8),
                        TestType(9), TestType(10), TestType(11), TestType(12),
                        TestType(13), TestType(14), TestType(15), TestType(16) };
        const Matrix mIdentity = Matrix::Identity();

        const Matrix mResult1 = m * mIdentity;
        const Matrix mResult2 = mIdentity * m;

        REQUIRE(mResult1 == m);
        REQUIRE(mResult2 == m);
    }

    SECTION("General matrix multiplication")
    {
        // 4x4 matrix multiplication
        const Matrix mA{ TestType(1), TestType(2), TestType(3), TestType(4),
                         TestType(5), TestType(6), TestType(7), TestType(8),
                         TestType(9), TestType(10), TestType(11), TestType(12),
                         TestType(13), TestType(14), TestType(15), TestType(16) };

        const Matrix mB{ TestType(16), TestType(15), TestType(14), TestType(13),
                         TestType(12), TestType(11), TestType(10), TestType(9),
                         TestType(8), TestType(7), TestType(6), TestType(5),
                         TestType(4), TestType(3), TestType(2), TestType(1) };

        const Matrix mResult = mA * mB;

        // Verify specific elements (calculated manually)
        REQUIRE(mResult(0, 0) == TestType(80));
        REQUIRE(mResult(0, 1) == TestType(70));
        REQUIRE(mResult(1, 0) == TestType(240));
        REQUIRE(mResult(2, 3) == TestType(274));
        REQUIRE(mResult(3, 3) == TestType(386));
    }

    SECTION("Diagonal matrix multiplication")
    {
        const Matrix mA{ TestType(2), TestType(0), TestType(0), TestType(0),
                         TestType(0), TestType(3), TestType(0), TestType(0),
                         TestType(0), TestType(0), TestType(4), TestType(0),
                         TestType(0), TestType(0), TestType(0), TestType(5) };

        const Matrix mB{ TestType(1), TestType(2), TestType(3), TestType(4),
                         TestType(5), TestType(6), TestType(7), TestType(8),
                         TestType(9), TestType(10), TestType(11), TestType(12),
                         TestType(13), TestType(14), TestType(15), TestType(16) };

        const Matrix mResult = mA * mB;

        // Each row scaled by diagonal element
        REQUIRE(mResult(0, 0) == TestType(2));
        REQUIRE(mResult(0, 1) == TestType(4));
        REQUIRE(mResult(1, 0) == TestType(15));
        REQUIRE(mResult(1, 1) == TestType(18));
        REQUIRE(mResult(2, 2) == TestType(44));
        REQUIRE(mResult(3, 3) == TestType(80));
    }

    SECTION("Compound assignment")
    {
        Matrix mA{ TestType(2) };
        const Matrix mB{ TestType(3) };
        const Matrix mExpected = mA * mB;

        mA *= mB;
        REQUIRE(mA == mExpected);
    }

    SECTION("Non-commutative property")
    {
        const Matrix mA{ TestType(1), TestType(2), TestType(3), TestType(4),
                         TestType(0), TestType(1), TestType(0), TestType(0),
                         TestType(0), TestType(0), TestType(1), TestType(0),
                         TestType(0), TestType(0), TestType(0), TestType(1) };

        const Matrix mB{ TestType(1), TestType(0), TestType(0), TestType(0),
                         TestType(5), TestType(1), TestType(0), TestType(0),
                         TestType(0), TestType(0), TestType(1), TestType(0),
                         TestType(0), TestType(0), TestType(0), TestType(1) };

        const Matrix mAB = mA * mB;
        const Matrix mBA = mB * mA;

        REQUIRE(mAB != mBA);
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Vector Multiplication", "[Matrix4x4][math]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec4 = ETL::Math::Vector4<TestType>;

    SECTION("Identity matrix vector multiplication")
    {
        const Matrix mIdentity = Matrix::Identity();
        const Vec4 v{ TestType(1), TestType(2), TestType(3), TestType(4) };

        const Vec4 vResult = mIdentity * v;

        REQUIRE(vResult == v);
    }

    SECTION("General matrix vector multiplication")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(5), TestType(6), TestType(7), TestType(8),
                        TestType(9), TestType(10), TestType(11), TestType(12),
                        TestType(13), TestType(14), TestType(15), TestType(16) };

        const Vec4 v{ TestType(1), TestType(2), TestType(3), TestType(4) };
        const Vec4 vExpected{ TestType(30), TestType(70), TestType(110), TestType(150) };
        const Vec4 vResult = m * v;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Diagonal matrix vector multiplication")
    {
        const Matrix m{ TestType(2), TestType(0), TestType(0), TestType(0),
                        TestType(0), TestType(3), TestType(0), TestType(0),
                        TestType(0), TestType(0), TestType(4), TestType(0),
                        TestType(0), TestType(0), TestType(0), TestType(5) };

        const Vec4 v{ TestType(1), TestType(2), TestType(3), TestType(4) };
        const Vec4 vExpected{ TestType(2), TestType(6), TestType(12), TestType(20) };

        const Vec4 vResult = m * v;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Translation matrix vector multiplication")
    {
        const Matrix m = Matrix::CreateTranslation(TestType(10), TestType(20), TestType(30));
        const Vec4 v{ TestType(1), TestType(2), TestType(3), TestType(1) };
        const Vec4 vExpected{ TestType(11), TestType(22), TestType(33), TestType(1) };

        const Vec4 vResult = m * v;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Determinant", "[Matrix4x4][math]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;

    SECTION("Identity determinant")
    {
        const Matrix m = Matrix::Identity();
        REQUIRE(m.determinant(true) == ETL::Math::EncodeValue<TestType>(1));

        TestType det;
        m.determinantTo(det, true);
        REQUIRE(det == ETL::Math::EncodeValue<TestType>(1));
    }

    SECTION("Zero determinant (singular matrix)")
    {
        // Rows are linearly dependent
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(2), TestType(4), TestType(6), TestType(8),
                        TestType(3), TestType(6), TestType(9), TestType(12),
                        TestType(4), TestType(8), TestType(12), TestType(16) };

        REQUIRE(m.determinant(true) == ETL::Math::EncodeValue<TestType>(0));

        TestType det;
        m.determinantTo(det, true);
        REQUIRE(det == ETL::Math::EncodeValue<TestType>(0));
    }

    SECTION("Non-zero determinant")
    {
        const Matrix m{ TestType(1), TestType(0), TestType(2), TestType(-1),
                        TestType(3), TestType(0), TestType(0), TestType(5),
                        TestType(2), TestType(1), TestType(4), TestType(-3),
                        TestType(1), TestType(0), TestType(5), TestType(0) };

        // Determinant calculated manually: 30
        REQUIRE(m.determinant(true) == ETL::Math::EncodeValue<TestType>(30));

        TestType det;
        m.determinantTo(det, true);
        REQUIRE(det == ETL::Math::EncodeValue<TestType>(30));
    }

    SECTION("Diagonal matrix determinant")
    {
        const Matrix m{ TestType(2), TestType(0), TestType(0), TestType(0),
                        TestType(0), TestType(3), TestType(0), TestType(0),
                        TestType(0), TestType(0), TestType(4), TestType(0),
                        TestType(0), TestType(0), TestType(0), TestType(5) };

        // Product of diagonal: 2*3*4*5 = 120
        REQUIRE(m.determinant(true) == ETL::Math::EncodeValue<TestType>(120));

        TestType det;
        m.determinantTo(det, true);
        REQUIRE(det == ETL::Math::EncodeValue<TestType>(120));
    }

    SECTION("Negative determinant")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(0), TestType(1), TestType(2), TestType(3),
                        TestType(0), TestType(0), TestType(1), TestType(2),
                        TestType(0), TestType(0), TestType(0), TestType(-1)
        };

        const TestType det = m.determinant(true);
        REQUIRE(det < TestType(0));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Transpose", "[Matrix4x4][math]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;

    SECTION("Transpose - output arg")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(5), TestType(6), TestType(7), TestType(8),
                        TestType(9), TestType(10), TestType(11), TestType(12),
                        TestType(13), TestType(14), TestType(15), TestType(16) };

        const Matrix mExpected{ TestType(1), TestType(5), TestType(9), TestType(13),
                                TestType(2), TestType(6), TestType(10), TestType(14),
                                TestType(3), TestType(7), TestType(11), TestType(15),
                                TestType(4), TestType(8), TestType(12), TestType(16) };

        Matrix mResult;
        m.transposeTo(mResult);

        REQUIRE(mResult == mExpected);
    }

    SECTION("Transpose - return value")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(5), TestType(6), TestType(7), TestType(8),
                        TestType(9), TestType(10), TestType(11), TestType(12),
                        TestType(13), TestType(14), TestType(15), TestType(16) };

        const Matrix mExpected{ TestType(1), TestType(5), TestType(9), TestType(13),
                                TestType(2), TestType(6), TestType(10), TestType(14),
                                TestType(3), TestType(7), TestType(11), TestType(15),
                                TestType(4), TestType(8), TestType(12), TestType(16) };

        const Matrix mResult = m.transpose();

        REQUIRE(mResult == mExpected);
    }

    SECTION("MakeTranspose - in-place")
    {
        Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                  TestType(5), TestType(6), TestType(7), TestType(8),
                  TestType(9), TestType(10), TestType(11), TestType(12),
                  TestType(13), TestType(14), TestType(15), TestType(16) };

        const Matrix mExpected{ TestType(1), TestType(5), TestType(9), TestType(13),
                                TestType(2), TestType(6), TestType(10), TestType(14),
                                TestType(3), TestType(7), TestType(11), TestType(15),
                                TestType(4), TestType(8), TestType(12), TestType(16) };

        m.makeTranspose();

        REQUIRE(m == mExpected);
    }

    SECTION("Double transpose returns original")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(5), TestType(6), TestType(7), TestType(8),
                        TestType(9), TestType(10), TestType(11), TestType(12),
                        TestType(13), TestType(14), TestType(15), TestType(16) };

        const Matrix mResult = m.transpose().transpose();

        REQUIRE(mResult == m);
    }

    SECTION("Symmetric matrix transpose")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(2), TestType(5), TestType(6), TestType(7),
                        TestType(3), TestType(6), TestType(8), TestType(9),
                        TestType(4), TestType(7), TestType(9), TestType(10) };

        const Matrix mResult = m.transpose();

        REQUIRE(mResult == m);
    }

    SECTION("Identity transpose")
    {
        const Matrix m = Matrix::Identity();
        const Matrix mResult = m.transpose();

        REQUIRE(mResult == m);
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Inverse", "[Matrix4x4][math]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;

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
        const Matrix original{ TestType(1), TestType(0), TestType(2), TestType(-1),
                               TestType(3), TestType(0), TestType(0), TestType(5),
                               TestType(2), TestType(1), TestType(4), TestType(-3),
                               TestType(1), TestType(0), TestType(5), TestType(0) };

        Matrix m;
        original.inverseTo(m);
        const Matrix mResult = m * original;
        const Matrix mExpected = Matrix::Identity();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("Inverse property: M * M^-1 = I")
    {
        const Matrix m{ TestType(1), TestType(0), TestType(2), TestType(-1),
                        TestType(3), TestType(0), TestType(0), TestType(5),
                        TestType(2), TestType(1), TestType(4), TestType(-3),
                        TestType(1), TestType(0), TestType(5), TestType(0) };

        const Matrix mInverse = m.inverse();
        const Matrix mResult = m * mInverse;
        const Matrix mExpected = Matrix::Identity();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("Inverse property: M^-1 * M = I")
    {
        const Matrix m{ TestType(2), TestType(0), TestType(0), TestType(1),
                        TestType(0), TestType(3), TestType(0), TestType(2),
                        TestType(0), TestType(0), TestType(4), TestType(3),
                        TestType(0), TestType(0), TestType(0), TestType(1) };

        const Matrix mInverse = m.inverse();
        const Matrix mResult = mInverse * m;
        const Matrix mExpected = Matrix::Identity();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("MakeInverse - in-place")
    {
        const Matrix original{ TestType(1), TestType(0), TestType(2), TestType(-1),
                               TestType(3), TestType(0), TestType(0), TestType(5),
                               TestType(2), TestType(1), TestType(4), TestType(-3),
                               TestType(1), TestType(0), TestType(5), TestType(0) };

        Matrix m = original;
        m.makeInverse();
        const Matrix mResult = m * original;
        const Matrix mExpected = Matrix::Identity();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected));
    }

    SECTION("Double inverse returns original")
    {
        const Matrix m{ TestType(1), TestType(0), TestType(2), TestType(-1),
                        TestType(3), TestType(0), TestType(0), TestType(5),
                        TestType(2), TestType(1), TestType(4), TestType(-3),
                        TestType(1), TestType(0), TestType(5), TestType(0) };

        const Matrix mResult = m.inverse().inverse();

        REQUIRE(ETL::Math::isEqual(mResult, m, 0.0015));
    }

    SECTION("Diagonal matrix inverse")
    {
        const Matrix m{ TestType(2), TestType(0), TestType(0), TestType(0),
                        TestType(0), TestType(4), TestType(0), TestType(0),
                        TestType(0), TestType(0), TestType(5), TestType(0),
                        TestType(0), TestType(0), TestType(0), TestType(10) };

        const Matrix mInverse = m.inverse();
        const Matrix mResult = m * mInverse;
        const Matrix mExpected = Matrix::Identity();

        REQUIRE(ETL::Math::isEqual(mResult, mExpected, 0.0002));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 3D Transformations Factories", "[Matrix4x4][transform]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec4 = ETL::Math::Vector4<TestType>;
    constexpr double PI_HALF = PI / 2.0;

    SECTION("Scale static factory")
    {
        const Matrix mScale = Matrix::CreateScale(2.0, 3.0, 4.0);
        const Vec4 vPoint{ TestType(1), TestType(2), TestType(3), TestType(1) };
        const Vec4 vExpected{ TestType(2), TestType(6), TestType(12), TestType(1) };
        const Vec4 vResult = mScale * vPoint;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Rotation static factory - X axis")
    {
        const Matrix mRotX = Matrix::CreateRotation(PI_HALF, 0.0, 0.0); // 90° around X
        const Vec4 vPoint{ TestType(0), TestType(1), TestType(0), TestType(1) };
        const Vec4 vExpected{ TestType(0), TestType(0), TestType(1), TestType(1) };
        const Vec4 vResult = mRotX * vPoint;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Rotation static factory - Y axis")
    {
        const Matrix mRotY = Matrix::CreateRotation(0.0, PI_HALF, 0.0); // 90° around Y
        const Vec4 vPoint{ TestType(1), TestType(0), TestType(0), TestType(1) };
        const Vec4 vExpected{ TestType(0), TestType(0), TestType(-1), TestType(1) };
        const Vec4 vResult = mRotY * vPoint;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Rotation static factory - Z axis")
    {
        const Matrix mRotZ = Matrix::CreateRotation(0.0, 0.0, PI_HALF); // 90° around Z
        const Vec4 vPoint{ TestType(1), TestType(0), TestType(0), TestType(1) };
        const Vec4 vExpected{ TestType(0), TestType(1), TestType(0), TestType(1) };
        const Vec4 vResult = mRotZ * vPoint;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Translation static factory")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20), TestType(30));
        const Vec4 vPoint{ TestType(1), TestType(2), TestType(3), TestType(1) };
        const Vec4 vExpected{ TestType(11), TestType(22), TestType(33), TestType(1) };
        const Vec4 vResult = mTrans * vPoint;

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 3D Transform Point & Direction", "[Matrix4x4][transform]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec3 = ETL::Math::Vector3<TestType>;
    constexpr double PI_HALF = PI / 2.0;

    SECTION("TransformPoint - output arg")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20), TestType(30));
        const Vec3 vPoint{ TestType(5), TestType(3), TestType(7) };
        const Vec3 vExpected{ TestType(15), TestType(23), TestType(37) };

        Vec3 vResult;
        mTrans.transformPointTo(vResult, vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformPoint - return value")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20), TestType(30));
        const Vec3 vPoint{ TestType(5), TestType(3), TestType(7) };
        const Vec3 vExpected{ TestType(15), TestType(23), TestType(37) };

        const Vec3 vResult = mTrans.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformPoint - in-place")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20), TestType(30));
        Vec3 vPoint{ TestType(5), TestType(3), TestType(7) };
        const Vec3 vExpected{ TestType(15), TestType(23), TestType(37) };

        mTrans.transformPointInPlace(vPoint);

        REQUIRE(ETL::Math::isEqual(vPoint, vExpected));
    }

    SECTION("TransformDirection - output arg")
    {
        const Matrix mRotZ = Matrix::CreateRotation(0.0, 0.0, PI_HALF); // 90° around Z
        const Vec3 vDirection{ TestType(1), TestType(0), TestType(0) };
        const Vec3 vExpected{ TestType(0), TestType(1), TestType(0) };

        Vec3 vResult;
        mRotZ.transformDirectionTo(vResult, vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformDirection - return value")
    {
        const Matrix mRotZ = Matrix::CreateRotation(0.0, 0.0, PI_HALF);
        const Vec3 vDirection{ TestType(1), TestType(0), TestType(0) };
        const Vec3 vExpected{ TestType(0), TestType(1), TestType(0) };

        const Vec3 vResult = mRotZ.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("TransformDirection - in-place")
    {
        const Matrix mRotZ = Matrix::CreateRotation(0.0, 0.0, PI_HALF);
        Vec3 vDirection{ TestType(1), TestType(0), TestType(0) };
        const Vec3 vExpected{ TestType(0), TestType(1), TestType(0) };

        mRotZ.transformDirectionInPlace(vDirection);

        REQUIRE(ETL::Math::isEqual(vDirection, vExpected));
    }

    SECTION("TransformDirection ignores translation")
    {
        const Matrix mTrans = Matrix::CreateTranslation(TestType(10), TestType(20), TestType(30));
        const Vec3 vDirection{ TestType(1), TestType(0), TestType(0) };

        const Vec3 vResult = mTrans.transformDirection(vDirection);

        REQUIRE(ETL::Math::isEqual(vResult, vDirection));
    }

    SECTION("TransformPoint with scale")
    {
        const Matrix mScale = Matrix::CreateScale(2.0, 3.0, 4.0);
        const Vec3 vPoint{ TestType(1), TestType(2), TestType(3) };
        const Vec3 vExpected{ TestType(2), TestType(6), TestType(12) };

        const Vec3 vResult = mScale.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 3D Transform Methods", "[Matrix4x4][transform]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec3 = ETL::Math::Vector3<TestType>;
    constexpr double PI_HALF = PI / 2.0;

    SECTION("Scale method (post-multiply)")
    {
        Matrix m = Matrix::Identity();
        m.scale(2.0, 3.0, 4.0);

        const Vec3 vPoint{ TestType(1), TestType(2), TestType(3) };
        const Vec3 vExpected{ TestType(2), TestType(6), TestType(12) };
        const Vec3 vResult = m.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Rotate method (post-multiply)")
    {
        Matrix m = Matrix::Identity();
        m.rotate(0.0, 0.0, PI_HALF); /// 90° around Z

        const Vec3 vPoint{ TestType(1), TestType(0), TestType(0) };
        const Vec3 vExpected{ TestType(0), TestType(1), TestType(0) };
        const Vec3 vResult = m.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Translate method (post-multiply)")
    {
        Matrix m = Matrix::Identity();
        m.translate(TestType(10), TestType(20), TestType(30));

        const Vec3 vPoint{ TestType(1), TestType(2), TestType(3) };
        const Vec3 vExpected{ TestType(11), TestType(22), TestType(33) };
        const Vec3 vResult = m.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Combined transformations (TRS order)")
    {
        const ETL::Math::Vector3<double> scale{ 2.0, 2.0, 2.0 };
        const ETL::Math::Vector3<double> rotation{ 0.0, 0.0, PI_HALF };
        const ETL::Math::Vector3<TestType> translation{ TestType(10), TestType(0), TestType(0) };

        Matrix mA = Matrix::Identity();
        mA.translate(translation);
        mA.rotate(rotation);
        mA.scale(scale);

        const Vec3 vPoint{ TestType(1), TestType(0), TestType(0) };
        /// Point (1,0,0) -> scale<2> -> (2,0,0) -> rotate<90°Z> -> (0,2,0) -> translate<10,0,0> -> (10,2,0)
        const Vec3 vExpected{ TestType(10), TestType(2), TestType(0) };
        const Vec3 vResult = mA.transformPoint(vPoint);

        REQUIRE(ETL::Math::isEqual(vResult, vExpected));
    }

    SECTION("Transform setters - overwrite current values")
    {
        const ETL::Math::Vector3<double> newScale{ 3.0, 3.0, 3.0 };
        const ETL::Math::Vector3<double> newRotation{ PI_HALF, 0.0, 0.0 };
        const ETL::Math::Vector3<TestType> newTranslation{ TestType(5), TestType(15), TestType(25) };

        Matrix mA = Matrix::Identity();
        mA.translate(TestType(10), TestType(0), TestType(0));
        mA.rotate(0.0, 0.0, PI_HALF);
        mA.scale(2.0, 2.0, 2.0);

        /// Overwrite with new values
        mA.setTranslation(newTranslation);
        mA.setRotation(newRotation);
        mA.setScale(newScale);

        const Matrix mExpected = Matrix::Identity()
            .translate(newTranslation)
            .rotate(newRotation)
            .scale(newScale);

        REQUIRE(ETL::Math::isEqual(mA, mExpected));
    }

    SECTION("Chained transformations act local, order independent")
    {
        const ETL::Math::Vector3<double> scale{ 2.0, 3.0, 4.0 };
        const ETL::Math::Vector3<double> rotation{ 0.0, 0.0, PI / 4.0 };
        const ETL::Math::Vector3<TestType> translation{ TestType(5), TestType(10), TestType(15) };

        const Matrix mA = Matrix::Identity()
            .translate(translation)
            .rotate(rotation)
            .scale(scale);

        const Matrix mB = Matrix::Identity()
            .scale(scale)
            .rotate(rotation)
            .translate(translation);

        REQUIRE(ETL::Math::isEqual(mA, mB));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Transform Decomposition", "[Matrix4x4][transform]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec3 = ETL::Math::Vector3<TestType>;

    SECTION("GetScale from scale matrix")
    {
        const ETL::Math::Vector3<double> vExpected{ 2.0, 3.0, 4.0 };
        const Matrix mScale = Matrix::CreateScale(vExpected.x(), vExpected.y(), vExpected.z());

        const ETL::Math::Vector3<double> vScale1 = mScale.getScale();
        REQUIRE(ETL::Math::isEqual(vScale1, vExpected, 0.001));

        ETL::Math::Vector3<double> vScale2;
        mScale.getScaleTo(vScale2);
        REQUIRE(ETL::Math::isEqual(vScale2, vExpected, 0.001));
    }

    SECTION("GetRotation from rotation matrix - X axis")
    {
        const ETL::Math::Vector3<double> angles{ PI / 4.0, 0.0, 0.0 };
        const Matrix mRot = Matrix::CreateRotation(angles.x(), angles.y(), angles.z());

        const ETL::Math::Vector3<double> extractedAngles1 = mRot.getRotation();
        REQUIRE(ETL::Math::isEqual(extractedAngles1, angles, 0.001));

        ETL::Math::Vector3<double> extractedAngles2;
        mRot.getRotationTo(extractedAngles2);
        REQUIRE(ETL::Math::isEqual(extractedAngles2, angles, 0.001));
    }

    SECTION("GetRotation from rotation matrix - Y axis")
    {
        const ETL::Math::Vector3<double> angles{ 0.0, PI / 6.0, 0.0 };
        const Matrix mRot = Matrix::CreateRotation(angles.x(), angles.y(), angles.z());

        const ETL::Math::Vector3<double> extractedAngles = mRot.getRotation();
        REQUIRE(ETL::Math::isEqual(extractedAngles, angles, 0.001));
    }

    SECTION("GetRotation from rotation matrix - Z axis")
    {
        const ETL::Math::Vector3<double> angles{ 0.0, 0.0, PI / 3.0 };
        const Matrix mRot = Matrix::CreateRotation(angles.x(), angles.y(), angles.z());

        const ETL::Math::Vector3<double> extractedAngles = mRot.getRotation();
        REQUIRE(ETL::Math::isEqual(extractedAngles, angles, 0.001));
    }

    SECTION("GetTranslation from translation matrix")
    {
        const Vec3 vExpected{ TestType(10), TestType(20), TestType(30) };
        const Matrix mTrans = Matrix::CreateTranslation(vExpected.x(), vExpected.y(), vExpected.z());

        const Vec3 vTranslation1 = mTrans.getTranslation();
        REQUIRE(ETL::Math::isEqual(vTranslation1, vExpected));

        Vec3 vTranslation2;
        mTrans.getTranslationTo(vTranslation2);
        REQUIRE(ETL::Math::isEqual(vTranslation2, vExpected));
    }

    SECTION("Decompose combined transformation")
    {
        const ETL::Math::Vector3<double> expectedScale{ 2.0, 3.0, 4.0 };
        const ETL::Math::Vector3<double> expectedRotation{ PI / 6.0, PI / 4.0, PI / 3.0 };
        const Vec3 expectedTranslation{ TestType(5), TestType(10), TestType(15) };

        Matrix m = Matrix::Identity();
        m.translate(expectedTranslation);
        m.rotate(expectedRotation);
        m.scale(expectedScale);

        const auto vScale = m.getScale();
        const auto vRotation = m.getRotation();
        const Vec3 vTranslation = m.getTranslation();

        REQUIRE(ETL::Math::isEqual(vScale, expectedScale, 0.001));
        REQUIRE(ETL::Math::isEqual(vRotation, expectedRotation, 0.001));
        REQUIRE(ETL::Math::isEqual(vTranslation, expectedTranslation));
    }

    SECTION("Decompose with negative scale")
    {
        Matrix m = Matrix::Identity();
        m.scale(-2.0, 3.0, 4.0); // Negative X scale (reflection)

        const auto vScale = m.getScale();

        // Should detect negative scale
        REQUIRE(vScale.z() < 0.0);
        REQUIRE(ETL::Math::isEqual(vScale.x(), 2.0, 0.001));
        REQUIRE(ETL::Math::isEqual(vScale.y(), 3.0, 0.001));
        REQUIRE(ETL::Math::isEqual(std::abs(vScale.z()), 4.0, 0.001));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Transform Edge Cases", "[Matrix4x4][edge]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec3 = ETL::Math::Vector3<TestType>;
    constexpr double PI_HALF = PI / 2.0;

    SECTION("Gimbal lock - positive")
    {
        // Rotation with Y = 90° (gimbal lock)
        const ETL::Math::Vector3<double> angles{ 0.0, PI_HALF, 0.0 };
        const Matrix mRot = Matrix::CreateRotation(angles.x(), angles.y(), angles.z());

        const ETL::Math::Vector3<double> extractedAngles = mRot.getRotation();

        // Y should be PI/2, Z should be 0 (by convention)
        REQUIRE(ETL::Math::isEqual(extractedAngles.y(), PI_HALF, 0.001));
        REQUIRE(ETL::Math::isEqual(extractedAngles.z(), 0.0, 0.001));
    }

    SECTION("Gimbal lock - negative")
    {
        // Rotation with Y = -90° (gimbal lock)
        const ETL::Math::Vector3<double> angles{ 0.0, -PI_HALF, 0.0 };
        const Matrix mRot = Matrix::CreateRotation(angles.x(), angles.y(), angles.z());

        const ETL::Math::Vector3<double> extractedAngles = mRot.getRotation();

        // Y should be -PI/2, Z should be 0 (by convention)
        REQUIRE(ETL::Math::isEqual(extractedAngles.y(), -PI_HALF, 0.001));
        REQUIRE(ETL::Math::isEqual(extractedAngles.z(), 0.0, 0.001));
    }

    SECTION("Zero scale handling")
    {
        Matrix m = Matrix::Identity();
        m.scale(0.0, 1.0, 1.0);

        const auto vScale = m.getScale();
        const auto vRotation = m.getRotation();

        // Should handle zero scale gracefully
        REQUIRE(ETL::Math::isEqual(vScale.x(), 0.0, 0.001));
        REQUIRE(ETL::Math::isEqual(vRotation.x(), 0.0, 0.001));
        REQUIRE(ETL::Math::isEqual(vRotation.y(), 0.0, 0.001));
        REQUIRE(ETL::Math::isEqual(vRotation.z(), 0.0, 0.001));
    }

    SECTION("Very small scale")
    {
        Matrix m = Matrix::Identity();
        m.scale(0.0002, 0.0002, 0.0003);

        const auto vScale = m.getScale();

        REQUIRE(ETL::Math::isEqual(vScale.x(), 0.0002, 0.0001));
        REQUIRE(ETL::Math::isEqual(vScale.y(), 0.0002, 0.0001));
        REQUIRE(ETL::Math::isEqual(vScale.z(), 0.0003, 0.0001));
    }

    SECTION("Large scale")
    {
        Matrix m = Matrix::Identity();
        m.scale(1000.0, 2000.0, 3000.0);

        const auto vScale = m.getScale();

        REQUIRE(ETL::Math::isEqual(vScale.x(), 1000.0, 0.1));
        REQUIRE(ETL::Math::isEqual(vScale.y(), 2000.0, 0.1));
        REQUIRE(ETL::Math::isEqual(vScale.z(), 3000.0, 0.1));
    }

    SECTION("Full rotation (2π)")
    {
        const ETL::Math::Vector3<double> angles{ 2.0 * PI, 0.0, 0.0 };
        const Matrix mRot = Matrix::CreateRotation(angles.x(), angles.y(), angles.z());

        const Vec3 vPoint{ TestType(1), TestType(2), TestType(3) };
        const Vec3 vResult = mRot.transformPoint(vPoint);

        // Should be back to original (within floating point tolerance)
        REQUIRE(ETL::Math::isEqual(vResult, vPoint, 0.001));
    }

    SECTION("Negative scale preservation through set operations")
    {
        Matrix m = Matrix::Identity();
        m.scale(-2.0, 3.0, 4.0);

        const auto originalScale = m.getScale();

        // Set new rotation, scale should be preserved
        m.setRotation(0.0, 0.0, PI / 4.0);

        const auto newScale = m.getScale();
        REQUIRE(ETL::Math::isEqual(originalScale, newScale, 0.001));
    }
}


TEMPLATE_TEST_CASE("Matrix4x4 Free Functions", "[Matrix4x4][free]", MATRIX4x4_TYPES)
{
    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec3 = ETL::Math::Vector3<TestType>;
    using Vec4 = ETL::Math::Vector4<TestType>;

    using Matrix = ETL::Math::Matrix4x4<TestType>;
    using Vec3 = ETL::Math::Vector3<TestType>;
    using Vec4 = ETL::Math::Vector4<TestType>;

    SECTION("Multiply - Matrix * Matrix")
    {
        const Matrix mA{ TestType(2) };
        const Matrix mB{ TestType(3) };

        Matrix mResult;
        ETL::Math::Multiply(mResult, mA, mB);

        const Matrix mExpected = mA * mB;
        REQUIRE(mResult == mExpected);
    }

    SECTION("Multiply - Matrix * Vector")
    {
        const Matrix m = Matrix::Identity();
        const Vec4 v{ TestType(1), TestType(2), TestType(3), TestType(4) };

        Vec4 vResult;
        ETL::Math::Multiply(vResult, m, v);

        REQUIRE(vResult == v);
    }

    SECTION("GetCol and SetCol")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(5), TestType(6), TestType(7), TestType(8),
                        TestType(9), TestType(10), TestType(11), TestType(12),
                        TestType(13), TestType(14), TestType(15), TestType(16) };

        Vec4 col;
        ETL::Math::GetCol(col, m, 1);

        REQUIRE(col[0] == TestType(2));
        REQUIRE(col[1] == TestType(6));
        REQUIRE(col[2] == TestType(10));
        REQUIRE(col[3] == TestType(14));

        Matrix mResult;
        const Vec4 newCol{ TestType(100), TestType(200), TestType(300), TestType(400) };
        ETL::Math::SetCol(mResult, m, 1, newCol);

        REQUIRE(mResult(0, 1) == TestType(100));
        REQUIRE(mResult(1, 1) == TestType(200));
        REQUIRE(mResult(2, 1) == TestType(300));
        REQUIRE(mResult(3, 1) == TestType(400));
    }

    SECTION("GetRow and SetRow")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(5), TestType(6), TestType(7), TestType(8),
                        TestType(9), TestType(10), TestType(11), TestType(12),
                        TestType(13), TestType(14), TestType(15), TestType(16) };

        Vec4 row;
        ETL::Math::GetRow(row, m, 1);

        REQUIRE(row[0] == TestType(5));
        REQUIRE(row[1] == TestType(6));
        REQUIRE(row[2] == TestType(7));
        REQUIRE(row[3] == TestType(8));

        Matrix mResult;
        const Vec4 newRow{ TestType(100), TestType(200), TestType(300), TestType(400) };
        ETL::Math::SetRow(mResult, m, 1, newRow);

        REQUIRE(mResult(1, 0) == TestType(100));
        REQUIRE(mResult(1, 1) == TestType(200));
        REQUIRE(mResult(1, 2) == TestType(300));
        REQUIRE(mResult(1, 3) == TestType(400));
    }

    SECTION("TransformPoint and TransformDirection")
    {
        const Matrix m = Matrix::CreateTranslation(TestType(10), TestType(20), TestType(30));
        const Vec3 vPoint{ TestType(1), TestType(2), TestType(3) };
        const Vec3 vDirection{ TestType(1), TestType(0), TestType(0) };

        Vec3 vPointResult, vDirResult;
        ETL::Math::TransformPoint(vPointResult, m, vPoint);
        ETL::Math::TransformDirection(vDirResult, m, vDirection);

        REQUIRE(ETL::Math::isEqual(vPointResult, Vec3{ TestType(11), TestType(22), TestType(33) }));
        REQUIRE(ETL::Math::isEqual(vDirResult, vDirection));
    }

    SECTION("Determinant and Inverse")
    {
        const Matrix m{ TestType(1), TestType(0), TestType(2), TestType(-1),
                        TestType(3), TestType(0), TestType(0), TestType(5),
                        TestType(2), TestType(1), TestType(4), TestType(-3),
                        TestType(1), TestType(0), TestType(5), TestType(0) };

        TestType det;
        ETL::Math::Determinant(det, m);
        REQUIRE(ETL::Math::isEqual(det, TestType(30)));

        Matrix mInverse;
        ETL::Math::Inverse(mInverse, m);

        const Matrix mResult = m * mInverse;
        const Matrix mIdentity = Matrix::Identity();
        REQUIRE(ETL::Math::isEqual(mResult, mIdentity));
    }

    SECTION("Transpose")
    {
        const Matrix m{ TestType(1), TestType(2), TestType(3), TestType(4),
                        TestType(5), TestType(6), TestType(7), TestType(8),
                        TestType(9), TestType(10), TestType(11), TestType(12),
                        TestType(13), TestType(14), TestType(15), TestType(16) };

        Matrix mResult;
        ETL::Math::Transpose(mResult, m);

        REQUIRE(mResult(0, 1) == m(1, 0));
        REQUIRE(mResult(1, 0) == m(0, 1));
        REQUIRE(mResult(2, 3) == m(3, 2));
        REQUIRE(mResult(3, 2) == m(2, 3));
    }

    SECTION("Transform decomposition free functions")
    {
        Matrix m = Matrix::Identity();
        m.translate(TestType(5), TestType(10), TestType(15));
        m.rotate(0.0, 0.0, PI / 4.0);
        m.scale(2.0, 3.0, 4.0);

        Vec3 translation;
        ETL::Math::Vector3<double> rotation, scale;

        ETL::Math::GetTranslation(translation, m);
        ETL::Math::GetRotation(rotation, m);
        ETL::Math::GetScaling(scale, m);

        REQUIRE(ETL::Math::isEqual(translation, Vec3{ TestType(5), TestType(10), TestType(15) }));
        REQUIRE(ETL::Math::isEqual(scale, ETL::Math::Vector3<double>{ 2.0, 3.0, 4.0 }, 0.001));
    }
}