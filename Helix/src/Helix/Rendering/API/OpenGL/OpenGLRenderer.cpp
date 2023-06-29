#include "stdafx.hpp"

#include "OpenGLRenderer.hpp"

namespace hlx
{
    OpenGLRenderer::OpenGLRenderer()
    {
        TextureBlueprint positionTextureBp{};
        TextureBlueprint colorTextureBp{};
        TextureBlueprint specularTextureBp{};

        positionTextureBp.format = Texture::Format::RGB;
        colorTextureBp.format = Texture::Format::RGB;
        positionTextureBp.colorDepth = Texture::ColorDepth::_16Bit;
        colorTextureBp.colorDepth = Texture::ColorDepth::_16Bit;
        specularTextureBp.colorDepth = Texture::ColorDepth::_8Bit;

        RenderBufferBlueprint depthRenderBufferBp{};
        depthRenderBufferBp.type = RenderBuffer::Type::Depth;
        depthRenderBufferBp.colorDepth = RenderBuffer::Layout::Depth32;

        std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> tbps{};
        tbps.emplace_back(std::make_tuple("Position", FrameBuffer::Attachment::Color, positionTextureBp));
        tbps.emplace_back(std::make_tuple("Color", FrameBuffer::Attachment::Color, colorTextureBp));
        tbps.emplace_back(std::make_tuple("Specular", FrameBuffer::Attachment::Color, specularTextureBp));

        std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> rbps{};
        rbps.emplace_back(std::make_tuple("Depth", FrameBuffer::Attachment::Depth, depthRenderBufferBp));

        FrameBufferBlueprint fbbp{};
        fbbp.textures = tbps;
        fbbp.renderBuffers = rbps;

        m_fbm = fbbp.build_ms(Vector2f{ 1280, 720 }, 2);
        m_gBuffers[0] = fbbp.build(Vector2f{ 1280, 720 });                     //TODO: fetch target window from application
        m_gBuffers[1] = fbbp.build(Vector2f{ 1280, 720 });






        const auto sz = Vector2u{ 1024, 1024 };
        TextureBlueprint depthTexture{};
        depthTexture.format = Texture::Format::D;
        depthTexture.colorDepth = Texture::ColorDepth::_32Bit;
        depthTexture.filter = Texture::Filter::Point;
        depthTexture.wrappingS = Texture::Wrapping::Repeat;
        depthTexture.wrappingT = Texture::Wrapping::Repeat;

        FrameBufferBlueprint depthBp{};
        depthBp.textures.emplace_back(std::make_tuple("Depth", FrameBuffer::Attachment::Depth, depthTexture));
        m_depthMap = depthBp.build(sz);
















        constexpr auto lightCount = 32;
        m_matricesBuffer = std::make_shared<OpenGLUniformBuffer<UMatrices>>(0, UMatrices{});
        m_materialBuffer = std::make_shared<OpenGLUniformBuffer<UMaterial>>(1, UMaterial{});
        m_lightBuffer = std::make_shared<OpenGLUniformArrayBuffer<ULight>>(lightCount, 2);
        m_cameraBuffer = std::make_shared<OpenGLUniformBuffer<UCamera>>(3, UCamera{});
        


        auto geometryPipeline = GraphicsAPI::create_plo("shaders/compiled/geometryvert.spv", "shaders/compiled/geometryfrag.spv");
        m_pipelines.emplace("Geometry", geometryPipeline);

        auto skyboxPipeline = GraphicsAPI::create_plo("shaders/compiled/skyboxvert.spv", "shaders/compiled/skyboxfrag.spv");
        m_pipelines.emplace("Skybox", skyboxPipeline);

        auto lightingPipeline = GraphicsAPI::create_plo("shaders/compiled/lightingvert.spv", "shaders/compiled/lightingfrag.spv");
        m_pipelines.emplace("Lighting", lightingPipeline);

        auto postProcessingPipeline = GraphicsAPI::create_plo("shaders/compiled/sharpenvert.spv", "shaders/compiled/sharpenfrag.spv");
        m_postProcessingPipelines.emplace("SharpenKernel", postProcessingPipeline);



        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDepthFunc(GL_LEQUAL);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }

    void OpenGLRenderer::start(const RenderInfo& renderInfo)
    {
        m_renderInfo = renderInfo;

        const auto& camera = renderInfo.camera;
        const auto& position = renderInfo.viewPosition;

        const auto viewMatrix = glm::lookAt(position.position, position.position + position.forward(), position.up());
        const auto& projectionMatrix = camera.projection();



        auto index = 0u;
        std::array<ULight, 32> uLights{};

        for (const auto& [light, position] : renderInfo.lights)
        {
            ULight uLight;
            uLight.position = Vector4f{ position, 0.0f };
            uLight.color = Vector4f{ light.color, 0.0f };
            uLight.linear = 0.1f;
            uLight.quadratic = 0.1f;
            uLight.radius = 10.0f;

            uLights[index] = uLight;

            ++index;
        }

        m_lightBuffer->copy(uLights);









        m_fbm->bind(FrameBuffer::Target::Write);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        m_matricesBuffer->copy_tuple(offsetof(UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraBuffer->copy(UCamera{ Vector4f{ position.position, 0.0f } });

        m_pipelines.find("Geometry")->second->bind();
    }
    void OpenGLRenderer::finish()
    {
        glDisable(GL_CULL_FACE);

        if (m_renderInfo.skybox != nullptr)
        {
            m_pipelines.find("Skybox")->second->bind();
            Cube::vao->bind();
            m_renderInfo.skybox->bind(0);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(Cube::vao->indices()->size()), GL_UNSIGNED_INT, nullptr);
        }



        const auto width = 1280;
        const auto height = 720;
        m_fbm->bind(FrameBuffer::Target::Read);
        m_gBuffers[m_pingpong]->bind(FrameBuffer::Target::Write);

        for (auto i = 0u; i < 3; ++i)
        {
            glReadBuffer(GL_COLOR_ATTACHMENT0 + i);
            glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
            glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }

        m_fbm->unbind();                                                      

        m_gBuffers[m_pingpong]->unbind();                                     
        m_gBuffers[m_pingpong]->bind_texture("Position", 0);
        m_gBuffers[m_pingpong]->bind_texture("Color", 1);
        m_gBuffers[m_pingpong]->bind_texture("Specular", 2);

        m_pipelines.find("Lighting")->second->bind();
        Geometry::quad->vao->bind();

        glDisable(GL_DEPTH_TEST);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        //m_pingpong = !m_pingpong;
    }

    void OpenGLRenderer::render(const std::shared_ptr<const Model> model, const Transform& transform)
    {
        m_matricesBuffer->copy_tuple(0, std::make_tuple(transform.transform()));

        for (const auto& mesh : model->meshes)
        {
            const auto vao = mesh->vao();
            vao->bind();
            if (vao->indexed()) vao->indices()->bind();

            const auto& material = mesh->material();
            m_materialBuffer->copy(UMaterial{ material->color, material->metallic, material->roughness });
            material->albedo->bind(0);
            material->normal->bind(1);
            
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vao->indices()->count()), GL_UNSIGNED_INT, nullptr);
        }
    }
}
