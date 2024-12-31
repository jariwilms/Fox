#pragma once

#include "stdafx.hpp"

namespace fox::gfx
{
	static fox::uint32_t calculate_mip_map(const fox::Vector2u& dimensions)
	{
		return static_cast<fox::uint32_t>(std::floor(std::log2(std::max(dimensions.x, dimensions.y)))) + fox::uint32_t{ 1u };
	}
}

