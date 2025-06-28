#pragma once

#include <glm/gtx/texture.hpp>

#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/math/linear_algebra/vector.hpp>

namespace fox::math
{
    static constexpr auto calculate_mipmap_levels(auto const& vector)
    {
        return static_cast<fox::uint32_t>(glm::levels(vector));
    }
}
