#pragma once

#include <stdafx.hpp>

import fox.rendering.mesh;

namespace fox::gfx::geometry
{
    void init();

    inline std::shared_ptr<gfx::Mesh> plane;
    inline std::shared_ptr<gfx::Mesh> cube;
    inline std::shared_ptr<gfx::Mesh> sphere;
}
