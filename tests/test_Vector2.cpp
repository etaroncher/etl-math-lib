///----------------------------------------------------------------------------
/// ETL - MathLib Unit Test
/// test_Vector2.h
///----------------------------------------------------------------------------
#include <catch_amalgamated.hpp>
#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Vector2.h>

TEMPLATE_TEST_CASE("Vector2 Construction & Acces", "[Vector2][core]", int, float, double)
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

        // Array operator
        REQUIRE(v[0] == TestType(10));
        REQUIRE(v[1] == TestType(20));

        v[0] = TestType(5);
        REQUIRE(v.x() == TestType(5));
    }
}


TEMPLATE_TEST_CASE("Vector2 Arithmetic", "[Vector2][math]", int, float, double)
{
    using Vector = ETL::Math::Vector2<TestType>;

    const Vector v1{ TestType(1), TestType(2) };
    const Vector v2{ TestType(3), TestType(4) };

    SECTION("Addition")
    {
        const Vector res = v1 + v2;
        REQUIRE(res.x() == TestType(4));
        REQUIRE(res.y() == TestType(6));

        Vector v3 = v1;
        v3 += v2;
        REQUIRE(v3 == res);
    }

    SECTION("Substraction")
    {
        const Vector res = v2 - v1;
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(2));

        Vector v3 = v2;
        v3 -= v1;
        REQUIRE(v3 == res);
    }

    SECTION("Scalar Multiplication")
    {
        const Vector res = v1 * TestType(2);
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(4));

        // Test Commutative Property (s * v)
        const Vector res2 = TestType(2) * v1;
        REQUIRE(res == res2);
    }

    SECTION("Scalar Division")
    {
        const Vector res = Vector{ TestType(4), TestType(6) } / TestType(2);
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(3));
    }

    SECTION("Dot Product")
    {
        // 1*3 + 2*4
        TestType d = dot(v1, v2);
        REQUIRE(d == TestType(11));
    }

    SECTION("Cross Product")
    {
        // 1*4-2*3
        TestType d = cross(v1, v2);
        REQUIRE(d == TestType(-2));
    }
}


TEMPLATE_TEST_CASE("Vector2 Lenght", "[Vector2][geo]", int, float, double)
{
    using Vector = ETL::Math::Vector2<TestType>;

    SECTION("Length")
    {
        const Vector v{ TestType(3), TestType(4) }; /// 3-4-5 triangle logic

        REQUIRE(v.lengthSquared() == TestType(25));
        REQUIRE(v.length() == TestType(5));
    }
}


TEMPLATE_TEST_CASE("Vector2 Normalization", "[Vector2][geo]", float, double)
{
    using Vector = ETL::Math::Vector2<TestType>;

    SECTION("Normalization")
    {
        Vector v{ TestType(3), TestType(4) }; /// 3-4-5 triangle logic

        const Vector vn = v.normalize();
        REQUIRE(vn.length() == Catch::Approx(1.0));
        REQUIRE(vn.x() == Catch::Approx(0.6)); // 3/5
        REQUIRE(vn.y() == Catch::Approx(0.8)); // 4/5

        v.makeNormalize();
        REQUIRE(v.length() == Catch::Approx(1.0));
        REQUIRE(v.x() == Catch::Approx(vn.x()));
        REQUIRE(v.y() == Catch::Approx(vn.y()));
    }
}


TEMPLATE_TEST_CASE("Vector2 isEqual with epsilon - floating", "[Vector2][utils]", float, double)
{
    using Vector = ETL::Math::Vector2<TestType>;

    const Vector v1{ TestType(1),      TestType(2)      };
    const Vector v2{ TestType(1.0001), TestType(2.0001) };
    const Vector v3{ TestType(1.1),    TestType(2.1)    };

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


TEMPLATE_TEST_CASE("Vector2 factories", "[Vector2][utils]", int, float, double)
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
