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



        m_gBuffer                 = gfx::FrameBuffer           ::create(viewportDimensions ,           gBufferManifest );
        m_gBufferMultisample      = gfx::FrameBufferMultisample::create(viewportDimensions ,  samples, gBufferManifest );
        m_sBuffer                 = gfx::FrameBuffer           ::create(shadowMapDimensions,           sBufferManifest );
        m_pBuffers.at(0)          = gfx::FrameBuffer           ::create(viewportDimensions ,           ppBufferManifest);
        m_pBuffers.at(1)          = gfx::FrameBuffer           ::create(viewportDimensions ,           ppBufferManifest);
        m_shadowCubemaps          = {
            gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
            gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
            gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
            gfx::FrameBuffer::create(shadowMapDimensions, scBufferManifest),
        };

        m_contextBuffer           = gfx::UniformBuffer<unf::Context>                 ::create();
        m_matricesBuffer          = gfx::UniformBuffer<unf::Matrices>                ::create();
        m_materialBuffer          = gfx::UniformBuffer<unf::Material>                ::create();
        m_cameraBuffer            = gfx::UniformBuffer<unf::Camera>                  ::create();
        m_lightBuffer             = gfx::UniformBuffer<unf::Light>                   ::create();
        m_lightShadowBuffer       = gfx::UniformBuffer<unf::LightShadow>             ::create();
        m_shadowProjectionsBuffer = gfx::UniformArrayBuffer<unf::ShadowProjection, 6>::create();
            


        const auto& depthTexture = m_sBuffer->find_texture("Depth");
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

        m_pipelines.emplace("DeferredMesh",        gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = deferredMeshShaders.at(0),                                              .fragment = deferredMeshShaders.at(1) }));
        m_pipelines.emplace("Lighting",            gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = lightingShaders.at(0),                                                  .fragment = lightingShaders.at(1) }));
        m_pipelines.emplace("PointLighting",       gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = pointLightingShaders.at(0),                                             .fragment = pointLightingShaders.at(1) }));
        m_pipelines.emplace("DirectionalLighting", gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = directionalLightingShaders.at(0),                                       .fragment = directionalLightingShaders.at(1) }));
        m_pipelines.emplace("LightingStencil",     gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = lightingStencilShaders.at(0),                                           .fragment = lightingStencilShaders.at(1) }));
        m_pipelines.emplace("AmbientLighting",     gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = ambientLightingShaders.at(0),                                           .fragment = ambientLightingShaders.at(1) }));
        m_pipelines.emplace("DirectionalShadow",   gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = directionalShadowShaders.at(0),                                         .fragment = directionalShadowShaders.at(1) }));
        m_pipelines.emplace("PointShadow",         gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = pointShadowShaders.at(0),         .geometry = pointShadowShaders.at(1), .fragment = pointShadowShaders.at(2) }));
        m_pipelines.emplace("Skybox",              gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = skyboxShaders.at(0),                                                    .fragment = skyboxShaders.at(1) }));
        m_pipelines.emplace("Debug",               gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = debugShaders.at(0),                                                     .fragment = debugShaders.at(1) }));
    }

    void OpenGLRenderer::start(gfx::RenderInfo renderInfo)
    {
        m_renderInfo = renderInfo;

        const auto& camera              = m_renderInfo.camera;
        const auto& transform           = m_renderInfo.cameraTransform;
        const auto& viewMatrix          = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
        const auto& projectionMatrix    = camera.projection().matrix();

        m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraBuffer  ->copy    (unf::Camera{ fox::Vector4f{ transform.position, 1.0f } });

        

        m_mmt              .clear();
        m_sceneLights      .clear();
        m_pointLights      .clear();
        m_directionalLights.clear();
        m_debugTransforms  .clear();



        constexpr auto maximumPointLights{ 4 };
        for (const auto& [light, position] : m_renderInfo.lights)
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
                    case fox::Light::Type::Point:       if (m_pointLights.size() < maximumPointLights) m_pointLights.emplace_back(std::move(result)); break;
                    case fox::Light::Type::Directional:
                    case fox::Light::Type::Spot:
                    case fox::Light::Type::Area:

                    default: m_sceneLights.emplace_back(std::move(result));
                }
            }
            else
            {
                m_sceneLights.emplace_back(std::move(result));
            }
        }
    }

    void OpenGLRenderer::finish()
    {
        constexpr gl::Vector2u  dimensions{ 1280u,  720u };
        constexpr gl::Vector2u sDimensions{ 2048u, 2048u };

        //Bind Uniform Buffers to correct indices
        m_contextBuffer->          bind_index( 0);
        m_cameraBuffer->           bind_index( 1);
        m_matricesBuffer->         bind_index( 2);
        m_materialBuffer->         bind_index( 3);
        m_lightBuffer->            bind_index( 4);
        m_lightShadowBuffer->      bind_index( 6);
        m_shadowProjectionsBuffer->bind_index(13);

        m_contextBuffer->copy(unf::Context{ dimensions, input::cursor_position(), fox::Time::since_epoch(), fox::Time::delta() });





        //Main rendering process
        
        //Render meshes into gBuffer
        render_meshes(m_gBufferMultisample, m_pipelines.at("DeferredMesh"));

        //Render shadow map for each shadow-casting point light (up to 4)
        for (const auto& i : std::views::iota(0u, m_pointLights.size()))
            render_shadow_map(m_pointLights.at(i), m_shadowCubemaps.at(i));

        //Blit Position, Albedo, Normal, and RoughnessMetallic color buffers into the regular gBuffer
        //It is necessary to resolve the multisampled gBuffer into the regular gBuffer
        constexpr fox::size_t colorAttachments{ 4 };
        for (const auto& i : std::views::iota(fox::size_t{ 0 }, colorAttachments))
        {
            gl::frame_buffer_read_buffer(m_gBufferMultisample->handle(), glf::FrameBuffer::Source::ColorAttachmentIndex + i);
            gl::frame_buffer_draw_buffer(m_gBuffer           ->handle(), glf::FrameBuffer::Source::ColorAttachmentIndex + i);
                
            gl::blit_framebuffer(m_gBufferMultisample->handle(), m_gBuffer->handle(), glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, m_gBufferMultisample->dimensions(), m_gBuffer->dimensions());
        }

        //Blit depth and stencil information into the regular gBuffer
        gl::blit_framebuffer(m_gBufferMultisample->handle(), m_gBuffer->handle(), glf::Buffer::Mask::Depth  , glf::FrameBuffer::Filter::Nearest, m_gBufferMultisample->dimensions(), m_gBuffer->dimensions());
        gl::blit_framebuffer(m_gBufferMultisample->handle(), m_gBuffer->handle(), glf::Buffer::Mask::Stencil, glf::FrameBuffer::Filter::Nearest, m_gBufferMultisample->dimensions(), m_gBuffer->dimensions());

        //Lighting calculations
        render_lighting_shadow (m_pBuffers.at(0));
        render_ambient_lighting(m_pBuffers.at(1), m_pBuffers.at(0));

        //Skybox
        render_skybox(m_pBuffers.at(1), m_gBuffer);





        //Render simple cubes for debugging
#ifdef FOX_DEBUG
        m_pipelines.at("Debug")->bind();

        for (const auto& transform : m_debugTransforms)
        {
            m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, gfx::Geometry::Cube::mesh()->vertexArray->index_count());
        }
