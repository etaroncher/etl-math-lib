# MathLib/src/Types/CMakeLists.txt

# Source files
set(MODULE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Matrix3x3.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/Matrix4x4.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector4.cpp
)

# Header files
set(MODULE_HEADERS
    ${CMAKE_SOURCE_DIR}/include/MathLib/Types/Matrix3x3.h
    #${CMAKE_SOURCE_DIR}/include/MathLib/Types/Matrix4x4.h
    ${CMAKE_SOURCE_DIR}/include/MathLib/Types/Vector2.h
    ${CMAKE_SOURCE_DIR}/include/MathLib/Types/Vector3.h
    ${CMAKE_SOURCE_DIR}/include/MathLib/Types/Vector4.h

    ${CMAKE_SOURCE_DIR}/include/MathLib/Types/inline/Matrix3x3.inl
    #${CMAKE_SOURCE_DIR}/include/MathLib/Types/inline/Matrix4x4.inl
    ${CMAKE_SOURCE_DIR}/include/MathLib/Types/inline/Vector2.inl
    ${CMAKE_SOURCE_DIR}/include/MathLib/Types/inline/Vector3.inl
    ${CMAKE_SOURCE_DIR}/include/MathLib/Types/inline/Vector4.inl
)

# Header private files
set(MODULE_HEADERS_PRIVATE
)

# Append to MATHLIB_SOURCES & MATHLIB_HEADERS
set(MATHLIB_SOURCES         ${MATHLIB_SOURCES}         ${MODULE_SOURCES}         PARENT_SCOPE)
set(MATHLIB_HEADERS         ${MATHLIB_HEADERS}         ${MODULE_HEADERS}         PARENT_SCOPE)
set(MATHLIB_HEADERS_PRIVATE ${MATHLIB_HEADERS_PRIVATE} ${MODULE_HEADERS_PRIVATE} PARENT_SCOPE)
