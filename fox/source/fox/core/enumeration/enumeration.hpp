#pragma once

#include <stdafx.hpp>

#include <fox/core/utility/utility.hpp>

namespace fox
{
	template<typename T> struct  enumeration_operator         { static constexpr fox::bool_t enable = fox::False; };
	template<typename T> concept enumeration_operator_concept = enumeration_operator<T>::enable;

	template<enumeration_operator_concept T>                  constexpr auto operator<=>(T first, T second) { return static_cast<T>(fox::to_underlying(first) <=> fox::to_underlying(second)); };
	template<enumeration_operator_concept T, std::integral U> constexpr auto operator+  (T first, U second) { return static_cast<T>(fox::to_underlying(first)  +                     second ); };
	template<enumeration_operator_concept T, std::integral U> constexpr auto operator-  (T first, U second) { return static_cast<T>(fox::to_underlying(first)  -                     second ); };
}
