#include "stdafx.hpp"
#include "OpenGLRenderer.hpp"

namespace fox::gfx::api
{
    OpenGLRenderer::OpenGLRenderer()
    {
        gl::enable(glf::Feature::Multisampling);
        gl::enable(glf::Feature::SeamlessCubeMapTexture);



        constexpr gl::uint8_t  samples   {  4u };
        constexpr gl::uint32_t lightCount{ 32u };
        constexpr gl::Vector2u viewportDimensions { 1280u,  720u };
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
        std::array<FM, 2> hdrBufferManifest { FM{ "Color", TF::RGBA16_FLOAT }, FM{ "Depth", RF::D24_UNORM_S8_UINT } };
        std::array<FM, 1> sBufferManifest   { FM{ "Depth", TF::D24_UNORM    }                                       };
        std::array<FM, 2> pBufferManifest   { FM{ "Color", TF::RGBA16_UNORM }, FM{ "Depth", RF::D24_UNORM_S8_UINT } };
        std::array<FM, 1> scBufferManifest  { FM{ "Depth", CF::D24_UNORM    }                                       };



        m_gBuffer                 = gfx::FrameBuffer           ::create(viewportDimensions ,          gBufferManifest  );
        m_gBufferMultisample      = gfx::FrameBufferMultisample::create(viewportDimensions , samples, gBufferManifest  );
        m_sBuffer                 = gfx::FrameBuffer           ::create(shadowMapDimensions,          sBufferManifest  );
        m_hdrBuffer               = gfx::FrameBuffer           ::create(viewportDimensions ,          hdrBufferManifest);
        m_pBuffers.at(0)          = gfx::FrameBuffer           ::create(viewportDimensions ,          pBufferManifest  );
        m_pBuffers.at(1)          = gfx::FrameBuffer           ::create(viewportDimensions ,          pBufferManifest  );
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
        gl::texture_parameter(depthTexture->handle(), glp::magnification_filter{ glf::Texture::MagnificationFilter::Nearest });
        gl::texture_parameter(depthTexture->handle(), glp::minification_filter { glf::Texture::MinificationFilter ::Nearest });
        gl::texture_parameter(depthTexture->handle(), glp::border_color        { borderColor });




        
        const auto& add_to_pipeline = [this](const std::string& identifier, const std::string& vertex, std::optional<std::string> geometry,const std::string& fragment)
            {
                const std::filesystem::path dir{ "shaders/compiled" };

                if (geometry.has_value())
                {
                    const auto& shaders = api::shaders_from_binaries<gfx::Shader>(dir / vertex, dir / geometry.value(), dir / fragment);
                    m_pipelines.emplace(identifier, gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = shaders.at(0), .geometry = shaders.at(1), .fragment = shaders.at(2) }));
                }
                else
                {
                    const auto& shaders = api::shaders_from_binaries<gfx::Shader>(dir / vertex, dir / fragment);
                    m_pipelines.emplace(identifier, gfx::Pipeline::create(gfx::Pipeline::Layout{ .vertex = shaders.at(0), .fragment = shaders.at(1) }));
                }
            };

        add_to_pipeline("DeferredMesh", "mesh_deferred.vert.spv", {}, "mesh_deferred.frag.spv");
        add_to_pipeline("Debug"       , "transform_mvp.vert.spv", {}, "debug.frag.spv");
        add_to_pipeline("PBR"         , "pbr.vert.spv"          , {}, "pbr.frag.spv");
        add_to_pipeline("ConvertEqui" , "cubemap.vert.spv"      , {}, "convert_equirectangular.frag.spv");
        add_to_pipeline("Background"  , "background.vert.spv"   , {}, "background.frag.spv");
        add_to_pipeline("Irradiance"  , "cubemap.vert.spv"      , {}, "irradiance.frag.spv");
        add_to_pipeline("PreFilter"   , "cubemap.vert.spv"      , {}, "prefilter.frag.spv");
        add_to_pipeline("BRDF"        , "brdf.vert.spv"         , {}, "brdf.frag.spv");





        //PBR setup
        gl::Matrix4f captureProjection = gfx::Projection{ gfx::Projection::perspective_p{ 1.0f, 90.0f, 0.1f, 10.0f } }.matrix();
        const std::array<gl::Matrix4f, 6> captureViews =
        {
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  1.0f,  0.0f,  0.0f }, gl::Vector3f{ 0.0f, -1.0f,  0.0f }),
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{ -1.0f,  0.0f,  0.0f }, gl::Vector3f{ 0.0f, -1.0f,  0.0f }),
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  0.0f,  1.0f,  0.0f }, gl::Vector3f{ 0.0f,  0.0f,  1.0f }),
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  0.0f, -1.0f,  0.0f }, gl::Vector3f{ 0.0f,  0.0f, -1.0f }),
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  0.0f,  0.0f,  1.0f }, gl::Vector3f{ 0.0f, -1.0f,  0.0f }),
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  0.0f,  0.0f, -1.0f }, gl::Vector3f{ 0.0f, -1.0f,  0.0f }),
        };

        const auto& cva = gfx::Geometry::Cube::mesh() ->vertexArray;
        const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;



        //Load HDR environment texture
        const fox::Vector2u envDimensions{ 512u, 512u };
        const std::array<gfx::api::FrameBuffer::Manifest, 1> manifest{ FM{ "Depth", RF::D24_UNORM }, };
        auto frameBuffer     = gfx::FrameBuffer::create(envDimensions, manifest);
        const auto& rb       = frameBuffer->find_render_buffer("Depth");
        auto hdrImage        = io::load<io::Asset::Image>("textures/venice_sunset.hdr", fox::Image::Format::RGB32_FLOAT);
        auto hdrTex          = gfx::Texture2D::create(gfx::Texture2D::Format::RGB32_FLOAT, gfx::Texture2D::Filter::Trilinear, gfx::Texture2D::Wrapping::ClampToEdge, hdrImage.dimensions(), hdrImage.data());
        m_environmentCubemap = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::None, gfx::Cubemap::Wrapping::ClampToEdge, envDimensions);



        //Convert HDR texture to cubemap
        m_pipelines.at("ConvertEqui")->bind();
        m_matricesBuffer->bind_index(2);
        m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));

        gl::viewport(envDimensions);
        gl::frame_buffer_draw_buffer(frameBuffer->handle(), glf::FrameBuffer::Source::ColorIndex);

        frameBuffer->bind(gfx::FrameBuffer::Target::Write);
        hdrTex->bind(0);
        cva->bind();

        for (fox::uint32_t index{}; const auto& view : captureViews)
        {
            m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

            gl::frame_buffer_texture_layer(frameBuffer->handle(), m_environmentCubemap->handle(), glf::FrameBuffer::Attachment::ColorIndex, 0, index++);
            gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
        }



        //Irradiance step
        const fox::Vector2u cvDimensions{ 32u, 32u };

        m_irradianceCubemap = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::None, gfx::Cubemap::Wrapping::ClampToEdge, cvDimensions);

        m_pipelines.at("Irradiance")->bind();
        m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));
        m_environmentCubemap->bind(0);

        gl::viewport(cvDimensions);
        gl::frame_buffer_draw_buffer(frameBuffer->handle(), glf::FrameBuffer::Source::ColorIndex);
        gl::render_buffer_storage(rb->handle(), glf::RenderBuffer::Format::D24_UNORM, cvDimensions);

        frameBuffer->bind(gfx::FrameBuffer::Target::Write);
        cva->bind();

        for (fox::uint32_t index{}; const auto& view : captureViews)
        {
            m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

            gl::frame_buffer_texture_layer(frameBuffer->handle(), m_irradianceCubemap->handle(), glf::FrameBuffer::Attachment::ColorIndex, 0, index++);
            gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
        }



        gl::texture_parameter(m_environmentCubemap->handle(), glp::magnification_filter{ glf::Texture::MagnificationFilter::Linear             });
        gl::texture_parameter(m_environmentCubemap->handle(), glp::minification_filter { glf::Texture::MinificationFilter ::LinearMipmapLinear });
        gl::generate_texture_mipmap(m_environmentCubemap->handle());



        //PreFilter step
        const fox::Vector2u reflectionDimensions{ 128u, 128u };

        auto preFilterBuffer = gfx::UniformBuffer<unf::PreFilter>::create();
        preFilterBuffer->bind_index(5);

        m_preFilterCubemap = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::Trilinear, gfx::Cubemap::Wrapping::ClampToEdge, reflectionDimensions);

        m_pipelines.at("PreFilter")->bind();
        m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));
        m_environmentCubemap->bind(0);
        
        frameBuffer->bind(gfx::FrameBuffer::Target::Write);
        cva->bind();

        fox::uint32_t maxMipLevels{ m_preFilterCubemap->mipmap_levels() };
        for (const auto& mip : std::views::iota(0u, maxMipLevels))
        {
            const fox::Vector2u mipDimensions{ reflectionDimensions.x * std::pow(0.5f, mip), reflectionDimensions.y * std::pow(0.5f, mip) };
            const auto& roughness = static_cast<fox::float32_t>(mip) / (maxMipLevels - 1u);
            preFilterBuffer->copy(unf::PreFilter{ envDimensions.x, roughness });

            gl::viewport(mipDimensions);
            gl::render_buffer_storage(rb->handle(), glf::RenderBuffer::Format::D24_UNORM, mipDimensions);

            for (fox::uint32_t index{}; const auto& view : captureViews)
            {
                m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

                gl::frame_buffer_texture_layer(frameBuffer->handle(), m_preFilterCubemap->handle(), glf::FrameBuffer::Attachment::ColorIndex, mip, index++);
                gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
            }
        }



        //BRDF LUT step
        m_brdfTexture = gfx::Texture2D::create(gfx::Texture2D::Format::RG16_FLOAT, gfx::Texture2D::Filter::None, gfx::Texture2D::Wrapping::ClampToEdge, envDimensions);
        m_pipelines.at("BRDF")->bind();

        gl::viewport(envDimensions);
        gl::frame_buffer_texture(frameBuffer->handle(), m_brdfTexture->handle(), glf::FrameBuffer::Attachment::ColorIndex, 0);
        gl::render_buffer_storage(rb->handle(), glf::RenderBuffer::Format::D24_UNORM, envDimensions);
        gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

        pva->bind();
        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());
    }

    void OpenGLRenderer::start(gfx::RenderInfo renderInfo)
    {
        m_renderInfo = renderInfo;

        const auto& camera           = m_renderInfo.camera;
        const auto& transform        = m_renderInfo.cameraTransform;
        const auto& viewMatrix       = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
        const auto& projectionMatrix = camera.projection().matrix();

        m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraBuffer  ->copy    (unf::Camera{ fox::Vector4f{ transform.position, 1.0f } });



        m_mmt                           .clear();
        m_lights                        .clear();
        m_shadowCastingPointLights      .clear();
        m_shadowCastingDirectionalLights.clear();
        m_debugTransforms               .clear();



        fox::size_t shadowCastingLightCount{ 0u };
        constexpr auto maximumShadowCastingLights{ 4 };

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

            if (light.isShadowCasting and shadowCastingLightCount < maximumShadowCastingLights)
            {
                switch (light.type)
                {
                    case fox::Light::Type::Area:        throw std::exception{ "" };                            break;
                    case fox::Light::Type::Directional: m_shadowCastingDirectionalLights.emplace_back(result); break;
                    case fox::Light::Type::Point:       m_shadowCastingPointLights      .emplace_back(result); break;
                    case fox::Light::Type::Spot:        throw std::exception{ "" };                            break;
                }

                ++shadowCastingLightCount;
            }

            m_lights.emplace_back(std::move(result));
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



        gl::viewport(dimensions);

        
        //Render meshes into gBuffer
        render_meshes(m_gBufferMultisample, m_pipelines.at("DeferredMesh"));

        //Render shadow map for each shadow-casting point light (up to 4)
        for (fox::size_t index{}; const auto& light : m_shadowCastingPointLights)
        {
            //render_shadow_map_point(light, m_shadowCubemaps.at(index++));
        }

        //Blit Position, Albedo, Normal, and RoughnessMetallic color buffers into the regular gBuffer
        //It is necessary to resolve the multisampled gBuffer into the regular gBuffer
        constexpr fox::size_t colorAttachments{ 4 };
        for (const auto& i : std::views::iota(fox::size_t{ 0 }, colorAttachments))
        {
            gl::frame_buffer_read_buffer(m_gBufferMultisample->handle(), glf::FrameBuffer::Source::ColorIndex + i);
            gl::frame_buffer_draw_buffer(m_gBuffer           ->handle(), glf::FrameBuffer::Source::ColorIndex + i);
                
            gl::blit_frame_buffer(m_gBufferMultisample->handle(), m_gBuffer->handle(), glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, m_gBufferMultisample->dimensions(), m_gBuffer->dimensions());
        }

        //Blit depth and stencil information into the regular gBuffer
        gl::blit_frame_buffer(m_gBufferMultisample->handle(), m_gBuffer->handle(), glf::Buffer::Mask::Depth  , glf::FrameBuffer::Filter::Nearest, m_gBufferMultisample->dimensions(), m_gBuffer->dimensions());
        gl::blit_frame_buffer(m_gBufferMultisample->handle(), m_gBuffer->handle(), glf::Buffer::Mask::Stencil, glf::FrameBuffer::Filter::Nearest, m_gBufferMultisample->dimensions(), m_gBuffer->dimensions());



        //Lighting calculations
        render_lighting(m_pBuffers.at(0));

        //render_lighting(m_hdrBuffer);
        //gl::blit_framebuffer(m_hdrBuffer->handle(), m_pBuffers.at(0)->handle(), glf::Buffer::Mask::All, glf::FrameBuffer::Filter::Nearest, m_hdrBuffer->dimensions(), m_pBuffers.at(0)->dimensions());
        //render_hdr();
        //Skybox
        //render_skybox(m_pBuffers.at(0), m_gBuffer);




        m_pBuffers.at(0)->bind(gfx::FrameBuffer::Target::Write);
        m_pipelines.at("Background")->bind();
        m_environmentCubemap->bind(0);
        //imgtex->bind(0);

        gl::disable(glf::Feature::Blending);
        gl::disable(glf::Feature::FaceCulling);
        gl::enable(glf::Feature::DepthTest);
        gl::depth_function(glf::DepthFunction::LessEqual);

        const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
        cva->bind();
        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());





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
        gl::blit_frame_buffer(m_pBuffers.at(0)->handle(), gl::DefaultFrameBuffer, glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, m_pBuffers.at(0)->dimensions(), dimensions);
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
    void OpenGLRenderer::render_shadow_map_point(const unf::Light& light, std::shared_ptr<gfx::FrameBuffer> target)
    {
        const auto& position    = gl::Vector3f{ light.position };
        const auto& dimensions  = target->dimensions();
        const auto& aspectRatio = static_cast<fox::float32_t>(dimensions.x) / dimensions.y;
        const auto& fov         = 90.0f;
        const auto& nearPlane   = 0.1f;
        const auto& projection  = gfx::Projection{ gfx::Projection::perspective_p{ aspectRatio, fov, nearPlane, m_shadowFarPlane } };

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
        m_lightShadowBuffer->copy({ fox::Vector4f{ position, 1.0f }, m_shadowFarPlane });



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
    void OpenGLRenderer::render_lighting(std::shared_ptr<gfx::FrameBuffer> target)
    {
        target->bind(api::FrameBuffer::Target::Write);
        gl::clear(glf::Buffer::Mask::All);

        gl::blit_frame_buffer(m_gBuffer->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, m_gBuffer->dimensions(), target->dimensions());



        m_pipelines.at("PBR")->bind();
        m_gBuffer->bind_texture("Position", 0);
        m_gBuffer->bind_texture("Albedo"  , 1);
        m_gBuffer->bind_texture("Normal"  , 2);
        m_gBuffer->bind_texture("ARM"     , 3);

        m_irradianceCubemap ->bind(4);
        m_preFilterCubemap ->bind(5);
        m_brdfTexture->bind(6);

        gl::viewport(target->dimensions());

        const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;
        pva->bind();
        
        gl::depth_mask(gl::False);
        gl::disable(glf::Feature::DepthTest);
        gl::enable(glf::Feature::Blending);
        gl::blend_function(glf::Blending::Factor::SourceAlpha, glf::Blending::Factor::One);
        gl::disable(glf::Feature::FaceCulling);

        for (fox::size_t index{}; const auto& light : m_lights)
        {
            fox::Transform sphereTransform{ light.position, fox::Vector3f{}, fox::Vector3f{light.radius} };

            m_matricesBuffer   ->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(sphereTransform.matrix()));
            m_lightBuffer      ->copy({ light.position, light.color, light.radius, light.linearFalloff, light.quadraticFalloff });

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());
        }

        gl::depth_mask(gl::True);
    }
    void OpenGLRenderer::render_lighting_shadow(std::shared_ptr<gfx::FrameBuffer> target)
    {
        target->bind(api::FrameBuffer::Target::Write);
        gl::clear(glf::Buffer::Mask::All);

        gl::blit_frame_buffer(m_gBuffer->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, m_gBuffer->dimensions(), target->dimensions());



        m_gBuffer->bind_texture("Position", 0);
        m_gBuffer->bind_texture("Albedo"  , 1);
        m_gBuffer->bind_texture("Normal"  , 2);
        m_gBuffer->bind_texture("ARM"     , 3);

        gl::viewport(target->dimensions());
        //gl::enable(glf::Feature::StencilTest);

        const auto& sva = gfx::Geometry::Sphere::mesh()->vertexArray;
        sva->bind();

        for (fox::size_t index{}; const auto& light : m_shadowCastingPointLights)
        {
            fox::Transform sphereTransform{ light.position, fox::Vector3f{}, fox::Vector3f{light.radius} };

            //m_pipelines.at("LightingStencil")->bind();
            m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(sphereTransform.matrix()));
            m_lightBuffer->copy({ light.position, light.color, light.radius, light.linearFalloff, light.quadraticFalloff });
            m_lightShadowBuffer->copy({ light.position, m_shadowFarPlane });
            //m_shadowCubemaps.at(index++)->bind_cubemap("Depth", 4);



            //gl::enable(glf::Feature::DepthTest);
            //gl::disable(glf::Feature::FaceCulling);
            //gl::clear(glf::Buffer::Mask::Stencil);
            //gl::depth_mask(gl::False);
            //gl::stencil_function(glf::Stencil::Function::Always, 0u, 0u);
            //gl::stencil_operation_separate(glf::Stencil::Face::Back, glf::Stencil::Action::Keep, glf::Stencil::Action::IncrementWrap, glf::Stencil::Action::Keep);
            //gl::stencil_operation_separate(glf::Stencil::Face::Front, glf::Stencil::Action::Keep, glf::Stencil::Action::DecrementWrap, glf::Stencil::Action::Keep);

            //gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, sva->index_count());


            m_pipelines.at("PBR")->bind();
            //m_pipelines.at("PointLighting")->bind();

            //gl::stencil_function(glf::Stencil::Function::NotEqual, 0u, 0xFFFF);
            //gl::stencil_operation(glf::Stencil::Action::Keep, glf::Stencil::Action::Keep, glf::Stencil::Action::Keep);
            gl::disable(glf::Feature::DepthTest);
            gl::enable(glf::Feature::Blending);
            gl::blend_function(glf::Blending::Factor::SourceAlpha, glf::Blending::Factor::One);
            gl::enable(glf::Feature::FaceCulling);
            gl::cull_face(glf::Culling::Face::Front);

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, sva->index_count());
        }

        //gl::depth_mask(gl::True);
        gl::cull_face(glf::Culling::Face::Back);
        //gl::disable(glf::Feature::StencilTest);

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

        gl::blit_frame_buffer(previous->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, previous->dimensions(), target->dimensions());

        gl::viewport(target->dimensions());
        gl::disable(glf::Feature::FaceCulling);
        gl::enable(glf::Feature::DepthTest);
        gl::depth_function(glf::DepthFunction::LessEqual);
        gl::disable(glf::Feature::Blending);

        const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
        cva->bind();

        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
    }
    void OpenGLRenderer::render_hdr()
    {
        gl::Matrix4f captureProjection = gfx::Projection{ gfx::Projection::perspective_p{ 1.0f, 90.0f, 0.1f, 10.0f } }.matrix();
        const std::array<gl::Matrix4f, 6> captureViews =
        {
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  1.0f,  0.0f,  0.0f }, gl::Vector3f{ 0.0f, -1.0f,  0.0f }), 
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{ -1.0f,  0.0f,  0.0f }, gl::Vector3f{ 0.0f, -1.0f,  0.0f }), 
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  0.0f,  1.0f,  0.0f }, gl::Vector3f{ 0.0f,  0.0f,  1.0f }), 
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  0.0f, -1.0f,  0.0f }, gl::Vector3f{ 0.0f,  0.0f, -1.0f }), 
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  0.0f,  0.0f,  1.0f }, gl::Vector3f{ 0.0f, -1.0f,  0.0f }), 
           glm::lookAt(gl::Vector3f{ 0.0f, 0.0f, 0.0f }, gl::Vector3f{  0.0f,  0.0f, -1.0f }, gl::Vector3f{ 0.0f, -1.0f,  0.0f }), 
        };



















        //imgfb->bind(gfx::FrameBuffer::Target::Write);
        //m_pipelines.at("ConvertEqui2")->bind();
        //imgcub->bind(0);
        //m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));

        //gl::viewport(gl::Vector2u{ 512u, 512u });

        //for (fox::uint32_t index{}; const auto& view : captureViews)
        //{
        //    m_matricesBuffer->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

        //    gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

        //    const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
        //    cva->bind();
        //    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());

        //    ++index;
        //}
    }
}
