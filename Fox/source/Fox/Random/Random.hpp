#pragma once

#include "stdafx.hpp"

namespace fox::random::api
{
    inline auto device = std::random_device{};
    inline auto engine = std::mt19937{ device() };
}
namespace fox::random
{
    static void seed(fox::uint32_t seed)
    {
        api::engine.seed(seed);
    }

    template<typename T>
    static auto next(std::optional<T> min = std::nullopt, std::optional<T> max = std::nullopt)
    {
        if constexpr (std::is_integral_v<T>)
        {
            auto distribution = std::uniform_int_distribution<T>
                { 
                    min.value_or(std::numeric_limits<T>::min()), 
                    max.value_or(std::numeric_limits<T>::max()), 
                };

            return distribution(api::engine);
        }
        if constexpr (std::is_floating_point_v<T>)
        {
            auto distribution = std::uniform_real_distribution<T>
                { 
                    min.value_or(std::numeric_limits<T>::min()), 
                    max.value_or(std::numeric_limits<T>::max()), 
                };

            return distribution(api::engine);
        }
    }

    template<typename T>
    static void shuffle(std::span<const T> data)
    {
        std::ranges::shuffle(data, api::engine);
    }
}
