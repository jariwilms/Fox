#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
{
	class Sampler
	{
	public:
        enum class Parameter
        {
            TextureWrapS, 
            TextureWrapT, 
            TextureWrapR, 
            TextureMinFilter, 
            TextureMagFilter, 
            TextureBorderColor, 
            TextureMinLod, 
            TextureMaxLod, 
            TextureLodBias, 
            TextureCompareMode, 
            TextureCompareFunc, 
        };

	protected:
		Sampler() = default;
		Sampler(Sampler&& other) = default;
		~Sampler() = default;

		Sampler& operator=(Sampler&& other) = default;
	};
}
