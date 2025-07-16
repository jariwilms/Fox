export module fox.core.time;

import std;

import fox.core.types;

namespace api
{
    fox::time_point_t epoch {};
    fox::time_point_t now   {};
    fox::time_point_t before{};
    fox::delta_t      delta {};
}
export namespace fox::time
{
    auto delta      () -> fox::delta_t
    {
        return api::delta;
    }
    auto since_epoch() -> fox::delta_t
    {
        return std::chrono::duration_cast<fox::duration_t>(fox::clock_t::now() - api::epoch).count();
    }
    
    void update()
    {
        api::before = std::exchange(api::now, fox::clock_t::now());
        api::delta  = std::chrono::duration_cast<fox::duration_t>(api::now - api::before).count();
    }
    void reset ()
    {
        api::epoch  = fox::clock_t::now();
        api::now    = fox::clock_t::now();
        api::before = fox::clock_t::now();
        api::delta  = fox::delta_t{};
    }
}
