export module fox.rendering.renderer.opengl;

import std;
import fox.core.time;
import fox.core.transform;
import fox.core.types;
import fox.core.utility;
import fox.ecs.components;
import fox.input;
import fox.math;
import fox.rendering.api.gl;
import fox.rendering.api;
import fox.rendering.utility;
import fox.rendering;

export namespace fox::gfx::api
{
    class OpenGLRenderer
    {
    public:
        OpenGLRenderer()
        {
            gl::enable<gl::feature_e::seamless_cubemap_texture>();



            const fox::vector2u viewportDimensions { 1280u,  720u };
            const fox::vector2u shadowMapDimensions{ 2048u, 2048u };

            using FS = gfx::frame_buffer::specification_e;
            using TF = gfx::texture2d::format_e;
            using RF = gfx::render_buffer::format_e;
            using CF = gfx::cubemap::format_e;
            using FA = gfx::frame_buffer::attachment_e;

            std::array<FS, 5> gBufferManifest {
                FS{ "Position",     TF::rgb16_float },
                FS{ "Albedo",       TF::rgba8_unorm  },
                FS{ "Normal",       TF::rgb16_float },
                FS{ "ARM",          TF::rgb16_unorm  },
                FS{ "DepthStencil", RF::d24_unorm_s8_uint },
            };
            std::array<FS, 2> hdrBufferManifest { FS{ "Color", TF::rgba16_float }, FS{ "Depth", RF::d24_unorm_s8_uint } };
            std::array<FS, 1> sBufferManifest   { FS{ "Depth", TF::d24_unorm    }                                       };
            std::array<FS, 2> pBufferManifest   { FS{ "Color", TF::rgba16_unorm }, FS{ "Depth", RF::d24_unorm_s8_uint } };
            std::array<FS, 1> scBufferManifest  { FS{ "Depth", CF::d24_unorm    }                                       };



            gBuffer_         = gfx::frame_buffer::create(viewportDimensions , gBufferManifest  );
            sBuffer_         = gfx::frame_buffer::create(shadowMapDimensions, sBufferManifest  );
            pBuffers_.at(0)  = gfx::frame_buffer::create(viewportDimensions , pBufferManifest  );
            pBuffers_.at(1)  = gfx::frame_buffer::create(viewportDimensions , pBufferManifest  );

            contextUniform_  = gfx::uniform_buffer<unf::context> ::create();
            matricesUniform_ = gfx::uniform_buffer<unf::matrices>::create();
            materialUniform_ = gfx::uniform_buffer<unf::material>::create();
            cameraUniform_   = gfx::uniform_buffer<unf::camera>  ::create();
            lightUniform_    = gfx::uniform_buffer<unf::light>   ::create();





            auto depthTexture = sBuffer_->surface<gfx::frame_buffer::surface_e::texture>("Depth");
            const std::array<fox::float32_t, 4> borderColor{ 1.0f, 1.0f, 1.0f, 1.0f };
            gl::texture_parameter(depthTexture->handle(), glp::magnification_filter{ gl::texture_magnification_filter_e::nearest });
            gl::texture_parameter(depthTexture->handle(), glp::minification_filter { gl::texture_minification_filter_e ::nearest });
            gl::texture_parameter(depthTexture->handle(), glp::border_color        { borderColor });




            const auto& add_to_pipeline = [this](const std::string& identifier, const std::string& vertex, std::optional<std::string> geometry,const std::string& fragment)
                {
                    const std::filesystem::path dir{ "shaders/compiled" };

                    if (geometry.has_value())
                    {
                        const auto& shaders = gfx::utl::shaders_from_binaries<gfx::shader>(dir / vertex, dir / *geometry, dir / fragment);
                        pipelines_.emplace(identifier, gfx::pipeline::create(gfx::pipeline::layout_t{ .vert = shaders.at(0), .geom = shaders.at(1), .frag = shaders.at(2) }));
                    }
                    else
                    {
                        const auto& shaders = gfx::utl::shaders_from_binaries<gfx::shader>(dir / vertex, dir / fragment);
                        pipelines_.emplace(identifier, gfx::pipeline::create(gfx::pipeline::layout_t{ .vert = shaders.at(0), .frag = shaders.at(1) }));
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
            const std::array<fox::matrix4f, 6> captureViews =
            {
                glm::lookAt(fox::vector3f{ 0.0f, 0.0f, 0.0f }, fox::vector3f{  1.0f,  0.0f,  0.0f }, fox::vector3f{ 0.0f, -1.0f,  0.0f }),
                glm::lookAt(fox::vector3f{ 0.0f, 0.0f, 0.0f }, fox::vector3f{ -1.0f,  0.0f,  0.0f }, fox::vector3f{ 0.0f, -1.0f,  0.0f }),
                glm::lookAt(fox::vector3f{ 0.0f, 0.0f, 0.0f }, fox::vector3f{  0.0f,  1.0f,  0.0f }, fox::vector3f{ 0.0f,  0.0f,  1.0f }),
                glm::lookAt(fox::vector3f{ 0.0f, 0.0f, 0.0f }, fox::vector3f{  0.0f, -1.0f,  0.0f }, fox::vector3f{ 0.0f,  0.0f, -1.0f }),
                glm::lookAt(fox::vector3f{ 0.0f, 0.0f, 0.0f }, fox::vector3f{  0.0f,  0.0f,  1.0f }, fox::vector3f{ 0.0f, -1.0f,  0.0f }),
                glm::lookAt(fox::vector3f{ 0.0f, 0.0f, 0.0f }, fox::vector3f{  0.0f,  0.0f, -1.0f }, fox::vector3f{ 0.0f, -1.0f,  0.0f }),
            };

            const auto& cva = gfx::geometry::cube;
            const auto& pva = gfx::geometry::plane;



            //Load HDR environment texture
            const fox::vector2u envDimensions{ 512u, 512u };
            const std::array<gfx::frame_buffer::specification_e, 1> manifest{ FS{ "Depth", RF::d24_unorm }, };
            auto frameBuffer     = gfx::frame_buffer::create(envDimensions, manifest);
            auto renderBuffer    = frameBuffer->surface<gfx::frame_buffer::surface_e::render_buffer>("Depth");
            auto hdrImage        = io::load<io::asset_e::image>("textures/kloppenheim_sky.hdr", fox::image::format_e::rgb32_float);
            auto hdrTex          = gfx::texture2d::create(gfx::texture2d::format_e::rgb32_float, hdrImage.dimensions(), hdrImage.data());
            environmentCubemap_  = gfx::cubemap::create(gfx::cubemap::format_e::rgb16_float, gfx::cubemap::filter_e::none, gfx::cubemap::wrapping_e::clamp_to_edge, envDimensions);



            //Convert HDR texture to cubemap
            pipelines_.at("ConvertEqui")->bind();
            matricesUniform_->bind(gfx::binding_t{ 2u });
            matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::projection>(), std::make_tuple(captureProjection));

            gl::viewport(envDimensions);
            gl::frame_buffer_draw_buffer(frameBuffer->handle(), gl::frame_buffer_source_e::color0);

            frameBuffer->bind(gfx::frame_buffer::target_e::write);
            hdrTex->bind(gfx::binding_t{ 0u });
            cva->bind();

            for (auto [index, view] : std::views::zip(std::views::iota(0u), captureViews))
            {
                matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::view>(), std::make_tuple(view));

                gl::frame_buffer_texture_layer(frameBuffer->handle(), environmentCubemap_->handle(), gl::frame_buffer_attachment_e::color0, 0, index++);
                gl::clear(gl::buffer_mask_e::color | gl::buffer_mask_e::depth);
                gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, cva->index_count());
            }









