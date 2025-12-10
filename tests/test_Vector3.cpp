///----------------------------------------------------------------------------
/// ETL - MathLib Unit Test
/// test_Vector3.h
///----------------------------------------------------------------------------
#include <catch_amalgamated.hpp>
#include <MathLib/Common/TypeComparisons.h>
#include <MathLib/Types/Vector3.h>

TEMPLATE_TEST_CASE("Vector3 Construction & Acces", "[Vector3][core]", int, float, double)
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
}


TEMPLATE_TEST_CASE("Vector3 Arithmetic", "[Vector3][math]", int, float, double)
{
    using Vector = ETL::Math::Vector3<TestType>;

    const Vector v1{ TestType(1), TestType(2), TestType(3) };
    const Vector v2{ TestType(4), TestType(5), TestType(6) };

    SECTION("Equality")
    {
        const Vector v3 = v1;
        REQUIRE(v1 != v2);
        REQUIRE(v1 == v3);
        REQUIRE_FALSE(v1 == v2);
        REQUIRE_FALSE(v1 != v3);
    }

    SECTION("Addition")
    {
        const Vector res = v1 + v2;
        REQUIRE(res.x() == TestType(5));
        REQUIRE(res.y() == TestType(7));
        REQUIRE(res.z() == TestType(9));

        Vector res2 = v1;
        res2 += v2;
        REQUIRE(res2 == res);
    }

    SECTION("Substraction")
    {
        const Vector res = v2 - v1;
        REQUIRE(res.x() == TestType(3));
        REQUIRE(res.y() == TestType(3));
        REQUIRE(res.z() == TestType(3));

        Vector res2 = v2;
        res2 -= v1;
        REQUIRE(res2 == res);
    }

    SECTION("Scalar Multiplication")
    {
        const Vector res = v1 * TestType(2);
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(4));
        REQUIRE(res.z() == TestType(6));

        Vector res2 = v1;
        res2 *= TestType(2);
        REQUIRE(res2 == res);

        const Vector res3 = TestType(2) * v1;
        REQUIRE(res3 == res);
    }

    SECTION("Scalar Division")
    {
        const Vector v3{ TestType(4), TestType(6), TestType(8) };
        const Vector res = v3 / TestType(2);
        REQUIRE(res.x() == TestType(2));
        REQUIRE(res.y() == TestType(3));
        REQUIRE(res.z() == TestType(4));

        Vector res2 = v3;
        res2 /= TestType(2);
        REQUIRE(res2 == res);
    }

    SECTION("Dot Product")
    {
        /// d = 1*4 + 2*5 + 3*6 = 22
        TestType d = dot(v1, v2);
        REQUIRE(d == TestType(32));
    }

    SECTION("Cross Product")
    {
        /// res{ 2*6-3*5, 3*4-1*6, 1*5-2*4 }
        const Vector res = cross(v1, v2);
        REQUIRE(res.x() == TestType(-3));
        REQUIRE(res.y() == TestType( 6));
        REQUIRE(res.z() == TestType(-3));
    }
}


TEMPLATE_TEST_CASE("Vector3 Lenght", "[Vector3][geo]", int, float, double)
{
    using Vector = ETL::Math::Vector3<TestType>;

    SECTION("Length")
    {
        const Vector v{ TestType(3), TestType(0), TestType(4) }; /// 3-4-5 triangle logic

        REQUIRE(v.lengthSquared() == TestType(25));
        REQUIRE(v.length() == TestType(5));
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
        REQUIRE(vn.x() == Catch::Approx(0.6)); // 3/5
        REQUIRE(vn.y() == Catch::Approx(0.0)); // 0/5
        REQUIRE(vn.z() == Catch::Approx(0.8)); // 4/5

        v.makeNormalize();
        REQUIRE(v.length() == Catch::Approx(1.0));
        REQUIRE(v.x() == Catch::Approx(vn.x()));
        REQUIRE(v.y() == Catch::Approx(vn.y()));
        REQUIRE(v.z() == Catch::Approx(vn.z()));
    }
}


TEMPLATE_TEST_CASE("Vector3 isEqual with epsilon - floating", "[Vector3][utils]", float, double)
{
    using Vector = ETL::Math::Vector3<TestType>;

    const Vector v1{ TestType(1),      TestType(2)     , TestType(3)      };
    const Vector v2{ TestType(1.0001), TestType(2.0001), TestType(3.0001) };
    const Vector v3{ TestType(1.1),    TestType(2.1)   , TestType(3.1)    };

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


TEMPLATE_TEST_CASE("Vector3 factories", "[Vector3][utils]", int, float, double)
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
