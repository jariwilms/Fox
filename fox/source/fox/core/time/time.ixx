export module fox.core.time;

import std;

import fox.core.types;

fox::time_point_t now;
fox::time_point_t before;
fox::time_point_t epoch;
fox::delta_t      delta;

export namespace fox::time
{
    void update()
    {
        ::before = std::exchange(::now, fox::clock_t::now());
        ::delta  = std::chrono::duration_cast<fox::duration_t>(::now - ::before).count();
    }
    void reset ()
    {
        ::epoch  = fox::clock_t::now();
        ::now    = fox::clock_t::now();
        ::before = fox::clock_t::now();
        ::delta  = fox::delta_t{};
    }

    auto delta      () -> fox::delta_t
    {
        return ::delta;
    }
    auto since_epoch() -> fox::delta_t
    {
        return std::chrono::duration_cast<fox::duration_t>(fox::clock_t::now() - ::epoch).count();
    }
}
