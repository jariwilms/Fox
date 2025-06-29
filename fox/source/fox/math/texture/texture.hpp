#pragma once

#include <glm/gtx/texture.hpp>

#include <fox/core/types/fundamental/fundamental.hpp>

namespace fox::math
{
    static constexpr auto mipmap_levels(const auto& vector)
    {
        return static_cast<fox::uint32_t>(glm::levels(vector));
    }
}
