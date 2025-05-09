#include "stdafx.hpp"
#include "OpenGLRenderer.hpp"

namespace fox::gfx::api
{
    OpenGLRenderer::OpenGLRenderer()
    {
        gl::enable(glf::Feature::Multisampling);
        gl::enable(glf::Feature::SeamlessCubeMapTexture);



        constexpr gl::uint8_t  samples{ 4u };
        constexpr gl::uint32_t lightCount{ 32u };
        constexpr gl::Vector2u viewportDimensions{ 1280u, 720u };
        constexpr gl::Vector2u shadowMapDimensions{ 2048u, 2048u };

        using FM = gfx::FrameBuffer::Manifest;
        using FA = gfx::FrameBuffer::Attachment;
        using TF = gfx::Texture2D::Format;
        using RF = gfx::RenderBuffer::Format;
        using CF = gfx::Cubemap::Format;

        std::array<FM, 5> gBufferManifest {
            FM{ "Position",     TF::RGB16_FLOAT },
            FM{ "Albedo",       TF::RGBA8_UNORM  },
            FM{ "Normal",       TF::RGB16_FLOAT },
            FM{ "ARM",          TF::RGB16_UNORM  },
            FM{ "DepthStencil", RF::D24_UNORM_S8_UINT },
        };
        std::array<FM, 1> sBufferManifest  { FM{ "Depth", TF::D24_UNORM    }                                       };
        std::array<FM, 2> ppBufferManifest { FM{ "Color", TF::RGBA16_UNORM }, FM{ "Depth", RF::D24_UNORM_S8_UINT } };
        std::array<FM, 1> scBufferManifest { FM{ "Depth", CF::D24_UNORM    }                                       };



        gBuffer                 = gfx::FrameBuffer           ::create(viewportDimensions ,           gBufferManifest );
        gBufferMultisample      = gfx::FrameBufferMultisample::create(viewportDimensions ,  samples, gBufferManifest );
        sBuffer                 = gfx::FrameBuffer           ::create(shadowMapDimensions,           sBufferManifest );
        pBuffers.at(0)          = gfx::FrameBuffer           ::create(viewportDimensions ,           ppBufferManifest);
        pBuffers.at(1)          = gfx::FrameBuffer           ::create(viewportDimensions ,           ppBufferManifest);
        shadowCubemaps          = {
            gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
            gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
            gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
            gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
        };

        contextBuffer           = gfx::UniformBuffer<unf::Context>                 ::create();
        matricesBuffer          = gfx::UniformBuffer<unf::Matrices>                ::create();
        materialBuffer          = gfx::UniformBuffer<unf::Material>                ::create();
        cameraBuffer            = gfx::UniformBuffer<unf::Camera>                  ::create();
        lightBuffer             = gfx::UniformBuffer<unf::Light>                   ::create();
        lightShadowBuffer       = gfx::UniformBuffer<unf::LightShadow>             ::create();
        shadowProjectionsBuffer = gfx::UniformArrayBuffer<unf::ShadowProjection, 6>::create();
            


        const auto& depthTexture = sBuffer->find_texture("Depth");
        const std::array<gl::float32_t, 4> borderColor{ 1.0f, 1.0f, 1.0f, 1.0f };
        gl::texture_parameter(depthTexture->handle(), glf::Texture::MinificationFilter ::Nearest);
        gl::texture_parameter(depthTexture->handle(), glf::Texture::MagnificationFilter::Nearest);
        gl::texture_parameter(depthTexture->handle(), gl::border_color_p{ borderColor });



        const std::filesystem::path dir{ "shaders/compiled" };

        const auto& deferredMeshShaders        = api::shaders_from_binaries<gfx::Shader>(dir / "mesh_deferred.vert.spv",                                                       dir / "mesh_deferred.frag.spv");
        const auto& lightingShaders            = api::shaders_from_binaries<gfx::Shader>(dir / "lighting_blinn-phong_sphere.vert.spv",                                         dir / "lighting_blinn-phong_sphere.frag.spv");
        const auto& pointLightingShaders       = api::shaders_from_binaries<gfx::Shader>(dir / "lighting_blinn-phong_sphere_shadow_3.vert.spv",                                dir / "lighting_blinn-phong_sphere_shadow_3.frag.spv");
        const auto& directionalLightingShaders = api::shaders_from_binaries<gfx::Shader>(dir / "lighting_blinn-phong_sphere_shadow_2.vert.spv",                                dir / "lighting_blinn-phong_sphere_shadow_2.frag.spv");
        const auto& ambientLightingShaders     = api::shaders_from_binaries<gfx::Shader>(dir / "ambient.vert.spv",                                                             dir / "ambient.frag.spv");
        const auto& directionalShadowShaders   = api::shaders_from_binaries<gfx::Shader>(dir / "directional_shadow.vert.spv",                                                  dir / "directional_shadow.frag.spv");
        const auto& lightingStencilShaders     = api::shaders_from_binaries<gfx::Shader>(dir / "lighting_stencil.vert.spv",                                                    dir / "lighting_stencil.frag.spv");
        const auto& pointShadowShaders         = api::shaders_from_binaries<gfx::Shader>(dir / "point_shadow.vert.spv",                         dir / "point_shadow.geom.spv", dir / "point_shadow.frag.spv");
        const auto& skyboxShaders              = api::shaders_from_binaries<gfx::Shader>(dir / "skybox.vert.spv",                                                              dir / "skybox.frag.spv");
        const auto& debugShaders               = api::shaders_from_binaries<gfx::Shader>(dir / "debug.vert.spv",                                                               dir / "debug.frag.spv");

        pipelines.emplace("DeferredMesh",        gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = deferredMeshShaders.at(0),                                              .fragment = deferredMeshShaders.at(1) }));
        pipelines.emplace("Lighting",            gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = lightingShaders.at(0),                                                  .fragment = lightingShaders.at(1) }));
        pipelines.emplace("PointLighting",       gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = pointLightingShaders.at(0),                                             .fragment = pointLightingShaders.at(1) }));
        pipelines.emplace("DirectionalLighting", gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = directionalLightingShaders.at(0),                                       .fragment = directionalLightingShaders.at(1) }));
        pipelines.emplace("LightingStencil",     gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = lightingStencilShaders.at(0),                                           .fragment = lightingStencilShaders.at(1) }));
        pipelines.emplace("AmbientLighting",     gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = ambientLightingShaders.at(0),                                           .fragment = ambientLightingShaders.at(1) }));
        pipelines.emplace("DirectionalShadow",   gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = directionalShadowShaders.at(0),                                         .fragment = directionalShadowShaders.at(1) }));
        pipelines.emplace("PointShadow",         gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = pointShadowShaders.at(0),         .geometry = pointShadowShaders.at(1), .fragment = pointShadowShaders.at(2) }));
        pipelines.emplace("Skybox",              gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = skyboxShaders.at(0),                                                    .fragment = skyboxShaders.at(1) }));
        pipelines.emplace("Debug",               gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = debugShaders.at(0),                                                     .fragment = debugShaders.at(1) }));
    }

    void OpenGLRenderer::start(const gfx::RenderInfo& renderInfo)
    {
        const auto& [camera, transform] = renderInfo.camera;
        const auto& viewMatrix          = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
        const auto& projectionMatrix    = camera.projection().matrix();

        matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(viewMatrix, projectionMatrix));
        cameraBuffer  ->copy    (unf::Camera{ fox::Vector4f{ transform.position, 1.0f } });



        mmt              .clear();
        sceneLights      .clear();
        pointLights      .clear();
        directionalLights.clear();
        debugTransforms  .clear();

        skybox = renderInfo.skybox;



        constexpr auto maximumPointLights{ 4 };
        for (const auto& [light, position] : renderInfo.lights)
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
                    case fox::Light::Type::Point:       if (pointLights.size() < maximumPointLights) pointLights.emplace_back(std::move(result)); break;
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
    }

    void OpenGLRenderer::finish()
    {
        constexpr gl::Vector2u  dimensions{ 1280u,  720u };
        constexpr gl::Vector2u sDimensions{ 2048u, 2048u };

        const auto& pva = gfx::Geometry::Plane ::mesh()->vertexArray;
        const auto& cva = gfx::Geometry::Cube  ::mesh()->vertexArray;
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



        const auto& nearPlane =   0.1f;
        const auto& farPlane  = 100.0f;

        const auto& render_meshes                 = [&]()
            {
                gBufferMultisample->bind(gfx::FrameBuffer::Target::Write);
                pipelines.at("DeferredMesh")->bind();

                gl::viewport(gBufferMultisample->dimensions());
                gl::clear(glf::Buffer::Mask::All);
                gl::enable(glf::Feature::FaceCulling);
                gl::cull_face(glf::Culling::Face::Back);
                gl::front_face(glf::Orientation::CounterClockwise);
                gl::enable(glf::Feature::DepthTest);
                gl::depth_function(glf::DepthFunction::Less);
                gl::disable(glf::Feature::Blending);

                for (const auto& _ : mmt)
                {
                    const auto& [mesh, material, transform] = _;

                    matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
                    materialBuffer->copy    (unf::Material{ material->color, material->roughnessFactor, material->metallicFactor });

                    mesh    ->vertexArray->bind();
                    material->albedo     ->bind(0);
                    material->normal     ->bind(1);
                    material->arm        ->bind(2);

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
            const gl::Vector3f& position, 
            const gl::Vector2u& dimensions, gl::float32_t nearPlane, gl::float32_t farPlane, 
            const std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>>& mmt, 
            std::shared_ptr<gfx::FrameBuffer> cubemap)
            {
                const auto& aspectRatio = static_cast<gl::float32_t>(dimensions.x) / dimensions.y;
                const auto& projection  = glm::perspective(glm::radians(90.0f), aspectRatio, nearPlane, farPlane);

                std::array<const unf::ShadowProjection, 6> shadowTransforms {
                    projection * glm::lookAt(position, position + gl::Vector3f{  1.0, 0.0, 0.0 }, gl::Vector3f{ 0.0,-1.0, 0.0 }), 
                    projection * glm::lookAt(position, position + gl::Vector3f{ -1.0, 0.0, 0.0 }, gl::Vector3f{ 0.0,-1.0, 0.0 }), 
                    projection * glm::lookAt(position, position + gl::Vector3f{  0.0, 1.0, 0.0 }, gl::Vector3f{ 0.0, 0.0, 1.0 }), 
                    projection * glm::lookAt(position, position + gl::Vector3f{  0.0,-1.0, 0.0 }, gl::Vector3f{ 0.0, 0.0,-1.0 }), 
                    projection * glm::lookAt(position, position + gl::Vector3f{  0.0, 0.0, 1.0 }, gl::Vector3f{ 0.0,-1.0, 0.0 }), 
                    projection * glm::lookAt(position, position + gl::Vector3f{  0.0, 0.0,-1.0 }, gl::Vector3f{ 0.0,-1.0, 0.0 }), 
                };



                cubemap->bind(api::FrameBuffer::Target::Write);
                pipelines.at("PointShadow")->bind();
                shadowProjectionsBuffer->copy(shadowTransforms);
                lightShadowBuffer      ->copy({ fox::Vector4f{ position, 1.0f }, farPlane });

                gl::viewport(dimensions);
                gl::clear(glf::Buffer::Mask::Depth);
                gl::enable(glf::Feature::FaceCulling);
                gl::cull_face (glf::Culling::Face::Back);
                gl::front_face(glf::Orientation::CounterClockwise);
                gl::enable(glf::Feature::DepthTest);
                gl::depth_function(glf::DepthFunction::Less);
                gl::disable(glf::Feature::Blending);

                for (const auto& _ : mmt)
                {
                    const auto& [mesh, material, transform] = _;

                    matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));

                    mesh->vertexArray->bind();

                    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, mesh->vertexArray->index_count());
                }
            };
        const auto& render_lighting               = [&](gl::float32_t farPlane)
            {
                pBuffers.at(0)->bind(api::FrameBuffer::Target::Write);
                gl::clear(glf::Buffer::Mask::All);

                
                
                gl::blit_framebuffer(gBuffer->handle(), pBuffers.at(0)->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);



                gBuffer->bind_texture("Position", 0);
                gBuffer->bind_texture("Albedo",   1);
                gBuffer->bind_texture("Normal",   2);
                gBuffer->bind_texture("ARM",      3);

                gl::viewport(dimensions);
                gl::enable(glf::Feature::StencilTest);

                sva->bind();

                for (fox::size_t index{}; const auto& light : pointLights)
                {
                    fox::Transform sphereTransform{ light.position, fox::Vector3f{}, fox::Vector3f{light.radius} };

                    matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(sphereTransform.matrix()));
                    lightBuffer->copy({ light.position, light.color, light.radius, light.linearFalloff, light.quadraticFalloff });
                    lightShadowBuffer->copy({ light.position, farPlane });
                    shadowCubemaps.at(index++)->bind_cubemap("Depth", 4);



                    pipelines.at("LightingStencil")->bind();

                    gl::enable(glf::Feature::DepthTest);
                    gl::disable(glf::Feature::FaceCulling);
                    gl::clear(glf::Buffer::Mask::Stencil);
                    gl::depth_mask(gl::False);

                    gl::stencil_function(glf::Stencil::Function::Always, 0u, 0u);
                    gl::stencil_operation_separate(glf::Stencil::Face::Back , glf::Stencil::Action::Keep, glf::Stencil::Action::IncrementWrap, glf::Stencil::Action::Keep);
                    gl::stencil_operation_separate(glf::Stencil::Face::Front, glf::Stencil::Action::Keep, glf::Stencil::Action::DecrementWrap, glf::Stencil::Action::Keep);

                    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, sva->index_count());



                    pipelines.at("PointLighting")->bind();
                    gl::stencil_function(glf::Stencil::Function::NotEqual, 0u, 0xFFFF);
                    gl::disable(glf::Feature::DepthTest);
                    gl::enable(glf::Feature::Blending);
                    gl::blend_function(glf::Blending::Factor::SourceAlpha, glf::Blending::Factor::One);
                    gl::enable(glf::Feature::FaceCulling);
                    gl::cull_face(glf::Culling::Face::Front);

                    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, sva->index_count());
                }

                gl::depth_mask(gl::True);
                gl::cull_face(glf::Culling::Face::Back);
                gl::disable(glf::Feature::StencilTest);
            };





        render_meshes();

        for (fox::size_t index{}; const auto& pointLight : pointLights)
        {
            render_shadow_map_point(pointLight.position, sDimensions, nearPlane, farPlane, mmt, shadowCubemaps.at(index++));
        }



        constexpr fox::size_t colorAttachments{ 4 };
        for (const auto& i : std::ranges::views::iota(fox::size_t{ 0 }, colorAttachments))
        {
            gl::frame_buffer_read_buffer(gBufferMultisample->handle(), glf::FrameBuffer::Source::ColorAttachmentIndex + i);
            gl::frame_buffer_draw_buffer(gBuffer           ->handle(), glf::FrameBuffer::Source::ColorAttachmentIndex + i);
                
            gl::blit_framebuffer(gBufferMultisample->handle(), gBuffer->handle(), glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);
        }

        gl::blit_framebuffer(gBufferMultisample->handle(), gBuffer->handle(), glf::Buffer::Mask::Depth  , glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);
        gl::blit_framebuffer(gBufferMultisample->handle(), gBuffer->handle(), glf::Buffer::Mask::Stencil, glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);



        render_lighting(farPlane);


        //Ambient Lighting
        pBuffers.at(1)->bind(gfx::FrameBuffer::Target::Write);
        pipelines.at("AmbientLighting")->bind();
        gBuffer       ->bind_texture("Albedo", 0);
        pBuffers.at(0)->bind_texture("Color" , 1);

        gl::viewport(dimensions);
        gl::clear(glf::Buffer::Mask::All);
        gl::enable(glf::Feature::FaceCulling);
        gl::cull_face(glf::Culling::Face::Back);

        pva->bind();
        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());



        //Skybox
        gl::blit_framebuffer(gBuffer->handle(), pBuffers.at(1)->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);

        pipelines.at("Skybox")->bind();
        skybox->bind(0);

        gl::viewport(dimensions);
        gl::disable(glf::Feature::FaceCulling);
        gl::enable(glf::Feature::DepthTest);
        gl::depth_function(glf::DepthFunction::LessEqual);
        gl::disable(glf::Feature::Blending);

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
        gl::blit_framebuffer(pBuffers.at(1)->handle(), gl::handle_t{ 0 }, glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);
    }

    void OpenGLRenderer::render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
    {
        mmt.emplace_back(mesh, material, transform);
    }
    void OpenGLRenderer::render_debug(const fox::Transform& transform)
    {
        debugTransforms.emplace_back(transform);
    }
}
