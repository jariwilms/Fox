#include <stdafx.hpp>

#include <fox/application.hpp>
#include <fox/core/image/image.hpp>
#include <fox/core/json/json.hpp>
#include <fox/core/time/time.hpp>
#include <fox/core/transform/transform.hpp>
#include <fox/core/types/collection/circular_buffer.hpp>
#include <fox/ecs/components/components.hpp>
#include <fox/input/input.hpp>
#include <fox/io/import/model/model_importer.hpp>
#include <fox/io/io.hpp>
#include <fox/rendering/base/shader/utility.hpp>
#include <fox/rendering/renderer/renderer.hpp>
#include <fox/rendering/rendering.hpp>
#include <fox/scene/actor.hpp>
#include <fox/scene/scene.hpp>

namespace fox
{
    static void model_to_scene_graph(scene::Scene& scene, scene::Actor& actor, const gfx::Model& model, const gfx::Model::Node& node)
    {
        auto& tc = actor.get_component<ecs::TransformComponent>().get();
        tc = node.transform;

        auto& mf = actor.add_component<ecs::MeshFilterComponent>().get();
        if (node.mesh)     mf.mesh     = model.meshes.at(*node.mesh);
        if (node.material) mf.material = model.materials.at(*node.material);

        for (auto& childIndex : node.children)
        {
            auto& childActor = scene.create_actor();
            scene.set_parent(actor, childActor);

            model_to_scene_graph(scene, childActor, model, model.nodes.at(childIndex));
        }
    }
    static auto transform_product   (const scene::Scene& scene, const Relationship& relation, const fox::Transform& transform) -> fox::Transform
    {
        if (!relation.parent) return transform;

        const auto& parent = scene.find_actor(*relation.parent);
        const auto& rel    = parent.get_component<ecs::RelationshipComponent>().get();
        const auto& trs    = parent.get_component<ecs::TransformComponent>().get();

        return transform_product(scene, rel, trs) * transform;
    }

    Application::Application(fox::int32_t argc, fox::char_t* argv[])
    {
        window_ = interface::Window::create("Fox", fox::Vector2u{ 1280u, 720u });

        gfx::geometry     ::init();
        io ::ModelImporter::init();
        gfx::Renderer     ::init();
    }

