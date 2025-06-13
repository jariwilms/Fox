#pragma once

#include <cstdint>

namespace fox
{
	using void_t     = void;

	using bool_t     = bool;
	using char_t     =          char; //Not equal to signed char apparently...
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





	template<typename T> struct fundamental{};

	template<> struct fundamental<          bool     > { using type = fox::bool_t   ; };
	template<> struct fundamental<          char     > { using type = fox::char_t   ; };
	template<> struct fundamental<   signed char     > { using type = fox::int8_t   ; };
	template<> struct fundamental< unsigned char     > { using type = fox::uint8_t  ; };
	template<> struct fundamental<   signed short    > { using type = fox::int16_t  ; };
	template<> struct fundamental< unsigned short    > { using type = fox::uint16_t ; };
	template<> struct fundamental<   signed int      > { using type = fox::int32_t  ; };
	template<> struct fundamental< unsigned int      > { using type = fox::uint32_t ; };
	template<> struct fundamental<   signed long long> { using type = fox::int64_t  ; };
	template<> struct fundamental< unsigned long long> { using type = fox::uint64_t ; };
	template<> struct fundamental<          float    > { using type = fox::float32_t; };
	template<> struct fundamental<          double   > { using type = fox::float64_t; };

	template<typename T>
	using fundamental_t = fox::fundamental<T>::type;

	template<typename T>
	static constexpr auto to_fundamental_type(T value) -> fundamental_t<T>
	{
		return value;
	}
}
