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
#include "Fox/Rendering/Model/Model.hpp"
#include "Fox/Rendering/Utility/Utility.hpp"
#include "Fox/Scene/Scene.hpp"
#include "Fox/Window/WindowManager.hpp"
#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"

namespace fox
{
    static void model_to_scene_graph(std::shared_ptr<scn::Scene> scene, std::shared_ptr<scn::Actor> actor, const gfx::Model& model, const gfx::Model::Node& node)
    {
        auto& mrc = actor->add_component<ecs::MeshRendererComponent>();
        if (node.meshIndex)     mrc.mesh     = model.meshes.at(node.meshIndex.value());
        if (node.materialIndex) mrc.material = model.materials.at(node.materialIndex.value());

        for (auto& childIndex : node.children)
        {
            auto childActor = scene->create_actor();
            scene->set_parent(actor, childActor);

            model_to_scene_graph(scene, childActor, model, model.nodes.at(childIndex));
        }
    }
    //very inefficient
    static fox::Transform transform_product(scn::Scene& scene, scn::Actor& actor)
    {
        const auto& rc = actor.get_component<ecs::RelationshipComponent>();
        const auto& tc = actor.get_component<ecs::TransformComponent>();

        if (rc.parent)
        {
            const auto& find_actor = [](scn::Scene& scene, fox::id_t id)
                {
                    const auto& actors  = scene.actors();

                    return std::find_if(actors.begin(), actors.end(), [id](std::shared_ptr<scn::Actor> _) { return _->id() == id; });
                };
            auto it = find_actor(scene, rc.parent.value());

            if (it == scene.actors().end()) throw std::runtime_error{ "Parent actor not found!" };

            return transform_product(scene, *it->get()) * tc.transform();
        }
        else
        {
            return tc.transform();
        }

    }
    static void render_actor(scn::Scene& scene, scn::Actor& actor, gfx::UniformBuffer<gfx::UMatrices>& matrices)
    {
        const auto& view = reg::view<ecs::TransformComponent, ecs::MeshRendererComponent>();

        view.each([&](auto entity, const ecs::TransformComponent& tc, const ecs::MeshRendererComponent& mrc)
            {
                namespace gl = fox::gfx::api::gl;

                const auto& mesh     = mrc.mesh;
                const auto& material = mrc.material;

                if (!mesh || !material) return;

                const auto& matrix = transform_product(scene, actor).matrix();
                matrices.copy_tuple(offsetof(gfx::UMatrices, model), std::make_tuple(matrix));

                material->albedo->bind(0);
                material->normal->bind(1);
                material->arm->bind(2);

                mesh->vertexArray->bind();
                gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, mesh->vertexArray->index_buffer()->count());
            });
    }

    Application::Application(int argc, char* argv[])
    {
        m_window = wnd::WindowManager::create("Window", "Fox", fox::Vector2u{ 1280u, 720u });
        
        io::ModelImporter::init();
        //gfx::Geometry::init();
        //gfx::Renderer::init();
    }
    Application::~Application()
    {

    }

    int Application::run()
    {
        auto  scene           = std::make_shared<scn::Scene>();
        auto  model           = io::ModelImporter::import2("models/sponza/Sponza.gltf");
        auto  observer        = scene->create_actor();
        auto& camera          = observer->add_component<ecs::CameraComponent>().camera();
        auto& cameraTransform = observer->get_component<ecs::TransformComponent>().transform();

        cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 5.0f });

        auto actor = scene->create_actor();
        model_to_scene_graph(scene, actor, *model, model->nodes.at(model->rootNode));



        namespace gl = gfx::api::gl;

        const auto& shaders          = gfx::api::shaders_from_binaries<gfx::Shader>("shaders/compiled/test.vert.spv", "shaders/compiled/test.frag.spv");
              auto  testPipeline     = std::make_shared<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertexShader = shaders.at(0), .fragmentShader = shaders.at(1) });

        const auto& file             = io::load("images/anna.png");
        const auto& data             = file->read();
        const auto& image            = fox::Image::decode(fox::Image::Layout::RGBA8, *data);
              auto  texture          = std::make_shared<gfx::Texture2D>(gfx::Texture2D::Format::RGBA8_UNORM, image.dimensions(), image.data());

        const auto& renderInfo       = gfx::RenderInfo{ { camera, cameraTransform }, {} };
        const auto& modelMatrix      = fox::Matrix4f{ 1.0f };
        const auto& viewMatrix       = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward(), cameraTransform.up());
        const auto& projectionMatrix = camera.projection().matrix();

              auto  matricesBuffer   = std::make_shared<gfx::UniformBuffer<gfx::UMatrices>>();
              auto  cameraBuffer     = std::make_shared<gfx::UniformBuffer<gfx::UCamera>>();





        Time::reset();
        fox::CyclicBuffer<fox::float32_t, 128> frametimes{};

        gl::clear_color(fox::Vector4f{ 0.1f, 0.1f, 0.1f, 1.0f });
        //gl::enable(gl::Flags::Capability::FaceCulling);
        //gl::front_face(gl::Flags::Orientation::CounterClockwise);
        //gl::face_culling(gl::Flags::FaceCulling::Back);
        gl::enable(gl::Flags::Capability::DepthTest);
        gl::depth_function(gl::Flags::DepthFunction::Less);



        while (!m_window->should_close())
        {
            Time::update();
            m_window->poll_events();



            auto speed{ 10.0f * Time::delta() };
            if (inp::key_pressed(inp::key::LeftShift))   speed *= 10.0f;
            if (inp::key_pressed(inp::key::LeftControl)) speed /=  5.0f;
            if (inp::key_pressed(inp::key::W)) cameraTransform.position += cameraTransform.forward() * speed;
            if (inp::key_pressed(inp::key::A)) cameraTransform.position -= cameraTransform.right()   * speed;
            if (inp::key_pressed(inp::key::S)) cameraTransform.position -= cameraTransform.forward() * speed;
            if (inp::key_pressed(inp::key::D)) cameraTransform.position += cameraTransform.right()   * speed;
            if (inp::key_pressed(inp::key::E)) cameraTransform.position += cameraTransform.up()      * speed;
            if (inp::key_pressed(inp::key::Q)) cameraTransform.position -= cameraTransform.up()      * speed;

            if (inp::button_pressed(inp::btn::RightMouse)) //RMB
            {
                static fox::Vector3f rotation{};
                const auto& cpr = inp::cursor_position_relative() / 10.0f;

                rotation += fox::Vector3f{ cpr.y, cpr.x, 0.0f };

                cameraTransform.rotation = fox::Quaternion{ glm::radians(rotation) };
            }



            gl::clear(gl::Flags::Buffer::Mask::ColorBuffer | gl::Flags::Buffer::Mask::DepthBuffer);

            const auto& viewMatrix = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward(), cameraTransform.up());

            auto& tc = actor->get_component<ecs::TransformComponent>();
            tc.transform().scale = fox::Vector3f{ 0.008f, 0.008f, 0.008f };

            matricesBuffer->bind_index(gfx::api::gl::index_t{ 0 });
            matricesBuffer->copy_tuple(offsetof(gfx::UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
            cameraBuffer->bind_index(gfx::api::gl::index_t{ 2 });
            cameraBuffer->copy(gfx::UCamera{ Vector4f{ cameraTransform.position, 1.0f } });

            testPipeline->bind();


            //const auto& mrc = actor->get_component<ecs::MeshRendererComponent>();
            //mrc.material->albedo->bind(0);
            //mrc.material->normal->bind(1);
            //mrc.material->arm->bind(2);
            //mrc.mesh->vertexArray->bind();

            //model->materials.at(0)->albedo->bind(0);
            //model->materials.at(0)->normal->bind(1);
            //model->materials.at(0)->arm->bind(2);
            //model->meshes.at(0)->vertexArray->bind();

            //gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, model->meshes.at(0)->vertexArray->index_buffer()->count());
            //gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, mrc.mesh->vertexArray->index_buffer()->count());
            render_actor(*scene, *actor, *matricesBuffer);





            m_window->swap_buffers();
            frametimes.push_back(Time::delta());
        }

        const auto& avgFrameTime = std::accumulate(frametimes.begin(), frametimes.end(), 0.0f) / static_cast<fox::float32_t>(frametimes.size());
        std::system("CLS");
        std::cout << "Average frame time: " << avgFrameTime << '\n';
        std::cout << "Average frame rate: " << 1.0f / avgFrameTime << '\n';



        return 0;
    }
}
