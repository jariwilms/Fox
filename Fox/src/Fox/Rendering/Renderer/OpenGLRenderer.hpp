#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Time/Time.hpp"
#include "Fox/Core/Library/Utility/Utility.hpp"
#include "Fox/Input/Input.hpp"
#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/API/Shader/Utility.hpp"

namespace fox::gfx::api
{
    class OpenGLRenderer
    {
    public:
        OpenGLRenderer();

        void start(const gfx::RenderInfo& renderInfo);
        void finish();

        void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform);
        void render_debug(const fox::Transform& transform);

    private:
        std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>> mmt{};
        std::vector<unf::Light>                                            sceneLights{};
        std::vector<unf::Light>                                            pointLights{};
        std::vector<unf::Light>                                            directionalLights{};
        std::vector<fox::Transform>                                        debugTransforms{};
                                                    
        std::shared_ptr<gfx::FrameBuffer>                                  gBuffer{};
        std::shared_ptr<gfx::FrameBufferMultisample>                       gBufferMultisample{}; 
        std::shared_ptr<gfx::FrameBuffer>                                  sBuffer{};
        std::array<std::shared_ptr<gfx::FrameBuffer>, 4>                   shadowCubemaps{}; //TODO: change to cube map array
        std::array<std::shared_ptr<gfx::FrameBuffer>, 2>                   pBuffers{};
                                                    
        std::shared_ptr<gfx::UniformBuffer<unf::Context>>                  contextBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Matrices>>                 matricesBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Material>>                 materialBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Camera>>                   cameraBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Light>>                    lightBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::LightShadow>>              lightShadowBuffer{};
        std::shared_ptr<gfx::UniformArrayBuffer<unf::ShadowProjection, 6>> shadowProjectionsBuffer{};
        std::unordered_map<std::string, std::shared_ptr<gfx::Pipeline>>    pipelines{};
                                                    
        std::shared_ptr<const gfx::Cubemap>                                skybox{};
    };
}
