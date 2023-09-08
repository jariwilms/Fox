#pragma once

#include "stdafx.hpp"

#include "Helix/Core/Library/Camera/Camera.hpp"
#include "Helix/Core/Library/Lighting/Light.hpp"
#include "Helix/ECS/Components/Components.hpp"
#include "Helix/Rendering/Geometry/Geometry.hpp"
#include "Helix/Rendering/Buffer/UniformBuffer.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"
#include "Helix/Rendering/Model/Model.hpp"
#include "Helix/Rendering/PostProcessing/PostProcessing.hpp"
#include "Helix/Rendering/Shader/Uniform/Uniform.hpp"
#include "Helix/Rendering/Texture/CubemapTexture.hpp"

namespace hlx
{
    class RendererAPI
    {
    public:
        struct RenderInfo
        {
        public:
            const Camera& camera{};
            const Transform& cameraPosition{};
            std::span<std::tuple<Light, Vector3f> const> lights{};
        };

        virtual ~RendererAPI() = default;

        virtual void start(const RenderInfo& renderInfo) = 0;
        virtual void finish() = 0;

        virtual void render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const DefaultMaterial> material, const Transform& transform) = 0;

    protected:
        RendererAPI() = default;
    };
}
