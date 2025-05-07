#pragma once

#include "stdafx.hpp"

#include "Flags.hpp"
#include "Library.hpp"
#include "Mapping.hpp"
#include "Types.hpp"
#include "Parameters.hpp"
#include "Concepts.hpp"

namespace fox::gfx::api::gl
{
    //OpenGL wrapper library
    // 
    //This library has the following goals:
    //    * Provide a more modern and accessible interface
    //    * Wrap around existing OpenGL functions, allowing easy implementation of custom logic
    //    * Compile/Runtime input validation and safety
    // 
    //Functions are ordered according to their appearance in the OpenGL 4.6 core specification
    //https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf





    //Chapter 22 - Context State Queries
    static void get_boolean_v            (glf::Data data, std::optional<gl::uint32_t> index, gl::bool_t*    value)
    {
        if   (index.has_value()) glGetBooleani_v(gl::to_underlying(data), index.value(), value);
        else                     glGetBooleanv  (gl::to_underlying(data),                value);
    }
    static void get_integer32_v          (glf::Data data, std::optional<gl::uint32_t> index, gl::int32_t*   value)
    {
        if   (index.has_value()) glGetIntegeri_v(gl::to_underlying(data), index.value(), value);
        else                     glGetIntegerv  (gl::to_underlying(data),                value);
    }
    static void get_integer64_v          (glf::Data data, std::optional<gl::uint32_t> index, gl::int64_t*   value)
    {
        if   (index.has_value()) glGetInteger64i_v(gl::to_underlying(data), index.value(), value);
        else                     glGetInteger64v  (gl::to_underlying(data),                value);
    }
    static void get_float32_v            (glf::Data data, std::optional<gl::uint32_t> index, gl::float32_t* value)
    {
        if   (index.has_value()) glGetFloati_v(gl::to_underlying(data), index.value(), value);
        else                     glGetFloatv  (gl::to_underlying(data),                value);
    }
    static void get_float64_v            (glf::Data data, std::optional<gl::uint32_t> index, gl::float64_t* value)
    {
        if   (index.has_value()) glGetDoublei_v(gl::to_underlying(data), index.value(), value);
        else                     glGetDoublev  (gl::to_underlying(data),                value);
    }
    static auto is_enabled               (glf::Feature feature, std::optional<gl::uint32_t> index)
    {
        gl::bool_t value{};

        if   (index.has_value()) value = glIsEnabledi(gl::to_underlying(feature), index.value());
        else                     value = glIsEnabled (gl::to_underlying(feature)               );

        return value;
    }
    static auto get_pointer_v            (glf::Callback::Pointer pointer)
    {
        gl::void_t* value{};
        glGetPointerv(gl::to_underlying(pointer), &value);

        return value;
    }
    static auto get_string               (glf::Connection connection, std::optional<gl::uint32_t> index)
    {
        const gl::uint8_t* value{};

        if   (index.has_value()) value = glGetStringi(gl::to_underlying(connection), index.value());
        else                     value = glGetString (gl::to_underlying(connection)               );

        return std::string{ reinterpret_cast<const gl::char_t*>(value) };
    }
    static void get_internal_format_iv   (gl::enum_t target, gl::enum_t internalformat, gl::enum_t pname, gl::sizei_t bufsize)
    {
        //@OpenGL devs: This function is plain ridiculous
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }
    static void get_transform_feedback_iv(gl::handle_t transformFeedback, glf::TransformFeedback::Property property, gl::int32_t* value)
    {
        glGetTransformFeedbackiv(gl::to_underlying(transformFeedback), gl::to_underlying(property), value);
    }
    
    template<glf::Data D>
    static auto get_value(std::optional<gl::uint32_t> index = {})
    {
        const auto& _bool_t          = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::bool_t value{};
                gl::get_boolean_v(data, index, &value);

                return value;
            };
        const auto& _int32_t         = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::int32_t value{};
                gl::get_integer32_v(data, index, &value);

