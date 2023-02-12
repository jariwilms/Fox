#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Core/Library/Time/Time.hpp"
#include "Helix/ECS/Components/Camera.hpp"
#include "Helix/ECS/Components/Transform.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/ECS/Registry.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/IO/IO.hpp"
#include "Helix/IO/Import/Model/ModelImporter.hpp"
#include "Helix/Prefab/Rendering/Geometry/Geometry.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Blueprint/FrameBufferBlueprint.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Model/Prefab/Cube.hpp"
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Window/Window.hpp"

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



    auto model = ModelImporter::load("assets/models/backpack/scene.gltf");
    Transform modelTransform{};
    modelTransform.rotate(Vector3f{ -90.0f, 0.0f, 0.0f });

    auto observer = Registry::create();
    auto& camera = Registry::add_component<Camera>(observer);
    auto& cameraTransform = Registry::get_component<Transform>(observer);
    cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 3.0f });



    Time::reset();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    std::array<std::tuple<Light, Vector3f>, 32> lights{};
    Light l{};
    l.color = Vector3f{ 1.0f, 0.0f, 1.0f };
    lights[0] = std::make_tuple(l, Vector3f{ 0.5f, 0.5f, 0.5f });

	while (true)
	{
        Time::tick();

        const auto mul = Input::key_pressed(Key::LeftShift) ? 10.0f : 1.0f;
        if (Input::key_pressed(Key::W)) cameraTransform.position += 1.0f * cameraTransform.forward() * Time::delta() * mul;
        if (Input::key_pressed(Key::S)) cameraTransform.position -= 1.0f * cameraTransform.forward() * Time::delta() * mul;
        if (Input::key_pressed(Key::A)) cameraTransform.position -= 1.0f * cameraTransform.right()   * Time::delta() * mul;
        if (Input::key_pressed(Key::D)) cameraTransform.position += 1.0f * cameraTransform.right()   * Time::delta() * mul;
        if (Input::key_pressed(Key::E)) cameraTransform.position += 1.0f * cameraTransform.up()      * Time::delta() * mul;
        if (Input::key_pressed(Key::Q)) cameraTransform.position -= 1.0f * cameraTransform.up()      * Time::delta() * mul;



        auto& [testLight, testPosition] = lights.at(0);
        testPosition.x = glm::cos(glfwGetTime());



        Renderer::start(RendererAPI::RenderInfo{ camera, cameraTransform, lights });

        Renderer::render(model, modelTransform);

        Renderer::finish();
		window->refresh();
	}
}
