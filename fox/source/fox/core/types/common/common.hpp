#pragma once

#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/linear_algebra/vector.hpp>

namespace fox
{
	using byte_t   = fox::uint8_t;
	using size_t   = fox::uint64_t; //Number of bytes
	using offset_t = fox::uint64_t; //Number of bytes offset
	using count_t  = fox::uint32_t; //Number of elements
	using index_t  = fox::uint32_t; //Number of elements offset



	template<typename T>
	struct interval_t
	{
		interval_t(T min = {}, T max = {})
			: min{ min }, max{ max } {}

		auto operator==(const interval_t&) const -> fox::bool_t = default;

		T min;
		T max;
	};
	
	struct     range_t
	{
		range_t(fox::count_t count = {}, fox::index_t index = {})
			: count{ count }, index{ index } {}

		auto operator==(const range_t&) const -> fox::bool_t = default;

		fox::count_t count;
		fox::index_t index;
	};
	struct byterange_t
	{
		byterange_t(fox::size_t size = {}, fox::offset_t offset = {})
			: size{ size }, offset{ offset } {}

		auto operator==(const byterange_t&) const -> fox::bool_t = default;

		fox::size_t   size;
		fox::offset_t offset;
	};
	
	template<typename T, fox::uint32_t N>
	struct region_t
	{
		region_t(const fox::Vector<T, N>& extent = {}, const fox::Vector<T, N>& origin = {})
			: extent{ extent }, origin{ origin } {}

		auto operator==(const region_t&) const -> fox::bool_t = default;

		fox::Vector<T, N> extent;
		fox::Vector<T, N> origin;
	};



	using length_t      = fox::region_t<fox::uint32_t, 1u>;
	using area_t        = fox::region_t<fox::uint32_t, 2u>;
	using volume_t      = fox::region_t<fox::uint32_t, 3u>;
	using hypervolume_t = fox::region_t<fox::uint32_t, 4u>;
}