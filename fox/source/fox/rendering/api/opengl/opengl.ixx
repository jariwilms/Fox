module;

#include <stdafx.hpp>
#include <glad/gl.h>

export module fox.rendering.api.opengl;

export import fox.rendering.api.opengl.concepts;
export import fox.rendering.api.opengl.flags;
export import fox.rendering.api.opengl.mapping;
export import fox.rendering.api.opengl.object;
export import fox.rendering.api.opengl.parameters;
export import fox.rendering.api.opengl.structures;
export import fox.rendering.api.opengl.types;
export import fox.rendering.api.opengl.utility;

export namespace fox::gfx::api::gl
{
    //C++ OpenGL Wrapper Library
    //
    //This library provides a modern, robust, and user-friendly interface for OpenGL.
    //Its primary goals are to:
    //    * Offer a more intuitive and correct interface for development.
    //    * Encapsulate existing OpenGL functions, simplifying integration of custom logic.
    //    * Implement state caching to eliminate redundant driver calls.
    //    * Ensure compile-time and runtime safety through comprehensive input validation.
    //
    //Functions are organized based on their appearance in the OpenGL 4.6 Core Profile Specification.
    //Reference: https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf


    




    //Chapter 22 - Context State Queries
    template<glf::Data D>    requires (not gl::indexed_data_c<D>)
    inline auto get_value                                  () -> auto
    {
        auto get_boolean_v            = [](glf::Data data) -> gl::bool_t
            {
                auto value = gl::boolean_t{};
                return glGetBooleanv(gl::to_underlying(data), &value), value;
            };
        auto get_integer32_v          = [](glf::Data data) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), value;
            };
        auto get_integer64_v          = [](glf::Data data) -> gl::int64_t
            {
                auto value = gl::int64_t{};
                return glGetInteger64v(gl::to_underlying(data), &value), value;
            };
        auto get_unsigned_integer32_v = [](glf::Data data) -> gl::uint32_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::int32_t>(value);
            };
        auto get_unsigned_integer64_v = [](glf::Data data) -> gl::uint64_t
            {
                auto value = gl::int64_t{};
                return glGetInteger64v(gl::to_underlying(data), &value), static_cast<gl::uint64_t>(value);
            };
        auto get_floating_point32_v   = [](glf::Data data) -> gl::float32_t
            {
                auto value = gl::float32_t{};
                return glGetFloatv(gl::to_underlying(data), &value), value;
            };
        auto get_floating_point64_v   = [](glf::Data data) -> gl::float64_t
            {
                auto value = gl::float64_t{};
                return glGetDoublev(gl::to_underlying(data), &value), value;
            };
        auto get_vector4b_v           = [](glf::Data data) -> gl::Vector4b
            {
                auto value = gl::Vector4b{};
                return glGetBooleanv(gl::to_underlying(data), glm::value_ptr(value)), value;
            };
        auto get_vector2i_v           = [](glf::Data data) -> gl::Vector2i
            {
                auto value = gl::Vector2i{};
                return glGetIntegerv(gl::to_underlying(data), glm::value_ptr(value)), value;
            };
        auto get_vector2f_v           = [](glf::Data data) -> gl::Vector2f
            {
                auto value = gl::Vector2f{};
                return glGetFloatv(gl::to_underlying(data), glm::value_ptr(value)), value;
            };
        auto get_vector4f_v           = [](glf::Data data) -> gl::Vector4f
            {
                auto value = gl::Vector4f{};
                return glGetFloatv(gl::to_underlying(data), glm::value_ptr(value)), value;
            };
        auto get_handle_v             = [](glf::Data data) -> gl::handle_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::handle_t>(value);
            };
        auto get_index_v              = [](glf::Data data) -> gl::index_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::index_t>(value);
            };
        auto get_bitfield_v           = [](glf::Data data) -> gl::bitfield_t
            {
                auto value = gl::int32_t{};
                return glGetIntegerv(gl::to_underlying(data), &value), static_cast<gl::bitfield_t>(value);
            };
        auto get_binary_formats_v     = [](glf::Data data) -> std::vector<gl::enum_t>
            {
                auto numberProgramBinaryFormats = gl::int32_t{};
                glGetIntegerv(gl::to_underlying(glf::Data::NumberProgramBinaryFormats), &numberProgramBinaryFormats);

                auto programBinaryFormats = std::vector<gl::enum_t>(static_cast<std::uint32_t>(numberProgramBinaryFormats));
                glGetIntegerv(gl::to_underlying(data), std::bit_cast<gl::int32_t*>(programBinaryFormats.data()));

                return programBinaryFormats;
            };
        auto get_area_v               = [](glf::Data data) -> gl::area_t
            {
                auto value = gl::Vector4u{};
                glGetIntegerv(gl::to_underlying(data), std::bit_cast<gl::int32_t*>(glm::value_ptr(value)));

                return gl::area_t{ gl::Vector2u{ value.z, value.w }, gl::Vector2u{ value.x, value.y } };
            };

        if constexpr (D == glf::Data::AliasedLineWidthRange                           ) return get_vector2f_v(D);
        if constexpr (D == glf::Data::BlendColor                                      ) return get_vector4f_v(D);
        if constexpr (D == glf::Data::BlendDestinationAlpha                           ) return static_cast<glf::Blending::Factor>           (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::BlendDestinationRGB                             ) return static_cast<glf::Blending::Factor>           (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::BlendEquationAlpha                              ) return static_cast<glf::Blending::Equation>         (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::BlendEquationRGB                                ) return static_cast<glf::Blending::Equation>         (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::BlendSourceAlpha                                ) return static_cast<glf::Blending::Factor>           (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::BlendSourceRGB                                  ) return static_cast<glf::Blending::Factor>           (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::ColorClearValue                                 ) return get_vector4f_v(D);
        if constexpr (D == glf::Data::ColorWriteMask                                  ) return get_vector4b_v(D);
        if constexpr (D == glf::Data::ContextFlags                                    ) return static_cast<glf::Context::Flag>              (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::ContextProfileMask                              ) return static_cast<glf::Context::Profile>           (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::CopyReadBufferBinding                           ) return get_handle_v(D);
        if constexpr (D == glf::Data::CopyWriteBufferBinding                          ) return get_handle_v(D);
        if constexpr (D == glf::Data::CurrentProgram                                  ) return get_handle_v(D);
        if constexpr (D == glf::Data::DebugGroupStackDepth                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::DebugLoggedMessages                             ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::DepthClearValue                                 ) return get_floating_point64_v(D);
        if constexpr (D == glf::Data::DepthFunction                                   ) return static_cast<glf::DepthFunction>              (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::DepthRange                                      ) return get_vector2f_v(D);
        if constexpr (D == glf::Data::DispatchIndirectBufferBinding                   ) return get_handle_v(D);
        if constexpr (D == glf::Data::DoubleBuffer                                    ) return get_boolean_v  (D);
        if constexpr (D == glf::Data::DrawBuffer                                      ) return static_cast<glf::FrameBuffer::Source>        (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::DrawFramebufferBinding                          ) return get_handle_v(D);
        if constexpr (D == glf::Data::DrawIndirectBufferBinding                       ) return get_handle_v(D);
        if constexpr (D == glf::Data::FragmentShaderDerivativeHint                    ) return static_cast<glf::Hint::Mode>                 (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::ImplementationColorReadFormat                   ) return static_cast<glf::PixelData::Format>          (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::ImplementationColorReadType                     ) return static_cast<glf::PixelData::Type>            (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::IndexArrayBufferBinding                         ) return get_handle_v(D);
        if constexpr (D == glf::Data::LayerProvokingVertex                            ) return static_cast<glf::ProvokingVertex::Mode>      (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::LineSmoothHint                                  ) return static_cast<glf::Hint::Mode>                 (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::LineWidth                                       ) return get_floating_point64_v(D);
        if constexpr (D == glf::Data::LogicOperationMode                              ) return static_cast<glf::LogicalPixelOperation>      (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::MajorVersion                                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::Maximum3DTextureSize                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumArrayTextureLayers                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumClipDistances                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumColorAttachments                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumColorTextureSamples                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedAtomicCounters                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedComputeUniformComponents         ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedFragmentUniformComponents        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedGeometryUniformComponents        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedShaderStorageBlocks              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedTextureImageUnits                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedUniformBlocks                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedVertexUniformComponents          ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeAtomicCounterBuffers              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeAtomicCounters                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeShaderStorageBlocks               ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeTextureImageUnits                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeUniformBlocks                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeUniformComponents                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupCount                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupInvocations              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupSize                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCubemapTextureSize                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDebugGroupStackDepth                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDebugMessageLength                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDepthTextureSamples                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDrawBuffers                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDualSourceDrawBuffers                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumElementIndex                             ) return get_index_v(D);
        if constexpr (D == glf::Data::MaximumFragmentAtomicCounters                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentInputComponents                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentShaderStorageBlocks              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentUniformBlocks                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentUniformComponents                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentUniformVectors                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFrameBufferHeight                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFrameBufferLayers                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFrameBufferSamples                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFrameBufferWidth                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryAtomicCounters                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryInputComponents                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryOutputComponents                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryShaderStorageBlocks              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryTextureImageUnits                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryUniformBlocks                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryUniformComponents                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumIndexElements                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumIntegerSamples                           ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumLabelLength                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumProgramTexelOffset                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumRectangleTextureSize                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumRenderBufferSize                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumSampleMaskWords                          ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumServerWaitTimeout                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumShaderStorageBufferBindings              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTessellationControlAtomicCounters        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTessellationControlShaderStorageBlocks   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTessellationEvaluationAtomicCounters     ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTessellationEvaluationShaderStorageBlocks) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTextureBufferSize                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTextureImageUnits                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTextureLODBias                           ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTextureSize                              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumUniformBlockSize                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumUniformBufferBindings                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumUniformLocations                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVaryingComponents                        ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVaryingFloats                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVaryingVectors                           ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexAtomicCounters                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexAttributeBindings                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexAttributeRelativeOffset            ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexAttributes                         ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexElements                           ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexOutputComponents                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexShaderStorageBlocks                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexTextureImageUnits                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexUniformBlocks                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexUniformComponents                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexUniformVectors                     ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumViewportDimensions                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumViewports                                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MinimumMapBufferAlignment                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MinimumProgramTexelOffset                       ) return get_integer32_v(D);
        if constexpr (D == glf::Data::MinorVersion                                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::NumberCompressedTextureFormats                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::NumberExtensions                                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::NumberProgramBinaryFormats                      ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::NumberShaderBinaryFormats                       ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackAlignment                                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackImageHeight                                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackRowLength                                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackSkipImages                                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackSkipPixels                                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackSkipRows                                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackSwapBytes                                   ) return get_boolean_v(D);
        if constexpr (D == glf::Data::PixelPackBufferBinding                          ) return get_handle_v(D);
        if constexpr (D == glf::Data::PixelUnpackBufferBinding                        ) return get_handle_v(D);
        if constexpr (D == glf::Data::PointFadeThresholdSize                          ) return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PointSize                                       ) return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PointSizeGranularity                            ) return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PointSizeRange                                  ) return get_vector2f_v(D);
        if constexpr (D == glf::Data::PolygonOffsetFactor                             ) return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PolygonOffsetUnits                              ) return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PolygonSmoothHint                               ) return static_cast<glf::Hint::Mode>                 (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::PrimitiveRestartIndex                           ) return get_index_v(D);
        if constexpr (D == glf::Data::ProgramBinaryFormats                            ) return get_binary_formats_v(D);
        if constexpr (D == glf::Data::ProgramPipelineBinding                          ) return get_handle_v(D);
        if constexpr (D == glf::Data::ProvokingVertex                                 ) return static_cast<glf::ProvokingVertex::Mode>      (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::QueryBufferBinding                              ) return get_handle_v(D);
        if constexpr (D == glf::Data::ReadBuffer                                      ) return static_cast<glf::FrameBuffer::Source>        (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::ReadFrameBufferBinding                          ) return get_handle_v(D);
        if constexpr (D == glf::Data::RenderbufferBinding                             ) return get_handle_v(D);
        if constexpr (D == glf::Data::SampleBuffers                                   ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::SampleCoverageInvert                            ) return get_boolean_v(D);
        if constexpr (D == glf::Data::SampleCoverageValue                             ) return get_floating_point32_v(D);
        if constexpr (D == glf::Data::SamplerBinding                                  ) return get_handle_v(D);
        if constexpr (D == glf::Data::Samples                                         ) return get_bitfield_v(D);
        if constexpr (D == glf::Data::ScissorBox                                      ) return get_area_v(D);
        if constexpr (D == glf::Data::ShaderCompiler                                  ) return get_boolean_v(D);
        if constexpr (D == glf::Data::ShaderStorageBufferBinding                      ) return get_handle_v(D);
        if constexpr (D == glf::Data::ShaderStorageBufferOffsetAlignment              ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::SmoothLineWidthGranularity                      ) return get_floating_point32_v(D);
        if constexpr (D == glf::Data::SmoothLineWidthRange                            ) return get_vector2f_v(D);
        if constexpr (D == glf::Data::StencilBackFail                                 ) return static_cast<glf::Stencil::Action>            (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::StencilBackFunction                             ) return static_cast<glf::Stencil::Function>          (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::StencilBackPassDepthFail                        ) return static_cast<glf::Stencil::Action>            (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::StencilBackPassDepthPass                        ) return static_cast<glf::Stencil::Action>            (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::StencilBackReference                            ) return get_integer32_v(D);
        if constexpr (D == glf::Data::StencilBackValueMask                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::StencilBackWriteMask                            ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::StencilClearValue                               ) return get_index_v(D);
        if constexpr (D == glf::Data::StencilFail                                     ) return static_cast<glf::Stencil::Action>            (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::StencilFunction                                 ) return static_cast<glf::Stencil::Function>          (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::StencilPassDepthFail                            ) return static_cast<glf::Stencil::Action>            (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::StencilPassDepthPass                            ) return static_cast<glf::Stencil::Action>            (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::StencilReference                                ) return get_integer32_v(D);
        if constexpr (D == glf::Data::StencilValueMask                                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::StencilWriteMask                                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::Stereo                                          ) return get_boolean_v(D);
        if constexpr (D == glf::Data::SubpixelBits                                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::TextureBinding1D                                ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding1DArray                           ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding2D                                ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding2DArray                           ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding2DMultisample                     ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding2DMultisampleArray                ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding3D                                ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBindingBuffer                            ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBindingCubemap                           ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBindingRectangle                         ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBufferBinding                            ) return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBufferOffsetAlignment                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::TextureCompressionHint                          ) return static_cast<glf::Hint::Mode>                 (get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::Timestamp                                       ) return get_integer64_v(D);
        if constexpr (D == glf::Data::TransformFeedbackBufferBinding                  ) return get_handle_v(D);
        if constexpr (D == glf::Data::UniformBufferBinding                            ) return get_handle_v(D);
        if constexpr (D == glf::Data::UniformBufferOffsetAlignment                    ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackAlignment                                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackImageHeight                               ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackRowLength                                 ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackSkipImages                                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackSkipPixels                                ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackSkipRows                                  ) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackSwapBytes                                 ) return get_boolean_v(D);
        if constexpr (D == glf::Data::VertexArrayBinding                              ) return get_handle_v(D);
        if constexpr (D == glf::Data::Viewport                                        ) return get_area_v(D);
        if constexpr (D == glf::Data::ViewportBoundsRange                             ) return get_vector2i_v(D);
        if constexpr (D == glf::Data::ViewportIndexProvokingVertex                    ) return static_cast<glf::ProvokingVertex::Convention>(get_unsigned_integer32_v(D));
        if constexpr (D == glf::Data::ViewportSubPixelBits                            ) return get_unsigned_integer32_v(D);
    }
    template<glf::Data D>    requires (gl::indexed_data_c<D>)
    inline auto get_value_index                            (gl::index_t index) -> auto
    {
        auto get_unsigned_integer32_v = [](glf::Data data, gl::index_t index) -> gl::uint32_t
            {
                auto value = gl::int32_t{};
                return glGetIntegeri_v(gl::to_underlying(data), index, &value), static_cast<gl::uint32_t>(value);
            };
        auto get_unsigned_integer64_v = [](glf::Data data, gl::index_t index) -> gl::uint64_t
            {
                auto value = gl::int64_t{};
                return glGetInteger64i_v(gl::to_underlying(data), index, &value), static_cast<gl::uint64_t>(value);
            };
        auto get_handle_v             = [](glf::Data data, gl::index_t index) -> gl::handle_t
            {
                auto value = gl::int32_t{};
                return glGetIntegeri_v(gl::to_underlying(data), index, &value), static_cast<gl::handle_t>(value);
            };
        auto get_area_v               = [](glf::Data data, gl::index_t index) -> gl::area_t
            {
                auto value = gl::Vector4u{};
                glGetIntegeri_v(gl::to_underlying(data), index, std::bit_cast<gl::int32_t*>(glm::value_ptr(value)));

                return gl::area_t{ gl::Vector2u{ value.z, value.w }, gl::Vector2u{ value.x, value.y } };
            };
        
        if constexpr (D == glf::Data::MaximumComputeWorkGroupCount  ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupSize   ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == glf::Data::ShaderStorageBufferBinding    ) return get_handle_v            (D, index);
        if constexpr (D == glf::Data::ShaderStorageBufferSize       ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == glf::Data::ShaderStorageBufferStart      ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == glf::Data::TransformFeedbackBufferBinding) return get_handle_v            (D, index);
        if constexpr (D == glf::Data::TransformfeedbackBufferSize   ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == glf::Data::TransformFeedbackBufferStart  ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == glf::Data::UniformBufferBinding          ) return get_handle_v            (D, index);
        if constexpr (D == glf::Data::UniformBufferSize             ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == glf::Data::UniformBufferStart            ) return get_unsigned_integer64_v(D, index);
        if constexpr (D == glf::Data::VertexBindingBuffer           ) return get_handle_v            (D, index);
        if constexpr (D == glf::Data::VertexBindingDivisor          ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == glf::Data::VertexBindingOffset           ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == glf::Data::VertexBindingStride           ) return get_unsigned_integer32_v(D, index);
        if constexpr (D == glf::Data::Viewport                      ) return get_area_v              (D, index);
    }
    template<glf::Feature F>
    inline void enable                                     ()
    {
        glEnable(gl::to_underlying(F));
    }
    template<glf::Feature F> requires (gl::indexed_feature_c<F>)
    inline void enable_index                               (gl::index_t index)
    {
        glEnablei(gl::to_underlying(F), index);
    }
    template<glf::Feature F>
    inline void disable                                    ()
    {
        glDisable(gl::to_underlying(F));
    }
    template<glf::Feature F> requires (gl::indexed_feature_c<F>)
    inline void disable_index                              (gl::index_t index)
    {
        glDisablei(gl::to_underlying(F), index);
    }
    template<glf::Feature F>
    inline auto is_enabled                                 () -> gl::bool_t
    {
        return glIsEnabled(gl::to_underlying(F));
    }
    template<glf::Feature F> requires (gl::indexed_feature_c<F>)
    inline auto is_enabled_index                           (gl::index_t index) -> gl::bool_t
    {
        return glIsEnabledi(gl::to_underlying(F));
    }
    template<glf::Callback::Pointer P>
    inline auto get_pointer_value                          () -> gl::pointer_t
    {
        auto value = gl::pointer_t{};
        return glGetPointerv(gl::to_underlying(P), &value), value;
    }
    template<glf::Context::Property P>
    inline auto get_string                                 () -> std::string
    {
        return std::string{ std::bit_cast<const gl::char_t*>(glGetString(gl::to_underlying(P))) };
    }
    template<glf::Context::Property P>
    inline auto get_string_index                           (gl::index_t index) -> std::string
    {
        return std::string{ std::bit_cast<const gl::char_t*>(glGetStringi(gl::to_underlying(P), index)) };
    }
    inline auto get_internal_format_value                  () -> auto
    {
        gl::todo();
    }



    //Chapter 4 - Event Model
    template<glf::Synchronization::Property P>
    inline auto get_sync_value                             (gl::sync_t sync) -> auto
    {
        auto get_sync_iv = [](gl::sync_t sync, glf::Synchronization::Property property) -> gl::int32_t
            {
                gl::int32_t value{};
                return glGetSynciv(sync, gl::to_underlying(property), gl::sizei_t{ 1 }, nullptr, &value), value;
            };

        if constexpr (P == glf::Synchronization::Property::Type     ) return static_cast<glf::Synchronization::Object::Type>     (get_sync_iv(sync, P));
        if constexpr (P == glf::Synchronization::Property::Status   ) return static_cast<glf::Synchronization::Object::Status>   (get_sync_iv(sync, P));
        if constexpr (P == glf::Synchronization::Property::Condition) return static_cast<glf::Synchronization::Object::Condition>(get_sync_iv(sync, P));
        if constexpr (P == glf::Synchronization::Property::Flags    ) return gl::bitfield_t{ 0u };
    }
    template<glf::Query::Symbol S>
    inline auto get_query_value                            (glf::Query::Target target) -> gl::uint32_t
    {
        auto value = gl::int32_t{};
        return glGetQueryiv(gl::to_underlying(target), gl::to_underlying(S), &value), static_cast<gl::uint32_t>(value);
    }
    template<glf::Query::Symbol S>
    inline auto get_query_value_index                      (glf::Query::Target target, gl::index_t index) -> gl::uint32_t
    {
        auto value = gl::int32_t{};
        return glGetQueryIndexediv(gl::to_underlying(target), index, gl::to_underlying(S), &value), static_cast<gl::uint32_t>(value);
    }
    template<glf::Query::Parameter P>
    inline auto get_query_object_value                     (gl::handle_t query) -> auto
    {
        auto get_query_object_iv  = [](gl::handle_t query, glf::Query::Parameter parameter) -> gl::int32_t
            {
                gl::int32_t value{};
                return glGetQueryObjectiv(gl::to_underlying(query), gl::to_underlying(parameter), &value), value;
            };
        auto get_query_object_uiv = [](gl::handle_t query, glf::Query::Parameter parameter) -> gl::uint32_t
            {
                gl::uint32_t value{};
                return glGetQueryObjectuiv(gl::to_underlying(query), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == glf::Query::Parameter::Result         ) return                                 get_query_object_uiv(query, P) ;
        if constexpr (P == glf::Query::Parameter::ResultNoWait   ) return                                 get_query_object_uiv(query, P) ;
        if constexpr (P == glf::Query::Parameter::ResultAvailable) return static_cast<gl::bool_t>        (get_query_object_iv (query, P));
        if constexpr (P == glf::Query::Parameter::Target         ) return static_cast<glf::Query::Target>(get_query_object_iv (query, P));
    }
    template<glf::Query::Parameter P>
    inline void get_query_buffer_object_value              (gl::handle_t query, gl::handle_t buffer, gl::offset_t offset)
    {
        auto get_query_buffer_object_iv  = [](gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
            {
                glGetQueryBufferObjectiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
            };
        auto get_query_buffer_object_uiv = [](gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
            {
                glGetQueryBufferObjectuiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
            };

        if constexpr (P == glf::Query::Parameter::Result         ) get_query_buffer_object_uiv(query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::ResultNoWait   ) get_query_buffer_object_uiv(query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::ResultAvailable) get_query_buffer_object_iv (query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::Target         ) get_query_buffer_object_iv (query, buffer, P, offset);
    }



    //Chapter 6 - Buffer Objects
    template<glf::Buffer::Parameter P>
    inline auto get_buffer_parameter_value                 (gl::handle_t buffer) -> auto
    {
        auto get_buffer_parameter_iv   = [](gl::handle_t buffer, glf::Buffer::Parameter parameter) -> gl::int32_t
            {
                gl::int32_t value{};
                return glGetNamedBufferParameteriv(gl::to_underlying(buffer), gl::to_underlying(parameter), &value), value;
            };
        auto get_buffer_parameter_i64v = [](gl::handle_t buffer, glf::Buffer::Parameter parameter) -> gl::int64_t
            {
                gl::int64_t value{};
                return glGetNamedBufferParameteri64v(gl::to_underlying(buffer), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == glf::Buffer::Parameter::Access      ) return static_cast<glf::Buffer::Mapping::Access>     (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::AccessFlags ) return static_cast<glf::Buffer::Mapping::AccessFlags>(get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Immutable   ) return static_cast<gl::bool_t>                       (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::IsMapped    ) return static_cast<gl::bool_t>                       (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::MapLength   ) return static_cast<gl::uint64_t>                     (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::MapOffset   ) return static_cast<gl::uint64_t>                     (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Size        ) return static_cast<gl::size_t>                       (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::StorageFlags) return static_cast<glf::Buffer::StorageFlags>        (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Usage       ) return static_cast<glf::Buffer::Usage>               (get_buffer_parameter_iv  (buffer, P));
    }
    template<typename T>
    inline auto get_buffer_data                            (gl::handle_t buffer) -> std::vector<T>
    {
        auto size = gl::get_buffer_parameter_value(buffer, glf::Buffer::Parameter::Size);
        auto data = std::vector<T>(size);
        return glGetNamedBufferSubData(gl::to_underlying(buffer), gl::offset_t{ 0 }, size, data.data()), data;
    }
    template<typename T>
    inline auto get_buffer_sub_data                        (gl::handle_t buffer, gl::range_t range) -> std::vector<T>
    {
        auto byterange = gl::convert_range<T>(range);
        auto data      = std::vector<T>(range.count);
        return glGetNamedBufferSubData(gl::to_underlying(buffer), byterange.offset, byterange.size, data.data()), data;
    }
    


    //Chapter 7 - Programs and Shaders
    template<glf::Shader::Parameter P>
    inline auto get_shader_value                           (gl::handle_t shader) -> auto
    {
        auto get_shader_iv = [](gl::handle_t shader, glf::Shader::Parameter parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetShaderiv(gl::to_underlying(shader), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == glf::Shader::Parameter::Type         ) return static_cast<glf::Shader::Type>(get_shader_iv(shader, P));
        if constexpr (P == glf::Shader::Parameter::DeleteStatus ) return static_cast<gl::bool_t>       (get_shader_iv(shader, P));
        if constexpr (P == glf::Shader::Parameter::CompileStatus) return static_cast<gl::bool_t>       (get_shader_iv(shader, P));
        if constexpr (P == glf::Shader::Parameter::InfoLogLength) return static_cast<gl::uint32_t>     (get_shader_iv(shader, P));
        if constexpr (P == glf::Shader::Parameter::SourceLength ) return static_cast<gl::uint32_t>     (get_shader_iv(shader, P));
    }
    template<glf::Program::Parameter P>
    inline auto get_program_value                          (gl::handle_t program) -> auto
    {
        auto get_program_iv = [](gl::handle_t program, glf::Program::Parameter parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetProgramiv(gl::to_underlying(program), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == glf::Program::Parameter::ActiveAtomicCounterBuffers           ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveAttributeMaximumLength         ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveAttributes                     ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformBlockMaximumNameLength  ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformBlocks                  ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniformMaximumLength           ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ActiveUniforms                       ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::AttachedShaders                      ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::BinaryLength                         ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ComputeWorkGroupSize                 ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::DeleteStatus                         ) return static_cast<gl::bool_t>                        (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::GeometryInputType                    ) return static_cast<glf::Draw::Mode>                   (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::GeometryOutputType                   ) return static_cast<glf::Draw::Mode>                   (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::GeometryShaderInvocations            ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::GeometryVerticesOut                  ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::InfoLogLength                        ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::IsBinaryRetrievable                  ) return static_cast<gl::bool_t>                        (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::IsSeparable                          ) return static_cast<gl::bool_t>                        (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::LinkStatus                           ) return static_cast<gl::bool_t>                        (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationControlOutputVertices    ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationGenerationMode           ) return static_cast<glf::Tessellation::Generation>     (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationGenerationPointMode      ) return static_cast<gl::bool_t>                        (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationGenerationSpacing        ) return static_cast<glf::Tessellation::Spacing>        (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TessellationGenerationVertexOrder    ) return static_cast<glf::Tessellation::VertexOrder>    (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TransformFeedbackBufferMode          ) return static_cast<glf::TransformFeedback::BufferMode>(get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TransformFeedbackVaryingMaximumLength) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::TransformFeedbackVaryings            ) return static_cast<gl::uint32_t>                      (get_program_iv(program, P));
        if constexpr (P == glf::Program::Parameter::ValidateStatus                       ) return static_cast<gl::bool_t>                        (get_program_iv(program, P));
    }
    template<glf::Pipeline::Property P>
    inline auto get_program_pipeline_value                 (gl::handle_t pipeline) -> auto
    {
        auto get_program_pipeline_iv = [](gl::handle_t pipeline, glf::Pipeline::Property property) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetProgramPipelineiv(gl::to_underlying(pipeline), gl::to_underlying(property), &value), value;
            };

        if   constexpr (P == glf::Pipeline::Property::ValidateStatus) return static_cast<gl::bool_t>  (get_program_pipeline_iv(pipeline, P));
        if   constexpr (P == glf::Pipeline::Property::InfoLogLength ) return static_cast<gl::uint32_t>(get_program_pipeline_iv(pipeline, P));
        else                                                          return static_cast<gl::handle_t>(get_program_pipeline_iv(pipeline, P));
    }
    inline auto get_attached_shaders                       (gl::handle_t program) -> std::vector<gl::handle_t>
    {
        auto attachedShaders = gl::get_program_value<glf::Program::Parameter::AttachedShaders>(program);
        auto shaders         = std::vector<gl::handle_t>(attachedShaders);
        return glGetAttachedShaders(gl::to_underlying(program), attachedShaders, nullptr, gl::to_underlying_ptr(shaders.data())), shaders;
    }
    inline auto get_shader_info_log                        (gl::handle_t shader) -> std::string
    {
        auto infoLogLength = get_shader_value<glf::Shader::Parameter::InfoLogLength>(shader);
        auto infoLog       = std::string(infoLogLength, '\0');

        if (!infoLog.empty())
        {
            glGetShaderInfoLog(gl::to_underlying(shader), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    inline auto get_program_info_log                       (gl::handle_t program) -> std::string
    {
        auto infoLogLength = gl::get_program_value<glf::Program::Parameter::InfoLogLength>(program);
        auto infoLog       = std::string(infoLogLength, '\0');

        if (!infoLog.empty())
        {
            glGetProgramInfoLog(gl::to_underlying(program), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    inline auto get_pipeline_info_log                      (gl::handle_t pipeline) -> std::string
    {
        auto infoLogLength = gl::get_program_pipeline_value<glf::Pipeline::Property::InfoLogLength>(pipeline);
        auto infoLog       = std::string(infoLogLength, '\0');

        if (!infoLog.empty())
        {
            glGetProgramPipelineInfoLog(gl::to_underlying(pipeline), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    inline auto get_shader_source                          (gl::handle_t shader) -> std::string
    {
        auto sourceLength = get_shader_value<glf::Shader::Parameter::SourceLength>(shader);
        auto shaderSource = std::string(sourceLength, '\0');

        if (!shaderSource.empty())
        {
            glGetShaderSource(gl::to_underlying(shader), sourceLength, nullptr, shaderSource.data());
            shaderSource.pop_back();
        }

        return shaderSource;
    }
    inline auto get_shader_precision_format                (glf::Shader::Type type, glf::Shader::PrecisionFormat format) -> std::tuple<std::array<gl::int32_t, 2u>, gl::int32_t>
    {
        auto range     = std::array<gl::int32_t, 2u>{};
        auto precision = gl::int32_t{};
        return glGetShaderPrecisionFormat(gl::to_underlying(type), gl::to_underlying(format), range.data(), &precision), std::make_tuple(range, precision);
    }



    //Chapter 8 - Textures and Samplers
    template<glf::Sampler::Parameter P>
    inline auto get_sampler_parameter_value                (gl::handle_t sampler) -> auto
    {
        auto get_sampler_parameter_iv  = [](gl::handle_t sampler, glf::Sampler::Parameter parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value), value;
            };
        auto get_sampler_parameter_uiv = [](gl::handle_t sampler, glf::Sampler::Parameter parameter) -> gl::uint32_t
            {
                auto value = gl::uint32_t{};
                return glGetSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value), value;
            };
        auto get_sampler_parameter_fv  = [](gl::handle_t sampler, glf::Sampler::Parameter parameter) -> gl::float32_t
            {
                auto value = gl::float32_t{};
                return glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value), value;
            };
        auto get_border_color          = [](gl::handle_t sampler) -> gl::Vector4f
            {
                auto value = gl::Vector4f{};
                return glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(glf::Sampler::Parameter::BorderColor), glm::value_ptr(value)), value;
            };

        if constexpr (P == glf::Sampler::Parameter::BorderColor        ) return                                                get_border_color         (sampler    );
        if constexpr (P == glf::Sampler::Parameter::CompareFunction    ) return static_cast<glf::Texture::CompareFunction>    (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::CompareMode        ) return static_cast<glf::Texture::CompareMode>        (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::LodBias            ) return                                                get_sampler_parameter_fv (sampler, P );
        if constexpr (P == glf::Sampler::Parameter::MagnificationFilter) return static_cast<glf::Texture::MagnificationFilter>(get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::MaximumAnisotropy  ) return                                                get_sampler_parameter_fv (sampler, P );
        if constexpr (P == glf::Sampler::Parameter::MaximumLOD         ) return                                                get_sampler_parameter_fv (sampler, P );
        if constexpr (P == glf::Sampler::Parameter::MinificationFilter ) return static_cast<glf::Texture::MinificationFilter> (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::MinimumLOD         ) return                                                get_sampler_parameter_fv (sampler, P );
        if constexpr (P == glf::Sampler::Parameter::WrappingR          ) return static_cast<glf::Texture::Wrapping>           (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::WrappingS          ) return static_cast<glf::Texture::Wrapping>           (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::WrappingT          ) return static_cast<glf::Texture::Wrapping>           (get_sampler_parameter_uiv(sampler, P));
    }
    template<glf::Texture::Format F>
    inline auto get_texture_image                          (gl::handle_t texture, gl::uint32_t level, gl::size_t size) -> auto
    {
        if constexpr (F == glf::Texture::Format::RGBA8_UNORM )
        {
            auto value = std::vector<gl::Vector4u>(size);

            glGetTextureImage(
                gl::to_underlying       (texture)                      , 
                static_cast<gl::int32_t>(level)                        , 
                gl::to_underlying       (glf::Buffer::BaseFormat::RGBA), gl::to_underlying(glf::PixelData::Type::UnsignedByte), 
                static_cast<gl::sizei_t>(value.size())                 , value.data());

            return value;
        }
        if constexpr (F == glf::Texture::Format::RGBA32_FLOAT)
        {
            gl::todo();
        }
    }
    template<glf::Texture::Format F>
    inline auto get_texture_sub_image                      (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, gl::size_t size) -> auto
    {
        if constexpr (F == glf::Texture::Format::RGBA8_UNORM )
        {
            auto value = std::vector<gl::Vector4u>(size);

            glGetTextureSubImage(
                gl::to_underlying       (texture)                      , 
                static_cast<gl::int32_t>(level)                        , 
                static_cast<gl::int32_t>(region.origin.x)              , static_cast<gl::int32_t>(region.origin.y)            , static_cast<gl::int32_t>(region.origin.z), 
                static_cast<gl::sizei_t>(region.extent.x)              , static_cast<gl::sizei_t>(region.extent.y)            , static_cast<gl::sizei_t>(region.extent.z), 
                gl::to_underlying       (glf::Buffer::BaseFormat::RGBA), gl::to_underlying(glf::PixelData::Type::UnsignedByte), 
                static_cast<gl::sizei_t>(value.size())                 , value.data());

            return value;
        }
        if constexpr (F == glf::Texture::Format::RGBA32_FLOAT)
        {
            gl::todo();
        }
    }
    template<glf::Texture::Format F>
    inline auto get_compressed_texture_image               (gl::handle_t texture, gl::uint32_t level, gl::size_t size) -> auto
    {
        if constexpr (F == glf::Texture::Format::RGBA8_UNORM )
        {
            auto value = std::vector<gl::Vector4u>(size);

            glGetCompressedTextureImage(
                gl::to_underlying       (texture)                      , 
                static_cast<gl::int32_t>(level)                        , 
                static_cast<gl::sizei_t>(value.size())                 , value.data());

            return value;
        }
        if constexpr (F == glf::Texture::Format::RGBA32_FLOAT)
        {
            gl::todo();
        }
    }
    template<glf::Texture::Format F>
    inline auto get_compressed_texture_sub_image           (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, gl::size_t size) -> auto
    {
        if constexpr (F == glf::Texture::Format::RGBA8_UNORM )
        {
            auto value = std::vector<gl::Vector4u>(size);

            glGetCompressedTextureSubImage(
                gl::to_underlying       (texture)        , 
                static_cast<gl::int32_t>(level)          , 
                static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
                static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
                static_cast<gl::sizei_t>(value.size())   , value.data());

            return value;
        }
        if constexpr (F == glf::Texture::Format::RGBA32_FLOAT)
        {
            gl::todo();
        }
    }



    //Chapter 9 - FrameBuffer and FrameBuffer Objects
    template<glf::FrameBuffer::Parameter P>
    inline auto get_frame_buffer_parameter_value           (gl::handle_t frameBuffer) -> auto
    {
        auto get_frame_buffer_parameter_iv = [](gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetNamedFramebufferParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == glf::FrameBuffer::Parameter::DefaultWidth               ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv   (frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::DefaultHeight              ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv   (frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::DefaultLayers              ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv   (frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::DefaultSamples             ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv   (frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::DefaultFixedSampleLocations) return static_cast<gl::bool_t>            (get_frame_buffer_parameter_iv   (frameBuffer, P));

        if (frameBuffer == gl::DefaultFrameBuffer) throw std::invalid_argument{ "Operation may not be called on the default framebuffer!" };

        if constexpr (P == glf::FrameBuffer::Parameter::ColorReadFormat            ) return static_cast<glf::PixelData::Format>(get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::ColorReadType              ) return static_cast<glf::PixelData::Type>  (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::DoubleBuffer               ) return static_cast<gl::bool_t>            (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::SampleBuffers              ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::Samples                    ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv(frameBuffer, P));
        if constexpr (P == glf::FrameBuffer::Parameter::Stereo                     ) return static_cast<gl::bool_t>            (get_frame_buffer_parameter_iv(frameBuffer, P));
    }
    template<glf::FrameBuffer::Parameter P>
    inline auto get_frame_buffer_attachment_parameter_value(gl::handle_t frameBuffer) -> auto
    {
        auto get_frame_buffer_attachment_parameter_iv = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, glf::FrameBuffer::Parameter parameter)
            {
                auto value = gl::int32_t{};
                return glGetNamedFramebufferAttachmentParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(parameter), &value), value;
            };

        gl::todo();
    }
    template<glf::RenderBuffer::Parameter P>
    inline auto get_render_buffer_parameter_value          (gl::handle_t renderBuffer) -> auto
    {
        auto get_render_buffer_parameter_iv = [](gl::handle_t renderBuffer, glf::RenderBuffer::Parameter parameter) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetNamedRenderbufferParameteriv(gl::to_underlying(renderBuffer), gl::to_underlying(parameter), &value), value;
            };

        if constexpr (P == glf::RenderBuffer::Parameter::Width         ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::Height        ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::InternalFormat) return static_cast<glf::FrameBuffer::Format>(get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::Samples       ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::RedSize       ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::GreenSize     ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::BlueSize      ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::AlphaSize     ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::DepthSize     ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
        if constexpr (P == glf::RenderBuffer::Parameter::StencilSize   ) return static_cast<gl::uint32_t>            (get_render_buffer_parameter_iv(renderBuffer, P));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    template<glf::VertexArray::Parameter P>
    inline auto get_vertex_array_indexed_value             (gl::handle_t vertexArray) -> gl::handle_t
    {
        if constexpr (P == glf::VertexArray::Parameter::ElementArrayBufferBinding)
        {
            auto value = gl::int32_t{};
            return glGetVertexArrayiv(gl::to_underlying(vertexArray), gl::to_underlying(P), &value), static_cast<gl::handle_t>(value);
        }
    }
    template<glf::VertexArray::Parameter P>
    inline auto get_vertex_array_indexed_value             (gl::handle_t vertexArray, gl::index_t index) -> auto
    {
        auto get_vertex_array_indexed32_iv = [](gl::handle_t vertexArray, glf::VertexArray::Parameter parameter, gl::index_t index) -> gl::int32_t
            {
                auto value = gl::int32_t{};
                return glGetVertexArrayIndexediv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value), value;
            };
        auto get_vertex_array_indexed64_iv = [](gl::handle_t vertexArray, glf::VertexArray::Parameter parameter, gl::index_t index) -> gl::int32_t
            {
                auto value = gl::int64_t{};
                return glGetVertexArrayIndexed64iv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value), value;
            };
        
        auto maximumVertexAttributes = gl::get_value<glf::Data::MaximumVertexAttributes>();
        if (gl::compare<std::greater>(index, maximumVertexAttributes - 1u)) throw std::out_of_range{ "The given index is out of range!" };
        
        if constexpr (P == glf::VertexArray::Parameter::BindingOffset ) return static_cast<gl::uint64_t>                     (get_vertex_array_indexed64_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Divisor       ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Enabled       ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::IsIntegerData ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::IsLongData    ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::IsNormalized  ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::RelativeOffset) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Size          ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Stride        ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Type          ) return static_cast<glf::VertexArray::Attribute::Type>(get_vertex_array_indexed32_iv(vertexArray, P, index));
    }



    //Chapter 20 - Debug Output
    inline auto get_debug_message_log                      (gl::count_t count) -> std::vector<gl::message_log>
    {
        auto get_debug_message_log = [](gl::count_t count, std::span<glf::Debug::Source> sources, std::span<glf::Debug::Type> types, std::span<gl::uint32_t> ids, std::span<glf::Debug::Severity> severities, std::span<gl::sizei_t> lengths, std::string& messageLog)
            {
                auto maximumLength = gl::get_value<glf::Data::MaximumDebugMessageLength>();
                     messageLog    = std::string(count * maximumLength, '\0');

                return glGetDebugMessageLog(
                    count, static_cast<gl::sizei_t>(maximumLength), 
                    gl::to_underlying_ptr(sources   .data()), 
                    gl::to_underlying_ptr(types     .data()), 
                                          ids       .data(), 
                    gl::to_underlying_ptr(severities.data()), 
                                          lengths   .data(), 
                                          messageLog.data());
            };
        
        auto sources     = std::vector<glf::Debug::Source>  (count);
        auto types       = std::vector<glf::Debug::Type>    (count);
        auto ids         = std::vector<gl::uint32_t>        (count);
        auto severities  = std::vector<glf::Debug::Severity>(count);
        auto lengths     = std::vector<gl::sizei_t>         (count);
        auto messageLog  = std::string{};

        auto amount      = get_debug_message_log(count, sources, types, ids, severities, lengths, messageLog);
        auto messageLogs = std::vector<gl::message_log>(amount);

        if (!messageLogs.empty())
        {
            for (auto offset = gl::offset_t{}; auto index : std::views::iota(0u, amount))
            {
                auto length = lengths.at(index);
                auto log    = std::string{ messageLog.data() + offset, static_cast<std::size_t>(length) - 1u };

                offset += length;

                messageLogs.emplace_back(
                    ids       .at(index),
                    std::move(log), 
                    sources   .at(index),
                    types     .at(index),
                    severities.at(index));
            }
        }

        return messageLogs;
    }







    //Chapter 2 - OpenGL Fundamentals
    inline auto get_graphics_reset_status                  () -> glf::Error::GraphicsResetStatus
    {
        return static_cast<glf::Error::GraphicsResetStatus>(glGetGraphicsResetStatus());
    }
    inline void flush                                      ()
    {
        glFlush();
    }
    inline void finish                                     ()
    {
        glFinish();
    }



    //Chapter 4 - Event Model
    inline auto fence_sync                                 () -> gl::sync_t
    {
        return static_cast<gl::sync_t>(glFenceSync(gl::to_underlying(glf::Synchronization::Object::Condition::GPUCommandsComplete), gl::bitfield_t{ 0u }));
    }
    inline void delete_sync                                (gl::sync_t sync)
    {
        if (sync) glDeleteSync(sync);
    }
    inline auto client_wait_sync                           (gl::sync_t sync, glf::Synchronization::Command command, gl::time_t timeout) -> glf::Synchronization::Status
    {
        return static_cast<glf::Synchronization::Status>(glClientWaitSync(sync, gl::to_underlying(command), timeout));
    }
    inline void server_wait_sync                           (gl::sync_t sync)
    {
        glWaitSync(sync, gl::bitfield_t{ 0u }, gl::to_underlying(glf::Synchronization::Timeout::Ignored));
    }
    inline auto create_query                               (glf::Query::Target target) -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateQueries(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    inline auto create_queries                             (glf::Query::Target target, gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateQueries(gl::to_underlying(target), static_cast<gl::sizei_t>(count), gl::to_underlying_ptr(handles.data())), handles;
    }
    inline void delete_query                               (gl::handle_t query)
    {
        glDeleteQueries(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&query));
    }
    inline void delete_queries                             (std::span<const gl::handle_t> queries)
    {
        glDeleteQueries(static_cast<gl::sizei_t>(queries.size()), gl::to_underlying_ptr(queries.data()));
    }
    inline void begin_query                                (gl::handle_t query, glf::Query::Target target)
    {
        glBeginQuery(gl::to_underlying(target), gl::to_underlying(query));
    }
    inline void begin_query_index                          (gl::handle_t query, glf::Query::Target target, gl::index_t index)
    {
        glBeginQueryIndexed(gl::to_underlying(target), index, gl::to_underlying(query));
    }
    inline void end_query                                  (glf::Query::Target target)
    {
        glEndQuery(gl::to_underlying(target));
    }
    inline void end_query_index                            (glf::Query::Target target, gl::index_t index)
    {
        glEndQueryIndexed(gl::to_underlying(target), index);
    }
    inline void query_counter                              (gl::handle_t query)
    {
        glQueryCounter(gl::to_underlying(query), gl::to_underlying(glf::Query::Counter::Timestamp));
    }



    //Chapter 6 - Buffer Objects
    inline auto create_buffer                              () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    inline auto create_buffers                             (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateBuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    inline void delete_buffer                              (gl::handle_t buffer)
    {
        glDeleteBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&buffer));
    }
    inline void delete_buffers                             (std::span<const gl::handle_t> buffers)
    {
        glDeleteBuffers(static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()));
    }
    inline void bind_buffer_base                           (gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::binding_t binding)
    {
        glBindBufferBase(gl::to_underlying(target), gl::to_underlying(binding), gl::to_underlying(buffer));
    }
    inline void bind_buffers_base                          (std::span<const gl::handle_t> buffers, glf::Buffer::BaseTarget target, gl::binding_t binding)
    {
        glBindBuffersBase(gl::to_underlying(target), gl::to_underlying(binding), static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()));
    }
    template<typename T>
    inline void bind_buffer_range                          (gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::binding_t binding, gl::range_t range)
    {
        auto byterange = gl::convert_range<T>(range);
        glBindBufferRange(gl::to_underlying(target), gl::to_underlying(binding), gl::to_underlying(buffer), byterange.offset, byterange.size);
    }
    template<typename T>
    inline void bind_buffers_range                         (std::span<const gl::handle_t> buffers, std::span<const gl::range_t> ranges, glf::Buffer::BaseTarget target, gl::binding_t binding)
    {
        auto sizes   = std::vector<gl::size_t>  (ranges.size());
        auto offsets = std::vector<gl::offset_t>(ranges.size());

        std::ranges::for_each(ranges, [&](const gl::range_t& range)
            {
                auto byterange = gl::convert_range<T>(range);

                sizes  .emplace_back(byterange.size  );
                offsets.emplace_back(byterange.offset);
            });

        glBindBuffersRange(gl::to_underlying(target), gl::to_underlying(binding), static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()), offsets.data(), sizes.data());
    }
    template<typename T>
    inline void buffer_storage                             (gl::handle_t buffer, glf::Buffer::StorageFlags flags, gl::count_t count)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(count * sizeof(T)), nullptr, gl::to_underlying(flags));
    }
    template<typename T>                  
    inline void buffer_storage                             (gl::handle_t buffer, glf::Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(data.size_bytes()), data.data(), gl::to_underlying(flags));
    }
    template<typename T>
    inline void buffer_data                                (gl::handle_t buffer, gl::index_t index, std::span<const T> data)
    {
        glNamedBufferSubData(gl::to_underlying(buffer), static_cast<gl::offset_t>(index * sizeof(T)), static_cast<gl::size_t>(data.size_bytes()), data.data());
    }
    template<typename T>
    inline void clear_buffer_data                          (gl::handle_t buffer, glf::Buffer::BaseFormat baseFormat, glf::Buffer::Format format, glf::DataType type, std::span<const T> data)
    {
        gl::todo();
        glClearNamedBufferData(gl::to_underlying(buffer), gl::to_underlying(format), gl::to_underlying(baseFormat), gl::to_underlying(type), data.data());
    }
    template<typename T>
    inline void clear_buffer_sub_data                      (gl::handle_t buffer, glf::Buffer::BaseFormat baseFormat, glf::Buffer::Format format, glf::DataType type, gl::range_t range)
    {
        auto byterange = gl::convert_range<T>(range);
        glClearNamedBufferSubData(gl::to_underlying(buffer), gl::to_underlying(format), byterange.offset, byterange.size, gl::to_underlying(baseFormat), gl::to_underlying(type), nullptr);
    }
    template<typename T>
    inline auto map_buffer                                 (gl::handle_t buffer, glf::Buffer::Mapping::AccessFlags access, gl::count_t count) -> std::span<T>
    {
        return std::span{ std::bit_cast<T*>(glMapNamedBuffer(gl::to_underlying(buffer), gl::to_underlying(access))), count };
    }
    template<typename T>
    inline auto map_buffer_range                           (gl::handle_t buffer, glf::Buffer::Mapping::RangeAccessFlags access, gl::range_t range) -> std::span<T>
    {
        auto byterange = gl::convert_range<T>(range);
        return std::span{ std::bit_cast<T*>(glMapNamedBufferRange(gl::to_underlying(buffer), byterange.offset, byterange.size, gl::to_underlying(access))), range.count };
    }
    template<typename T>
    inline void flush_buffer_range                         (gl::handle_t buffer, gl::range_t range)
    {
        auto byterange = gl::convert_range<T>(range);
        glFlushMappedNamedBufferRange(gl::to_underlying(buffer), byterange.offset, byterange.size);
    }
    inline auto unmap_buffer                               (gl::handle_t buffer) -> gl::bool_t
    {
        return glUnmapNamedBuffer(gl::to_underlying(buffer));
    }
    inline void invalidate_buffer_data                     (gl::handle_t buffer)
    {
        glInvalidateBufferData(gl::to_underlying(buffer));
    }
    template<typename T>
    inline void invalidate_buffer_sub_data                 (gl::handle_t buffer, gl::range_t range)
    {
        auto byterange = gl::convert_range<T>(range);
        glInvalidateBufferSubData(gl::to_underlying(buffer), byterange.offset, byterange.size);
    }
    template<typename T>
    inline void copy_buffer_sub_data                       (gl::handle_t source, gl::handle_t destination, gl::range_t sourceRange, gl::range_t destinationRange)
    {
        auto sourceByterange      = gl::convert_range<T>(sourceRange     );
        auto destinationByterange = gl::convert_range<T>(destinationRange);
        glCopyNamedBufferSubData(gl::to_underlying(source), gl::to_underlying(destination), sourceByterange.offset, destinationByterange.offset, sourceByterange.size);
    }
    


    //Chapter 7 - Programs and Shaders
    inline auto create_shader                              (glf::Shader::Type type) -> gl::handle_t
    {
        return static_cast<gl::handle_t>(glCreateShader(gl::to_underlying(type)));
    }
    inline void shader_source                              (gl::handle_t shader, const std::string& source)
    {
        const auto* cstr = source.c_str();
        glShaderSource(gl::to_underlying(shader), gl::sizei_t{ 1 }, &cstr, nullptr);
    }
    inline void compile_shader                             (gl::handle_t shader)
    {
        glCompileShader(gl::to_underlying(shader));
    }
    inline void release_shader_compiler                    ()
    {
        glReleaseShaderCompiler();
    }
    inline void delete_shader                              (gl::handle_t shader)
    {
        glDeleteShader(gl::to_underlying(shader));
    }
    inline void shader_binary                              (gl::handle_t shader, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glShaderBinary(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&shader), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    inline void shader_binaries                            (std::span<const gl::handle_t> shaders, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glShaderBinary(static_cast<gl::sizei_t>(shaders.size()), gl::to_underlying_ptr(shaders.data()), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    template<gl::count_t N = 0>
    inline void specialize_shader                          (gl::handle_t shader, const std::string& entry, std::span<const gl::uint32_t, N> indices = {}, std::span<const gl::uint32_t, N> values = {})
    {
        const auto* cstr = entry.c_str();
        glSpecializeShader(gl::to_underlying(shader), cstr, N, indices.data(), values.data());
    }
    inline auto create_program                             () -> gl::handle_t
    {
        return static_cast<gl::handle_t>(glCreateProgram());
    }
    inline void attach_shader                              (gl::handle_t program, gl::handle_t shader)
    {
        glAttachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    inline void detach_shader                              (gl::handle_t program, gl::handle_t shader)
    {
        glDetachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    inline void link_program                               (gl::handle_t program)
    {
        glLinkProgram(gl::to_underlying(program));
    }
    template<glf::Program::Specification S>
    inline void program_parameter                          (gl::handle_t program, gl::bool_t value)
    {
        glProgramParameteri(gl::to_underlying(program), gl::to_underlying(S), value);
    }
    inline void delete_program                             (gl::handle_t program)
    {
        glDeleteProgram(gl::to_underlying(program));
    }
    inline auto create_shader_program                      (glf::Shader::Type type, const std::string& source) -> gl::handle_t
    {
        const auto* cstr = source.c_str();
        return static_cast<gl::handle_t>(glCreateShaderProgramv(gl::to_underlying(type), gl::sizei_t{ 1 }, &cstr));
    }
    inline auto create_program_pipeline                    () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    inline auto create_program_pipelines                   (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateProgramPipelines(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    inline void delete_program_pipeline                    (gl::handle_t pipeline)
    {
        glDeleteProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&pipeline));
    }
    inline void delete_program_pipelines                   (std::span<const gl::handle_t> pipeline)
    {
        glDeleteProgramPipelines(static_cast<gl::sizei_t>(pipeline.size()), gl::to_underlying_ptr(pipeline.data()));
    }
    inline void bind_program_pipeline                      (gl::handle_t pipeline)
    {
        glBindProgramPipeline(gl::to_underlying(pipeline));
    }
    inline void use_program_stages                         (gl::handle_t pipeline, gl::handle_t program, glf::Program::Stage stages)
    {
        glUseProgramStages(gl::to_underlying(pipeline), gl::to_underlying(stages), gl::to_underlying(program));
    }
    inline auto get_program_binary                         (gl::handle_t program) -> gl::binary_info
    {
        auto binaryLength = gl::get_program_value<glf::Program::Parameter::BinaryLength>(program);
        auto info         = gl::binary_info{};
        return glGetProgramBinary(gl::to_underlying(program), binaryLength, nullptr, &info.format, info.binary.data()), info;
    }
    inline void program_binary                             (gl::handle_t program, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glProgramBinary(gl::to_underlying(program), format, binary.data(), static_cast<gl::sizei_t>(binary.size()));
    }
    inline void memory_barrier                             (glf::Memory::Barrier         barrier)
    {
        glMemoryBarrier(gl::to_underlying(barrier));
    }
    inline void memory_barrier_by_region                   (glf::Memory::RegionalBarrier barrier)
    {
        glMemoryBarrierByRegion(gl::to_underlying(barrier));
    }



    //Chapter 8 - Textures and Samplers
    inline auto create_texture                             (glf::Texture::Target target) -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateTextures(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    inline auto create_textures                            (glf::Texture::Target target, gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateTextures(gl::to_underlying(target), static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    inline void delete_texture                             (gl::handle_t texture)
    {
        glDeleteTextures(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&texture));
    }
    inline void delete_textures                            (std::span<const gl::handle_t> textures)
    {
        glDeleteTextures(static_cast<gl::sizei_t>(textures.size()), gl::to_underlying_ptr(textures.data()));
    }
    inline void bind_texture_unit                          (gl::handle_t texture, gl::binding_t binding)
    {
        glBindTextureUnit(gl::to_underlying(binding), gl::to_underlying(texture));
    }
    inline auto create_sampler                             () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateSamplers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    inline auto create_samplers                            (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateSamplers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    inline void delete_sampler                             (gl::handle_t sampler)
    {
        glDeleteSamplers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&sampler));
    }
    inline void delete_samplers                            (std::span<const gl::handle_t> samplers)
    {
        glDeleteSamplers(static_cast<gl::sizei_t>(samplers.size()), gl::to_underlying_ptr(samplers.data()));
    }
    inline void bind_sampler                               (gl::handle_t sampler, gl::binding_t binding)
    {
        glBindSampler(gl::to_underlying(binding), gl::to_underlying(sampler));
    }
    inline void bind_samplers                              (std::span<const gl::handle_t> samplers, gl::range_t range)
    {
        glBindSamplers(range.index, range.count, gl::to_underlying_ptr(samplers.data()));
    }
    inline auto sampler_parameter                          (gl::handle_t sampler, glp::sampler_parameter_v parameter) -> auto
    {
        auto sampler_parameter_iv  = [](gl::handle_t sampler, glf::Sampler::Parameter parameter, gl::int32_t   value)
            {
                glSamplerParameterIiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };
        auto sampler_parameter_uiv = [](gl::handle_t sampler, glf::Sampler::Parameter parameter, gl::uint32_t  value)
            {
                glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };
        auto sampler_parameter_fv  = [](gl::handle_t sampler, glf::Sampler::Parameter parameter, gl::float32_t value)
            {
                glSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };

        const auto overload = gl::overload
        {
            [=](glp::compare_mode         _) { sampler_parameter_uiv(sampler, glf::Sampler::Parameter::CompareMode        , gl::to_underlying(_.value)); }, 
            [=](glp::compare_function     _) { sampler_parameter_uiv(sampler, glf::Sampler::Parameter::CompareFunction    , gl::to_underlying(_.value)); }, 
            [=](glp::magnification_filter _) { sampler_parameter_uiv(sampler, glf::Sampler::Parameter::MagnificationFilter, gl::to_underlying(_.value)); }, 
            [=](glp::minification_filter  _) { sampler_parameter_uiv(sampler, glf::Sampler::Parameter::MinificationFilter , gl::to_underlying(_.value)); }, 
            [=](glp::wrapping_s           _) { sampler_parameter_uiv(sampler, glf::Sampler::Parameter::WrappingS          , gl::to_underlying(_.value)); }, 
            [=](glp::wrapping_t           _) { sampler_parameter_uiv(sampler, glf::Sampler::Parameter::WrappingT          , gl::to_underlying(_.value)); }, 
            [=](glp::wrapping_r           _) { sampler_parameter_uiv(sampler, glf::Sampler::Parameter::WrappingR          , gl::to_underlying(_.value)); }, 
            [=](glp::border_color         _) 
                {
                    const auto overload = gl::overload
                    {
                        [=](std::array<gl::int32_t  , 4u> _) { glSamplerParameterIiv (gl::to_underlying(sampler), gl::to_underlying(glf::Sampler::Parameter::BorderColor), _.data()); }, 
                        [=](std::array<gl::uint32_t , 4u> _) { glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(glf::Sampler::Parameter::BorderColor), _.data()); }, 
                        [=](std::array<gl::float32_t, 4u> _) { glSamplerParameterfv  (gl::to_underlying(sampler), gl::to_underlying(glf::Sampler::Parameter::BorderColor), _.data()); }, 
                    };

                    std::visit(overload, _.value);
                }, 
            [=](glp::maximum_lod          _) { sampler_parameter_fv (sampler, glf::Sampler::Parameter::MaximumLOD         ,                   _.value ); }, 
            [=](glp::minimum_lod          _) { sampler_parameter_fv (sampler, glf::Sampler::Parameter::MinimumLOD         ,                   _.value ); }, 
        };

        std::visit(overload, parameter);
    }
    template<glf::PackingMode P>
    inline void pixel_store                                (gl::int32_t parameter)
    {
        glPixelStorei(gl::to_underlying(P), parameter);
    }
    inline void texture_sub_image_1d                       (gl::handle_t texture, glf::Texture::BaseFormat format, glf::PixelData::Type type, gl::uint32_t level, gl::length_t region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(region.origin.x), 
            static_cast<gl::sizei_t>(region.extent.x), 
            gl::to_underlying       (format)         , gl::to_underlying(type)        , 
            data.data());
    }
    inline void texture_sub_image_2d                       (gl::handle_t texture, glf::Texture::BaseFormat format, glf::PixelData::Type type, gl::uint32_t level, gl::area_t   region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying       (format)         , gl::to_underlying(type), 
            data.data());
    }
    inline void texture_sub_image_3d                       (gl::handle_t texture, glf::Texture::BaseFormat format, glf::PixelData::Type type, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , gl::to_underlying(type)                  , 
            data.data());
    }
    inline void copy_texture_sub_image_1d                  (gl::handle_t texture, gl::uint32_t level, gl::length_t region, const gl::Vector2u& coordinates)
    {
        glCopyTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)        , 
            static_cast<gl::int32_t>(region.origin.x), 
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates.y), 
            static_cast<gl::sizei_t>(region.extent.x));
    }
    inline void copy_texture_sub_image_2d                  (gl::handle_t texture, gl::uint32_t level, gl::area_t   region, const gl::Vector2u& coordinates)
    {
        glCopyTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates  .y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    inline void copy_texture_sub_image_3d                  (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, const gl::Vector2u& coordinates)
    {
        glCopyTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates  .y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    inline void compressed_texture_sub_image_1d            (gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, gl::length_t region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(region.origin.x), 
            static_cast<gl::sizei_t>(region.extent.x), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    inline void compressed_texture_sub_image_2d            (gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, gl::area_t   region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    inline void compressed_texture_sub_image_3d            (gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    inline void texture_buffer                             (gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format)
    {
        glTextureBuffer(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer));
    }
    template<typename T>
    inline void texture_buffer_range                       (gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format, gl::range_t range)
    {
        auto byterange = gl::convert_range<T>(range);
        glTextureBufferRange(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer), byterange.offset, byterange.size);
    }
    inline void texture_parameter                          (gl::handle_t texture, glp::texture_parameter_v parameter)
    {
        auto texture_parameter_iv  = [](gl::handle_t texture, glf::Texture::Parameter parameter, gl::int32_t   value) -> gl::void_t
            {
                glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), value);
            };
        auto texture_parameter_uiv = [](gl::handle_t texture, glf::Texture::Parameter parameter, gl::uint32_t  value) -> gl::void_t
            {
                glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
            };
        auto texture_parameter_fv  = [](gl::handle_t texture, glf::Texture::Parameter parameter, gl::float32_t value) -> gl::void_t
            {
                glTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(parameter), &value);
            };
        
        auto overload = gl::overload
        {
            [=](glp::compare_function     _) { texture_parameter_uiv(texture, glf::Texture::Parameter::CompareFunction    , gl::to_underlying(_.value)); }, 
            [=](glp::compare_mode         _) { texture_parameter_uiv(texture, glf::Texture::Parameter::CompareMode        , gl::to_underlying(_.value)); }, 
            [=](glp::base_level           _) { texture_parameter_uiv(texture, glf::Texture::Parameter::BaseLevel          ,                   _.value ); }, 
            [=](glp::maximum_level        _) { texture_parameter_uiv(texture, glf::Texture::Parameter::MaximumLevel       ,                   _.value ); }, 
            [=](glp::border_color         _)
            {
                auto overload = gl::overload
                {
                    [=](std::array<gl::int32_t  , 4u> __) { glTextureParameterIiv (gl::to_underlying(texture), gl::to_underlying(glf::Texture::Parameter::BorderColor), __.data()); }, 
                    [=](std::array<gl::uint32_t , 4u> __) { glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(glf::Texture::Parameter::BorderColor), __.data()); }, 
                    [=](std::array<gl::float32_t, 4u> __) { glTextureParameterfv  (gl::to_underlying(texture), gl::to_underlying(glf::Texture::Parameter::BorderColor), __.data()); }, 
                };

                std::visit(overload, _.value);
            }, 
            [=](glp::depth_stencil_mode   _) { texture_parameter_uiv(texture, glf::Texture::Parameter::DepthStencilMode   , gl::to_underlying(_.value)); }, 
            [=](glp::magnification_filter _) { texture_parameter_uiv(texture, glf::Texture::Parameter::MagnificationFilter, gl::to_underlying(_.value)); }, 
            [=](glp::minification_filter  _) { texture_parameter_uiv(texture, glf::Texture::Parameter::MinificationFilter , gl::to_underlying(_.value)); }, 
            [=](glp::maximum_anisotropy   _) { texture_parameter_fv (texture, glf::Texture::Parameter::MaximumAnisotropy  ,                   _.value ); }, 
            [=](glp::wrapping_s           _) { texture_parameter_uiv(texture, glf::Texture::Parameter::WrappingS          , gl::to_underlying(_.value)); }, 
            [=](glp::wrapping_t           _) { texture_parameter_uiv(texture, glf::Texture::Parameter::WrappingT          , gl::to_underlying(_.value)); }, 
            [=](glp::wrapping_r           _) { texture_parameter_uiv(texture, glf::Texture::Parameter::WrappingR          , gl::to_underlying(_.value)); }, 
            [=](glp::swizzle_r            _) { texture_parameter_uiv(texture, glf::Texture::Parameter::SwizzleRed         , gl::to_underlying(_.value)); }, 
            [=](glp::swizzle_g            _) { texture_parameter_uiv(texture, glf::Texture::Parameter::SwizzleGreen       , gl::to_underlying(_.value)); }, 
            [=](glp::swizzle_b            _) { texture_parameter_uiv(texture, glf::Texture::Parameter::SwizzleBlue        , gl::to_underlying(_.value)); }, 
            [=](glp::swizzle_a            _) { texture_parameter_uiv(texture, glf::Texture::Parameter::SwizzleAlpha       , gl::to_underlying(_.value)); }, 
            [=](glp::swizzle_rgba         _) { glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(glf::Texture::Parameter::SwizzleRGBA), gl::to_underlying_ptr(_.value.data())); }, 
            [=](glp::maximum_lod          _) { texture_parameter_fv (texture, glf::Texture::Parameter::MaximumLOD         ,                   _.value ); }, 
            [=](glp::minimum_lod          _) { texture_parameter_fv (texture, glf::Texture::Parameter::MinimumLOD         ,                   _.value ); }, 
            [=](glp::lod_bias             _) { texture_parameter_fv (texture, glf::Texture::Parameter::LODBias            ,                   _.value ); }, 
        };

        std::visit(overload, parameter);
    }
    inline void generate_texture_mipmap                    (gl::handle_t texture)
    {
        glGenerateTextureMipmap(gl::to_underlying(texture));
    }
    template<glf::Texture::Target T, glf::Texture::Target U> requires (valid_texture_view_c<T, U>)
    inline void texture_view                               (gl::handle_t source, gl::handle_t destination, glf::Texture::Format format, gl::uint32_t minimumLevel, gl::uint32_t levels, gl::uint32_t minimumLayer, gl::uint32_t layers)
    {
        glTextureView(gl::to_underlying(destination), gl::to_underlying(U), gl::to_underlying(source), gl::to_underlying(format), minimumLevel, levels, minimumLayer, layers);
    }
    inline void texture_storage_1d                         (gl::handle_t texture, glf::Texture::Format format, const gl::Vector1u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage1D(
            gl::to_underlying       (texture)      , 
            static_cast<gl::sizei_t>(levels)       , 
            gl::to_underlying       (format)       , 
            static_cast<gl::sizei_t>(dimensions.x));
    }
    inline void texture_storage_2d                         (gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage2D(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(levels)      , 
            gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    inline void texture_storage_3d                         (gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage3D(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(levels)      , 
            gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z));
    }
    inline void texture_storage_2d_multisample             (gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage2DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), 
            fixed);
    }
    inline void texture_storage_3d_multisample             (gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage3DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z), 
            fixed);
    }
    inline void invalidate_texture_image                   (gl::handle_t texture, gl::uint32_t level)
    {
        glInvalidateTexImage(
            gl::to_underlying       (texture), 
            static_cast<gl::int32_t>(level) );
    }
    inline void invalidate_texture_sub_image               (gl::handle_t texture, gl::uint32_t level, gl::volume_t region)
    {
        glInvalidateTexSubImage(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z) , 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z));
    }
    inline void clear_texture_image                        (gl::handle_t texture, glf::Texture::BaseFormat format, glf::Texture::Type type, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glClearTexImage(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level), 
            gl::to_underlying(format) , gl::to_underlying       (type) , data.data());
    }
    inline void clear_texture_sub_image                    (gl::handle_t texture, glf::Texture::BaseFormat format, glf::Texture::Type type, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glClearTexSubImage(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , gl::to_underlying       (type)           , data.data());
    }



    //Chapter 9 - FrameBuffers and FrameBuffer Objects
    inline auto create_frame_buffer                        () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    inline auto create_frame_buffer                        (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateFramebuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    inline void delete_frame_buffer                        (gl::handle_t frameBuffer)
    {
        glDeleteFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&frameBuffer));
    }
    inline void delete_frame_buffers                       (std::span<const gl::handle_t> frameBuffers)
    {
        glDeleteFramebuffers(static_cast<gl::sizei_t>(frameBuffers.size()), gl::to_underlying_ptr(frameBuffers.data()));
    }
    inline void bind_frame_buffer                          (gl::handle_t frameBuffer, glf::FrameBuffer::Target target)
    {
        glBindFramebuffer(gl::to_underlying(target), gl::to_underlying(frameBuffer));
    }
    template<glf::FrameBuffer::Parameter P>
    inline void frame_buffer_parameter                     (gl::handle_t frameBuffer, gl::uint32_t value)
    {
        auto frame_buffer_parameter_i = [](gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter, gl::uint32_t value) -> gl::void_t
            {
                glNamedFramebufferParameteri(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
            };

        if constexpr (
               P == glf::FrameBuffer::Parameter::DefaultWidth               
            or P == glf::FrameBuffer::Parameter::DefaultHeight              
            or P == glf::FrameBuffer::Parameter::DefaultLayers              
            or P == glf::FrameBuffer::Parameter::DefaultSamples             
            or P == glf::FrameBuffer::Parameter::DefaultFixedSampleLocations
            or P == glf::FrameBuffer::Parameter::DefaultWidth               ) frame_buffer_parameter_i(frameBuffer, P, value);
        else static_assert(gl::False, "Invalid FrameBuffer Parameter!");
    }
    inline auto create_render_buffer                       () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    inline auto create_render_buffers                      (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateRenderbuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    inline void delete_render_buffer                       (gl::handle_t renderBuffer)
    {
        glDeleteRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&renderBuffer));
    }
    inline void delete_render_buffers                      (std::span<const gl::handle_t> renderBuffers)
    {
        glDeleteRenderbuffers(static_cast<gl::sizei_t>(renderBuffers.size()), gl::to_underlying_ptr(renderBuffers.data()));
    }
    inline void render_buffer_storage                      (gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(
            gl::to_underlying       (renderBuffer),
            gl::to_underlying       (format)      ,
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    inline void render_buffer_storage_multisample          (gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions, gl::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(
            gl::to_underlying       (renderBuffer),
            static_cast<gl::sizei_t>(samples)     ,
            gl::to_underlying       (format)      ,
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    inline void frame_buffer_render_buffer                 (gl::handle_t frameBuffer, gl::handle_t renderBuffer, glf::FrameBuffer::Attachment attachment)
    {
        glNamedFramebufferRenderbuffer(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(glf::RenderBuffer::Target::RenderBuffer), gl::to_underlying(renderBuffer));
    }
    inline void frame_buffer_texture                       (gl::handle_t frameBuffer, gl::handle_t texture, glf::FrameBuffer::Attachment attachment, gl::uint32_t level)
    {
        glNamedFramebufferTexture(
            gl::to_underlying       (frameBuffer), gl::to_underlying(attachment), 
            gl::to_underlying       (texture)    , 
            static_cast<gl::int32_t>(level)     );
    }
    inline void frame_buffer_texture_layer                 (gl::handle_t frameBuffer, gl::handle_t texture, glf::FrameBuffer::Attachment attachment, gl::uint32_t level, gl::uint32_t layer)
    {
        glNamedFramebufferTextureLayer(
            gl::to_underlying       (frameBuffer), gl::to_underlying       (attachment), 
            gl::to_underlying       (texture)    , 
            static_cast<gl::int32_t>(level)      , static_cast<gl::int32_t>(layer)    );
    }
    inline void texture_barrier                            ()
    {
        glTextureBarrier();
    }
    inline auto check_frame_buffer_status                  (gl::handle_t frameBuffer) -> glf::FrameBuffer::Status
    {
        return static_cast<glf::FrameBuffer::Status>(glCheckNamedFramebufferStatus(gl::to_underlying(frameBuffer), gl::to_underlying(glf::FrameBuffer::Target::Write)));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    inline void patch_parameter                            (glp::patch_parameter_v parameter)
    {
        auto patch_parameter_i = [](glf::Patch::Parameter parameter, gl::int32_t   value)
            {
                glPatchParameteri(gl::to_underlying(parameter), value);
            };
        auto patch_parameter_f = [](glf::Patch::Parameter parameter, gl::float32_t value)
            {
                glPatchParameterfv(gl::to_underlying(parameter), &value);
            };

        auto overload = gl::overload
        {
            [=](glp::patch_vertices            _) { patch_parameter_i (                  glf::Patch::Parameter::PatchVertices          , _.value)       ; }, 
            [=](glp::patch_default_outer_level _) { glPatchParameterfv(gl::to_underlying(glf::Patch::Parameter::PatchDefaultOuterLevel), _.value.data()); }, 
            [=](glp::patch_default_inner_level _) { glPatchParameterfv(gl::to_underlying(glf::Patch::Parameter::PatchDefaultInnerLevel), _.value.data()); }, 
        };

        std::visit(overload, parameter);
    }
    template<typename T, gl::uint32_t N, gl::bool_t NORM = gl::False>
    inline void vertex_attribute                           (gl::index_t index, const gl::Vector<T, N>& value)
    {
        auto maximumAttributes = gl::get_value<glf::Data::MaximumVertexAttributes>();
        if (gl::compare<std::greater>(index, maximumAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };
        
        if   constexpr (std::is_same_v<T, gl::uint8_t  >)
        {
            if constexpr (N == 4 and NORM == gl::True ) glVertexAttrib4Nub(index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::int16_t  >)
        {
            if constexpr (N == 1 and NORM == gl::False) glVertexAttrib1s  (index, value.x                           );
            if constexpr (N == 2 and NORM == gl::False) glVertexAttrib2s  (index, value.x, value.y                  );
            if constexpr (N == 3 and NORM == gl::False) glVertexAttrib3s  (index, value.x, value.y, value.z         );
            if constexpr (N == 4 and NORM == gl::False) glVertexAttrib4s  (index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::int32_t  >)
        {
            if constexpr (N == 1 and NORM == gl::False) glVertexAttribI1i (index, value.x                           );
            if constexpr (N == 2 and NORM == gl::False) glVertexAttribI2i (index, value.x, value.y                  );
            if constexpr (N == 3 and NORM == gl::False) glVertexAttribI3i (index, value.x, value.y, value.z         );
            if constexpr (N == 4 and NORM == gl::False) glVertexAttribI4i (index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::uint32_t >)
        {
            if constexpr (N == 1 and NORM == gl::False) glVertexAttribI1ui(index, value.x                           );
            if constexpr (N == 2 and NORM == gl::False) glVertexAttribI2ui(index, value.x, value.y                  );
            if constexpr (N == 3 and NORM == gl::False) glVertexAttribI3ui(index, value.x, value.y, value.z         );
            if constexpr (N == 4 and NORM == gl::False) glVertexAttribI4ui(index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::float32_t>)
        {
            if constexpr (N == 1 and NORM == gl::False) glVertexAttrib1f  (index, value.x                           );
            if constexpr (N == 2 and NORM == gl::False) glVertexAttrib2f  (index, value.x, value.y                  );
            if constexpr (N == 3 and NORM == gl::False) glVertexAttrib3f  (index, value.x, value.y, value.z         );
            if constexpr (N == 4 and NORM == gl::False) glVertexAttrib4f  (index, value.x, value.y, value.z, value.w);
        }
        if   constexpr (std::is_same_v<T, gl::float64_t>)
        {
            if constexpr (N == 1 and NORM == gl::False) glVertexAttribL1d (index, value.x                           );
            if constexpr (N == 2 and NORM == gl::False) glVertexAttribL2d (index, value.x, value.y                  );
            if constexpr (N == 3 and NORM == gl::False) glVertexAttribL3d (index, value.x, value.y, value.z         );
            if constexpr (N == 4 and NORM == gl::False) glVertexAttribL4d (index, value.x, value.y, value.z, value.w);
        }
        else static_assert(gl::False, "The given input does not match a valid vertex attribute function!");
    }
    inline auto create_vertex_array                        () -> gl::handle_t
    {
        auto handle = gl::handle_t{};
        return glCreateVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle)), handle;
    }
    inline auto create_vertex_arrays                       (gl::count_t count) -> std::vector<gl::handle_t>
    {
        auto handles = std::vector<gl::handle_t>(count);
        return glCreateVertexArrays(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data())), handles;
    }
    inline void delete_vertex_array                        (gl::handle_t vertexArray)
    {
        glDeleteVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&vertexArray));
    }
    inline void delete_vertex_arrays                       (std::span<const gl::handle_t> vertexArrays)
    {
        glDeleteVertexArrays(static_cast<gl::sizei_t>(vertexArrays.size()), gl::to_underlying_ptr(vertexArrays.data()));
    }
    inline void bind_vertex_array                          (gl::handle_t vertexArray)
    {
        glBindVertexArray(gl::to_underlying(vertexArray));
    }
    inline void vertex_array_element_buffer                (gl::handle_t vertexArray, gl::handle_t elementBuffer)
    {
        glVertexArrayElementBuffer(gl::to_underlying(vertexArray), gl::to_underlying(elementBuffer));
    }
    inline void vertex_array_attribute_format              (gl::handle_t vertexArray, gl::index_t attribute, gl::offset_t offset, glf::VertexArray::Attribute::Type type, gl::count_t count, gl::bool_t normalized = gl::False)
    {
        auto vertex_array_attribute_format_i = [](gl::handle_t vertexArray, gl::index_t attribute, glf::VertexArray::Attribute::Type type, gl::count_t count, gl::offset_t offset) -> gl::void_t
            {
                glVertexArrayAttribIFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
            };
        auto vertex_array_attribute_format_f = [](gl::handle_t vertexArray, gl::index_t attribute, glf::VertexArray::Attribute::Type type, gl::count_t count, gl::offset_t offset, gl::bool_t normalized)
            {
                glVertexArrayAttribFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), normalized, static_cast<gl::uint32_t>(offset));
            };
        auto vertex_array_attribute_format_l = [](gl::handle_t vertexArray, gl::index_t attribute, glf::VertexArray::Attribute::Type type, gl::count_t count, gl::offset_t offset)
            {
                glVertexArrayAttribLFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
            };

        auto maximumVertexAttributes = gl::get_value<glf::Data::MaximumVertexAttributes>();
        if (gl::compare<std::greater>(attribute, maximumVertexAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };

        switch (type)
        {
            case glf::VertexArray::Attribute::Type::Byte                                 : 
            case glf::VertexArray::Attribute::Type::UnsignedByte                         : 
            case glf::VertexArray::Attribute::Type::Short                                : 
            case glf::VertexArray::Attribute::Type::UnsignedShort                        : 
            case glf::VertexArray::Attribute::Type::Integer                              : 
            case glf::VertexArray::Attribute::Type::UnsignedInteger                      : 
            case glf::VertexArray::Attribute::Type::Int_2_10_10_10_Rev                   : 
            case glf::VertexArray::Attribute::Type::UnsignedInteger_2_10_10_10_Rev       : 
            case glf::VertexArray::Attribute::Type::UnsignedInteger_10_11_11_11_Float_Rev:
            {
                vertex_array_attribute_format_i(vertexArray, attribute, type, count, offset);
                break;
            }

            case glf::VertexArray::Attribute::Type::Float                                : 
            case glf::VertexArray::Attribute::Type::HalfFloat                            : 
            case glf::VertexArray::Attribute::Type::Fixed                                : 
            {
                vertex_array_attribute_format_f(vertexArray, attribute, type, count, offset, normalized);
                break;
            }

            case glf::VertexArray::Attribute::Type::Double                               : 
            {
                vertex_array_attribute_format_l(vertexArray, attribute, type, count, offset);
                break;
            }
        }
    }
    inline void vertex_array_vertex_buffer                 (gl::handle_t vertexArray, gl::handle_t buffer, gl::binding_t binding, gl::size_t stride, gl::index_t index)
    {
        glVertexArrayVertexBuffer(gl::to_underlying(vertexArray), gl::to_underlying(binding), gl::to_underlying(buffer), static_cast<gl::offset_t>(index), static_cast<gl::sizei_t>(stride));
    }
    inline void vertex_array_vertex_buffers                (gl::handle_t vertexArray, std::span<const gl::handle_t> buffers, std::span<const gl::byterange_t> strides, gl::range_t range)
    {
        gl::todo();
        //glVertexArrayVertexBuffers(gl::to_underlying(vertexArray), range.index, range.count, gl::to_underlying_ptr(buffers.data()), );
    }
    inline void vertex_array_attribute_binding             (gl::handle_t vertexArray, gl::index_t attribute, gl::binding_t binding)
    {
        glVertexArrayAttribBinding(gl::to_underlying(vertexArray), attribute, gl::to_underlying(binding));
    }
    inline void enable_vertex_array_attribute              (gl::handle_t vertexArray, gl::index_t index)
    {
        glEnableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }
    inline void disable_vertex_array_attribute             (gl::handle_t vertexArray, gl::index_t index)
    {
        glDisableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }
    inline void vertex_array_binding_divisor               (gl::handle_t vertexArray, gl::binding_t binding, gl::uint32_t divisor)
    {
        glVertexArrayBindingDivisor(gl::to_underlying(vertexArray), gl::to_underlying(binding), divisor);
    }
    inline void primitive_restart_index                    (gl::index_t index)
    {
        glPrimitiveRestartIndex(index);
    }
    inline void draw_arrays                                (glf::Draw::Mode mode, gl::range_t range)
    {
        glDrawArrays(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count));
    }
    inline void draw_arrays_instanced                      (glf::Draw::Mode mode, gl::range_t range, gl::count_t instances)
    {
        glDrawArraysInstanced(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count), static_cast<gl::sizei_t>(instances));
    }
    inline void draw_arrays_instanced_base_instance        (glf::Draw::Mode mode, gl::range_t range, gl::count_t instances, gl::index_t base)
    {
        glDrawArraysInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count), static_cast<gl::sizei_t>(instances), base);
    }
    inline void draw_elements                              (glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count)
    {
        glDrawElements(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr);
    }
    inline void draw_elements_instanced                    (glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count, gl::count_t instances)
    {
        glDrawElementsInstanced(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instances));
    }
    inline void draw_elements_instanced_base_instance      (glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count, gl::count_t instances, gl::index_t base)
    {
        glDrawElementsInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instances), base);
    }
    inline void begin_conditional_render                   (gl::handle_t query, glf::Query::Mode mode)
    {
        glBeginConditionalRender(gl::to_underlying(query), gl::to_underlying(mode));
    }
    inline void end_conditional_render                     ()
    {
        glEndConditionalRender();
    }



    //Chapter 11 - Programmable Vertex Processing
    inline void validate_program                           (gl::handle_t program)
    {
        glValidateProgram(gl::to_underlying(program));
    }
    inline void validate_program_pipeline                  (gl::handle_t pipeline)
    {
        glValidateProgramPipeline(gl::to_underlying(pipeline));
    }



    //Chapter 13 - Fixed-Function Vertex Post-Processing
    inline void provoking_vertex                           (glf::ProvokingVertex::Mode mode)
    {
        glProvokingVertex(gl::to_underlying(mode));
    }
    inline void clip_control                               (glf::Clip::Origin origin, glf::Clip::DepthMode mode)
    {
        glClipControl(gl::to_underlying(origin), gl::to_underlying(mode));
    }
    inline void depth_range_array_value                    (gl::index_t index, std::span<const gl::Vector2d> ranges)
    {
        glDepthRangeArrayv(index, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    inline void depth_range_indexed                        (gl::index_t index, const gl::Vector2d& range)
    {
        glDepthRangeIndexed(index, range.x, range.y);
    }
    inline void depth_range                                (const gl::Vector2f& range)
    {
        glDepthRangef(range.x, range.y);
    }
    inline void viewport_array_value                       (gl::index_t index, std::span<const gl::Vector2f> ranges)
    {
        glViewportArrayv(index, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    inline void viewport_indexed                           (gl::index_t index, const gl::region_t<gl::float32_t, 2u> region)
    {
        glViewportIndexedf(index, region.origin.x, region.origin.y, region.extent.x, region.extent.y);
    }
    inline void viewport                                   (gl::area_t region)
    {
        glViewport(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }



    //Chapter 14 - Fixed-Function Primitive Assembly and Rasterization
    inline auto get_multisample_value                      (gl::index_t index) -> gl::Vector2f
    {
        auto value = gl::Vector2f{};
        return glGetMultisamplefv(gl::to_underlying(glf::Multisample::Parameter::SamplePosition), index, glm::value_ptr(value)), value;
    }
    inline void minimum_sample_shading                     (gl::float32_t value)
    {
        glMinSampleShading(value);
    }
    inline void point_size                                 (gl::float32_t size)
    {
        glPointSize(size);
    }
    inline void point_parameter                            (glp::point_parameter_v parameter)
    {
        auto point_parameter_i = [](glf::Point::Parameter parameter, gl::int32_t value) -> gl::void_t
            {
                glPointParameteri(gl::to_underlying(parameter), value);
            };
        auto point_parameter_f = [](glf::Point::Parameter parameter, gl::float32_t value) -> gl::void_t
            {
                glPointParameterf(gl::to_underlying(parameter), value);
            };

        auto overload = gl::overload
        {
            [=](glp::fade_threshold_size      _) { point_parameter_f(glf::Point::Parameter::FadeThresholdSize     ,                   _.value ); }, 
            [=](glp::sprite_coordinate_origin _) { point_parameter_i(glf::Point::Parameter::SpriteCoordinateOrigin, gl::to_underlying(_.value)); }, 
        };

        std::visit(overload, parameter);
    }
    inline void line_width                                 (gl::float32_t value)
    {
        glLineWidth(value);
    }
    inline void front_face                                 (glf::Orientation orientation)
    {
        glFrontFace(gl::to_underlying(orientation));
    }
    inline void cull_face                                  (glf::Culling::Facet face)
    {
        glCullFace(gl::to_underlying(face));
    }
    inline void polygon_mode                               (glf::Polygon::Mode mode)
    {
        glPolygonMode(gl::to_underlying(glf::Polygon::Face::FrontAndBack), gl::to_underlying(mode));
    }
    inline void polygon_offset_clamp                       (gl::float32_t factor, gl::float32_t units, gl::float32_t clamp)
    {
        glPolygonOffsetClamp(factor, units, clamp);
    }
    inline void scissor_array                              (gl::index_t index, std::span<const gl::uint32_t, 4u> values)
    {
        glScissorArrayv(
            index                                            , 
            static_cast<gl::sizei_t>         (values.size()) , 
            std::bit_cast<const gl::int32_t*>(values.data())); 
    }
    inline void scissor_indexed                            (gl::index_t index, gl::area_t region)
    {
        glScissorIndexed(
            index                                                                                , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y) ,  
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    inline void scissor                                    (gl::area_t region)
    {
        glScissor(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y) , 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    inline void sample_coverage                            (gl::float32_t value, gl::bool_t invert)
    {
        glSampleCoverage(value, invert);
    }
    inline void sample_mask_index                          (gl::uint32_t mask, gl::uint32_t value)
    {
        glSampleMaski(mask, value);
    }



    //Chapter 17 - Writing Fragments and Samples to the Framebuffer
    inline void stencil_function                           (glf::Stencil::Function function, gl::uint32_t reference, gl::uint32_t mask)
    {
        glStencilFunc(gl::to_underlying(function), static_cast<gl::int32_t>(reference), mask);
    }
    inline void stencil_function_separate                  (glf::Stencil::Face face, glf::Stencil::Function function, gl::uint32_t reference, gl::uint32_t mask)
    {
        glStencilFuncSeparate(gl::to_underlying(face), gl::to_underlying(function), static_cast<gl::int32_t>(reference), mask);
    }
    inline void stencil_operation                          (glf::Stencil::Action stencil, glf::Stencil::Action depth, glf::Stencil::Action depthStencil)
    {
        glStencilOp(gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }
    inline void stencil_operation_separate                 (glf::Stencil::Face face, glf::Stencil::Action stencil, glf::Stencil::Action depth, glf::Stencil::Action depthStencil)
    {
        glStencilOpSeparate(gl::to_underlying(face), gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }
    inline void depth_function                             (glf::DepthFunction function)
    {
        glDepthFunc(gl::to_underlying(function));
    }
    inline void blend_equation                             (glf::Blending::Equation equation)
    {
        glBlendEquation(gl::to_underlying(equation));
    }
    inline void blend_equation_indexed                     (glf::Blending::Equation equation, gl::index_t index)
    {
        glBlendEquationi(index, gl::to_underlying(equation));
    }
    inline void blend_equation_separate                    (glf::Blending::Equation equationRGB, glf::Blending::Equation equationAlpha)
    {
        glBlendEquationSeparate(gl::to_underlying(equationRGB), gl::to_underlying(equationAlpha));
    }
    inline void blend_equation_separate_indexed            (glf::Blending::Equation color, glf::Blending::Equation alpha, gl::index_t index)
    {
        glBlendEquationSeparatei(index, gl::to_underlying(color), gl::to_underlying(alpha));
    }
    inline void blend_function                             (glf::Blending::Factor source, glf::Blending::Factor destination)
    {
        glBlendFunc(gl::to_underlying(source), gl::to_underlying(destination));
    }
    inline void blend_function_indexed                     (glf::Blending::Factor sourceColor, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationColor, glf::Blending::Factor destinationAlpha, gl::index_t index)
    {
        glBlendFuncSeparatei(index, gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    inline void blend_function_separate                    (glf::Blending::Factor sourceColor, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationColor, glf::Blending::Factor destinationAlpha)
    {
        glBlendFuncSeparate(gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    inline void blend_function_separate_indexed            (glf::Blending::Factor sourceColor, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationColor, glf::Blending::Factor destinationAlpha, gl::index_t index)
    {
        glBlendFuncSeparatei(index, gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    inline void blend_color                                (const gl::Vector4f& color)
    {
        glBlendColor(color.r, color.g, color.b, color.a);
    }
    inline void logical_pixel_operation                    (glf::LogicalPixelOperation operation)
    {
        glLogicOp(gl::to_underlying(operation));
    }
    inline void frame_buffer_draw_buffer                   (gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferDrawBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    inline void frame_buffer_draw_buffers                  (gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Source> sources)
    {
        glNamedFramebufferDrawBuffers(gl::to_underlying(frameBuffer), static_cast<gl::sizei_t>(sources.size()), gl::to_underlying_ptr(sources.data()));
    }
    inline void color_mask                                 (const gl::Vector4b& mask)
    {
        glColorMask(mask.r, mask.g, mask.b, mask.a);
    }
    inline void color_mask_index                           (gl::handle_t buffer, const gl::Vector4b& mask)
    {
        glColorMaski(gl::to_underlying(buffer), mask.r, mask.g, mask.b, mask.a);
    }
    inline void depth_mask                                 (gl::bool_t flag)
    {
        glDepthMask(flag);
    }
    inline void stencil_mask                               (gl::uint32_t mask)
    {
        glStencilMask(mask);
    }
    inline void stencil_mask_separate                      (glf::Stencil::Face face, gl::uint32_t mask)
    {
        glStencilMaskSeparate(gl::to_underlying(face), mask);
    }
    inline void clear                                      (glf::Buffer::Mask mask)
    {
        glClear(gl::to_underlying(mask));
    }
    inline void clear_color                                (const gl::Vector4f& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    inline void clear_depth                                (gl::float32_t depth)
    {
        glClearDepthf(depth);
    }
    inline void clear_stencil                              (gl::index_t index)
    {
        glClearStencil(static_cast<gl::int32_t>(index));
    }
    inline void clear_frame_buffer_value                   (gl::handle_t frameBuffer, glp::clear_v parameter, gl::index_t index)
    {
        auto clear_frame_buffer_iv  = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::index_t index, const gl::int32_t* value)
            {
                glClearNamedFramebufferiv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_uiv = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::index_t index, const gl::uint32_t* value)
            {
                glClearNamedFramebufferuiv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_fv  = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::index_t index, const gl::float32_t* value)
            {
                glClearNamedFramebufferfv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        auto clear_frame_buffer_fi  = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::index_t index, gl::float32_t depth, gl::int32_t stencil)
            {
                glClearNamedFramebufferfi(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), depth, stencil);
            };

        auto overload = gl::overload
        {
            [=](glp::color_index  _)
            {
                auto overload = gl::overload
                {
                    [=](gl::Vector4i __) { clear_frame_buffer_iv (frameBuffer, glf::FrameBuffer::Attachment::Color0, _.index, glm::value_ptr(__)); }, 
                    [=](gl::Vector4u __) { clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::Color0, _.index, glm::value_ptr(__)); }, 
                    [=](gl::Vector4f __) { clear_frame_buffer_fv (frameBuffer, glf::FrameBuffer::Attachment::Color0, _.index, glm::value_ptr(__)); }, 
                };

                std::visit(overload, _.color);
            }, 
            [=](glp::depth        _)
            {
                auto overload = gl::overload
                {
                    [=](gl::int32_t   __) { clear_frame_buffer_iv (frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &__); }, 
                    [=](gl::uint32_t  __) { clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &__); }, 
                    [=](gl::float32_t __) { clear_frame_buffer_fv (frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &__); }, 
                };

                std::visit(overload, _.value);
            }, 
            [=](glp::stencil      _)
            {
                auto overload = gl::overload
                {
                    [=](gl::int32_t   __) { clear_frame_buffer_iv (frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &__); }, 
                    [=](gl::uint32_t  __) { clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &__); }, 
                    [=](gl::float32_t __) { clear_frame_buffer_fv (frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &__); }, 
                };

                std::visit(overload, _.value);
            },
            [=](glp::depthstencil _)
            {
                clear_frame_buffer_fi(frameBuffer, glf::FrameBuffer::Attachment::DepthStencil, gl::uint32_t{ 0u }, _.depth, _.stencil);
            }, 
        };

        std::visit(overload, parameter);
    }
    inline void invalidate_frame_buffer_data               (gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Attachment> attachments)
    {
        glInvalidateNamedFramebufferData(
            gl::to_underlying       (frameBuffer)        , 
            static_cast<gl::sizei_t>(attachments.size()) , 
            gl::to_underlying_ptr   (attachments.data()));
    }
    inline void invalidate_frame_buffer_sub_data           (gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Attachment> attachments, gl::area_t region)
    {
        glInvalidateNamedFramebufferSubData(
            gl::to_underlying       (frameBuffer)       , 
            static_cast<gl::sizei_t>(attachments.size()), gl::to_underlying_ptr   (attachments.data()), 
            static_cast<gl::int32_t>(region.origin.x)   , static_cast<gl::int32_t>(region.origin.y)   , 
            static_cast<gl::sizei_t>(region.extent.x)   , static_cast<gl::sizei_t>(region.extent.y)  );
    }



    //Chapter 18 - Reading and Copying Pixels
    inline void frame_buffer_read_buffer                   (gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferReadBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    template<glf::PixelData::Format F, glf::PixelData::Type T>
    inline void read_pixels                                (gl::area_t region)
    {
        gl::todo();

        //const auto& map_format_size = []<glf::PixelData::Format F>() constexpr
        //    {
        //        if (F == glf::PixelData::Format::R             ) return 0;
        //        if (F == glf::PixelData::Format::G             ) return 0;
        //        if (F == glf::PixelData::Format::B             ) return 0;
        //        if (F == glf::PixelData::Format::RGB           ) return 0;
        //        if (F == glf::PixelData::Format::RGBA          ) return 0;
        //        if (F == glf::PixelData::Format::BGR           ) return 0;
        //        if (F == glf::PixelData::Format::BGRA          ) return 0;
        //        if (F == glf::PixelData::Format::StencilIndex  ) return 0;
        //        if (F == glf::PixelData::Format::DepthComponent) return 0;
        //        if (F == glf::PixelData::Format::DepthStencil  ) return 0;
        //    };

        //const auto& binding = gl::get_value<glf::Data::PixelPackBufferBinding>();

        //if (binding == gl::NullObject)
        //{
        //    const auto& size = region.extent.x * region.extent.y;
        //    std::vector<T> value(size);

        //    glReadnPixels(
        //        static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
        //        static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
        //        gl::to_underlying       (format)         , gl::to_underlying       (type)           , 
        //        static_cast<gl::sizei_t>(value.size())   , 
        //        value.data());

        //    return value;
        //}
    }
    inline void clamp_color                                (gl::bool_t value)
    {
        glClampColor(gl::to_underlying(glf::ClampColor::Read), value);
    }
    inline void blit_frame_buffer                          (gl::handle_t source, gl::handle_t destination, glf::Buffer::Mask mask, glf::FrameBuffer::Filter filter, gl::area_t sourceRegion, gl::area_t destinationRegion)
    {
        glBlitNamedFramebuffer(
            gl::to_underlying       (source)                    ,
            gl::to_underlying       (destination)               ,
            static_cast<gl::int32_t>(sourceRegion     .origin.x), static_cast<gl::int32_t>(sourceRegion     .origin.y), static_cast<gl::int32_t>(sourceRegion     .extent.x), static_cast<gl::int32_t>(sourceRegion     .extent.y),
            static_cast<gl::int32_t>(destinationRegion.origin.x), static_cast<gl::int32_t>(destinationRegion.origin.y), static_cast<gl::int32_t>(destinationRegion.extent.x), static_cast<gl::int32_t>(destinationRegion.extent.y),
            gl::to_underlying       (mask)                      , gl::to_underlying       (filter)                   );
    }
    inline void copy_image_sub_data                        (gl::handle_t source, gl::handle_t destination, glf::Texture::Target sourceTarget, glf::Texture::Target destinationTarget, gl::hypervolume_t sourceRegion, gl::hypervolume_t destinationRegion)
    {
        glCopyImageSubData(
            gl::to_underlying       (source                    ), gl::to_underlying       (sourceTarget              ), static_cast<gl::int32_t>(sourceRegion     .extent.w), 
            static_cast<gl::int32_t>(sourceRegion     .origin.x), static_cast<gl::int32_t>(sourceRegion     .origin.y), static_cast<gl::int32_t>(sourceRegion     .origin.z), 
            gl::to_underlying       (destination               ), gl::to_underlying       (destinationTarget         ), static_cast<gl::int32_t>(destinationRegion.extent.w), 
            static_cast<gl::int32_t>(destinationRegion.origin.x), static_cast<gl::int32_t>(destinationRegion.origin.y), static_cast<gl::int32_t>(destinationRegion.origin.z), 
            static_cast<gl::sizei_t>(sourceRegion     .extent.x), static_cast<gl::sizei_t>(sourceRegion     .extent.y), static_cast<gl::sizei_t>(sourceRegion     .extent.z));
    }



    //Chapter 19 - Compute Shaders
    inline void dispatch_compute                           (glp::dispatch_v parameter)
    {
        auto overload = gl::overload
        {
            [=](gl::Vector3u _) { glDispatchCompute        (_.x, _.y, _.z); }, 
            [=](gl::offset_t _) { glDispatchComputeIndirect(_            ); }, 
        };
        
        std::visit(overload, parameter);
    }



    //Chapter 20 - Debug Output
    inline void debug_message_callback                     (gl::debug_callback_t callback, const gl::pointer_t parameter = nullptr)
    {
        glDebugMessageCallback(callback, parameter);
    }
    inline void debug_message_control                      (glf::Debug::Source source, glf::Debug::Type type, glf::Debug::Severity severity, gl::bool_t state)
    {
        glDebugMessageControl(gl::to_underlying(source), gl::to_underlying(type), gl::to_underlying(severity), gl::sizei_t{ 0 }, nullptr, state);
    }
    inline void debug_message_insert                       (gl::handle_t identifier, glf::Debug::Type type, glf::Debug::Severity severity, const std::string& message)
    {
        glDebugMessageInsert(
            gl::to_underlying(glf::Debug::Source::Application), 
            gl::to_underlying(type)                           , gl::to_underlying(identifier), gl::to_underlying(severity),
            static_cast<gl::sizei_t>(message.length())        , message.data()              );
    }
    inline void push_debug_group                           (gl::handle_t identifier, const std::string& message)
    {
        const auto* cstr = message.c_str();
        glPushDebugGroup(gl::to_underlying(glf::Debug::Source::Application), gl::to_underlying(identifier), gl::sizei_t{ -1 }, cstr);
    }
    inline void pop_debug_group                            ()
    {
        glPopDebugGroup();
    }
    inline void object_label                               (gl::handle_t identifier, glf::Object::Type type, const std::string& label)
    {
        const auto* cstr = label.c_str();
        glObjectLabel(gl::to_underlying(type), gl::to_underlying(identifier), gl::sizei_t{ -1 }, cstr);
    }
    inline void object_pointer_label                       (gl::sync_t sync, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glObjectPtrLabel(sync, gl::sizei_t{ -1 }, cstr);
    }
    

    
    //Chapter 21 - Special Functions
    inline void hint                                       (glf::Hint::Target target, glf::Hint::Mode mode)
    {
        glHint(gl::to_underlying(target), gl::to_underlying(mode));
    }


    


#ifdef GL_EXTENDED
    inline namespace ext
    {

    }
#endif
#ifdef GL_LEGACY
    inline namespace lgc
    {
        inline auto get_error() -> glf::Error::Flag
        {
            return static_cast<glf::Error::Flag>(glGetError());
        }
        inline auto is_sync(gl::sync_t sync) -> gl::bool_t
        {
            return static_cast<gl::bool_t>(glIsSync(sync));
        }
    }
#endif
}
