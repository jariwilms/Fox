#pragma once

#include "stdafx.hpp"

namespace hlx
{
    class Time
    {
    public:
        using DeltaTime = float;
        using Clock     = std::chrono::steady_clock;
        using Duration  = std::chrono::duration<float>;
        using TimePoint = std::chrono::time_point<Clock>;

        static void init()
        {

        }
        
        static void reset()
        {
            s_t0 = Clock::now();
            s_t1 = Clock::now();
        }

        static void tick()
        {
            s_t1 = Clock::now();
            s_deltaTime = std::chrono::duration_cast<Duration>(s_t1 - s_t0).count();
            s_t0 = s_t1;
        }

        static const DeltaTime& delta()
        {
            return s_deltaTime;
        }

    private:
        static inline Clock s_clock{};
        static inline TimePoint s_t0{};
        static inline TimePoint s_t1{};

        static inline DeltaTime s_deltaTime{};
    };
}
