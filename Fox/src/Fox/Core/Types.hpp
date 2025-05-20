#pragma once

#include <cstdint>
#include <bitset>

#include <glm/glm.hpp>

namespace fox
{
	using bool_t     = bool;
	using char_t     = char;          //Not equal to signed char apparently...
	using uchar_t    = unsigned char;
	using schar_t    = signed char;

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
	using count_t    = fox::uint32_t; //Amount of elements
	using index_t    = fox::uint32_t; //Amount of elements offset

	using uuid_t     = std::bitset<128u>;



	template<typename T, fox::uint32_t N> using Vector     = glm::vec<N, T, glm::packed_highp>;
    template<typename T, fox::uint32_t N> using Matrix     = glm::mat<N, N, T>;
                                          using Quaternion = glm::quat;

	using Vector1i   = fox::Vector<fox::int32_t  , 1>;
	using Vector2i   = fox::Vector<fox::int32_t  , 2>;
	using Vector3i   = fox::Vector<fox::int32_t  , 3>;
	using Vector4i   = fox::Vector<fox::int32_t  , 4>;
	using Vector1u   = fox::Vector<fox::uint32_t , 1>;
	using Vector2u   = fox::Vector<fox::uint32_t , 2>;
	using Vector3u   = fox::Vector<fox::uint32_t , 3>;
	using Vector4u   = fox::Vector<fox::uint32_t , 4>;
	using Vector1f   = fox::Vector<fox::float32_t, 1>;
	using Vector2f   = fox::Vector<fox::float32_t, 2>;
	using Vector3f   = fox::Vector<fox::float32_t, 3>;
	using Vector4f   = fox::Vector<fox::float32_t, 4>;
	using Matrix2f   = fox::Matrix<fox::float32_t, 2>;
	using Matrix3f   = fox::Matrix<fox::float32_t, 3>;
	using Matrix4f   = fox::Matrix<fox::float32_t, 4>;

	enum : fox::bool_t
	{
		False = false, 
		True  = true, 
	};

	struct     range_t
	{
		explicit range_t(fox::count_t count, fox::index_t index = {})
			: count{ count }, index{ index } {}

		fox::count_t count{};
		fox::index_t index{};
	};
	struct byterange_t
	{
		explicit byterange_t(fox::size_t size, fox::offset_t offset = {})
			: size{ size }, offset{ offset } {}

		fox::size_t   size{};
		fox::offset_t offset{};
	};
}
