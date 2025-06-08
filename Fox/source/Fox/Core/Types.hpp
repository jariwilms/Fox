#pragma once

#include <cstdint>
#include <bitset>

#include <glm/glm.hpp>
#include "glm/gtx/texture.hpp"

namespace fox
{
	using bool_t     = bool;
	using char_t     = char;          //Not equal to signed char apparently...
	using uchar_t    = unsigned char;
	using schar_t    =   signed char;
	
	using int8_t     = std::int8_t;
	using uint8_t    = std::uint8_t;
	using int16_t    = std::int16_t;
	using uint16_t   = std::uint16_t;
	using int32_t    = std::int32_t;
	using uint32_t   = std::uint32_t;
	using int64_t    = std::int64_t;
	using uint64_t   = std::uint64_t;
	using float32_t  = float;         //Thanks Microsoft...
	using float64_t  = double;		  //

	using byte_t     = fox::uint8_t;
	using size_t     = fox::uint64_t; //Size in bytes
	using offset_t   = fox::uint64_t; //Offset in bytes
	using count_t    = fox::uint32_t; //Number of elements
	using index_t    = fox::uint32_t; //Number of elements offset

	using uuid_t     = std::bitset<128u>;

	enum class id_t      : fox::uint32_t {};
	enum class binding_t : fox::index_t {};

	enum : fox::bool_t
	{
		False = false,
		True  = true,
	};




	template<typename T, fox::uint32_t N> using Vector     = glm::vec<N, T, glm::packed_highp>;
    template<typename T, fox::uint32_t N> using Matrix     = glm::mat<N, N, T>;
                                          using Quaternion = glm::quat;

	using Vector1i   = fox::Vector<fox::int32_t,   1u>;
	using Vector2i   = fox::Vector<fox::int32_t,   2u>;
	using Vector3i   = fox::Vector<fox::int32_t,   3u>;
	using Vector4i   = fox::Vector<fox::int32_t,   4u>;

	using Vector1u   = fox::Vector<fox::uint32_t,  1u>;
	using Vector2u   = fox::Vector<fox::uint32_t,  2u>;
	using Vector3u   = fox::Vector<fox::uint32_t,  3u>;
	using Vector4u   = fox::Vector<fox::uint32_t,  4u>;
	
	using Vector1f   = fox::Vector<fox::float32_t, 1u>;
	using Vector2f   = fox::Vector<fox::float32_t, 2u>;
	using Vector3f   = fox::Vector<fox::float32_t, 3u>;
	using Vector4f   = fox::Vector<fox::float32_t, 4u>;
	
	using Matrix2f   = fox::Matrix<fox::float32_t, 2u>;
	using Matrix3f   = fox::Matrix<fox::float32_t, 3u>;
	using Matrix4f   = fox::Matrix<fox::float32_t, 4u>;



	template<typename T, fox::uint32_t N>
    struct region_t
    {
        region_t(const fox::Vector<T, N>& extent = {}, const fox::Vector<T, N>& origin = {})
            : extent{ extent }, origin{ origin } {}

        bool operator==(const region_t&) const = default;

        fox::Vector<T, N> extent{};
        fox::Vector<T, N> origin{};
    };
    struct range_t
    {
        range_t(fox::count_t count = {}, fox::index_t index = {})
            : count{ count }, index{ index } {}

        bool operator==(const range_t&) const = default;

        fox::count_t count{};
        fox::index_t index{};
    };
    struct byterange_t
    {
        byterange_t(fox::size_t size = {}, fox::offset_t offset = {})
            : size{ size }, offset{ offset } {}

        bool operator==(const byterange_t&) const = default;

        fox::size_t   size{};
        fox::offset_t offset{};
    };

    using length_t = fox::region_t<fox::uint32_t, 1u>;
    using area_t   = fox::region_t<fox::uint32_t, 2u>;
    using volume_t = fox::region_t<fox::uint32_t, 3u>;
}
