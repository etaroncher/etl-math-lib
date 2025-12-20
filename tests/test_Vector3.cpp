///----------------------------------------------------------------------------
/// ETL - MathLib Unit Test
/// test_Vector3.h
///----------------------------------------------------------------------------
#include <catch_amalgamated.hpp>
#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Vector3.h>

#define VECTOR3_TYPES int, float, double

TEMPLATE_TEST_CASE("Vector3 Construction & Access", "[Vector3][core]", VECTOR3_TYPES)
{
    using Vector = ETL::Math::Vector3<TestType>;

    SECTION("Scalar constructor")
    {
        Vector v{ TestType(5) };
        REQUIRE(v.x() == TestType(5));
        REQUIRE(v.y() == TestType(5));
        REQUIRE(v.z() == TestType(5));
    }

    SECTION("Component constructor")
    {
        Vector v{ TestType(3), TestType(4), TestType(5) };
        REQUIRE(v.x() == TestType(3));
        REQUIRE(v.y() == TestType(4));
        REQUIRE(v.z() == TestType(5));
    }

    SECTION("From-vector2 constructor")
    {
        ETL::Math::Vector2<Type> vec2{ TestType(3), TestType(4) };
        Vector v{ vec2, TestType(5) };
        REQUIRE(v.x() == TestType(3));
        REQUIRE(v.y() == TestType(4));
        REQUIRE(v.z() == TestType(5));
    }

    SECTION("Accessors and Mutators") {
        Vector v;
        v.x(TestType(10));
        v.y(TestType(20));
        v.z(TestType(30));

        REQUIRE(v.x() == TestType(10));
        REQUIRE(v.y() == TestType(20));
        REQUIRE(v.z() == TestType(30));

        REQUIRE(v[0] == TestType(10));
        REQUIRE(v[1] == TestType(20));
        REQUIRE(v[2] == TestType(30));

        v[0] = TestType(5);
        REQUIRE(v.x() == TestType(5));
    }

    SECTION("Equality and inequality operators")
    {
        Vector vA{ TestType(3), TestType(4), TestType(5) };
        Vector vB{ TestType(3), TestType(4), TestType(5) };
        Vector vC{ TestType(4), TestType(3), TestType(5) };
        REQUIRE(vA == vB);
        REQUIRE(vA != vC);
        REQUIRE_FALSE(vA == vC);
    }
}


TEMPLATE_TEST_CASE("Vector3 isEqual with epsilon - floating", "[Vector3][utils]", float, double)
{
    using Vector = ETL::Math::Vector3<TestType>;

    const Vector v1{ TestType(1),      TestType(2)     , TestType(3) };
    const Vector v2{ TestType(1.0001), TestType(2.0001), TestType(3.0001) };
    const Vector v3{ TestType(1.1),    TestType(2.1)   , TestType(3.1) };

    REQUIRE(ETL::Math::isEqual(v1, v2, TestType(0.001)));
    REQUIRE_FALSE(ETL::Math::isEqual(v1, v3, TestType(0.001)));
    REQUIRE(ETL::Math::isEqual(v1, v3, TestType(0.15)));
}


TEMPLATE_TEST_CASE("Vector3 isEqual with epsilon - integers", "[Vector3][utils]", int)
{
    using Vector = ETL::Math::Vector3<TestType>;

    const Vector v1{ TestType(1), TestType(2), TestType(3) };
    const Vector v2{ TestType(1), TestType(2), TestType(3) };
    const Vector v3{ TestType(2), TestType(3), TestType(4) };

    REQUIRE(ETL::Math::isEqual(v1, v2, TestType(1)));
    REQUIRE_FALSE(ETL::Math::isEqual(v1, v3, TestType(1)));
    REQUIRE(ETL::Math::isEqual(v1, v3, TestType(2)));
}


