#include "stdafx.hpp"
#include "OpenGLRenderer.hpp"

namespace fox::gfx::api
{
    OpenGLRenderer::OpenGLRenderer()
    {
        gl::enable<glf::Feature::SeamlessCubeMapTexture>();



        constexpr fox::uint32_t multisamples{ 4u };
        constexpr fox::uint32_t lightCount{ 32u };
        constexpr fox::Vector2u viewportDimensions { 1280u,  720u };
        constexpr fox::Vector2u shadowMapDimensions{ 2048u, 2048u };

        using FS = gfx::FrameBuffer::Specification;
        using TF = gfx::Texture2D::Format;
        using RF = gfx::RenderBuffer::Format;
        using CF = gfx::Cubemap::Format;
        using FA = gfx::FrameBuffer::Attachment;
        {
            "Position",     FA::Color0      , TF::RGB16_FLOAT,
            "Albedo",       FA::Color1      , TF::RGBA8_UNORM,
            "Normal",       FA::Color2      , TF::RGB16_FLOAT,
            "ARM",          FA::Color3      , TF::RGB16_UNORM,
            "DepthStencil", FA::DepthStencil, RF::D24_UNORM_S8_UINT;
        }
        std::array<FS, 5> gBufferManifest {
            FS{ "Position",     TF::RGB16_FLOAT },
            FS{ "Albedo",       TF::RGBA8_UNORM  },
            FS{ "Normal",       TF::RGB16_FLOAT },
            FS{ "ARM",          TF::RGB16_UNORM  },
            FS{ "DepthStencil", RF::D24_UNORM_S8_UINT },
        };
        std::array<FS, 2> hdrBufferManifest { FS{ "Color", TF::RGBA16_FLOAT }, FS{ "Depth", RF::D24_UNORM_S8_UINT } };
        std::array<FS, 1> sBufferManifest   { FS{ "Depth", TF::D24_UNORM    }                                       };
        std::array<FS, 2> pBufferManifest   { FS{ "Color", TF::RGBA16_UNORM }, FS{ "Depth", RF::D24_UNORM_S8_UINT } };
        std::array<FS, 1> scBufferManifest  { FS{ "Depth", CF::D24_UNORM    }                                       };



        m_gBuffer                 = gfx::FrameBuffer::create(viewportDimensions , gBufferManifest  );
        m_sBuffer                 = gfx::FrameBuffer::create(shadowMapDimensions, sBufferManifest  );
        m_pBuffers.at(0)          = gfx::FrameBuffer::create(viewportDimensions , pBufferManifest  );
        m_pBuffers.at(1)          = gfx::FrameBuffer::create(viewportDimensions , pBufferManifest  );

        m_contextUniform           = gfx::UniformBuffer<unf::Context> ::create();
        m_matricesUniform          = gfx::UniformBuffer<unf::Matrices>::create();
        m_materialUniform          = gfx::UniformBuffer<unf::Material>::create();
        m_cameraUniform            = gfx::UniformBuffer<unf::Camera>  ::create();
        m_lightUniform             = gfx::UniformBuffer<unf::Light>   ::create();





        auto depthTexture = m_sBuffer->surface<gfx::FrameBuffer::Surface::Texture>("Depth");
        const std::array<fox::float32_t, 4> borderColor{ 1.0f, 1.0f, 1.0f, 1.0f };
        gl::texture_parameter(depthTexture->handle(), glp::magnification_filter{ glf::Texture::MagnificationFilter::Nearest });
        gl::texture_parameter(depthTexture->handle(), glp::minification_filter { glf::Texture::MinificationFilter ::Nearest });
        gl::texture_parameter(depthTexture->handle(), glp::border_color        { borderColor });




        
        const auto& add_to_pipeline = [this](const std::string& identifier, const std::string& vertex, std::optional<std::string> geometry,const std::string& fragment)
            {
                const std::filesystem::path dir{ "shaders/compiled" };

                if (geometry.has_value())
                {
                    const auto& shaders = api::shaders_from_binaries<gfx::Shader>(dir / vertex, dir / *geometry, dir / fragment);
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
        add_to_pipeline("SSAO"        , "ssao.vert.spv"         , {}, "ssao.frag.spv");





        //PBR setup
        auto captureProjection = math::perspective(1.0f, math::to_radians(90.0f), 0.1f, 10.0f);
        const std::array<fox::Matrix4f, 6> captureViews =
        {
            glm::lookAt(fox::Vector3f{ 0.0f, 0.0f, 0.0f }, fox::Vector3f{  1.0f,  0.0f,  0.0f }, fox::Vector3f{ 0.0f, -1.0f,  0.0f }),
            glm::lookAt(fox::Vector3f{ 0.0f, 0.0f, 0.0f }, fox::Vector3f{ -1.0f,  0.0f,  0.0f }, fox::Vector3f{ 0.0f, -1.0f,  0.0f }),
            glm::lookAt(fox::Vector3f{ 0.0f, 0.0f, 0.0f }, fox::Vector3f{  0.0f,  1.0f,  0.0f }, fox::Vector3f{ 0.0f,  0.0f,  1.0f }),
            glm::lookAt(fox::Vector3f{ 0.0f, 0.0f, 0.0f }, fox::Vector3f{  0.0f, -1.0f,  0.0f }, fox::Vector3f{ 0.0f,  0.0f, -1.0f }),
            glm::lookAt(fox::Vector3f{ 0.0f, 0.0f, 0.0f }, fox::Vector3f{  0.0f,  0.0f,  1.0f }, fox::Vector3f{ 0.0f, -1.0f,  0.0f }),
            glm::lookAt(fox::Vector3f{ 0.0f, 0.0f, 0.0f }, fox::Vector3f{  0.0f,  0.0f, -1.0f }, fox::Vector3f{ 0.0f, -1.0f,  0.0f }),
        };

        const auto& cva = gfx::Geometry::Cube::mesh() ->vertexArray;
        const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;



        //Load HDR environment texture
        const fox::Vector2u envDimensions{ 512u, 512u };
        const std::array<gfx::FrameBuffer::Specification, 1> manifest{ FS{ "Depth", RF::D24_UNORM }, };
        auto frameBuffer     = gfx::FrameBuffer::create(envDimensions, manifest);
        auto renderBuffer    = frameBuffer->surface<gfx::FrameBuffer::Surface::RenderBuffer>("Depth");
        auto hdrImage        = io::load<io::Asset::Image>("textures/kloppenheim_sky.hdr", fox::Image::Format::RGB32_FLOAT);
        auto hdrTex          = gfx::Texture2D::create(gfx::Texture2D::Format::RGB32_FLOAT, hdrImage.dimensions(), hdrImage.data());
        m_environmentCubemap = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::None, gfx::Cubemap::Wrapping::ClampToEdge, envDimensions);



        //Convert HDR texture to cubemap
        m_pipelines.at("ConvertEqui")->bind();
        m_matricesUniform->bind(fox::binding_t{ 2u });
        m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));

