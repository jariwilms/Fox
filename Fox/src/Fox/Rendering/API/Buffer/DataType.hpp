#pragma once

#include "stdafx.hpp"

namespace fox::gfx::api
{
	enum class Type
	{
		Boolean, 
		Byte   , UnsignedByte, 
		Short  , UnsignedShort, 
		Integer, UnsignedInteger, 
		Float  , Double, 
	};

	template<typename T>
	constexpr auto map_type()
	{
		if constexpr (std::is_same_v<T, fox::int8_t>   ) return Type::Byte;
        if constexpr (std::is_same_v<T, fox::uint8_t>  ) return Type::UnsignedByte;
		if constexpr (std::is_same_v<T, fox::int16_t>  ) return Type::Short;
		if constexpr (std::is_same_v<T, fox::uint16_t> ) return Type::UnsignedShort;
		if constexpr (std::is_same_v<T, fox::int32_t>  ) return Type::Integer;
		if constexpr (std::is_same_v<T, fox::uint32_t> ) return Type::UnsignedInteger;
		if constexpr (std::is_same_v<T, fox::float32_t>) return Type::Float;
		if constexpr (std::is_same_v<T, fox::float64_t>) return Type::Double;
	}
}
