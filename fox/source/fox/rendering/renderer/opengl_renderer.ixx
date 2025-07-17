export module fox.rendering.renderer.opengl;

import std;
import fox.core.time;
import fox.core.transform;
import fox.core.types.common;
import fox.core.types.fundamental;
import fox.core.types.math;
import fox.core.utility;
import fox.ecs.component;
import fox.ecs.components.mesh_filter;
import fox.ecs.components.relationship;
import fox.input;
import fox.math;
import fox.rendering.api;
import fox.rendering.base.pipeline;
import fox.rendering.base.shader;
import fox.rendering.base.utility;
import fox.rendering.buffer;
import fox.rendering.cubemap;
import fox.rendering.frame_buffer;
import fox.rendering.geometry;
import fox.rendering.material;
import fox.rendering.mesh;
import fox.rendering.model;
import fox.rendering.pipeline;
import fox.rendering.render_buffer;
import fox.rendering.render_info;
import fox.rendering.shader;
import fox.rendering.texture;
import fox.rendering.uniform;
import fox.rendering.vertex_array;
import fox.rendering;
import fox.rendering.api.gl;

export namespace fox::gfx::api
{
    class OpenGLRenderer
    {
    public:
        OpenGLRenderer()
        {
            gl::enable<glf::Feature::SeamlessCubeMapTexture>();



            const fox::uint32_t multisamples{ 4u };
            const fox::uint32_t lightCount{ 32u };
            const fox::Vector2u viewportDimensions { 1280u,  720u };
            const fox::Vector2u shadowMapDimensions{ 2048u, 2048u };

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



            gBuffer_         = gfx::FrameBuffer::create(viewportDimensions , gBufferManifest  );
            sBuffer_         = gfx::FrameBuffer::create(shadowMapDimensions, sBufferManifest  );
            pBuffers_.at(0)  = gfx::FrameBuffer::create(viewportDimensions , pBufferManifest  );
            pBuffers_.at(1)  = gfx::FrameBuffer::create(viewportDimensions , pBufferManifest  );

            contextUniform_  = gfx::UniformBuffer<unf::Context> ::create();
            matricesUniform_ = gfx::UniformBuffer<unf::Matrices>::create();
            materialUniform_ = gfx::UniformBuffer<unf::Material>::create();
            cameraUniform_   = gfx::UniformBuffer<unf::Camera>  ::create();
            lightUniform_    = gfx::UniformBuffer<unf::Light>   ::create();





            auto depthTexture = sBuffer_->surface<gfx::FrameBuffer::Surface::Texture>("Depth");
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
                        pipelines_.emplace(identifier, gfx::Pipeline::create(gfx::Pipeline::Layout{ .vert = shaders.at(0), .geom = shaders.at(1), .frag = shaders.at(2) }));
                    }
                    else
                    {
                        const auto& shaders = api::shaders_from_binaries<gfx::Shader>(dir / vertex, dir / fragment);
                        pipelines_.emplace(identifier, gfx::Pipeline::create(gfx::Pipeline::Layout{ .vert = shaders.at(0), .frag = shaders.at(1) }));
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

            const auto& cva = gfx::geometry::cube;
            const auto& pva = gfx::geometry::plane;



            //Load HDR environment texture
            const fox::Vector2u envDimensions{ 512u, 512u };
            const std::array<gfx::FrameBuffer::Specification, 1> manifest{ FS{ "Depth", RF::D24_UNORM }, };
            auto frameBuffer     = gfx::FrameBuffer::create(envDimensions, manifest);
            auto renderBuffer    = frameBuffer->surface<gfx::FrameBuffer::Surface::RenderBuffer>("Depth");
            auto hdrImage        = io::load<io::Asset::Image>("textures/kloppenheim_sky.hdr", fox::Image::Format::RGB32_FLOAT);
            auto hdrTex          = gfx::Texture2D::create(gfx::Texture2D::Format::RGB32_FLOAT, hdrImage.dimensions(), hdrImage.data());
            environmentCubemap_  = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::None, gfx::Cubemap::Wrapping::ClampToEdge, envDimensions);



