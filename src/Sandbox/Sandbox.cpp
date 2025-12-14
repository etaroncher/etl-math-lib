#include <iostream>
#include "MathLib/Types/Matrix3x3.h"
#include "MathLib/Types/Vector3.h"
#include "MathLib/Types/Vector2.h"
#include "MathLib/Common/Asserts.h"

int main(int argc, char*argv[])
{
    using namespace ETL::Math;

    // Quick tests here
    Mat3 m = Mat3::Identity();
    m.scale(2.0, 3.0);

    Vec2 point{ 1.0f, 1.0f };
    Vec2 result = m.transformPoint(point);

    std::cout << "Result: (" << result.x() << ", " << result.y() << ")\n";

    m(0, 0) = 5.f;
    ETLMATH_ASSERT(5.f == m[0], "ops");

    std::cout << "Result: (" << m(0, 0) << " == 5.f)\n";

    m[2] = 6.f;
    ETLMATH_ASSERT(6.f == m(2, 0), "ops");

    std::cout << "Result: (" << m[2] << " == 6.f)\n";

    return 0;
}