        gl::viewport(envDimensions);
        gl::frame_buffer_draw_buffer(frameBuffer->handle(), glf::FrameBuffer::Source::Color0);

        frameBuffer->bind(gfx::FrameBuffer::Target::Write);
        hdrTex->bind(fox::binding_t{ 0u });
        cva->bind();

        for (fox::uint32_t index{}; const auto& view : captureViews)
        {
            m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

            gl::frame_buffer_texture_layer(frameBuffer->handle(), m_environmentCubemap->handle(), glf::FrameBuffer::Attachment::Color0, 0, index++);
            gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
        }



        //Irradiance step
        constexpr fox::Vector2u cvDimensions{ 32u, 32u };

        m_irradianceCubemap = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::None, gfx::Cubemap::Wrapping::ClampToEdge, cvDimensions);

        m_pipelines.at("Irradiance")->bind();
        m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));
        m_environmentCubemap->bind(fox::binding_t{ 0u });

        gl::viewport(cvDimensions);
        gl::frame_buffer_draw_buffer(frameBuffer->handle(), glf::FrameBuffer::Source::Color0);
        gl::render_buffer_storage(renderBuffer->handle(), glf::RenderBuffer::Format::D24_UNORM, cvDimensions);

        frameBuffer->bind(gfx::FrameBuffer::Target::Write);
        cva->bind();

        for (fox::uint32_t index{}; const auto& view : captureViews)
        {
            m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

            gl::frame_buffer_texture_layer(frameBuffer->handle(), m_irradianceCubemap->handle(), glf::FrameBuffer::Attachment::Color0, 0, index++);
            gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
        }



        gl::texture_parameter(m_environmentCubemap->handle(), glp::magnification_filter{ glf::Texture::MagnificationFilter::Linear             });
        gl::texture_parameter(m_environmentCubemap->handle(), glp::minification_filter { glf::Texture::MinificationFilter ::LinearMipmapLinear });
        gl::generate_texture_mipmap(m_environmentCubemap->handle());



        //PreFilter step
        const fox::Vector2u reflectionDimensions{ 128u, 128u };

        auto preFilterBuffer = gfx::UniformBuffer<unf::PreFilter>::create();
        preFilterBuffer->bind(fox::binding_t{ 5u });

        m_preFilterCubemap = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::Trilinear, gfx::Cubemap::Wrapping::ClampToEdge, reflectionDimensions);

        m_pipelines.at("PreFilter")->bind();
        m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));
        m_environmentCubemap->bind(fox::binding_t{ 0u });
        
        frameBuffer->bind(gfx::FrameBuffer::Target::Write);
        cva->bind();

        fox::uint32_t maxMipLevels{ m_preFilterCubemap->mipmap_levels() };
        for (const auto& mip : std::views::iota(0u, maxMipLevels))
        {
            const fox::Vector2u mipDimensions{ reflectionDimensions.x * std::pow(0.5f, mip), reflectionDimensions.y * std::pow(0.5f, mip) };
            const auto& roughness = static_cast<fox::float32_t>(mip) / (maxMipLevels - 1u);
            preFilterBuffer->copy(unf::PreFilter{ envDimensions.x, roughness });

            gl::viewport(mipDimensions);
            gl::render_buffer_storage(renderBuffer->handle(), glf::RenderBuffer::Format::D24_UNORM, mipDimensions);

            for (fox::uint32_t index{}; const auto& view : captureViews)
            {
                m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

                gl::frame_buffer_texture_layer(frameBuffer->handle(), m_preFilterCubemap->handle(), glf::FrameBuffer::Attachment::Color0, mip, index++);
                gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
            }
        }



        //BRDF LUT step
        m_brdfTexture = gfx::Texture2D::create(gfx::Texture2D::Format::RG16_FLOAT, gfx::Texture2D::Filter::None, gfx::Texture2D::Wrapping::ClampToEdge, envDimensions);
        m_pipelines.at("BRDF")->bind();

        gl::viewport(envDimensions);
        gl::frame_buffer_texture(frameBuffer->handle(), m_brdfTexture->handle(), glf::FrameBuffer::Attachment::Color0, 0);
        gl::render_buffer_storage(renderBuffer->handle(), glf::RenderBuffer::Format::D24_UNORM, envDimensions);
        gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

        pva->bind();
        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());










        std::array<FS, 1> ssaoFrameBufferManifest{ FS{ "Occlusion", TF::R32_FLOAT }};
        m_ssaoBuffer = gfx::FrameBuffer::create(viewportDimensions, ssaoFrameBufferManifest);
        auto occlusion = m_ssaoBuffer->surface<gfx::FrameBuffer::Surface::Texture>("Occlusion");
        gl::texture_parameter(occlusion->handle(), glp::magnification_filter{ glf::Texture::MagnificationFilter::Nearest });
        gl::texture_parameter(occlusion->handle(), glp::minification_filter { glf::Texture::MinificationFilter ::Nearest });



        constexpr auto                                 ssaoSamples{ 64u };
        std::vector<unf::SSAOSample>                   ssaoKernel(ssaoSamples);
        std::uniform_real_distribution<fox::float32_t> distribution(0.0f, 1.0f);
        std::default_random_engine                     engine;
        for (const auto& index : std::views::iota(0u, 64u))
        {
            unf::SSAOSample sample
            { 
                distribution(engine) * 2.0f - 1.0f, 
                distribution(engine) * 2.0f - 1.0f, 
                distribution(engine), 
                0.0f 
            };

            sample  = glm::normalize(sample);
            sample *= distribution(engine);

            auto scale = static_cast<fox::float32_t>(index) / ssaoSamples;

            scale = std::lerp(0.1f, 1.0f, scale * scale);
            sample *= scale;

            ssaoKernel.at(index) = sample;
        }

        m_ssaoSampleUniform = gfx::UniformArrayBuffer<unf::SSAOSample, ssaoSamples>::create(ssaoKernel);
        m_ssaoSampleUniform->bind(fox::binding_t{ 7u });



        constexpr auto             ssaoNoiseSamples{ 16u };
        std::vector<fox::Vector3f> ssaoNoise(ssaoNoiseSamples);
        for (const auto& index : std::views::iota(0u, ssaoNoiseSamples))
        {
            fox::Vector3f noise
            { 
                distribution(engine) * 2.0f - 1.0f, 
                distribution(engine) * 2.0f - 1.0f, 
                0.0f 
            };

            ssaoNoise.at(index) = noise;
        }

        m_ssaoNoiseTexture = gfx::Texture2D::create(gfx::Texture2D::Format::RGB32_FLOAT, gfx::Texture2D::Filter::Nearest, gfx::Texture2D::Wrapping::Repeat, fox::Vector2u{ 4u, 4u }, utl::as_bytes(ssaoNoise));
    }

    void OpenGLRenderer::start(gfx::RenderInfo renderInfo)
    {
        m_renderInfo = renderInfo;

        const auto& camera           = m_renderInfo.camera;
        const auto& transform        = m_renderInfo.cameraTransform;
        const auto& viewMatrix       = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
        const auto& projectionMatrix = camera.projection();

        m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(viewMatrix, projectionMatrix));
        m_cameraUniform  ->copy    (unf::Camera{ fox::Vector4f{ transform.position, 1.0f } });



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

            if (light.isShadowCasting and std::cmp_less(shadowCastingLightCount, maximumShadowCastingLights))
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
        constexpr fox::Vector2u  dimensions{ 1280u,  720u };
        constexpr fox::Vector2u sDimensions{ 2048u, 2048u };

        //Bind Uniform Buffers to correct indices
        m_contextUniform-> bind(fox::binding_t{ 0u });
        m_cameraUniform->  bind(fox::binding_t{ 1u });
        m_matricesUniform->bind(fox::binding_t{ 2u });
        m_materialUniform->bind(fox::binding_t{ 3u });
        m_lightUniform->   bind(fox::binding_t{ 4u });

        m_contextUniform->copy(unf::Context{ dimensions, input::cursor_position(), fox::time::since_epoch(), fox::time::delta() });



        gl::viewport(dimensions);
        
        //Render meshes into gBuffer
        render_meshes(m_gBuffer, m_pipelines.at("DeferredMesh"));




        



        m_ssaoBuffer->bind(gfx::FrameBuffer::Target::Write);

        m_pipelines.at("SSAO")->bind();
        m_gBuffer->bind_surface("Position", fox::binding_t{ 0u });
        m_gBuffer->bind_surface("Normal"  , fox::binding_t{ 1u });

        m_ssaoNoiseTexture->bind(fox::binding_t{ 2u });

        gl::viewport(dimensions);
        gl::clear(glf::Buffer::Mask::Color);
        gl::disable<glf::Feature::FaceCulling>();
        gl::disable<glf::Feature::DepthTest>();
        gl::disable<glf::Feature::Blending>();

        const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;
        pva->bind();
        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());





        //Lighting calculations
        render_lighting(m_pBuffers.at(0));






        m_pBuffers.at(0)->bind(gfx::FrameBuffer::Target::Write);
        m_pipelines.at("Background")->bind();
        m_environmentCubemap->bind(fox::binding_t{ 0u });

        gl::disable<glf::Feature::Blending>();
        gl::disable<glf::Feature::FaceCulling>();
        gl::enable <glf::Feature::DepthTest>();
        gl::depth_function(glf::DepthFunction::LessEqual);

        const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
        cva->bind();
        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());





        //Render simple cubes for debugging