TEMPLATE_TEST_CASE("Vector3 Arithmetic", "[Vector3][math]", VECTOR3_TYPES)
{
    using Vector = ETL::Math::Vector3<TestType>;

    const Vector v1{ TestType(4), TestType(6), TestType(8) };
    const Vector v2{ TestType(2), TestType(3), TestType(4) };

    SECTION("Minus operator")
    {
        const Vector res = -v1;
        REQUIRE(res.x() == TestType(-4));
        REQUIRE(res.y() == TestType(-6));
        REQUIRE(res.z() == TestType(-8));
    }

    SECTION("Addition")
    {
        const Vector res = v1 + v2;
        REQUIRE(res.x() == TestType(6));
        REQUIRE(res.y() == TestType(9));
        REQUIRE(res.z() == TestType(12));

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
        res1.componentDivInPlace(v2);
        REQUIRE(res1 == v1);

        Vector res2 = v1.componentDiv(v2);
        REQUIRE(res2.x() == TestType(2));
        REQUIRE(res2.y() == TestType(2));
        REQUIRE(res2.z() == TestType(2));
        res2.componentMulInPlace(v2);
        REQUIRE(res2 == v1);
    }

    SECTION("Dot Product")
    {
        const double d1 = v1.dot(v2); /// d = 4*2 + 6*3 + 8*4
        REQUIRE(d1 == 58.0);

        const Vector v3{ TestType(3), TestType(2), TestType(1) };
        const double d2 = v1.dot(v3); /// d = 4*3 + 6*2 + 8*1
        REQUIRE(d2 == 32.0);

        const double d3 = v1 * v3;
        REQUIRE(d2 == d3);
    }

    SECTION("Cross Product")
    {
        const Vector c1 = v1.cross(v2);
        REQUIRE(isZero(c1));  /// { 6*4-8*3, 8*2-4*4, 4*3-6*2 } = Vector::ZERO

        const Vector v3{ TestType(3), TestType(2), TestType(1) };
        const Vector c2 = v1.cross(v3);
        REQUIRE(c2.x() == TestType(-10)); /// 6*1 - 8*2
        REQUIRE(c2.y() == TestType( 20)); /// 8*3 - 4*1
        REQUIRE(c2.z() == TestType(-10)); /// 4*2 - 6*3

        const double c3 = v1 ^ v3;
        REQUIRE(c2 == c3);
    }
}


TEMPLATE_TEST_CASE("Vector3 Length", "[Vector3][geo]", VECTOR3_TYPES)
{
    using Vector = ETL::Math::Vector3<TestType>;

    SECTION("Length")
    {
        const Vector v1{ TestType(3), TestType(0), TestType(4) }; /// 3-4-5 triangle logic
        REQUIRE(v1.lengthSquared() == 25.0);
        REQUIRE(v1.length() == 5.0);

        const Vector v2{ TestType(1), TestType(2), TestType(3) };
        REQUIRE(v2.lengthSquared() == 14.0);
        REQUIRE(v2.length() == std::sqrt(14.0));
    }
}


TEMPLATE_TEST_CASE("Vector3 Normalization", "[Vector3][geo]", float, double)
{
    using Vector = ETL::Math::Vector3<TestType>;

    SECTION("Normalization")
    {
        Vector v{ TestType(3), TestType(0), TestType(4) }; /// 3-4-5 triangle logic

        const Vector vn = v.normalize();
        REQUIRE(vn.lengthSquared() == Catch::Approx(1.0));
        REQUIRE(vn.length() == Catch::Approx(1.0));
        REQUIRE(vn.x() == Catch::Approx(TestType(0.6))); // 3/5
        REQUIRE(vn.y() == Catch::Approx(TestType(0.0))); // 0/5
        REQUIRE(vn.z() == Catch::Approx(TestType(0.8))); // 4/5

        v.makeNormalize();
        REQUIRE(v.length() == Catch::Approx(1.0));
        REQUIRE(v.x() == Catch::Approx(vn.x()));
        REQUIRE(v.y() == Catch::Approx(vn.y()));
        REQUIRE(v.z() == Catch::Approx(vn.z()));
    }
}

