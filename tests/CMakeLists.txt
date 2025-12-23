# MathLib/tests/CMakeLists.txt

# Test executable
add_executable(MathLib_Tests
    test_Vector2.cpp
    test_Vector3.cpp
    test_Vector4.cpp
    test_Matrix3x3.cpp
    test_Matrix4x4.cpp
    ${CMAKE_SOURCE_DIR}/external/catch2/v3.11.0/catch_amalgamated.cpp
)


target_include_directories(MathLib_Tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/external/catch2/v3.11.0
)

# Link against your library
target_link_libraries(MathLib_Tests PRIVATE MathLib)


# IDE source groups
source_group("Source Files\\Catch2" FILES 
    ${CMAKE_SOURCE_DIR}/external/catch2/v3.11.0/catch_amalgamated.cpp
)

# Register individual test groups with CTest
add_test(NAME Vector2_Tests      COMMAND MathLib_Tests "[Vector2]"      --reporter console)
add_test(NAME Vector3_Tests      COMMAND MathLib_Tests "[Vector3]"      --reporter console)
add_test(NAME Vector4_Tests      COMMAND MathLib_Tests "[Vector4]"      --reporter console)
add_test(NAME Matrix3x3_Tests    COMMAND MathLib_Tests "[Matrix3x3]"    --reporter console)
add_test(NAME Matrix4x4_Tests    COMMAND MathLib_Tests "[Matrix4x4]"    --reporter console)

# Or single test with organized output
# add_test(NAME AllMathLibTests COMMAND mathlib_tests --reporter console)