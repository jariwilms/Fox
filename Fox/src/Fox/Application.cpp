#include "stdafx.hpp"

#include "Application.hpp"

#include "Fox/Core/Library/Container/CyclicBuffer.hpp"
#include "Fox/Core/Library/Image/Image.hpp"
#include "Fox/Core/Library/Time/Time.hpp"
#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/ECS/Components/Components.hpp"
#include "Fox/Input/Input.hpp"
#include "Fox/IO/Import/Model/GLTFImporter.hpp"
#include "Fox/IO/IO.hpp"
#include "Fox/Rendering/Model/Model.hpp"
#include "Fox/Rendering/Utility/Utility.hpp"
#include "Fox/Scene/Scene.hpp"
#include "Fox/Window/WindowManager.hpp"

namespace fox
{
    //Transform transform_product(TransformComponent& tc)
    //{
    //    const auto& owner = tc.owner;
    //    const auto& rc = Registry::get_component<RelationshipComponent>(owner.id());

    //    if (!rc.parent.has_value()) return tc;

    //    auto& ptc = Registry::get_component<TransformComponent>(rc.parent.value());
    //    return transform_product(ptc) * tc;
    //};
    //std::shared_ptr<Actor> model_to_scene_graph(Scene* scene, std::shared_ptr<gfx::Model> model, std::shared_ptr<Actor> parent, gfx::Model::Node* node)
    //{
    //    auto actor = scene->create_actor();
    //    scene->set_parent(parent, actor);

    //    auto& transformComponent = actor->get_component<TransformComponent>();
    //    if (node->localTransform.has_value())
    //    {
    //        Transform& t = transformComponent;
    //        t = node->localTransform.value();
    //    }

    //    if (node->meshPrimitive.has_value())
    //    {
    //        const auto& mp = node->meshPrimitive.value();
    //        auto& meshR = actor->add_component<MeshRendererComponent>();
    //        meshR.mesh = model->meshes[mp.meshIndex];
    //        meshR.material = model->materials[mp.materialIndex];
    //    }

    //    for (auto& child : node->children)
    //    {
    //        model_to_scene_graph(scene, model, actor, &child);
    //    }

    //    return actor;
    //};

    //static void model_to_scene_graph(fox::scene::Scene& scene, fox::scn::Actor& parent, const gfx::Model& model, const gfx::Model::Node& node)
    //{
    //    throw std::logic_error{ "Not implemented." };

    //    auto actor = scene.create_actor();
    //    
    //    //RelationshipComponent rc = parent.get_component<RelationshipComponent>();
    //    //rc.children.emplace_back(actor->id());

    //    auto& t = actor->get_component<ecs::TransformComponent>().transform();
    //    t = node.localTransform;

    //    auto& mrc = actor->add_component<ecs::MeshRendererComponent>();
    //    if (node.meshIndex)     mrc.mesh     = model.meshes.at(node.meshIndex.value());
    //    if (node.materialIndex) mrc.material = model.materials.at(node.materialIndex.value());
    //    
    //    for (const auto& child : node.children)
    //    {
    //        model_to_scene_graph(scene, *actor, model, child);
    //    }
    //}



    Application::Application(int argc, char* argv[])
    {
        m_window = wnd::WindowManager::create("Window", "Fox", fox::Vector2u{ 1280u, 720u });
        
        //gfx::Geometry::init();
        //gfx::Renderer::init();
    }
    Application::~Application()
    {

    }

    int Application::run()
    {
        auto  scene           = std::make_shared<scn::Scene>();
        auto  model           = io::GLTFImporter::import2("models/cube/Cube.gltf");
        auto  observer        = scene->create_actor();
        auto& camera          = observer->add_component<ecs::CameraComponent>().camera();
        auto& cameraTransform = observer->get_component<ecs::TransformComponent>().transform();

        cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 5.0f });





        namespace gl = gfx::api::gl;

        const auto& shaders          = gfx::api::shaders_from_binaries<gfx::Shader>("shaders/compiled/test.vert.spv", "shaders/compiled/test.frag.spv");
              auto  testPipeline     = std::make_shared<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertexShader = shaders.at(0), .fragmentShader = shaders.at(1) });

        const auto& file             = io::load("images/anna.png");
        const auto& data             = file->read();
        const auto& image            = fox::Image::decode(fox::Image::Layout::RGBA8, *data);
              auto  texture          = std::make_shared<gfx::Texture2D>(gfx::Texture2D::Format::RGBA8_UNORM, gfx::Texture2D::Filter::Trilinear, gfx::Texture2D::Wrapping::Repeat, image.dimensions(), image.data());

        const auto& renderInfo       = gfx::RenderInfo{ { camera, cameraTransform }, {} };
        const auto& modelMatrix      = fox::Matrix4f{ 1.0f };
        const auto& viewMatrix       = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward(), cameraTransform.up());
        const auto& projectionMatrix = camera.projection().matrix();

              auto  matricesBuffer   = std::make_shared<gfx::UniformBuffer<gfx::UMatrices>>();
              auto  cameraBuffer     = std::make_shared<gfx::UniformBuffer<gfx::UCamera>>();





        Time::reset();
        CyclicBuffer<fox::float32_t, 128> frametimes{};

        gl::clear_color(fox::Vector4f{ 0.1f, 0.1f, 0.1f, 1.0f });
        gl::enable(gl::Flags::Capability::FaceCulling);
        gl::front_face(gl::Flags::Orientation::CounterClockwise);
        gl::face_culling(gl::Flags::FaceCulling::Back);



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



            gl::clear(gfx::api::gl::Flags::Buffer::ColorBuffer);

            const auto& viewMatrix = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward(), cameraTransform.up());

            matricesBuffer->bind_index(gfx::api::gl::index_t{ 0 });
            matricesBuffer->copy(gfx::UMatrices{ modelMatrix, viewMatrix, projectionMatrix, {} });
            cameraBuffer->bind_index(gfx::api::gl::index_t{ 2 });
            cameraBuffer->copy(gfx::UCamera{ Vector4f{ cameraTransform.position, 1.0f } });

            testPipeline->bind();
            model->materials.at(0)->albedo->bind(0);
            //model->materials.at(0)->normal->bind(1);
            model->materials.at(0)->arm->bind(2);

            model->meshes.at(0)->vertexArray->bind();
            gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, model->meshes.at(0)->vertexArray->index_buffer()->count());





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
