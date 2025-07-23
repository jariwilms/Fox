export module fox.random;

import std;
import fox.core.types;


       namespace fox::random
{
    auto device_ = std::random_device{};
    auto engine_ = std::mt19937{ device_() };
}
export namespace fox::random
{
    namespace distribution
    {
        template<typename T>
        auto normal   (fox::interval<T> interval = {})
        {
            return std::normal_distribution<T>{ interval.min, interval.max }(random::engine_);
        }
        template<typename T>
        auto uniform  (fox::interval<T> interval = {})
        {
            if constexpr (std::is_integral_v      <T>) return std::uniform_int_distribution <T>{ interval.min, interval.max }(random::engine_);
            if constexpr (std::is_floating_point_v<T>) return std::uniform_real_distribution<T>{ interval.min, interval.max }(random::engine_);
        }
        template<std::unsigned_integral T>
        auto binomial (fox::count_t trials = 1u, fox::float64_t probability = 0.5)
        {
            return std::binomial_distribution<T>{ trials, probability }(random::engine_);
        } 
        template<std::unsigned_integral T>
        auto bernoulli(fox::float64_t probability = 0.5)
        {
            return std::bernoulli_distribution{ probability }(random::engine_);
        }
        template<std::unsigned_integral T>
        auto poisson  (fox::float64_t mean = 1.0)
        {
            return std::poisson_distribution{ mean }(random::engine_);
        }
    }

    void seed   (fox::uint32_t seed)
    {
        random::engine_.seed(seed);
    }
    template<typename T>
    auto next   (fox::interval<T> interval = {})
    {
        return distribution::uniform<T>(interval);
    }
    template<typename T>
    void shuffle(std::span<const T> data)
    {
        std::ranges::shuffle(data, random::engine_);
    }
    template<typename T>
    auto choice (std::span<const T> data) -> T&
    {
        if (data.empty()) throw std::range_error{ "Data is empty!" };
        return data[next(0u, data.size() - 1u)];
    }
}
