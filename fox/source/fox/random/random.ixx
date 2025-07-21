export module fox.random;

import std;
import fox.core.types;

auto device = std::random_device{};
auto engine = std::mt19937{ device() };

export namespace fox::random
{
    namespace distribution
    {
        template<typename T> requires (std::is_arithmetic_v<T>)
        auto normal   (fox::interval_t<T> interval = {})
        {
            return std::normal_distribution<T>{ interval.min, interval.max }(::engine);
        }
        template<typename T> requires (std::is_arithmetic_v<T>)
        auto uniform  (fox::interval_t<T> interval = {})
        {
            if constexpr (std::is_integral_v      <T>) return std::uniform_int_distribution <T>{ interval.min, interval.max }(::engine);
            if constexpr (std::is_floating_point_v<T>) return std::uniform_real_distribution<T>{ interval.min, interval.max }(::engine);
        }
        template<typename T> requires (std::is_integral_v<T> && std::is_unsigned_v<T>)
        auto binomial (fox::count_t trials = 1u, fox::float64_t probability = 0.5)
        {
            return std::binomial_distribution<T>{ trials, probability }(::engine);
        } 
        template<typename T> requires (std::is_integral_v<T> && std::is_unsigned_v<T>)
        auto bernoulli(fox::float64_t probability = 0.5)
        {
            return std::bernoulli_distribution{ probability }(::engine);
        }
        template<typename T> requires (std::is_integral_v<T> && std::is_unsigned_v<T>)
        auto poisson  (fox::float64_t mean = 1.0)
        {
            return std::poisson_distribution{ mean }(::engine);
        }
    }

    void seed   (fox::uint32_t seed)
    {
        ::engine.seed(seed);
    }
    template<typename T>
    auto next   (fox::interval_t<T> interval = {})
    {
        return distribution::uniform<T>(interval);
    }
    template<typename T>
    void shuffle(std::span<const T> data)
    {
        std::ranges::shuffle(data, ::engine);
    }
    template<typename T>
    auto choice (std::span<const T> data) -> T&
    {
        if (data.empty()) throw std::range_error{ "Data is empty!" };
        
        return data[next(0u, data.size() - 1u)];
    }
}
