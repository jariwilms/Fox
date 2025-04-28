#pragma once

#include "stdafx.hpp"

#include "Fox/Core/Library/Time/Time.hpp"
#include "Fox/Core/Library/Utility/Utility.hpp"
#include "Fox/Input/Input.hpp"
#include "Fox/Rendering/Rendering.hpp"
#include "Fox/Rendering/API/Shader/Utility.hpp"

namespace fox::gfx::api
{
    class OpenGLRenderer
    {
    public:
        OpenGLRenderer()
        {
            gl::enable(glf::Feature::Multisampling);
            gl::enable(glf::Feature::SeamlessCubeMapTexture);





            const fox::uint8_t  samples{ 4u };
            const fox::uint32_t lightCount{ 32u };
            const fox::Vector2u dimensions{ 1280u, 720u };
            const fox::Vector2u shadowMapDimensions{ 2048u, 2048u };



            using FM = gfx::FrameBuffer::Manifest;
            using FA = gfx::FrameBuffer::Attachment;
            using TF = gfx::Texture2D::Format;
            using RF = gfx::RenderBuffer::Format;
            using CF = gfx::Cubemap::Format;

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
                FM{ "Color",        TF::RGBA16_UNORM }, 
                FM{ "Depth",        RF::D24_UNORM_S8_UINT }, 
            };
            std::array<FM, 1> scBufferManifest
            {
                FM{"Depth",         CF::D24_UNORM }, 
            };

            gBuffer              = gfx::FrameBuffer::create(dimensions, gBufferManifest);
            sBuffer              = gfx::FrameBuffer::create(shadowMapDimensions, sBufferManifest);
            gBufferMultisample   = gfx::FrameBufferMultisample::create(dimensions, samples, gBufferManifest);
            ppBuffers.at(0)      = gfx::FrameBuffer::create(dimensions, ppBufferManifest);
            ppBuffers.at(1)      = gfx::FrameBuffer::create(dimensions, ppBufferManifest);
            shadowCubemaps =
            {
                gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
                gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
                gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
                gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
            };

            contextBuffer           = gfx::UniformBuffer<unf::Context>::create();
            matricesBuffer          = gfx::UniformBuffer<unf::Matrices>::create();
            materialBuffer          = gfx::UniformBuffer<unf::Material>::create();
            cameraBuffer            = gfx::UniformBuffer<unf::Camera>::create();
            lightBuffer             = gfx::UniformBuffer<unf::Light>::create();
            lightShadowBuffer       = gfx::UniformBuffer<unf::LightShadow>::create();
            shadowProjectionsBuffer = gfx::UniformArrayBuffer<unf::ShadowProjection, 6>::create();
            


            const auto& depthTexture = sBuffer->find_texture("Depth");
            const std::array<gl::float32_t, 4> borderColor{ 1.0f, 1.0f, 1.0f, 1.0f };
            glTextureParameteri( static_cast<gl::uint32_t>(depthTexture->handle()), GL_TEXTURE_MIN_FILTER,   GL_NEAREST);
            glTextureParameteri( static_cast<gl::uint32_t>(depthTexture->handle()), GL_TEXTURE_MAG_FILTER,   GL_NEAREST);
            glTextureParameterfv(static_cast<gl::uint32_t>(depthTexture->handle()), GL_TEXTURE_BORDER_COLOR, borderColor.data());





            const std::filesystem::path sDir{ "shaders/compiled" };

