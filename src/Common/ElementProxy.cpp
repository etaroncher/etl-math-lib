///----------------------------------------------------------------------------
/// ETL - MathLib
/// ElementProxy.cpp
///---------------------------------------------------------------------------- 

#include "MathLib/Common/ElementProxy.h"

namespace ETL::Math
{

    ///------------------------------------------------------------------------------------------
    /// Explicit template instantiations (precompiled declaration)

    template class ElementProxy<float>;
    template class ElementProxy<double>;
    template class ElementProxy<int>;

} /// namespace ETL::Math