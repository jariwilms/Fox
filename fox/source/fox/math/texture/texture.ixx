export module fox.math.texture;

import std;
import fox.core.types;
import vendor.glm;

export namespace fox::math
{
    template<std::integral T, fox::uint32_t N>
    constexpr auto mipmap_levels(const fox::vector_t<T, N>& vector) -> T
    {
        return glm::levels(vector);
    }
}
