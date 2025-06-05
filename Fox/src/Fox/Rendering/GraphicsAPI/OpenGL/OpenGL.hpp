#pragma once

#include "stdafx.hpp"

#include "Core/Concepts.hpp"
#include "Core/Data.hpp"
#include "Core/Flags.hpp"
#include "Core/Library.hpp"
#include "Core/Mapping.hpp"
#include "Core/Parameters.hpp"
#include "Core/Types.hpp"

namespace fox::gfx::api::gl
{
    //OpenGL wrapper library
    // 
    //This library has the following goals:
    //    * Provide a more modern, correct, and accessible interface
    //    * Wrap around existing OpenGL functions, allowing for easy addition of custom logic
    //    * Keep track of state, preventing redundant calls to the graphics driver
    //    * Compile/Runtime input validation and safety
    // 
    //Functions are ordered in accordance with their appearance in the OpenGL 4.6 core specification
    //https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf





    //Chapter 22 - Context State Queries
    template<glf::Data D> requires (not gl::indexed_data_c<D>)
    static auto get_value                               ()
    {
        const auto& get_boolean_v            = [](glf::Data data)
            {
                gl::bool_t value{};
                glGetBooleanv(gl::to_underlying(data), &value);

                return value;
            };
        const auto& get_integer32_v          = [](glf::Data data)
            {
                gl::int32_t value{};
                glGetIntegerv(gl::to_underlying(data), &value);

                return value;
            };
        const auto& get_integer64_v          = [](glf::Data data)
            {
                gl::int64_t value{};
                glGetInteger64v(gl::to_underlying(data), &value);

                return value;
            };
        const auto& get_unsigned_integer32_v = [](glf::Data data)
            {
                gl::int32_t value{};
                glGetIntegerv(gl::to_underlying(data), &value);

                return static_cast<gl::uint32_t>(value);
            };
        const auto& get_unsigned_integer64_v = [](glf::Data data)
            {
                gl::int64_t value{};
                glGetInteger64v(gl::to_underlying(data), &value);

                return static_cast<gl::uint64_t>(value);
            };
        const auto& get_floating_point32_v   = [](glf::Data data)
            {
                gl::float32_t value{};
                glGetFloatv(gl::to_underlying(data), &value);

                return value;
            };
        const auto& get_floating_point64_v   = [](glf::Data data)
            {
                gl::float64_t value{};
                glGetDoublev(gl::to_underlying(data), &value);

                return value;
            };

        const auto& get_vector4b_v           = [](glf::Data data)
            {
                gl::Vector4b value{};
                glGetBooleanv(gl::to_underlying(data), glm::value_ptr(value));

                return value;
            };
        const auto& get_vector2i_v           = [](glf::Data data)
            {
                gl::Vector2i value{};
                glGetIntegerv(gl::to_underlying(data), glm::value_ptr(value));

                return value;
            };
        const auto& get_vector2f_v           = [](glf::Data data)
            {
                gl::Vector2f value{};
                glGetFloatv(gl::to_underlying(data), glm::value_ptr(value));

                return value;
            };
        const auto& get_vector4f_v           = [](glf::Data data)
            {
                gl::Vector4f value{};
                glGetFloatv(gl::to_underlying(data), glm::value_ptr(value));

                return value;
            };

        const auto& get_handle_v             = [](glf::Data data)
            {
                gl::int32_t value{};
                glGetIntegerv(gl::to_underlying(data), &value);

                return static_cast<gl::handle_t>(value);
            };
        const auto& get_index_v              = [](glf::Data data)
            {
                gl::int32_t value{};
                glGetIntegerv(gl::to_underlying(data), &value);

                return static_cast<gl::index_t>(value);
            };
        const auto& get_bitfield_v           = [](glf::Data data)
            {
                gl::int32_t value{};
                glGetIntegerv(gl::to_underlying(data), &value);

                return static_cast<gl::bitfield_t>(value);
            };

        const auto& get_binary_formats_v     = [](glf::Data data)
            {
                gl::int32_t numberProgramBinaryFormats{};
                glGetIntegerv(gl::to_underlying(glf::Data::NumberProgramBinaryFormats), &numberProgramBinaryFormats);

                std::vector<gl::enum_t> programBinaryFormats(static_cast<std::uint32_t>(numberProgramBinaryFormats));
                glGetIntegerv(gl::to_underlying(data), reinterpret_cast<gl::int32_t*>(programBinaryFormats.data()));

                return programBinaryFormats;
            };
        const auto& get_area_v               = [](glf::Data data)
            {
                std::array<gl::uint32_t, 4> value{};
                glGetIntegerv(gl::to_underlying(data), reinterpret_cast<gl::int32_t*>(value.data()));

                struct result_t{ gl::area_t area{}; };
                return result_t{ gl::area_t{ gl::Vector2u{ value.at(2), value.at(3) }, gl::Vector2u{ value.at(0), value.at(1) } } };
            };



        if constexpr (D == glf::Data::AliasedLineWidthRange)                            return get_vector2f_v(D);
        if constexpr (D == glf::Data::BlendColor)                                       return get_vector4f_v(D);
        if constexpr (D == glf::Data::BlendDestinationAlpha)                            return glf::Blending::Factor{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::BlendDestinationRGB)                              return glf::Blending::Factor{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::BlendEquationAlpha)                               return glf::Blending::Equation{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::BlendEquationRGB)                                 return glf::Blending::Equation{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::BlendSourceAlpha)                                 return glf::Blending::Factor{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::BlendSourceRGB)                                   return glf::Blending::Factor{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::ColorClearValue)                                  return get_vector4f_v(D);
        if constexpr (D == glf::Data::ColorWriteMask)                                   return get_vector4b_v(D);
        if constexpr (D == glf::Data::ContextFlags)                                     return glf::Context::Flag{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::ContextProfileMask)                               return glf::Context::Profile{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::CopyReadBufferBinding)                            return get_handle_v(D);
        if constexpr (D == glf::Data::CopyWriteBufferBinding)                           return get_handle_v(D);
        if constexpr (D == glf::Data::CurrentProgram)                                   return get_handle_v(D);
        if constexpr (D == glf::Data::DebugGroupStackDepth)                             return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::DebugLoggedMessages)                              return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::DepthClearValue)                                  return get_floating_point64_v(D);
        if constexpr (D == glf::Data::DepthFunction)                                    return glf::DepthFunction{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::DepthRange)                                       return get_vector2f_v(D);
        if constexpr (D == glf::Data::DispatchIndirectBufferBinding)                    return get_handle_v(D);
        if constexpr (D == glf::Data::DoubleBuffer)                                     return get_boolean_v  (D);
        if constexpr (D == glf::Data::DrawBuffer)                                       return glf::FrameBuffer::Source{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::DrawFramebufferBinding)                           return get_handle_v(D);
        if constexpr (D == glf::Data::DrawIndirectBufferBinding)                        return get_handle_v(D);
        if constexpr (D == glf::Data::FragmentShaderDerivativeHint)                     return glf::Hint::Mode{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::ImplementationColorReadFormat)                    return glf::PixelData::Format{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::ImplementationColorReadType)                      return glf::PixelData::Type{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::IndexArrayBufferBinding)                          return get_handle_v(D);
        if constexpr (D == glf::Data::LayerProvokingVertex)                             return glf::ProvokingVertex::Mode{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::LineSmoothHint)                                   return glf::Hint::Mode{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::LineWidth)                                        return get_floating_point64_v(D);
        if constexpr (D == glf::Data::LogicOperationMode)                               return glf::LogicalPixelOperation{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::MajorVersion)                                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::Maximum3DTextureSize)                             return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumArrayTextureLayers)                        return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumClipDistances)                             return get_unsigned_integer32_v(D);
		if constexpr (D == glf::Data::MaximumColorAttachments)                          return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumColorTextureSamples)                       return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedAtomicCounters)                    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedComputeUniformComponents)          return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedFragmentUniformComponents)         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedGeometryUniformComponents)         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedShaderStorageBlocks)               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedTextureImageUnits)                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedUniformBlocks)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCombinedVertexUniformComponents)           return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeAtomicCounterBuffers)               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeAtomicCounters)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeShaderStorageBlocks)                return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeTextureImageUnits)                  return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeUniformBlocks)                      return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeUniformComponents)                  return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupCount)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupInvocations)               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupSize)                      return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumCubemapTextureSize)                        return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDebugGroupStackDepth)                      return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDebugMessageLength)                        return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDepthTextureSamples)                       return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDrawBuffers)                               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumDualSourceDrawBuffers)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumElementIndex)                              return get_index_v(D);
        if constexpr (D == glf::Data::MaximumFragmentAtomicCounters)                    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentInputComponents)                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentShaderStorageBlocks)               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentUniformBlocks)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentUniformComponents)                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFragmentUniformVectors)                    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFrameBufferHeight)                         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFrameBufferLayers)                         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFrameBufferSamples)                        return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumFrameBufferWidth)                          return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryAtomicCounters)                    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryInputComponents)                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryOutputComponents)                  return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryShaderStorageBlocks)               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryTextureImageUnits)                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryUniformBlocks)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumGeometryUniformComponents)                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumIndexElements)                             return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumIntegerSamples)                            return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumLabelLength)                               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumProgramTexelOffset)                        return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumRectangleTextureSize)                      return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumRenderBufferSize)                          return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumSampleMaskWords)                           return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumServerWaitTimeout)                         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumShaderStorageBufferBindings)               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTessellationControlAtomicCounters)         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTessellationControlShaderStorageBlocks)    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTessellationEvaluationAtomicCounters)      return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTessellationEvaluationShaderStorageBlocks) return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTextureBufferSize)                         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTextureImageUnits)                         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTextureLODBias)                            return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumTextureSize)                               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumUniformBlockSize)                          return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumUniformBufferBindings)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumUniformLocations)                          return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVaryingComponents)                         return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVaryingFloats)                             return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVaryingVectors)                            return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexAtomicCounters)                      return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexAttributeBindings)                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexAttributeRelativeOffset)             return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexAttributes)                          return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexElements)                            return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexOutputComponents)                    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexShaderStorageBlocks)                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexTextureImageUnits)                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexUniformBlocks)                       return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexUniformComponents)                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumVertexUniformVectors)                      return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumViewportDimensions)                        return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MaximumViewports)                                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MinimumMapBufferAlignment)                        return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::MinimumProgramTexelOffset)                        return get_integer32_v(D);
        if constexpr (D == glf::Data::MinorVersion)                                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::NumberCompressedTextureFormats)                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::NumberExtensions)                                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::NumberProgramBinaryFormats)                       return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::NumberShaderBinaryFormats)                        return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackAlignment)                                    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackImageHeight)                                  return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackRowLength)                                    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackSkipImages)                                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackSkipPixels)                                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackSkipRows)                                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::PackSwapBytes)                                    return get_boolean_v(D);
        if constexpr (D == glf::Data::PixelPackBufferBinding)                           return get_handle_v(D);
        if constexpr (D == glf::Data::PixelUnpackBufferBinding)                         return get_handle_v(D);
        if constexpr (D == glf::Data::PointFadeThresholdSize)                           return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PointSize)                                        return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PointSizeGranularity)                             return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PointSizeRange)                                   return get_vector2f_v(D);
        if constexpr (D == glf::Data::PolygonOffsetFactor)                              return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PolygonOffsetUnits)                               return get_floating_point32_v(D);
        if constexpr (D == glf::Data::PolygonSmoothHint)                                return glf::Hint::Mode{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::PrimitiveRestartIndex)                            return get_index_v(D);
        if constexpr (D == glf::Data::ProgramBinaryFormats)                             return get_binary_formats_v(D);
        if constexpr (D == glf::Data::ProgramPipelineBinding)                           return get_handle_v(D);
        if constexpr (D == glf::Data::ProvokingVertex)                                  return glf::ProvokingVertex::Mode{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::QueryBufferBinding)                               return get_handle_v(D);
        if constexpr (D == glf::Data::ReadBuffer)                                       return glf::FrameBuffer::Source{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::ReadFrameBufferBinding)                           return get_handle_v(D);
        if constexpr (D == glf::Data::RenderbufferBinding)                              return get_handle_v(D);
        if constexpr (D == glf::Data::SampleBuffers)                                    return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::SampleCoverageInvert)                             return get_boolean_v(D);
        if constexpr (D == glf::Data::SampleCoverageValue)                              return get_floating_point32_v(D);
        if constexpr (D == glf::Data::SamplerBinding)                                   return get_handle_v(D);
        if constexpr (D == glf::Data::Samples)                                          return get_bitfield_v(D);
        if constexpr (D == glf::Data::ScissorBox)                                       return get_area_v(D);
        if constexpr (D == glf::Data::ShaderCompiler)                                   return get_boolean_v(D);
        if constexpr (D == glf::Data::ShaderStorageBufferBinding)                       return get_handle_v(D);
        if constexpr (D == glf::Data::ShaderStorageBufferOffsetAlignment)               return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::SmoothLineWidthGranularity)                       return get_floating_point32_v(D);
        if constexpr (D == glf::Data::SmoothLineWidthRange)                             return get_vector2f_v (D);
        if constexpr (D == glf::Data::StencilBackFail)                                  return glf::Stencil::Action{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::StencilBackFunction)                              return glf::Stencil::Function{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::StencilBackPassDepthFail)                         return glf::Stencil::Action{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::StencilBackPassDepthPass)                         return glf::Stencil::Action{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::StencilBackReference)                             return get_integer32_v(D);
        if constexpr (D == glf::Data::StencilBackValueMask)                             return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::StencilBackWriteMask)                             return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::StencilClearValue)                                return get_index_v(D);
        if constexpr (D == glf::Data::StencilFail)                                      return glf::Stencil::Action{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::StencilFunction)                                  return glf::Stencil::Function{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::StencilPassDepthFail)                             return glf::Stencil::Action{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::StencilPassDepthPass)                             return glf::Stencil::Action{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::StencilReference)                                 return get_integer32_v(D);
        if constexpr (D == glf::Data::StencilValueMask)                                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::StencilWriteMask)                                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::Stereo)                                           return get_boolean_v(D);
        if constexpr (D == glf::Data::SubpixelBits)                                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::TextureBinding1D)                                 return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding1DArray)                            return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding2D)                                 return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding2DArray)                            return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding2DMultisample)                      return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding2DMultisampleArray)                 return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBinding3D)                                 return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBindingBuffer)                             return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBindingCubemap)                            return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBindingRectangle)                          return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBufferBinding)                             return get_handle_v(D);
        if constexpr (D == glf::Data::TextureBufferOffsetAlignment)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::TextureCompressionHint)                           return glf::Hint::Mode{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::Timestamp)                                        return get_integer64_v(D);
        if constexpr (D == glf::Data::TransformFeedbackBufferBinding)                   return get_handle_v(D);
        if constexpr (D == glf::Data::UniformBufferBinding)                             return get_handle_v(D);
        if constexpr (D == glf::Data::UniformBufferOffsetAlignment)                     return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackAlignment)                                  return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackImageHeight)                                return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackRowLength)                                  return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackSkipImages)                                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackSkipPixels)                                 return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackSkipRows)                                   return get_unsigned_integer32_v(D);
        if constexpr (D == glf::Data::UnpackSwapBytes)                                  return get_boolean_v(D);
        if constexpr (D == glf::Data::VertexArrayBinding)                               return get_handle_v(D);
        if constexpr (D == glf::Data::Viewport)                                         return get_area_v(D);
        if constexpr (D == glf::Data::ViewportBoundsRange)                              return get_vector2i_v(D);
        if constexpr (D == glf::Data::ViewportIndexProvokingVertex)                     return glf::ProvokingVertex::Convention{ get_unsigned_integer32_v(D) };
        if constexpr (D == glf::Data::ViewportSubPixelBits)                             return get_unsigned_integer32_v(D);
    }
    template<glf::Data D> requires gl::indexed_data_c<D>
    static auto get_value_index                         (gl::index_t index)
    {
        const auto& get_unsigned_integer32_v = [](glf::Data data, gl::index_t index)
            {
                gl::int32_t value{};
                glGetIntegeri_v(gl::to_underlying(data), index, &value);

                return static_cast<gl::uint32_t>(value);
            };
        const auto& get_unsigned_integer64_v = [](glf::Data data, gl::index_t index)
            {
                gl::int64_t value{};
                glGetInteger64i_v(gl::to_underlying(data), index, &value);

                return static_cast<gl::uint64_t>(value);
            };
        const auto& get_handle_v             = [](glf::Data data, gl::index_t index)
            {
                gl::int32_t value{};
                glGetIntegeri_v(gl::to_underlying(data), index, &value);

                return static_cast<gl::handle_t>(value);
            };
        const auto& get_area_v               = [](glf::Data data, gl::index_t index)
            {
                std::array<gl::uint32_t, 4> value{};
                glGetIntegeri_v(gl::to_underlying(data), index, reinterpret_cast<gl::int32_t*>(value.data()));

                struct result_t{ gl::area_t area{ {} }; };
                return result_t{ gl::area_t{ gl::Vector2u{ value.at(2), value.at(3) }, gl::Vector2u{ value.at(0), value.at(1) } } };
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
    static void enable                                  ()
    {
        glEnable(gl::to_underlying(F));
    }
    template<glf::Feature F> requires gl::indexed_feature_c<F>
    static void enable_index                            (gl::index_t index)
    {
        glEnablei(gl::to_underlying(F), index);
    }
    template<glf::Feature F>
    static void disable                                 ()
    {
        glDisable(gl::to_underlying(F));
    }
    template<glf::Feature F> requires gl::indexed_feature_c<F>
    static void disable_index                           (gl::index_t index)
    {
        glDisablei(gl::to_underlying(F), index);
    }
    template<glf::Feature F>
    static auto is_enabled                              ()
    {
        return static_cast<gl::bool_t>(glIsEnabled(gl::to_underlying(F)));
    }
    template<glf::Feature F> requires gl::indexed_feature_c<F>
    static auto is_enabled_index                        (gl::index_t index)
    {
        return static_cast<gl::bool_t>(glIsEnabledi(gl::to_underlying(F)));
    }
    template<glf::Callback::Pointer P>
    static auto get_pointer_value                       ()
    {
        gl::void_t* value{};
        glGetPointerv(gl::to_underlying(P), &value);

        return value;
    }
    template<glf::Connection C>
    static auto get_string                              ()
    {
        const gl::byte_t* value = glGetString(gl::to_underlying(C));
        return std::string{ reinterpret_cast<const gl::char_t*>(value) };
    }
    template<glf::Connection C>
    static auto get_string_index                        (gl::index_t index)
    {
        const gl::byte_t* value = glGetStringi(gl::to_underlying(C), index);
        return std::string{ reinterpret_cast<const gl::char_t*>(value) };
    }
    static void get_internal_format_value               ()
    {
        //TODO
        //@OpenGL devs: This function is plain ridiculous
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }



    //Chapter 4 - Event Model
    template<glf::Synchronization::Property P>
    static auto get_sync_value                          (gl::sync_t sync)
    {
        const auto& get_sync_iv = [](gl::sync_t sync, glf::Synchronization::Property property)
            {
                gl::int32_t value{};
                glGetSynciv(sync, gl::to_underlying(property), gl::sizei_t{ 1 }, nullptr, &value);

                return value;
            };



        if constexpr (P == glf::Synchronization::Property::Type)      return static_cast<glf::Synchronization::Object::Type>     (get_sync_iv(sync, P));
        if constexpr (P == glf::Synchronization::Property::Status)    return static_cast<glf::Synchronization::Object::Status>   (get_sync_iv(sync, P));
        if constexpr (P == glf::Synchronization::Property::Condition) return static_cast<glf::Synchronization::Object::Condition>(get_sync_iv(sync, P));
        if constexpr (P == glf::Synchronization::Property::Flags)     return gl::bitfield_t{ 0u };
    }
    template<glf::Query::Symbol S>
    static auto get_query_value                         (glf::Query::Target target)
    {
        gl::int32_t value{};
        glGetQueryiv(gl::to_underlying(target), gl::to_underlying(S), &value);

        return static_cast<gl::uint32_t>(value);
    }
    template<glf::Query::Symbol S>
    static auto get_query_value_index                   (glf::Query::Target target, gl::index_t index)
    {
        gl::int32_t value{};
        glGetQueryIndexediv(gl::to_underlying(target), index.value_or(0u), gl::to_underlying(S), &value);

        return static_cast<gl::uint32_t>(value);
    }
    template<glf::Query::Parameter P>
    static auto get_query_object_value                  (gl::handle_t query)
    {
        const auto& get_query_object_iv  = [](gl::handle_t query, glf::Query::Parameter parameter)
            {
                gl::int32_t value{};
                glGetQueryObjectiv(gl::to_underlying(query), gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_query_object_uiv = [](gl::handle_t query, glf::Query::Parameter parameter)
            {
                gl::uint32_t value{};
                glGetQueryObjectuiv(gl::to_underlying(query), gl::to_underlying(parameter), &value);

                return value;
            };



        if constexpr (P == glf::Query::Parameter::Result         ) return                                 get_query_object_uiv(query, P) ;
        if constexpr (P == glf::Query::Parameter::ResultNoWait   ) return                                 get_query_object_uiv(query, P) ;
        if constexpr (P == glf::Query::Parameter::ResultAvailable) return static_cast<gl::bool_t>        (get_query_object_iv (query, P));
        if constexpr (P == glf::Query::Parameter::Target         ) return static_cast<glf::Query::Target>(get_query_object_iv (query, P));
    }
    template<glf::Query::Parameter P>
    static void get_query_object_value_buffer           (gl::handle_t query, gl::handle_t buffer, gl::offset_t offset)
    {
        const auto& get_query_object_iv_buffer  = [](gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
            {
                glGetQueryBufferObjectiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
            };
        const auto& get_query_object_uiv_buffer = [](gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
            {
                glGetQueryBufferObjectuiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
            };



        if constexpr (P == glf::Query::Parameter::Result         ) get_query_object_uiv_buffer(query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::ResultNoWait   ) get_query_object_uiv_buffer(query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::ResultAvailable) get_query_object_iv_buffer (query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::Target         ) get_query_object_iv_buffer (query, buffer, P, offset);
    }



    //Chapter 6 - Buffer Objects
    template<glf::Buffer::Parameter P>
    static auto get_buffer_parameter_value              (gl::handle_t buffer)
    {
        const auto& get_buffer_parameter_iv   = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int32_t value{};
                glGetNamedBufferParameteriv(gl::to_underlying(buffer), gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_buffer_parameter_i64v = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int64_t value{};
                glGetNamedBufferParameteri64v(gl::to_underlying(buffer), gl::to_underlying(parameter), &value);

                return value;
            };



        if constexpr (P == glf::Buffer::Parameter::Access)       return static_cast<glf::Buffer::Mapping::Access>     (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::AccessFlags)  return static_cast<glf::Buffer::Mapping::AccessFlags>(get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Immutable)    return static_cast<gl::bool_t>                       (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::IsMapped)     return static_cast<gl::bool_t>                       (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::MapLength)    return static_cast<gl::uint64_t>                     (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::MapOffset)    return static_cast<gl::uint64_t>                     (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Size)         return static_cast<gl::uint64_t>                     (get_buffer_parameter_i64v(buffer, P));
        if constexpr (P == glf::Buffer::Parameter::StorageFlags) return static_cast<glf::Buffer::StorageFlags>        (get_buffer_parameter_iv  (buffer, P));
        if constexpr (P == glf::Buffer::Parameter::Usage)        return static_cast<glf::Buffer::Usage>               (get_buffer_parameter_iv  (buffer, P));
    }
    template<typename T>
    static auto get_buffer_data                         (gl::handle_t buffer)
    {
        const auto& size = gl::get_buffer_parameter_value(buffer, glf::Buffer::Parameter::Size);
        std::vector<T> data(size);

        glGetNamedBufferSubData(gl::to_underlying(buffer), gl::offset_t{ 0 }, size, data.data());

        return data;
    }
    template<typename T>
    static auto get_buffer_sub_data(gl::handle_t buffer, gl::byterange_t range)
    {
        std::vector<T> data(range.size);
        
        glGetNamedBufferSubData(gl::to_underlying(buffer), range.offset, range.size, data.data());

        return data;
    }



    //Chapter 7 - Programs and Shaders
    template<glf::Shader::Parameter P>
    static auto get_shader_value                        (gl::handle_t shader)
    {
        const auto& get_shader_iv = [](gl::handle_t shader, glf::Shader::Parameter parameter)
            {
                gl::int32_t value{};
                glGetShaderiv(gl::to_underlying(shader), gl::to_underlying(parameter), &value);

                return value;
            };



        if constexpr (P == glf::Shader::Parameter::Type         ) return static_cast<glf::Shader::Type>(get_shader_iv(shader, P));
        if constexpr (P == glf::Shader::Parameter::DeleteStatus ) return static_cast<gl::bool_t>       (get_shader_iv(shader, P));
        if constexpr (P == glf::Shader::Parameter::CompileStatus) return static_cast<gl::bool_t>       (get_shader_iv(shader, P));
        if constexpr (P == glf::Shader::Parameter::InfoLogLength) return static_cast<gl::uint32_t>     (get_shader_iv(shader, P));
        if constexpr (P == glf::Shader::Parameter::SourceLength ) return static_cast<gl::uint32_t>     (get_shader_iv(shader, P));
    }
    template<glf::Program::Parameter P>
    static auto get_program_value                       (gl::handle_t program)
    {
        const auto& get_program_iv = [](gl::handle_t program, glf::Program::Parameter parameter)
            {
                gl::int32_t value{};
                glGetProgramiv(gl::to_underlying(program), gl::to_underlying(parameter), &value);

                return value;
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
    static auto get_program_pipeline_value              (gl::handle_t pipeline)
    {
        const auto& get_program_pipeline_iv = [](gl::handle_t pipeline, glf::Pipeline::Property property)
            {
                gl::int32_t value{};
                glGetProgramPipelineiv(gl::to_underlying(pipeline), gl::to_underlying(property), &value);

                return value;
            };

        if   constexpr (P == glf::Pipeline::Property::ValidateStatus) return static_cast<gl::bool_t>  (get_program_pipeline_iv(pipeline, P));
        if   constexpr (P == glf::Pipeline::Property::InfoLogLength ) return static_cast<gl::uint32_t>(get_program_pipeline_iv(pipeline, P));
        else                                                                   return static_cast<gl::handle_t>(get_program_pipeline_iv(pipeline, P));
    }
    static auto get_attached_shaders                    (gl::handle_t program)
    {
        const auto& attachedShaders = gl::get_program_value<glf::Program::Parameter::AttachedShaders>(program);
        std::vector<gl::handle_t> shaders(attachedShaders);

        glGetAttachedShaders(gl::to_underlying(program), attachedShaders, nullptr, gl::to_underlying_ptr(shaders.data()));

        return shaders;
    }
    static auto get_shader_info_log                     (gl::handle_t shader)
    {
        std::string infoLog{};

        if (const auto& infoLogLength = get_shader_value<glf::Shader::Parameter::InfoLogLength>(shader); std::cmp_greater(infoLogLength, 0u))
        {
            infoLog.resize(infoLogLength);
            glGetShaderInfoLog(gl::to_underlying(shader), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    static auto get_program_info_log                    (gl::handle_t program)
    {
        std::string infoLog{};

        if (const auto& infoLogLength = gl::get_program_value<glf::Program::Parameter::InfoLogLength>(program); std::cmp_greater(infoLogLength, 0u))
        {
            infoLog.resize(infoLogLength);
            glGetProgramInfoLog(gl::to_underlying(program), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    static auto get_pipeline_info_log                   (gl::handle_t pipeline)
    {
        std::string infoLog{};

        if (const auto& infoLogLength = gl::get_program_pipeline_value<glf::Pipeline::Property::InfoLogLength>(pipeline); std::cmp_greater(infoLogLength, 0u))
        {
            infoLog.resize(infoLogLength);
            glGetProgramPipelineInfoLog(gl::to_underlying(pipeline), infoLogLength, nullptr, infoLog.data());
            infoLog.pop_back();
        }

        return infoLog;
    }
    static auto get_shader_source                       (gl::handle_t shader)
    {
        std::string shaderSource{};

        if (const auto& sourceLength = get_shader_value<glf::Shader::Parameter::SourceLength>(shader); std::cmp_greater(sourceLength, 0u))
        {
            shaderSource.resize(sourceLength);
            glGetShaderSource(gl::to_underlying(shader), sourceLength, nullptr, shaderSource.data());
            shaderSource.pop_back();
        }

        return shaderSource;
    }
    static auto get_shader_precision_format             (glf::Shader::Type type, glf::Shader::PrecisionFormat format)
    {
        std::array<gl::int32_t, 2> range{};
        gl::int32_t                precision{};

        glGetShaderPrecisionFormat(gl::to_underlying(type), gl::to_underlying(format), range.data(), &precision);

        struct result_t{ std::array<gl::int32_t, 2> range{}; gl::int32_t precision{}; };
        return result_t{ range, precision };
    }



    //Chapter 8 - Textures and Samplers
    template<glf::Sampler::Parameter P>
    static auto get_sampler_parameter_value             (gl::handle_t sampler)
    {
        const auto& get_sampler_parameter_iv  = [](gl::handle_t sampler, glf::Sampler::Parameter parameter)
            {
                gl::int32_t value{};
                glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_sampler_parameter_uiv = [](gl::handle_t sampler, glf::Sampler::Parameter parameter)
            {
                gl::uint32_t value{};
                glGetSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_sampler_parameter_fv  = [](gl::handle_t sampler, glf::Sampler::Parameter parameter)
            {
                gl::float32_t value{};
                glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

                return value;
            };
        
        const auto& get_border_color          = [](gl::handle_t sampler)
            {
                std::array<gl::float32_t, 4> value{};
                glGetSamplerParameterfv(gl::to_underlying(sampler), glf::Sampler::Parameter::BorderColor, &value);

                return value;
            };



        if constexpr (P == glf::Sampler::Parameter::BorderColor        ) return                                                get_border_color         (sampler);
        if constexpr (P == glf::Sampler::Parameter::CompareFunction    ) return static_cast<glf::Texture::CompareFunction>    (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::CompareMode        ) return static_cast<glf::Texture::CompareMode>        (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::LodBias            ) return                                                get_sampler_parameter_fv (sampler, P);
        if constexpr (P == glf::Sampler::Parameter::MagnificationFilter) return static_cast<glf::Texture::MagnificationFilter>(get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::MaximumAnisotropy  ) return                                                get_sampler_parameter_fv (sampler, P);
        if constexpr (P == glf::Sampler::Parameter::MaximumLOD         ) return                                                get_sampler_parameter_fv (sampler, P);
        if constexpr (P == glf::Sampler::Parameter::MinificationFilter ) return static_cast<glf::Texture::MinificationFilter> (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::MinimumLOD         ) return                                                get_sampler_parameter_fv (sampler, P);
        if constexpr (P == glf::Sampler::Parameter::WrappingR          ) return static_cast<glf::Texture::Wrapping>           (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::WrappingS          ) return static_cast<glf::Texture::Wrapping>           (get_sampler_parameter_uiv(sampler, P));
        if constexpr (P == glf::Sampler::Parameter::WrappingT          ) return static_cast<glf::Texture::Wrapping>           (get_sampler_parameter_uiv(sampler, P));
    }
    template<glf::Texture::Format F>
    static auto get_texture_image                       (gl::handle_t texture, gl::uint32_t level, gl::size_t size)
    {
        if constexpr (F == glf::Texture::Format::RGBA8_UNORM)
        {
            std::vector<gl::Vector4u> value(size);

            glGetTextureImage(
                gl::to_underlying       (texture)                      , 
                static_cast<gl::int32_t>(level)                        , 
                gl::to_underlying       (glf::Buffer::BaseFormat::RGBA), gl::to_underlying(glf::PixelData::Type::UnsignedByte), 
                static_cast<gl::sizei_t>(value.data())                 , value.data());

            return value;
        }
    }
    template<glf::Texture::Format F>
    static auto get_texture_sub_image                   (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, gl::size_t size)
    {
        if constexpr (F == glf::Texture::Format::RGBA8_UNORM)
        {
            std::vector<gl::Vector4u> value(size);

            glGetTextureSubImage(
                gl::to_underlying       (texture)                      , 
                static_cast<gl::int32_t>(level)                        , 
                static_cast<gl::int32_t>(region.origin.x)              , static_cast<gl::int32_t>(region.origin.y)            , static_cast<gl::int32_t>(region.origin.z), 
                static_cast<gl::sizei_t>(region.extent.x)              , static_cast<gl::sizei_t>(region.extent.y)            , static_cast<gl::sizei_t>(region.extent.z), 
                gl::to_underlying       (glf::Buffer::BaseFormat::RGBA), gl::to_underlying(glf::PixelData::Type::UnsignedByte), 
                static_cast<gl::sizei_t>(value.data())                 , value.data());

            return value;
        }
    }
    template<glf::Texture::Format F>
    static auto get_compressed_texture_image            (gl::handle_t texture, gl::uint32_t level, gl::size_t size)
    {
        if constexpr (F == glf::Texture::Format::RGBA8_UNORM)
        {
            std::vector<gl::Vector4u> value(size);

            glGetCompressedTextureImage(
                gl::to_underlying       (texture)                      , 
                static_cast<gl::int32_t>(level)                        , 
                static_cast<gl::sizei_t>(value.data())                 , value.data());

            return value;
        }
    }
    template<glf::Texture::Format F>
    static auto get_compressed_texture_sub_image        (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, gl::size_t size)
    {
        if constexpr (F == glf::Texture::Format::RGBA8_UNORM)
        {
            std::vector<gl::Vector4u> value(size);

            glGetCompressedTextureSubImage(
                gl::to_underlying       (texture)        , 
                static_cast<gl::int32_t>(level)          , 
                static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
                static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
                static_cast<gl::sizei_t>(value.data())   , value.data());

            return value;
        }
    }



    //Chapter 9 - FrameBuffer and FrameBuffer Objects
    template<glf::FrameBuffer::Parameter P>
    static auto get_frame_buffer_parameter_value        (gl::handle_t frameBuffer)
    {
        const auto& get_frame_buffer_parameter_iv    = [](gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter)
            {
                gl::int32_t value{};
                glGetNamedFramebufferParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_frame_buffer_parameter_iv_nd = [](gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter)
            {
                if (frameBuffer == gl::DefaultFrameBuffer) throw std::invalid_argument{ "These parameters may not be queried for the default frame buffer!" };

                gl::int32_t value{};
                glGetNamedFramebufferParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), &value);

                return value;
            };

        if   constexpr (P == glf::FrameBuffer::Parameter::DefaultWidth               ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv   (frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::DefaultHeight              ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv   (frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::DefaultLayers              ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv   (frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::DefaultSamples             ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv   (frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::DefaultFixedSampleLocations) return static_cast<gl::bool_t>            (get_frame_buffer_parameter_iv   (frameBuffer, P));

        if   constexpr (P == glf::FrameBuffer::Parameter::ColorReadFormat            ) return static_cast<glf::PixelData::Format>(get_frame_buffer_parameter_iv_nd(frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::ColorReadType              ) return static_cast<glf::PixelData::Type>  (get_frame_buffer_parameter_iv_nd(frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::DoubleBuffer               ) return static_cast<gl::bool_t>            (get_frame_buffer_parameter_iv_nd(frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::SampleBuffers              ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv_nd(frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::Samples                    ) return static_cast<gl::uint32_t>          (get_frame_buffer_parameter_iv_nd(frameBuffer, P));
        if   constexpr (P == glf::FrameBuffer::Parameter::Stereo                     ) return static_cast<gl::bool_t>            (get_frame_buffer_parameter_iv_nd(frameBuffer, P));
    }
    template<glf::FrameBuffer::Parameter P>
    static auto get_frame_buffer_attachment_parameter_value(gl::handle_t frameBuffer)
    {
        const auto& get_frame_buffer_attachment_parameter_iv = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, glf::FrameBuffer::Parameter parameter, gl::int32_t value)
            {
                glGetNamedFramebufferAttachmentParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(parameter), &value);
            };

        //i cant
        //TODO
    }
    template<glf::RenderBuffer::Parameter P>
    static auto get_render_buffer_parameter_value       (gl::handle_t renderBuffer)
    {
        const auto& get_render_buffer_parameter_iv = [](gl::handle_t renderBuffer, glf::RenderBuffer::Parameter parameter)
            {
                gl::int32_t value{};
                glGetNamedRenderbufferParameteriv(gl::to_underlying(renderBuffer), gl::to_underlying(parameter), &value);

                return value;
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
    static auto get_vertex_array_indexed_value          (gl::handle_t vertexArray)
    {
        if constexpr (P == glf::VertexArray::Parameter::ElementArrayBufferBinding)
        {
            gl::int32_t value{};
            glGetVertexArrayiv(gl::to_underlying(vertexArray), gl::to_underlying(P), &value);

            return static_cast<gl::handle_t>(value);
        }
    }
    template<glf::VertexArray::Parameter P>
    static auto get_vertex_array_indexed_value          (gl::handle_t vertexArray, gl::index_t index)
    {
        const auto& get_vertex_array_indexed32_iv = [](gl::handle_t vertexArray, glf::VertexArray::Parameter parameter, gl::index_t index)
            {
                gl::int32_t value{};
                glGetVertexArrayIndexediv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value);

                return value;
            };
        const auto& get_vertex_array_indexed64_iv = [](gl::handle_t vertexArray, glf::VertexArray::Parameter parameter, gl::index_t index)
            {
                gl::int64_t value{};
                glGetVertexArrayIndexed64iv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value);

                return value;
            };



        const auto& maximumVertexAttributes = gl::get_value<glf::Data::MaximumVertexAttributes>();
        if (std::cmp_greater(index, maximumVertexAttributes - 1u)) throw std::out_of_range{ "The given index is out of range!" };

        if constexpr (P == glf::VertexArray::Parameter::BindingOffset            ) return static_cast<gl::uint64_t>                     (get_vertex_array_indexed64_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Divisor                  ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Enabled                  ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::IsIntegerData            ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::IsLongData               ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::IsNormalized             ) return static_cast<gl::bool_t>                       (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::RelativeOffset           ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Size                     ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Stride                   ) return static_cast<gl::uint32_t>                     (get_vertex_array_indexed32_iv(vertexArray, P, index));
        if constexpr (P == glf::VertexArray::Parameter::Type                     ) return static_cast<glf::VertexArray::Attribute::Type>(get_vertex_array_indexed32_iv(vertexArray, P, index));
    }



    //Chapter 20 - Debug Output
    static auto get_debug_message_log                   (gl::count_t count)
    {
        const auto& maximumLength = gl::get_value<glf::Data::MaximumDebugMessageLength>();

        std::string                       messageLog(count * static_cast<gl::uint64_t>(maximumLength), '\0');
        std::vector<glf::Debug::Source>   sources   (count);
        std::vector<glf::Debug::Type>     types     (count);
        std::vector<gl::uint32_t>         ids       (count);
        std::vector<glf::Debug::Severity> severities(count);
        std::vector<gl::sizei_t>          lengths   (count);

        gl::count_t amount = glGetDebugMessageLog(
            count, maximumLength, 
            gl::to_underlying_ptr(sources   .data()), 
            gl::to_underlying_ptr(types     .data()), 
                                  ids       .data(), 
            gl::to_underlying_ptr(severities.data()), 
                                  lengths   .data(), 
                                  messageLog.data());

        struct result_t
        {
            gl::uint32_t         id{};
            std::string          message{};
            glf::Debug::Source   source{};
            glf::Debug::Type     type{};
            glf::Debug::Severity severity{};
        };

        std::vector<result_t> result(amount);

        if (std::cmp_greater(amount, 0u))
        {
            gl::offset_t offset{};

            for (const auto& index : std::views::iota(0u, amount))
            {
                const auto& length = lengths.at(index);

                std::string message{ messageLog.data() + offset, static_cast<std::size_t>(length) - 1u };
                offset += length;

                result.emplace_back(
                    ids       .at(index),
                    message,
                    sources   .at(index),
                    types     .at(index),
                    severities.at(index));
            }
        }

        return result;
    }







    //Chapter 2 - OpenGL Fundamentals
    static auto get_graphics_reset_status               ()
    {
        return static_cast<glf::Error::GraphicsResetStatus>(glGetGraphicsResetStatus());
    }
    static void flush                                   ()
    {
        glFlush();
    }
    static void finish                                  ()
    {
        glFinish();
    }



    //Chapter 4 - Event Model
    static auto fence_sync                              ()
    {
        return static_cast<gl::sync_t>(glFenceSync(gl::to_underlying(glf::Synchronization::Object::Condition::GPUCommandsComplete), gl::bitfield_t{ 0u }));
    }
    static void delete_sync                             (gl::sync_t sync)
    {
        if (sync) glDeleteSync(sync);
    }
    static auto client_wait_sync                        (gl::sync_t sync, glf::Synchronization::Command command, gl::time_t timeout)
    {
        return static_cast<glf::Synchronization::Status>(glClientWaitSync(sync, gl::to_underlying(command), timeout));
    }
    static void server_wait_sync                        (gl::sync_t sync)
    {
        glWaitSync(sync, gl::bitfield_t{ 0u }, gl::to_underlying(glf::Synchronization::Timeout::Ignored));
    }
    static auto create_query                            (glf::Query::Target target)
    {
        gl::handle_t handle{};
        glCreateQueries(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static auto create_queries                          (glf::Query::Target target, gl::uint32_t amount)
    {
        std::vector<gl::handle_t> handles(amount);
        glCreateQueries(gl::to_underlying(target), static_cast<gl::sizei_t>(amount), gl::to_underlying_ptr(handles.data()));

        return handles;
    }
    static void delete_query                            (gl::handle_t query)
    {
        glDeleteQueries(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&query));
    }
    static void delete_queries                          (std::span<const gl::handle_t> queries)
    {
        glDeleteQueries(static_cast<gl::sizei_t>(queries.size()), gl::to_underlying_ptr(queries.data()));
    }
    static void begin_query                             (gl::handle_t query, glf::Query::Target target)
    {
        glBeginQuery(gl::to_underlying(target), gl::to_underlying(query));
    }
    static void begin_query_index                       (gl::handle_t query, glf::Query::Target target, gl::index_t index)
    {
        glBeginQueryIndexed(gl::to_underlying(target), index, gl::to_underlying(query));
    }
    static void end_query                               (glf::Query::Target target)
    {
        glEndQuery(gl::to_underlying(target));
    }
    static void end_query_index                         (glf::Query::Target target, gl::index_t index)
    {
        glEndQueryIndexed(gl::to_underlying(target), index);
    }
    static void query_counter                           (gl::handle_t query)
    {
        glQueryCounter(gl::to_underlying(query), gl::to_underlying(glf::Query::Counter::Timestamp));
    }



    //Chapter 6 - Buffer Objects
    static auto create_buffer                           ()
    {
        gl::handle_t handle{};
        glCreateBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static auto create_buffers                          (gl::count_t count)
    {
        std::vector<gl::handle_t> handles(count);
        glCreateBuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data()));

        return handles;
    }
    static void delete_buffer                           (gl::handle_t buffer)
    {
        glDeleteBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&buffer));
    }
    static void delete_buffers                          (std::span<const gl::handle_t> buffers)
    {
        glDeleteBuffers(static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()));
    }
    static void bind_buffer_base                        (gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::binding_t binding)
    {
        glBindBufferBase(gl::to_underlying(target), gl::to_underlying(binding), gl::to_underlying(buffer));
    }
    static void bind_buffers_base                       (std::span<const gl::handle_t> buffers, glf::Buffer::BaseTarget target, gl::binding_t binding)
    {
        glBindBuffersBase(gl::to_underlying(target), gl::to_underlying(binding), static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()));
    }
    static void bind_buffer_range                       (gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::binding_t binding, gl::byterange_t range)
    {
        glBindBufferRange(gl::to_underlying(target), gl::to_underlying(binding), gl::to_underlying(buffer), range.offset, range.size);
    }
    static void bind_buffers_range(std::span<const gl::handle_t> buffers, std::span<const gl::byterange_t> ranges, glf::Buffer::BaseTarget target, gl::binding_t binding)
    {
        std::vector<gl::size_t>   sizes(ranges.size());
        std::vector<gl::offset_t> offsets(ranges.size());

        for (const auto& range : ranges)
        {
            sizes.emplace_back(range.size);
            offsets.emplace_back(range.offset);
        }

        glBindBuffersRange(gl::to_underlying(target), gl::to_underlying(binding), static_cast<gl::sizei_t>(buffers.size()), gl::to_underlying_ptr(buffers.data()), offsets.data(), sizes.data());
    }
    static void buffer_storage                          (gl::handle_t buffer, glf::Buffer::StorageFlags flags, gl::size_t size)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), size, nullptr, gl::to_underlying(flags));
    }
    template<typename T>                  
    static void buffer_storage                          (gl::handle_t buffer, glf::Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(data.size_bytes()), data.data(), gl::to_underlying(flags));
    }
    template<typename T>
    static void buffer_data                             (gl::handle_t buffer, gl::offset_t offset, std::span<const T> data)
    {
        glNamedBufferSubData(gl::to_underlying(buffer), offset, static_cast<gl::size_t>(data.size_bytes()), data.data());
    }
    template<typename T>
    static void clear_buffer_data                       (gl::handle_t buffer, glf::Buffer::BaseFormat baseFormat, glf::Buffer::Format format, glf::DataType type, std::span<const T> data)
    {
        //TODO
        glClearNamedBufferData(gl::to_underlying(buffer), gl::to_underlying(format), gl::to_underlying(baseFormat), gl::to_underlying(type), data.data());
    }
    static void clear_buffer_sub_data                   (gl::handle_t buffer, glf::Buffer::BaseFormat baseFormat, glf::Buffer::Format format, glf::DataType type, gl::byterange_t range)
    {
        glClearNamedBufferSubData(gl::to_underlying(buffer), gl::to_underlying(format), range.offset, range.size, gl::to_underlying(baseFormat), gl::to_underlying(type), nullptr);
    }
    template<typename T>
    static auto map_buffer                              (gl::handle_t buffer, glf::Buffer::Mapping::AccessFlags access)
    {
        return reinterpret_cast<T*>(glMapNamedBuffer(gl::to_underlying(buffer), gl::to_underlying(access)));
    }
    template<typename T>
    static auto map_buffer_range                        (gl::handle_t buffer, glf::Buffer::Mapping::RangeAccessFlags access, gl::byterange_t range)
    {
        return reinterpret_cast<T*>(glMapNamedBufferRange(gl::to_underlying(buffer), range.offset, range.size, gl::to_underlying(access)));
    }
    static void flush_buffer_range                      (gl::handle_t buffer, gl::byterange_t range)
    {
        glFlushMappedNamedBufferRange(gl::to_underlying(buffer), range.offset, range.size);
    }
    static auto unmap_buffer                            (gl::handle_t buffer)
    {
        return static_cast<gl::bool_t>(glUnmapNamedBuffer(gl::to_underlying(buffer)));
    }
    static void invalidate_buffer_data                  (gl::handle_t buffer)
    {
        glInvalidateBufferData(gl::to_underlying(buffer));
    }
    static void invalidate_buffer_sub_data              (gl::handle_t buffer, gl::byterange_t range)
    {
        glInvalidateBufferSubData(gl::to_underlying(buffer), range.offset, range.size);
    }
    static void copy_buffer_sub_data                    (gl::handle_t source, gl::handle_t destination, gl::byterange_t sourceRange, gl::offset_t destinationOffset)
    {
        glCopyNamedBufferSubData(gl::to_underlying(source), gl::to_underlying(destination), sourceRange.offset, destinationOffset, sourceRange.size);
    }
    


    //Chapter 7 - Programs and Shaders
    static auto create_shader                           (glf::Shader::Type type)
    {
        return static_cast<gl::handle_t>(glCreateShader(gl::to_underlying(type)));
    }
    static void shader_source                           (gl::handle_t shader, const std::string& source)
    {
        const auto* cstr = source.c_str();
        glShaderSource(gl::to_underlying(shader), gl::sizei_t{ 1 }, &cstr, nullptr);
    }
    static void compile_shader                          (gl::handle_t shader)
    {
        glCompileShader(gl::to_underlying(shader));
    }
    static void release_shader_compiler                 ()
    {
        glReleaseShaderCompiler();
    }
    static void delete_shader                           (gl::handle_t shader)
    {
        glDeleteShader(gl::to_underlying(shader));
    }
    static void shader_binary                           (gl::handle_t shader, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glShaderBinary(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&shader), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    static void shader_binaries                         (std::span<const gl::handle_t> shaders, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glShaderBinary(static_cast<gl::sizei_t>(shaders.size()), gl::to_underlying_ptr(shaders.data()), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    template<gl::count_t N = 0>
    static void specialize_shader                       (gl::handle_t shader, const std::string& entry, std::span<const gl::uint32_t, N> indices = {}, std::span<const gl::uint32_t, N> values = {})
    {
        const auto* cstr = entry.c_str();
        glSpecializeShader(gl::to_underlying(shader), cstr, N, indices.data(), values.data());
    }
    static auto create_program                          ()
    {
        return static_cast<gl::handle_t>(glCreateProgram());
    }
    static void attach_shader                           (gl::handle_t program, gl::handle_t shader)
    {
        glAttachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    static void detach_shader                           (gl::handle_t program, gl::handle_t shader)
    {
        glDetachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    static void link_program                            (gl::handle_t program)
    {
        glLinkProgram(gl::to_underlying(program));
    }
    template<glf::Program::Specification S>
    static void program_parameter                       (gl::handle_t program, gl::bool_t value)
    {
        glProgramParameteri(gl::to_underlying(program), gl::to_underlying(S), value);
    }
    static void delete_program                          (gl::handle_t program)
    {
        glDeleteProgram(gl::to_underlying(program));
    }
    static auto create_shader_program                   (glf::Shader::Type type, const std::string& source)
    {
        const auto* cstr = source.c_str();
        return static_cast<gl::handle_t>(glCreateShaderProgramv(gl::to_underlying(type), gl::sizei_t{ 1 }, &cstr));
    }
    static auto create_program_pipeline                 ()
    {
        gl::handle_t handle{};
        glCreateProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static auto create_program_pipelines                (gl::count_t count)
    {
        std::vector<gl::handle_t> handles(count);
        glCreateProgramPipelines(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data()));

        return handles;
    }
    static void delete_program_pipeline                 (gl::handle_t pipeline)
    {
        glDeleteProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&pipeline));
    }
    static void delete_program_pipelines                (std::span<const gl::handle_t> pipeline)
    {
        glDeleteProgramPipelines(static_cast<gl::sizei_t>(pipeline.size()), gl::to_underlying_ptr(pipeline.data()));
    }
    static void bind_program_pipeline                   (gl::handle_t pipeline)
    {
        glBindProgramPipeline(gl::to_underlying(pipeline));
    }
    static void use_program_stages                      (gl::handle_t pipeline, gl::handle_t program, glf::Program::Stage stages)
    {
        glUseProgramStages(gl::to_underlying(pipeline), gl::to_underlying(stages), gl::to_underlying(program));
    }
    static auto get_program_binary                      (gl::handle_t program)
    {
        const auto& binaryLength = gl::get_program_value<glf::Program::Parameter::BinaryLength>(program);
        std::vector<gl::uint8_t> binary(binaryLength);
        gl::enum_t               format{};

        glGetProgramBinary(gl::to_underlying(program), binaryLength, nullptr, &format, binary.data());

        struct result_t{ std::vector<gl::uint8_t> binary{}; gl::enum_t format{}; };
        return result_t{ binary, format };
    }
    static void program_binary                          (gl::handle_t program, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glProgramBinary(gl::to_underlying(program), format, binary.data(), static_cast<gl::sizei_t>(binary.size()));
    }
    static void memory_barrier                          (glf::Memory::Barrier         barrier)
    {
        glMemoryBarrier(gl::to_underlying(barrier));
    }
    static void memory_barrier_by_region                (glf::Memory::RegionalBarrier barrier)
    {
        glMemoryBarrierByRegion(gl::to_underlying(barrier));
    }



    //Chapter 8 - Textures and Samplers
    static auto create_texture                          (glf::Texture::Target target)
    {
        gl::handle_t handle{};
        glCreateTextures(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static auto create_textures                         (glf::Texture::Target target, gl::count_t count)
    {
        std::vector<gl::handle_t> handles(count);
        glCreateTextures(gl::to_underlying(target), static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data()));

        return handles;
    }
    static void delete_texture                          (gl::handle_t texture)
    {
        glDeleteTextures(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&texture));
    }
    static void delete_textures                         (std::span<const gl::handle_t> textures)
    {
        glDeleteTextures(static_cast<gl::sizei_t>(textures.size()), gl::to_underlying_ptr(textures.data()));
    }
    static void bind_texture_unit                       (gl::handle_t texture, gl::binding_t binding)
    {
        glBindTextureUnit(gl::to_underlying(binding), gl::to_underlying(texture));
    }
    static auto create_sampler                          ()
    {
        gl::handle_t handle{};
        glCreateSamplers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static auto create_samplers                         (gl::count_t count)
    {
        std::vector<gl::handle_t> handles(count);
        glCreateSamplers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data()));

        return handles;
    }
    static void delete_sampler                          (gl::handle_t sampler)
    {
        glDeleteSamplers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&sampler));
    }
    static void delete_samplers                         (std::span<const gl::handle_t> samplers)
    {
        glDeleteSamplers(static_cast<gl::sizei_t>(samplers.size()), gl::to_underlying_ptr(samplers.data()));
    }
    static void bind_sampler                            (gl::handle_t sampler, gl::binding_t binding)
    {
        glBindSampler(gl::to_underlying(binding), gl::to_underlying(sampler));
    }
    static void bind_samplers                           (std::span<const gl::handle_t> samplers, gl::range_t range)
    {
        glBindSamplers(range.index, range.count, gl::to_underlying_ptr(samplers.data()));
    }
    static auto sampler_parameter                       (gl::handle_t sampler, glp::sampler_parameter_t value)
    {
        const auto& sampler_parameter_iv  = [](gl::handle_t sampler, glf::Sampler::Parameter parameter, gl::int32_t   value)
            {
                glSamplerParameterIiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };
        const auto& sampler_parameter_uiv = [](gl::handle_t sampler, glf::Sampler::Parameter parameter, gl::uint32_t  value)
            {
                glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };
        const auto& sampler_parameter_fv  = [](gl::handle_t sampler, glf::Sampler::Parameter parameter, gl::float32_t value)
            {
                glSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);
            };

        if (std::holds_alternative<glp::compare_mode>        (value))
        {
            const auto& v = std::get<glp::compare_mode>(value);
            sampler_parameter_uiv(sampler, glf::Sampler::Parameter::CompareMode, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::compare_function>    (value))
        {
            const auto& v = std::get<glp::compare_function>(value);
            sampler_parameter_uiv(sampler, glf::Sampler::Parameter::CompareFunction, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::magnification_filter>(value))
        {
            const auto& v = std::get<glp::magnification_filter>(value);
            sampler_parameter_uiv(sampler, glf::Sampler::Parameter::MagnificationFilter, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::minification_filter> (value))
        {
            const auto& v = std::get<glp::minification_filter>(value);
            sampler_parameter_uiv(sampler, glf::Sampler::Parameter::MinificationFilter, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::wrapping_s>          (value))
        {
            const auto& v = std::get<glp::wrapping_s>(value);
            sampler_parameter_uiv(sampler, glf::Sampler::Parameter::WrappingS, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::wrapping_t>          (value))
        {
            const auto& v = std::get<glp::wrapping_t>(value);
            sampler_parameter_uiv(sampler, glf::Sampler::Parameter::WrappingT, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::wrapping_r>          (value))
        {
            const auto& v = std::get<glp::wrapping_r>(value);
            sampler_parameter_uiv(sampler, glf::Sampler::Parameter::WrappingR, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::border_color>        (value))
        {
            const auto& v = std::get<glp::border_color>(value);
            
            if (std::holds_alternative<std::array<gl::int32_t  , 4>>(v.value))
            {
                const auto& w = std::get<std::array<gl::int32_t, 4>>(v.value);
                glSamplerParameterIiv(gl::to_underlying(sampler), gl::to_underlying(glf::Sampler::Parameter::BorderColor), w.data());
            }
            if (std::holds_alternative<std::array<gl::uint32_t , 4>>(v.value))
            {
                const auto& w = std::get<std::array<gl::uint32_t, 4>>(v.value);
                glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(glf::Sampler::Parameter::BorderColor), w.data());
            }
            if (std::holds_alternative<std::array<gl::float32_t, 4>>(v.value))
            {
                const auto& w = std::get<std::array<gl::float32_t, 4>>(v.value);
                glSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(glf::Sampler::Parameter::BorderColor), w.data());
            }
        }
        if (std::holds_alternative<glp::maximum_lod>       (value))
        {
            const auto& v = std::get<glp::maximum_lod>(value);
            sampler_parameter_fv(sampler, glf::Sampler::Parameter::MaximumLOD, v.value);
        }
        if (std::holds_alternative<glp::minimum_lod>       (value))
        {
            const auto& v = std::get<glp::minimum_lod>(value);
            sampler_parameter_fv(sampler, glf::Sampler::Parameter::MinimumLOD, v.value);
        }
    }
    static auto pixel_store                             (glf::PackingMode mode, gl::int32_t parameter)
    {
        glPixelStorei(gl::to_underlying(mode), parameter);
    }
    static void texture_sub_image_1d                    (gl::handle_t texture, glf::Texture::BaseFormat format, glf::PixelData::Type type, gl::uint32_t level, gl::length_t region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage1D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            static_cast<gl::int32_t>(region.origin.x), 
            static_cast<gl::sizei_t>(region.extent.x), 
            gl::to_underlying(format), gl::to_underlying(type),
            data.data());
    }
    static void texture_sub_image_2d                    (gl::handle_t texture, glf::Texture::BaseFormat format, glf::PixelData::Type type, gl::uint32_t level, gl::area_t   region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage2D(
            gl::to_underlying(texture), level,
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying(format), gl::to_underlying(type),
            data.data());
    }
    static void texture_sub_image_3d                    (gl::handle_t texture, glf::Texture::BaseFormat format, glf::PixelData::Type type, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glTextureSubImage3D(
            gl::to_underlying(texture), level,
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying(format), gl::to_underlying(type),
            data.data());
    }
    static void copy_texture_sub_image_1d               (gl::handle_t texture, gl::uint32_t level, gl::length_t region, const gl::Vector2u& coordinates)
    {
        glCopyTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)        ,
            static_cast<gl::int32_t>(region.origin.x),
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates.y),
            static_cast<gl::sizei_t>(region.extent.x));
    }
    static void copy_texture_sub_image_2d               (gl::handle_t texture, gl::uint32_t level, gl::area_t   region, const gl::Vector2u& coordinates)
    {
        glCopyTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y),
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates  .y),
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    static void copy_texture_sub_image_3d               (gl::handle_t texture, gl::uint32_t level, gl::volume_t region, const gl::Vector2u& coordinates)
    {
        glCopyTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          ,
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z),
            static_cast<gl::int32_t>(coordinates  .x), static_cast<gl::int32_t>(coordinates  .y),
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    static void compressed_texture_sub_image_1d         (gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, gl::length_t region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage1D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level), 
            static_cast<gl::int32_t>(region.origin.x), 
            static_cast<gl::sizei_t>(region.extent.x), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    static void compressed_texture_sub_image_2d         (gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, gl::area_t   region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage2D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    static void compressed_texture_sub_image_3d         (gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage3D(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , 
            static_cast<gl::sizei_t>(data.size())    , data.data());
    }
    static void texture_buffer                          (gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format)
    {
        glTextureBuffer(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer));
    }
    static void texture_buffer_range                    (gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format, gl::byterange_t range)
    {
        glTextureBufferRange(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer), range.offset, range.size);
    }
    static void texture_parameter                       (gl::handle_t texture, glp::texture_parameter_t value)
    {
        const auto& texture_parameter_iv  = [](gl::handle_t texture, glf::Texture::Parameter parameter, gl::int32_t   value)
            {
                glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), value);
            };
        const auto& texture_parameter_uiv = [](gl::handle_t texture, glf::Texture::Parameter parameter, gl::uint32_t  value)
            {
                glTextureParameteri(gl::to_underlying(texture), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
            };
        const auto& texture_parameter_fv  = [](gl::handle_t texture, glf::Texture::Parameter parameter, gl::float32_t value)
            {
                glTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(parameter), &value);
            };
        
        if (std::holds_alternative<glp::compare_mode>        (value))
        {
            const auto& v = std::get<glp::compare_mode>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::CompareMode, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::compare_function>    (value))
        {
            const auto& v = std::get<glp::compare_function>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::CompareFunction, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::base_level>          (value))
        {
            const auto& v = std::get<glp::base_level>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::BaseLevel, v.value);
        }
        if (std::holds_alternative<glp::maximum_level>       (value))
        {
            const auto& v = std::get<glp::maximum_level>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::MaximumLevel, v.value);
        }
        if (std::holds_alternative<glp::border_color>        (value))
        {
            const auto& v = std::get<glp::border_color>(value);

            if (std::holds_alternative<std::array<gl::int32_t, 4>>(v.value))
            {
                const auto& w = std::get<std::array<gl::int32_t, 4>>(v.value);
                glTextureParameterIiv(gl::to_underlying(texture), gl::to_underlying(glf::Texture::Parameter::BorderColor), w.data());
            }
            if (std::holds_alternative<std::array<gl::uint32_t, 4>>(v.value))
            {
                const auto& w = std::get<std::array<gl::uint32_t, 4>>(v.value);
                glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(glf::Texture::Parameter::BorderColor), w.data());
            }
            if (std::holds_alternative<std::array<gl::float32_t, 4>>(v.value))
            {
                const auto& w = std::get<std::array<gl::float32_t, 4>>(v.value);
                glTextureParameterfv(gl::to_underlying(texture), gl::to_underlying(glf::Texture::Parameter::BorderColor), w.data());
            }
        }
        if (std::holds_alternative<glp::depth_stencil_mode>  (value))
        {
            const auto& v = std::get<glp::depth_stencil_mode>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::DepthStencilMode, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::magnification_filter>(value))
        {
            const auto& v = std::get<glp::magnification_filter>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::MagnificationFilter, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::minification_filter> (value))
        {
            const auto& v = std::get<glp::minification_filter>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::MinificationFilter, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::maximum_anisotropy>  (value))
        {
            const auto& v = std::get<glp::maximum_anisotropy>(value);
            texture_parameter_fv(texture, glf::Texture::Parameter::MaximumAnisotropy, v.value);
        }
        if (std::holds_alternative<glp::wrapping_s>          (value))
        {
            const auto& v = std::get<glp::wrapping_s>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::WrappingS, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::wrapping_t>          (value))
        {
            const auto& v = std::get<glp::wrapping_t>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::WrappingT, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::wrapping_r>          (value))
        {
            const auto& v = std::get<glp::wrapping_r>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::WrappingR, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::swizzle_r>           (value))
        {
            const auto& v = std::get<glp::swizzle_r>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::SwizzleRed, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::swizzle_g>           (value))
        {
            const auto& v = std::get<glp::swizzle_g>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::SwizzleGreen, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::swizzle_b>           (value))
        {
            const auto& v = std::get<glp::swizzle_b>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::SwizzleBlue, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::swizzle_a>           (value))
        {
            const auto& v = std::get<glp::swizzle_a>(value);
            texture_parameter_uiv(texture, glf::Texture::Parameter::SwizzleAlpha, gl::to_underlying(v.value));
        }
        if (std::holds_alternative<glp::swizzle_rgba>        (value))
        {
            const auto& v = std::get<glp::swizzle_rgba>(value);
            glTextureParameterIuiv(gl::to_underlying(texture), gl::to_underlying(glf::Texture::Parameter::SwizzleRGBA), gl::to_underlying_ptr(v.value.data()));
        }
    }
    static void generate_texture_mipmap                 (gl::handle_t texture)
    {
        glGenerateTextureMipmap(gl::to_underlying(texture));
    }
    template<glf::Texture::Target T, glf::Texture::Target U> requires valid_texture_view_c<T, U>
    static void texture_view                            (gl::handle_t source, gl::handle_t destination, glf::Texture::Format format, gl::uint32_t minimumLevel, gl::uint32_t levels, gl::uint32_t minimumLayer, gl::uint32_t layers)
    {
        glTextureView(gl::to_underlying(destination), gl::to_underlying(U), gl::to_underlying(source), gl::to_underlying(format), minimumLevel, levels, minimumLayer, layers);
    }
    static void texture_storage_1d                      (gl::handle_t texture, glf::Texture::Format format, const gl::Vector1u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage1D(
            gl::to_underlying       (texture)      , 
            static_cast<gl::sizei_t>(levels)       , 
            gl::to_underlying       (format)       , 
            static_cast<gl::sizei_t>(dimensions.x));
    }
    static void texture_storage_2d                      (gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage2D(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(levels)      , 
            gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    static void texture_storage_3d                      (gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage3D(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(levels)      , 
            gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z));
    }
    static void texture_storage_2d_multisample          (gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage2DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format)      , 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), 
            fixed);
    }
    static void texture_storage_3d_multisample          (gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage3DMultisample(
            gl::to_underlying       (texture)     , 
            static_cast<gl::sizei_t>(samples)     , gl::to_underlying       (format), 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z), 
            fixed);
    }
    static void invalidate_texture_image                (gl::handle_t texture, gl::uint32_t level)
    {
        glInvalidateTexImage(
            gl::to_underlying       (texture), 
            static_cast<gl::int32_t>(level));
    }
    static void invalidate_texture_sub_image            (gl::handle_t texture, gl::uint32_t level, gl::volume_t region)
    {
        glInvalidateTexSubImage(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z));
    }
    static void clear_texture_image                     (gl::handle_t texture, glf::Texture::BaseFormat format, glf::Texture::Type type, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glClearTexImage(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level), 
            gl::to_underlying(format) , gl::to_underlying       (type) , data.data());
    }
    static void clear_texture_sub_image(gl::handle_t texture, glf::Texture::BaseFormat format, glf::Texture::Type type, gl::uint32_t level, gl::volume_t region, std::span<const gl::byte_t> data)
    {
        glClearTexSubImage(
            gl::to_underlying       (texture)        , static_cast<gl::int32_t>(level)          , 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), static_cast<gl::int32_t>(region.origin.z), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y), static_cast<gl::sizei_t>(region.extent.z), 
            gl::to_underlying       (format)         , gl::to_underlying       (type)           , data.data());
    }



    //Chapter 9 - FrameBuffers and FrameBuffer Objects
    static auto create_frame_buffer                     ()
    {
        gl::handle_t handle{};
        glCreateFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static auto create_frame_buffer                     (gl::count_t count)
    {
        std::vector<gl::handle_t> handles(count);
        glCreateFramebuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data()));

        return handles;
    }
    static void delete_frame_buffer                     (gl::handle_t frameBuffer)
    {
        glDeleteFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&frameBuffer));
    }
    static void delete_frame_buffers                    (std::span<const gl::handle_t> frameBuffers)
    {
        glDeleteFramebuffers(static_cast<gl::sizei_t>(frameBuffers.size()), gl::to_underlying_ptr(frameBuffers.data()));
    }
    static void bind_frame_buffer                       (gl::handle_t frameBuffer, glf::FrameBuffer::Target target)
    {
        glBindFramebuffer(gl::to_underlying(target), gl::to_underlying(frameBuffer));
    }
    template<glf::FrameBuffer::Parameter P>
    static void frame_buffer_parameter                  (gl::handle_t frameBuffer, gl::uint32_t value)
    {
        const auto& frame_buffer_parameter_i = [](gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter, gl::uint32_t value)
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
        else static_assert(false, "Invalid FrameBuffer Parameter!");
    }
    static auto create_render_buffer                    ()
    {
        gl::handle_t handle{};
        glCreateRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static auto create_render_buffers                   (gl::count_t count)
    {
        std::vector<gl::handle_t> handles(count);
        glCreateRenderbuffers(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data()));

        return handles;
    }
    static void delete_render_buffer                    (gl::handle_t renderBuffer)
    {
        glDeleteRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&renderBuffer));
    }
    static void delete_render_buffers                   (std::span<const gl::handle_t> renderBuffers)
    {
        glDeleteRenderbuffers(static_cast<gl::sizei_t>(renderBuffers.size()), gl::to_underlying_ptr(renderBuffers.data()));
    }
    static void render_buffer_storage                   (gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(
            gl::to_underlying       (renderBuffer),
            gl::to_underlying       (format)      ,
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    static void render_buffer_storage_multisample       (gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions, gl::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(
            gl::to_underlying       (renderBuffer),
            static_cast<gl::sizei_t>(samples)     ,
            gl::to_underlying       (format)      ,
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    static void frame_buffer_render_buffer              (gl::handle_t frameBuffer, gl::handle_t renderBuffer, glf::FrameBuffer::Attachment attachment)
    {
        glNamedFramebufferRenderbuffer(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(glf::RenderBuffer::Target::RenderBuffer), gl::to_underlying(renderBuffer));
    }
    static void frame_buffer_texture                    (gl::handle_t frameBuffer, gl::handle_t texture, glf::FrameBuffer::Attachment attachment, gl::uint32_t level)
    {
        glNamedFramebufferTexture(
            gl::to_underlying       (frameBuffer), gl::to_underlying(attachment), 
            gl::to_underlying       (texture)    , 
            static_cast<gl::int32_t>(level));
    }
    static void frame_buffer_texture_layer              (gl::handle_t frameBuffer, gl::handle_t texture, glf::FrameBuffer::Attachment attachment, gl::uint32_t level, gl::uint32_t layer)
    {
        glNamedFramebufferTextureLayer(
            gl::to_underlying       (frameBuffer), gl::to_underlying       (attachment), 
            gl::to_underlying       (texture)    , 
            static_cast<gl::int32_t>(level)      , static_cast<gl::int32_t>(layer));
    }
    static void texture_barrier                         ()
    {
        glTextureBarrier();
    }
    static auto check_frame_buffer_status               (gl::handle_t frameBuffer)
    {
        return static_cast<glf::FrameBuffer::Status>(glCheckNamedFramebufferStatus(gl::to_underlying(frameBuffer), gl::to_underlying(glf::FrameBuffer::Target::Write)));
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    static void patch_parameter                         (glp::patch_parameter_t value)
    {
        if (std::holds_alternative<glp::patch_vertices>(value))
        {
            const auto& v = std::get<glp::patch_vertices>(value);
            glPatchParameteri(gl::to_underlying(glf::Patch::Parameter::PatchVertices), v.value);
        }
        if (std::holds_alternative<glp::patch_default_outer_level>(value))
        {
            const auto& v = std::get<glp::patch_default_outer_level>(value);
            glPatchParameterfv(gl::to_underlying(glf::Patch::Parameter::PatchDefaultOuterLevel), v.value.data());
        }
        if (std::holds_alternative<glp::patch_default_inner_level>(value))
        {
            const auto& v = std::get<glp::patch_default_inner_level>(value);
            glPatchParameterfv(gl::to_underlying(glf::Patch::Parameter::PatchDefaultInnerLevel), v.value.data());
        }
    }
    template<typename T, gl::uint32_t N, gl::bool_t NORM = gl::False>
    static void vertex_attribute                        (gl::index_t index, const gl::Vector<T, N>& value)
    {
        const auto& maximumAttributes = gl::get_value<glf::Data::MaximumVertexAttributes>();
        if (std::cmp_greater(index, maximumAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };
        
             if constexpr (std::is_same_v<T, gl::int16_t>   and N == 1 and NORM == gl::False) glVertexAttrib1s  (index, value.x);
        else if constexpr (std::is_same_v<T, gl::int16_t>   and N == 2 and NORM == gl::False) glVertexAttrib2s  (index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::int16_t>   and N == 3 and NORM == gl::False) glVertexAttrib3s  (index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::int16_t>   and N == 4 and NORM == gl::False) glVertexAttrib4s  (index, value.x, value.y, value.z, value.w);

        else if constexpr (std::is_same_v<T, gl::float32_t> and N == 1 and NORM == gl::False) glVertexAttrib1f  (index, value.x);
        else if constexpr (std::is_same_v<T, gl::float32_t> and N == 2 and NORM == gl::False) glVertexAttrib2f  (index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::float32_t> and N == 3 and NORM == gl::False) glVertexAttrib3f  (index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::float32_t> and N == 4 and NORM == gl::False) glVertexAttrib4f  (index, value.x, value.y, value.z, value.w);

        else if constexpr (std::is_same_v<T, gl::float64_t> and N == 1 and NORM == gl::False) glVertexAttribL1d (index, value.x);
        else if constexpr (std::is_same_v<T, gl::float64_t> and N == 2 and NORM == gl::False) glVertexAttribL2d (index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::float64_t> and N == 3 and NORM == gl::False) glVertexAttribL3d (index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::float64_t> and N == 4 and NORM == gl::False) glVertexAttribL4d (index, value.x, value.y, value.z, value.w);
                                                                                                           
        else if constexpr (std::is_same_v<T, gl::uint8_t>   and N == 4 and NORM == gl::True ) glVertexAttrib4Nub(index, value.x, value.y, value.z, value.w);

        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 1 and NORM == gl::False) glVertexAttribI1i (index, value.x);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 2 and NORM == gl::False) glVertexAttribI2i (index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 3 and NORM == gl::False) glVertexAttribI3i (index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 4 and NORM == gl::False) glVertexAttribI4i (index, value.x, value.y, value.z, value.w);

        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 1 and NORM == gl::False) glVertexAttribI1ui(index, value.x);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 2 and NORM == gl::False) glVertexAttribI2ui(index, value.x, value.y);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 3 and NORM == gl::False) glVertexAttribI3ui(index, value.x, value.y, value.z);
        else if constexpr (std::is_same_v<T, gl::int32_t>   and N == 4 and NORM == gl::False) glVertexAttribI4ui(index, value.x, value.y, value.z, value.w);

        else    static_assert(false, "The given input does not match a valid Vertex Attribute function!");
    }
    static auto create_vertex_array                     ()
    {
        gl::handle_t handle{};
        glCreateVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static auto create_vertex_arrays                    (gl::count_t count)
    {
        std::vector<gl::handle_t> handles(count);
        glCreateVertexArrays(static_cast<gl::sizei_t>(handles.size()), gl::to_underlying_ptr(handles.data()));

        return handles;
    }
    static void delete_vertex_array                     (gl::handle_t vertexArray)
    {
        glDeleteVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&vertexArray));
    }
    static void delete_vertex_arrays                    (std::span<const gl::handle_t> vertexArrays)
    {
        glDeleteVertexArrays(static_cast<gl::sizei_t>(vertexArrays.size()), gl::to_underlying_ptr(vertexArrays.data()));
    }
    static void bind_vertex_array                       (gl::handle_t vertexArray)
    {
        glBindVertexArray(gl::to_underlying(vertexArray));
    }
    static void vertex_array_element_buffer             (gl::handle_t vertexArray, gl::handle_t elementBuffer)
    {
        glVertexArrayElementBuffer(gl::to_underlying(vertexArray), gl::to_underlying(elementBuffer));
    }
    static void vertex_array_attribute_format           (gl::handle_t vertexArray, gl::index_t attribute, gl::offset_t offset, glf::VertexArray::Attribute::Type type, gl::uint32_t count, gl::bool_t normalized = gl::False)
    {
        const auto& maximumVertexAttributes = gl::get_value<glf::Data::MaximumVertexAttributes>();
        if (std::cmp_greater(attribute, maximumVertexAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };

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
                glVertexArrayAttribIFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
                break;
            }

            case glf::VertexArray::Attribute::Type::Float                                : 
            case glf::VertexArray::Attribute::Type::HalfFloat                            : 
            case glf::VertexArray::Attribute::Type::Fixed                                : 
            {
                glVertexArrayAttribFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), normalized, static_cast<gl::uint32_t>(offset));
                break;
            }

            case glf::VertexArray::Attribute::Type::Double                               : 
            {
                glVertexArrayAttribLFormat(gl::to_underlying(vertexArray), attribute, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
                break;
            }
        }
    }
    static void vertex_array_vertex_buffer              (gl::handle_t vertexArray, gl::handle_t buffer, gl::binding_t binding, gl::size_t stride, gl::index_t index)
    {
        glVertexArrayVertexBuffer(gl::to_underlying(vertexArray), gl::to_underlying(binding), gl::to_underlying(buffer), static_cast<gl::offset_t>(index), static_cast<gl::sizei_t>(stride));
    }
    static void vertex_array_vertex_buffers             (gl::handle_t vertexArray)
    {
        //glVertexArrayVertexBuffers(gl::to_underlying(vertexArray));
    }
    static void vertex_array_attribute_binding          (gl::handle_t vertexArray, gl::index_t attribute, gl::binding_t binding)
    {
        glVertexArrayAttribBinding(gl::to_underlying(vertexArray), attribute, gl::to_underlying(binding));
    }
    static void enable_vertex_array_attribute           (gl::handle_t vertexArray, gl::index_t index)
    {
        glEnableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }
    static void disable_vertex_array_attribute          (gl::handle_t vertexArray, gl::index_t index)
    {
        glDisableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }
    static void vertex_array_binding_divisor            (gl::handle_t vertexArray, gl::binding_t binding, gl::uint32_t divisor)
    {
        glVertexArrayBindingDivisor(gl::to_underlying(vertexArray), gl::to_underlying(binding), divisor);
    }
    static void primitive_restart_index                 (gl::index_t index)
    {
        glPrimitiveRestartIndex(index);
    }
    static void draw_arrays                             (glf::Draw::Mode mode, gl::range_t range)
    {
        glDrawArrays(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count));
    }
    static void draw_arrays_instanced                   (glf::Draw::Mode mode, gl::range_t range, gl::count_t instances)
    {
        glDrawArraysInstanced(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count), static_cast<gl::sizei_t>(instances));
    }
    static void draw_arrays_instanced_base_instance     (glf::Draw::Mode mode, gl::range_t range, gl::count_t instances, gl::index_t base)
    {
        glDrawArraysInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::int32_t>(range.index), static_cast<gl::sizei_t>(range.count), static_cast<gl::sizei_t>(instances), base);
    }
    static void draw_elements                           (glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count)
    {
        glDrawElements(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr);
    }
    static void draw_elements_instanced                 (glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count, gl::count_t instances)
    {
        glDrawElementsInstanced(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instances));
    }
    static void draw_elements_instanced_base_instance   (glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count, gl::count_t instances, gl::index_t base)
    {
        glDrawElementsInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instances), base);
    }
    static void begin_conditional_render                (gl::handle_t query, glf::Query::Mode mode)
    {
        glBeginConditionalRender(gl::to_underlying(query), gl::to_underlying(mode));
    }
    static void end_conditional_render                  ()
    {
        glEndConditionalRender();
    }



    //Chapter 11 - Programmable Vertex Processing
    static void validate_program                        (gl::handle_t program)
    {
        glValidateProgram(gl::to_underlying(program));
    }
    static void validate_program_pipeline               (gl::handle_t pipeline)
    {
        glValidateProgramPipeline(gl::to_underlying(pipeline));
    }



    //Chapter 13 - Fixed-Function Vertex Post-Processing
    static void provoking_vertex                        (glf::ProvokingVertex::Mode mode)
    {
        glProvokingVertex(gl::to_underlying(mode));
    }
    static void clip_control                            (glf::Clip::Origin origin, glf::Clip::DepthMode mode)
    {
        glClipControl(gl::to_underlying(origin), gl::to_underlying(mode));
    }
    static void depth_range_array_value                 (gl::index_t index, std::span<const gl::Vector2d> ranges)
    {
        glDepthRangeArrayv(index, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    static void depth_range_indexed                     (gl::index_t index, const gl::Vector2d& range)
    {
        glDepthRangeIndexed(index, range.x, range.y);
    }
    static void depth_range                             (const gl::Vector2f& range)
    {
        glDepthRangef(range.x, range.y);
    }
    static void viewport_array_value                    (gl::index_t index, std::span<const gl::Vector2f> ranges)
    {
        glViewportArrayv(index, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    static void viewport_indexed                        (gl::index_t index, const gl::region_t<gl::float32_t, 2> region)
    {
        glViewportIndexedf(index, region.origin.x, region.origin.y, region.extent.x, region.extent.y);
    }
    static void viewport                                (gl::area_t region)
    {
        glViewport(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }



    //Chapter 14 - Fixed-Function Primitive Assembly and Rasterization
    static auto get_multisample_value                   (gl::index_t index)
    {
        gl::Vector2f value{};
        glGetMultisamplefv(gl::to_underlying(glf::Multisample::Parameter::SamplePosition), index, glm::value_ptr(value));

        return value;
    }
    static void minimum_sample_shading                  (gl::float32_t value)
    {
        glMinSampleShading(value);
    }
    static void point_size                              (gl::float32_t size)
    {
        glPointSize(size);
    }
    static void point_parameter                         (glp::point_parameter_t parameter)
    {
        if (std::holds_alternative<glp::fade_threshold_size>(parameter))
        {
            const auto& p = std::get<glp::fade_threshold_size>(parameter);
            glPointParameterf(gl::to_underlying(glf::Point::Parameter::FadeThresholdSize), p.value);
        }
        if (std::holds_alternative<glp::sprite_coordinate_origin>(parameter))
        {
            const auto& p = std::get<glp::sprite_coordinate_origin>(parameter);
            glPointParameteri(gl::to_underlying(glf::Point::Parameter::SpriteCoordinateOrigin), gl::to_underlying(p.value));
        }
    }
    static void line_width                              (gl::float32_t value)
    {
        glLineWidth(value);
    }
    static void front_face                              (glf::Orientation orientation)
    {
        glFrontFace(gl::to_underlying(orientation));
    }
    static void cull_face                               (glf::Culling::Facet face)
    {
        glCullFace(gl::to_underlying(face));
    }
    static void polygon_mode                            (glf::Polygon::Mode mode)
    {
        glPolygonMode(gl::to_underlying(glf::Polygon::Face::FrontAndBack), gl::to_underlying(mode));
    }
    static void polygon_offset_clamp                    (gl::float32_t factor, gl::float32_t units, gl::float32_t clamp)
    {
        glPolygonOffsetClamp(factor, units, clamp);
    }
    static void scissor_array                           (gl::index_t index, std::span<const gl::uint32_t, 4> values)
    {
        glScissorArrayv(
            index, 
            static_cast<gl::sizei_t>            (values.size()), 
            reinterpret_cast<const gl::int32_t*>(values.data()));
    }
    static void scissor_indexed                         (gl::index_t index, gl::area_t region)
    {
        glScissorIndexed(
            index, 
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    static void scissor                                 (gl::area_t region)
    {
        glScissor(
            static_cast<gl::int32_t>(region.origin.x), static_cast<gl::int32_t>(region.origin.y), 
            static_cast<gl::sizei_t>(region.extent.x), static_cast<gl::sizei_t>(region.extent.y));
    }
    static void sample_coverage                         (gl::float32_t value, gl::bool_t invert)
    {
        glSampleCoverage(value, invert);
    }
    static void sample_mask_index                       (gl::uint32_t mask, gl::uint32_t value)
    {
        glSampleMaski(mask, value);
    }



    //Chapter 17 - Writing Fragments and Samples to the Framebuffer
    static void stencil_function                        (glf::Stencil::Function function, gl::uint32_t reference, gl::uint32_t mask)
    {
        glStencilFunc(gl::to_underlying(function), static_cast<gl::int32_t>(reference), mask);
    }
    static void stencil_function_separate               (glf::Stencil::Face face, glf::Stencil::Function function, gl::uint32_t reference, gl::uint32_t mask)
    {
        glStencilFuncSeparate(gl::to_underlying(face), gl::to_underlying(function), static_cast<gl::int32_t>(reference), mask);
    }
    static void stencil_operation                       (glf::Stencil::Action stencil, glf::Stencil::Action depth, glf::Stencil::Action depthStencil)
    {
        glStencilOp(gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }
    static void stencil_operation_separate              (glf::Stencil::Face face, glf::Stencil::Action stencil, glf::Stencil::Action depth, glf::Stencil::Action depthStencil)
    {
        glStencilOpSeparate(gl::to_underlying(face), gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }
    static void depth_function                          (glf::DepthFunction function)
    {
        glDepthFunc(gl::to_underlying(function));
    }
    static void blend_equation                          (glf::Blending::Equation equation)
    {
        glBlendEquation(gl::to_underlying(equation));
    }
    static void blend_equation_indexed                  (gl::index_t index, glf::Blending::Equation equation)
    {
        glBlendEquationi(index, gl::to_underlying(equation));
    }
    static void blend_equation_separate                 (glf::Blending::Equation equationRGB, glf::Blending::Equation equationAlpha)
    {
        glBlendEquationSeparate(gl::to_underlying(equationRGB), gl::to_underlying(equationAlpha));
    }
    static void blend_equation_separate_indexed         (gl::index_t index, glf::Blending::Equation color, glf::Blending::Equation alpha)
    {
        glBlendEquationSeparatei(index, gl::to_underlying(color), gl::to_underlying(alpha));
    }
    static void blend_function                          (glf::Blending::Factor source, glf::Blending::Factor destination)
    {
        glBlendFunc(gl::to_underlying(source), gl::to_underlying(destination));
    }
    static void blend_function_indexed                  (gl::index_t index, glf::Blending::Factor sourceColor, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationColor, glf::Blending::Factor destinationAlpha)
    {
        glBlendFuncSeparatei(index, gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    static void blend_function_separate                 (glf::Blending::Factor sourceColor, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationColor, glf::Blending::Factor destinationAlpha)
    {
        glBlendFuncSeparate(gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    static void blend_function_separate_indexed         (gl::index_t index, glf::Blending::Factor sourceColor, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationColor, glf::Blending::Factor destinationAlpha)
    {
        glBlendFuncSeparatei(index, gl::to_underlying(sourceColor), gl::to_underlying(destinationColor), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    static void blend_color                             (const gl::Vector4f& color)
    {
        glBlendColor(color.r, color.g, color.b, color.a);
    }
    static void logical_pixel_operation                 (glf::LogicalPixelOperation operation)
    {
        glLogicOp(gl::to_underlying(operation));
    }
    static void frame_buffer_draw_buffer                (gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferDrawBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    static void frame_buffer_draw_buffers               (gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Source> sources)
    {
        glNamedFramebufferDrawBuffers(gl::to_underlying(frameBuffer), static_cast<gl::sizei_t>(sources.size()), gl::to_underlying_ptr(sources.data()));
    }
    static void color_mask                              (const gl::Vector4b& mask)
    {
        glColorMask(mask.r, mask.g, mask.b, mask.a);
    }
    static void color_mask_index                        (gl::handle_t buffer, const gl::Vector4b& mask)
    {
        glColorMaski(gl::to_underlying(buffer), mask.r, mask.g, mask.b, mask.a);
    }
    static void depth_mask                              (gl::bool_t flag)
    {
        glDepthMask(flag);
    }
    static void stencil_mask                            (gl::uint32_t mask)
    {
        glStencilMask(mask);
    }
    static void stencil_mask_separate                   (glf::Stencil::Face face, gl::uint32_t mask)
    {
        glStencilMaskSeparate(gl::to_underlying(face), mask);
    }
    static void clear                                   (glf::Buffer::Mask mask)
    {
        glClear(gl::to_underlying(mask));
    }
    static void clear_color                             (const gl::Vector4f& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    static void clear_depth                             (gl::float32_t depth)
    {
        glClearDepthf(depth);
    }
    static void clear_stencil                           (gl::index_t index)
    {
        glClearStencil(static_cast<gl::int32_t>(index));
    }
    static void clear_frame_buffer_value                (gl::handle_t frameBuffer, glp::clear_t parameter, gl::index_t index)
    {
        const auto& clear_frame_buffer_iv  = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::index_t index, const gl::int32_t* value)
            {
                glClearNamedFramebufferiv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        const auto& clear_frame_buffer_uiv = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::index_t index, const gl::uint32_t* value)
            {
                glClearNamedFramebufferuiv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        const auto& clear_frame_buffer_fv  = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::index_t index, const gl::float32_t* value)
            {
                glClearNamedFramebufferfv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
            };
        const auto& clear_frame_buffer_fi  = [](gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::index_t index, gl::float32_t depth, gl::int32_t stencil)
            {
                glClearNamedFramebufferfi(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), depth, stencil);
            };

        if (std::holds_alternative<glp::color_index>     (parameter))
        {
            const auto& p = std::get<glp::color_index>(parameter);

            if (std::holds_alternative<gl::Vector4i>(p.color))
            {
                const auto& c = std::get<gl::Vector4i>(p.color);
                clear_frame_buffer_iv(frameBuffer, glf::FrameBuffer::Attachment::Color0, p.index, glm::value_ptr(c));
            }
            if (std::holds_alternative<gl::Vector4u>(p.color))
            {
                const auto& c = std::get<gl::Vector4u>(p.color);
                clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::Color0, p.index, glm::value_ptr(c));
            }
            if (std::holds_alternative<gl::Vector4f>(p.color))
            {
                const auto& c = std::get<gl::Vector4f>(p.color);
                clear_frame_buffer_fv(frameBuffer, glf::FrameBuffer::Attachment::Color0, p.index, glm::value_ptr(c));
            }
        }
        if (std::holds_alternative<glp::depth>       (parameter))
        {
            const auto& p = std::get<glp::depth>(parameter);

            if (std::holds_alternative<gl::int32_t>(p.value))
            {
                const auto& v = std::get<gl::int32_t>(p.value);
                clear_frame_buffer_iv(frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &v);
            }
            if (std::holds_alternative<gl::uint32_t>(p.value))
            {
                const auto& v = std::get<gl::uint32_t>(p.value);
                clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &v);
            }
            if (std::holds_alternative<gl::float32_t>(p.value))
            {
                const auto& v = std::get<gl::float32_t>(p.value);
                clear_frame_buffer_fv(frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &v);
            }
        }
        if (std::holds_alternative<glp::stencil>     (parameter))
        {
            const auto& p = std::get<glp::stencil>(parameter);

            if (std::holds_alternative<gl::int32_t>(p.value))
            {
                const auto& v = std::get<gl::int32_t>(p.value);
                clear_frame_buffer_iv(frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &v);
            }
            if (std::holds_alternative<gl::uint32_t>(p.value))
            {
                const auto& v = std::get<gl::uint32_t>(p.value);
                clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &v);
            }
            if (std::holds_alternative<gl::float32_t>(p.value))
            {
                const auto& v = std::get<gl::float32_t>(p.value);
                clear_frame_buffer_fv(frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &v);
            }
        }
        if (std::holds_alternative<glp::depthstencil>(parameter))
        {
            const auto& p = std::get<glp::depthstencil>(parameter);
            clear_frame_buffer_fi(frameBuffer, glf::FrameBuffer::Attachment::DepthStencil, gl::uint32_t{ 0u }, p.depth, p.stencil);
        }
    }
    static void invalidate_frame_buffer_data            (gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Attachment> attachments)
    {
        glInvalidateNamedFramebufferData(
            gl::to_underlying       (frameBuffer)        , 
            static_cast<gl::sizei_t>(attachments.size()) , 
            gl::to_underlying_ptr   (attachments.data()));
    }
    static void invalidate_frame_buffer_sub_data        (gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Attachment> attachments, gl::area_t region)
    {
        glInvalidateNamedFramebufferSubData(
            gl::to_underlying       (frameBuffer)       , 
            static_cast<gl::sizei_t>(attachments.size()), gl::to_underlying_ptr   (attachments.data()), 
            static_cast<gl::int32_t>(region.origin.x)   , static_cast<gl::int32_t>(region.origin.y)   , 
            static_cast<gl::sizei_t>(region.extent.x)   , static_cast<gl::sizei_t>(region.extent.y));
    }



    //Chapter 18 - Reading and Copying Pixels
    static void frame_buffer_read_buffer                (gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferReadBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    template<glf::PixelData::Format F, glf::PixelData::Type T>
    static void read_pixels                             (gl::area_t region)
    {
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
    static void clamp_color                             (gl::bool_t value)
    {
        glClampColor(gl::to_underlying(glf::ClampColor::Read), static_cast<gl::enum_t>(value));
    }
    static void blit_frame_buffer                       (gl::handle_t source, gl::handle_t destination, glf::Buffer::Mask mask, glf::FrameBuffer::Filter filter, gl::area_t sourceRegion, gl::area_t destinationRegion)
    {
        glBlitNamedFramebuffer(
            gl::to_underlying       (source)                    ,
            gl::to_underlying       (destination)               ,
            static_cast<gl::int32_t>(sourceRegion     .origin.x), static_cast<gl::int32_t>(sourceRegion     .origin.y), static_cast<gl::int32_t>(sourceRegion     .extent.x), static_cast<gl::int32_t>(sourceRegion     .extent.y),
            static_cast<gl::int32_t>(destinationRegion.origin.x), static_cast<gl::int32_t>(destinationRegion.origin.y), static_cast<gl::int32_t>(destinationRegion.extent.x), static_cast<gl::int32_t>(destinationRegion.extent.y),
            gl::to_underlying       (mask)                      , gl::to_underlying       (filter));
    }
    static void copy_image_sub_data                     (gl::handle_t source, gl::handle_t destination, glf::Texture::Target sourceTarget, glf::Texture::Target destinationTarget, gl::hypervolume_t sourceRegion, gl::hypervolume_t destinationRegion)
    {
        glCopyImageSubData(
            gl::to_underlying       (source                    ), gl::to_underlying       (sourceTarget              ), static_cast<gl::int32_t>(sourceRegion     .extent.w), 
            static_cast<gl::int32_t>(sourceRegion     .origin.x), static_cast<gl::int32_t>(sourceRegion     .origin.y), static_cast<gl::int32_t>(sourceRegion     .origin.z), 
            gl::to_underlying       (destination               ), gl::to_underlying       (destinationTarget         ), static_cast<gl::int32_t>(destinationRegion.extent.w), 
            static_cast<gl::int32_t>(destinationRegion.origin.x), static_cast<gl::int32_t>(destinationRegion.origin.y), static_cast<gl::int32_t>(destinationRegion.origin.z), 
            static_cast<gl::sizei_t>(sourceRegion     .extent.x), static_cast<gl::sizei_t>(sourceRegion     .extent.y), static_cast<gl::sizei_t>(sourceRegion     .extent.z));
    }



    //Chapter 19 - Compute Shaders
    static void dispatch_compute                        (glp::dispatch_t dispatch)
    {
        if (std::holds_alternative<gl::Vector3u>(dispatch))
        {
            const auto& group = std::get<gl::Vector3u>(dispatch);
            glDispatchCompute(group.x, group.y, group.z);
        }
        if (std::holds_alternative<gl::offset_t>(dispatch))
        {
            const auto& offset = std::get<gl::offset_t>(dispatch);
            glDispatchComputeIndirect(offset);
        }
    }



    //Chapter 20 - Debug Output
    static void debug_message_callback                  (debug_callback_t callback, const void* parameter = nullptr)
    {
        glDebugMessageCallback(callback, parameter);
    }
    static void debug_message_control                   (glf::Debug::Source source, glf::Debug::Type type, glf::Debug::Severity severity, gl::bool_t state)
    {
        glDebugMessageControl(gl::to_underlying(source), gl::to_underlying(type), gl::to_underlying(severity), 0, nullptr, state);
    }
    static void debug_message_insert                    (gl::uint32_t id, glf::Debug::Type type, glf::Debug::Severity severity, const std::string& message)
    {
        glDebugMessageInsert(
            gl::to_underlying(glf::Debug::Source::Application), 
            gl::to_underlying(type), id, gl::to_underlying(severity), 
            static_cast<gl::sizei_t>(message.length()), message.data());
    }
    static void push_debug_group                        (gl::uint32_t id, const std::string& message)
    {
        const auto* cstr = message.c_str();
        glPushDebugGroup(gl::to_underlying(glf::Debug::Source::Application), id, -1, cstr);
    }
    static void pop_debug_group                         ()
    {
        glPopDebugGroup();
    }
    static void object_label                            (gl::handle_t handle, glf::Object::Type type, const std::string& label)
    {
        const auto* cstr = label.c_str();
        glObjectLabel(gl::to_underlying(type), gl::to_underlying(handle), -1, cstr);
    }
    static void object_pointer_label                    (gl::sync_t sync, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glObjectPtrLabel(sync, -1, cstr);
    }
    

    
    //Chapter 21 - Special Functions
    static void hint                                    (glf::Hint::Target target, glf::Hint::Mode mode)
    {
        glHint(gl::to_underlying(target), gl::to_underlying(mode));
    }


    


#ifdef GL_EXTENDED

#endif
#ifdef GL_LEGACY
    static auto get_error()
    {
        return static_cast<glf::Error::Flag>(glGetError());
    }
    static auto is_sync(gl::sync_t sync)
    {
        return static_cast<gl::bool_t>(glIsSync(sync));
    }
#endif
}