TEMPLATE_TEST_CASE("Vector3 Normalization", "[Vector3][geo]", int)
{
    using Vector = ETL::Math::Vector3<TestType>;

    SECTION("Normalization")
    {
        Vector v{ TestType(3), TestType(0), TestType(4) }; /// 3-4-5 triangle logic

        const Vector vn = v.normalize();
        REQUIRE(ETL::Math::isEqual(vn.lengthSquared(), 1.0, 0.0001));
        REQUIRE(ETL::Math::isEqual(vn.length(), 1.0, 0.0001));
        REQUIRE(vn.getRawValue(0) == Catch::Approx(static_cast<TestType>(0.6 * ETL::Math::FIXED_ONE))); // 3/5
        REQUIRE(vn.getRawValue(1) == Catch::Approx(static_cast<TestType>(0.0 * ETL::Math::FIXED_ONE))); // 0/5
        REQUIRE(vn.getRawValue(2) == Catch::Approx(static_cast<TestType>(0.8 * ETL::Math::FIXED_ONE))); // 4/5

        v.makeNormalize();
        REQUIRE(ETL::Math::isEqual(v.length(), 1.0, 0.0001));
        REQUIRE(v.getRawValue(0) == Catch::Approx(vn.getRawValue(0)));
        REQUIRE(v.getRawValue(1) == Catch::Approx(vn.getRawValue(1)));
        REQUIRE(v.getRawValue(2) == Catch::Approx(vn.getRawValue(2)));
    }
}


TEMPLATE_TEST_CASE("Vector3 factories", "[Vector3][utils]", VECTOR3_TYPES)
{
    using Vector = ETL::Math::Vector3<TestType>;

    SECTION("Common Constants")
    {
        REQUIRE(Vector::zero()  == Vector{ TestType(0), TestType(0), TestType(0) });
        REQUIRE(Vector::one()   == Vector{ TestType(1), TestType(1), TestType(1) });
        REQUIRE(Vector::unitX() == Vector{ TestType(1), TestType(0), TestType(0) });
        REQUIRE(Vector::unitY() == Vector{ TestType(0), TestType(1), TestType(0) });
        REQUIRE(Vector::unitZ() == Vector{ TestType(0), TestType(0), TestType(1) });
    }

    SECTION("Semantic aliases")
    {
        REQUIRE(Vector::up()      == Vector{ TestType(0),  TestType(1),  TestType(0)  });
        REQUIRE(Vector::down()    == Vector{ TestType(0),  TestType(-1), TestType(0)  });
        REQUIRE(Vector::left()    == Vector{ TestType(-1), TestType(0),  TestType(0)  });
        REQUIRE(Vector::right()   == Vector{ TestType(1),  TestType(0),  TestType(0)  });
        REQUIRE(Vector::forward() == Vector{ TestType(0),  TestType(0),  TestType(-1) });
        REQUIRE(Vector::back()    == Vector{ TestType(0),  TestType(0),  TestType(1)  });
    }
}


TEMPLATE_TEST_CASE("Vector3 2D Transform", "[Vector3][utils]", VECTOR3_TYPES)
{
    using Vector3 = ETL::Math::Vector3<TestType>;
    using Vector2 = ETL::Math::Vector2<TestType>;

    const Vector2 vec2{ Type(4), Type(5) };

    SECTION("2D Transform factories")
    {
        const Vector3 point = Vector3::MakePoint(vec2);
        REQUIRE(point.x() == TestType(4));
        REQUIRE(point.y() == TestType(5));
        REQUIRE(point.z() == TestType(1));

        const Vector3 dir = Vector3::MakeDirection(vec2);
        REQUIRE(dir.x() == TestType(4));
        REQUIRE(dir.y() == TestType(5));
        REQUIRE(dir.z() == TestType(0));
    }

    SECTION("2D Transform helpers")
    {
        const Vector3 p{ vec2, Type(1) };
        REQUIRE(p.isPoint());
        REQUIRE_FALSE(p.isDirection());

        const Vector3 d{ vec2, Type(0) };
        REQUIRE(d.isDirection());
        REQUIRE_FALSE(d.isPoint());

        const Vector2 v1 = p.toVector2();
        REQUIRE(v1 == vec2);

        const Vector3 v2{ Type(4), Type(8), Type(2) };
        const Vector2 res = v2.perspectiveDivide();
        REQUIRE(res.x() = Type(2));
        REQUIRE(res.y() = Type(4));
    }
}