            //Convert HDR texture to cubemap
            pipelines_.at("ConvertEqui")->bind();
            matricesUniform_->bind(gfx::binding_t{ 2u });
            matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));

            gl::viewport(envDimensions);
            gl::frame_buffer_draw_buffer(frameBuffer->handle(), glf::FrameBuffer::Source::Color0);

            frameBuffer->bind(gfx::FrameBuffer::Target::Write);
            hdrTex->bind(gfx::binding_t{ 0u });
            cva->bind();

            //for (auto [index, view] : std::views::zip(std::views::iota(0u), captureViews))
            //{
            //    matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));
            //    gl::frame_buffer_texture_layer(frameBuffer->handle(), environmentCubemap_->handle(), glf::FrameBuffer::Attachment::Color0, 0, index);
            //    gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);
            //    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
            //}
            for (auto index = fox::uint32_t{ 0u }; const auto& view : captureViews)
            {
                matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

                gl::frame_buffer_texture_layer(frameBuffer->handle(), environmentCubemap_->handle(), glf::FrameBuffer::Attachment::Color0, 0, index++);
                gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
            }










            //Irradiance step
            const fox::Vector2u cvDimensions{ 32u, 32u };

            irradianceCubemap_ = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::None, gfx::Cubemap::Wrapping::ClampToEdge, cvDimensions);

            pipelines_.at("Irradiance")->bind();
            matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));
            environmentCubemap_->bind(gfx::binding_t{ 0u });

            gl::viewport(cvDimensions);
            gl::frame_buffer_draw_buffer(frameBuffer->handle(), glf::FrameBuffer::Source::Color0);
            gl::render_buffer_storage(renderBuffer->handle(), glf::RenderBuffer::Format::D24_UNORM, cvDimensions);

            frameBuffer->bind(gfx::FrameBuffer::Target::Write);
            cva->bind();

            //for (auto [index, view] : std::views::zip(std::views::iota(0u), captureViews))
            //{
            //    matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));
            //    gl::frame_buffer_texture_layer(frameBuffer->handle(), irradianceCubemap_->handle(), glf::FrameBuffer::Attachment::Color0, 0, index);
            //    gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);
            //    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
            //}
            for (auto index = fox::uint32_t{ 0u }; const auto& view : captureViews)
            {
                matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

                gl::frame_buffer_texture_layer(frameBuffer->handle(), irradianceCubemap_->handle(), glf::FrameBuffer::Attachment::Color0, 0, index++);
                gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
            }


            gl::texture_parameter      (environmentCubemap_->handle(), glp::magnification_filter{ glf::Texture::MagnificationFilter::Linear             });
            gl::texture_parameter      (environmentCubemap_->handle(), glp::minification_filter { glf::Texture::MinificationFilter ::LinearMipmapLinear });
            gl::generate_texture_mipmap(environmentCubemap_->handle());



            //PreFilter step
            const fox::Vector2u reflectionDimensions{ 128u, 128u };

            auto preFilterBuffer = gfx::UniformBuffer<unf::PreFilter>::create();
            preFilterBuffer->bind(gfx::binding_t{ 5u });

            preFilterCubemap_ = gfx::Cubemap::create(gfx::Cubemap::Format::RGB16_FLOAT, gfx::Cubemap::Filter::Trilinear, gfx::Cubemap::Wrapping::ClampToEdge, reflectionDimensions);

            pipelines_.at("PreFilter")->bind();
            matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::projection>(), std::make_tuple(captureProjection));
            environmentCubemap_->bind(gfx::binding_t{ 0u });

            frameBuffer->bind(gfx::FrameBuffer::Target::Write);
            cva->bind();

            fox::uint32_t maxMipLevels{ preFilterCubemap_->mipmap_levels() };
            for (const auto& mip : std::views::iota(0u, maxMipLevels))
            {
                const fox::Vector2u mipDimensions{ reflectionDimensions.x * std::pow(0.5f, mip), reflectionDimensions.y * std::pow(0.5f, mip) };
                const auto& roughness = static_cast<fox::float32_t>(mip) / (maxMipLevels - 1u);
                preFilterBuffer->copy(unf::PreFilter{ envDimensions.x, roughness });

                gl::viewport(mipDimensions);
                gl::render_buffer_storage(renderBuffer->handle(), glf::RenderBuffer::Format::D24_UNORM, mipDimensions);

                //for (auto [index, view] : std::views::zip(std::views::iota(0u), captureViews))
                //{
                //    matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));
                //    gl::frame_buffer_texture_layer(frameBuffer->handle(), preFilterCubemap_->handle(), glf::FrameBuffer::Attachment::Color0, mip, index);
                //    gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);
                //    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
                //}
                for (auto index = fox::uint32_t{ 0u }; const auto& view : captureViews)
                {
                    matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(view));

                    gl::frame_buffer_texture_layer(frameBuffer->handle(), preFilterCubemap_->handle(), glf::FrameBuffer::Attachment::Color0, mip, index++);
                    gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

                    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
                }
            }



            //BRDF LUT step
            brdfTexture_ = gfx::Texture2D::create(gfx::Texture2D::Format::RG16_FLOAT, gfx::Texture2D::Filter::None, gfx::Texture2D::Wrapping::ClampToEdge, envDimensions);
            pipelines_.at("BRDF")->bind();

            gl::viewport(envDimensions);
            gl::frame_buffer_texture(frameBuffer->handle(), brdfTexture_->handle(), glf::FrameBuffer::Attachment::Color0, 0);
            gl::render_buffer_storage(renderBuffer->handle(), glf::RenderBuffer::Format::D24_UNORM, envDimensions);
            gl::clear(glf::Buffer::Mask::Color | glf::Buffer::Mask::Depth);

            pva->bind();
            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());










            std::array<FS, 1> ssaoFrameBufferManifest{ FS{ "Occlusion", TF::R32_FLOAT }};
            ssaoBuffer_ = gfx::FrameBuffer::create(viewportDimensions, ssaoFrameBufferManifest);
            auto occlusion = ssaoBuffer_->surface<gfx::FrameBuffer::Surface::Texture>("Occlusion");
            gl::texture_parameter(occlusion->handle(), glp::magnification_filter{ glf::Texture::MagnificationFilter::Nearest });
            gl::texture_parameter(occlusion->handle(), glp::minification_filter { glf::Texture::MinificationFilter ::Nearest });



            constexpr auto                                 ssaoSamples{ 64u };
            std::vector<unf::SSAOSample>                   ssaoKernel(ssaoSamples);
            std::uniform_real_distribution<fox::float32_t> distribution(0.0f, 1.0f);
            std::default_random_engine                     engine;
            for (auto index : std::views::iota(0u, 64u))
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

            ssaoSampleUniform_ = gfx::UniformArrayBuffer<unf::SSAOSample, ssaoSamples>::create(ssaoKernel);
            ssaoSampleUniform_->bind(gfx::binding_t{ 7u });



            constexpr auto             ssaoNoiseSamples{ 16u };
            std::vector<fox::Vector3f> ssaoNoise(ssaoNoiseSamples);

            for (auto index : std::views::iota(0u, ssaoNoiseSamples))
            {
                fox::Vector3f noise
                { 
                    distribution(engine) * 2.0f - 1.0f, 
                    distribution(engine) * 2.0f - 1.0f, 
                    0.0f 
                };

                ssaoNoise.at(index) = noise;
            }

            ssaoNoiseTexture_ = gfx::Texture2D::create(gfx::Texture2D::Format::RGB32_FLOAT, gfx::Texture2D::Filter::Nearest, gfx::Texture2D::Wrapping::Repeat, fox::Vector2u{ 4u, 4u }, fox::as_bytes(std::span<const fox::Vector3f>{ ssaoNoise }));
        }

        void start(gfx::RenderInfo renderInfo)
        {
            renderInfo_ = renderInfo;

            const auto& camera           = renderInfo_.camera;
            const auto& transform        = renderInfo_.cameraTransform;
            const auto& viewMatrix       = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
            const auto& projectionMatrix = camera.projection();

            matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::view>(), std::make_tuple(viewMatrix, projectionMatrix));
            cameraUniform_  ->copy    (unf::Camera{ fox::Vector4f{ transform.position, 1.0f } });



            mmt_                           .clear();
            lights_                        .clear();
            shadowCastingPointLights_      .clear();
            shadowCastingDirectionalLights_.clear();
            debugTransforms_               .clear();



            fox::size_t shadowCastingLightCount{ 0u };
            constexpr auto maximumShadowCastingLights{ 4 };

            for (const auto& [light, position] : renderInfo_.lights)
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
                        case fox::Light::Type::Directional: shadowCastingDirectionalLights_.emplace_back(result); break;
                        case fox::Light::Type::Point:       shadowCastingPointLights_      .emplace_back(result); break;
                        case fox::Light::Type::Spot:        throw std::exception{ "" };                            break;
                    }

                    ++shadowCastingLightCount;
                }

                lights_.emplace_back(std::move(result));
            }
        }
        void finish()
        {
            const fox::Vector2u  dimensions{ 1280u,  720u };
            const fox::Vector2u sDimensions{ 2048u, 2048u };

            //Bind Uniform Buffers to correct indices
            contextUniform_-> bind(gfx::binding_t{ 0u });
            cameraUniform_->  bind(gfx::binding_t{ 1u });
            matricesUniform_->bind(gfx::binding_t{ 2u });
            materialUniform_->bind(gfx::binding_t{ 3u });
            lightUniform_->   bind(gfx::binding_t{ 4u });

            contextUniform_->copy(unf::Context{ dimensions, input::cursor_position(), fox::time::since_epoch(), fox::time::delta() });



            gl::viewport(dimensions);

            //Render meshes into gBuffer
            render_meshes(gBuffer_, pipelines_.at("DeferredMesh"));








            ssaoBuffer_->bind(gfx::FrameBuffer::Target::Write);

            pipelines_.at("SSAO")->bind();
            gBuffer_->bind_surface("Position", gfx::binding_t{ 0u });
            gBuffer_->bind_surface("Normal"  , gfx::binding_t{ 1u });

            ssaoNoiseTexture_->bind(gfx::binding_t{ 2u });

            gl::viewport(dimensions);
            gl::clear(glf::Buffer::Mask::Color);
            gl::disable<glf::Feature::FaceCulling>();
            gl::disable<glf::Feature::DepthTest>();
            gl::disable<glf::Feature::Blending>();

            const auto& pva = gfx::geometry::plane;
            pva->bind();
            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());





            //Lighting calculations
            render_lighting(pBuffers_.at(0));






            pBuffers_.at(0)->bind(gfx::FrameBuffer::Target::Write);
            pipelines_.at("Background")->bind();
            environmentCubemap_->bind(gfx::binding_t{ 0u });

            gl::disable<glf::Feature::Blending>();
            gl::disable<glf::Feature::FaceCulling>();
            gl::enable <glf::Feature::DepthTest>();
            gl::depth_function(glf::DepthFunction::LessEqual);

            const auto& cva = gfx::geometry::cube;
            cva->bind();
            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());





            //Render simple cubes for debugging
