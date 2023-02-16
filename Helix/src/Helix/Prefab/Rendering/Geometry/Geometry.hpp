#pragma once

#include "stdafx.hpp"

#include "Quad.hpp"
#include "Cube.hpp"

namespace hlx
{
    struct Geometry
    {
    public:
        static void init()
        {
            quad = std::make_shared<Quad>();
            cube = std::make_shared<Cube>();
        }

        static inline std::shared_ptr<Quad> quad;
        static inline std::shared_ptr<Cube> cube;
    };
}
