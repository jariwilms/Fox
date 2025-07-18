import std;
import fox.core.image;
import fox.core.time;
import fox.core.transform;
import fox.core.types;
import fox.ecs.components;
import fox.ecs.registry;
import fox.input;
import fox.io.model_importer;
import fox.io;
import fox.rendering;
import fox.scene.actor;
import fox.scene;
import fox.window;
import fox.rendering.renderer;

using namespace fox;

static void model_to_scene_graph(fox::scene::Scene& scene, fox::scene::Actor& actor, gfx::Model& model, gfx::Model::Node& node)
{
    auto& tc = actor.get_component<ecs::TransformComponent> ().get();
    auto& mc = actor.add_component<ecs::MeshFilterComponent>().get();

    tc = node.transform;

    if (node.mesh)     mc.mesh     = model.meshes   .at(*node.mesh    );
    if (node.material) mc.material = model.materials.at(*node.material);
    
    std::ranges::for_each(node.children, [&](auto child)
        {
            auto& childActor = scene.create_actor();

            scene.set_parent(actor, childActor);
            model_to_scene_graph(scene, childActor, model, model.nodes.at(child));
        });
}
static auto transform_product   (std::shared_ptr<scene::Scene> scene, const fox::Relationship& relation, const fox::Transform& transform) -> fox::Transform
{
    if (!relation.parent) return transform;

    const auto& parent = scene->find_actor(*relation.parent);
    const auto& rc     = parent.get_component<ecs::RelationshipComponent>().get();
    const auto& tc     = parent.get_component<ecs::TransformComponent>   ().get();

    return transform_product(scene, rc, tc) * transform;
}

