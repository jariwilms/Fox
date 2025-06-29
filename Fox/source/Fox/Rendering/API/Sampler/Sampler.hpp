#pragma once

namespace fox::gfx::api
{
	class Sampler
	{
	public:
        enum class Parameter
        {
            CompareMode, 
            CompareFunc, 

            MinificationFilter, 
            MagnificationFilter, 
            
            WrappingS, 
            WrappingT, 
            WrappingR, 
            
            BorderColor, 
            
            MinimumLOD, 
            MaximumLOD, 
            LODBias, 
        };
	};
}
