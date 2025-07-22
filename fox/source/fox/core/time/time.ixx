export module fox.core.time;

import std;
import fox.core.types;

       namespace fox::time
{
    auto now_    = fox::time_point_t{};
    auto before_ = fox::time_point_t{};
    auto epoch_  = fox::time_point_t{};
    auto delta_  = fox::delta_t{};
}
export namespace fox::time
{
    void update()
    {
        time::before_ = std::exchange(time::now_, fox::clock_t::now());
        time::delta_  = std::chrono::duration_cast<fox::duration_t>(time::now_ - time::before_).count();
    }
    void reset ()
    {
        time::epoch_  = fox::clock_t::now();
        time::now_    = fox::clock_t::now();
        time::before_ = fox::clock_t::now();
        time::delta_  = fox::delta_t{};
    }

    auto delta      () -> fox::delta_t
    {
        return time::delta_;
    }
    auto since_epoch() -> fox::delta_t
    {
        return std::chrono::duration_cast<fox::duration_t>(fox::clock_t::now() - time::epoch_).count();
    }
}