    int Application::run()
    {
        //Scene creation and camera setup
        auto  scene           = std::make_shared<scene::Scene>();

        auto& observer        = scene->create_actor();
        auto& camera          = observer.add_component<ecs::CameraComponent>(16.0f / 9.0f, 82.0f).get();
        auto& cameraTransform = observer.get_component<ecs::TransformComponent>().get();

        cameraTransform.translate_by(fox::Vector3f{ 0.0f, 1.0f, 2.0f });





        //Loading models
        auto& helmetActor           = scene->create_actor();
        auto& helmetTransform       = helmetActor.get_component<ecs::TransformComponent>().get();
        auto  helmetModel           = io::ModelImporter::import("models/helmet/glTF/DamagedHelmet.gltf");

        model_to_scene_graph(*scene, helmetActor, *helmetModel, helmetModel->nodes.at(fox::size_t{ 0u }));
        helmetTransform.translate_by({ 0.0f, 1.0f, 0.0f });

        const auto& defaultAlbedo   = io::load<io::Asset::Texture2D>("textures/albedo.png");
        const auto& defaultNormal   = io::load<io::Asset::Texture2D>("textures/normal.png");
        const auto& defaultARM      = io::load<io::Asset::Texture2D>("textures/arm.png");
        const auto& defaultEmissive = io::load<io::Asset::Texture2D>("textures/emissive.png");

        auto defaultMaterial        = std::make_shared<gfx::Material>();
        defaultMaterial->albedo     = defaultAlbedo;
        defaultMaterial->normal     = defaultNormal;
        defaultMaterial->arm        = defaultARM;
        defaultMaterial->emissive   = defaultEmissive;

        auto& floorActor            = scene->create_actor();
        auto& fatc                  = floorActor.get_component<ecs::TransformComponent>().get();
        auto& famfc                 = floorActor.add_component<ecs::MeshFilterComponent>().get();
        famfc.mesh                  = gfx::geometry::plane;
        famfc.material              = defaultMaterial;
        fatc                        = fox::Transform{ fox::Vector3f{ 0.0f, -1.0f, 0.0f }, fox::Vector3f{ -90.0f, 0.0f, 0.0f }, fox::Vector3f{ 50.0f } };

        auto& boxActor              = scene->create_actor();
        auto& batc                  = boxActor.get_component<ecs::TransformComponent>().get();
        auto& bamfc                 = boxActor.add_component<ecs::MeshFilterComponent>().get();
        bamfc.mesh                  = gfx::geometry::cube;
        bamfc.material              = defaultMaterial;
        batc                        = fox::Transform{ fox::Vector3f{ 3.0f, 1.0f, -5.0f }, fox::Vector3f{ 0.0f, 30.0f, 0.0f }, fox::Vector3f{ 4.0f } };



        

        //Skybox setup
        const fox::Vector2u skyboxDimensions{ 2048u, 2048u };
        std::array<std::filesystem::path, 6u> skyboxImageFiles
        {
            "textures/skybox_space2/right.png", 
            "textures/skybox_space2/left.png",
            "textures/skybox_space2/top.png",
            "textures/skybox_space2/bottom.png",
            "textures/skybox_space2/front.png",
            "textures/skybox_space2/back.png",
        };
        std::array<fox::Image, 6u> cubemapFaces
        {
            io::load<io::Asset::Image>(skyboxImageFiles.at(0), fox::Image::Format::RGB8), 
            io::load<io::Asset::Image>(skyboxImageFiles.at(1), fox::Image::Format::RGB8), 
            io::load<io::Asset::Image>(skyboxImageFiles.at(2), fox::Image::Format::RGB8), 
            io::load<io::Asset::Image>(skyboxImageFiles.at(3), fox::Image::Format::RGB8), 
            io::load<io::Asset::Image>(skyboxImageFiles.at(4), fox::Image::Format::RGB8), 
            io::load<io::Asset::Image>(skyboxImageFiles.at(5), fox::Image::Format::RGB8), 
        };

        auto skybox = gfx::Cubemap::create(gfx::Cubemap::Format::RGB8_UNORM, skyboxDimensions, cubemapFaces);





        //Lights
        std::vector<std::tuple<fox::Light, fox::Vector3f>> lights
        {
            //std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 1.0f, 0.0f, 0.0f } * fox::Vector3f{ 50.0f }, 0.0f }, fox::Vector3f{ -3.0f, 8.0f, -3.0f }), 
            std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 0.1f, 0.2f, 1.0f } * fox::Vector3f{ 20.0f }, 0.0f }, fox::Vector3f{ -3.0f, 2.0f,  3.0f }), 
            //std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 1.0f, 0.4f, 0.0f } * fox::Vector3f{ 20.0f }, 0.0f }, fox::Vector3f{  3.0f, 2.0f,  3.0f }), 
        };





        const auto& move_camera         = [&]
        {
            auto speed{ 5.0f * fox::time::delta() };

            if (input::key_active(input::key::Escape     )) window_->close();
            if (input::key_active(input::key::LeftShift  )) speed *= 10.0f;
            if (input::key_active(input::key::LeftControl)) speed /=  5.0f;
            if (input::key_active(input::key::W          )) cameraTransform.position += cameraTransform.forward() * speed;
            if (input::key_active(input::key::A          )) cameraTransform.position -= cameraTransform.right  () * speed;
            if (input::key_active(input::key::S          )) cameraTransform.position -= cameraTransform.forward() * speed;
            if (input::key_active(input::key::D          )) cameraTransform.position += cameraTransform.right  () * speed;
            if (input::key_active(input::key::E          )) cameraTransform.position += cameraTransform.up     () * speed;
            if (input::key_active(input::key::Q          )) cameraTransform.position -= cameraTransform.up     () * speed;

            if (input::button_active(input::button::RightMouse))
            {
                static auto rotation = fox::Vector3f{};

                      auto& ct  = observer.get_component<ecs::TransformComponent>().get();
                const auto& cpr = input::cursor_position_delta() / 10.0f;

                rotation += fox::Vector3f{ cpr.y, cpr.x, 0.0f };

                cameraTransform.rotation = fox::Quaternion{ glm::radians(rotation) };
            }
        };
        const auto& rotate_helmet       = [&]
            {
                helmetTransform.rotate_by(fox::Vector3f{ 0.0f, 10.0f * fox::time::delta(), 0.0f });
            };
        const auto& render_lights_debug = [&](std::span<const std::tuple<fox::Light, fox::Vector3f>> lights, std::optional<fox::uint32_t> limit = {})
            {
                for (auto i : std::views::iota(0u, limit.value_or(lights.size())))
                {
                    const auto& [l, p] = lights[i];

                    fox::Transform t{};
                    t.position = p;
                    t.scale_by({ 0.1f, 0.1f, 0.1f });

                    gfx::Renderer::render_debug(t);
                }
            };



        fox::time::reset();
        fox::CircularBuffer<fox::float32_t, 144u> frametimes{};

        while (!window_->should_close())
        {
            fox::time::update();
            window_->poll_events();





            move_camera();
            rotate_helmet();



            //auto& l = lights.at(0);
            //auto& [_1, _2] = l;
            //_2.x = glm::cos(fox::Time::since_epoch() / 5.0f) * 20.0f;
            //_2.z = glm::sin(fox::Time::since_epoch() / 5.0f) * 20.0f;



            gfx::RenderInfo renderInfo{ camera, cameraTransform, lights, skybox };
            gfx::Renderer::start(renderInfo);

            const auto& view = registry::view<ecs::RelationshipComponent, ecs::TransformComponent, ecs::MeshFilterComponent>();
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

            render_lights_debug(lights);

            gfx::Renderer::finish();





            window_->swap_buffers();
            frametimes.push_back(fox::time::delta());
        }



        const auto& avgFrameTime = std::accumulate(frametimes.begin(), frametimes.end(), 0.0f) / static_cast<fox::float32_t>(frametimes.size());

        std::system("CLS");
        std::cout << "Average frame time: " <<        avgFrameTime << '\n';
        std::cout << "Average frame rate: " << 1.0f / avgFrameTime << '\n';



        return 0;
    }
}
