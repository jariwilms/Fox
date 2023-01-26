#include "stdafx.hpp"

#include "RenderBufferBlueprint.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"

namespace hlx
{
    std::shared_ptr<RenderBuffer> RenderBufferBlueprint::build(const glm::uvec2& dimensions, unsigned int multiSamples) const
    {
        return GraphicsAPI::create_rbo(type, layout, dimensions, multiSamples);
    }
}
