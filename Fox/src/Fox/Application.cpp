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
        
        gfx::Geometry::init();
        io::ModelImporter::init();
        gfx::Renderer::init();
    }
    Application::~Application()
    {

    }

    int Application::run()
    {
        //Scene creation and camera setup
        auto  scene           = std::make_shared<scn::Scene>();

        auto& observer        = scene->create_actor();
        auto& camera          = observer.add_component<ecs::CameraComponent>(16.0f / 9.0f).get();
        auto& cameraTransform = observer.get_component<ecs::TransformComponent>().get();

        cameraTransform.translate(fox::Vector3f{ 0.0f, 1.0f, 8.0f });





        //Loading models
        auto& helmetActor           = scene->create_actor();
        auto& helmetTransform       = helmetActor.get_component<ecs::TransformComponent>().get();
        auto  helmetModel           = io::ModelImporter::import2("models/helmet/glTF/DamagedHelmet.gltf");

        model_to_scene_graph(*scene, helmetActor, *helmetModel, helmetModel->nodes.at(helmetModel->rootNode));
        helmetTransform.translate({ 0.0f, 1.0f, 0.0f });


        const auto& defaultAlbedo   = gfx::api::texture_from_file("textures/albedo.png");
        const auto& defaultNormal   = gfx::api::texture_from_file("textures/normal.png");
        const auto& defaultARM      = gfx::api::texture_from_file("textures/arm.png");
        const auto& defaultEmissive = gfx::api::texture_from_file("textures/emissive.png");

        auto defaultMaterial        = std::make_shared<gfx::Material>();
        defaultMaterial->albedo     = defaultAlbedo;
        defaultMaterial->normal     = defaultNormal;
        defaultMaterial->arm        = defaultARM;
        defaultMaterial->emissive   = defaultEmissive;

        auto& floorActor            = scene->create_actor();
        auto& fatc                  = floorActor.get_component<ecs::TransformComponent>().get();
        auto& famfc                 = floorActor.add_component<ecs::MeshFilterComponent>().get();

        famfc.mesh       = gfx::Geometry::Plane::mesh();
        famfc.material   = defaultMaterial;
        fatc.translate(fox::Vector3f{ 0.0f, -1.0f, 0.0f });
        fatc.rotate(fox::Vector3f{ -90.0f, 0.0f, 0.0f });
        fatc.dilate(fox::Vector3f{ 10.0f });





        //Skybox setup
        const fox::Vector2u skyboxDimensions{ 2048, 2048 };
        std::array<std::filesystem::path, 6> skyboxImageFiles
        {
            "textures/skybox_space2/right.png", 
            "textures/skybox_space2/left.png",
            "textures/skybox_space2/top.png",
            "textures/skybox_space2/bottom.png",
            "textures/skybox_space2/front.png",
            "textures/skybox_space2/back.png",
        };
        gfx::CubemapTexture::Layout cubemapLayout
        {
            gfx::api::image_from_file(skyboxImageFiles.at(0), fox::Image::Layout::RGB8), 
            gfx::api::image_from_file(skyboxImageFiles.at(1), fox::Image::Layout::RGB8),
            gfx::api::image_from_file(skyboxImageFiles.at(2), fox::Image::Layout::RGB8),
            gfx::api::image_from_file(skyboxImageFiles.at(3), fox::Image::Layout::RGB8),
            gfx::api::image_from_file(skyboxImageFiles.at(4), fox::Image::Layout::RGB8),
            gfx::api::image_from_file(skyboxImageFiles.at(5), fox::Image::Layout::RGB8),
        };

        auto skybox = std::make_shared<gfx::CubemapTexture>(skyboxDimensions, cubemapLayout);



















        namespace gl = gfx::api::gl;

        Time::reset();
        fox::CyclicBuffer<fox::float32_t, 128> frametimes{};
        std::array<std::tuple<fox::Light, fox::Vector3f>, 32u> lights
        {
            std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 0.4f, 0.4f, 0.4f }, 20.0f }, fox::Vector3f{ -2.0f,  6.0f, -1.0f }),
            std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 0.1f, 0.2f, 1.0f }, 20.0f }, fox::Vector3f{ -3.0f,  0.0f,  3.0f }), 
            std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 1.0f, 0.4f, 0.0f }, 20.0f }, fox::Vector3f{  3.0f,  0.0f,  3.0f }), 
        };





        const auto& move_camera = [&]
        {
            auto speed{ 5.0f * Time::delta() };

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
                static fox::Vector3f rotation{};

                auto& ct  = observer.get_component<ecs::TransformComponent>().get();
                const auto& cpr = input::cursor_position_relative() / 10.0f;

                rotation += fox::Vector3f{ cpr.y, cpr.x, 0.0f };

                cameraTransform.rotation = fox::Quaternion{ glm::radians(rotation) };
            }
        };
        const auto& rotate_helmet = [&]
            {
                helmetTransform.rotate(fox::Vector3f{ 0.0f, 10.0f * Time::delta(), 0.0f });
            };
        const auto& render_lights_debug = [&](std::span<const std::tuple<fox::Light, fox::Vector3f>> lights, fox::uint32_t amount)
            {
                for (const auto& i : std::ranges::iota_view(0u, amount))
                {
                    const auto& [l, p] = lights[i];

                    fox::Transform t{};
                    t.position = p;
                    t.dilate({ 0.1f, 0.1f, 0.1f });

                    gfx::Renderer::render_debug(t);
                }
            };

        while (!m_window->should_close())
        {
            fox::Time::update();
            m_window->poll_events();





            move_camera();
            rotate_helmet();





            gfx::RenderInfo renderInfo{ {camera, cameraTransform}, lights, skybox };

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

            render_lights_debug(lights, 3);

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
