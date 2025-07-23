export module fox.core.types.domain;

import std;
import fox.core.types.common;
import fox.core.types.fundamental;
import fox.core.types.math.linear_algebra.vector;

export namespace fox
{
	template<typename T>
	struct interval
	{
		interval(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
			: min{ min }, max{ max } {}

		auto operator==(const interval&) const -> fox::bool_t = default;

		T min;
		T max;
	};
	struct range
	{
		range(fox::count_t count = {}, fox::index_t index = {})
			: count{ count }, index{ index } {}

		auto operator==(const range&) const -> fox::bool_t = default;

		fox::count_t count;
		fox::index_t index;
	};
	struct byterange
	{
		byterange(fox::size_t size = {}, fox::offset_t offset = {})
			: size{ size }, offset{ offset } {}

		auto operator==(const byterange&) const -> fox::bool_t = default;

		fox::size_t   size;
		fox::offset_t offset;
	};
	template<typename T, fox::uint32_t N>
	struct region
	{
		region(const fox::vector_t<T, N>& extent = {}, const fox::vector<T, N>& origin = {})
			: extent{ extent }, origin{ origin } {}

		auto operator==(const region&) const -> fox::bool_t = default;

		fox::vector_t<T, N> extent;
		fox::vector_t<T, N> origin;
	};

	using length_t      = fox::region<fox::uint32_t, 1u>;
	using area_t        = fox::region<fox::uint32_t, 2u>;
	using volume_t      = fox::region<fox::uint32_t, 3u>;
	using hypervolume_t = fox::region<fox::uint32_t, 4u>;
}
