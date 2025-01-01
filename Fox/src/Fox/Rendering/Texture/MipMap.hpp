#pragma once

#include "stdafx.hpp"

namespace fox::gfx
{
	static fox::uint32_t calculate_mipmap_level(const fox::Vector1u& dimensions)
	{
		return static_cast<fox::uint32_t>(std::floor(std::log2(dimensions.x))) + fox::uint32_t{ 1u };
	}
	static fox::uint32_t calculate_mipmap_level(const fox::Vector2u& dimensions)
	{
		return static_cast<fox::uint32_t>(std::floor(std::log2(std::max(dimensions.x, dimensions.y)))) + fox::uint32_t{ 1u };
	}
	static fox::uint32_t calculate_mipmap_level(const fox::Vector3u& dimensions)
	{
		return static_cast<fox::uint32_t>(std::floor(std::log2(std::max(std::max(dimensions.x, dimensions.y), dimensions.z)))) + fox::uint32_t{ 1u };
	}
}

