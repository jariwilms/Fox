#pragma once

#include <stdafx.hpp>

#include <fox/core/time/time.hpp>
#include <fox/core/utility/utility.hpp>
#include <fox/input/input.hpp>
#include <fox/math/linear_algebra/projection.hpp>
#include <fox/math/trigonometry/trigonometry.hpp>
#include <fox/rendering/base/shader/utility.hpp>
#include <fox/rendering/rendering.hpp>

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
        void render_meshes(std::shared_ptr<gfx::FrameBuffer> frameBuffer, std::shared_ptr<gfx::Pipeline> shader);
        void render_lighting(std::shared_ptr<gfx::FrameBuffer> target);
        void render_skybox(std::shared_ptr<gfx::FrameBuffer> target, std::shared_ptr<gfx::FrameBuffer> previous);



        std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>> mmt_{};
        std::vector<unf::Light>                                            lights_{};
        std::vector<unf::Light>                                            shadowCastingPointLights_{};
        std::vector<unf::Light>                                            shadowCastingDirectionalLights_{};
        std::vector<fox::Transform>                                        debugTransforms_{};

        std::shared_ptr<gfx::FrameBuffer>                                  gBuffer_{};
        std::shared_ptr<gfx::FrameBuffer>                                  sBuffer_{};
        std::array<std::shared_ptr<gfx::FrameBuffer>, 2>                   pBuffers_{};
        std::shared_ptr<gfx::FrameBuffer>                                  ssaoBuffer_{};
        std::shared_ptr<gfx::Texture2D>                                    ssaoNoiseTexture_{};

        std::shared_ptr<gfx::Cubemap>                                      environmentCubemap_{};
        std::shared_ptr<gfx::Cubemap>                                      irradianceCubemap_{};
        std::shared_ptr<gfx::Cubemap>                                      preFilterCubemap_{};
        std::shared_ptr<gfx::Texture2D>                                    brdfTexture_{};

        std::shared_ptr<gfx::UniformBuffer<unf::Context>>                  contextUniform_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Matrices>>                 matricesUniform_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Material>>                 materialUniform_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Camera>>                   cameraUniform_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Light>>                    lightUniform_{};
        std::shared_ptr<gfx::UniformArrayBuffer<unf::SSAOSample, 64u>>     ssaoSampleUniform_{};

        std::unordered_map<std::string, std::shared_ptr<gfx::Pipeline>>    pipelines_{};

        gl::float32_t                                                      shadowFarPlane_{ 100.0f };

        gfx::RenderInfo                                                    renderInfo_{};
    };
}
