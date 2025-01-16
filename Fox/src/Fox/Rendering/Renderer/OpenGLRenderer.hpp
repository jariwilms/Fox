#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/Geometry/Geometry.hpp"
#include "Fox/Rendering/Renderer/Renderer.hpp"
#include "Fox/Rendering/Renderer/RenderMode.hpp"
#include "Fox/Rendering/RenderInfo/RenderInfo.hpp"
#include "Fox/Rendering/Using.hpp"
#include "Fox/Rendering/Utility/Utility.hpp"
#include "Fox/Core/Library/Time/Time.hpp"
#include "Fox/Input/Input.hpp"

namespace fox::gfx::api
{
    class OpenGLRenderer : public api::Renderer
    {
    public:
        static void init()
        {
            gl::enable(glf::Feature::Multisampling);
            gl::enable(glf::Feature::SeamlessCubeMapTexture);





            const fox::uint8_t  samples{ 4u };
            const fox::uint32_t lightCount{ 32u };
            const fox::Vector2u dimensions{ 1280u, 720u };
            const fox::Vector2u shadowMapDimensions{ 1024u, 1024u };



            using FM = gfx::FrameBuffer::Manifest;
            using FA = gfx::FrameBuffer::Attachment;
            using FR = gfx::FrameBuffer::Resample;
            using TF = gfx::Texture::Format;
            using RF = gfx::RenderBuffer::Format;

            std::array<FM, 5> gBufferManifest
            {
                FM{ "Position",     TF::RGB16_FLOAT },
                FM{ "Albedo",       TF::RGBA8_UNORM  },
                FM{ "Normal",       TF::RGB16_FLOAT },
                FM{ "ARM",          TF::RGB16_UNORM  },

                FM{ "DepthStencil", RF::D24_UNORM_S8_UINT },
            };
            std::array<FM, 1> sBufferManifest
            {
                FM{ "Depth",        TF::D24_UNORM },
            };
            std::array<FM, 2> ppBufferManifest
            {
                FM{ "Color",        TF::RGBA8_UNORM },
                FM{ "Depth",        RF::D24_UNORM_S8_UINT },
            };

            s_gBuffer            = std::make_unique<gfx::FrameBuffer>(dimensions, gBufferManifest);
            s_sBuffer            = std::make_unique<gfx::FrameBuffer>(shadowMapDimensions, sBufferManifest);
            s_gBufferMultisample = std::make_unique<gfx::FrameBufferMultisample>(dimensions, samples, gBufferManifest);
            s_ppBuffers.at(0)    = std::make_unique<gfx::FrameBuffer>(dimensions, ppBufferManifest);
            s_ppBuffers.at(1)    = std::make_unique<gfx::FrameBuffer>(dimensions, ppBufferManifest);

            s_inputBuffer        = std::make_unique<gfx::UniformBuffer<UInput>>();
            s_matricesBuffer     = std::make_unique<gfx::UniformBuffer<UMatrices>>();
            s_materialBuffer     = std::make_unique<gfx::UniformBuffer<UMaterial>>();
            s_cameraBuffer       = std::make_unique<gfx::UniformBuffer<UCamera>>();
            s_lightBuffer        = std::make_unique<gfx::UniformArrayBuffer<ULight>>(lightCount);
            s_shadowBuffer       = std::make_unique<gfx::UniformBuffer<UShadow>>();

            s_INDEXBUFFER        = std::make_unique<gfx::UniformBuffer<fox::int32_t>>();
            


            const auto& depthTexture = s_sBuffer->find_texture("Depth");
            const std::array<gl::float32_t, 4> borderColor{ 1.0f, 1.0f, 1.0f, 1.0f };
            glTextureParameteri(static_cast<gl::uint32_t>(depthTexture->handle()), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTextureParameteri(static_cast<gl::uint32_t>(depthTexture->handle()), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameterfv(static_cast<gl::uint32_t>(depthTexture->handle()), GL_TEXTURE_BORDER_COLOR, borderColor.data());





            const auto& meshShaders     = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/mesh_deferred.vert.spv",               "shaders/compiled/mesh_deferred.frag.spv");
            const auto& blitShaders     = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/render_gbuffer_texture.vert.spv",      "shaders/compiled/render_gbuffer_texture.frag.spv");
            const auto& lightingShaders = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/lighting_blinn-phong_sphere_shadow_2.vert.spv", "shaders/compiled/lighting_blinn-phong_sphere_shadow_2.frag.spv");
            const auto& ambientShaders  = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/ambient.vert.spv",                     "shaders/compiled/ambient.frag.spv");
            const auto& shadowShaders   = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/shadow.vert.spv",                      "shaders/compiled/shadow.frag.spv");
            const auto& skyboxShaders   = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/skybox.vert.spv",                      "shaders/compiled/skybox.frag.spv");
            const auto& debugShaders    = api::shaders_from_binaries<gfx::Shader>("shaders/compiled/debug.vert.spv",                       "shaders/compiled/debug.frag.spv");

            s_pipelines.emplace("Mesh",     std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = meshShaders.at(0),     .fragment = meshShaders.at(1) }));
            s_pipelines.emplace("Blit",     std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = blitShaders.at(0),     .fragment = blitShaders.at(1) }));
            s_pipelines.emplace("Lighting", std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = lightingShaders.at(0), .fragment = lightingShaders.at(1) }));
            s_pipelines.emplace("Ambient",  std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = ambientShaders.at(0),  .fragment = ambientShaders.at(1) }));
            s_pipelines.emplace("Shadow",   std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = shadowShaders.at(0),   .fragment = shadowShaders.at(1) }));
            s_pipelines.emplace("Skybox",   std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = skyboxShaders.at(0),   .fragment = skyboxShaders.at(1) }));
            s_pipelines.emplace("Debug",    std::make_unique<gfx::Pipeline>(gfx::Pipeline::Layout{ .vertex = debugShaders.at(0),    .fragment = debugShaders.at(1) }));
        }

        static void start(const gfx::RenderInfo& renderInfo)
        {
            const auto& lights              = renderInfo.lights;
            const auto& [camera, transform] = renderInfo.camera;
            const auto& viewMatrix          = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
            const auto& projectionMatrix    = camera.projection().matrix();

            std::array<gfx::ULight, 32u> uLights{};
            std::transform(lights.begin(), lights.end(), uLights.begin(), [](const std::tuple<fox::Light, fox::Vector3f>& _)
                {
                    const auto& [light, position] = _;

                    return gfx::ULight
                    {
                        fox::Vector4f{ position,    0.0f },
                        fox::Vector4f{ light.color, 0.0f },
                        light.radius, 
                        0.0001f, 
                        0.0001f, 
                    };
                });



             

            //REMOVE
            s_lightsTEMP = uLights;




            s_skybox = renderInfo.skybox;




            s_matricesBuffer->copy_sub(offsetof(gfx::UMatrices, view), std::make_tuple(viewMatrix, projectionMatrix));
            s_cameraBuffer->copy(gfx::UCamera{ fox::Vector4f{ transform.position, 0.0f } });
            s_lightBuffer->copy(uLights);
            
            s_mmt.clear();
            s_debugTransforms.clear();
        }
        static void finish()
        {
            const fox::Vector2u dimensions{ 1280, 720 };
            const fox::Vector2u shadowMapDimensions{ 1024u, 1024u };
            const fox::Vector3f depthLightPosition{ -2.0f,  6.0f, -1.0f };

            const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;
            const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
            const auto& sva = gfx::Geometry::Sphere::mesh()->vertexArray;

            //Bind Uniform Buffers to correct indices
            s_inputBuffer->bind_index(gl::index_t{ 0 });
            s_matricesBuffer->bind_index(gl::index_t{ 1 });
            s_cameraBuffer->bind_index(gl::index_t{ 2 });
            s_materialBuffer->bind_index(gl::index_t{ 3 });
            s_lightBuffer->bind_index(gl::index_t{ 4 });
            s_shadowBuffer->bind_index(gl::index_t{ 5 });
            s_INDEXBUFFER->bind_index(gl::index_t{ 12 });

            s_inputBuffer->copy(UInput{ dimensions, static_cast<fox::float32_t>(glfwGetTime()), fox::Time::delta(), input::cursor_position() });





            //Render to shadow map
            gl::viewport(fox::Vector4u{ 0u, 0u, shadowMapDimensions });

            s_pipelines.at("Shadow")->bind();
            s_sBuffer->bind(api::FrameBuffer::Target::Write);

            gl::clear(glf::Buffer::Mask::Depth);

            gl::enable(glf::Feature::FaceCulling);
            gl::cull_face(glf::Culling::Face::Front);

            const auto& lightProjection  = gfx::Projection::create<gfx::Projection::Type::Orthographic>(10.0f, -10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
            const auto& lightView        = glm::lookAt(depthLightPosition, fox::Vector3f{}, fox::Vector3f{ 0.0f, 1.0f, 0.0f });
            const auto& lightSpaceMatrix = lightProjection.matrix() * lightView;

            for (const auto& mmt : s_mmt)
            {
                const auto& [mesh, material, transform] = mmt;
                const auto& vao                         = mesh->vertexArray;
                const auto& ind                         = vao->index_buffer();

                const auto& modelMatrix  = transform.matrix();
                
                s_shadowBuffer->copy(UShadow{ modelMatrix, lightSpaceMatrix });

                vao->bind();
                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, ind->count());
            }





            gl::viewport(fox::Vector4u{ 0u, 0u, dimensions });

            //Render Meshes
            gl::enable(glf::Feature::FaceCulling);
            gl::cull_face(glf::Culling::Face::Back);
            gl::front_face(glf::Orientation::CounterClockwise);

            gl::enable(glf::Feature::DepthTest);
            gl::depth_function(glf::DepthFunction::Less);

            gl::disable(glf::Feature::Blending);

            s_pipelines.at("Mesh")->bind();
            s_gBufferMultisample->bind(gfx::FrameBuffer::Target::Write);
            gl::clear(glf::Buffer::Mask::All);

            for (const auto& mmt : s_mmt)
            {
                const auto& [mesh, material, transform] = mmt;
                const auto& vao                         = mesh->vertexArray;
                const auto& ind                         = vao->index_buffer();

                const auto& modelMatrix  = transform.matrix();
                const auto& normalMatrix = glm::transpose(glm::inverse(fox::Matrix3f{ modelMatrix }));
                
                s_matricesBuffer->copy_sub(offsetof(gfx::UMatrices, model),  std::make_tuple(modelMatrix));
                s_materialBuffer->copy(gfx::UMaterial{ material->color, material->roughnessFactor, material->metallicFactor });

                vao->bind();

                material->albedo->bind(0);
                material->normal->bind(1);
                material->arm->bind(2);

                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, ind->count());
            }





            //Resolve multisampled frame buffer
            const auto& gBufferHandle   = static_cast<gl::uint32_t>(s_gBuffer->handle());
            const auto& gBufferMSHandle = static_cast<gl::uint32_t>(s_gBufferMultisample->handle());

            for (auto i{ 0u }; i < 4; ++i)
            {
                glNamedFramebufferReadBuffer(gBufferMSHandle, GL_COLOR_ATTACHMENT0 + i);
                glNamedFramebufferDrawBuffer(gBufferHandle,   GL_COLOR_ATTACHMENT0 + i);
                glBlitNamedFramebuffer(gBufferMSHandle, gBufferHandle, 0, 0, dimensions.x, dimensions.y, 0, 0, dimensions.x, dimensions.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            }
            glBlitNamedFramebuffer(gBufferMSHandle, gBufferHandle, 0, 0, dimensions.x, dimensions.y, 0, 0, dimensions.x, dimensions.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
            glBlitNamedFramebuffer(gBufferMSHandle, gBufferHandle, 0, 0, dimensions.x, dimensions.y, 0, 0, dimensions.x, dimensions.y, GL_STENCIL_BUFFER_BIT, GL_NEAREST);





            //Regular Lighting
            gl::disable(glf::Feature::DepthTest);

            gl::enable(glf::Feature::Blending);
            gl::blend_function(glf::Blending::Factor::SourceAlpha, glf::Blending::Factor::One);

            gl::cull_face(glf::Culling::Face::Front);

            s_pipelines.at("Lighting")->bind();

            s_gBuffer->bind_texture("Position", 0);
            s_gBuffer->bind_texture("Albedo",   1);
            s_gBuffer->bind_texture("Normal",   2);
            s_gBuffer->bind_texture("ARM",      3);
            s_sBuffer->bind_texture("Depth",    4);

            s_ppBuffers.at(0)->bind(api::FrameBuffer::Target::Write);
            gl::clear(glf::Buffer::Mask::All);

            sva->bind();
            for (int i = 0; i < 1; ++i)
            {
                const auto& light = s_lightsTEMP.at(i);
                auto sModel = fox::Transform{};
                sModel.position = light.position;
                sModel.dilate(fox::Vector3f{ light.radius });

                s_matricesBuffer->copy_sub(offsetof(gfx::UMatrices, model), std::make_tuple(sModel.matrix()));
                s_INDEXBUFFER->copy(i);

                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, sva->index_buffer()->count());
            }





            //Ambient Lighting
            gl::cull_face(glf::Culling::Face::Back);

            s_gBuffer->bind_texture("Albedo", 0);
            s_ppBuffers.at(0)->bind_texture("Color", 1);
            s_pipelines.at("Ambient")->bind();
            pva->bind();
            gl::bind_frame_buffer(s_ppBuffers.at(1)->handle(), glf::FrameBuffer::Target::Write);
            gl::clear(glf::Buffer::Mask::All);
            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_buffer()->count());




            //Skybox
            gl::disable(glf::Feature::Blending);

            cva->bind();

            gl::blit_framebuffer(s_gBuffer->handle(), s_ppBuffers.at(1)->handle(), fox::Vector4u{0, 0, 1280, 720}, fox::Vector4u{0, 0, 1280, 720}, glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest);

            gl::enable(glf::Feature::DepthTest);
            gl::depth_function(glf::DepthFunction::LessEqual);
            gl::disable(glf::Feature::FaceCulling);
            s_pipelines.at("Skybox")->bind();
            s_skybox->bind_index(0);

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_buffer()->count());





            //Debug cubes