            const auto& deferredMeshShaders        = api::shaders_from_binaries<gfx::Shader>(sDir / "mesh_deferred.vert.spv",                                                        sDir / "mesh_deferred.frag.spv");
            const auto& lightingShaders            = api::shaders_from_binaries<gfx::Shader>(sDir / "lighting_blinn-phong_sphere.vert.spv",                                          sDir / "lighting_blinn-phong_sphere.frag.spv");
            const auto& pointLightingShaders       = api::shaders_from_binaries<gfx::Shader>(sDir / "lighting_blinn-phong_sphere_shadow_3.vert.spv",                                 sDir / "lighting_blinn-phong_sphere_shadow_3.frag.spv");
            const auto& directionalLightingShaders = api::shaders_from_binaries<gfx::Shader>(sDir / "lighting_blinn-phong_sphere_shadow_2.vert.spv",                                 sDir / "lighting_blinn-phong_sphere_shadow_2.frag.spv");
            const auto& ambientLightingShaders     = api::shaders_from_binaries<gfx::Shader>(sDir / "ambient.vert.spv",                                                              sDir / "ambient.frag.spv");
            const auto& directionalShadowShaders   = api::shaders_from_binaries<gfx::Shader>(sDir / "directional_shadow.vert.spv",                                                   sDir / "directional_shadow.frag.spv");
            const auto& pointShadowShaders         = api::shaders_from_binaries<gfx::Shader>(sDir / "point_shadow.vert.spv",                         sDir / "point_shadow.geom.spv", sDir / "point_shadow.frag.spv");
            const auto& skyboxShaders              = api::shaders_from_binaries<gfx::Shader>(sDir / "skybox.vert.spv",                                                               sDir / "skybox.frag.spv");
            const auto& debugShaders               = api::shaders_from_binaries<gfx::Shader>(sDir / "debug.vert.spv",                                                                sDir / "debug.frag.spv");

