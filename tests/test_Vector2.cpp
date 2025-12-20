///----------------------------------------------------------------------------
/// ETL - MathLib Unit Test
/// test_Vector2.h
///----------------------------------------------------------------------------
#include <catch_amalgamated.hpp>
#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Vector2.h>

#define VECTOR2_TYPES int, float, double

TEMPLATE_TEST_CASE("Vector2 Construction & Access", "[Vector2][core]", VECTOR2_TYPES)
{
    using Vector = ETL::Math::Vector2<TestType>;

    SECTION("Scalar constructor")
    {
        Vector v{ TestType(5) };
        REQUIRE(v.x() == TestType(5));
        REQUIRE(v.y() == TestType(5));
    }

    SECTION("Component constructor")
    {
        Vector v{ TestType(3), TestType(4) };
        REQUIRE(v.x() == TestType(3));
        REQUIRE(v.y() == TestType(4));
    }

    SECTION("Accessors and Mutators") {
        Vector v;
        v.x(TestType(10));
        v.y(TestType(20));

        REQUIRE(v.x() == TestType(10));
        REQUIRE(v.y() == TestType(20));

        REQUIRE(v[0] == TestType(10));
        REQUIRE(v[1] == TestType(20));

        v[0] = TestType(5);
        REQUIRE(v.x() == TestType(5));
    }

    SECTION("Equality and inequality operators")
    {
        Vector vA{ TestType(3), TestType(4) };
        Vector vB{ TestType(3), TestType(4) };
        Vector vC{ TestType(4), TestType(3) };
        REQUIRE(vA == vB);
        REQUIRE(vA != vC);
        REQUIRE_FALSE(vA == vC);
    }
}


TEMPLATE_TEST_CASE("Vector2 isEqual with epsilon - floating", "[Vector2][utils]", float, double)
{
    using Vector = ETL::Math::Vector2<TestType>;

    const Vector v1{ TestType(1),      TestType(2) };
    const Vector v2{ TestType(1.0001), TestType(2.0001) };
    const Vector v3{ TestType(1.1),    TestType(2.1) };

    REQUIRE(ETL::Math::isEqual(v1, v2, TestType(0.001)));
    REQUIRE_FALSE(ETL::Math::isEqual(v1, v3, TestType(0.001)));
    REQUIRE(ETL::Math::isEqual(v1, v3, TestType(0.15)));
}


TEMPLATE_TEST_CASE("Vector2 isEqual with epsilon - integers", "[Vector2][utils]", int)
{
    using Vector = ETL::Math::Vector2<TestType>;

    const Vector v1{ TestType(1), TestType(2) };
    const Vector v2{ TestType(1), TestType(2) };
    const Vector v3{ TestType(2), TestType(3) };

    REQUIRE(ETL::Math::isEqual(v1, v2, TestType(1)));
    REQUIRE_FALSE(ETL::Math::isEqual(v1, v3, TestType(1)));
    REQUIRE(ETL::Math::isEqual(v1, v3, TestType(2)));
}


TEMPLATE_TEST_CASE("Vector2 Arithmetic", "[Vector2][math]", VECTOR2_TYPES)
{
    using Vector = ETL::Math::Vector2<TestType>;

    const Vector v1{ TestType(4), TestType(6) };
    const Vector v2{ TestType(2), TestType(3) };

    SECTION("Minus operator")
    {
        const Vector res = -v1;
        REQUIRE(res.x() == TestType(-4));
        REQUIRE(res.y() == TestType(-6));
    }

    SECTION("Addition")
    {
        const Vector res = v1 + v2;
        REQUIRE(res.x() == TestType(6));
        REQUIRE(res.y() == TestType(9));

        Vector v3 = v1;
        v3 += v2;
        REQUIRE(v3 == res);
    }

    SECTION("Subtraction")
    {
        const Vector res = v1 - v2;
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(3));

        Vector v3 = v1;
        v3 -= v2;
        REQUIRE(v3 == res);
    }

    SECTION("Scalar Multiplication")
    {
        const Vector res = v1 * TestType(2);
        REQUIRE(res.x() == TestType(8));
        REQUIRE(res.y() == TestType(12));

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

        Vector res2 = v1;
        res2 /= TestType(2);
        REQUIRE(res2 == res);
    }

    SECTION("Component-wise Mul and Div")
    {
        Vector res1 = v1.componentMul(v2);
        REQUIRE(res1.x() == TestType(8));
        REQUIRE(res1.y() == TestType(18));
        res1.componentDivInPlace(v2);
        REQUIRE(res1 == v1);

        Vector res2 = v1.componentDiv(v2);
        REQUIRE(res2.x() == TestType(2));
        REQUIRE(res2.y() == TestType(2));
        res2.componentMulInPlace(v2);
        REQUIRE(res2 == v1);
    }

    SECTION("Dot Product")
    {
        const double d1 = v1.dot(v2);  /// 4*2 + 6*3
        REQUIRE(d1 == 26.0);

        const Vector v3{ TestType(2), TestType(1) };
        const double d2 = v1.dot(v3);  /// 4*2 + 6*1
        REQUIRE(d2 == 14.0);

        const double d3 = v1 * v3;
        REQUIRE(d2 == d3);
    }

    SECTION("Cross Product")
    {
        const double c1 = v1.cross(v2); /// 4*3 - 6*2
        REQUIRE(c1 == 0.0);

        const Vector v3{ TestType(2), TestType(1) };
        const double c2 = v1.cross(v3); /// 4*1 - 6*2
        REQUIRE(c2 == -8.0);

        const double c3 = v1 ^ v3;
        REQUIRE(c2 == c3);
    }
}


