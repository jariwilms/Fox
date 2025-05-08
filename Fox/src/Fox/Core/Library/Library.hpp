#pragma once

namespace fox
{
    template <typename T>
    static constexpr auto to_underlying(T value) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(value);
    }


}
