#pragma once

#include <stdafx.hpp>

#include <fox/core/types/time/time.hpp>

namespace fox::time
{
    namespace api
    {
        inline fox::time_point_t epoch {};
        inline fox::time_point_t now   {};
        inline fox::time_point_t before{};
        inline fox::delta_t      delta {};
    }

    static void update()
    {
        api::before = std::exchange(api::now, fox::clock_t::now());
        api::delta  = std::chrono::duration_cast<fox::duration_t>(api::now - api::before).count();
    }
    static void reset ()
    {
        api::epoch  = fox::clock_t::now();
        api::now    = fox::clock_t::now();
        api::before = fox::clock_t::now();
        api::delta  = fox::delta_t{};
    }

    static auto since_epoch() -> fox::delta_t
    {
        auto const& now   = fox::clock_t::now();
        auto const& delta = std::chrono::duration_cast<fox::duration_t>(now - api::epoch).count();

        return delta;
    }
    static auto delta      () -> fox::delta_t
    {
        return api::delta;
    }
}
