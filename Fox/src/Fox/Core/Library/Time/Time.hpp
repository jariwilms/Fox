#pragma once

#include "stdafx.hpp"

namespace fox
{
    class Time
    {
    public:
        using DeltaTime  = fox::float32_t;
        using Clock      = std::chrono::system_clock;
        using TimePoint  = std::chrono::time_point<Clock>;
        using Duration   = std::chrono::duration<DeltaTime>;

        static void reset()
        {
            s_t0 = Clock::now();
            s_t1 = Clock::now();
        }

        static void advance()
        {
            s_t1 = Clock::now();
            s_delta = std::chrono::duration_cast<Duration>(s_t1 - s_t0).count();
            s_t0 = s_t1;
        }

        static const Clock::time_point now()
        {
            return Clock::now();
        }
        static const std::chrono::seconds epoch()
        {
            const auto& time = now().time_since_epoch();
            return std::chrono::duration_cast<std::chrono::seconds>(time);
        }
        static const DeltaTime& delta()
        {
            return s_delta;
        }

    private:
        static inline TimePoint s_t0{};                                        //Previous TimePoint
        static inline TimePoint s_t1{};                                        //Current  TimePoint
        static inline DeltaTime s_delta{};                                     //DeltaTime as difference of (t1, t0)
    };
}
