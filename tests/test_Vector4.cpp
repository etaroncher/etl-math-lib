///----------------------------------------------------------------------------
/// ETL - MathLib Unit Test
/// test_Vector4.cpp
///----------------------------------------------------------------------------
#include <catch_amalgamated.hpp>
#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Vector4.h>

#define VECTOR4_TYPES int, float, double

TEMPLATE_TEST_CASE("Vector4 Construction & Access", "[Vector4][core]", VECTOR4_TYPES)
{
    using Vector = ETL::Math::Vector4<TestType>;

    SECTION("Scalar constructor")
    {
        Vector v{ TestType(5) };
        REQUIRE(v.x() == TestType(5));
        REQUIRE(v.y() == TestType(5));
        REQUIRE(v.z() == TestType(5));
        REQUIRE(v.w() == TestType(5));
    }

    SECTION("Component constructor")
    {
        Vector v{ TestType(3), TestType(4), TestType(5), TestType(6) };
        REQUIRE(v.x() == TestType(3));
        REQUIRE(v.y() == TestType(4));
        REQUIRE(v.z() == TestType(5));
        REQUIRE(v.w() == TestType(6));
    }

    SECTION("From-Vector3 constructor")
    {
        ETL::Math::Vector3<TestType> vec2{ TestType(3), TestType(4), TestType(5) };
        Vector v{ vec2, TestType(6) };
        REQUIRE(v.x() == TestType(3));
        REQUIRE(v.y() == TestType(4));
        REQUIRE(v.z() == TestType(5));
        REQUIRE(v.w() == TestType(6));
    }

    SECTION("Accessors and Mutators")
    {
        Vector v;
        v.x(TestType(10));
        v.y(TestType(20));
        v.z(TestType(30));
        v.w(TestType(40));

        REQUIRE(v.x() == TestType(10));
        REQUIRE(v.y() == TestType(20));
        REQUIRE(v.z() == TestType(30));
        REQUIRE(v.w() == TestType(40));

        REQUIRE(v[0] == TestType(10));
        REQUIRE(v[1] == TestType(20));
        REQUIRE(v[2] == TestType(30));
        REQUIRE(v[3] == TestType(40));

        v[0] = TestType(5);
        REQUIRE(v.x() == TestType(5));
    }

    SECTION("Equality and inequality operators")
    {
        Vector vA{ TestType(3), TestType(4), TestType(5), TestType(6) };
        Vector vB{ TestType(3), TestType(4), TestType(5), TestType(6) };
        Vector vC{ TestType(4), TestType(3), TestType(5), TestType(6) };
        REQUIRE(vA == vB);
        REQUIRE(vA != vC);
        REQUIRE_FALSE(vA == vC);
    }
}


TEMPLATE_TEST_CASE("Vector4 Raw Access", "[Vector4][core]", float, double)
{
    using Vector = ETL::Math::Vector4<TestType>;

    SECTION("Raw access")
    {
        Vector v{ TestType(10), TestType(20), TestType(30), TestType(40) };

        REQUIRE(v.x() == TestType(10));
        REQUIRE(v.y() == TestType(20));
        REQUIRE(v.z() == TestType(30));
        REQUIRE(v.w() == TestType(40));
        REQUIRE(v.getRawValue(0) == TestType(10));
        REQUIRE(v.getRawValue(1) == TestType(20));
        REQUIRE(v.getRawValue(2) == TestType(30));
        REQUIRE(v.getRawValue(3) == TestType(40));

        v.setRawValue(0, TestType(100));
        v.setRawValue(1, TestType(200));
        v.setRawValue(2, TestType(300));
        v.setRawValue(3, TestType(400));

        REQUIRE(v.getRawValue(0) == TestType(100));
        REQUIRE(v.getRawValue(1) == TestType(200));
        REQUIRE(v.getRawValue(2) == TestType(300));
        REQUIRE(v.getRawValue(3) == TestType(400));
    }
}


