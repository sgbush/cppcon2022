


#pragma once

#include <memory>
#include <exception>

extern void Panic();



// the old way
bool CanFailSpectacularly(std::shared_ptr<int> param)
{
    if ( *param < 0 )
    {
        #if defined USES_EXCEPTIONS
            throw std::invalid_argument("Parameter cannot be negative");
        #else
            Panic();
        #endif
    }
}





// better way
bool CanFailSpectacularly(std::shared_ptr<int> param)
{
    if ( *param < 0 )
    {
        if constexpr ( __cpp_exceptions )
        {
            throw std::invalid_argument("Parameter cannot be negative");
        }
        else
        {
            Panic();
        }
    }
}



