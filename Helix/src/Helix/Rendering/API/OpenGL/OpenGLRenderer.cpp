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





        //std::array<ULight, 32> lights{};
        constexpr auto lightCount = 32;

        m_matricesBuffer = std::make_shared<OpenGLUniformBuffer<UMatrices>>(0, UMatrices{});
        m_materialBuffer = std::make_shared<OpenGLUniformBuffer<UMaterial>>(1, UMaterial{});
        m_lightBuffer = std::make_shared<OpenGLUniformArrayBuffer<ULight>>(lightCount, 2);
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
        const auto& position = renderInfo.viewPosition;
        //m_lights = renderInfo.lights;

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










        m_gBuffer->bind(FrameBuffer::Target::Write);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        m_matricesBuffer->copy_tuple(offsetof(UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraBuffer->copy(UCamera{ Vector4f{ position.position, 0.0f } });

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

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vao->indices()->size() / sizeof(unsigned int)), GL_UNSIGNED_INT, nullptr);
        }
    }
}