#ifdef FOX_DEBUG
        m_pipelines.at("Debug")->bind();

        for (const auto& transform : m_debugTransforms)
        {
            m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, gfx::Geometry::Cube::mesh()->vertexArray->index_count());
        }
#endif





        //Blit the final result into the default framebuffer
        //gl::blit_frame_buffer(m_ssaoBuffer->handle(), gl::DefaultFrameBuffer, glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);
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
    
    void OpenGLRenderer::render_meshes(std::shared_ptr<gfx::FrameBuffer> frameBuffer, std::shared_ptr<gfx::Pipeline> shader)
    {
        frameBuffer->bind(gfx::FrameBuffer::Target::Write);
        shader->bind();

        gl::viewport      (frameBuffer->dimensions());
        gl::clear         (glf::Buffer::Mask::All);
        gl::enable        <glf::Feature::FaceCulling>();
        gl::cull_face     (glf::Culling::Facet::Back);
        gl::front_face    (glf::Orientation::CounterClockwise);
        gl::enable        <glf::Feature::DepthTest>();
        gl::depth_function(glf::DepthFunction::Less);
        gl::disable       <glf::Feature::Blending>();

        auto positionTexture = m_gBuffer->surface("Position");
        std::array<fox::float32_t, 4u> data{ 0.0f, 0.0f, -1000.0f };
        gl::clear_texture_image(positionTexture->handle(), glf::Texture::BaseFormat::RGB, glf::Texture::Type::Float, 0, utl::as_bytes(data));


        for (const auto& _ : m_mmt)
        {
            const auto& [mesh, material, transform] = _;

            m_matricesUniform->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
            m_materialUniform->copy    (unf::Material{ material->color, material->roughnessFactor, material->metallicFactor });

            mesh    ->vertexArray->bind();
            material->albedo     ->bind(fox::binding_t{ 0u });
            material->normal     ->bind(fox::binding_t{ 1u });
            material->arm        ->bind(fox::binding_t{ 2u });

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, mesh->vertexArray->index_count());
        }
    }
    void OpenGLRenderer::render_lighting(std::shared_ptr<gfx::FrameBuffer> target)
    {
        target->bind(api::FrameBuffer::Target::Write);
        gl::clear(glf::Buffer::Mask::All);

        gl::blit_frame_buffer(m_gBuffer->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, m_gBuffer->dimensions(), target->dimensions());



        m_pipelines.at("PBR")->bind();
        m_gBuffer->bind_surface("Position", fox::binding_t{ 0u });
        m_gBuffer->bind_surface("Albedo"  , fox::binding_t{ 1u });
        m_gBuffer->bind_surface("Normal"  , fox::binding_t{ 2u });
        m_gBuffer->bind_surface("ARM"     , fox::binding_t{ 3u });

        m_irradianceCubemap->bind(fox::binding_t{ 4u });
        m_preFilterCubemap ->bind(fox::binding_t{ 5u });
        m_brdfTexture      ->bind(fox::binding_t{ 6u });

        gl::viewport(target->dimensions());
        gl::depth_mask(gl::False);
        gl::disable<glf::Feature::DepthTest>();
        gl::enable<glf::Feature::Blending>();
        gl::blend_function(glf::Blending::Factor::SourceAlpha, glf::Blending::Factor::One);
        gl::disable<glf::Feature::FaceCulling>();

        const auto& pva = gfx::Geometry::Plane::mesh()->vertexArray;
        pva->bind();

        for (fox::size_t index{}; const auto& light : m_lights)
        {
            fox::Transform sphereTransform{ light.position, fox::Vector3f{}, fox::Vector3f{light.radius} };

            m_matricesUniform   ->copy_sub(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(sphereTransform.matrix()));
            m_lightUniform      ->copy({ light.position, light.color, light.radius, light.linearFalloff, light.quadraticFalloff });

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());
        }

        gl::depth_mask(gl::True);
    }
    void OpenGLRenderer::render_skybox(std::shared_ptr<gfx::FrameBuffer> target, std::shared_ptr<gfx::FrameBuffer> previous)
    {
        if (!m_renderInfo.skybox) return;

        m_pipelines.at("Skybox")->bind();
        m_renderInfo.skybox->bind(fox::binding_t{ 0u });

        gl::blit_frame_buffer(previous->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, previous->dimensions(), target->dimensions());

        gl::viewport(target->dimensions());
        gl::disable<glf::Feature::FaceCulling>();
        gl::enable<glf::Feature::DepthTest>();
        gl::depth_function(glf::DepthFunction::LessEqual);
        gl::disable<glf::Feature::Blending>();

        const auto& cva = gfx::Geometry::Cube::mesh()->vertexArray;
        cva->bind();

        gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
    }
}
