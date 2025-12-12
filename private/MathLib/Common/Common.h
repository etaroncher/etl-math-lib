///----------------------------------------------------------------------------
/// ETL - MathLib
/// Common.h
///----------------------------------------------------------------------------

#pragma once

/// Assert
#ifdef NDEBUG
#define ETLMATH_ASSERT(condition, message) ((void)0)
#else
#include <cassert>
#define ETLMATH_ASSERT(condition, message) assert((condition) && (message))
#endif

namespace ETL::Math
{
    /// Fixed point arithmetic - Define the precision (2^16 = 65536)
    constexpr int FIXED_SHIFT = 16;
    constexpr int FIXED_ONE = 1 << FIXED_SHIFT;


    /// Helper to convert to fixed point safely
    template<typename Type>
    constexpr int ToFixed(Type val)
    {
        return static_cast<int>(val * FIXED_ONE);
    }


    /// Helper to automatically convert or NOT convert 
    /// to fixed point safely depending on return type
    template<typename ReturnType, typename InputType>
    constexpr ReturnType ProcessValue(InputType val)
    {
        if constexpr (std::integral<ReturnType>)
            return ToFixed<InputType>(val);
        else
            return static_cast<ReturnType>(val);
    }
}