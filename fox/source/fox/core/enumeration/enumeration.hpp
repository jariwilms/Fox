import std;

import fox.core.types.fundamental;

namespace fox
{
	template<typename T> struct  enumeration_operator{ static constexpr auto enable = fox::bool_t{ fox::False }; };
	template<typename T> concept enumeration_operator_c = enumeration_operator<T>::enable;

	template<enumeration_operator_c T                 > constexpr auto operator<=>(T first, T second) { return static_cast<T>(std::to_underlying(first) <=> std::to_underlying(second)); };
	template<enumeration_operator_c T, std::integral U> constexpr auto operator+  (T first, U second) { return static_cast<T>(std::to_underlying(first)  +                     second ); };
	template<enumeration_operator_c T, std::integral U> constexpr auto operator-  (T first, U second) { return static_cast<T>(std::to_underlying(first)  -                     second ); };
}
