#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/Mesh/Mesh.hpp"

namespace hlx
{
    class RenderAPI
    {
    public:
        virtual ~RenderAPI() = default;

        virtual void render(const std::shared_ptr<Mesh> mesh) = 0;

    protected:
        RenderAPI() = default;
    };
}
