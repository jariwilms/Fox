export module fox.core.types.math.linear_algebra.vector;

import std;
import fox.core.types.fundamental;
import vendor.glm;

export namespace fox
{
	template<typename T, fox::uint32_t N>
	using vector_t = glm::vec<N, T, glm::packed_highp>;
	template<typename T = fox::float32_t, fox::uint32_t N = 4u>
	class vector
	{
	public:
		static inline constexpr auto zero    = fox::vector_t<T, N>{ T{ 0 } };
		static inline constexpr auto one     = fox::vector_t<T, N>{ T{ 1 } };

		static inline constexpr auto right   = fox::vector_t<T, N>{ fox::vector_t<T, N>{ T{ 1 }, T{ 0 }, T{  0 }, T{ 0 } } };
		static inline constexpr auto up      = fox::vector_t<T, N>{ fox::vector_t<T, N>{ T{ 0 }, T{ 1 }, T{  0 }, T{ 0 } } };
		static inline constexpr auto forward = fox::vector_t<T, N>{ fox::vector_t<T, N>{ T{ 0 }, T{ 0 }, T{ -1 }, T{ 0 } } };
	};

	using vector1i = fox::vector_t<fox::int32_t,   1u>;
	using vector2i = fox::vector_t<fox::int32_t,   2u>;
	using vector3i = fox::vector_t<fox::int32_t,   3u>;
	using vector4i = fox::vector_t<fox::int32_t,   4u>;

	using vector1u = fox::vector_t<fox::uint32_t,  1u>;
	using vector2u = fox::vector_t<fox::uint32_t,  2u>;
	using vector3u = fox::vector_t<fox::uint32_t,  3u>;
	using vector4u = fox::vector_t<fox::uint32_t,  4u>;

	using vector1f = fox::vector_t<fox::float32_t, 1u>;
	using vector2f = fox::vector_t<fox::float32_t, 2u>;
	using vector3f = fox::vector_t<fox::float32_t, 3u>;
	using vector4f = fox::vector_t<fox::float32_t, 4u>;

	using vector1d = fox::vector_t<fox::float64_t, 1u>;
	using vector2d = fox::vector_t<fox::float64_t, 2u>;
	using vector3d = fox::vector_t<fox::float64_t, 3u>;
	using vector4d = fox::vector_t<fox::float64_t, 4u>;
}
