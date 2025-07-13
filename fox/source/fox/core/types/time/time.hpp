#pragma once

#include <stdafx.hpp>

import fox.core.types.fundamental;

namespace fox
{
    using delta_t      = fox::float32_t;
    using clock_t      = std::chrono::system_clock;
    using time_point_t = std::chrono::time_point<fox::clock_t>;
    using duration_t   = std::chrono::duration  <fox::delta_t>;
}