                return value;
            };
        const auto& _i64_t           = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::int64_t value{};
                gl::get_integer64_v(data, index, &value);

                return value;
            };
        const auto& _uint32_t        = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::int32_t value{};
                gl::get_integer32_v(data, index, &value);

                return static_cast<gl::uint32_t>(value);
            };
        const auto& _uint64_t        = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::int64_t value{};
                gl::get_integer64_v(data, index, &value);

                return static_cast<gl::uint64_t>(value);
            };
        const auto& _float32_t       = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::float32_t value{};
                gl::get_float32_v(data, index, &value);

                return value;
            };
        const auto& _float64_t       = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::float64_t value{};
                gl::get_float64_v(data, index, &value);

                return value;
            };
                                    
        const auto& _vector4b        = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::Vector4b value{};
                gl::get_boolean_v(data, index, glm::value_ptr(value));

                return value;
            };
        const auto& _vector2i        = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::Vector2i value{};
                gl::get_integer32_v(data, index, glm::value_ptr(value));

                return value;
            };
        const auto& _vector2f        = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::Vector2f value{};
                gl::get_float32_v(data, index, glm::value_ptr(value));

                return value;
            };
        const auto& _vector4f        = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::Vector4f value{};
                gl::get_float32_v(data, index, glm::value_ptr(value));

                return value;
            };
        const auto& _vector2d        = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::Vector2d value{};
                gl::get_float64_v(data, index, glm::value_ptr(value));

                return value;
            };
                                           
        const auto& _handle_t        = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::int32_t value{};
                gl::get_integer32_v(data, index, &value);

                return gl::handle_t{ static_cast<gl::uint32_t>(value) };
            };
        const auto& _bitfield_t      = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::int32_t value{};
                gl::get_integer32_v(data, index, &value);

                return static_cast<gl::bitfield_t>(value);
            };

        const auto& _binary_format_t = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                throw std::logic_error{ "The method or operation has not been implemented!" };
                return 0;

                //std::vector<gl::enum_t> formats{};

                //const auto& binaryFormatAmount = gl::query_value<glf::Data::NumberProgramBinaryFormats>(index);
                //formats.resize(binaryFormatAmount);

                //gl::get_integer32_v(data, index, gl::to_underlying_ptr(formats.data()));

                //return formats;
            };
        const auto& _area_t          = [](glf::Data data, std::optional<gl::uint32_t> index)
            {
                gl::area_t<gl::uint32_t> value{ {} };
                gl::get_integer32_v(data, index, reinterpret_cast<gl::int32_t*>(&value));

                return value;
            };



        if constexpr (D == glf::Data::AliasedLineWidthRange)                            return _vector2f(D, index);
        if constexpr (D == glf::Data::BlendColor)                                       return _vector4f(D, index);
        if constexpr (D == glf::Data::BlendDestinationAlpha)                            return glf::Blending::Factor           { _uint32_t(D, index) };
        if constexpr (D == glf::Data::BlendDestinationRGB)                              return glf::Blending::Factor           { _uint32_t(D, index) };
        if constexpr (D == glf::Data::BlendEquationAlpha)                               return glf::Blending::Equation         { _uint32_t(D, index) };
        if constexpr (D == glf::Data::BlendEquationRGB)                                 return glf::Blending::Equation         { _uint32_t(D, index) };
        if constexpr (D == glf::Data::BlendSourceAlpha)                                 return glf::Blending::Factor           { _uint32_t(D, index) };
        if constexpr (D == glf::Data::BlendSourceRGB)                                   return glf::Blending::Factor           { _uint32_t(D, index) };
        if constexpr (D == glf::Data::ColorClearValue)                                  return _vector4f(D, index);
        if constexpr (D == glf::Data::ColorWritemask)                                   return _vector4b(D, index);
        if constexpr (D == glf::Data::ContextFlags)                                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::CopyReadBufferBinding)                            return _handle_t(D, index);
        if constexpr (D == glf::Data::CopyWriteBufferBinding)                           return _handle_t(D, index);
        if constexpr (D == glf::Data::CurrentProgram)                                   return _handle_t(D, index);
        if constexpr (D == glf::Data::DebugGroupStackDepth)                             return _uint32_t(D, index);
        if constexpr (D == glf::Data::DebugLoggedMessages)                              return _uint32_t(D, index);
        if constexpr (D == glf::Data::DepthClearValue)                                  return _float64_t(D, index);
        if constexpr (D == glf::Data::DepthFunction)                                    return glf::DepthFunction              { _uint32_t(D, index) };
        if constexpr (D == glf::Data::DepthRange)                                       return _vector2d(D, index);
        if constexpr (D == glf::Data::DispatchIndirectBufferBinding)                    return _handle_t(D, index);
        if constexpr (D == glf::Data::DoubleBuffer)                                     return _bool_t  (D, index);
        if constexpr (D == glf::Data::DrawBuffer)                                       return glf::FrameBuffer::Source        { _uint32_t(D, index) };
        if constexpr (D == glf::Data::DrawFramebufferBinding)                           return _handle_t(D, index);
        if constexpr (D == glf::Data::DrawIndirectBufferBinding)                        return _handle_t(D, index);
        if constexpr (D == glf::Data::FragmentShaderDerivativeHint)                     return glf::Hint::Mode                 { _uint32_t(D, index) };
        if constexpr (D == glf::Data::ImplementationColorReadFormat)                    return glf::PixelData::Format          { _uint32_t(D, index) };
        if constexpr (D == glf::Data::ImplementationColorReadType)                      return glf::PixelData::Type            { _uint32_t(D, index) };
        if constexpr (D == glf::Data::IndexArrayBufferBinding)                          return _handle_t(D, index);
        if constexpr (D == glf::Data::LayerProvokingVertex)                             return glf::ProvokingVertex::Mode      { _uint32_t(D, index) };
        if constexpr (D == glf::Data::LineSmoothHint)                                   return glf::Hint::Mode                 { _uint32_t(D, index) };
        if constexpr (D == glf::Data::LineWidth)                                        return _float64_t(D, index);
        if constexpr (D == glf::Data::LogicOperationMode)                               return glf::Logic::Operation           { _uint32_t(D, index) };
        if constexpr (D == glf::Data::MajorVersion)                                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::Maximum3DTextureSize)                             return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumArrayTextureLayers)                        return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumClipDistances)                             return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumColorTextureSamples)                       return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCombinedAtomicCounters)                    return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCombinedComputeUniformComponents)          return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCombinedFragmentUniformComponents)         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCombinedGeometryUniformComponents)         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCombinedShaderStorageBlocks)               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCombinedTextureImageUnits)                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCombinedUniformBlocks)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCombinedVertexUniformComponents)           return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeAtomicCounterBuffers)               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeAtomicCounters)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeShaderStorageBlocks)                return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeTextureImageUnits)                  return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeUniformBlocks)                      return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeUniformComponents)                  return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupCount)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupInvocations)               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumComputeWorkGroupSize)                      return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumCubemapTextureSize)                        return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumDebugGroupStackDepth)                      return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumDebugMessageLength)                        return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumDepthTextureSamples)                       return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumDrawBuffers)                               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumDualSourceDrawBuffers)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumElementIndex)                              return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFragmentAtomicCounters)                    return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFragmentInputComponents)                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFragmentShaderStorageBlocks)               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFragmentUniformBlocks)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFragmentUniformComponents)                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFragmentUniformVectors)                    return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFrameBufferHeight)                         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFrameBufferLayers)                         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFrameBufferSamples)                        return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumFrameBufferWidth)                          return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumGeometryAtomicCounters)                    return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumGeometryInputComponents)                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumGeometryOutputComponents)                  return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumGeometryShaderStorageBlocks)               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumGeometryTextureImageUnits)                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumGeometryUniformBlocks)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumGeometryUniformComponents)                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumIndexElements)                             return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumIntegerSamples)                            return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumLabelLength)                               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumProgramTexelOffset)                        return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumRectangleTextureSize)                      return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumRenderBufferSize)                          return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumSampleMaskWords)                           return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumServerWaitTimeout)                         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumShaderStorageBufferBindings)               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumTessellationControlAtomicCounters)         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumTessellationControlShaderStorageBlocks)    return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumTessellationEvaluationAtomicCounters)      return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumTessellationEvaluationShaderStorageBlocks) return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumTextureBufferSize)                         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumTextureImageUnits)                         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumTextureLODBias)                            return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumTextureSize)                               return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumUniformBlockSize)                          return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumUniformBufferBindings)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumUniformLocations)                          return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVaryingComponents)                         return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVaryingFloats)                             return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVaryingVectors)                            return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexAtomicCounters)                      return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexAttributeBindings)                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexAttributeRelativeOffset)             return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexAttributes)                          return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexElements)                            return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexOutputComponents)                    return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexShaderStorageBlocks)                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexTextureImageUnits)                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexUniformBlocks)                       return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexUniformComponents)                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumVertexUniformVectors)                      return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumViewportDimensions)                        return _uint32_t(D, index);
        if constexpr (D == glf::Data::MaximumViewports)                                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::MinimumMapBufferAlignment)                        return _uint32_t(D, index);
        if constexpr (D == glf::Data::MinimumProgramTexelOffset)                        return _int32_t(D, index);
        if constexpr (D == glf::Data::MinorVersion)                                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::NumberCompressedTextureFormats)                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::NumberExtensions)                                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::NumberProgramBinaryFormats)                       return _uint32_t(D, index);
        if constexpr (D == glf::Data::NumberShaderBinaryFormats)                        return _uint32_t(D, index);
        if constexpr (D == glf::Data::PackAlignment)                                    return _uint32_t(D, index);
        if constexpr (D == glf::Data::PackImageHeight)                                  return _uint32_t(D, index);
        if constexpr (D == glf::Data::PackRowLength)                                    return _uint32_t(D, index);
        if constexpr (D == glf::Data::PackSkipImages)                                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::PackSkipPixels)                                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::PackSkipRows)                                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::PackSwapBytes)                                    return _bool_t(D, index);
        if constexpr (D == glf::Data::PixelPackBufferBinding)                           return _handle_t(D, index);
        if constexpr (D == glf::Data::PixelUnpackBufferBinding)                         return _handle_t(D, index);
        if constexpr (D == glf::Data::PointFadeThresholdSize)                           return _float32_t(D, index);
        if constexpr (D == glf::Data::PointSize)                                        return _float32_t(D, index);
        if constexpr (D == glf::Data::PointSizeGranularity)                             return _float32_t(D, index);
        if constexpr (D == glf::Data::PointSizeRange)                                   return _vector2f(D, index);
        if constexpr (D == glf::Data::PolygonOffsetFactor)                              return _float32_t(D, index);
        if constexpr (D == glf::Data::PolygonOffsetUnits)                               return _float32_t(D, index);
        if constexpr (D == glf::Data::PolygonSmoothHint)                                return glf::Hint::Mode                 { _uint32_t(D, index) };
        if constexpr (D == glf::Data::PrimitiveRestartIndex)                            return _uint32_t(D, index);
        if constexpr (D == glf::Data::ProgramBinaryFormats)                             return _binary_format_t(D, index);
        if constexpr (D == glf::Data::ProgramPipelineBinding)                           return _handle_t(D, index);
        if constexpr (D == glf::Data::ProvokingVertex)                                  return glf::ProvokingVertex::Mode      { _uint32_t(D, index) };
        if constexpr (D == glf::Data::QueryBufferBinding)                               return _handle_t(D, index);
        if constexpr (D == glf::Data::ReadBuffer)                                       return glf::FrameBuffer::Source        { _uint32_t(D, index) };
        if constexpr (D == glf::Data::ReadFrameBufferBinding)                           return _handle_t(D, index);
        if constexpr (D == glf::Data::RenderbufferBinding)                              return _handle_t(D, index);
        if constexpr (D == glf::Data::SampleBuffers)                                    return _uint32_t(D, index);
        if constexpr (D == glf::Data::SampleCoverageInvert)                             return _bool_t(D, index);
        if constexpr (D == glf::Data::SampleCoverageValue)                              return _float32_t(D, index);
        if constexpr (D == glf::Data::SampleMaskValue)                                  return _bitfield_t(D, index);
        if constexpr (D == glf::Data::SamplerBinding)                                   return _handle_t(D, index);
        if constexpr (D == glf::Data::Samples)                                          return _bitfield_t(D, index);
        if constexpr (D == glf::Data::ScissorBox)                                       return _area_t(D, index);
        if constexpr (D == glf::Data::ShaderCompiler)                                   return _bool_t(D, index);
        if constexpr (D == glf::Data::ShaderStorageBufferBinding)                       return _handle_t(D, index);
        if constexpr (D == glf::Data::ShaderStorageBufferOffsetAlignment)               return _uint32_t(D, index);
        if constexpr (D == glf::Data::ShaderStorageBufferSize)                          return _uint64_t(D, index);
        if constexpr (D == glf::Data::ShaderStorageBufferStart)                         return _uint64_t(D, index);
        if constexpr (D == glf::Data::SmoothLineWidthGranularity)                       return _float32_t(D, index);
        if constexpr (D == glf::Data::SmoothLineWidthRange)                             return _vector2f (D, index);
        if constexpr (D == glf::Data::StencilBackFail)                                  return glf::Stencil::Action            { _uint32_t(D, index) };
        if constexpr (D == glf::Data::StencilBackFunction)                              return glf::Stencil::Function          { _uint32_t(D, index) };
        if constexpr (D == glf::Data::StencilBackPassDepthFail)                         return glf::Stencil::Action            { _uint32_t(D, index) };
        if constexpr (D == glf::Data::StencilBackPassDepthPass)                         return glf::Stencil::Action            { _uint32_t(D, index) };
        if constexpr (D == glf::Data::StencilBackReference)                             return _int32_t(D, index);
        if constexpr (D == glf::Data::StencilBackValueMask)                             return _uint32_t(D, index);
        if constexpr (D == glf::Data::StencilBackWritemask)                             return _uint32_t(D, index);
        if constexpr (D == glf::Data::StencilClearValue)                                return _uint32_t(D, index);
        if constexpr (D == glf::Data::StencilFail)                                      return glf::Stencil::Action            { _uint32_t(D, index) };
        if constexpr (D == glf::Data::StencilFunction)                                  return glf::Stencil::Function          { _uint32_t(D, index) };
        if constexpr (D == glf::Data::StencilPassDepthFail)                             return glf::Stencil::Action            { _uint32_t(D, index) };
        if constexpr (D == glf::Data::StencilPassDepthPass)                             return glf::Stencil::Action            { _uint32_t(D, index) };
        if constexpr (D == glf::Data::StencilReference)                                 return _int32_t(D, index);
        if constexpr (D == glf::Data::StencilValueMask)                                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::StencilWritemask)                                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::Stereo)                                           return _bool_t(D, index);
        if constexpr (D == glf::Data::SubpixelBits)                                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::TextureBinding1D)                                 return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBinding1DArray)                            return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBinding2D)                                 return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBinding2DArray)                            return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBinding2DMultisample)                      return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBinding2DMultisampleArray)                 return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBinding3D)                                 return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBindingBuffer)                             return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBindingCubemap)                            return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBindingRectangle)                          return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBufferBinding)                             return _handle_t(D, index);
        if constexpr (D == glf::Data::TextureBufferOffsetAlignment)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::TextureCompressionHint)                           return glf::Hint::Mode                 { _uint32_t(D, index) };
        if constexpr (D == glf::Data::Timestamp)                                        return _i64_t(D, index);
        if constexpr (D == glf::Data::TransformFeedbackBufferBinding)                   return _handle_t(D, index);
        if constexpr (D == glf::Data::TransformfeedbackBufferSize)                      return _uint64_t(D, index);
        if constexpr (D == glf::Data::TransformFeedbackBufferStart)                     return _uint64_t(D, index);
        if constexpr (D == glf::Data::UniformBufferBinding)                             return _handle_t(D, index);
        if constexpr (D == glf::Data::UniformBufferOffsetAlignment)                     return _uint32_t(D, index);
        if constexpr (D == glf::Data::UniformBufferSize)                                return _uint64_t(D, index);
        if constexpr (D == glf::Data::UniformBufferStart)                               return _uint64_t(D, index);
        if constexpr (D == glf::Data::UnpackAlignment)                                  return _uint32_t(D, index);
        if constexpr (D == glf::Data::UnpackImageHeight)                                return _uint32_t(D, index);
        if constexpr (D == glf::Data::UnpackRowLength)                                  return _uint32_t(D, index);
        if constexpr (D == glf::Data::UnpackSkipImages)                                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::UnpackSkipPixels)                                 return _uint32_t(D, index);
        if constexpr (D == glf::Data::UnpackSkipRows)                                   return _uint32_t(D, index);
        if constexpr (D == glf::Data::UnpackSwapBytes)                                  return _bool_t(D, index);
        if constexpr (D == glf::Data::VertexArrayBinding)                               return _handle_t(D, index);
        if constexpr (D == glf::Data::VertexBindingDivisor)                             return _uint32_t(D, index);
        if constexpr (D == glf::Data::VertexBindingOffset)                              return _uint32_t(D, index);
        if constexpr (D == glf::Data::VertexBindingStride)                              return _uint32_t(D, index);
        if constexpr (D == glf::Data::Viewport)                                         return _area_t(D, index);
        if constexpr (D == glf::Data::ViewportBoundsRange)                              return _vector2i(D, index);
        if constexpr (D == glf::Data::ViewportIndexProvokingVertex)                     return glf::ProvokingVertex::Convention{ _uint32_t(D, index) };
        if constexpr (D == glf::Data::ViewportSubPixelBits)                             return _uint32_t(D, index);
    }



    //Chapter 4 - Event Model
    static auto get_sync_iv                  (gl::sync_t sync, glf::Synchronization::Property property, gl::int32_t* value)
    {
        glGetSynciv(sync, gl::to_underlying(property), sizeof(gl::int32_t), nullptr, value);
    }
    static auto get_query_iv                 (glf::Query::Target target, glf::Query::Symbol symbol, std::optional<gl::uint32_t> index)
    {
        gl::int32_t value{};
        glGetQueryIndexediv(gl::to_underlying(target), index.value_or(gl::uint32_t{ 0 }), gl::to_underlying(symbol), &value);

        return value;
    }
    static auto get_query_object_iv          (gl::handle_t query, glf::Query::Parameter parameter, gl::int32_t* value)
    {
        glGetQueryObjectiv(gl::to_underlying(query), gl::to_underlying(parameter), value);
    }
    static auto get_query_object_uiv         (gl::handle_t query, glf::Query::Parameter parameter, gl::uint32_t* value)
    {
        glGetQueryObjectuiv(gl::to_underlying(query), gl::to_underlying(parameter), value);
    }
    static auto get_query_object_i64v        (gl::handle_t query, glf::Query::Parameter parameter, gl::int64_t* value)
    {
        glGetQueryObjecti64v(gl::to_underlying(query), gl::to_underlying(parameter), value);
    }
    static auto get_query_object_ui64v       (gl::handle_t query, glf::Query::Parameter parameter, gl::uint64_t* value)
    {
        glGetQueryObjectui64v(gl::to_underlying(query), gl::to_underlying(parameter), value);
    }
    static void get_query_buffer_object_iv   (gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
    {
        glGetQueryBufferObjectiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
    }
    static void get_query_buffer_object_uiv  (gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
    {
        glGetQueryBufferObjectuiv(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
    }
    static void get_query_buffer_object_i64v (gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
    {
        glGetQueryBufferObjecti64v(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
    }
    static void get_query_buffer_object_ui64v(gl::handle_t query, gl::handle_t buffer, glf::Query::Parameter parameter, gl::offset_t offset)
    {
        glGetQueryBufferObjectui64v(gl::to_underlying(query), gl::to_underlying(buffer), gl::to_underlying(parameter), offset);
    }

    template<glf::Synchronization::Property P>
    static auto get_sync_value(gl::sync_t sync)
    {
        const auto& _sync_object_type      = [](gl::sync_t sync, glf::Synchronization::Property property)
            {
                gl::int32_t value{};
                gl::get_sync_iv(sync, property, &value);

                return glf::Synchronization::Object::Type{ static_cast<gl::uint32_t>(value) };
            };
        const auto& _sync_object_status    = [](gl::sync_t sync, glf::Synchronization::Property property)
            {
                gl::int32_t value{};
                gl::get_sync_iv(sync, property, &value);

                return glf::Synchronization::Object::Status{ static_cast<gl::uint32_t>(value) };
            };
        const auto& _sync_object_condition = [](gl::sync_t sync, glf::Synchronization::Property property)
            {
                gl::int32_t value{};
                gl::get_sync_iv(sync, property, &value);

                return glf::Synchronization::Object::Condition{ static_cast<gl::uint32_t>(value) };
            };



        if constexpr (P == glf::Synchronization::Property::Type)      return _sync_object_type     (sync, P);
        if constexpr (P == glf::Synchronization::Property::Status)    return _sync_object_status   (sync, P);
        if constexpr (P == glf::Synchronization::Property::Condition) return _sync_object_condition(sync, P);
        if constexpr (P == glf::Synchronization::Property::Flags)     return gl::bitfield_t{};
    }
    template<glf::Query::Parameter P>
    static auto get_query_object_value(gl::handle_t query)
    {
        const auto& _bool_t   = []()
            {
                gl::int32_t value{};
                gl::get_query_object_iv(query, P, &value);

                return gl::bool_t{ value };
            };
        const auto& _int32_t  = []()
            {
                gl::int32_t value{};
                gl::get_query_object_iv(query, P, &value);

                return value;
            };
        const auto& _uint32_t = []()
            {
                gl::uint32_t value{};
                gl::get_query_object_uiv(query, P, &value);

                return value;
            };



        if constexpr (P == glf::Query::Parameter::Result)          return _uint32_t(query, P);
        if constexpr (P == glf::Query::Parameter::ResultNoWait)    return _uint32_t(query, P);
        if constexpr (P == glf::Query::Parameter::ResultAvailable) return _bool_t  (query, P);
        if constexpr (P == glf::Query::Parameter::Target)          return _int32_t (query, P);
    }
    template<glf::Query::Parameter P>
    static void get_query_buffer_object_value(gl::handle_t query, gl::handle_t buffer, gl::offset_t offset)
    {
        if constexpr (P == glf::Query::Parameter::Result)          gl::get_query_buffer_object_uiv(query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::ResultNoWait)    gl::get_query_buffer_object_uiv(query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::ResultAvailable) gl::get_query_buffer_object_iv (query, buffer, P, offset);
        if constexpr (P == glf::Query::Parameter::Target)          gl::get_query_buffer_object_iv (query, buffer, P, offset);
    }



    //Chapter 6 - Buffer Objects
    static auto get_buffer_parameter_iv  (gl::handle_t buffer, glf::Buffer::Parameter parameter, gl::int32_t* value)
    {
        glGetNamedBufferParameteriv(gl::to_underlying(buffer), gl::to_underlying(parameter), value);
    }
    static auto get_buffer_parameter_i64v(gl::handle_t buffer, glf::Buffer::Parameter parameter, gl::int64_t* value)
    {
        glGetNamedBufferParameteri64v(gl::to_underlying(buffer), gl::to_underlying(parameter), value);
    }

    template<glf::Buffer::Parameter P>
    static auto get_buffer_parameter_value(gl::handle_t buffer)
    {
        const auto& _bool_t          = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int32_t value{};
                gl::get_buffer_parameter_iv(buffer, parameter, &value);

                return static_cast<gl::bool_t>(value);
            };
        const auto& _uint64_t        = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int64_t value{};
                gl::get_buffer_parameter_i64v(buffer, parameter, &value);

                return static_cast<gl::uint64_t>(value);
            };
        const auto& _access_t        = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int32_t value{};
                gl::get_buffer_parameter_iv(buffer, parameter, &value);

                return static_cast<glf::Buffer::Mapping::Access>(value);
            };
        const auto& _access_flags_t  = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int32_t value{};
                gl::get_buffer_parameter_iv(buffer, parameter, &value);

                return static_cast<glf::Buffer::Mapping::AccessFlags>(value);
            };
        const auto& _storage_flags_t = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int32_t value{};
                gl::get_buffer_parameter_iv(buffer, parameter, &value);

                return static_cast<glf::Buffer::StorageFlags>(value);
            };
        const auto& _usage_t         = [](gl::handle_t buffer, glf::Buffer::Parameter parameter)
            {
                gl::int32_t value{};
                gl::get_buffer_parameter_iv(buffer, parameter, &value);

                return static_cast<glf::Buffer::Usage>(value);
            };



        if constexpr (P == glf::Buffer::Parameter::Access)       return _access_t       (buffer, P);
        if constexpr (P == glf::Buffer::Parameter::AccessFlags)  return _access_flags_t (buffer, P);
        if constexpr (P == glf::Buffer::Parameter::Immutable)    return _bool_t         (buffer, P);
        if constexpr (P == glf::Buffer::Parameter::IsMapped)     return _bool_t         (buffer, P);
        if constexpr (P == glf::Buffer::Parameter::MapLength)    return _uint64_t       (buffer, P);
        if constexpr (P == glf::Buffer::Parameter::MapOffset)    return _uint64_t       (buffer, P);
        if constexpr (P == glf::Buffer::Parameter::Size)         return _uint64_t       (buffer, P);
        if constexpr (P == glf::Buffer::Parameter::StorageFlags) return _storage_flags_t(buffer, P);
        if constexpr (P == glf::Buffer::Parameter::Usage)        return _usage_t        (buffer, P);
    }



    //Chapter 7 - Programs and Shaders
    static auto get_shader_iv              (gl::handle_t shader, glf::Shader::Parameter parameter)
    {
        gl::int32_t value{};
        glGetShaderiv(gl::to_underlying(shader), gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_program_iv             (gl::handle_t program, glf::Program::Parameter parameter)
    {
        gl::int32_t value{};
        glGetProgramiv(gl::to_underlying(program), gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_program_pipeline_iv    (gl::handle_t pipeline, glf::Program::Pipeline::Property property)
    {
        gl::int32_t value{};
        glGetProgramPipelineiv(gl::to_underlying(pipeline), gl::to_underlying(property), &value);

        return value;
    }
    static auto get_attached_shaders       (gl::handle_t program)
    {
        std::vector<gl::handle_t> shaders{};

        const auto& attachedShaders = gl::get_program_iv(program, glf::Program::Parameter::AttachedShaders);
        shaders.resize(attachedShaders);

        glGetAttachedShaders(gl::to_underlying(program), attachedShaders, nullptr, gl::to_underlying_ptr(shaders.data()));

        return shaders;
    }
    static auto shader_info_log            (gl::handle_t shader)
    {
        std::string infoLog{};

        const auto& infoLogLength = get_shader_iv(shader, glf::Shader::Parameter::InfoLogLength);
        infoLog.resize(infoLogLength);

        glGetShaderInfoLog(gl::to_underlying(shader), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto program_info_log           (gl::handle_t program)
    {
        std::string infoLog{};

        const auto& infoLogLength = gl::get_program_iv(program, glf::Program::Parameter::InfoLogLength);
        infoLog.resize(infoLogLength);

        glGetProgramInfoLog(gl::to_underlying(program), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto pipeline_info_log          (gl::handle_t pipeline)
    {
        std::string infoLog{};

        const auto& infoLogLength = gl::get_program_pipeline_iv(pipeline, glf::Program::Pipeline::Property::InfoLogLength);
        infoLog.resize(infoLogLength);

        glGetProgramPipelineInfoLog(gl::to_underlying(pipeline), infoLogLength, nullptr, infoLog.data());

        if (!infoLog.empty()) infoLog.resize(infoLog.size() - 1u);

        return infoLog;
    }
    static auto get_shader_source          (gl::handle_t shader)
    {
        std::string source{};
        gl::sizei_t length{};

        const auto& sourceLength = gl::get_shader_iv(shader, glf::Shader::Parameter::SourceLength);
        source.resize(sourceLength);

        glGetShaderSource(gl::to_underlying(shader), sourceLength, &length, source.data());

        if (!source.empty()) source.resize(source.size() - 1u);

        return source;
    }
    static auto get_shader_precision_format(glf::Shader::Type type, glf::Shader::PrecisionFormat format)
    {
        std::array<gl::int32_t, 2> range{};
        gl::int32_t                precision{};

        glGetShaderPrecisionFormat(gl::to_underlying(type), gl::to_underlying(format), range.data(), &precision);

        struct result_t{ std::array<gl::int32_t, 2> range{}; gl::int32_t precision{}; };
        return result_t{ range, precision };
    }
    static auto get_uniform_iv             (gl::handle_t program, gl::int32_t location, gl::sizei_t amount)
    {
        std::vector<gl::int32_t> values{};

        values.resize(amount);

        glGetnUniformiv(gl::to_underlying(program), location, amount, values.data());

        return values;
    }
    static auto get_uniform_uiv            (gl::handle_t program, gl::int32_t location, gl::sizei_t amount)
    {
        std::vector<gl::uint32_t> values{};

        values.resize(amount);

        glGetnUniformuiv(gl::to_underlying(program), location, amount, values.data());

        return values;
    }
    static auto get_uniform_fv             (gl::handle_t program, gl::int32_t location, gl::sizei_t amount)
    {
        std::vector<gl::float32_t> values{};

        values.resize(amount);

        glGetnUniformfv(gl::to_underlying(program), location, amount, values.data());

        return values;
    }
    static auto get_uniform_f64v           (gl::handle_t program, gl::int32_t location, gl::sizei_t amount)
    {
        std::vector<gl::float64_t> values{};

        values.resize(amount);

        glGetnUniformdv(gl::to_underlying(program), location, amount, values.data());

        return values;
    }
    static auto get_uniform_subroutine_uiv (glf::Shader::Type type, gl::int32_t location)
    {
        gl::uint32_t value{};
        glGetUniformSubroutineuiv(gl::to_underlying(type), location, &value);

        return value;
    }
    static auto get_program_stage_iv(gl::handle_t program, glf::Shader::Type type, glf::Program::StageProperty property)
    {
        gl::int32_t value{};
        glGetProgramStageiv(gl::to_underlying(program), gl::to_underlying(type), gl::to_underlying(property), &value);

        return value;
    }






    //Chapter 8 - Textures and Samplers
    static auto get_sampler_parameter_iv (gl::handle_t sampler, glf::Sampler::Parameter parameter)
    {
        gl::int32_t value{};
        glGetSamplerParameteriv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_sampler_parameter_uiv(gl::handle_t sampler, glf::Sampler::Parameter parameter)
    {
        gl::uint32_t value{};
        glGetSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_sampler_parameter_fv (gl::handle_t sampler, glf::Sampler::Parameter parameter)
    {
        gl::float32_t value{};
        glGetSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), &value);

        return value;
    }



    static void texture_parameter(gl::handle_t texture, glf::Texture::Parameter parameter, gl::texture_v value) //TODO: implement further
    {
        if (std::holds_alternative<glf::Texture::MinificationFilter>(value))
        {
            const auto& v = std::get<glf::Texture::MinificationFilter>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), gl::to_underlying(parameter), gl::to_underlying(v));

            return;
        }
        if (std::holds_alternative<glf::Texture::MagnificationFilter>(value))
        {
            const auto& v = std::get<glf::Texture::MagnificationFilter>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), gl::to_underlying(parameter), gl::to_underlying(v));

            return;
        }
        if (std::holds_alternative<glf::Texture::Wrapping>(value))
        {
            const auto& v = std::get<glf::Texture::Wrapping>(value);
            glTextureParameteri(static_cast<gl::uint32_t>(texture), gl::to_underlying(parameter), gl::to_underlying(v));

            return;
        }

        throw std::invalid_argument{ "Invalid Texture Parameter!" };
    }












    static auto get_program_interface_iv(gl::handle_t program, glf::Program::Interface interface, glf::Program::Property property)
    {
        gl::int32_t value{};
        glGetProgramInterfaceiv(gl::to_underlying(program), gl::to_underlying(interface), gl::to_underlying(property), &value);

        return value;
    };
    static auto get_program_resource_index(gl::handle_t program, glf::Program::Interface interface, const std::string& identifier)
    {
        const auto* cstr   = identifier.c_str();
        gl::uint32_t value = glGetProgramResourceIndex(gl::to_underlying(program), gl::to_underlying(interface), cstr);

        return value;
    }
    static auto get_program_resource_name(gl::handle_t program, glf::Program::Interface interface, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_interface_iv(program, interface, glf::Program::Property::MaximumNameLength);
        name.resize(maximumLength);

        glGetProgramResourceName(gl::to_underlying(program), gl::to_underlying(interface), index, maximumLength, &length, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);
        
        return name;
    }
    static auto get_program_resource_iv(gl::handle_t program, glf::Program::Interface interface, std::span<const glf::Program::Resource> resources, gl::uint32_t index)
    {
        std::vector<gl::int32_t> values{};

        values.resize(resources.size());

        glGetProgramResourceiv(
            gl::to_underlying(program),
            gl::to_underlying(interface), index,
            static_cast<gl::sizei_t>(resources.size()), gl::to_underlying_ptr(resources.data()),
            static_cast<gl::sizei_t>(values.size()), nullptr, values.data());

        return values;
    }
    static auto get_program_resource_location(gl::handle_t program, glf::Program::Interface interface, const std::string& identifier)
    {
        const auto* cstr  = identifier.c_str();
        gl::int32_t value = glGetProgramResourceLocation(gl::to_underlying(program), gl::to_underlying(interface), cstr);

        return value;
    }
    static auto get_program_resource_location_index(gl::handle_t program, const std::string& identifier)
    {
        const auto* cstr  = identifier.c_str();
        gl::int32_t value = glGetProgramResourceLocationIndex(gl::to_underlying(program), gl::to_underlying(glf::Program::Interface::ProgramOutput), cstr);

        return value;
    }

    static auto get_active_uniforms_iv(gl::handle_t program, glf::Uniform::Property property, std::span<const gl::uint32_t> indices)
    {
        std::vector<gl::int32_t> values{};

        values.resize(indices.size());

        glGetActiveUniformsiv(gl::to_underlying(program), static_cast<gl::sizei_t>(indices.size()), indices.data(), gl::to_underlying(property), values.data());

        return values;
    };

    static auto get_active_uniform_block_iv(gl::handle_t program, glf::UniformBlock::Info info, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetActiveUniformBlockiv(gl::to_underlying(program), index, gl::to_underlying(info), &value);

        return value;
    };

    static auto get_active_atomic_counter_buffer_iv(gl::handle_t program, glf::AtomicCounterBuffer::Info info, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetActiveAtomicCounterBufferiv(gl::to_underlying(program), index, gl::to_underlying(info), &value);

        return value;
    };

    static auto get_active_subroutine_uniform_iv(gl::handle_t program, glf::Shader::Type type, glf::Shader::SubroutineParameter parameter, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetActiveSubroutineUniformiv(gl::to_underlying(program), gl::to_underlying(type), index, gl::to_underlying(parameter), &value);

        return value;
    }

    static auto uniform_subroutines_uiv(glf::Shader::Type type, std::span<const gl::uint32_t> indices)
    {
        glUniformSubroutinesuiv(gl::to_underlying(type), static_cast<gl::sizei_t>(indices.size()), indices.data());
    }









    //Chapter 8 - Textures and Samplers
    static void sampler_parameter_iv     (gl::handle_t sampler, glf::Sampler::Parameter parameter, std::span<const gl::int32_t>   values)
    {
        glSamplerParameterIiv(gl::to_underlying(sampler), gl::to_underlying(parameter), values.data());
    }
    static void sampler_parameter_uiv    (gl::handle_t sampler, glf::Sampler::Parameter parameter, std::span<const gl::uint32_t>  values)
    {
        glSamplerParameterIuiv(gl::to_underlying(sampler), gl::to_underlying(parameter), values.data());
    }
    static void sampler_parameter_fv     (gl::handle_t sampler, glf::Sampler::Parameter parameter, std::span<const gl::float32_t> values)
    {
        glSamplerParameterfv(gl::to_underlying(sampler), gl::to_underlying(parameter), values.data());
    }



    static auto get_frame_buffer_parameter_iv           (gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter)
    {
        gl::int32_t value{};
        glGetNamedFramebufferParameteriv(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto                           get_frame_buffer_attachment_parameter_iv(gl::framebuffer_v frameBuffer)
    {
        if (std::holds_alternative<gl::framebuffer_p>(frameBuffer))
        {
            //const auto& f = std::get<gl::framebuffer_p>(frameBuffer);
            //glGetNamedFramebufferAttachmentParameteriv(gl::to_underlying(f.frameBuffer), gl::to_underlying(f.attachment), );
        }
    }
    static auto                           get_render_buffer_parameter_iv          ()
    {
        throw std::logic_error{ "The method or operation has not been implemented!" };
    }

    static auto vertex_array_iv              (gl::handle_t vertexArray, glf::VertexArray::Parameter parameter)
    {
        gl::int32_t value{};
        glGetVertexArrayiv(gl::to_underlying(vertexArray), gl::to_underlying(parameter), &value);

        return value;
    }
    static auto get_vertex_array_indexed_iv  (gl::handle_t vertexArray, glf::VertexArray::IndexedParameter parameter, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetVertexArrayIndexediv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_vertex_array_indexed_i64v(gl::handle_t vertexArray, glf::VertexArray::IndexedParameter parameter, gl::uint32_t index)
    {
        gl::int64_t value{};
        glGetVertexArrayIndexed64iv(gl::to_underlying(vertexArray), index, gl::to_underlying(parameter), &value);

        return value;
    };
    
    static auto get_vertex_attribute_iv (glf::VertexAttribute::Parameter parameter, gl::uint32_t index)
    {
        gl::int32_t value{};
        glGetVertexAttribIiv(index, gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_vertex_attribute_uiv(glf::VertexAttribute::Parameter parameter, gl::uint32_t index)
    {
        gl::uint32_t value{};
        glGetVertexAttribIuiv(index, gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_vertex_attribute_fv (glf::VertexAttribute::Parameter parameter, gl::uint32_t index)
    {
        gl::float32_t value{};
        glGetVertexAttribfv(index, gl::to_underlying(parameter), &value);

        return value;
    };
    static auto get_vertex_attribute_dv (glf::VertexAttribute::Parameter parameter, gl::uint32_t index)
    {
        gl::float64_t value{};
        glGetVertexAttribLdv(index, gl::to_underlying(parameter), &value);

        return value;
    };















    //Chapter 2 - OpenGL Fundamentals
    static auto get_graphics_reset_status()
    {
        gl::enum_t value{};
        value = glGetGraphicsResetStatus();

        return glf::Error::GraphicsResetStatus{ value };
    }
    static void flush()
    {
        glFlush();
    }
    static void finish()
    {
        glFinish();
    }



    //Chapter 4 - Event Model
    static void fence_sync      ()
    {
        glFenceSync(gl::to_underlying(glf::Synchronization::Object::Condition::GPUCommandsComplete), gl::bitfield_t{ 0 });
    }
    static void delete_sync     (gl::sync_t sync)
    {
        if (sync) glDeleteSync(sync);
    }
    static auto client_wait_sync(gl::sync_t sync, gl::uint64_t timeout)
    {
        gl::enum_t value{};
        value = glClientWaitSync(sync, gl::to_underlying(glf::Synchronization::FlushingBehavior::Commands), timeout);

        return glf::Synchronization::Status{ value };
    }
    static void server_wait_sync(gl::sync_t sync)
    {
        glWaitSync(sync, gl::bitfield_t{ 0 }, gl::to_underlying(glf::Synchronization::Timeout::Ignored));
    }

    static auto create_query    (glf::Query::Target target)
    {
        gl::handle_t handle{};
        glCreateQueries(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_query    (gl::handle_t query)
    {
        if (query != gl::NullObject) glDeleteQueries(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&query));
    }
    static void begin_query     (gl::handle_t query, glf::Query::Target target, std::optional<gl::uint32_t> index = std::nullopt)
    {
        glBeginQueryIndexed(gl::to_underlying(target), index.value_or(gl::uint32_t{ 0 }), gl::to_underlying(query));
    }
    static void end_query       (glf::Query::Target target, std::optional<gl::uint32_t> index = std::nullopt)
    {
        glEndQueryIndexed(gl::to_underlying(target), index.value_or(gl::uint32_t{ 0 }));
    }

    static void query_counter   (gl::handle_t query)
    {
        glQueryCounter(gl::to_underlying(query), gl::to_underlying(glf::Query::Counter::Timestamp));
    }



    //Chapter 6 - Buffer Objects
    static auto create_buffer            ()
    {
        gl::handle_t handle{};
        glCreateBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_buffer            (gl::handle_t buffer)
    {
        if (buffer != gl::NullObject) glDeleteBuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&buffer));
    }
    static void bind_buffer_range        (gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::uint32_t index, gl::byterange_t range)
    {
        glBindBufferRange(gl::to_underlying(target), index, gl::to_underlying(buffer), range.offset, range.size);
    }
    static void bind_buffer_base         (gl::handle_t buffer, glf::Buffer::BaseTarget target, gl::uint32_t index)
    {
        glBindBufferBase(gl::to_underlying(target), index, gl::to_underlying(buffer));
    }
    
    static void buffer_storage           (gl::handle_t buffer, glf::Buffer::StorageFlags flags, gl::size_t size)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), size, nullptr, gl::to_underlying(flags));
    }
    template<typename T>                  
    static void buffer_storage           (gl::handle_t buffer, glf::Buffer::StorageFlags flags, std::span<const T> data)
    {
        glNamedBufferStorage(gl::to_underlying(buffer), static_cast<gl::size_t>(data.size_bytes()), data.data(), gl::to_underlying(flags));
    }
    template<typename T>
    static void buffer_data              (gl::handle_t buffer, gl::offset_t offset, std::span<const T> data)
    {
        glNamedBufferSubData(gl::to_underlying(buffer), offset, static_cast<gl::size_t>(data.size_bytes()), data.data());
    }
    static void clear_buffer_data        (gl::handle_t buffer, glf::DataType type, glf::Buffer::BaseFormat baseFormat, glf::Buffer::Format format, gl::byterange_t range, const void* data)
    {
        glClearNamedBufferSubData(gl::to_underlying(buffer), gl::to_underlying(format), range.offset, range.size, gl::to_underlying(baseFormat), gl::to_underlying(type), data);
    }
    
    template<typename T>
    static auto map_buffer               (gl::handle_t buffer, glf::Buffer::Mapping::Access access)
    {
        return reinterpret_cast<T*>(glMapNamedBuffer(gl::to_underlying(buffer), gl::to_underlying(access)));
    }
    template<typename T>
    static auto map_buffer_range         (gl::handle_t buffer, glf::Buffer::Mapping::AccessFlags access, gl::size_t size, gl::offset_t offset)
    {
        reinterpret_cast<T*>(glMapNamedBufferRange(gl::to_underlying(buffer), offset, size, gl::to_underlying(access)));
    }
    static void flush_mapped_buffer_range(gl::handle_t buffer, gl::byterange_t range)
    {
        glFlushMappedNamedBufferRange(gl::to_underlying(buffer), range.offset, range.size);
    }
    static void unmap_buffer             (gl::handle_t buffer)
    {
        if (!glUnmapNamedBuffer(gl::to_underlying(buffer))) throw std::runtime_error{ "Buffer data store may be undefined!" };
    }
    static void invalidate_buffer_data   (gl::handle_t buffer, std::optional<gl::byterange_t> range)
    {
        if   (range.has_value()) glInvalidateBufferSubData(gl::to_underlying(buffer), range->offset, range->size);
        else                     glInvalidateBufferSubData(gl::to_underlying(buffer), 0            , gl::get_buffer_parameter_value<glf::Buffer::Parameter::Size>(buffer));
    }
    
    static void copy_buffer_sub_data     (gl::handle_t source, gl::handle_t destination, gl::byterange_t sourceRange, gl::offset_t destinationOffset)
    {
        glCopyNamedBufferSubData(gl::to_underlying(source), gl::to_underlying(destination), sourceRange.offset, destinationOffset, sourceRange.size);
    }
    
    template<typename T>
    static auto get_buffer_data          (gl::handle_t buffer, std::optional<gl::byterange_t> range)
    {
        std::vector<T> data{};

        if (range.has_value())
        {
            data.resize(range->size);

            glGetNamedBufferSubData(gl::to_underlying(buffer), range->offset, range->size, data.data());
        }
        else
        {
            const auto& size = gl::get_buffer_parameter_iv(buffer, glf::Buffer::Parameter::Size);
            data.resize(size);

            glGetNamedBufferSubData(gl::to_underlying(buffer), gl::offset_t{ 0 }, size, data.data());
        }

        return data;
    }



    //Chapter 7 - Programs and Shaders
    static auto create_shader(glf::Shader::Type type)
    {
        return gl::handle_t{ glCreateShader(gl::to_underlying(type)) };
    }
    static void shader_source(gl::handle_t shader, const std::string& source)
    {
        const auto* cstr = source.c_str();
        glShaderSource(gl::to_underlying(shader), gl::sizei_t{ 1 }, &cstr, nullptr);
    }
    static void compile_shader(gl::handle_t shader)
    {
        glCompileShader(gl::to_underlying(shader));
    }
    static void release_shader_compiler()
    {
        glReleaseShaderCompiler();
    }
    static void delete_shader(gl::handle_t shader)
    {
        if (shader != gl::NullObject) glDeleteShader(gl::to_underlying(shader));
    }
    static void shader_binary(gl::handle_t shader, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glShaderBinary(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&shader), format, binary.data(), static_cast<gl::sizei_t>(binary.size_bytes()));
    }
    template<gl::uint32_t N = 0>
    static void specialize_shader(gl::handle_t shader, const std::string& entry, std::span<const gl::uint32_t, N> indices = {}, std::span<const gl::uint32_t, N> values = {})
    {
        const auto* cstr = entry.c_str();
        glSpecializeShader(gl::to_underlying(shader), cstr, N, indices.data(), values.data());
    }

    static auto create_program()
    {
        return gl::handle_t{ glCreateProgram() };
    }
    static void attach_shader(gl::handle_t program, gl::handle_t shader)
    {
        glAttachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    static void detach_shader(gl::handle_t program, gl::handle_t shader)
    {
        glDetachShader(gl::to_underlying(program), gl::to_underlying(shader));
    }
    static void link_program(gl::handle_t program)
    {
        glLinkProgram(gl::to_underlying(program));
    }
    static auto create_shader_program(glf::Shader::Type type, const std::string& source)
    {
        const auto* cstr = source.c_str();
        return gl::handle_t{ glCreateShaderProgramv(gl::to_underlying(type), gl::sizei_t{ 1 }, &cstr) };
    }
    static void program_specification(gl::handle_t program, glf::Program::Specification specification, gl::bool_t value)
    {
        glProgramParameteri(gl::to_underlying(program), gl::to_underlying(specification), value);
    }
    static void delete_program(gl::handle_t program)
    {
        if (program != gl::NullObject) glDeleteProgram(gl::to_underlying(program));
    }

    static auto create_program_pipeline()
    {
        gl::handle_t handle{};
        glCreateProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_program_pipeline(gl::handle_t pipeline)
    {
        if (pipeline != gl::NullObject) glDeleteProgramPipelines(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&pipeline));
    }
    static void bind_program_pipeline(gl::handle_t pipeline)
    {
        glBindProgramPipeline(gl::to_underlying(pipeline));
    }
    static void use_program_stages(gl::handle_t pipeline, gl::handle_t program, glf::Program::Stage stages)
    {
        glUseProgramStages(gl::to_underlying(pipeline), gl::to_underlying(stages), gl::to_underlying(program));
    }
    static void active_shader_program(gl::handle_t pipeline, gl::handle_t program)
    {
        glActiveShaderProgram(gl::to_underlying(pipeline), gl::to_underlying(program));
    }

    static auto get_program_binary(gl::handle_t program)
    {
        std::vector<gl::uint8_t> binary{};
        gl::enum_t               format{};

        const auto& binaryLength = gl::get_program_iv(program, glf::Program::Parameter::BinaryLength);
        binary.resize(static_cast<std::size_t>(binaryLength));

        glGetProgramBinary(gl::to_underlying(program), binaryLength, nullptr, &format, binary.data());

        struct result_t{ std::vector<gl::uint8_t> binary{}; gl::enum_t format{}; };
        return result_t{ binary, format };
    }
    static void program_binary(gl::handle_t program, gl::enum_t format, std::span<const gl::byte_t> binary)
    {
        glProgramBinary(gl::to_underlying(program), format, binary.data(), static_cast<gl::sizei_t>(binary.size()));
    }

    static auto get_uniform_location(gl::handle_t program, const std::string& identifier)
    {
        const auto* cstr  = identifier.c_str();
        gl::int32_t value = glGetUniformLocation(gl::to_underlying(program), cstr);

        return value;
    }
    static auto get_active_uniform_name(gl::handle_t program, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_iv(program, glf::Program::Parameter::ActiveUniformMaximumLength);
        name.resize(maximumLength);

        glGetActiveUniformName(gl::to_underlying(program), index, maximumLength, &length, name.data());

        if (length ==                          0) throw std::invalid_argument{ "Identifier does not correspond to an active uniform name!" };
        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }
    static auto get_uniform_indices(gl::handle_t program, gl::sizei_t count, std::span<const std::string> identifiers)
    {
        std::vector<const gl::char_t*> cstrs{};
        std::vector<gl::uint32_t>      values{};

        cstrs .resize (identifiers.size());
        values.reserve(identifiers.size());

        std::transform(identifiers.begin(), identifiers.end(), cstrs.begin(), [](const std::string& _)
            {
                return _.c_str();
            });
        glGetUniformIndices(gl::to_underlying(program), count, cstrs.data(), values.data());

        std::ranges::for_each(values, [](const auto& value)
            {
                if (value == gl::to_underlying(glf::Error::Sentinel::InvalidIndex)) throw std::invalid_argument{ "Identifier does not correspond to an active uniform name!" };
            });

        return values;
    }
    static auto get_active_uniform(gl::handle_t program, gl::uint32_t index)
    {
        std::string name{};
        gl::enum_t  type{};
        gl::int32_t size{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_iv(program, glf::Program::Parameter::ActiveUniformMaximumLength);
        name.resize(maximumLength);

        glGetActiveUniform(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result_t{ std::string name{}; glf::DataType type{}; };
        return result_t{ name, glf::DataType{ type } };
    }

    static auto get_uniform_block_index(gl::handle_t program, const std::string& identifier)
    {
        const auto&  cstr  = identifier.c_str();
        gl::uint32_t value = glGetUniformBlockIndex(gl::to_underlying(program), cstr);

        return value;
    }
    static auto get_active_uniform_block_name(gl::handle_t program, gl::uint32_t index)
    {
        const auto& numUniformBlocks = gl::get_program_iv(program, glf::Program::Parameter::ActiveUniformBlocks);
        if (std::cmp_greater_equal(index, numUniformBlocks)) throw std::invalid_argument{ "Index is greater than the amount of uniform blocks!" };

        std::string name{};
        gl::sizei_t length{};

        const auto& maximumLength = gl::get_program_interface_iv(program, glf::Program::Interface::UniformBlock, glf::Program::Property::MaximumNameLength);
        name.resize(maximumLength);

        glGetActiveUniformBlockName(gl::to_underlying(program), index, maximumLength, &length, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }
    static void uniform_block_binding(gl::handle_t program, gl::uint32_t index, gl::uint32_t binding)
    {
        glUniformBlockBinding(gl::to_underlying(program), index, binding);
    }

    static void shader_storage_block_binding(gl::handle_t program, gl::uint32_t index, gl::uint32_t binding)
    {
        glShaderStorageBlockBinding(gl::to_underlying(program), index, binding);
    }

    static auto get_subroutine_uniform_location(gl::handle_t program, glf::Shader::Type type, const std::string& identifier)
    {
        const auto* cstr  = identifier.c_str();
        gl::int32_t value = glGetSubroutineUniformLocation(gl::to_underlying(program), gl::to_underlying(type), cstr);

        return value;
    }
    static auto get_subroutine_index(gl::handle_t program, glf::Shader::Type type, const std::string& identifier)
    {
        const auto* cstr   = identifier.c_str();
        gl::uint32_t value = glGetSubroutineIndex(gl::to_underlying(program), gl::to_underlying(type), cstr);

        return value;
    }
    static auto get_active_subroutine_name(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumSize = gl::get_program_stage_iv(program, type, glf::Program::StageProperty::ActiveSubroutineMaximumLength);
        name.resize(maximumSize);

        glGetActiveSubroutineName(gl::to_underlying(program), gl::to_underlying(type), index, maximumSize, &length, name.data());

        if (std::cmp_less(length, maximumSize)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }
    static auto get_active_subroutine_uniform_name(gl::handle_t program, glf::Shader::Type type, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};

        const auto& maximumSize = gl::get_program_stage_iv(program, type, glf::Program::StageProperty::ActiveSubroutineUniformMaximumLength);
        name.resize(maximumSize);

        glGetActiveSubroutineUniformName(gl::to_underlying(program), gl::to_underlying(type), index, maximumSize, &length, name.data());

        if (std::cmp_less(length, maximumSize)) name.resize(static_cast<std::size_t>(length) - 1u);

        return name;
    }

    static void memory_barrier(glf::Memory::Barrier barrier)
    {
        glMemoryBarrier(gl::to_underlying(barrier));
    }
    static void memory_barrier_by_region(glf::Memory::RegionalBarrier barrier)
    {
        glMemoryBarrierByRegion(gl::to_underlying(barrier));
    }









    //Chapter 8 - Textures and Samplers
    static auto create_texture(glf::Texture::Target target)
    {
        gl::handle_t handle{};
        glCreateTextures(gl::to_underlying(target), gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_texture(gl::handle_t texture)
    {
        if (texture != gl::NullObject) glDeleteTextures(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&texture));
    }
    static void bind_texture_unit(gl::handle_t texture, gl::uint32_t unit)
    {
        glBindTextureUnit(unit, gl::to_underlying(texture));
    }

    static auto create_sampler()
    {
        gl::handle_t handle{};
        glCreateSamplers(1, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_sampler(gl::handle_t sampler)
    {
        if (sampler != gl::NullObject) glDeleteSamplers(1, gl::to_underlying_ptr(&sampler));
    }
    static void bind_sampler(gl::handle_t sampler, gl::uint32_t slot)
    {
        glBindSampler(slot, gl::to_underlying(sampler));
    }

    static auto pixel_store(glf::PackingMode mode, gl::int32_t parameter)
    {
        glPixelStorei(gl::to_underlying(mode), parameter);
    }

    static void texture_sub_image_1d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::line_t  <gl::uint32_t>& line,   gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage1D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            line.origin.x, 
            line.extent.x,
            gl::to_underlying(format), gl::to_underlying(glf::PixelData::Type::UnsignedByte),
            data.data());
    }
    static void texture_sub_image_2d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::area_t  <gl::uint32_t>& area,   gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage2D(
            gl::to_underlying(texture), level,
            area.origin.x, area.origin.y,
            area.extent.x, area.extent.y,
            gl::to_underlying(format), gl::to_underlying(glf::PixelData::Type::UnsignedByte),
            data.data());
    }
    static void texture_sub_image_3d(gl::handle_t texture, glf::Texture::BaseFormat format, const gl::volume_t<gl::uint32_t>& volume, gl::uint32_t level, std::span<const gl::byte_t> data)
    {
        glTextureSubImage3D(
            gl::to_underlying(texture), level,
            volume.origin.x, volume.origin.y, volume.origin.z,
            volume.extent.x, volume.extent.y, volume.extent.z,
            gl::to_underlying(format), gl::to_underlying(glf::PixelData::Type::UnsignedByte),
            data.data());
    }
    static void copy_texture_sub_image_1d(gl::handle_t texture, gl::uint32_t level, const gl::Vector2u& offset, const gl::line_t  <gl::uint32_t>& line)
    {
        glCopyTextureSubImage1D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            line.origin.x,
            offset.x,      offset.y,
            line.extent.x);
    }
    static void copy_texture_sub_image_2d(gl::handle_t texture, gl::uint32_t level, const gl::Vector2u& offset, const gl::area_t  <gl::uint32_t>& area)
    {
        glCopyTextureSubImage2D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            area.origin.x, area.origin.y,
            offset.x,      offset.y,
            area.extent.x, area.extent.y);
    }
    static void copy_texture_sub_image_3d(gl::handle_t texture, gl::uint32_t level, const gl::Vector2u& offset, const gl::volume_t<gl::uint32_t>& volume)
    {
        glCopyTextureSubImage3D(
            gl::to_underlying(texture), static_cast<gl::int32_t>(level),
            volume.origin.x, volume.origin.y, volume.origin.z,
            offset.x,        offset.y,
            volume.extent.x, volume.extent.y);
    }

    static void compressed_texture_sub_image_1d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::line_t  <gl::uint32_t> line,   std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage1D(
            gl::to_underlying(texture),
            level,
            line.origin.x, 
            line.extent.x, 
            gl::to_underlying(format),
            static_cast<gl::sizei_t>(data.size()), data.data());
    }
    static void compressed_texture_sub_image_2d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::area_t  <gl::uint32_t> area,   std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage2D(
            gl::to_underlying(texture), 
            level, 
            area.origin.x, area.origin.y, 
            area.extent.x, area.extent.y, 
            gl::to_underlying(format), 
            static_cast<gl::sizei_t>(data.size()), data.data());
    }
    static void compressed_texture_sub_image_3d(gl::handle_t texture, glf::Texture::CompressedFormat format, gl::uint32_t level, const gl::volume_t<gl::uint32_t> volume, std::span<const gl::byte_t> data)
    {
        glCompressedTextureSubImage3D(
            gl::to_underlying(texture),
            level,
            volume.origin.x, volume.origin.y, volume.origin.z,
            volume.extent.x, volume.extent.y, volume.extent.z,
            gl::to_underlying(format),
            static_cast<gl::sizei_t>(data.size()), data.data());
    }

    static void texture_buffer(gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format)
    {
        glTextureBuffer(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer));
    }
    static void texture_buffer_range(gl::handle_t texture, gl::handle_t buffer, glf::Buffer::Format format, gl::line_t<gl::uint32_t> line)
    {
        glTextureBufferRange(gl::to_underlying(texture), gl::to_underlying(format), gl::to_underlying(buffer), line.origin.x, line.extent.x);
    }

    static void generate_texture_mipmap(gl::handle_t texture)
    {
        glGenerateTextureMipmap(gl::to_underlying(texture));
    }

    template<glf::Texture::Target T, glf::Texture::Target U> requires valid_texture_view_c<T, U>
    static void texture_view(gl::handle_t source, gl::handle_t destination, glf::Texture::Format format, gl::uint32_t minimumLevel, gl::uint32_t levels, gl::uint32_t minimumLayer, gl::uint32_t layers)
    {
        glTextureView(gl::to_underlying(destination), gl::to_underlying(U), gl::to_underlying(source), gl::to_underlying(format), minimumLevel, levels, minimumLayer, layers);
    }

    static void texture_storage_1d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector1u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage1D(gl::to_underlying(texture), static_cast<gl::sizei_t>(levels), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x));
    }
    static void texture_storage_2d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage2D(gl::to_underlying(texture), static_cast<gl::sizei_t>(levels), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    static void texture_storage_3d(gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::uint32_t levels)
    {
        glTextureStorage3D(gl::to_underlying(texture), static_cast<gl::sizei_t>(levels), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z));
    }
    static void texture_storage_2d_multisample(gl::handle_t texture, glf::Texture::Format format, const gl::Vector2u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage2DMultisample(gl::to_underlying(texture), static_cast<gl::sizei_t>(samples), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), fixed);
    }
    static void texture_storage_3d_multisample(gl::handle_t texture, glf::Texture::Format format, const gl::Vector3u& dimensions, gl::uint32_t samples, gl::bool_t fixed = gl::True)
    {
        glTextureStorage3DMultisample(gl::to_underlying(texture), static_cast<gl::sizei_t>(samples), gl::to_underlying(format), static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y), static_cast<gl::sizei_t>(dimensions.z), fixed);
    }

    static void invalidate_texture_image(gl::handle_t texture, gl::uint32_t level, std::optional<gl::volume_t<gl::uint32_t>> volume)
    {
        if (volume.has_value())
        {
            glInvalidateTexSubImage(
                gl::to_underlying(texture), static_cast<gl::int32_t>(level),
                static_cast<gl::int32_t>(volume->origin.x), static_cast<gl::int32_t>(volume->origin.y), static_cast<gl::int32_t>(volume->origin.z),
                static_cast<gl::sizei_t>(volume->extent.x), static_cast<gl::sizei_t>(volume->extent.y), static_cast<gl::sizei_t>(volume->extent.z));
        }
        else
        {
            glInvalidateTexImage(gl::to_underlying(texture), static_cast<gl::int32_t>(level));
        }
    }

    static void clear_texture_image(gl::handle_t texture, glf::Texture::BaseFormat format, glf::Texture::Type type, gl::uint32_t level, std::optional<gl::volume_t<gl::uint32_t>> volume, std::span<const gl::byte_t> data)
    {
        if (volume.has_value())
        {
            glClearTexSubImage(
                gl::to_underlying(texture),  static_cast<gl::int32_t>(level), 
                static_cast<gl::int32_t>(volume->origin.x), static_cast<gl::int32_t>(volume->origin.y), static_cast<gl::int32_t>(volume->origin.z),
                static_cast<gl::sizei_t>(volume->extent.x), static_cast<gl::sizei_t>(volume->extent.y), static_cast<gl::sizei_t>(volume->extent.z), 
                gl::to_underlying(format), 
                gl::to_underlying(type), 
                data.data());
        }
        else
        {
            glClearTexImage(
                gl::to_underlying(texture), static_cast<gl::int32_t>(level), 
                gl::to_underlying(format), 
                gl::to_underlying(type),
                data.data());
        }
    }

    static void bind_image_texture(gl::handle_t image, gl::handle_t texture, glf::Image::Format format, glf::Image::Access access, gl::uint32_t level, std::optional<gl::uint32_t> layer)
    {
        glBindImageTexture(
            gl::to_underlying(image), 
            gl::to_underlying(texture),
            static_cast<gl::int32_t>(level),
            layer.has_value(), static_cast<gl::int32_t>(layer.value_or(gl::uint32_t{ 0 })),
            gl::to_underlying(access), 
            gl::to_underlying(format));
    }



    //Chapter 9 - FrameBuffers and FrameBuffer Objects
    static auto create_frame_buffer()
    {
        gl::handle_t handle{};
        glCreateFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_frame_buffer(gl::handle_t frameBuffer)
    {
        if (frameBuffer != gl::NullObject) glDeleteFramebuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&frameBuffer));
    }
    static void bind_frame_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Target target)
    {
        glBindFramebuffer(gl::to_underlying(target), gl::to_underlying(frameBuffer));
    }

    static void frame_buffer_parameter(gl::handle_t frameBuffer, glf::FrameBuffer::Parameter parameter, gl::uint32_t value)
    {
        glNamedFramebufferParameteri(gl::to_underlying(frameBuffer), gl::to_underlying(parameter), static_cast<gl::int32_t>(value));
    }

    static auto create_render_buffer()
    {
        gl::handle_t handle{};
        glCreateRenderbuffers(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_render_buffer(gl::handle_t renderBuffer)
    {
        if (renderBuffer != gl::NullObject) glDeleteRenderbuffers(1, gl::to_underlying_ptr(&renderBuffer));
    }
    static void render_buffer_storage(gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions)
    {
        glNamedRenderbufferStorage(
            gl::to_underlying(renderBuffer), 
            gl::to_underlying(format), 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }
    static void render_buffer_storage_multisample(gl::handle_t renderBuffer, glf::RenderBuffer::Format format, const gl::Vector2u& dimensions, gl::uint8_t samples)
    {
        glNamedRenderbufferStorageMultisample(
            gl::to_underlying(renderBuffer), static_cast<gl::sizei_t>(samples), 
            gl::to_underlying(format), 
            static_cast<gl::sizei_t>(dimensions.x), static_cast<gl::sizei_t>(dimensions.y));
    }

    static void frame_buffer_render_buffer(gl::handle_t frameBuffer, gl::handle_t renderBuffer, glf::FrameBuffer::Source attachment)
    {
        glNamedFramebufferRenderbuffer(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(glf::RenderBuffer::Target::RenderBuffer), gl::to_underlying(renderBuffer));
    }

    static void frame_buffer_texture(gl::handle_t frameBuffer, gl::handle_t texture, glf::FrameBuffer::Source attachment, gl::uint32_t level)
    {
        glNamedFramebufferTexture(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(texture), static_cast<gl::int32_t>(level));
    }
    static void frame_buffer_texture_layer(gl::handle_t frameBuffer, gl::handle_t texture, glf::FrameBuffer::Attachment attachment, gl::uint32_t level, gl::uint32_t layer)
    {
        glNamedFramebufferTextureLayer(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), gl::to_underlying(texture), static_cast<gl::int32_t>(level), static_cast<gl::int32_t>(layer));
    }

    static void texture_barrier()
    {
        glTextureBarrier();
    }

    static auto check_frame_buffer_status(gl::handle_t frameBuffer)
    {
        return glf::FrameBuffer::Status{ glCheckNamedFramebufferStatus(gl::to_underlying(frameBuffer), gl::to_underlying(glf::FrameBuffer::Target::Write)) };
    }



    //Chapter 10 - Vertex Specification and Drawing Commands
    static void patch_parameter_separate(glf::Patch::Parameter parameter, gl::int32_t value)
    {
        glPatchParameteri(gl::to_underlying(parameter), value);
    }

    template<typename T, gl::uint32_t N, gl::bool_t NORM = gl::False>
    static void vertex_attribute(gl::uint32_t index, const gl::Vector<T, N>& value)
    {
        const auto& maximumAttributes = gl::get_integer32_v(glf::Data::MaximumVertexAttributes);
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

    static auto create_vertex_array()
    {
        gl::handle_t handle{};
        glCreateVertexArrays(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_vertex_array(gl::handle_t vertexArray)
    {
        if (vertexArray != gl::NullObject) glDeleteVertexArrays(1, gl::to_underlying_ptr(&vertexArray));
    }
    static void bind_vertex_array(gl::handle_t vertexArray)
    {
        glBindVertexArray(gl::to_underlying(vertexArray));
    }
    static void vertex_array_element_buffer(gl::handle_t vertexArray, gl::handle_t elementBuffer)
    {
        glVertexArrayElementBuffer(gl::to_underlying(vertexArray), gl::to_underlying(elementBuffer));
    }
    
    static void vertex_array_attribute_format(gl::handle_t vertexArray, gl::uint32_t index, gl::offset_t offset, glf::VertexArray::Attribute::Type type, gl::uint32_t count, gl::bool_t normalized = gl::False)
    {
        const auto& maximumVertexAttributes = gl::get_value<glf::Data::MaximumVertexAttributes>();
        if (std::cmp_greater(index, maximumVertexAttributes)) throw std::invalid_argument{ "Index exceeds the maximum amount of vertex attributes!" };

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
                glVertexArrayAttribIFormat(gl::to_underlying(vertexArray), index, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
                break;
            }

            case glf::VertexArray::Attribute::Type::Float                                : 
            case glf::VertexArray::Attribute::Type::HalfFloat                            : 
            case glf::VertexArray::Attribute::Type::Fixed                                : 
            {
                glVertexArrayAttribFormat(gl::to_underlying(vertexArray), index, static_cast<gl::int32_t>(count), gl::to_underlying(type), normalized, static_cast<gl::uint32_t>(offset));
                break;
            }

            case glf::VertexArray::Attribute::Type::Double                               : 
            {
                glVertexArrayAttribLFormat(gl::to_underlying(vertexArray), index, static_cast<gl::int32_t>(count), gl::to_underlying(type), static_cast<gl::uint32_t>(offset));
                break;
            }
        }
    }

    static void vertex_array_vertex_buffer(gl::handle_t vertexArray, gl::handle_t buffer, gl::uint32_t index, gl::sizei_t stride, gl::offset_t offset)
    {
        glVertexArrayVertexBuffer(gl::to_underlying(vertexArray), index, gl::to_underlying(buffer), offset, stride);
    }
    static void vertex_array_attribute_binding(gl::handle_t vertexArray, gl::uint32_t index, gl::uint32_t binding)
    {
        glVertexArrayAttribBinding(gl::to_underlying(vertexArray), index, binding);
    }
    static void enable_vertex_array_attribute(gl::handle_t vertexArray, gl::uint32_t index)
    {
        glEnableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }
    static void disable_vertex_array_attribute(gl::handle_t vertexArray, gl::uint32_t index)
    {
        glDisableVertexArrayAttrib(gl::to_underlying(vertexArray), index);
    }

    static void vertex_array_binding_divisor(gl::handle_t vertexArray, gl::uint32_t binding, gl::uint32_t divisor)
    {
        glVertexArrayBindingDivisor(gl::to_underlying(vertexArray), binding, divisor);
    }

    static void enable(glf::Feature feature)
    {
        glEnable(gl::to_underlying(feature));
    }
    static void disable(glf::Feature feature)
    {
        glDisable(gl::to_underlying(feature));
    }
    static void primitive_restart_index(gl::uint32_t index)
    {
        glPrimitiveRestartIndex(index);
    }

    static void draw_arrays(glf::Draw::Mode mode, gl::range_t range)
    {
        glDrawArrays(gl::to_underlying(mode), static_cast<gl::int32_t>(range.offset), static_cast<gl::sizei_t>(range.count));
    }
    static void draw_arrays_instanced(glf::Draw::Mode mode, gl::range_t range, gl::sizei_t instanceCount, std::optional<gl::uint32_t> baseInstance)
    {
        if   (baseInstance.has_value()) glDrawArraysInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::int32_t>(range.offset), static_cast<gl::sizei_t>(range.count), instanceCount, baseInstance.value());
        else                            glDrawArraysInstanced            (gl::to_underlying(mode), static_cast<gl::int32_t>(range.offset), static_cast<gl::sizei_t>(range.count), instanceCount);
    }
    static void draw_elements(glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count)
    {
        glDrawElements(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr);
    }
    static void draw_elements_instanced(glf::Draw::Mode mode, glf::Draw::Type type, gl::count_t count, gl::uint32_t instanceCount, std::optional<gl::uint32_t> baseInstance)
    {
        if   (baseInstance.has_value()) glDrawElementsInstancedBaseInstance(gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instanceCount), baseInstance.value());
        else                            glDrawElementsInstanced            (gl::to_underlying(mode), static_cast<gl::sizei_t>(count), gl::to_underlying(type), nullptr, static_cast<gl::sizei_t>(instanceCount));
    }

    static void begin_conditional_render(gl::handle_t query, glf::Query::Mode mode)
    {
        glBeginConditionalRender(gl::to_underlying(query), gl::to_underlying(mode));
    }
    static void end_conditional_render()
    {
        glEndConditionalRender();
    }

    static void bind_attribute_location(gl::handle_t program, gl::uint32_t index, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glBindAttribLocation(gl::to_underlying(program), index, cstr);
    }
    static auto active_attribute(gl::handle_t program, gl::uint32_t index)
    {
        std::string name{};
        gl::sizei_t length{};
        gl::int32_t size{};
        gl::enum_t  type{};

        const auto& maximumLength = gl::get_program_iv(program, glf::Program::Parameter::ActiveAttributeMaximumLength);
        name.resize(maximumLength);

        glGetActiveAttrib(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result_t{ std::string name{}; glf::DataType type{}; gl::sizei_t size{}; };
        return result_t{ name, glf::DataType{ type }, size };
    }
    static auto get_attribute_location(gl::handle_t program)
    {
        const gl::char_t* identifier{};
        glGetAttribLocation(gl::to_underlying(program), identifier);

        if   (identifier) return std::string{ identifier };
        else              return std::string{};
    }

    template<gl::uint32_t N>
    static void                           transform_feedback_varyings(gl::handle_t program, std::span<const std::string, N> varyings, glf::TransformFeedback::BufferMode mode)
    {
        //const auto& transform = [](const std::string& identifier) { return identifier.c_str(); };
        //std::transform(varyings.begin(), varyings.end(), names.begin(), transform);

        std::array<const gl::char_t*, N> names{};

        std::uint32_t index{};
        for (const auto& varying : varyings)
        {
            names.at(index++) = varying.c_str();
        }

        glTransformFeedbackVaryings(gl::to_underlying(program), names.size(), names.data(), gl::to_underlying(mode));
    }
    static auto get_transform_feedback_varying(gl::handle_t program, gl::uint32_t index)
    {
        const auto& maximumIndex = gl::get_program_iv(program, glf::Program::Parameter::TransformFeedbackVaryings);
        if (std::cmp_greater_equal(index, maximumIndex)) throw std::invalid_argument{ "The given index is out of range!" };

        std::string name{};
        gl::sizei_t length{};
        gl::int32_t size{};
        gl::enum_t  type{};

        const auto& maximumLength = gl::get_program_iv(program, glf::Program::Parameter::TransformFeedbackVaryingMaximumLength);
        name.resize(maximumLength);

        glGetTransformFeedbackVarying(gl::to_underlying(program), index, maximumLength, &length, &size, &type, name.data());

        if (std::cmp_less(length, maximumLength)) name.resize(static_cast<std::size_t>(length) - 1u);

        struct result_t{ std::string identifier{}; glf::DataType type{}; gl::sizei_t size{}; };
        return result_t{ name, glf::DataType{ type }, size };
    }

    static void validate_program(gl::handle_t program)
    {
        glValidateProgram(gl::to_underlying(program));
    }
    static void validate_program_pipeline(gl::handle_t pipeline)
    {
        glValidateProgramPipeline(gl::to_underlying(pipeline));
    }

    static void patch_parameter(glf::Patch::Parameter parameter, std::span<const gl::float32_t, 4> values)
    {
        glPatchParameterfv(gl::to_underlying(parameter), values.data());
    }



    //Chapter 13 - Fixed-Function Vertex Post-Processing
    static auto create_transform_feedback()
    {
        gl::handle_t handle{};
        glCreateTransformFeedbacks(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&handle));

        return handle;
    }
    static void delete_transform_feedback(gl::handle_t transformFeedback)
    {
        if (transformFeedback != gl::NullObject) glDeleteTransformFeedbacks(gl::sizei_t{ 1 }, gl::to_underlying_ptr(&transformFeedback));
    }
    static void begin_transform_feedback(glf::TransformFeedback::PrimitiveMode mode)
    {
        glBeginTransformFeedback(gl::to_underlying(mode));
    }
    static void end_transform_feedback()
    {
        glEndTransformFeedback();
    }
    static void resume_transform_feedback()
    {
        glResumeTransformFeedback();
    }
    static void pause_tranform_feedback()
    {
        glPauseTransformFeedback();
    }
    static void transform_feedback_buffer_range(gl::handle_t transformFeedback, gl::handle_t buffer, gl::uint32_t index, gl::byterange_t range)
    {
        glTransformFeedbackBufferRange(gl::to_underlying(transformFeedback), index, gl::to_underlying(buffer), range.offset, range.size);
    }
    static void transform_feedback_buffer_base(gl::handle_t transformFeedback, gl::handle_t buffer, gl::uint32_t index)
    {
        glTransformFeedbackBufferBase(gl::to_underlying(transformFeedback), index, gl::to_underlying(buffer));
    }

    static void draw_transform_feedback(gl::handle_t transformFeedback, glf::Draw::Mode mode, std::optional<gl::uint32_t> instances)
    {
        if   (instances.has_value()) glDrawTransformFeedbackInstanced(gl::to_underlying(mode), gl::to_underlying(transformFeedback), static_cast<gl::sizei_t>(instances.value()));
        else                         glDrawTransformFeedback         (gl::to_underlying(mode), gl::to_underlying(transformFeedback));
    }
    static void draw_transform_feedback_stream(gl::handle_t transformFeedback, glf::Draw::Mode mode, gl::uint32_t stream, std::optional<gl::uint32_t> instances)
    {
        if   (instances.has_value()) glDrawTransformFeedbackStreamInstanced(gl::to_underlying(mode), gl::to_underlying(transformFeedback), stream, static_cast<gl::sizei_t>(instances.value()));
        else                         glDrawTransformFeedbackStream         (gl::to_underlying(mode), gl::to_underlying(transformFeedback), stream);
    }

    static void provoking_vertex(glf::ProvokingVertex::Mode provokingVertex)
    {
        glProvokingVertex(gl::to_underlying(provokingVertex));
    }

    static void clip_control(glf::Clip::Origin origin, glf::Clip::DepthMode mode)
    {
        glClipControl(gl::to_underlying(origin), gl::to_underlying(mode));
    }

    static void depth_range_array_v(gl::count_t offset, std::span<const gl::Vector2d> ranges)
    {
        glDepthRangeArrayv(offset, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    static void depth_range_indexed(gl::uint32_t index, const gl::Vector2d& range)
    {
        glDepthRangeIndexed(index, range.x, range.y);
    }
    static void depth_range(const gl::Vector2d& range)
    {
        glDepthRange(range.x, range.y);
    }
    static void depth_range(const gl::Vector2f& range)
    {
        glDepthRangef(range.x, range.y);
    }
    static void viewport_array_v(gl::count_t first, std::span<const gl::Vector2f> ranges)
    {
        glViewportArrayv(first, static_cast<gl::sizei_t>(ranges.size()), glm::value_ptr(*ranges.data()));
    }
    static void viewport_indexed(gl::uint32_t index, const gl::area_t<gl::float32_t>& area)
    {
        glViewportIndexedf(index, area.origin.x, area.origin.y, area.extent.x, area.extent.y);
    }
    static void viewport(const gl::area_t<gl::uint32_t>& area)
    {
        glViewport(area.origin.x, area.origin.y, area.extent.x, area.extent.y);
    }



    //Chapter 14 - Fixed-Function Primitive Assembly and Rasterization
    static auto multisample_v(gl::uint32_t index)
    {
        gl::Vector2f value{};
        glGetMultisamplefv(gl::to_underlying(glf::Multisample::Parameter::SamplePosition), index, glm::value_ptr(value));

        return value;
    }
    static void minimum_sample_shading(gl::float32_t value)
    {
        glMinSampleShading(value);
    }

    static void point_size(gl::float32_t size)
    {
        glPointSize(size);
    }
    template<glf::Point::Parameter, typename... Args> 
    static void                           point_parameter(Args... args) = delete;
    template<> 
    static void                           point_parameter<glf::Point::Parameter::FadeThresholdSize>(gl::float32_t value)
    {
        glPointParameterf(gl::to_underlying(glf::Point::Parameter::FadeThresholdSize), value);
    }
    template<> 
    static void                           point_parameter<glf::Point::Parameter::SpriteCoordinateOrigin>(glf::Point::CoordinateOrigin origin)
    {
        glPointParameteri(gl::to_underlying(glf::Point::Parameter::SpriteCoordinateOrigin), gl::to_underlying(origin));
    }

    static void line_width(gl::float32_t value)
    {
        glLineWidth(value);
    }

    static void front_face(glf::Orientation orientation)
    {
        glFrontFace(gl::to_underlying(orientation));
    }
    static void cull_face(glf::Culling::Face face)
    {
        glCullFace(gl::to_underlying(face));
    }

    static void polygon_mode(glf::Polygon::Mode mode)
    {
        glPolygonMode(gl::to_underlying(glf::Polygon::Face::FrontAndBack), gl::to_underlying(mode));
    }
    static void polygon_offset(gl::float32_t factor, gl::float32_t units, std::optional<gl::float32_t> clamp)
    {
        glPolygonOffsetClamp(factor, units, clamp.value_or(gl::float32_t{ 0.0f }));
    }

    static void scissor(const gl::area_t<gl::uint32_t>& area)
    {
        glScissor(
            static_cast<gl::int32_t>(area.origin.x), static_cast<gl::int32_t>(area.origin.y), 
            static_cast<gl::sizei_t>(area.extent.x), static_cast<gl::sizei_t>(area.extent.y));
    }
    

    
    //Chapter 15 - Programmable Fragment Processing
    static void bind_frag_data_location(gl::handle_t program, gl::uint32_t binding, std::optional<gl::uint32_t> index, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glBindFragDataLocationIndexed(gl::to_underlying(program), binding, index.value_or(gl::uint32_t{ 0u }), cstr);
    }
    static auto get_frag_data_location(gl::handle_t program, const std::string& identifier)
    {
        const auto& cstr  = identifier.c_str();
        gl::int32_t value = glGetFragDataLocation(gl::to_underlying(program), cstr);

        return value;
    }
    static auto get_frag_data_index(gl::handle_t program, const std::string& identifier)
    {
        const auto& cstr  = identifier.c_str();
        gl::int32_t value = glGetFragDataIndex(gl::to_underlying(program), cstr);

        return value;
    }



    //Chapter 17 - Writing Fragments and Samples to the Framebuffer
    static void stencil_function(glf::Stencil::Function function, std::optional<gl::uint32_t> reference, std::optional<gl::uint32_t> mask)
    {
        glStencilFunc(gl::to_underlying(function), reference.value_or(gl::uint32_t{ 0u }), mask.value_or(gl::uint32_t{ 0u }));
    }
    static void stencil_function_separate(glf::Stencil::Face face, glf::Stencil::Function function, std::optional<gl::uint32_t> reference, std::optional<gl::uint32_t> mask)
    {
        glStencilFuncSeparate(gl::to_underlying(face), gl::to_underlying(function), reference.value_or(gl::uint32_t{ 0u }), mask.value_or(gl::uint32_t{ 0u }));
    }
    static void stencil_operation(glf::Stencil::Action stencil, glf::Stencil::Action depth, glf::Stencil::Action depthStencil)
    {
        glStencilOp(gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }
    static void stencil_operation_separate(glf::Stencil::Face face, glf::Stencil::Action stencil, glf::Stencil::Action depth, glf::Stencil::Action depthStencil)
    {
        glStencilOpSeparate(gl::to_underlying(face), gl::to_underlying(stencil), gl::to_underlying(depth), gl::to_underlying(depthStencil));
    }

    static void depth_function(glf::DepthFunction function)
    {
        glDepthFunc(gl::to_underlying(function));
    }

    static void blend_equation(glf::Blending::Equation equation)
    {
        glBlendEquation(gl::to_underlying(equation));
    }
    static void blend_equation_separate(glf::Blending::Equation equationRGB, glf::Blending::Equation equationAlpha)
    {
        glBlendEquationSeparate(gl::to_underlying(equationRGB), gl::to_underlying(equationAlpha));
    }
    //There are blend equation functions for individual buffers. Add -here-?
    static void blend_function(glf::Blending::Factor source, glf::Blending::Factor destination)
    {
        glBlendFunc(gl::to_underlying(source), gl::to_underlying(destination));
    }
    static void blend_function_separate(glf::Blending::Factor sourceRGB, glf::Blending::Factor sourceAlpha, glf::Blending::Factor destinationRGB, glf::Blending::Factor destinationAlpha)
    {
        glBlendFuncSeparate(gl::to_underlying(sourceRGB), gl::to_underlying(destinationRGB), gl::to_underlying(sourceAlpha), gl::to_underlying(destinationAlpha));
    }
    //There are blend functions for individual buffers. Add -here-?
    static void blend_color(const gl::Vector4f& color)
    {
        glBlendColor(color.r, color.g, color.b, color.a);
    }

    static void logical_pixel_operation(glf::Logic::Operation operation)
    {
        glLogicOp(gl::to_underlying(operation));
    }

    static void frame_buffer_draw_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferDrawBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    static void frame_buffer_draw_buffers(gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Source> sources)
    {
        glNamedFramebufferDrawBuffers(gl::to_underlying(frameBuffer), static_cast<gl::sizei_t>(sources.size()), gl::to_underlying_ptr(sources.data()));
    }

    static void color_mask(const gl::Vector4b& mask)
    {
        glColorMask(mask.r, mask.g, mask.b, mask.a);
    }
    static void depth_mask(gl::bool_t flag)
    {
        glDepthMask(flag);
    }
    static void stencil_mask(gl::uint32_t mask)
    {
        glStencilMask(mask);
    }
    static void stencil_mask_separate(glf::Stencil::Face face, gl::uint32_t mask)
    {
        glStencilMaskSeparate(gl::to_underlying(face), mask);
    }

    static void clear(glf::Buffer::Mask mask)
    {
        glClear(gl::to_underlying(mask));
    }
    static void clear_color(const gl::Vector4f& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    static void clear_depth(gl::float32_t depth)
    {
        glClearDepthf(depth);
    }
    static void clear_stencil(gl::uint32_t index)
    {
        glClearStencil(static_cast<gl::int32_t>(index));
    }

    static void clear_frame_buffer_iv   (gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::uint32_t index, const gl::int32_t*   value)
    {
        glClearNamedFramebufferiv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
    }
    static void clear_frame_buffer_uiv  (gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::uint32_t index, const gl::uint32_t*  value)
    {
        glClearNamedFramebufferuiv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
    }
    static void clear_frame_buffer_fv   (gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::uint32_t index, const gl::float32_t* value)
    {
        glClearNamedFramebufferfv(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), value);
    }
    static void clear_frame_buffer_fi   (gl::handle_t frameBuffer, glf::FrameBuffer::Attachment attachment, gl::uint32_t index, gl::float32_t depth, gl::int32_t stencil)
    {
        glClearNamedFramebufferfi(gl::to_underlying(frameBuffer), gl::to_underlying(attachment), static_cast<gl::int32_t>(index), depth, stencil);
    }
    static void clear_frame_buffer_value(gl::handle_t frameBuffer, gl::clear_v parameter, gl::int32_t index)
    {
        if (std::holds_alternative<gl::color_p>(parameter))
        {
            const auto& p = std::get<gl::color_p>(parameter);

            if (std::holds_alternative<gl::Vector4i>(p.color))
            {
                const auto& c = std::get<gl::Vector4i>(p.color);
                gl::clear_frame_buffer_iv(frameBuffer, glf::FrameBuffer::Attachment::ColorIndex, p.index, glm::value_ptr(c));
            }
            if (std::holds_alternative<gl::Vector4u>(p.color))
            {
                const auto& c = std::get<gl::Vector4u>(p.color);
                gl::clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::ColorIndex, p.index, glm::value_ptr(c));
            }
            if (std::holds_alternative<gl::Vector4f>(p.color))
            {
                const auto& c = std::get<gl::Vector4f>(p.color);
                gl::clear_frame_buffer_fv(frameBuffer, glf::FrameBuffer::Attachment::ColorIndex, p.index, glm::value_ptr(c));
            }
        }
        if (std::holds_alternative<gl::depth_p>(parameter))
        {
            const auto& p = std::get<gl::depth_p>(parameter);

            if (std::holds_alternative<gl::int32_t>(p.value))
            {
                const auto& v = std::get<gl::int32_t>(p.value);
                gl::clear_frame_buffer_iv(frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &v);
            }
            if (std::holds_alternative<gl::uint32_t>(p.value))
            {
                const auto& v = std::get<gl::uint32_t>(p.value);
                gl::clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &v);
            }
            if (std::holds_alternative<gl::float32_t>(p.value))
            {
                const auto& v = std::get<gl::float32_t>(p.value);
                gl::clear_frame_buffer_fv(frameBuffer, glf::FrameBuffer::Attachment::Depth, gl::uint32_t{ 0u }, &v);
            }
        }
        if (std::holds_alternative<gl::stencil_p>(parameter))
        {
            const auto& p = std::get<gl::stencil_p>(parameter);

            if (std::holds_alternative<gl::int32_t>(p.value))
            {
                const auto& v = std::get<gl::int32_t>(p.value);
                gl::clear_frame_buffer_iv(frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &v);
            }
            if (std::holds_alternative<gl::uint32_t>(p.value))
            {
                const auto& v = std::get<gl::uint32_t>(p.value);
                gl::clear_frame_buffer_uiv(frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &v);
            }
            if (std::holds_alternative<gl::float32_t>(p.value))
            {
                const auto& v = std::get<gl::float32_t>(p.value);
                gl::clear_frame_buffer_fv(frameBuffer, glf::FrameBuffer::Attachment::Stencil, gl::uint32_t{ 0u }, &v);
            }
        }
        if (std::holds_alternative<gl::depthstencil_p>(parameter))
        {
            const auto& p = std::get<gl::depthstencil_p>(parameter);
            gl::clear_frame_buffer_fi(frameBuffer, glf::FrameBuffer::Attachment::DepthStencil, gl::uint32_t{ 0u }, p.depth, p.stencil);
        }
    }

    static void invalidate_frame_buffer_data(gl::handle_t frameBuffer, std::span<const glf::FrameBuffer::Attachment> attachments, std::optional<gl::area_t<gl::uint32_t>> area)
    {
        if (area.has_value())
        {
            glInvalidateNamedFramebufferSubData(
                gl::to_underlying(frameBuffer), 
                static_cast<gl::sizei_t>(attachments.size()), gl::to_underlying_ptr(attachments.data()), 
                static_cast<gl::int32_t>(area->origin.x), static_cast<gl::int32_t>(area->origin.y), 
                static_cast<gl::sizei_t>(area->extent.x), static_cast<gl::sizei_t>(area->extent.y));
        }
        else
        {
            glInvalidateNamedFramebufferData(
                gl::to_underlying(frameBuffer), 
                static_cast<gl::sizei_t>(attachments.size()), 
                gl::to_underlying_ptr(attachments.data()));
        }
    }



    //Chapter 18 - Reading and Copying Pixels
    static void frame_buffer_read_buffer(gl::handle_t frameBuffer, glf::FrameBuffer::Source source)
    {
        glNamedFramebufferReadBuffer(gl::to_underlying(frameBuffer), gl::to_underlying(source));
    }
    static void                           read_pixels(glf::PixelData::Format format, glf::PixelData::Type type, gl::area_t<gl::uint32_t> area, std::optional<gl::uint32_t> limit)
    {
        //const auto& viewportArea      = gl::get_value<glf::Data::Viewport>();
        //const auto& frameBuffer       = gl::get_value<glf::Data::DrawFramebufferBinding>();
        //const auto& frameBufferFormat = gl::get_frame_buffer_attachment_parameter_iv(gl::framebuffer_p{ frameBuffer, glf::FrameBuffer::Attachment{} });

        //glReadnPixels(
        //    area.origin.x, area.origin.y, area.extent.x, area.extent.y,
        //    gl::to_underlying(format), gl::to_underlying(type),
        //    );
    }

    static void clamp_color(gl::bool_t value)
    {
        glClampColor(gl::to_underlying(glf::ClampColor::Read), static_cast<gl::enum_t>(value));
    }

    static void blit_framebuffer(gl::handle_t source, gl::handle_t destination, glf::Buffer::Mask mask, glf::FrameBuffer::Filter filter, const gl::area_t<gl::uint32_t> sourceArea, const gl::area_t<gl::uint32_t> destinationArea)
    {
        glBlitNamedFramebuffer(
            gl::to_underlying(source),
            gl::to_underlying(destination),
            sourceArea.origin.x,      sourceArea.origin.y,      sourceArea.extent.x,      sourceArea.extent.y,
            destinationArea.origin.x, destinationArea.origin.y, destinationArea.extent.x, destinationArea.extent.y,
            gl::to_underlying(mask), gl::to_underlying(filter));
    }

    static void copy_image_sub_data(gl::handle_t sourceTexture, gl::handle_t destinationTexture, glf::Texture::Target sourceTarget, glf::Texture::Target destinationTarget, const gl::Vector4u& sourceOrigin, const gl::Vector4u& destinationOrigin, const gl::Vector3u& extent)
    {
        glCopyImageSubData(
            gl::to_underlying(sourceTexture),              gl::to_underlying(sourceTarget),               static_cast<gl::int32_t>(sourceOrigin.w),
            static_cast<gl::int32_t>(sourceOrigin.x),      static_cast<gl::int32_t>(sourceOrigin.y),      static_cast<gl::int32_t>(sourceOrigin.z),
            gl::to_underlying(destinationTexture),         gl::to_underlying(destinationTarget),          static_cast<gl::int32_t>(destinationOrigin.w),
            static_cast<gl::int32_t>(destinationOrigin.x), static_cast<gl::int32_t>(destinationOrigin.y), static_cast<gl::int32_t>(destinationOrigin.z),
            static_cast<gl::sizei_t>(extent.x),            static_cast<gl::sizei_t>(extent.y),            static_cast<gl::sizei_t>(extent.z));
    }




    //Chapter 19 - Compute Shaders
    static void dispatch_compute(gl::dispatch_v dispatch)
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
    static void debug_message_callback(debug_callback_t callback, const void* parameter = nullptr)
    {
        glDebugMessageCallback(callback, parameter);
    }
    static void debug_message_control(glf::Debug::Source source, glf::Debug::Type type, glf::Debug::Severity severity, gl::bool_t state)
    {
        glDebugMessageControl(gl::to_underlying(source), gl::to_underlying(type), gl::to_underlying(severity), 0, nullptr, state);
    }
    static void debug_message_insert(gl::uint32_t id, glf::Debug::Type type, glf::Debug::Severity severity, const std::string& message)
    {
        glDebugMessageInsert(
            gl::to_underlying(glf::Debug::Source::Application), 
            gl::to_underlying(type), id, gl::to_underlying(severity), 
            static_cast<gl::sizei_t>(message.length()), message.data());
    }
    static void push_debug_group(gl::uint32_t id, const std::string& message)
    {
        const auto* cstr = message.c_str();
        glPushDebugGroup(gl::to_underlying(glf::Debug::Source::Application), id, -1, cstr);
    }
    static void pop_debug_group()
    {
        glPopDebugGroup();
    }
    static void object_label(gl::handle_t handle, glf::Object::Type type, const std::string& label)
    {
        const auto* cstr = label.c_str();
        glObjectLabel(gl::to_underlying(type), gl::to_underlying(handle), -1, cstr);
    }
    static void object_pointer_label(gl::sync_t sync, const std::string& identifier)
    {
        const auto* cstr = identifier.c_str();
        glObjectPtrLabel(sync, -1, cstr);
    }
    static auto get_debug_message_log(gl::uint32_t count)
    {
        std::string                       messageLog{};
        std::vector<glf::Debug::Source>   sources{};
        std::vector<glf::Debug::Type>     types{};
        std::vector<gl::uint32_t>         ids{};
        std::vector<glf::Debug::Severity> severities{};
        std::vector<gl::sizei_t>          lengths{};

        const auto& maximumLength = gl::get_value<glf::Data::MaximumDebugMessageLength>();

        messageLog.resize(count * static_cast<gl::uint64_t>(maximumLength));
        sources   .resize(count);
        types     .resize(count);
        ids       .resize(count);
        severities.resize(count);
        lengths   .resize(count);

        gl::uint32_t amount = glGetDebugMessageLog(
            count, maximumLength, 
            gl::to_underlying_ptr(sources.data()), 
            gl::to_underlying_ptr(types.data()), ids.data(), 
            gl::to_underlying_ptr(severities.data()), 
            lengths.data(), messageLog.data());

        

        struct result_t
        {
            gl::uint32_t         id{};
            std::string          message{};
            glf::Debug::Source   source{};
            glf::Debug::Type     type{};
            glf::Debug::Severity severity{};
        };

        std::vector<result_t> result{};

        if (std::cmp_greater(amount, 0))
        {
            result.reserve(amount);

            std::size_t offset{};

            for (const auto& index : std::ranges::views::iota(0u, amount))
            {
                const auto& length = lengths.at(index);

                std::string message{ messageLog.data() + offset, static_cast<std::size_t>(length) - 1 };
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
    static auto get_object_label(gl::handle_t handle, glf::Object::Type type)
    {
        std::string label{};
        gl::sizei_t length{};

        const auto& maximumLabelLength = gl::get_value<glf::Data::MaximumLabelLength>();
        label.resize(static_cast<std::size_t>(maximumLabelLength));

        glGetObjectLabel(gl::to_underlying(type), gl::to_underlying(handle), maximumLabelLength, &length, label.data());

        if (std::cmp_less(length, maximumLabelLength)) label.resize(static_cast<std::size_t>(length) - 1);

        return label;
    }
    static auto get_object_pointer_label(gl::sync_t sync)
    {
        std::string label{};
        gl::sizei_t length{};

        const auto& maximumLabelLength = gl::get_value<glf::Data::MaximumLabelLength>();
        label.resize(static_cast<std::size_t>(maximumLabelLength));

        glGetObjectPtrLabel(sync, maximumLabelLength, &length, label.data());

        if (std::cmp_less(length, maximumLabelLength)) label.resize(static_cast<std::size_t>(length) - 1);

        return label;
    }
    
    
    
    //Chapter 21 - Special Functions
    static void hint(glf::Hint::Target target, glf::Hint::Mode mode)
    {
        glHint(gl::to_underlying(target), gl::to_underlying(mode));
    }



#ifdef FOX_GRAPHICS_API_GL_EXTENDED
    //TODO
    //create_*** functions that return N amount of handles eg.:
    //template<gl::sizei_t N>
    //create_buffers(...) => returns N amount of buffer handles. Returns handle if (N == 1). Returns handle array if (N > 1)
    //Same idea for delete_buffers(...) etc.
#endif
#ifdef FOX_GRAPHICS_API_GL_LEGACY
    static auto get_error()
    {
        gl::enum_t value = glGetError();

        return glf::Error::Flag{ value };
    }
    static auto is_sync(gl::sync_t sync)
    {
        gl::bool_t value{};
        value = glIsSync(sync);

        return value;
    }
    //Legacy OpenGL functions here (pre 3.0)
#endif
}
