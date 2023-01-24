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

using namespace hlx;

struct Matrices
{
    glm::mat4 model{ 1.0f };
    glm::mat4 view{ 1.0f };
    glm::mat4 projection{ 1.0f };
};
struct Light
{
    glm::vec3 color{};
};

int main()
{
    IO::init();
    Time::init();

    auto window = Window::create("Helix", glm::uvec2{ 1280, 720 });
    glEnable(GL_DEPTH_TEST);





    //Component setup
    auto observer = Registry::create();
    auto& camera = Registry::add_component<Camera>(observer);
    auto& transform = Registry::get_component<Transform>(observer);
    transform.translate(glm::vec3{ 0.0f, 0.0f, 3.0f });

    Transform kiryuTransform{};
    Transform lightTransform{};
    lightTransform.translate(glm::vec3{ 1.0f, 0.0f, 0.0f });

    //UniformBuffer setup
    auto localRotation = glm::vec3{};
    auto viewMatrix = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
    Matrices mts{ kiryuTransform.transform(), viewMatrix, camera.projection() };
    auto ubo = GraphicsAPI::create_ubo(mts);
    ubo->bind_base(0);

    Light l{ glm::vec3{1.0f} };
    auto lightUBO = GraphicsAPI::create_ubo(l);
    lightUBO->bind_base(1);



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

	auto cubeVAO = GraphicsAPI::create_vao();
	cubeVAO->tie(cubePositionsVBO, layout3f);
    cubeVAO->tie(cubeNormalsVBO, layout3f);
    cubeVAO->tie(cubeTexCoordsVBO, layout2f);



    //Pipeline setup
    const auto texVertexSource = IO::load<File>("shaders/compiled/texturevert.spv")->read(); 
    const auto texFragmentSource = IO::load<File>("shaders/compiled/texturefrag.spv")->read();
    auto texVertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *texVertexSource);
    if (!texVertexShader->valid()) throw std::runtime_error{ texVertexShader->error().data() };
    auto texFragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *texFragmentSource);
    if (!texFragmentShader->valid()) throw std::runtime_error{ texFragmentShader->error().data() };
    auto texPipeline = GraphicsAPI::create_plo({ texVertexShader, texFragmentShader });

    //Pipeline setup
    const auto lightVertexSource = IO::load<File>("shaders/compiled/lightingvert.spv")->read();
    const auto lightFragmentSource = IO::load<File>("shaders/compiled/lightingfrag.spv")->read();
    auto lightVertexShader = GraphicsAPI::create_sho(Shader::Type::Vertex, *texVertexSource);
    if (!lightVertexShader->valid()) throw std::runtime_error{ lightVertexShader->error().data() };
    auto lightFragmentShader = GraphicsAPI::create_sho(Shader::Type::Fragment, *texFragmentSource);
    if (!lightFragmentShader->valid()) throw std::runtime_error{ lightFragmentShader->error().data() };
    auto lightPipeline = GraphicsAPI::create_plo({ lightVertexShader, lightFragmentShader });

    TextureBlueprint bp{};
    auto kiryuImage = IO::load<Image>("textures/Kiryu.png");
    auto kiryuTexture = bp.build<Texture2D>(kiryuImage);
    kiryuTexture->bind(0);












    Time::reset();
	while (true)
	{
        Time::tick();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        if (Input::key_pressed(Key::W)) transform.position += 1.0f * transform.forward() * Time::delta();
        if (Input::key_pressed(Key::S)) transform.position -= 1.0f * transform.forward() * Time::delta();
        if (Input::key_pressed(Key::A)) transform.position -= 1.0f * transform.right()   * Time::delta();
        if (Input::key_pressed(Key::D)) transform.position += 1.0f * transform.right()   * Time::delta();
        if (Input::key_pressed(Key::E)) transform.position += 1.0f * transform.up()      * Time::delta();
        if (Input::key_pressed(Key::Q)) transform.position -= 1.0f * transform.up()      * Time::delta();
        if (Input::button_pressed(Button::Button1))
        {
            auto rel = Input::cursor_position_relative();
            localRotation -= glm::vec3{ rel.y, rel.x, 0.0f } * 100.0f * Time::delta();
            transform.rotation = glm::quat(glm::radians(localRotation));
        }



        cubeVAO->bind();

        texPipeline->bind();
        ubo->copy_tuple(0, std::make_tuple(kiryuTransform.transform()));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightPipeline->bind();
        ubo->copy_tuple(0, std::make_tuple(lightTransform.transform()));
        glDrawArrays(GL_TRIANGLES, 0, 36);



		window->refresh();
	}
}
