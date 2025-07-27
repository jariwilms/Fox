import std;
import fox;

using namespace fox;

static void model_to_scene_graph(fox::scene& scene, fox::actor& actor, gfx::model& model, gfx::model::node& node)
{
    auto& tc = actor.get_component<ecs::transform_component  >().value();
    auto& mc = actor.add_component<ecs::mesh_filter_component>().value();

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
static auto transform_product   (std::shared_ptr<fox::scene> scene, const fox::relationship& relation, const fox::transform& transform) -> fox::transform
{
    if (!relation.parent) return transform;

    const auto& parent = scene->find_actor(*relation.parent);
    const auto& rc     = parent.get_component<ecs::relationship_component>().value();
    const auto& tc     = parent.get_component<ecs::transform_component>   ().value();

    return transform_product(scene, rc, tc) * transform;
}

int main()
{
    fox::initialize();



    auto  scene                 = std::make_shared<fox::scene>();

    auto& observer              = scene->create_actor();
    auto& camera                = observer.add_component<ecs::camera_component>(16.0f / 9.0f, 82.0f).value();
    auto& cameraTransform       = observer.get_component<ecs::transform_component>().value();
    cameraTransform.translate_by(fox::vector3f{ 0.0f, 1.0f, 2.0f });

    auto& helmetActor           = scene->create_actor();
    auto& helmetTransform       = helmetActor.get_component<ecs::transform_component>().value();
    auto  helmetModel           = io::model_importer::import2("models/helmet/glTF/DamagedHelmet.gltf");
    model_to_scene_graph(*scene, helmetActor, *helmetModel, helmetModel->nodes.at(fox::size_t{ 0u }));
    helmetTransform.translate_by({ 0.0f, 1.0f, 0.0f });

    const auto& defaultAlbedo   = io::load<io::asset_e::texture2d>("textures/albedo.png");
    const auto& defaultNormal   = io::load<io::asset_e::texture2d>("textures/normal.png");
    const auto& defaultARM      = io::load<io::asset_e::texture2d>("textures/arm.png");
    const auto& defaultEmissive = io::load<io::asset_e::texture2d>("textures/emissive.png");

    auto defaultMaterial        = std::make_shared<gfx::material>();
    defaultMaterial->albedo     = defaultAlbedo;
    defaultMaterial->normal     = defaultNormal;
    defaultMaterial->arm        = defaultARM;
    defaultMaterial->emissive   = defaultEmissive;

    auto& floorActor            = scene->create_actor();
    auto& fatc                  = floorActor.get_component<ecs::transform_component> ().value();
    auto& famfc                 = floorActor.add_component<ecs::mesh_filter_component>().value();
    famfc.mesh                  = gfx::geometry::plane;
    famfc.material              = defaultMaterial;
    fatc                        = fox::transform{ fox::vector3f{ 0.0f, -1.0f, 0.0f }, fox::vector3f{ -90.0f, 0.0f, 0.0f }, fox::vector3f{ 50.0f } };

    auto& boxActor              = scene->create_actor();
    auto& batc                  = boxActor.get_component<ecs::transform_component> ().value();
    auto& bamfc                 = boxActor.add_component<ecs::mesh_filter_component>().value();
    bamfc.mesh                  = gfx::geometry::cube;
    bamfc.material              = defaultMaterial;
    batc                        = fox::transform{ fox::vector3f{ 3.0f, 1.0f, -5.0f }, fox::vector3f{ 0.0f, 30.0f, 0.0f }, fox::vector3f{ 4.0f } };

    const auto skyboxDimensions = fox::vector2u{ 2048u };
    const auto skyboxImageFiles = std::array<const std::filesystem::path, fox::size_t{ 6u }>
    {
        "textures/skybox_space2/right.png" , 
        "textures/skybox_space2/left.png"  ,
        "textures/skybox_space2/top.png"   ,
        "textures/skybox_space2/bottom.png",
        "textures/skybox_space2/front.png" ,
        "textures/skybox_space2/back.png"  ,
    };
    const auto cubemapFaces     = std::array<const fox::image, fox::size_t{ 6u }>
    {
        io::load<io::asset_e::image>(skyboxImageFiles.at(0), fox::image::format_e::rgb8), 
        io::load<io::asset_e::image>(skyboxImageFiles.at(1), fox::image::format_e::rgb8), 
        io::load<io::asset_e::image>(skyboxImageFiles.at(2), fox::image::format_e::rgb8), 
        io::load<io::asset_e::image>(skyboxImageFiles.at(3), fox::image::format_e::rgb8), 
        io::load<io::asset_e::image>(skyboxImageFiles.at(4), fox::image::format_e::rgb8), 
        io::load<io::asset_e::image>(skyboxImageFiles.at(5), fox::image::format_e::rgb8), 
    };
    auto skybox                 = gfx::cubemap::create(gfx::cubemap::format_e::rgb8_unorm, skyboxDimensions, cubemapFaces);

    auto lights                 = std::vector<std::tuple<fox::light, fox::vector3f>>
    {
        std::make_tuple(fox::light{ fox::light::type_e::point, fox::vector3f{ 1.0f, 0.5f, 0.0f } * fox::vector3f{ 400.0f }, 0.0f }, fox::vector3f{ 6.0f, 1.0f, 4.5f }), 
    };

    auto move_camera            = [&]
        {
            auto speed = fox::float32_t{ fox::time::delta() * 5.0f };

            if (input::key_active(input::key_e::escape      )) window::close();
            if (input::key_active(input::key_e::left_shift  )) speed *= 10.0f;
            if (input::key_active(input::key_e::left_control)) speed /=  5.0f;
            if (input::key_active(input::key_e::w           )) cameraTransform.position += cameraTransform.forward() * speed;
            if (input::key_active(input::key_e::a           )) cameraTransform.position -= cameraTransform.right  () * speed;
            if (input::key_active(input::key_e::s           )) cameraTransform.position -= cameraTransform.forward() * speed;
            if (input::key_active(input::key_e::d           )) cameraTransform.position += cameraTransform.right  () * speed;
            if (input::key_active(input::key_e::e           )) cameraTransform.position += cameraTransform.up     () * speed;
            if (input::key_active(input::key_e::q           )) cameraTransform.position -= cameraTransform.up     () * speed;

            if (input::button_active(input::button_e::right_mouse))
            {
                static auto rotation = fox::vector3f{};
                const  auto cpr      = input::cursor_position_delta() / 10.0f;

                rotation += fox::vector3f{ cpr.y, cpr.x, 0.0f };
                cameraTransform.rotation = fox::quaternion4f{ glm::radians(rotation) };
            }
        };
    auto rotate_helmet          = [&]
        {
            helmetTransform.rotate_by(fox::vector3f{ 0.0f, 10.0f * fox::time::delta(), 0.0f });
        };
    auto render_lights_debug    = [&](std::span<const std::tuple<fox::light, fox::vector3f>> lights)
        {
            std::ranges::for_each(lights, [](const auto& tuple)
                {
                    const auto& [light, position] = tuple;
                    gfx::renderer::render_debug(fox::transform{ position, fox::vector3f{}, fox::vector3f{ 0.1f, 0.1f, 0.1f }});
                });
        };



    

    fox::time::reset();
    auto frametimes = fox::circular_buffer<fox::float32_t, fox::size_t{ 144u }>{};

    while (!window::should_close())
    {
        fox::time::update();
        window::poll_events();

        move_camera();
        rotate_helmet();

        auto renderInfo = gfx::render_info{ window::dimensions(), camera, cameraTransform, lights, skybox };
        gfx::renderer::start(renderInfo);

        auto view = ecs::registry::view<ecs::relationship_component, ecs::transform_component, ecs::mesh_filter_component>();
        view.each([&](auto, const ecs::relationship_component& r, const ecs::transform_component& t, const ecs::mesh_filter_component& m)
            {
                const auto& relationship = r.value();
                const auto& transform    = t.value();
                const auto& meshFilter   = m.value();
                const auto& mesh         = meshFilter.mesh;
                const auto& material     = meshFilter.material;

                if (!mesh || !material) return;

                auto transformProduct = transform_product(scene, relationship, transform);
                gfx::renderer::render(mesh, material, transformProduct);
            });

        render_lights_debug(lights);

        gfx::renderer::finish();

        window::swap_buffers();
        frametimes.push_back(fox::time::delta());
    }



    auto averageFrameTime = std::ranges::fold_left(frametimes, fox::float32_t{ 0.0f }, std::plus<fox::float32_t>{}) / frametimes.size();

    std::system("CLS");
    std::println("Average frame rate: {}", 1.0f / averageFrameTime);
    std::println("Average frame time: {}",        averageFrameTime);



    return 0;
}
