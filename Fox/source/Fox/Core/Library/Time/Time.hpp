#pragma once

#include "stdafx.hpp"

namespace fox
{
    class Time
    {
    public:
        using delta_t     = fox::float32_t;
        using clock_t     = std::chrono::system_clock;
        using timepoint_t = std::chrono::time_point<clock_t>;
        using duration_t  = std::chrono::duration<delta_t>;

        static void    update()
        {
            s_t0    = std::exchange(s_t1, clock_t::now());
            s_delta = std::chrono::duration_cast<duration_t>(s_t1 - s_t0).count();
        }
        static void    reset()
        {
            s_epoch = clock_t::now();

            s_t0    = clock_t::now();
            s_t1    = clock_t::now();
        }

        static delta_t since_epoch()
        {
            const auto& now   = clock_t::now();
            const auto& delta = std::chrono::duration_cast<duration_t>(now - s_epoch).count();

            return delta;
        }
        static delta_t delta()
        {
            return s_delta;
        }

    private:
        static inline timepoint_t s_epoch{};

        static inline timepoint_t s_t0{};
        static inline timepoint_t s_t1{};
        static inline delta_t     s_delta{};
    };
}
