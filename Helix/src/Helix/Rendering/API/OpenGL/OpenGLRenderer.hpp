#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/RenderAPI.hpp"

namespace hlx
{
    class OpenGLRenderer : public RenderAPI
    {
    public:
        void render(const std::shared_ptr<Mesh> mesh) override;
    };
}
