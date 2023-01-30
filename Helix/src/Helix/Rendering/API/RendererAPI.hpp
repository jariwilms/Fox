#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Components/Camera.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"
#include "Helix/ECS/Components/Components.hpp"
#include "Helix/Rendering/Buffer/UniformBuffer.hpp"
#include "Helix/Prefab/Rendering/Geometry/Geometry.hpp"
#include "Helix/ECS/Components/Light.hpp"
#include "Helix/Rendering/Shader/Uniform/Uniform.hpp"

namespace hlx
{
    class RendererAPI
    {
    public:
        struct RenderInfo
        {
            const Camera& camera{};
            const Transform& viewPosition{};
            std::span<const Light> lights{};
        };

        virtual ~RendererAPI() = default;

        virtual void start(const RenderInfo& renderInfo) = 0;
        virtual void finish() = 0;

        virtual void render_mesh(const std::shared_ptr<Mesh> mesh) = 0;

    protected:
        RendererAPI() = default;
    };
}
