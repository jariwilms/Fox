#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/GraphicsAPI.hpp"
#include "Fox/Rendering/Buffer/Buffer.hpp"

namespace fox::gfx::imp
{
    inline namespace api
    {
        template<gfx::api::GraphicsAPI, gfx::api::Buffer::Type, gfx::api::Buffer::Access, typename>
        class GBuffer;
    }
}
