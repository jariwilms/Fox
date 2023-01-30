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
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Prefab/Rendering/Geometry/Geometry.hpp"

using namespace hlx;



int main()
{
    IO::init();
    Time::init();

    std::string windowTitle{ "Helix" };
    const Vector2f windowDimensions{ 1280, 720 };
    auto window = Window::create(windowTitle, windowDimensions);

    //TODO: move into rendercontext?
    Geometry::init();
    Renderer::init();



    //Component setup
    auto observer = Registry::create();
    auto& camera = Registry::add_component<Camera>(observer);
    auto& transform = Registry::get_component<Transform>(observer);
    transform.translate(Vector3f{ 0.0f, 0.0f, 3.0f });



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



    TextureBlueprint bp{};
    auto kiryuImage = IO::load<Image>("textures/kiryu.png");
    auto kiryuTexture = bp.build(kiryuImage, 1);

    auto normalImage = IO::load<Image>("textures/normal.png");
    auto normalTexture = bp.build(normalImage, 1);



    auto mat = std::make_shared<Material>();
    mat->albedo = kiryuTexture;
    mat->normal = normalTexture;
    auto kiryuMesh = std::make_shared<Mesh>(texturedCubeVAO, mat);

    

    Time::reset();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    RendererAPI::RenderInfo ri{ camera, transform, {} };

	while (true)
	{
        Time::tick();

        if (Input::key_pressed(Key::W)) transform.position += 1.0f * transform.forward() * Time::delta();
        if (Input::key_pressed(Key::S)) transform.position -= 1.0f * transform.forward() * Time::delta();
        if (Input::key_pressed(Key::A)) transform.position -= 1.0f * transform.right()   * Time::delta();
        if (Input::key_pressed(Key::D)) transform.position += 1.0f * transform.right()   * Time::delta();
        if (Input::key_pressed(Key::E)) transform.position += 1.0f * transform.up()      * Time::delta();
        if (Input::key_pressed(Key::Q)) transform.position -= 1.0f * transform.up()      * Time::delta();

        Renderer::start(ri);
        Renderer::render_mesh(kiryuMesh);
        Renderer::finish();
		window->refresh();
	}
}
