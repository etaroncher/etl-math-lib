# MathLib/src/Common/CMakeLists.txt

# Source files
set(MODULE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ElementProxy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TypeComparisons.cpp
)

# Header files
set(MODULE_HEADERS
    ${CMAKE_SOURCE_DIR}/include/MathLib/Common/ElementProxy.h
    ${CMAKE_SOURCE_DIR}/include/MathLib/Common/TypeComparisons.h
)

# Header private files
set(MODULE_HEADERS_PRIVATE
    ${CMAKE_SOURCE_DIR}/private/MathLib/Common/Asserts.h
    ${CMAKE_SOURCE_DIR}/private/MathLib/Common/Constants.h
    ${CMAKE_SOURCE_DIR}/private/MathLib/Common/FixedPointHelpers.h
    ${CMAKE_SOURCE_DIR}/private/MathLib/Common/RawTag.h
)

# Append to MATHLIB_SOURCES & MATHLIB_HEADERS
set(MATHLIB_SOURCES         ${MATHLIB_SOURCES}         ${MODULE_SOURCES}         PARENT_SCOPE)
set(MATHLIB_HEADERS         ${MATHLIB_HEADERS}         ${MODULE_HEADERS}         PARENT_SCOPE)
set(MATHLIB_HEADERS_PRIVATE ${MATHLIB_HEADERS_PRIVATE} ${MODULE_HEADERS_PRIVATE} PARENT_SCOPE)
