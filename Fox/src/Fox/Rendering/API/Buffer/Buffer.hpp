#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
{
    class Buffer
    {
    public:
        enum class Type
        {
            Vertex, 
            Index, 
            Uniform, 

            //SSBO, 
            //TransformFeedback, 
            
            //DrawIndirect?, 
            //PixelPack?, 
            //PixelUnpack?, 
            //Texture?, 
        };
        enum class Access
        {
            Read, 
            Write, 
            ReadWrite, 

            ReadPersistent, 
            WritePersistent, 
            ReadWritePersistent, 

            ReadCoherent, 
            WriteCoherent, 
            ReadWriteCoherent, 

            //InvalidateRange, 
            //InvalidateBuffer, 
            //FlushExplicit, 
            //Unsynchronized, 
        };
    };
}
