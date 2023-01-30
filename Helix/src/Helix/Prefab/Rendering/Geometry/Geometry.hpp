#pragma once

#include "stdafx.hpp"

#include "Quad.hpp"

namespace hlx
{
    struct Geometry
    {
    public:
        static void init()
        {
            quad = std::make_shared<Quad>();
        }

        static inline std::shared_ptr<Quad> quad;
    };
}
