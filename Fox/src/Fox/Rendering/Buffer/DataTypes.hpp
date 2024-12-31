#pragma once

namespace fox::gfx
{
	enum class DataType : fox::uint32_t
	{
		Boolean,
		Byte,
		UnsignedByte,
		Short,
		UnsignedShort,
		Integer,
		UnsignedInteger,
		Float,
		Double,
	};

	template<typename T>
	constexpr DataType map_data_type()
	{
		if constexpr (std::is_same_v<T, fox::int8_t>)    return DataType::Byte;
        if constexpr (std::is_same_v<T, fox::uint8_t>)   return DataType::UnsignedByte;
		if constexpr (std::is_same_v<T, fox::int16_t>)   return DataType::Short;
		if constexpr (std::is_same_v<T, fox::uint16_t>)  return DataType::UnsignedShort;
		if constexpr (std::is_same_v<T, fox::int32_t>)   return DataType::Integer;
		if constexpr (std::is_same_v<T, fox::uint32_t>)  return DataType::UnsignedInteger;
		if constexpr (std::is_same_v<T, fox::float32_t>) return DataType::Float;
		if constexpr (std::is_same_v<T, fox::float64_t>) return DataType::Double;
	}
}