TEMPLATE_TEST_CASE("Vector4 Raw Access", "[Vector4][core]", int)
{
    using Vector = ETL::Math::Vector4<TestType>;

    SECTION("Raw access")
    {
        Vector v{ TestType(10), TestType(20), TestType(30), TestType(40) };

        REQUIRE(v.x() == TestType(10));
        REQUIRE(v.y() == TestType(20));
        REQUIRE(v.z() == TestType(30));
        REQUIRE(v.w() == TestType(40));
        REQUIRE(v.getRawValue(0) == TestType(10 << ETL::Math::FIXED_SHIFT));
        REQUIRE(v.getRawValue(1) == TestType(20 << ETL::Math::FIXED_SHIFT));
        REQUIRE(v.getRawValue(2) == TestType(30 << ETL::Math::FIXED_SHIFT));
        REQUIRE(v.getRawValue(3) == TestType(40 << ETL::Math::FIXED_SHIFT));

        v.setRawValue(0, TestType(100));
        v.setRawValue(1, TestType(200));
        v.setRawValue(2, TestType(300));
        v.setRawValue(3, TestType(400));

        REQUIRE(v.getRawValue(0) == TestType(100));
        REQUIRE(v.getRawValue(1) == TestType(200));
        REQUIRE(v.getRawValue(2) == TestType(300));
        REQUIRE(v.getRawValue(3) == TestType(400));
    }
}


TEMPLATE_TEST_CASE("Vector4 isEqual with epsilon", "[Vector4][utils]", float, double)
{
    using Vector = ETL::Math::Vector4<TestType>;

    const Vector v1{ TestType(1),      TestType(2)     , TestType(3)     , TestType(4) };
    const Vector v2{ TestType(1.0001), TestType(2.0001), TestType(3.0001), TestType(4.0001) };
    const Vector v3{ TestType(1.1),    TestType(2.1)   , TestType(3.1)   , TestType(4.1) };

    REQUIRE(ETL::Math::isEqual(v1, v2, TestType(0.001)));
    REQUIRE_FALSE(ETL::Math::isEqual(v1, v3, TestType(0.001)));
    REQUIRE(ETL::Math::isEqual(v1, v3, TestType(0.15)));
}


TEMPLATE_TEST_CASE("Vector4 isEqual with epsilon", "[Vector4][utils]", int)
{
    using Vector = ETL::Math::Vector4<TestType>;

    const Vector v1{ TestType(1), TestType(2), TestType(3), TestType(4) };
    const Vector v2{ TestType(1), TestType(2), TestType(3), TestType(4) };
    const Vector v3{ TestType(2), TestType(3), TestType(4), TestType(4) };

    REQUIRE(ETL::Math::isEqual(v1, v2, TestType(1)));
    REQUIRE_FALSE(ETL::Math::isEqual(v1, v3, TestType(1)));
    REQUIRE(ETL::Math::isEqual(v1, v3, TestType(2)));
}


