#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/GraphicsAPI/OpenGL/Types.hpp"

namespace fox::gfx::api::gl
{
    template<typename T>
    concept ValidBitmaskTypeConcept = std::is_same_v<std::underlying_type_t<T>, gl::bitfield_t>;

    template<typename T> requires ValidBitmaskTypeConcept<T>
    struct BitmaskTraits { static constexpr bool enable_bitmask_operations = false; };



    template<typename T>
    concept ValidBitmaskEnumClassConcept = std::is_enum_v<T> && BitmaskTraits<T>::enable_bitmask_operations;

    template<ValidBitmaskEnumClassConcept T> constexpr T  operator| (T  first, T second) { return static_cast<T>( std::to_underlying(first) | std::to_underlying(second)); }
    template<ValidBitmaskEnumClassConcept T> constexpr T  operator& (T  first, T second) { return static_cast<T>( std::to_underlying(first) & std::to_underlying(second)); }
    template<ValidBitmaskEnumClassConcept T> constexpr T  operator^ (T  first, T second) { return static_cast<T>( std::to_underlying(first) ^ std::to_underlying(second)); }
    template<ValidBitmaskEnumClassConcept T> constexpr T  operator~ (T  value)           { return static_cast<T>(~std::to_underlying(value)); }
    template<ValidBitmaskEnumClassConcept T> constexpr T& operator|=(T& first, T second) { return first = first | second; }
    template<ValidBitmaskEnumClassConcept T> constexpr T& operator&=(T& first, T second) { return first = first & second; }
    template<ValidBitmaskEnumClassConcept T> constexpr T& operator^=(T& first, T second) { return first = first ^ second; }
}