TEMPLATE_TEST_CASE("Vector2 Length", "[Vector2][geo]", VECTOR2_TYPES)
{
    using Vector = ETL::Math::Vector2<TestType>;

    SECTION("Length")
    {
        const Vector v1{ TestType(3), TestType(4) }; /// 3-4-5 triangle logic
        REQUIRE(v1.lengthSquared() == 25.0);
        REQUIRE(v1.length() == 5.0);

        const Vector v2{ TestType(1), TestType(2) };
        REQUIRE(v2.lengthSquared() == 5.0);
        REQUIRE(v2.length() == std::sqrt(5.0));
    }
}


TEMPLATE_TEST_CASE("Vector2 Normalization", "[Vector2][geo]", float, double)
{
    using Vector = ETL::Math::Vector2<TestType>;

    SECTION("Normalization")
    {
        Vector v{ TestType(3), TestType(4) }; /// 3-4-5 triangle logic

        const Vector vn = v.normalize();
        REQUIRE(vn.lengthSquared() == Catch::Approx(1.0));
        REQUIRE(vn.length() == Catch::Approx(1.0));
        REQUIRE(vn.x() == Catch::Approx(TestType(0.6))); // 3/5
        REQUIRE(vn.y() == Catch::Approx(TestType(0.8))); // 4/5

        v.makeNormalize();
        REQUIRE(v.length() == Catch::Approx(1.0));
        REQUIRE(v.x() == Catch::Approx(vn.x()));
        REQUIRE(v.y() == Catch::Approx(vn.y()));
    }
}


TEMPLATE_TEST_CASE("Vector2 Normalization", "[Vector2][geo]", int)
{
    using Vector = ETL::Math::Vector2<TestType>;

    SECTION("Normalization")
    {
        Vector v{ TestType(3), TestType(4) }; /// 3-4-5 triangle logic

        const Vector vn = v.normalize();
        REQUIRE(ETL::Math::isEqual(vn.lengthSquared(), 1.0, 0.0001));
        REQUIRE(ETL::Math::isEqual(vn.length(), 1.0, 0.0001));
        REQUIRE(vn.getRawValue(0) == Catch::Approx(static_cast<TestType>(0.6 * ETL::Math::FIXED_ONE))); // 3/5
        REQUIRE(vn.getRawValue(1) == Catch::Approx(static_cast<TestType>(0.8 * ETL::Math::FIXED_ONE))); // 4/5

        v.makeNormalize();
        REQUIRE(ETL::Math::isEqual(v.length(), 1.0, 0.0001));
        REQUIRE(v.getRawValue(0) == Catch::Approx(vn.getRawValue(0)));
        REQUIRE(v.getRawValue(1) == Catch::Approx(vn.getRawValue(1)));
        REQUIRE(v == vn);
    }
}


TEMPLATE_TEST_CASE("Vector2 factories", "[Vector2][utils]", VECTOR2_TYPES)
{
    using Vector = ETL::Math::Vector2<TestType>;

    SECTION("Common Constants")
    {
        REQUIRE(Vector::zero()  == Vector{ TestType(0), TestType(0) });
        REQUIRE(Vector::one()   == Vector{ TestType(1), TestType(1) });
        REQUIRE(Vector::unitX() == Vector{ TestType(1), TestType(0) });
        REQUIRE(Vector::unitY() == Vector{ TestType(0), TestType(1) });
    }

    SECTION("Semantic aliases")
    {
        REQUIRE(Vector::up()    == Vector{ TestType(0),  TestType(1)  });
        REQUIRE(Vector::down()  == Vector{ TestType(0),  TestType(-1) });
        REQUIRE(Vector::left()  == Vector{ TestType(-1), TestType(0)  });
        REQUIRE(Vector::right() == Vector{ TestType(1),  TestType(0)  });
    }
}
