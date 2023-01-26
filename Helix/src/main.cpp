#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Core/Library/Time/Time.hpp"
#include "Helix/ECS/Components/Camera.hpp"
#include "Helix/ECS/Components/Transform.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/ECS/Registry.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/IO/Import/Model/GLTFImporter.hpp"
#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Model/Prefab/Cube.hpp"
#include "Helix/Window/Window.hpp"
#include "Helix/Rendering/Blueprint/FrameBufferBlueprint.hpp"

using namespace hlx;

struct Matrices
{
    glm::mat4 view{ 1.0f };
    glm::mat4 projection{ 1.0f };
};

int main()
{
    IO::init();
    Time::init();



    std::string windowTitle{ "Helix" };
    const glm::vec2 windowDimensions{ 1280, 720 };
    auto window = Window::create(windowTitle, windowDimensions);



    //Component setup
    auto observer = Registry::create();
    auto& camera = Registry::add_component<Camera>(observer);
    auto& transform = Registry::get_component<Transform>(observer);
    transform.translate(glm::vec3{ 0.0f, 0.0f, 3.0f });



    //UniformBuffer setup
    auto matricesUBO = GraphicsAPI::create_ubo<Matrices>();
    matricesUBO->bind_base(0);
    auto modelTransformUBO = GraphicsAPI::create_ubo(glm::mat4{1.0f});
    modelTransformUBO->bind_base(1);

    auto viewPositionUBO = GraphicsAPI::create_ubo<glm::vec3>();
    viewPositionUBO->copy(glm::vec3{ 0.0f, 0.0f, 3.0f });
    viewPositionUBO->bind_base(4);



    //Model setup
    std::vector<float> cubeVertices  = Cube::positions;
    std::vector<float> cubeNormals   = Cube::normals;
    std::vector<float> cubeTexCoords = Cube::texCoords;
	auto cubePositionsVBO = GraphicsAPI::create_vbo<float>(cubeVertices);
    auto cubeNormalsVBO   = GraphicsAPI::create_vbo<float>(cubeNormals);
    auto cubeTexCoordsVBO = GraphicsAPI::create_vbo<float>(cubeTexCoords);

    auto layout2f = std::make_shared<VertexLayout>();
    auto layout3f = std::make_shared<VertexLayout>();
    layout2f->specify<float>(2);
    layout3f->specify<float>(3);

	auto texturedCubeVAO = GraphicsAPI::create_vao();
	texturedCubeVAO->tie(cubePositionsVBO, layout3f);
    texturedCubeVAO->tie(cubeNormalsVBO, layout3f);
    texturedCubeVAO->tie(cubeTexCoordsVBO, layout2f);



    std::vector<float> quadData =
    {
        -1.0f,  1.0f, 0.0f,   0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
    };

    auto layout3f2f = std::make_shared<VertexLayout>();
    layout3f2f->specify<float>(3);
    layout3f2f->specify<float>(2);

    auto quadVBO = GraphicsAPI::create_vbo<float>(quadData);
    auto quadVAO = GraphicsAPI::create_vao();
    quadVAO->tie(quadVBO, layout3f2f);









    TextureBlueprint bp{};
    auto kiryuImage = IO::load<Image>("textures/Kiryu.png");
    auto kiryuTexture = bp.build(kiryuImage, 1);
    kiryuTexture->bind(0);

    auto missingImage = IO::load<Image>("textures/missing.png");
    auto missingTexture = bp.build(missingImage, 1);
    missingTexture->bind(1);



    const auto geometryVertexSource = IO::load<File>("shaders/compiled/geometryvert.spv")->read(); 
    const auto geometryFragmentSource = IO::load<File>("shaders/compiled/geometryfrag.spv")->read();
    auto geometryVertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *geometryVertexSource);
    if (!geometryVertexShader->valid()) throw std::runtime_error{ geometryVertexShader->error().data() };
    auto geometryFragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *geometryFragmentSource);
    if (!geometryFragmentShader->valid()) throw std::runtime_error{ geometryFragmentShader->error().data() };
    auto geometryPipeline = GraphicsAPI::create_plo({ geometryVertexShader, geometryFragmentShader });
    
    const auto deferredVertexSource = IO::load<File>("shaders/compiled/deferredvert.spv")->read();
    const auto deferredFragmentSource = IO::load<File>("shaders/compiled/deferredfrag.spv")->read();
    auto deferredVertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *deferredVertexSource);
    if (!deferredVertexShader->valid()) throw std::runtime_error{ deferredVertexShader->error().data() };
    auto deferredFragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *deferredFragmentSource);
    if (!deferredFragmentShader->valid()) throw std::runtime_error{ deferredFragmentShader->error().data() };
    auto gBufferPipeline = GraphicsAPI::create_plo({ deferredVertexShader, deferredFragmentShader });





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

    const auto gBuffer = fbbp.build(windowDimensions);





    Time::reset();
    const auto viewMatrix = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
    const auto& projectionMatrix = camera.projection();

	while (true)
	{
        Time::tick();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        gBuffer->bind(FrameBuffer::Target::Write);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        geometryPipeline->bind();
        matricesUBO->copy_tuple(0, std::make_tuple(viewMatrix, projectionMatrix));
        modelTransformUBO->copy_tuple(0, std::make_tuple(glm::translate(glm::mat4{ 1.0f }, glm::vec3{0.5f, 0.0f, 0.0f})));
        texturedCubeVAO->bind();
        kiryuTexture->bind(0);
        missingTexture->bind(1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        gBuffer->unbind();




        gBufferPipeline->bind();
        gBuffer->bind_texture("Position", 0);
        gBuffer->bind_texture("Color", 1);
        gBuffer->bind_texture("Specular", 2);
        gBuffer->bind(FrameBuffer::Target::Read);
        quadVAO->bind();
        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		window->refresh();
	}
}