#endif





        //Blit the final result into the default framebuffer
        gl::blit_framebuffer(m_pBuffers.at(1)->handle(), gl::DefaultFrameBuffer, glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, m_pBuffers.at(1)->dimensions(), dimensions);
    }

    void OpenGLRenderer::render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
    {
        m_mmt.emplace_back(mesh, material, transform);
    }
    void OpenGLRenderer::render_debug(const fox::Transform& transform)
    {
        m_debugTransforms.emplace_back(transform);
    }
    
    void OpenGLRenderer::render_meshes(std::shared_ptr<gfx::FrameBufferMultisample> frameBuffer, std::shared_ptr<gfx::Pipeline> shader)
    {
        frameBuffer->bind(gfx::FrameBuffer::Target::Write);
        shader->bind();

        gl::viewport      (frameBuffer->dimensions());
        gl::clear         (glf::Buffer::Mask::All);
        gl::enable        (glf::Feature::FaceCulling);
        gl::cull_face     (glf::Culling::Face::Back);
        gl::front_face    (glf::Orientation::CounterClockwise);
        gl::enable        (glf::Feature::DepthTest);
        gl::depth_function(glf::DepthFunction::Less);
        gl::disable       (glf::Feature::Blending);

        for (const auto& _ : m_mmt)
        {
            const auto& [mesh, material, transform] = _;

            m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
            m_materialBuffer->copy    (unf::Material{ material->color, material->roughnessFactor, material->metallicFactor });

            mesh    ->vertexArray->bind();
            material->albedo     ->bind(0);
            material->normal     ->bind(1);
            material->arm        ->bind(2);

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, mesh->vertexArray->index_count());
        }
    }
    void OpenGLRenderer::render_shadow_map(const unf::Light& light, std::shared_ptr<gfx::FrameBuffer> target)
    {
        const auto& position    = gl::Vector3f{ light.position };
        const auto& dimensions  = target->dimensions();
        const auto& aspectRatio = static_cast<fox::float32_t>(dimensions.x) / dimensions.y;
        const auto& fov         = 90.0f;
        const auto& nearPlane   = 0.1f;
        const auto& farPlane    = 100.0f;
        const auto& projection  = gfx::Projection{ gfx::Projection::perspective_p{ aspectRatio, fov, nearPlane, farPlane } };

        std::array<const unf::ShadowProjection, 6> shadowTransforms{
            projection.matrix() * glm::lookAt(position, position + gl::Vector3f{  1.0, 0.0, 0.0 }, gl::Vector3f{ 0.0,-1.0, 0.0 }), 
            projection.matrix() * glm::lookAt(position, position + gl::Vector3f{ -1.0, 0.0, 0.0 }, gl::Vector3f{ 0.0,-1.0, 0.0 }), 
            projection.matrix() * glm::lookAt(position, position + gl::Vector3f{  0.0, 1.0, 0.0 }, gl::Vector3f{ 0.0, 0.0, 1.0 }), 
            projection.matrix() * glm::lookAt(position, position + gl::Vector3f{  0.0,-1.0, 0.0 }, gl::Vector3f{ 0.0, 0.0,-1.0 }), 
            projection.matrix() * glm::lookAt(position, position + gl::Vector3f{  0.0, 0.0, 1.0 }, gl::Vector3f{ 0.0,-1.0, 0.0 }), 
            projection.matrix() * glm::lookAt(position, position + gl::Vector3f{  0.0, 0.0,-1.0 }, gl::Vector3f{ 0.0,-1.0, 0.0 }), 
        };



        target->bind(api::FrameBuffer::Target::Write);
        m_pipelines.at("PointShadow")->bind();
        m_shadowProjectionsBuffer->copy(shadowTransforms);
        m_lightShadowBuffer->copy({ fox::Vector4f{ position, 1.0f }, farPlane });



        gl::viewport(dimensions);
        gl::clear(glf::Buffer::Mask::Depth);
        gl::enable(glf::Feature::FaceCulling);
        gl::cull_face(glf::Culling::Face::Back);
        gl::front_face(glf::Orientation::CounterClockwise);
        gl::enable(glf::Feature::DepthTest);
        gl::depth_function(glf::DepthFunction::Less);
        gl::disable(glf::Feature::Blending);

        for (const auto& _ : m_mmt)
        {
            const auto& [mesh, material, transform] = _;

            m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));

            mesh->vertexArray->bind();

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, mesh->vertexArray->index_count());
        }
    }
    void OpenGLRenderer::render_lighting_shadow(std::shared_ptr<gfx::FrameBuffer> target)
    {
        target->bind(api::FrameBuffer::Target::Write);
        gl::clear(glf::Buffer::Mask::All);

        gl::blit_framebuffer(m_gBuffer->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, m_gBuffer->dimensions(), target->dimensions());



        m_gBuffer->bind_texture("Position", 0);
        m_gBuffer->bind_texture("Albedo", 1);
        m_gBuffer->bind_texture("Normal", 2);
        m_gBuffer->bind_texture("ARM", 3);

        gl::viewport(target->dimensions());
        gl::enable(glf::Feature::StencilTest);

        const auto& farPlane = 100.0f;
        const auto& sva = gfx::Geometry::Sphere::mesh()->vertexArray;
        sva->bind();

        for (fox::size_t index{}; const auto & light : m_pointLights)
        {
            fox::Transform sphereTransform{ light.position, fox::Vector3f{}, fox::Vector3f{light.radius} };

            m_pipelines.at("LightingStencil")->bind();
            m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(sphereTransform.matrix()));
            m_lightBuffer->copy({ light.position, light.color, light.radius, light.linearFalloff, light.quadraticFalloff });
            m_lightShadowBuffer->copy({ light.position, farPlane });
            m_shadowCubemaps.at(index++)->bind_cubemap("Depth", 4);



            gl::enable(glf::Feature::DepthTest);
            gl::disable(glf::Feature::FaceCulling);
            gl::clear(glf::Buffer::Mask::Stencil);
            gl::depth_mask(gl::False);
            gl::stencil_function(glf::Stencil::Function::Always, 0u, 0u);
            gl::stencil_operation_separate(glf::Stencil::Face::Back, glf::Stencil::Action::Keep, glf::Stencil::Action::IncrementWrap, glf::Stencil::Action::Keep);
            gl::stencil_operation_separate(glf::Stencil::Face::Front, glf::Stencil::Action::Keep, glf::Stencil::Action::DecrementWrap, glf::Stencil::Action::Keep);

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, sva->index_count());



            m_pipelines.at("PointLighting")->bind();

            gl::stencil_function(glf::Stencil::Function::NotEqual, 0u, 0xFFFF);
            gl::stencil_operation(glf::Stencil::Action::Keep, glf::Stencil::Action::Keep, glf::Stencil::Action::Keep);
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

    }
    void OpenGLRenderer::render_ambient_lighting(std::shared_ptr<gfx::FrameBuffer> target, std::shared_ptr<gfx::FrameBuffer> previous)
    {
        target->bind(gfx::FrameBuffer::Target::Write);
        m_pipelines.at("AmbientLighting")->bind();
        m_gBuffer->bind_texture("Albedo", 0);
        previous ->bind_texture("Color" , 1);

        gl::viewport(target->dimensions());
        gl::clear(glf::Buffer::Mask::All);
        gl::enable(glf::Feature::FaceCulling);
        gl::cull_face(glf::Culling::Face::Back);

        const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;
        pva->bind();

        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());
    }
    void OpenGLRenderer::render_skybox(std::shared_ptr<gfx::FrameBuffer> target, std::shared_ptr<gfx::FrameBuffer> previous)
    {
        if (!m_renderInfo.skybox) return;

        m_pipelines.at("Skybox")->bind();
        m_renderInfo.skybox->bind(0);

        gl::blit_framebuffer(previous->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, previous->dimensions(), target->dimensions());

        gl::viewport(target->dimensions());
        gl::disable(glf::Feature::FaceCulling);
        gl::enable(glf::Feature::DepthTest);
        gl::depth_function(glf::DepthFunction::LessEqual);
        gl::disable(glf::Feature::Blending);

        const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
        cva->bind();

        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
    }
}
