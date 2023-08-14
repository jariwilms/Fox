#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Application.hpp"
#include "Helix/Core/Library/Time/Time.hpp"
#include "Helix/ECS/Components/Components.hpp"
#include "Helix/ECS/Entity/Entity.hpp"
#include "Helix/ECS/Registry.hpp"
#include "Helix/Input/Input.hpp"
#include "Helix/IO/IO.hpp"
#include "Helix/IO/Import/Model/ModelImporter.hpp"
#include "Helix/Prefab/Rendering/Geometry/Geometry.hpp"
#include "Helix/Prefab/Rendering/Geometry/Cube.hpp"
#include "Helix/Rendering/API/GraphicsAPI.hpp"
#include "Helix/Rendering/Blueprint/FrameBufferBlueprint.hpp"
#include "Helix/Rendering/Blueprint/TextureBlueprint.hpp"
#include "Helix/Rendering/Renderer.hpp"
#include "Helix/Scene/Scene.hpp"
#include "Helix/Window/Window.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLCubemapTexture.hpp"
#include "Helix/Core/Library/Data/CyclicBuffer.hpp"

#include "Helix/Test/Test.hpp"
#include "Helix/Experimental/Texture/Texture.hpp"

#include "Helix/IO/Import/Model/ModelImporter2.hpp"

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
    ModelImporter2::init();











    hlx::ModelImporter2 test{};
    auto model = test.import(R"(models/backpack/scene.gltf)");















    auto scene = std::make_shared<Scene>();

    auto observer = scene->create_entity();
    auto& camera = Registry::add_component<CameraComponent>(observer);
    auto& cameraTransform = Registry::get_component<Transform>(observer);
    cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 3.0f });



    auto backpackObject = scene->create_entity();

    for (const auto& mesh : model->meshes)
    {
        auto obj = scene->create_entity();
        //backpackObject.

        auto& meshRenderer = Registry::add_component<MeshRendererComponent>(obj);

        meshRenderer.mesh = mesh;
        meshRenderer.material = model->materialMap[mesh];
    }









    std::vector<std::tuple<LightComponent, Vector3f>> lights{};
    lights.resize(32);
    LightComponent l{};
    l.color = Vector3f{ 0.01f, 0.01f, 0.01f };
    lights[0] = std::make_tuple(l, Vector3f{ 0.0f, 0.0f, 0.0f });





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
        auto group = Registry::view<Transform, MeshRendererComponent>();
        group.each([](auto entity, Transform& transform, MeshRendererComponent& meshRenderer)
            {
                Renderer::render(meshRenderer.mesh, meshRenderer.material, transform);
            });
        
        Renderer::finish();



		window->refresh();
        frametimes.push_back(Time::delta());
	}

    float avgFrameTime = std::accumulate(frametimes.begin(), frametimes.end(), 0.0f) / static_cast<float>(frametimes.size());
    std::cout << "Average frametime: " << avgFrameTime;

    return 0;
}
