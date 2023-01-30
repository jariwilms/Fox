#include "stdafx.hpp"

#include "OpenGLRenderer.hpp"

namespace hlx
{
    OpenGLRenderer::OpenGLRenderer()
    {
        TextureBlueprint positionTextureBp{};
        TextureBlueprint colorTextureBp{};
        TextureBlueprint specularTextureBp{};
        positionTextureBp.layout = Texture::Layout::RGB16;
        positionTextureBp.format = Texture::Format::RGB;
        colorTextureBp.layout = Texture::Layout::RGB16;
        colorTextureBp.format = Texture::Format::RGB;
        specularTextureBp.layout = Texture::Layout::RGBA8;

        RenderBufferBlueprint depthRenderBufferBp{};
        depthRenderBufferBp.type = RenderBuffer::Type::Depth;
        depthRenderBufferBp.layout = RenderBuffer::Layout::Depth32;

        std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>> tbps{};
        tbps.emplace_back(std::make_tuple("Position", FrameBuffer::Attachment::Color, positionTextureBp));
        tbps.emplace_back(std::make_tuple("Color", FrameBuffer::Attachment::Color, colorTextureBp));
        tbps.emplace_back(std::make_tuple("Specular", FrameBuffer::Attachment::Color, specularTextureBp));

        std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>> rbps{};
        rbps.emplace_back(std::make_tuple("Depth", FrameBuffer::Attachment::Depth, depthRenderBufferBp));

        FrameBufferBlueprint fbbp{};
        fbbp.textures = tbps;
        fbbp.renderBuffers = rbps;

        m_gBuffer = fbbp.build(Vector2f{ 1280, 720 });                         //TODO: fetch target window from application





        std::array<ULight, 32> lights{};
        lights[0] = ULight{ Vector4f{ 1.0f, 0.2f, 1.0f, 1.0f }, Vector4f{ 1.0f, 0.0f, 1.0f, 1.0f }, 0.01f, 0.01f, 10.0f };

        m_matricesBuffer = std::make_shared<OpenGLUniformBuffer<UMatrices>>(0, UMatrices{});
        m_materialBuffer = std::make_shared<OpenGLUniformBuffer<UMaterial>>(1, UMaterial{});
        m_lightBuffer = std::make_shared<OpenGLUniformArrayBuffer<ULight>>(2, lights);
        m_cameraBuffer = std::make_shared<OpenGLUniformBuffer<UCamera>>(3, UCamera{});





        const auto geometryVertexSource = IO::load<File>("shaders/compiled/geometryvert.spv")->read();
        const auto geometryFragmentSource = IO::load<File>("shaders/compiled/geometryfrag.spv")->read();
        auto geometryVertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *geometryVertexSource);
        if (!geometryVertexShader->valid()) throw std::runtime_error{ geometryVertexShader->error().data() };
        auto geometryFragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *geometryFragmentSource);
        if (!geometryFragmentShader->valid()) throw std::runtime_error{ geometryFragmentShader->error().data() };
        auto geometryPipeline = GraphicsAPI::create_plo({ geometryVertexShader, geometryFragmentShader });
        m_pipelines.emplace("Geometry", geometryPipeline);

        const auto lightingVertexSource = IO::load<File>("shaders/compiled/lightingvert.spv")->read();
        const auto lightingFragmentSource = IO::load<File>("shaders/compiled/lightingfrag.spv")->read();
        auto lightingVertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *lightingVertexSource);
        if (!lightingVertexShader->valid()) throw std::runtime_error{ lightingVertexShader->error().data() };
        auto lightingFragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *lightingFragmentSource);
        if (!lightingFragmentShader->valid()) throw std::runtime_error{ lightingFragmentShader->error().data() };
        auto lightingPipeline = GraphicsAPI::create_plo({ lightingVertexShader, lightingFragmentShader });
        m_pipelines.emplace("Lighting", lightingPipeline);
    }

    void OpenGLRenderer::start(const RenderInfo& renderInfo)
    {
        const auto& camera = renderInfo.camera;
        const auto& transform = renderInfo.viewPosition;
        m_lights = renderInfo.lights;

        const auto viewMatrix = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
        const auto& projectionMatrix = camera.projection();

        m_gBuffer->bind(FrameBuffer::Target::Write);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        m_matricesBuffer->copy_tuple(offsetof(UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraBuffer->copy(UCamera{ Vector4f{ transform.position, 0.0f } });

        m_pipelines.find("Geometry")->second->bind();
    }
    void OpenGLRenderer::finish()
    {
        m_gBuffer->unbind();
        m_pipelines.find("Lighting")->second->bind();

        m_gBuffer->bind_texture("Position", 0);
        m_gBuffer->bind_texture("Color", 1);
        m_gBuffer->bind_texture("Specular", 2);
        m_gBuffer->bind(FrameBuffer::Target::Read);

        Geometry::quad->vao->bind();

        glDisable(GL_DEPTH_TEST);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::render_mesh(const std::shared_ptr<Mesh> mesh)
    {
        mesh->vao()->bind();

        const auto& material = mesh->material();
        m_materialBuffer->copy(UMaterial{ material->color, material->metallic, material->roughness });
        material->albedo->bind(0);
        material->normal->bind(1);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
