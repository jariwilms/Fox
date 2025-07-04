#pragma once

#include <glm/gtx/texture.hpp>

#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>

namespace fox::math
{
    template<std::integral T, fox::uint32_t N>
    static constexpr auto mipmap_levels(const fox::Vector<T, N>& vector) -> fox::uint32_t
    {
        return static_cast<fox::uint32_t>(glm::levels(vector));
    }
}
