#pragma once

#include "stdafx.hpp"

#include "Helix/ECS/Components/Camera.hpp"
#include "Helix/Rendering/Mesh/Mesh.hpp"
#include "Helix/ECS/Components/Components.hpp"
#include "Helix/Rendering/Buffer/UniformBuffer.hpp"
#include "Helix/Prefab/Rendering/Geometry/Geometry.hpp"
#include "Helix/ECS/Components/Light.hpp"
#include "Helix/Rendering/Shader/Uniform/Uniform.hpp"
#include "Helix/ECS/Components/Transform.hpp"
#include "Helix/Rendering/Model/Model.hpp"
#include "Helix/Rendering/PostProcessing/PostProcessing.hpp"
#include "Helix/Rendering/Texture/CubemapTexture.hpp"
//#include "Helix/"

namespace hlx
{
    class RendererAPI
    {
    public:
        struct RenderInfo
        {
        public:
            RenderInfo(const Camera& camera, const Transform& cameraPosition, const std::vector<std::tuple<Light, Vector3f>>& lights)
                : camera{ camera }, cameraPosition{ cameraPosition }, lights{ lights } {}

            const Camera& camera{};
            const Transform& cameraPosition{};
            const std::vector<std::tuple<Light, Vector3f>>& lights{};
        };

        virtual ~RendererAPI() = default;

        virtual void start(const RenderInfo& renderInfo) = 0;
        virtual void finish() = 0;

        virtual void render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const DefaultMaterial> material, const Transform& transform) = 0;

    protected:
        RendererAPI() = default;
    };
}