int main()
{
    auto window_ = interface::Window::create("Fox", fox::Vector2u{ 1280u, 720u });

    gfx::geometry     ::init();
    io ::ModelImporter::init();
    gfx::renderer     ::init();


    auto  scene                 = std::make_shared<scene::Scene>();

    auto& observer              = scene->create_actor();
    auto& camera                = observer.add_component<ecs::CameraComponent>(16.0f / 9.0f, 82.0f).get();
    auto& cameraTransform       = observer.get_component<ecs::TransformComponent>().get();
    cameraTransform.translate_by(fox::Vector3f{ 0.0f, 1.0f, 2.0f });

    auto& helmetActor           = scene->create_actor();
    auto& helmetTransform       = helmetActor.get_component<ecs::TransformComponent>().get();
    auto  helmetModel           = io::ModelImporter::import2("models/helmet/glTF/DamagedHelmet.gltf");
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
    auto& fatc                  = floorActor.get_component<ecs::TransformComponent> ().get();
    auto& famfc                 = floorActor.add_component<ecs::MeshFilterComponent>().get();
    famfc.mesh                  = gfx::geometry::plane;
    famfc.material              = defaultMaterial;
    fatc                        = fox::Transform{ fox::Vector3f{ 0.0f, -1.0f, 0.0f }, fox::Vector3f{ -90.0f, 0.0f, 0.0f }, fox::Vector3f{ 50.0f } };

    auto& boxActor              = scene->create_actor();
    auto& batc                  = boxActor.get_component<ecs::TransformComponent> ().get();
    auto& bamfc                 = boxActor.add_component<ecs::MeshFilterComponent>().get();
    bamfc.mesh                  = gfx::geometry::cube;
    bamfc.material              = defaultMaterial;
    batc                        = fox::Transform{ fox::Vector3f{ 3.0f, 1.0f, -5.0f }, fox::Vector3f{ 0.0f, 30.0f, 0.0f }, fox::Vector3f{ 4.0f } };

    const auto skyboxDimensions = fox::Vector2u{ 2048u };
    const auto skyboxImageFiles = std::array<const std::filesystem::path, fox::size_t{ 6u }>
    {
        "textures/skybox_space2/right.png" , 
        "textures/skybox_space2/left.png"  ,
        "textures/skybox_space2/top.png"   ,
        "textures/skybox_space2/bottom.png",
        "textures/skybox_space2/front.png" ,
        "textures/skybox_space2/back.png"  ,
    };
    const auto cubemapFaces     = std::array<const fox::Image, fox::size_t{ 6u }>
    {
        io::load<io::Asset::Image>(skyboxImageFiles.at(0), fox::Image::Format::RGB8), 
        io::load<io::Asset::Image>(skyboxImageFiles.at(1), fox::Image::Format::RGB8), 
        io::load<io::Asset::Image>(skyboxImageFiles.at(2), fox::Image::Format::RGB8), 
        io::load<io::Asset::Image>(skyboxImageFiles.at(3), fox::Image::Format::RGB8), 
        io::load<io::Asset::Image>(skyboxImageFiles.at(4), fox::Image::Format::RGB8), 
        io::load<io::Asset::Image>(skyboxImageFiles.at(5), fox::Image::Format::RGB8), 
    };
    auto skybox                 = gfx::Cubemap::create(gfx::Cubemap::Format::RGB8_UNORM, skyboxDimensions, cubemapFaces);

    auto lights                 = std::vector<std::tuple<fox::Light, fox::Vector3f>>
    {
        //std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 1.0f, 0.0f, 0.0f } * fox::Vector3f{ 50.0f }, 0.0f }, fox::Vector3f{ -3.0f, 8.0f, -3.0f }), 
        std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 0.1f, 0.2f, 1.0f } * fox::Vector3f{ 20.0f }, 0.0f }, fox::Vector3f{ -3.0f, 2.0f,  3.0f }), 
        //std::make_tuple(fox::Light{ fox::Light::Type::Point, fox::Vector3f{ 1.0f, 0.4f, 0.0f } * fox::Vector3f{ 20.0f }, 0.0f }, fox::Vector3f{  3.0f, 2.0f,  3.0f }), 
    };

    auto move_camera            = [&]
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

                const auto cpr = input::cursor_position_delta() / 10.0f;
                rotation += fox::Vector3f{ cpr.y, cpr.x, 0.0f };

                cameraTransform.rotation = fox::Quaternion{ glm::radians(rotation) };
            }
        };
    auto rotate_helmet          = [&]
        {
            helmetTransform.rotate_by(fox::Vector3f{ 0.0f, 10.0f * fox::time::delta(), 0.0f });
        };
    auto render_lights_debug    = [&](std::span<const std::tuple<fox::Light, fox::Vector3f>> lights)
        {
            std::ranges::for_each(lights, [](const auto& tuple)
                {
                    const auto& [light, position] = tuple;
                    gfx::renderer::render_debug(fox::Transform{ position, fox::Vector3f{}, fox::Vector3f{ 0.1f, 0.1f, 0.1f }});
                });
        };





    fox::time::reset();
    auto frametimes = fox::CircularBuffer<fox::float32_t, fox::size_t{ 144u }>{};

    while (!window_->should_close())
    {
        fox::time::update();
        window_->poll_events();

        move_camera();
        rotate_helmet();

        auto renderInfo = gfx::RenderInfo{ camera, cameraTransform, lights, skybox };
        gfx::renderer::start(renderInfo);

        auto view = registry::view<ecs::RelationshipComponent, ecs::TransformComponent, ecs::MeshFilterComponent>();
        view.each([&](auto entity, const ecs::RelationshipComponent& r, const ecs::TransformComponent& t, const ecs::MeshFilterComponent& m)
            {
                const auto& relationship = r.get();
                const auto& transform    = t.get();
                const auto& meshFilter   = m.get();
                const auto& mesh         = meshFilter.mesh;
                const auto& material     = meshFilter.material;

                if (!mesh || !material) return;

                auto transformProduct = transform_product(scene, relationship, transform);
                gfx::renderer::render(mesh, material, transformProduct);
            });

        render_lights_debug(lights);

        gfx::renderer::finish();

        window_->swap_buffers();
        frametimes.push_back(fox::time::delta());
    }



    auto averageFrameTime = std::ranges::fold_left(frametimes, fox::float32_t{ 0.0f }, std::plus<fox::float32_t>{}) / frametimes.size();

    std::system("CLS");
    std::println("Average frame rate: {}", 1.0f / averageFrameTime);
    std::println("Average frame time: {}",        averageFrameTime);



    return 0;
}
