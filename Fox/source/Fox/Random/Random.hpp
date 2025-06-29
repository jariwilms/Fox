#pragma once

#include <stdafx.hpp>

#include <fox/core/types/common/common.hpp>
#include <fox/core/types/fundamental/fundamental.hpp>
#include <fox/core/types/math/math.hpp>

namespace fox::random
{
    namespace api
    {
        inline auto device = std::random_device{};
        inline auto engine = std::mt19937{ device() };
    }



    static void seed(fox::uint32_t seed)
    {
        api::engine.seed(seed);
    }

    template<typename T>
    static auto next(fox::interval_t<T> interval = fox::interval_t<T>{ std::numeric_limits<T>::min(), std::numeric_limits<T>::max() })
    {
        if constexpr (std::is_integral_v      <T>) return std::uniform_int_distribution <T>{ interval.min, interval.max }(api::engine);
        if constexpr (std::is_floating_point_v<T>) return std::uniform_real_distribution<T>{ interval.min, interval.max }(api::engine);
    }

    template<typename T>
    static void shuffle(std::span<const T> data)
    {
        std::ranges::shuffle(data, api::engine);
    }
    template<typename T>
    static auto choice (std::span<const T> data) -> T&
    {
        if (data.empty()) throw std::range_error{ "Data is empty!" };
        
        return data[next(1u, data.size() - 1u)];
    }



    namespace distribution
    {
        template<typename T> requires (std::is_arithmetic_v<T>)
        static auto normal   (fox::interval_t<T> interval = fox::interval_t<T>{ std::numeric_limits<T>::min(), std::numeric_limits<T>::max() })
        {
            return std::normal_distribution<T>{ interval.min, interval.max }(api::engine);
        }
        template<typename T> requires (std::is_arithmetic_v<T>)
        static auto uniform  (fox::interval_t<T> interval = fox::interval_t<T>{ std::numeric_limits<T>::min(), std::numeric_limits<T>::max() })
        {
            if constexpr (std::is_integral_v      <T>) return std::uniform_int_distribution <T>{ interval.min, interval.max }(api::engine);
            if constexpr (std::is_floating_point_v<T>) return std::uniform_real_distribution<T>{ interval.min, interval.max }(api::engine);
        }
        template<typename T> requires (std::is_integral_v<T> and std::is_unsigned_v<T>)
        static auto binomial (fox::count_t trials = fox::count_t{ 1u }, fox::float64_t probability = fox::float64_t{ 0.5 })
        {
            return std::binomial_distribution<T>{ trials, probability }(api::engine);
        } 
        template<typename T> requires (std::is_integral_v<T> and std::is_unsigned_v<T>)
        static auto bernoulli(fox::float64_t probability = fox::float64_t{ 0.5 })
        {
            return std::bernoulli_distribution{ probability }(api::engine);
        }
        template<typename T> requires (std::is_integral_v<T> and std::is_unsigned_v<T>)
        static auto poisson  (fox::float64_t mean = fox::float64_t{ 1.0 })
        {
            return std::poisson_distribution{ mean }(api::engine);
        }
    }
}
