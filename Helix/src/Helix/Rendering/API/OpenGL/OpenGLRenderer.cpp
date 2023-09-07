#include "stdafx.hpp"

#include "OpenGLRenderer.hpp"

#include "Helix/Core/Library/Utility/Utility.hpp"
#include "Helix/Rendering/RenderSettings.hpp"

namespace hlx
{
    OpenGLRenderer::OpenGLRenderer()
    {
        //Create FrameBuffer and RenderBuffer textures
        TextureBlueprint positionTextureBp{ Texture::Format::RGB, Texture::ColorDepth::_16bit, };
        TextureBlueprint colorTextureBp{ Texture::Format::RGB, Texture::ColorDepth::_16bit, };
        TextureBlueprint specularTextureBp{ .colorDepth = Texture::ColorDepth::_8bit, };

        RenderBufferBlueprint depthRenderBufferBp{ RenderBuffer::Type::Depth, RenderBuffer::Layout::Depth32 };

        std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> textureBlueprints{};
        textureBlueprints.emplace_back(std::make_tuple("Position", FrameBuffer::Attachment::Color, positionTextureBp));
        textureBlueprints.emplace_back(std::make_tuple("Color", FrameBuffer::Attachment::Color, colorTextureBp));
        textureBlueprints.emplace_back(std::make_tuple("Specular", FrameBuffer::Attachment::Color, specularTextureBp));

        std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> renderBufferBlueprints{};
        renderBufferBlueprints.emplace_back(std::make_tuple("Depth", FrameBuffer::Attachment::Depth, depthRenderBufferBp));

        FrameBufferBlueprint frameBufferBlueprint{ textureBlueprints, renderBufferBlueprints };

        m_frameBufferMultisample = frameBufferBlueprint.build_ms(Vector2f{ 1280, 720 }, 2);
        m_gBuffers[0] = frameBufferBlueprint.build(Vector2f{ 1280, 720 });     //TODO: fetch target window resolution from WindowManager
        m_gBuffers[1] = frameBufferBlueprint.build(Vector2f{ 1280, 720 });

        TextureBlueprint depthTexture{ Texture::Format::D, Texture::ColorDepth::_32bit, Texture::Filter::Point, Texture::Wrapping::Repeat, Texture::Wrapping::Repeat, };
        FrameBufferBlueprint depthBp{};
        depthBp.textures.emplace_back(std::make_tuple("Depth", FrameBuffer::Attachment::Depth, depthTexture));
        m_depthMap = depthBp.build(Vector2u{ 1024, 1024 });





        //Buffer for lights, TODO: pass actual light count to lighting shader instead of const value
        constexpr auto lightCount = 32;
        m_matricesBuffer = std::make_shared<OpenGLUniformBuffer<UMatrices>>(0, UMatrices{});
        m_materialBuffer = std::make_shared<OpenGLUniformBuffer<UMaterial>>(1, UMaterial{});
        m_lightBuffer = std::make_shared<OpenGLUniformArrayBuffer<ULight>>(lightCount, 2);
        m_cameraBuffer = std::make_shared<OpenGLUniformBuffer<UCamera>>(3, UCamera{});
        




        //TODO: maybe predefined pipeline names (constexpr?), these will probably not change anyways
        m_pipelines.emplace("Geometry", GraphicsAPI::create_plo("shaders/compiled/geometryvert.spv", "shaders/compiled/geometryfrag.spv"));
        m_pipelines.emplace("Lighting", GraphicsAPI::create_plo("shaders/compiled/lightingvert.spv", "shaders/compiled/lightingfrag.spv"));
        m_pipelines.emplace("Skybox", GraphicsAPI::create_plo("shaders/compiled/skyboxvert.spv", "shaders/compiled/skyboxfrag.spv"));





        //TODO: global state control class (set + remember current state so unnecessary (and maybe expensive) changes do not need to be made
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDepthFunc(GL_LEQUAL);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void OpenGLRenderer::start(const RenderInfo& renderInfo)
    {
        const auto& camera = renderInfo.camera;
        const auto& position = renderInfo.cameraPosition;

        const auto viewMatrix = glm::lookAt(position.position, position.position + position.forward(), position.up());
        const auto& projectionMatrix = camera.projection_matrix();





        std::array<ULight, 32> uLights{};
        for (auto index{ 0u }; const auto& [light, position] : renderInfo.lights)
        {
            ULight uLight
            {
                .position  = Vector4f{ position, 0.0f },
                .color     = Vector4f{ light.color, 0.0f },
                .linear    = 0.1f,
                .quadratic = 0.1f,
                .radius    = 100.0f,
            };

            uLights[index] = uLight;
            ++index;
        }

        m_lightBuffer->copy(uLights);





        m_frameBufferMultisample->bind(FrameBuffer::Target::Write);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        m_matricesBuffer->copy_tuple(offsetof(UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraBuffer->copy(UCamera{ Vector4f{ position.position, 0.0f } });

        m_pipelines.find("Geometry")->second->bind(); //TODO: move to render func? It may be safer to call this every render, bind state is remembered anyways
    }
    void OpenGLRenderer::finish()
    {
        glDisable(GL_CULL_FACE);









        //Render the skybox last  so unnecessary fragments are not drawn
        const auto& skybox = RenderSettings::lighting.skybox;
        const auto& skyboxPipeline = m_pipelines.find("Skybox");
        if (skybox && skyboxPipeline != m_pipelines.end())
        {
            Cube::vao->bind();
            skyboxPipeline->second->bind();
            skybox->bind(0);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Cube::vao->indices()->size()), GL_UNSIGNED_INT, nullptr);
        }











        const auto width = 1280;
        const auto height = 720;
        m_frameBufferMultisample->bind(FrameBuffer::Target::Read);
        m_gBuffers[m_pingpong]->bind(FrameBuffer::Target::Write);

        //TODO: render manually to texture instead of blitting?
        for (auto i = 0u; i < 3; ++i)
        {
            glReadBuffer(GL_COLOR_ATTACHMENT0 + i);
            glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
            glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }

        m_frameBufferMultisample->unbind();                                                      

        m_gBuffers[m_pingpong]->unbind();                                     
        m_gBuffers[m_pingpong]->bind_texture("Position", 0);
        m_gBuffers[m_pingpong]->bind_texture("Color", 1);
        m_gBuffers[m_pingpong]->bind_texture("Specular", 2);

        m_pipelines.find("Lighting")->second->bind();
        Geometry::quad->vao->bind();

        glDisable(GL_DEPTH_TEST);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::render(const std::shared_ptr<const Mesh> mesh, const std::shared_ptr<const DefaultMaterial> material, const Transform& transform)
    {
        m_matricesBuffer->copy_tuple(0, std::make_tuple(transform.matrix()));

        const auto vao = mesh->vao();
        vao->bind();
        if (vao->indexed()) vao->indices()->bind();

        m_materialBuffer->copy(UMaterial{ Vector4f{ material->color, 1.0f }, material->metallic, material->roughness });
        material->albedo->bind(0);
        material->normal->bind(1);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vao->indices()->count()), GL_UNSIGNED_INT, nullptr);
    }
}