            //Irradiance step
            const fox::vector2u cvDimensions{ 32u, 32u };

            irradianceCubemap_ = gfx::cubemap::create(gfx::cubemap::format_e::rgb16_float, gfx::cubemap::filter_e::none, gfx::cubemap::wrapping_e::clamp_to_edge, cvDimensions);

            pipelines_.at("Irradiance")->bind();
            matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::projection>(), std::make_tuple(captureProjection));
            environmentCubemap_->bind(gfx::binding_t{ 0u });

            gl::viewport(cvDimensions);
            gl::frame_buffer_draw_buffer(frameBuffer->handle(), gl::frame_buffer_source_e::color0);
            gl::render_buffer_storage(renderBuffer->handle(), gl::render_buffer_format_e::d24_unorm, cvDimensions);

            frameBuffer->bind(gfx::frame_buffer::target_e::write);
            cva->bind();

            for (auto [index, view] : std::views::zip(std::views::iota(0u), captureViews))
            {
                matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::view>(), std::make_tuple(view));

                gl::frame_buffer_texture_layer(frameBuffer->handle(), irradianceCubemap_->handle(), gl::frame_buffer_attachment_e::color0, 0, index++);
                gl::clear(gl::buffer_mask_e::color | gl::buffer_mask_e::depth);
                gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, cva->index_count());
            }


            gl::texture_parameter      (environmentCubemap_->handle(), glp::magnification_filter{ gl::texture_magnification_filter_e::linear               });
            gl::texture_parameter      (environmentCubemap_->handle(), glp::minification_filter { gl::texture_minification_filter_e ::linear_mipmap_linear });
            gl::generate_texture_mipmap(environmentCubemap_->handle());



            //PreFilter step
            const fox::vector2u reflectionDimensions{ 128u, 128u };

            auto preFilterBuffer = gfx::uniform_buffer<unf::pre_filter>::create();
            preFilterBuffer->bind(gfx::binding_t{ 5u });

            preFilterCubemap_ = gfx::cubemap::create(gfx::cubemap::format_e::rgb16_float, gfx::cubemap::filter_e::trilinear, gfx::cubemap::wrapping_e::clamp_to_edge, reflectionDimensions);

            pipelines_.at("PreFilter")->bind();
            matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::projection>(), std::make_tuple(captureProjection));
            environmentCubemap_->bind(gfx::binding_t{ 0u });

            frameBuffer->bind(gfx::frame_buffer::target_e::write);
            cva->bind();

            fox::uint32_t maxMipLevels{ preFilterCubemap_->mipmap_levels() };
            for (const auto& mip : std::views::iota(0u, maxMipLevels))
            {
                const fox::vector2u mipDimensions{ reflectionDimensions.x * std::pow(0.5f, mip), reflectionDimensions.y * std::pow(0.5f, mip) };
                const auto& roughness = static_cast<fox::float32_t>(mip) / (maxMipLevels - 1u);
                preFilterBuffer->copy(unf::pre_filter{ envDimensions.x, roughness });

                gl::viewport(mipDimensions);
                gl::render_buffer_storage(renderBuffer->handle(), gl::render_buffer_format_e::d24_unorm, mipDimensions);

                for (auto [index, view] : std::views::zip(std::views::iota(0u), captureViews))
                {
                    matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::view>(), std::make_tuple(view));

                    gl::frame_buffer_texture_layer(frameBuffer->handle(), preFilterCubemap_->handle(), gl::frame_buffer_attachment_e::color0, mip, index++);
                    gl::clear(gl::buffer_mask_e::color | gl::buffer_mask_e::depth);
                    gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, cva->index_count());
                }
            }



            //BRDF LUT step
            brdfTexture_ = gfx::texture2d::create(gfx::texture2d::format_e::rg16_float, gfx::texture2d::filter_e::none, gfx::texture2d::wrapping_e::clamp_to_edge, envDimensions);
            pipelines_.at("BRDF")->bind();

            gl::viewport(envDimensions);
            gl::frame_buffer_texture(frameBuffer->handle(), brdfTexture_->handle(), gl::frame_buffer_attachment_e::color0, 0);
            gl::render_buffer_storage(renderBuffer->handle(), gl::render_buffer_format_e::d24_unorm, envDimensions);
            gl::clear(gl::buffer_mask_e::color | gl::buffer_mask_e::depth);

            pva->bind();
            gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, pva->index_count());










            std::array<FS, 1> ssaoFrameBufferManifest{ FS{ "Occlusion", TF::r32_float }};
            ssaoBuffer_ = gfx::frame_buffer::create(viewportDimensions, ssaoFrameBufferManifest);
            auto occlusion = ssaoBuffer_->surface<gfx::frame_buffer::surface_e::texture>("Occlusion");
            gl::texture_parameter(occlusion->handle(), glp::magnification_filter{ gl::texture_magnification_filter_e::nearest });
            gl::texture_parameter(occlusion->handle(), glp::minification_filter { gl::texture_minification_filter_e ::nearest });



            constexpr auto                                 ssaoSamples{ 64u };
            std::vector<unf::ssao_sample>                  ssaoKernel(ssaoSamples);
            std::uniform_real_distribution<fox::float32_t> distribution(0.0f, 1.0f);
            std::default_random_engine                     engine;
            for (auto index : std::views::iota(0u, 64u))
            {
                unf::ssao_sample sample
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

            ssaoSampleUniform_ = gfx::uniform_array_buffer<unf::ssao_sample, ssaoSamples>::create(ssaoKernel);
            ssaoSampleUniform_->bind(gfx::binding_t{ 7u });



            constexpr auto             ssaoNoiseSamples{ 16u };
            std::vector<fox::vector3f> ssaoNoise(ssaoNoiseSamples);

            for (auto index : std::views::iota(0u, ssaoNoiseSamples))
            {
                fox::vector3f noise
                { 
                    distribution(engine) * 2.0f - 1.0f, 
                    distribution(engine) * 2.0f - 1.0f, 
                    0.0f 
                };

                ssaoNoise.at(index) = noise;
            }

            ssaoNoiseTexture_ = gfx::texture2d::create(gfx::texture2d::format_e::rgb32_float, gfx::texture2d::filter_e::nearest, gfx::texture2d::wrapping_e::repeat, fox::vector2u{ 4u, 4u }, fox::as_bytes(std::span<const fox::vector3f>{ ssaoNoise }));
        }

        void start(gfx::render_info renderInfo)
        {
            renderInfo_ = renderInfo;

            const auto& camera           = renderInfo_.camera;
            const auto& transform        = renderInfo_.cameraTransform;
            const auto& viewMatrix       = glm::lookAt(transform.position, transform.position + transform.forward(), transform.up());
            const auto& projectionMatrix = camera.projection();

            matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::view>(), std::make_tuple(viewMatrix, projectionMatrix));
            cameraUniform_  ->copy    (unf::camera{ fox::vector4f{ transform.position, 1.0f } });



            mmt_                           .clear();
            lights_                        .clear();
            shadowCastingPointLights_      .clear();
            shadowCastingDirectionalLights_.clear();
            debugTransforms_               .clear();



            fox::size_t shadowCastingLightCount{ 0u };
            constexpr auto maximumShadowCastingLights{ 4 };

            for (const auto& [light, position] : renderInfo_.lights)
            {
                unf::light result
                {
                    fox::vector4f{ position,    1.0f },
                    fox::vector4f{ light.color, 1.0f },

                    light.radius,

                    0.01f,
                    0.01f,
                };

                if (light.isShadowCasting && std::cmp_less(shadowCastingLightCount, maximumShadowCastingLights))
                {
                    switch (light.type)
                    {
                        case fox::light::type_e::area:        throw std::exception{ "" };                           break;
                        case fox::light::type_e::directional: shadowCastingDirectionalLights_.emplace_back(result); break;
                        case fox::light::type_e::point:       shadowCastingPointLights_      .emplace_back(result); break;
                        case fox::light::type_e::spot:        throw std::exception{ "" };                           break;
                    }

                    ++shadowCastingLightCount;
                }

                lights_.emplace_back(std::move(result));
            }
        }
        void finish()
        {
            const fox::vector2u  dimensions{ 1280u,  720u };
            const fox::vector2u sDimensions{ 2048u, 2048u };

            //Bind Uniform Buffers to correct indices
            contextUniform_-> bind(gfx::binding_t{ 0u });
            cameraUniform_->  bind(gfx::binding_t{ 1u });
            matricesUniform_->bind(gfx::binding_t{ 2u });
            materialUniform_->bind(gfx::binding_t{ 3u });
            lightUniform_->   bind(gfx::binding_t{ 4u });

            contextUniform_->copy(unf::context{ dimensions, input::cursor_position(), fox::time::since_epoch(), fox::time::delta() });



            gl::viewport(dimensions);

            //Render meshes into gBuffer
            render_meshes(gBuffer_, pipelines_.at("DeferredMesh"));








            ssaoBuffer_->bind(gfx::frame_buffer::target_e::write);

            pipelines_.at("SSAO")->bind();
            gBuffer_->bind_surface("Position", gfx::binding_t{ 0u });
            gBuffer_->bind_surface("Normal"  , gfx::binding_t{ 1u });

            ssaoNoiseTexture_->bind(gfx::binding_t{ 2u });

            gl::viewport(dimensions);
            gl::clear(gl::buffer_mask_e::color);
            gl::disable<gl::feature_e::face_culling>();
            gl::disable<gl::feature_e::depth_test>();
            gl::disable<gl::feature_e::blending>();

            const auto& pva = gfx::geometry::plane;
            pva->bind();
            gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, pva->index_count());





            //Lighting calculations
            render_lighting(pBuffers_.at(0));






            pBuffers_.at(0)->bind(gfx::frame_buffer::target_e::write);
            pipelines_.at("Background")->bind();
            environmentCubemap_->bind(gfx::binding_t{ 0u });

            gl::disable<gl::feature_e::blending>();
            gl::disable<gl::feature_e::face_culling>();
            gl::enable <gl::feature_e::depth_test>();
            gl::depth_function(gl::depth_function_e::less_equal);

            const auto& cva = gfx::geometry::cube;
            cva->bind();
            gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, cva->index_count());





            //Render simple cubes for debugging