#ifdef FOX_DEBUG
            s_pipelines.at("Debug")->bind();

            for (const auto& transform : s_debugTransforms)
            {
                s_matricesBuffer->copy_sub(offsetof(gfx::UMatrices, model), std::make_tuple(transform.matrix()));
                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_buffer()->count());
            }
#endif





            gl::blit_framebuffer(s_ppBuffers.at(1)->handle(), gl::handle_t{ 0 }, fox::Vector4u{ 0, 0, dimensions }, fox::Vector4u{ 0, 0, dimensions }, glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest);
        }

        static void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
        {
            s_mmt.emplace_back(mesh, material, transform);
        }
        static void render_debug(const fox::Transform& transform)
        {
            s_debugTransforms.emplace_back(transform);
        }

    private:
        OpenGLRenderer() = delete;

        static inline std::unique_ptr<gfx::FrameBuffer>                s_gBuffer{};
        static inline std::unique_ptr<gfx::FrameBuffer>                s_sBuffer{};
        static inline std::array<std::unique_ptr<gfx::FrameBuffer>, 2> s_ppBuffers{};
        static inline std::unique_ptr<gfx::FrameBufferMultisample>     s_gBufferMultisample{};
        
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UInput>>      s_inputBuffer{};
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UMatrices>>   s_matricesBuffer{};
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UMaterial>>   s_materialBuffer{};
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UCamera>>     s_cameraBuffer{};
        static inline std::unique_ptr<gfx::UniformArrayBuffer<gfx::ULight>> s_lightBuffer{};
        static inline std::unique_ptr<gfx::UniformBuffer<gfx::UShadow>>     s_shadowBuffer{};

        static inline std::unordered_map<std::string, std::unique_ptr<gfx::Pipeline>> s_pipelines{};

        static inline std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>> s_mmt{};


        static inline std::shared_ptr<const gfx::CubemapTexture> s_skybox{};
        

        static inline std::unique_ptr<gfx::UniformBuffer<fox::int32_t>> s_INDEXBUFFER{};
        static inline std::array<gfx::ULight, 32u>                      s_lightsTEMP{};
        static inline std::vector<fox::Transform>                       s_debugTransforms{};
    };
}
