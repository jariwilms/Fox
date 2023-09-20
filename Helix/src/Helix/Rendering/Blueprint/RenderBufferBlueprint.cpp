#include "stdafx.hpp"

#include "RenderBufferBlueprint.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx
{
    std::shared_ptr<RenderBuffer> RenderBufferBlueprint::build(const Vector2u& dimensions) const
    {
        return gfx::create_renderbuffer(type, layout, dimensions);
    }
    std::shared_ptr<RenderBuffer> RenderBufferBlueprint::build_ms(const Vector2u& dimensions, unsigned int samples) const
    {
        return gfx::create_renderbuffer_multisample(type, layout, dimensions, samples);
    }
}