#ifdef FOX_DEBUG
            pipelines_.at("Debug")->bind();

            for (const auto& transform : debugTransforms_)
            {
                matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::model>(), std::make_tuple(transform.matrix()));
                gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, cva->index_count());
            }
#endif





            //Blit the final result into the default framebuffer
            //gl::blit_frame_buffer(ssaoBuffer_->handle(), gl::DefaultFrameBuffer, gl::buffer_mask_e::color, glf::FrameBuffer::Filter::Nearest, dimensions, dimensions);
            gl::blit_frame_buffer(pBuffers_.at(0)->handle(), gl::default_frame_buffer, gl::buffer_mask_e::color, gl::frame_buffer_filter_e::nearest, pBuffers_.at(0)->dimensions(), dimensions);
        }

        void render(std::shared_ptr<const gfx::mesh> mesh, std::shared_ptr<const gfx::material> material, const fox::transform& transform)
        {
            mmt_.emplace_back(mesh, material, transform);
        }
        void render_debug(const fox::transform& transform)
        {
            debugTransforms_.emplace_back(transform);
        }

    private:
        void render_meshes(std::shared_ptr<gfx::frame_buffer> frameBuffer, std::shared_ptr<gfx::pipeline> shader)
        {
            frameBuffer->bind(gfx::frame_buffer::target_e::write);
            shader->bind();

            gl::viewport      (frameBuffer->dimensions());
            gl::clear         (gl::buffer_mask_e::all);
            gl::enable        <gl::feature_e::face_culling>();
            gl::cull_face     (gl::culling_facet_e::back);
            gl::front_face    (gl::orientation_e::counter_clockwise);
            gl::enable        <gl::feature_e::depth_test>();
            gl::depth_function(gl::depth_function_e::less);
            gl::disable       <gl::feature_e::blending>();

            auto positionTexture = gBuffer_->surface("Position");
            std::array<fox::float32_t, 4u> data{ 0.0f, 0.0f, -1000.0f };
            gl::clear_texture_image(positionTexture->handle(), gl::texture_base_format_e::rgb, gl::texture_type_e::float_, 0, fox::utl::as_bytes(data));

            for (const auto& _ : mmt_)
            {
                const auto& [mesh, material, transform] = _;

                matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::model>(), std::make_tuple(transform.matrix()));
                materialUniform_->copy      (unf::material{ material->color, material->roughnessFactor, material->metallicFactor });

                mesh            ->bind();
                material->albedo->bind(gfx::binding_t{ 0u });
                material->normal->bind(gfx::binding_t{ 1u });
                material->arm   ->bind(gfx::binding_t{ 2u });

                gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, mesh->index_count());
            }
        }
        void render_lighting(std::shared_ptr<gfx::frame_buffer> target)
        {
            target->bind(api::frame_buffer::target_e::write);
            gl::clear(gl::buffer_mask_e::all);

            gl::blit_frame_buffer(gBuffer_->handle(), target->handle(), gl::buffer_mask_e::depth, gl::frame_buffer_filter_e::nearest, gBuffer_->dimensions(), target->dimensions());



            pipelines_.at("PBR")->bind();
            gBuffer_->bind_surface("Position", gfx::binding_t{ 0u });
            gBuffer_->bind_surface("Albedo"  , gfx::binding_t{ 1u });
            gBuffer_->bind_surface("Normal"  , gfx::binding_t{ 2u });
            gBuffer_->bind_surface("ARM"     , gfx::binding_t{ 3u });

            irradianceCubemap_->bind(gfx::binding_t{ 4u });
            preFilterCubemap_ ->bind(gfx::binding_t{ 5u });
            brdfTexture_      ->bind(gfx::binding_t{ 6u });

            gl::viewport(target->dimensions());
            gl::depth_mask(gl::false_);
            gl::disable<gl::feature_e::depth_test>();
            gl::enable<gl::feature_e::blending>();
            gl::blend_function(gl::blending_factor_e::source_alpha, gl::blending_factor_e::one);
            gl::disable<gl::feature_e::face_culling>();

            const auto& pva = gfx::geometry::plane;
            pva->bind();

            std::ranges::for_each(lights_, [&](const auto& light)
                {
                    fox::transform sphereTransform{ light.position, fox::vector3f{}, fox::vector3f{light.radius} };

                    matricesUniform_->copy_slice(fox::utl::offset_of<unf::matrices, &unf::matrices::model>(), std::make_tuple(sphereTransform.matrix()));
                    lightUniform_   ->copy      ({ light.position, light.color, light.radius, light.linearFalloff, light.quadraticFalloff });

                    gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, pva->index_count());

                });

            gl::depth_mask(gl::true_);
        }
        void render_skybox(std::shared_ptr<gfx::frame_buffer> target, std::shared_ptr<gfx::frame_buffer> previous)
        {
            if (!renderInfo_.skybox) return;

            pipelines_.at("Skybox")->bind();
            renderInfo_.skybox->bind(gfx::binding_t{ 0u });

            gl::blit_frame_buffer(previous->handle(), target->handle(), gl::buffer_mask_e::depth, gl::frame_buffer_filter_e::nearest, previous->dimensions(), target->dimensions());

            gl::viewport(target->dimensions());
            gl::disable<gl::feature_e::face_culling>();
            gl::enable<gl::feature_e::depth_test>();
            gl::depth_function(gl::depth_function_e::less_equal);
            gl::disable<gl::feature_e::blending>();

            const auto& cva = gfx::geometry::cube;
            cva->bind();

            gl::draw_elements(gl::draw_mode_e::triangles, gl::draw_type_e::unsigned_int, cva->index_count());
        }

        std::vector<std::tuple<std::shared_ptr<const gfx::mesh>, std::shared_ptr<const gfx::material>, fox::transform>> mmt_{};
        std::vector<unf::light>                                            lights_{};
        std::vector<unf::light>                                            shadowCastingPointLights_{};
        std::vector<unf::light>                                            shadowCastingDirectionalLights_{};
        std::vector<fox::transform>                                        debugTransforms_{};
        std::shared_ptr<gfx::frame_buffer>                                 gBuffer_{};
        std::shared_ptr<gfx::frame_buffer>                                 sBuffer_{};
        std::array<std::shared_ptr<gfx::frame_buffer>, 2>                  pBuffers_{};
        std::shared_ptr<gfx::frame_buffer>                                 ssaoBuffer_{};
        std::shared_ptr<gfx::texture2d>                                    ssaoNoiseTexture_{};
        std::shared_ptr<gfx::cubemap>                                      environmentCubemap_{};
        std::shared_ptr<gfx::cubemap>                                      irradianceCubemap_{};
        std::shared_ptr<gfx::cubemap>                                      preFilterCubemap_{};
        std::shared_ptr<gfx::texture2d>                                    brdfTexture_{};
        std::shared_ptr<gfx::uniform_buffer<unf::context>>                 contextUniform_{};
        std::shared_ptr<gfx::uniform_buffer<unf::matrices>>                matricesUniform_{};
        std::shared_ptr<gfx::uniform_buffer<unf::material>>                materialUniform_{};
        std::shared_ptr<gfx::uniform_buffer<unf::camera>>                  cameraUniform_{};
        std::shared_ptr<gfx::uniform_buffer<unf::light>>                   lightUniform_{};
        std::shared_ptr<gfx::uniform_array_buffer<unf::ssao_sample, 64u>>  ssaoSampleUniform_{};
        std::unordered_map<std::string, std::shared_ptr<gfx::pipeline>>    pipelines_{};
        fox::float32_t                                                     shadowFarPlane_{ 100.0f };
        gfx::render_info                                                   renderInfo_{};
    };
}
