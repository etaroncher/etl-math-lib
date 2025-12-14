///----------------------------------------------------------------------------
/// ETL - MathLib
/// FixedPointHelpers.h
///----------------------------------------------------------------------------
#pragma once

#include <concepts>

namespace ETL::Math
{
    /// Fixed point arithmetic - Define the precision (2^16 = 65536)
    constexpr int FIXED_SHIFT = 16;
    constexpr int FIXED_ONE = 1 << FIXED_SHIFT;


    /// Helper to safely convert FROM FIXED POINT to normal value
    template<typename Type>
    constexpr Type FromFixed(int val)
    {
        if constexpr (std::integral<Type>)
            return static_cast<Type>(val >> FIXED_SHIFT);
        else
            return static_cast<Type>(val) / FIXED_ONE;
    }


    /// Helper to safely convert from normal value TO FIXED POINT
    template<typename Type>
    constexpr int ToFixed(Type val)
    {
        return static_cast<int>(val * FIXED_ONE);
    }


    /// Helper to automatically convert or NOT convert 
    /// TO fixed point safely depending on return type
    template<typename ReturnType, typename InputType>
    constexpr ReturnType ProcessValue(InputType val)
    {
        if constexpr (std::integral<ReturnType>)
            return ToFixed<InputType>(val);
        else
            return static_cast<ReturnType>(val);
    }


    /// Helper to automatically convert or NOT convert 
    /// FROM fixed point safely depending
    template<typename ReturnType, typename InputType>
    constexpr ReturnType UnprocessValue(InputType val)
    {
        if constexpr (std::integral<InputType>)
            return FromFixed<ReturnType>(val);
        else
            return static_cast<ReturnType>(val);
    }
}
