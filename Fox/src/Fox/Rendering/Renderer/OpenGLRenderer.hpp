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

        void start(gfx::RenderInfo renderInfo);
        void finish();

        void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform);
        void render_debug(const fox::Transform& transform);

    private:
        void render_meshes(std::shared_ptr<gfx::FrameBufferMultisample> frameBuffer, std::shared_ptr<gfx::Pipeline> shader);
        void render_shadow_map_point(const unf::Light& light, std::shared_ptr<gfx::FrameBuffer> target);
        void render_lighting(std::shared_ptr<gfx::FrameBuffer> target);
        void render_lighting_shadow(std::shared_ptr<gfx::FrameBuffer> target);
        void render_ambient_lighting(std::shared_ptr<gfx::FrameBuffer> target, std::shared_ptr<gfx::FrameBuffer> previous);
        void render_skybox(std::shared_ptr<gfx::FrameBuffer> target, std::shared_ptr<gfx::FrameBuffer> previous);
        void render_hdr();



        std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>> m_mmt{};
        std::vector<unf::Light>                                            m_lights{};
        std::vector<unf::Light>                                            m_shadowCastingPointLights{};
        std::vector<unf::Light>                                            m_shadowCastingDirectionalLights{};
        std::vector<fox::Transform>                                        m_debugTransforms{};
                                                    
        std::shared_ptr<gfx::FrameBuffer>                                  m_gBuffer{};
        std::shared_ptr<gfx::FrameBufferMultisample>                       m_gBufferMultisample{}; 
        std::shared_ptr<gfx::FrameBuffer>                                  m_sBuffer{};
        std::array<std::shared_ptr<gfx::FrameBuffer>, 4>                   m_shadowCubemaps{}; //TODO: change to cube map array
        std::shared_ptr<gfx::FrameBuffer>                                  m_hdrBuffer{};
        std::array<std::shared_ptr<gfx::FrameBuffer>, 2>                   m_pBuffers{};
                                                    
        std::shared_ptr<gfx::UniformBuffer<unf::Context>>                  m_contextBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Matrices>>                 m_matricesBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Material>>                 m_materialBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Camera>>                   m_cameraBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Light>>                    m_lightBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::LightShadow>>              m_lightShadowBuffer{};
        std::shared_ptr<gfx::UniformArrayBuffer<unf::ShadowProjection, 6>> m_shadowProjectionsBuffer{};
        std::unordered_map<std::string, std::shared_ptr<gfx::Pipeline>>    m_pipelines{};

        gl::float32_t                                                      m_shadowFarPlane{ 100.0f };

        gfx::RenderInfo                                                    m_renderInfo{};
    };
}
