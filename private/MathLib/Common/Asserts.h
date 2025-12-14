///----------------------------------------------------------------------------
/// ETL - MathLib
/// Asserts.h
///----------------------------------------------------------------------------
#pragma once

/// Assert
#ifdef NDEBUG
#define ETLMATH_ASSERT(condition, message) ((void)0)
#else
#include <cassert>
#define ETLMATH_ASSERT(condition, message) assert((condition) && (message))
#endif
