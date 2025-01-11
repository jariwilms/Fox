#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Image/Image.hpp"

namespace fox::gfx::api
{
	class CubemapTexture
	{
	public:
		struct Layout
		{
			fox::Image right;
			fox::Image left;
			fox::Image top;
			fox::Image bottom;
			fox::Image front;
			fox::Image back;
		};

	protected:
		CubemapTexture() = default;
		~CubemapTexture() = default;
	};
}
