#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/GraphicsAPI.hpp"
#include "Fox/Rendering/Buffer/VertexArray.hpp"

namespace fox::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI>
        class GVertexArray;
    }
}
