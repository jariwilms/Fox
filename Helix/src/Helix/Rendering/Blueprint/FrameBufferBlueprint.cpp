#include "stdafx.hpp"

#include "FrameBufferBlueprint.hpp"

#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx
{
    std::shared_ptr<FrameBuffer> FrameBufferBlueprint::build(const Vector2u& dimensions) const
    {
        return GFX_DEPRECATED::create_framebuffer(dimensions, utl::to_span(textures), utl::to_span(renderBuffers));
    }
    std::shared_ptr<FrameBufferMultisample> FrameBufferBlueprint::build_multisample(const Vector2u& dimensions, unsigned int samples) const
    {
        return GFX_DEPRECATED::create_framebuffer_multisample(dimensions, samples, utl::to_span(textures), utl::to_span(renderBuffers));
    }
}