#ifdef FOX_DEBUG
            pipelines_.at("Debug")->bind();

            for (const auto& transform : debugTransforms_)
            {
                matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
            }
#endif





            //Blit the final result into the default framebuffer
            //gl::blit_frame_buffer(ssaoBuffer_->handle(), gl::DefaultFrameBuffer, glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);
            gl::blit_frame_buffer(pBuffers_.at(0)->handle(), gl::DefaultFrameBuffer, glf::Buffer::Mask::Color, glf::FrameBuffer::Filter::Nearest, pBuffers_.at(0)->dimensions(), dimensions);
        }

        void render(std::shared_ptr<const gfx::Mesh> mesh, std::shared_ptr<const gfx::Material> material, const fox::Transform& transform)
        {
            mmt_.emplace_back(mesh, material, transform);
        }
        void render_debug(const fox::Transform& transform)
        {
            debugTransforms_.emplace_back(transform);
        }

    private:
        void render_meshes(std::shared_ptr<gfx::FrameBuffer> frameBuffer, std::shared_ptr<gfx::Pipeline> shader)
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

            auto positionTexture = gBuffer_->surface("Position");
            std::array<fox::float32_t, 4u> data{ 0.0f, 0.0f, -1000.0f };
            gl::clear_texture_image(positionTexture->handle(), glf::Texture::BaseFormat::RGB, glf::Texture::Type::Float, 0, utl::as_bytes(data));

            for (const auto& _ : mmt_)
            {
                const auto& [mesh, material, transform] = _;

                matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(transform.matrix()));
                materialUniform_->copy      (unf::Material{ material->color, material->roughnessFactor, material->metallicFactor });

                mesh            ->bind();
                material->albedo->bind(gfx::binding_t{ 0u });
                material->normal->bind(gfx::binding_t{ 1u });
                material->arm   ->bind(gfx::binding_t{ 2u });

                gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, mesh->index_count());
            }
        }
        void render_lighting(std::shared_ptr<gfx::FrameBuffer> target)
        {
            target->bind(api::FrameBuffer::Target::Write);
            gl::clear(glf::Buffer::Mask::All);

            gl::blit_frame_buffer(gBuffer_->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, gBuffer_->dimensions(), target->dimensions());



            pipelines_.at("PBR")->bind();
            gBuffer_->bind_surface("Position", gfx::binding_t{ 0u });
            gBuffer_->bind_surface("Albedo"  , gfx::binding_t{ 1u });
            gBuffer_->bind_surface("Normal"  , gfx::binding_t{ 2u });
            gBuffer_->bind_surface("ARM"     , gfx::binding_t{ 3u });

            irradianceCubemap_->bind(gfx::binding_t{ 4u });
            preFilterCubemap_ ->bind(gfx::binding_t{ 5u });
            brdfTexture_      ->bind(gfx::binding_t{ 6u });

            gl::viewport(target->dimensions());
            gl::depth_mask(gl::False);
            gl::disable<glf::Feature::DepthTest>();
            gl::enable<glf::Feature::Blending>();
            gl::blend_function(glf::Blending::Factor::SourceAlpha, glf::Blending::Factor::One);
            gl::disable<glf::Feature::FaceCulling>();

            const auto& pva = gfx::geometry::plane;
            pva->bind();

            std::ranges::for_each(lights_, [&](const auto& light)
                {
                    fox::Transform sphereTransform{ light.position, fox::Vector3f{}, fox::Vector3f{light.radius} };

                    matricesUniform_->copy_slice(utl::offset_of<unf::Matrices, &unf::Matrices::model>(), std::make_tuple(sphereTransform.matrix()));
                    lightUniform_   ->copy      ({ light.position, light.color, light.radius, light.linearFalloff, light.quadraticFalloff });

                    gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, pva->index_count());

                });

            gl::depth_mask(gl::True);
        }
        void render_skybox(std::shared_ptr<gfx::FrameBuffer> target, std::shared_ptr<gfx::FrameBuffer> previous)
        {
            if (!renderInfo_.skybox) return;

            pipelines_.at("Skybox")->bind();
            renderInfo_.skybox->bind(gfx::binding_t{ 0u });

            gl::blit_frame_buffer(previous->handle(), target->handle(), glf::Buffer::Mask::Depth, glf::FrameBuffer::Filter::Nearest, previous->dimensions(), target->dimensions());

            gl::viewport(target->dimensions());
            gl::disable<glf::Feature::FaceCulling>();
            gl::enable<glf::Feature::DepthTest>();
            gl::depth_function(glf::DepthFunction::LessEqual);
            gl::disable<glf::Feature::Blending>();

            const auto& cva = gfx::geometry::cube;
            cva->bind();

            gl::draw_elements(glf::Draw::Mode::Triangles, glf::Draw::Type::UnsignedInt, cva->index_count());
        }

        std::vector<std::tuple<std::shared_ptr<const gfx::Mesh>, std::shared_ptr<const gfx::Material>, fox::Transform>> mmt_{};
        std::vector<unf::Light>                                            lights_{};
        std::vector<unf::Light>                                            shadowCastingPointLights_{};
        std::vector<unf::Light>                                            shadowCastingDirectionalLights_{};
        std::vector<fox::Transform>                                        debugTransforms_{};
        std::shared_ptr<gfx::FrameBuffer>                                  gBuffer_{};
        std::shared_ptr<gfx::FrameBuffer>                                  sBuffer_{};
        std::array<std::shared_ptr<gfx::FrameBuffer>, 2>                   pBuffers_{};
        std::shared_ptr<gfx::FrameBuffer>                                  ssaoBuffer_{};
        std::shared_ptr<gfx::Texture2D>                                    ssaoNoiseTexture_{};
        std::shared_ptr<gfx::Cubemap>                                      environmentCubemap_{};
        std::shared_ptr<gfx::Cubemap>                                      irradianceCubemap_{};
        std::shared_ptr<gfx::Cubemap>                                      preFilterCubemap_{};
        std::shared_ptr<gfx::Texture2D>                                    brdfTexture_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Context>>                  contextUniform_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Matrices>>                 matricesUniform_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Material>>                 materialUniform_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Camera>>                   cameraUniform_{};
        std::shared_ptr<gfx::UniformBuffer<unf::Light>>                    lightUniform_{};
        std::shared_ptr<gfx::UniformArrayBuffer<unf::SSAOSample, 64u>>     ssaoSampleUniform_{};
        std::unordered_map<std::string, std::shared_ptr<gfx::Pipeline>>    pipelines_{};
        fox::float32_t                                                     shadowFarPlane_{ 100.0f };
        gfx::RenderInfo                                                    renderInfo_{};
    };
}
