///----------------------------------------------------------------------------
/// ETL - MathLib
/// Version.h
///----------------------------------------------------------------------------

#pragma once


/// Version info
#define MATHLIB_VERSION_MAJOR 0
#define MATHLIB_VERSION_MINOR 1
#define MATHLIB_VERSION_PATCH 0

// Helper macros
#define MATHLIB_VERSION_STRING "0.1.0"
#define MATHLIB_VERSION_NUMBER (MATHLIB_VERSION_MAJOR * 10000 + \
                                MATHLIB_VERSION_MINOR * 100 + \
                                MATHLIB_VERSION_PATCH)
