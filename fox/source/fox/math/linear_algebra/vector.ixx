export module fox.math.linear_algebra.vector;

import std;
import fox.core.types;
import vendor.glm;

export namespace fox::math
{
    template<typename T, fox::uint32_t N>
    constexpr auto dot      (const fox::Vector<T, N>& first, const fox::Vector<T, N>& second) -> fox::fundamental_t<T>
    {
        return glm::dot(first, second);
    }
    template<typename T, fox::uint32_t N>
    constexpr auto normalize(const fox::Vector<T, N>& value) -> fox::Vector<T, N>
    {
        return glm::normalize(value);
    }
}
