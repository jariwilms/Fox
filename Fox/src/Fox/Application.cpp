#include "stdafx.hpp"

#include "Application.hpp"

#include "Fox/Core/Library/Container/CyclicBuffer.hpp"
#include "Fox/Core/Library/Image/Image.hpp"
#include "Fox/Core/Library/Time/Time.hpp"
#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/ECS/Components/Components.hpp"
#include "Fox/Input/Input.hpp"
#include "Fox/IO/Import/Model/ModelImporter.hpp"
#include "Fox/IO/IO.hpp"
#include "Fox/Rendering/Geometry/Geometry.hpp"
#include "Fox/Rendering/Model/Model.hpp"
#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"
#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/Utility/Utility.hpp"
#include "Fox/Scene/Actor.hpp"
#include "Fox/Scene/Scene.hpp"
#include "Fox/Window/WindowManager.hpp"

namespace fox
{
    static void           model_to_scene_graph(scn::Scene& scene, scn::Actor& actor, const gfx::Model& model, const gfx::Model::Node& node)
    {
        auto& tc = actor.get_component<ecs::TransformComponent>().get();
        tc = node.localTransform;

        auto& mf = actor.add_component<ecs::MeshFilterComponent>().get();
        if (node.meshIndex)     mf.mesh     = model.meshes.at(node.meshIndex.value());
        if (node.materialIndex) mf.material = model.materials.at(node.materialIndex.value());

        for (auto& childIndex : node.children)
        {
            auto& childActor = scene.create_actor();
            scene.set_parent(actor, childActor);

            model_to_scene_graph(scene, childActor, model, model.nodes.at(childIndex));
        }
    }
    static fox::Transform transform_product(const scn::Scene& scene, const Relationship& relation, const fox::Transform& transform)
    {
        if (!relation.parent) return transform;

        const auto& parent = scene.find_actor(relation.parent.value());
        const auto& rel    = parent.get_component<ecs::RelationshipComponent>().get();
        const auto& trs    = parent.get_component<ecs::TransformComponent>().get();

        return transform_product(scene, rel, trs) * transform;
    }

    Application::Application(int argc, char* argv[])
    {
        m_window = wnd::WindowManager::create("Window", "Fox", fox::Vector2u{ 1280u, 720u });
        
        io::ModelImporter::init();
        gfx::Geometry::init();
        gfx::Renderer::init();
    }
    Application::~Application()
    {

    }

    int Application::run()
    {
        auto  scene           = std::make_shared<scn::Scene>();
        auto  model           = io::ModelImporter::import2("models/cube/Cube.gltf");
        auto& observer        = scene->create_actor();
        auto& camera          = observer.add_component<ecs::CameraComponent>(16.0f / 9.0f).get();
        auto& cameraTransform = observer.get_component<ecs::TransformComponent>().get();

        cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 5.0f });

        auto& actor = scene->create_actor();
        model_to_scene_graph(*scene, actor, *model, model->nodes.at(model->rootNode));



        namespace gl = gfx::api::gl;

        const auto& shaders          = gfx::api::shaders_from_binaries<gfx::Shader>("shaders/compiled/test.vert.spv", "shaders/compiled/test.frag.spv");
              auto  testPipeline     = std::make_shared<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertexShader = shaders.at(0), .fragmentShader = shaders.at(1) });

              auto  texture          = gfx::api::texture_from_file("images/anna.png");

        const auto& renderInfo       = gfx::RenderInfo{ { camera, cameraTransform }, {} };
        const auto& modelMatrix      = fox::Matrix4f{ 1.0f };
        const auto& viewMatrix       = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward(), cameraTransform.up());
        const auto& projectionMatrix = camera.projection().matrix();

              auto  matricesBuffer   = std::make_shared<gfx::UniformBuffer<gfx::UMatrices>>();
              auto  cameraBuffer     = std::make_shared<gfx::UniformBuffer<gfx::UCamera>>();





        Time::reset();
        fox::CyclicBuffer<fox::float32_t, 128> frametimes{};
        std::array<std::tuple<fox::Light, fox::Vector3f>, 32u> lights{};
        gl::clear_color(fox::Vector4f{ 0.08f, 0.08f, 0.08f, 1.0f });

        while (!m_window->should_close())
        {
            Time::update();
            m_window->poll_events();



            auto speed{ 10.0f * Time::delta() };
            if (input::key_pressed(input::key::Escape))      m_window->close();
            if (input::key_pressed(input::key::LeftShift))   speed *= 10.0f;
            if (input::key_pressed(input::key::LeftControl)) speed /=  5.0f;
            if (input::key_pressed(input::key::W)) cameraTransform.position += cameraTransform.forward() * speed;
            if (input::key_pressed(input::key::A)) cameraTransform.position -= cameraTransform.right()   * speed;
            if (input::key_pressed(input::key::S)) cameraTransform.position -= cameraTransform.forward() * speed;
            if (input::key_pressed(input::key::D)) cameraTransform.position += cameraTransform.right()   * speed;
            if (input::key_pressed(input::key::E)) cameraTransform.position += cameraTransform.up()      * speed;
            if (input::key_pressed(input::key::Q)) cameraTransform.position -= cameraTransform.up()      * speed;
            
            if (input::button_pressed(input::btn::RightMouse))
            {
                      auto& ct  = observer.get_component<ecs::TransformComponent>().get();
                const auto& cpr = input::cursor_position_relative() / 10.0f;

                ct.rotate({cpr.y, cpr.x, 0.0f});
                ct.rotation.z = 0.0f;
            }





            gfx::RenderInfo renderInfo{ {camera, cameraTransform}, lights };

            gfx::Renderer::start(renderInfo);
            const auto& view = reg::view<ecs::RelationshipComponent, ecs::TransformComponent, ecs::MeshFilterComponent>();
            view.each([&](auto entity, const ecs::RelationshipComponent& rlc, const ecs::TransformComponent& tc, const ecs::MeshFilterComponent& mfc)
                {
                    const auto& relation   = rlc.get();
                    const auto& transform  = tc.get();
                    const auto& meshFilter = mfc.get();
                    const auto& mesh       = meshFilter.mesh;
                    const auto& material   = meshFilter.material;
                    
                    if (!mesh || !material) return;

                    const auto& transformProduct = transform_product(*scene, relation, transform);
                    gfx::Renderer::render(mesh, material, transformProduct);
                });
            gfx::Renderer::finish();





            m_window->swap_buffers();
            frametimes.push_back(Time::delta());
        }



        const auto& avgFrameTime = std::accumulate(frametimes.begin(), frametimes.end(), 0.0f) / static_cast<fox::float32_t>(frametimes.size());

        std::system("CLS");
        std::cout << "Average frame time: " <<        avgFrameTime << '\n';
        std::cout << "Average frame rate: " << 1.0f / avgFrameTime << '\n';



        return 0;
    }
}