            pipelines.emplace("DeferredMesh",        gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = deferredMeshShaders.at(0),                                              .fragment = deferredMeshShaders.at(1) }));
            pipelines.emplace("Lighting",            gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = lightingShaders.at(0),                                                  .fragment = lightingShaders.at(1) }));
            pipelines.emplace("PointLighting",       gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = pointLightingShaders.at(0),                                             .fragment = pointLightingShaders.at(1) }));
            pipelines.emplace("DirectionalLighting", gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = directionalLightingShaders.at(0),                                       .fragment = directionalLightingShaders.at(1) }));
            pipelines.emplace("AmbientLighting",     gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = ambientLightingShaders.at(0),                                           .fragment = ambientLightingShaders.at(1) }));
            pipelines.emplace("DirectionalShadow",   gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = directionalShadowShaders.at(0),                                         .fragment = directionalShadowShaders.at(1) }));
            pipelines.emplace("PointShadow",         gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = pointShadowShaders.at(0),         .geometry = pointShadowShaders.at(1), .fragment = pointShadowShaders.at(2) }));
            pipelines.emplace("Skybox",              gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = skyboxShaders.at(0),                                                    .fragment = skyboxShaders.at(1) }));
            pipelines.emplace("Debug",               gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = debugShaders.at(0),                                                     .fragment = debugShaders.at(1) }));
        }

        void start(const gfx::RenderInfo& renderInfo)
        {
            const auto& lights              = renderInfo.lights;
            const auto& [camera, transform] = renderInfo.camera;
            const auto& viewMatrix          = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
            const auto& projectionMatrix    = camera.projection().matrix();



            sceneLights.clear();
            pointLights.clear();
            directionalLights.clear();

            constexpr auto MAX_POINT_LIGHTS{ 4 };
            for (const auto& [light, position] : lights)
            {
                unf::Light result
                {
                    fox::Vector4f{ position,    1.0f },
                    fox::Vector4f{ light.color, 1.0f },

                    light.radius,

                    0.01f, 
                    0.01f,
                };

                if (light.isShadowCasting)
                {
                    switch (light.type)
                    {
                        case fox::Light::Type::Point:       if (pointLights.size() < MAX_POINT_LIGHTS) pointLights.emplace_back(std::move(result)); break;
                        case fox::Light::Type::Directional:
                        case fox::Light::Type::Spot:
                        case fox::Light::Type::Area:        

                        default: sceneLights.emplace_back(std::move(result));
                    }
                }
                else
                {
                    sceneLights.emplace_back(std::move(result));
                }
                
            }



            skybox = renderInfo.skybox;

            matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(viewMatrix, projectionMatrix));
            cameraBuffer->copy(unf::Camera{ fox::Vector4f{ transform.position, 1.0f } });
            
            mmt.clear();
            debugTransforms.clear();
        }
        void finish()
        {
            constexpr fox::Vector2u dimensions{ 1280u, 720u };
            constexpr fox::Vector2u shadowMapDimensions{ 2048u, 2048u };

            const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;
            const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
            const auto& sva = gfx::Geometry::Sphere::mesh()->vertexArray;

            //Bind Uniform Buffers to correct indices
            contextBuffer->          bind_index( 0);
            cameraBuffer->           bind_index( 1);
            matricesBuffer->         bind_index( 2);
            materialBuffer->         bind_index( 3);
            lightBuffer->            bind_index( 4);
            lightShadowBuffer->      bind_index( 6);
            shadowProjectionsBuffer->bind_index(13);

            contextBuffer->copy(unf::Context{ dimensions, input::cursor_position(), fox::Time::since_epoch(), fox::Time::delta(),});





            const auto& nearPlane = 0.1f;
            const auto& farPlane = 100.0f;

            const auto& render_meshes = [&]()
                {
                    gl::viewport(gBufferMultisample->dimensions());

                    gl::enable(glf::Feature::FaceCulling);
                    gl::cull_face(glf::Culling::Face::Back);
                    gl::front_face(glf::Orientation::CounterClockwise);

                    gl::enable(glf::Feature::DepthTest);
                    gl::depth_function(glf::DepthFunction::Less);

                    gl::disable(glf::Feature::Blending);

                    pipelines.at("DeferredMesh")->bind();
                    gBufferMultisample->bind(gfx::FrameBuffer::Target::Write);
                    gl::clear(glf::Buffer::Mask::All);

                    for (const auto& _ : mmt)
                    {
                        const auto& [mesh, material, transform] = _;

                        matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
                        materialBuffer->copy(unf::Material{ material->color, material->roughnessFactor, material->metallicFactor });

                        material->albedo->bind(0);
                        material->normal->bind(1);
                        material->arm->bind(2);

                        mesh->vertexArray->bind();
                        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, mesh->vertexArray->index_count());
                    }
                };
            const auto& render_shadow_map_directional = [&](const fox::Light& light, const fox::Vector3f& position)
                {
                    //sBuffer->bind(api::FrameBuffer::Target::Write);
                    //gl::clear(glf::Buffer::Mask::Depth);

                    //gl::viewport(fox::Vector4u{ 0u, 0u, shadowMapDimensions });
                    //pipelines.at("DirectionalShadow")->bind();

                    //gl::enable(glf::Feature::FaceCulling);
                    //gl::cull_face(glf::Culling::Face::Back);

                    //const auto& lightProjection  = gfx::Projection::create<gfx::Projection::Type::Orthographic>(10.0f, -10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
                    //const auto& lightView        = glm::lookAt(position, fox::Vector3f{}, fox::Vector3f{ 0.0f, 1.0f, 0.0f });
                    //const auto& lightSpaceMatrix = lightProjection.matrix() * lightView;

                    //for (const auto& mmt : mmt)
                    //{
                    //    const auto& [mesh, material, transform] = mmt;
                    //    const auto& vao                         = mesh->vertexArray;

                    //    const auto& modelMatrix  = transform.matrix();
                    //    
                    //    shadowProjectionsBuffer->copy(UShadow{ modelMatrix, lightSpaceMatrix });

                    //    vao->bind();
                    //    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, vao->index_count());
                    //}
                };
            const auto& render_shadow_map_point       = [&](
                const fox::Vector3f& position, 
                const fox::Vector2u& dimensions, fox::float32_t nearPlane, fox::float32_t farPlane, 
                const std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>>& mmt, 
                gfx::FrameBuffer& cubemap)
                {
                    cubemap.bind(api::FrameBuffer::Target::Write);

                    gl::clear(glf::Buffer::Mask::Depth);

                    gl::viewport(dimensions);

                    gl::enable(glf::Feature::FaceCulling);
                    gl::cull_face(glf::Culling::Face::Back);



                    const auto& aspectRatio = static_cast<fox::float32_t>(dimensions.x) / dimensions.y;
                    const auto& projection  = glm::perspective(glm::radians(90.0f), aspectRatio, nearPlane, farPlane);

                    std::array<const unf::ShadowProjection, 6> shadowTransforms
                    {
                        projection * glm::lookAt(position, position + fox::Vector3f{  1.0, 0.0, 0.0 }, fox::Vector3f{ 0.0,-1.0, 0.0 }), 
                        projection * glm::lookAt(position, position + fox::Vector3f{ -1.0, 0.0, 0.0 }, fox::Vector3f{ 0.0,-1.0, 0.0 }), 
                        projection * glm::lookAt(position, position + fox::Vector3f{  0.0, 1.0, 0.0 }, fox::Vector3f{ 0.0, 0.0, 1.0 }), 
                        projection * glm::lookAt(position, position + fox::Vector3f{  0.0,-1.0, 0.0 }, fox::Vector3f{ 0.0, 0.0,-1.0 }), 
                        projection * glm::lookAt(position, position + fox::Vector3f{  0.0, 0.0, 1.0 }, fox::Vector3f{ 0.0,-1.0, 0.0 }), 
                        projection * glm::lookAt(position, position + fox::Vector3f{  0.0, 0.0,-1.0 }, fox::Vector3f{ 0.0,-1.0, 0.0 }), 
                    };

                    pipelines.at("PointShadow")->bind();
                    shadowProjectionsBuffer->copy(shadowTransforms);
                    lightShadowBuffer->copy({ fox::Vector4f{ position, 1.0f }, farPlane });

                    for (const auto& _ : mmt)
                    {
                        const auto& [mesh, material, transform] = _;
                        const auto& vao = mesh->vertexArray;

                        matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));

                        vao->bind();
                        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, vao->index_count());
                    }
                };
            const auto& render_lighting = [&](fox::float32_t farPlane)
                {
                    gl::enable(glf::Feature::FaceCulling);
                    gl::cull_face(glf::Culling::Face::Front);
                    gl::enable(glf::Feature::Blending);
                    gl::blend_function(glf::Blending::Factor::SourceAlpha, glf::Blending::Factor::One);
                    gl::disable(glf::Feature::DepthTest);

                    pipelines.at("PointLighting")->bind();

                    ppBuffers.at(0)->bind(api::FrameBuffer::Target::Write);
                    gl::clear(glf::Buffer::Mask::All);

                    gBuffer->bind_texture("Position", 0);
                    gBuffer->bind_texture("Albedo",   1);
                    gBuffer->bind_texture("Normal",   2);
                    gBuffer->bind_texture("ARM",      3);

                    sva->bind();
                    fox::uint32_t li{};

                    for (const auto& light : pointLights)
                    {
                        fox::Transform sphereTransform{ light.position, fox::Vector3f{}, fox::Vector3f{light.radius} };

                        matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(sphereTransform.matrix()));
                        lightBuffer->copy({ light.position, light.color, light.radius, light.linearFalloff, light.quadraticFalloff });
                        lightShadowBuffer->copy({ light.position, farPlane });
                        shadowCubemaps.at(li++)->bind_cubemap("Depth", 4);

                        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, sva->index_count());
                    }
                };



            fox::uint32_t index{};
            for (const auto& pointLight : pointLights)
            {
                render_shadow_map_point(pointLight.position, shadowMapDimensions, nearPlane, farPlane, mmt, *shadowCubemaps.at(index++));
            }



            render_meshes();



            //Resolve multisampled frame buffer
            const auto& gBufferHandle   = static_cast<gl::uint32_t>(gBuffer->handle());
            const auto& gBufferMSHandle = static_cast<gl::uint32_t>(gBufferMultisample->handle());

            for (auto i{ 0u }; i < 4; ++i)
            {
                glNamedFramebufferReadBuffer(gBufferMSHandle, GL_COLOR_ATTACHMENT0 + i);
                glNamedFramebufferDrawBuffer(gBufferHandle,   GL_COLOR_ATTACHMENT0 + i);
                glBlitNamedFramebuffer(gBufferMSHandle, gBufferHandle, 0, 0, dimensions.x, dimensions.y, 0, 0, dimensions.x, dimensions.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
            }
            glBlitNamedFramebuffer(gBufferMSHandle, gBufferHandle, 0, 0, dimensions.x, dimensions.y, 0, 0, dimensions.x, dimensions.y, GL_DEPTH_BUFFER_BIT,   GL_NEAREST);
            glBlitNamedFramebuffer(gBufferMSHandle, gBufferHandle, 0, 0, dimensions.x, dimensions.y, 0, 0, dimensions.x, dimensions.y, GL_STENCIL_BUFFER_BIT, GL_NEAREST);



            render_lighting(farPlane);



            //Ambient Lighting
            gl::cull_face(glf::Culling::Face::Back);

            gBuffer->bind_texture("Albedo", 0);
            ppBuffers.at(0)->bind_texture("Color", 1);
            pipelines.at("AmbientLighting")->bind();
            pva->bind();
            gl::bind_frame_buffer(ppBuffers.at(1)->handle(), glf::FrameBuffer::Target::Write);
            gl::clear(glf::Buffer::Mask::All);
            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());





            //Skybox
            gl::enable(glf::Feature::DepthTest);
            gl::depth_function(glf::DepthFunction::LessEqual);
            gl::disable(glf::Feature::Blending);
            gl::disable(glf::Feature::FaceCulling);

            pipelines.at("Skybox")->bind();
            skybox->bind(0);

            gl::blit_framebuffer(gBuffer->handle(), ppBuffers.at(1)->handle(), gl::Area<gl::uint32_t>{ {}, { 1280, 720 } }, gl::Area<gl::uint32_t>{ {}, { 1280, 720 } }, glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest);

            cva->bind();
            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());





            //Debug cubes
