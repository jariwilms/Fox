#pragma once

#include "stdafx.hpp"

namespace hlx
{
    class Time
    {
    public:
        using DeltaTime = float;
        using Clock     = std::chrono::system_clock;
        using Duration  = std::chrono::duration<DeltaTime>;
        using TimePoint = std::chrono::time_point<Clock>;

        static void reset()
        {
            s_t0 = Clock::now();
            s_t1 = Clock::now();
        }

        static void advance()
        {
            s_t1 = Clock::now();
            s_deltaTime = std::chrono::duration_cast<Duration>(s_t1 - s_t0).count();
            s_t0 = s_t1;
        }

        static const Clock::time_point now()
        {
            return Clock::now();
        }
        static const std::chrono::seconds epoch()
        {
            const auto time = std::chrono::system_clock::now().time_since_epoch();
            return std::chrono::duration_cast<std::chrono::seconds>(time);
        }
        static const DeltaTime& delta()
        {
            return s_deltaTime;
        }

    private:
        static inline TimePoint s_t0{};
        static inline TimePoint s_t1{};
        static inline DeltaTime s_deltaTime{};
    };
}
