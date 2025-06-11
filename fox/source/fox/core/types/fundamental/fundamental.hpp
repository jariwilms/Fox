#pragma once

#include <cstdint>

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

	enum : fox::bool_t
	{
		False = false,
		True  = true,
	};
}
