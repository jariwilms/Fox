#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
{
    class Buffer
    {
    public:
        enum class Access
        {
            Read, 
            Write, 
            ReadWrite, 

            Persistent, 
            Coherent, 
        };
    };
}
