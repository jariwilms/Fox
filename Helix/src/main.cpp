#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Application.hpp"
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
#include "Helix/Prefab/Rendering/Geometry/Cube.hpp"
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Window/Window.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLCubemapTexture.hpp"
#include "Helix/Core/Library/Array/CyclicBuffer.hpp"

#include "Helix/Test/Test.hpp"
#include "Helix/Experimental/Texture/Texture.hpp"

using namespace hlx;

int main(int argc, char** argv)
{
    Application application{ argc, argv };

    const std::string windowIdentifier{ "Window 1" };
    const std::string windowTitle{ "Helix" };
    const Vector2u windowDimensions{ 1280, 720 };
    const auto window = WindowManager::create(windowIdentifier, windowTitle, windowDimensions);

    IO::init();
    Geometry::init();
    Renderer::init();
    ModelImporter::init();

    auto observer = Registry::create();
    auto& camera = Registry::add_component<Camera>(observer);
    auto& cameraTransform = Registry::get_component<Transform>(observer);
    cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 3.0f });




    //auto planeModel = ModelImporter::load(R"(models/plane/plane.glb)");
    auto planeModel = ModelImporter::load(R"(models/backpack/scene.gltf)");
    Transform planeTransform{};

    std::vector<std::tuple<Light, Vector3f>> lights{};
    lights.resize(32);
    Light l{};
    l.color = Vector3f{ 0.0f, 0.01f, 0.0f };
    lights[0] = std::make_tuple(l, Vector3f{ 0.5f, 0.5f, 0.5f });





    Time::reset();
    CyclicBuffer<float, 128> frametimes{};

    const auto native = window->native_window();
	while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(native)))
	{
        Time::advance();



        const auto shift = Input::key_pressed(Key::LeftShift) ? 10.0f : 1.0f;
        if (Input::key_pressed(Key::W)) cameraTransform.position += cameraTransform.forward() * shift * Time::delta();
        if (Input::key_pressed(Key::S)) cameraTransform.position -= cameraTransform.forward() * shift * Time::delta();
        if (Input::key_pressed(Key::A)) cameraTransform.position -= cameraTransform.right()   * shift * Time::delta();
        if (Input::key_pressed(Key::D)) cameraTransform.position += cameraTransform.right()   * shift * Time::delta();
        if (Input::key_pressed(Key::E)) cameraTransform.position += cameraTransform.up()      * shift * Time::delta();
        if (Input::key_pressed(Key::Q)) cameraTransform.position -= cameraTransform.up()      * shift * Time::delta();

        if (Input::button_pressed(Button::Button1)) //RMB
        {
            static Vector3f rotation{};
            const auto rel = Input::cursor_position_relative() / 10.0f;
            rotation += Vector3f{ rel.y, rel.x, 0.0f };

            cameraTransform.rotation = Quaternion{ glm::radians(rotation) };
        }

        Renderer::start(RendererAPI::RenderInfo{ camera, cameraTransform, lights });
        //The render system starts running here and submits all models/meshes to the renderer
        Renderer::render(planeModel, planeTransform);
        Renderer::finish();



		window->refresh();
        frametimes.push_back(Time::delta());
	}

    return 0;
}
