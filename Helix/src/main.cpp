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

std::shared_ptr<Actor> dfs_test(Scene* scene, std::shared_ptr<Model> model, std::shared_ptr<Actor> parent, Model::Node* node)
{
    auto actor = scene->create_actor();
    scene->set_parent(parent, actor);
    
    auto& transformComponent = actor->get_component<TransformComponent>();
    if (node->localTransform.has_value())
    {
        Transform& t = transformComponent;
        t = node->localTransform.value();
    }

    if (node->meshPrimitive.has_value())
    {
        const auto& mp = node->meshPrimitive.value();
        auto& meshR = actor->add_component<MeshRendererComponent>();
        meshR.mesh = model->meshes[mp.meshIndex];
        meshR.material = model->materials[mp.materialIndex];
    }

    for (auto& child : node->children)
    {
        dfs_test(scene, model, actor, &child);
    }

    return actor;
};


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





    auto scene = std::make_shared<Scene>();
    auto observer = scene->create_actor();
    auto& camera = observer->add_component<CameraComponent>();
    auto& cameraTransform = observer->get_component<TransformComponent>();
    cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 3.0f });





    hlx::ModelImporter2 testImporter{};
    auto model = testImporter.import(R"(models/backpack/scene.gltf)");
    auto modelActor = scene->create_actor();



    auto res = dfs_test(scene.get(), model, nullptr, model->rootNode.get());







    //TODO: fix component include in gameobject!!!




    std::vector<std::tuple<Light, Vector3f>> lights{};
    lights.resize(32);
    Light l{};
    l.color = Vector3f{ 0.01f, 0.01f, 0.01f };
    lights[0] = std::make_tuple(l, Vector3f{ 0.0f, 0.0f, 0.0f });





    Time::reset();
    CyclicBuffer<float, 128> frametimes{};
	while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(window->native_window())))
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

        //The render system starts running here and submits all models/meshes to the renderer
        //So, TODO: RenderSystem::update, which calls the code below
        Renderer::start(RendererAPI::RenderInfo{ camera, cameraTransform, lights });

        auto group = Registry::view<TransformComponent, MeshRendererComponent>();
        group.each([](auto entity, TransformComponent& transform, MeshRendererComponent& meshRenderer)
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
