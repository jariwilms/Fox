#include "stdafx.hpp"

#include "Application.hpp"
#include "Fox/Window/WindowManager.hpp"

#include "Fox/Core/Library/Container/CyclicBuffer.hpp"
#include "Fox/Core/Library/Time/Time.hpp"
#include "Fox/Core/Library/Transform/Transform.hpp"
#include "Fox/ECS/Components/Components.hpp"
#include "Fox/Input/Input.hpp"
#include "Fox/IO/IO.hpp"
#include "Fox/IO/Import/Model/GLTFImporter.hpp"
#include "Fox/Scene/Scene.hpp"
#include "Fox/Rendering/Model/Model.hpp"
#include "Fox/Core/Library/Image/Image.hpp"
#include "Fox/Rendering/Utility/Utility.hpp"

namespace fox
{
    //////////////////REMOVEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
    using ModelImporter = io::GLTFImporter;
    //////////////////AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA


    Transform transform_product(TransformComponent& tc)
    {
        const auto& owner = tc.owner;
        const auto& rc = Registry::get_component<RelationshipComponent>(owner.id());

        if (!rc.parent.has_value()) return tc;

        auto& ptc = Registry::get_component<TransformComponent>(rc.parent.value());
        return transform_product(ptc) * tc;
    };
    std::shared_ptr<Actor> model_to_scene_graph(Scene* scene, std::shared_ptr<gfx::Model> model, std::shared_ptr<Actor> parent, gfx::Model::Node* node)
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
            model_to_scene_graph(scene, model, actor, &child);
        }

        return actor;
    };



    Application::Application(int argc, char* argv[])
    {
        m_window = WindowManager::create("Window", "Fox", Vector2u{ 1280u, 720u });
        
        //gfx::Geometry::init();
        //gfx::Renderer::init();
    }
    Application::~Application()
    {

    }

    int Application::run()
    {
        auto scene = std::make_shared<Scene>();
        auto observer = scene->create_actor();
        auto& camera = observer->add_component<CameraComponent>();
        auto& cameraTransform = observer->get_component<TransformComponent>();
        cameraTransform.translate(Vector3f{ 0.0f, 0.0f, 1.0f });
        
//        fox::ModelImporter modelImporter{};
//#ifdef _DEBUG
//        //auto model = modelImporter.import(R"(models/cube_textured/scene.gltf)");
//        auto model = modelImporter.import(R"(models/backpack/scene.gltf)");
//#endif
//#ifndef _DEBUG
//        //auto model = modelImporter.import(R"(models/sponza_gltf/glTF/Sponza.gltf)");
//        auto model = modelImporter.import(R"(models/fish/scene.gltf)");
//#endif
//        auto modelActor = model_to_scene_graph(scene.get(), model, nullptr, model->rootNode.get());
//        auto& t = modelActor->get_component<TransformComponent>();
//        t.dilate(Vector3f{ 0.01f });

        //const Vector2u skyboxDimensions{ 2048, 2048 };
        //gfx::api::TextureBlueprint skyboxBlueprint{};
        //std::string skyboxDirectory{ "textures/skybox2/" };
        //std::array<std::string, 6> skyboxFileNames{ "right.png", "left.png", "bottom.png", "top.png", "front.png", "back.png", };
        //std::array<std::shared_ptr<const std::vector<byte>>, 6> skyboxImages
        //{
        //    //Image{ io::load(skyboxDirectory + skyboxFileNames.at(0))->read(4u) },
        //    //Image{ io::load(skyboxDirectory + skyboxFileNames.at(1))->read(4u) },
        //    //Image{ io::load(skyboxDirectory + skyboxFileNames.at(2))->read(4u) },
        //    //Image{ io::load(skyboxDirectory + skyboxFileNames.at(3))->read(4u) },
        //    //Image{ io::load(skyboxDirectory + skyboxFileNames.at(4))->read(4u) },
        //    //Image{ io::load(skyboxDirectory + skyboxFileNames.at(5))->read(4u) },
        //};
        //std::array<std::span<const byte>, 6> skyboxImageData
        //{
        //    *skyboxImages[0], 
        //    *skyboxImages[1], 
        //    *skyboxImages[2], 
        //    *skyboxImages[3], 
        //    *skyboxImages[4], 
        //    *skyboxImages[5], 
        //};
        //RenderSettings::lighting.skybox = std::make_shared<OpenGLCubemapTexture>(Texture::Format::RGBA8_SRGB, Texture::Filter::Trilinear, Texture::Wrapping::ClampToEdge, skyboxDimensions, Texture::Components::RGBA, skyboxImageData);

        //std::array<std::tuple<Light, Vector3f>, 32> lights
        //{
        //    std::make_tuple(Light{.color = { 1.0f, 0.0f, 1.0f }, .radius = 100.0f }, Vector3f{ 1.0f, 0.0f, 1.0f }),
        //};





        auto model = ModelImporter::import("assets/models/cube2/cube.gltf");








        namespace gl = gfx::api::gl;



        const auto& shaders = gfx::api::shaders_from_binaries<gfx::Shader>("shaders/compiled/test.vert.spv", "shaders/compiled/test.frag.spv");
        auto testPipeline = std::make_shared<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertexShader = shaders.at(0), .fragmentShader = shaders.at(1) });



        float vertices[] = 
        {
             0.5f,  0.5f, 0.0f,  // top right
            -0.5f,  0.5f, 0.0f,  // top left 
            -0.5f, -0.5f, 0.0f,  // bottom left
             0.5f, -0.5f, 0.0f,  // bottom right
        };
        float texCoords[] =
        {
            1.0f, 1.0f, 
            0.0f, 1.0f, 
            0.0f, 0.0f, 
            1.0f, 0.0f, 
        };
        unsigned int indices[] = 
        {  // note that we start from 0!
            0, 1, 2,  // first Triangle
            0, 2, 3,  // second Triangle
        };
         
        auto layout3f = gfx::VertexLayout<float>{ 3 };
        auto layout2f = gfx::VertexLayout<float>{ 2 };

        auto vbo  = std::make_shared<gfx::VertexBuffer<gfx::api::Buffer::Access::Static, float>>(vertices);
        auto vbo2 = std::make_shared<gfx::VertexBuffer<gfx::api::Buffer::Access::Static, float>>(texCoords);
        auto ibo  = std::make_shared<gfx::IndexBuffer<gfx::api::Buffer::Access::Static>>(indices);
        auto vao  = std::make_shared<gfx::VertexArray>();

        vao->tie(vbo,  layout3f);
        vao->tie(vbo2, layout2f);
        vao->tie(ibo);



        const auto& file  = io::load("images/anna.png");
        const auto& data  = file->read();
        const auto& image = fox::Image::decode(fox::Image::Layout::RGBA8, *data);
        auto texture = std::make_shared<gfx::Texture2D>(gfx::Texture2D::Format::RGBA8_UNORM, gfx::Texture2D::Filter::Trilinear, gfx::Texture2D::Wrapping::ClampToEdge, image.dimensions(), image.data());



        const auto& renderInfo       = gfx::RenderInfo{ { camera, cameraTransform }, {} };
        const auto& modelMatrix      = fox::Matrix4f{ 1.0f };
        const auto& viewMatrix       = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward(), cameraTransform.up());
        const auto& projectionMatrix = camera.projection().matrix();

        auto matricesBuffer = std::make_shared<gfx::UniformBuffer<gfx::UMatrices>>();
        auto cameraBuffer   = std::make_shared<gfx::UniformBuffer<gfx::UCamera>>();



        gl::clear_color(fox::Vector4f{ 0.1f, 0.1f, 0.1f, 1.0f });











        Time::reset();
        CyclicBuffer<float, 128> frametimes{};
        while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(m_window->native_handle())))
        {
            Time::advance();

            auto speed{ 10.0f * Time::delta() };
            if (Input::key_pressed(Key::LeftShift))   speed *= 10.0f;
            if (Input::key_pressed(Key::LeftControl)) speed /=  5.0f;
            if (Input::key_pressed(Key::W)) cameraTransform.position += cameraTransform.forward() * speed;
            if (Input::key_pressed(Key::S)) cameraTransform.position -= cameraTransform.forward() * speed;
            if (Input::key_pressed(Key::A)) cameraTransform.position -= cameraTransform.right()   * speed;
            if (Input::key_pressed(Key::D)) cameraTransform.position += cameraTransform.right()   * speed;
            if (Input::key_pressed(Key::E)) cameraTransform.position += cameraTransform.up()      * speed;
            if (Input::key_pressed(Key::Q)) cameraTransform.position -= cameraTransform.up()      * speed;

            if (Input::button_pressed(Button::Button1)) //RMB
            {
                static Vector3f rotation{};
                const auto rel = Input::cursor_position_relative() / 10.0f;
                rotation += Vector3f{ rel.y, rel.x, 0.0f };

                cameraTransform.rotation = Quaternion{ glm::radians(rotation) };
            }

            //The render system starts running here and submits all models/meshes to the renderer
            //So, TODO: RenderSystem::update, which calls the code below
            //gfx::Renderer::start(gfx::RenderInfo{ {camera, cameraTransform}, lights });
            //auto group = Registry::view<TransformComponent, MeshRendererComponent>();
            //group.each([](auto entity, TransformComponent& transform, MeshRendererComponent& meshRenderer)
            //    {
            //        gfx::Renderer::render(meshRenderer.mesh, meshRenderer.material, transform_product(transform));
            //    });
            //gfx::Renderer::finish();






            

            gl::clear(gfx::api::gl::Flags::Buffer::ColorBuffer);

            const auto& viewMatrix = glm::lookAt(cameraTransform.position, cameraTransform.position + cameraTransform.forward(), cameraTransform.up());

            matricesBuffer->bind_index(gfx::api::gl::index_t{ 0 });
            matricesBuffer->copy(gfx::UMatrices{ modelMatrix, viewMatrix, projectionMatrix, {} });
            cameraBuffer->bind_index(gfx::api::gl::index_t{ 2 });
            cameraBuffer->copy(gfx::UCamera{ Vector4f{ cameraTransform.position, 1.0f } });

            texture->bind(0);
            testPipeline->bind();

            //vao->bind();
            //gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, ibo->count());

            gl::enable(gl::Flags::Capability::FaceCulling);
            gl::face_culling(gl::Flags::FaceCulling::Back);

            model->meshes.at(0)->vertex_array()->bind();
            gl::draw_elements(gl::Flags::Draw::Mode::Triangles, gl::Flags::Draw::Type::UnsignedInt, model->meshes.at(0)->vertex_array()->index_buffer()->count());












            m_window->refresh();
            frametimes.push_back(Time::delta());
        }

        float avgFrameTime = std::accumulate(frametimes.begin(), frametimes.end(), 0.0f) / static_cast<float>(frametimes.size());
        std::system("CLS");
        std::cout << "Average frame time: " << avgFrameTime << '\n';
        std::cout << "Average frame rate: " << 1.0f / avgFrameTime << '\n';



        return 0;
    }
}
