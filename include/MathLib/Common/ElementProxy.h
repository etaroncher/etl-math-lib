///----------------------------------------------------------------------------
/// ETL - MathLib
/// ElementProxy.h
///---------------------------------------------------------------------------- 
#pragma once

#include "MathLib/Common/FixedPointHelpers.h"

namespace ETL::Math
{
    /// Proxy class for non-const access
    template<typename Type>
    class ElementProxy
    {
    private:
        Type& element;

    public:
        ElementProxy(Type& elem);

        // Conversion operator for reading
        operator Type() const;

        // Assignment operator for writing
        ElementProxy& operator=(Type value);
        ElementProxy& operator=(const ElementProxy& other);

        // Compound operators if needed
        ElementProxy& operator+=(Type value);
        ElementProxy& operator-=(Type value);
        ElementProxy& operator*=(Type value);
        ElementProxy& operator/=(Type value);
    };


    /// Constructor
    template<typename Type>
    inline ElementProxy<Type>::ElementProxy(Type& elem)
        : element(elem)
    {
    }

    /// Read conversion
    template<typename Type>
    inline ElementProxy<Type>::operator Type() const
    {
        return UnprocessValue<Type>(element); /// Integers converted from Fixed Point
    }

    /// Write assignment
    template<typename Type>
    inline ElementProxy<Type>& ElementProxy<Type>::operator=(Type value)
    {
        element = ProcessValue<Type>(value); /// Integers converted to Fixed Point

        return *this;
    }

    /// Copy assignment from another proxy
    template<typename Type>
    inline ElementProxy<Type>& ElementProxy<Type>::operator=(const ElementProxy& other)
    {
        element = other.element;
        return *this;
    }

    /// Addition compound operator
    template<typename Type>
    inline ElementProxy<Type>& ElementProxy<Type>::operator+=(Type value)
    {
        element += ProcessValue<Type>(value); /// Integers converted to Fixed Point

        return *this;
    }

    /// Subtraction compound operator
    template<typename Type>
    inline ElementProxy<Type>& ElementProxy<Type>::operator-=(Type value)
    {
        element -= ProcessValue<Type>(value);  /// Integers converted to Fixed Point

        return *this;
    }

    /// Multiplication compound operator
    template<typename Type>
    inline ElementProxy<Type>& ElementProxy<Type>::operator*=(Type value)
    {
        element *= value;
        return *this;
    }

    /// Division compound operator
    template<typename Type>
    inline ElementProxy<Type>& ElementProxy<Type>::operator/=(Type value)
    {
        element /= value;
        return *this;
    }


    /// Explicit template instantiation (precompiled declaration)
    extern template class ElementProxy<float>;
    extern template class ElementProxy<double>;
    extern template class ElementProxy<int>;

} // namespace ETL::Math
