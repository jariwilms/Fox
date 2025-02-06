#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
{
	class Sampler
	{
	public:
        enum class Parameter
        {
            WrappingS, 
            WrappingT, 
            WrappingR, 
            MinificationFilter, 
            MagnificationFilter, 
            BorderColor, 
            MinimumLod, 
            MaximumLod, 
            LodBias, 
            CompareMode, 
            CompareFunc, 
        };

	protected:
		Sampler() = default;
	};
}
