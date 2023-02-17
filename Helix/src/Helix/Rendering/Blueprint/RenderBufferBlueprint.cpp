#include "stdafx.hpp"

#include "RenderBufferBlueprint.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx
{
    std::shared_ptr<RenderBuffer> RenderBufferBlueprint::build(const Vector2u& dimensions) const
    {
        return GraphicsAPI::create_rbo(type, layout, dimensions);
    }
    std::shared_ptr<RenderBuffer> RenderBufferBlueprint::build_ms(const Vector2u& dimensions, unsigned int multiSamples) const
    {
        return GraphicsAPI::create_rbo_ms(type, layout, dimensions, multiSamples);
    }
}
