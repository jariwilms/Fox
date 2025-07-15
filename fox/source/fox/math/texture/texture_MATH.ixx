export module fox.math.texture;

import std;

import fox.core.types.fundamental;
import fox.core.types.math;

import vendor.glm;

export namespace fox::math
{
    template<std::integral T, fox::uint32_t N>
    constexpr auto mipmap_levels(const fox::Vector<T, N>& vector) -> fox::uint32_t
    {
        return static_cast<fox::uint32_t>(glm::levels(vector));
    }
}