#ifdef FOX_DEBUG
            pipelines.at("Debug")->bind();

            for (const auto& transform : debugTransforms)
            {
                matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
            }
#endif





            //Final result of rendering copied to default framebuffer
            gl::blit_framebuffer(ppBuffers.at(1)->handle(), gl::handle_t{ 0 }, gl::Area<gl::uint32_t>{ {}, dimensions }, gl::Area<gl::uint32_t>{ {}, dimensions }, glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest);
        }

        void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
        {
            mmt.emplace_back(mesh, material, transform);
        }
        void render_debug(const fox::Transform& transform)
        {
            debugTransforms.emplace_back(transform);
        }

    private:
        std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>> mmt{};
        std::vector<unf::Light>                                            sceneLights{};
        std::vector<unf::Light>                                            pointLights{};
        std::vector<unf::Light>                                            directionalLights{};
        std::vector<fox::Transform>                                        debugTransforms{};
                                                    
        std::shared_ptr<gfx::FrameBuffer>                                  gBuffer{};
        std::shared_ptr<gfx::FrameBufferMultisample>                       gBufferMultisample{}; 
        std::shared_ptr<gfx::FrameBuffer>                                  sBuffer{};
        std::array<std::shared_ptr<gfx::FrameBuffer>, 4>                   shadowCubemaps{}; //TODO: change to cube map array
        std::array<std::shared_ptr<gfx::FrameBuffer>, 2>                   ppBuffers{};
                                                    
        std::shared_ptr<gfx::UniformBuffer<unf::Context>>                  contextBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Matrices>>                 matricesBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Material>>                 materialBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Camera>>                   cameraBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::Light>>                    lightBuffer{};
        std::shared_ptr<gfx::UniformBuffer<unf::LightShadow>>              lightShadowBuffer{};
        std::shared_ptr<gfx::UniformArrayBuffer<unf::ShadowProjection, 6>> shadowProjectionsBuffer{};
        std::unordered_map<std::string, std::shared_ptr<gfx::Pipeline>>    pipelines{};
                                                    
        std::shared_ptr<const gfx::Cubemap>                                skybox{};
    };
}
