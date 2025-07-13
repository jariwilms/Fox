#pragma once

#include <fox/core/types/math/linear_algebra/vector.hpp>

import fox.core.types.fundamental;
import vendor.glm;

namespace fox::math
{
    template<std::integral T, fox::uint32_t N>
    inline constexpr auto mipmap_levels(const fox::Vector<T, N>& vector) -> fox::uint32_t
    {
        return static_cast<fox::uint32_t>(glm::levels(vector));
    }
}
