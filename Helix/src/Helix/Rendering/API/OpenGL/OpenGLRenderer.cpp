#include "stdafx.hpp"

#include "OpenGLRenderer.hpp"

namespace hlx
{
    OpenGLRenderer::OpenGLRenderer()
    {
        std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> gBufferTextureBlueprints
        {
            std::make_tuple("Position", FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGB,  Texture::ColorDepth::_16bit, }),
            std::make_tuple("Albedo",   FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGBA, Texture::ColorDepth::_8bit, }),
            std::make_tuple("Normal",   FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGB,  Texture::ColorDepth::_16bit, }),
            std::make_tuple("ARM",      FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGBA, Texture::ColorDepth::_8bit, }),
        };
        std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> gBufferRenderBufferBlueprints
        {
            std::make_tuple("DepthStencil", FrameBuffer::Attachment::DepthStencil, RenderBufferBlueprint{ RenderBuffer::Type::DepthStencil, RenderBuffer::Layout::Depth24Stencil8 }), 
        };
        
        FrameBufferBlueprint frameBufferBlueprint{ gBufferTextureBlueprints, gBufferRenderBufferBlueprints };
        m_gBufferMultisample = frameBufferBlueprint.build_ms(Vector2f{ 1280, 720 }, 2);
        m_gBuffer = frameBufferBlueprint.build(Vector2f{ 1280, 720 });



        std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> ppBufferTextureBlueprint
        {
            std::make_tuple("Color", FrameBuffer::Attachment::Color, TextureBlueprint{ Texture::Format::RGB, Texture::ColorDepth::_16bit, }),
        };
        std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> ppBufferRenderBufferBlueprint
        {
            std::make_tuple("Depth", FrameBuffer::Attachment::Depth, RenderBufferBlueprint{ RenderBuffer::Type::Depth, RenderBuffer::Layout::Depth24 }),
        };

        FrameBufferBlueprint ppBufferBlueprint{ ppBufferTextureBlueprint, ppBufferRenderBufferBlueprint };
        for (auto& ppBuffer : m_ppBuffers)
        {
            ppBuffer = ppBufferBlueprint.build({ 1280, 720 });
        }





        //Buffer for lights, TODO: pass actual light count to lighting shader instead of const value
        const auto lightCount = 8;
        m_matricesBuffer = std::make_shared<OpenGLUniformBuffer<UMatrices>>(0, UMatrices{});
        m_materialBuffer = std::make_shared<OpenGLUniformBuffer<UMaterial>>(1, UMaterial{});
        m_lightBuffer    = std::make_shared<OpenGLUniformArrayBuffer<ULight>>(lightCount, 2); //2 = binding number
        m_cameraBuffer   = std::make_shared<OpenGLUniformBuffer<UCamera>>(3, UCamera{});
        




        //TODO: maybe predefined pipeline names (constexpr?), these will probably not change anyways
        m_pipelines.emplace("Geometry", GraphicsAPI::create_plo("shaders/compiled/geometry_pbrvert.spv", "shaders/compiled/geometry_pbrfrag.spv"));
        m_pipelines.emplace("Lighting", GraphicsAPI::create_plo("shaders/compiled/lighting_pbrvert.spv", "shaders/compiled/lighting_pbrfrag.spv"));
        m_pipelines.emplace("Skybox",   GraphicsAPI::create_plo("shaders/compiled/skyboxvert.spv",       "shaders/compiled/skyboxfrag.spv"));





        //TODO: global state control class (set + remember current state so unnecessary (and maybe expensive) changes do not need to be made
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void OpenGLRenderer::start(const RenderInfo& renderInfo)
    {
        const auto& camera           = renderInfo.camera;
        const auto& transform        = renderInfo.cameraTransform;
        const auto& viewMatrix       = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
        const auto& projectionMatrix = camera.projection_matrix();

        std::array<ULight, 8> uLights{};
        const auto& lights = renderInfo.lights;
        std::transform(lights.begin(), lights.end(), uLights.begin(), [](const std::tuple<Light, Vector3f>& _)
            {
                const auto& [light, position] = _;
                return ULight
                {
                    Vector4f{ position, 0.0f },
                    Vector4f{ light.color, 0.0f },
                };
            });

        m_matricesBuffer->copy_tuple(offsetof(UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraBuffer->copy(UCamera{ Vector4f{ transform.position, 0.0f } });
        m_lightBuffer->copy(uLights);



        m_gBufferMultisample->bind(FrameBuffer::Target::Write);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }
    void OpenGLRenderer::finish()
    {
        glDisable(GL_CULL_FACE);


        
        



        //Multisampled framebuffer textures can not be sampled like a regular framebuffer, so we have to copy it into a regular framebuffer
        const auto width{ 1280 };
        const auto height{ 720 };
        for (auto i{ 0u }; i < 4; ++i)
        {
            glNamedFramebufferReadBuffer(m_gBufferMultisample->id(), GL_COLOR_ATTACHMENT0 + i);
            glNamedFramebufferDrawBuffer(m_gBuffer->id(), GL_COLOR_ATTACHMENT0 + i);
            glBlitNamedFramebuffer(m_gBufferMultisample->id(), m_gBuffer->id(), 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }
        glBlitNamedFramebuffer(m_gBufferMultisample->id(), m_gBuffer->id(), 0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);


        


        //Lighting pass render into ppBuffer
        glDisable(GL_BLEND);

        m_ppBuffers[0]->bind(FrameBuffer::Target::Write);
        m_gBuffer->bind_texture("Position", 0);
        m_gBuffer->bind_texture("Albedo",   1);
        m_gBuffer->bind_texture("Normal",   2);
        m_gBuffer->bind_texture("ARM",      3);

        m_pipelines.at("Lighting")->bind();
        Geometry::Plane::vao()->bind();

        glDisable(GL_DEPTH_TEST);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glEnable(GL_BLEND);



        //Skybox pass after copying depth information from gBuffer
        const auto& skybox = RenderSettings::lighting.skybox;
        if (skybox)
        {
            Geometry::Cube::vao()->bind();

            m_pipelines.at("Skybox")->bind();
            skybox->bind(0);

            glEnable(GL_DEPTH_TEST);
            glBlitNamedFramebuffer(m_gBuffer->id(), m_ppBuffers[0]->id(), 0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Geometry::Cube::vao()->indices()->size()), GL_UNSIGNED_INT, nullptr);
            glDisable(GL_DEPTH_TEST);
        }



        glBlitNamedFramebuffer(m_ppBuffers[0]->id(), 0, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        //glNamedFramebufferReadBuffer(m_gBuffer->id(), GL_COLOR_ATTACHMENT0 + 3);
        //glBlitNamedFramebuffer(m_gBuffer->id(), 0, 0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

    void OpenGLRenderer::render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const Material> material, const Transform& transform)
    {
        m_pipelines.at("Geometry")->bind();
        m_matricesBuffer->copy_tuple(offsetof(UMatrices, model),  std::make_tuple(transform.matrix()));
        m_matricesBuffer->copy_tuple(offsetof(UMatrices, normal), std::make_tuple(glm::transpose(glm::inverse(transform.matrix()))));

        const auto& vao = mesh->vao();
        vao->bind();
        if (vao->indexed()) vao->indices()->bind();

        m_materialBuffer->copy(UMaterial{ material->color, material->roughness, material->metallic });
        material->albedoMap->bind(0);
        material->normalMap->bind(1);
        material->armMap->bind(2);
        material->emissionMap->bind(3);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vao->indices()->count()), GL_UNSIGNED_INT, nullptr);
    }
}