TEMPLATE_TEST_CASE("Vector4 Arithmetic", "[Vector4][math]", VECTOR4_TYPES)
{
    using Vector = ETL::Math::Vector4<TestType>;

    const Vector v1{ TestType(4), TestType(6), TestType(8), TestType(10) };
    const Vector v2{ TestType(2), TestType(3), TestType(4), TestType(5)  };

    SECTION("Minus operator")
    {
        const Vector res = -v1;
        REQUIRE(res.x() == TestType(-4));
        REQUIRE(res.y() == TestType(-6));
        REQUIRE(res.z() == TestType(-8));
        REQUIRE(res.w() == TestType(-10));
    }

    SECTION("Addition")
    {
        const Vector res = v1 + v2;
        REQUIRE(res.x() == TestType(6));
        REQUIRE(res.y() == TestType(9));
        REQUIRE(res.z() == TestType(12));
        REQUIRE(res.w() == TestType(15));

        Vector res2 = v1;
        res2 += v2;
        REQUIRE(res2 == res);
    }

    SECTION("Subtraction")
    {
        const Vector res = v1 - v2;
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(3));
        REQUIRE(res.z() == TestType(4));
        REQUIRE(res.w() == TestType(5));

        Vector res2 = v1;
        res2 -= v2;
        REQUIRE(res2 == res);
    }

    SECTION("Scalar Multiplication")
    {
        const Vector res = v1 * TestType(2);
        REQUIRE(res.x() == TestType(8));
        REQUIRE(res.y() == TestType(12));
        REQUIRE(res.z() == TestType(16));
        REQUIRE(res.w() == TestType(20));

        Vector res2 = v1;
        res2 *= TestType(2);
        REQUIRE(res2 == res);

        const Vector res3 = TestType(2) * v1;
        REQUIRE(res3 == res);
    }

    SECTION("Scalar Division")
    {
        const Vector res = v1 / TestType(2);
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(3));
        REQUIRE(res.z() == TestType(4));
        REQUIRE(res.w() == TestType(5));

        Vector res2 = v1;
        res2 /= TestType(2);
        REQUIRE(res2 == res);
    }

    SECTION("Component-wise Mul and Div")
    {
        Vector res1 = v1.componentMul(v2);
        REQUIRE(res1.x() == TestType(8));
        REQUIRE(res1.y() == TestType(18));
        REQUIRE(res1.z() == TestType(32));
        REQUIRE(res1.w() == TestType(50));
        res1.componentDivInPlace(v2);
        REQUIRE(res1 == v1);

        Vector res2 = v1.componentDiv(v2);
        REQUIRE(res2.x() == TestType(2));
        REQUIRE(res2.y() == TestType(2));
        REQUIRE(res2.z() == TestType(2));
        REQUIRE(res2.w() == TestType(2));
        res2.componentMulInPlace(v2);
        REQUIRE(res2 == v1);
    }

    SECTION("Dot Product")
    {
        const double d1 = v1.dot(v2); /// d = 4*2 + 6*3 + 8*4 + 10*5
        REQUIRE(d1 == 108.0);

        const Vector v3{ TestType(4), TestType(3), TestType(2), TestType(1) };
        const double d2 = v1.dot(v3); /// d = 4*4 + 6*3 + 8*2 10*1
        REQUIRE(d2 == 60.0);

        const double d3 = v1 * v3;
        REQUIRE(d2 == d3);
    }
}


TEMPLATE_TEST_CASE("Vector4 Length", "[Vector4][geo]", VECTOR4_TYPES)
{
    using Vector = ETL::Math::Vector4<TestType>;

    SECTION("Length")
    {
        const Vector v1{ TestType(3), TestType(4), TestType(5), TestType(6) };
        REQUIRE(v1.lengthSquared() == 86.0);
        REQUIRE(v1.length() == std::sqrt(86.0));

        const Vector v2{ TestType(1), TestType(2), TestType(3), TestType(4) };
        REQUIRE(v2.lengthSquared() == 30.0);
        REQUIRE(v2.length() == std::sqrt(30.0));
    }
}


TEMPLATE_TEST_CASE("Vector4 Normalization", "[Vector4][geo]", float, double)
{
    using Vector = ETL::Math::Vector4<TestType>;

    SECTION("Normalization")
    {
        Vector v{ TestType(1), TestType(2), TestType(3), TestType(4) };
        const double invLength = 1.0 / v.length();

        const Vector vn = v.normalize();
        REQUIRE(vn.lengthSquared() == Catch::Approx(1.0));
        REQUIRE(vn.length() == Catch::Approx(1.0));
        REQUIRE(vn.x() == Catch::Approx(static_cast<TestType>(1.0 * invLength)));
        REQUIRE(vn.y() == Catch::Approx(static_cast<TestType>(2.0 * invLength)));
        REQUIRE(vn.z() == Catch::Approx(static_cast<TestType>(3.0 * invLength)));
        REQUIRE(vn.w() == Catch::Approx(static_cast<TestType>(4.0 * invLength)));

        v.makeNormalize();
        REQUIRE(v.length() == Catch::Approx(1.0));
        REQUIRE(v.x() == Catch::Approx(vn.x()));
        REQUIRE(v.y() == Catch::Approx(vn.y()));
        REQUIRE(v.z() == Catch::Approx(vn.z()));
        REQUIRE(v.w() == Catch::Approx(vn.w()));
    }
}


TEMPLATE_TEST_CASE("Vector4 Normalization", "[Vector4][geo]", int)
{
    using Vector = ETL::Math::Vector4<TestType>;

    SECTION("Normalization")
    {
        Vector v{ TestType(1), TestType(2), TestType(3), TestType(4) };
        const double invLength = 1.0 / v.length();

        const Vector vn = v.normalize();
        REQUIRE(ETL::Math::isEqual(vn.lengthSquared(), 1.0, 0.0001));
        REQUIRE(ETL::Math::isEqual(vn.length(), 1.0, 0.0001));
        REQUIRE(vn.getRawValue(0) == Catch::Approx(static_cast<TestType>(1.0 * invLength * ETL::Math::FIXED_ONE)));
        REQUIRE(vn.getRawValue(1) == Catch::Approx(static_cast<TestType>(2.0 * invLength * ETL::Math::FIXED_ONE)));
        REQUIRE(vn.getRawValue(2) == Catch::Approx(static_cast<TestType>(3.0 * invLength * ETL::Math::FIXED_ONE)));
        REQUIRE(vn.getRawValue(3) == Catch::Approx(static_cast<TestType>(4.0 * invLength * ETL::Math::FIXED_ONE)));

        v.makeNormalize();
        REQUIRE(ETL::Math::isEqual(v.length(), 1.0, 0.0001));
        REQUIRE(v.getRawValue(0) == Catch::Approx(vn.getRawValue(0)));
        REQUIRE(v.getRawValue(1) == Catch::Approx(vn.getRawValue(1)));
        REQUIRE(v.getRawValue(2) == Catch::Approx(vn.getRawValue(2)));
        REQUIRE(v.getRawValue(3) == Catch::Approx(vn.getRawValue(3)));
    }
}


TEMPLATE_TEST_CASE("Vector4 factories", "[Vector4][utils]", VECTOR4_TYPES)
{
    using Vector = ETL::Math::Vector4<TestType>;

    SECTION("Common Constants")
    {
        REQUIRE(Vector::Zero() == Vector{ TestType(0), TestType(0), TestType(0), TestType(0) });
        REQUIRE(Vector::One()  == Vector{ TestType(1), TestType(1), TestType(1), TestType(1) });
        REQUIRE(Vector::DirX() == Vector{ TestType(1), TestType(0), TestType(0), TestType(0) });
        REQUIRE(Vector::DirY() == Vector{ TestType(0), TestType(1), TestType(0), TestType(0) });
        REQUIRE(Vector::DirZ() == Vector{ TestType(0), TestType(0), TestType(1), TestType(0) });
    }
}


TEMPLATE_TEST_CASE("Vector4 3D Transform", "[Vector4][utils]", VECTOR4_TYPES)
{
    using Vector4 = ETL::Math::Vector4<TestType>;
    using Vector3 = ETL::Math::Vector3<TestType>;

    const Vector3 vec3{ TestType(4), TestType(5), TestType(6) };

    SECTION("3D Transform factories")
    {
        const Vector4 point = Vector4::MakePoint(vec3);
        REQUIRE(point.x() == TestType(4));
        REQUIRE(point.y() == TestType(5));
        REQUIRE(point.z() == TestType(6));
        REQUIRE(point.w() == TestType(1));

        const Vector4 dir = Vector4::MakeDirection(vec3);
        REQUIRE(dir.x() == TestType(4));
        REQUIRE(dir.y() == TestType(5));
        REQUIRE(dir.z() == TestType(6));
        REQUIRE(dir.w() == TestType(0));
    }

    SECTION("3D Transform helpers")
    {
        const Vector4 p{ vec3, TestType(1) };
        REQUIRE(p.isPoint());
        REQUIRE_FALSE(p.isDirection());

        const Vector4 d{ vec3, TestType(0) };
        REQUIRE(d.isDirection());
        REQUIRE_FALSE(d.isPoint());

        const Vector3 v1 = p.toVector3();
        REQUIRE(v1 == vec3);

        const Vector4 v2{ TestType(4), TestType(6), TestType(8), TestType(2) };
        const Vector3 res = v2.perspectiveDivide();
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(3));
        REQUIRE(res.z() == TestType(4));
    }
}
