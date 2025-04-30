#pragma once

#include "stdafx.hpp"

#include "Types.hpp"
#include "Enum.hpp"

namespace fox::gfx::api::glf
{
    struct     AtomicCounterBuffer
    {
        enum class Info : gl::enum_t
        {
            Binding                                  = GL_ATOMIC_COUNTER_BUFFER_BINDING, 
            DataSize                                 = GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, 

            ActiveAtomicCounters                     = GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS, 
            ActiveAtomicCounterIndices               = GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, 

            ReferencedByVertexShader                 = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER, 
            ReferencedByTessellationControlShader    = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER, 
            ReferencedByTessellationEvaluationShader = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER, 
            ReferencedByGeometryShader               = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER, 
            ReferencedByFragmentShader               = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER, 
            ReferencedByComputeShader                = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER, 
        };
    };
    struct     Blending
    {
        enum class Equation : gl::enum_t
        {
            Add             = GL_FUNC_ADD, 
            Subtract        = GL_FUNC_SUBTRACT, 
            ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT, 
            Minimum         = GL_MIN, 
            Maximum         = GL_MAX, 
        };
        enum class Factor : gl::enum_t
        {
            Zero                     = GL_ZERO, 
            One                      = GL_ONE, 

            SourceColor              = GL_SRC_COLOR, 
            OneMinusSourceColor      = GL_ONE_MINUS_SRC_COLOR, 
            DestinationColor         = GL_DST_COLOR, 
            OneMinusDestinationColor = GL_ONE_MINUS_DST_COLOR, 
            SourceAlpha              = GL_SRC_ALPHA, 
            OneMinusSourceAlpha      = GL_ONE_MINUS_SRC_ALPHA, 
            DestinationAlpha         = GL_DST_ALPHA, 
            OneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA, 
            ConstantColor            = GL_CONSTANT_COLOR, 
            OneMinusConstantColor    = GL_ONE_MINUS_CONSTANT_COLOR, 
            ConstantAlpha            = GL_CONSTANT_ALPHA, 
            OneMinusConstantAlpha    = GL_ONE_MINUS_CONSTANT_ALPHA, 
            SourceAlphaSaturate      = GL_SRC_ALPHA_SATURATE, 
            Source1Color             = GL_SRC1_COLOR, 
            OneMinusSource1Color     = GL_ONE_MINUS_SRC1_COLOR, 
            Source1Alpha             = GL_SRC1_ALPHA, 
            OneMinusSource1Alpha     = GL_ONE_MINUS_SRC1_ALPHA, 
        };
    };
    struct     Buffer
    {
        enum class BaseTarget : gl::enum_t
        {
            AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER,
            ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER,
            UniformBuffer           = GL_UNIFORM_BUFFER,
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
        };
        enum class BaseFormat : gl::enum_t
        {
            R        = GL_RED, 
            G        = GL_GREEN, 
            B        = GL_BLUE, 

            RG       = GL_RG, 
            RGB      = GL_RGB, 
            RGBA     = GL_RGBA, 

            BGR      = GL_BGR, 
            BGRA     = GL_BGRA, 

            R_INT    = GL_RED_INTEGER, 
            G_INT    = GL_GREEN_INTEGER, 
            B_INT    = GL_BLUE_INTEGER, 

            RG_INT   = GL_RG_INTEGER, 
            RGB_INT  = GL_RGB_INTEGER, 
            RGBA_INT = GL_RGBA_INTEGER, 

            BGR_INT  = GL_BGR_INTEGER, 
            BGRA_INT = GL_BGRA_INTEGER, 

            S        = GL_STENCIL_INDEX, 
            D        = GL_DEPTH_COMPONENT, 
            DS       = GL_DEPTH_STENCIL, 
        };
        enum class Format : gl::enum_t
        {
            R8           = GL_R8,
            R16          = GL_R16,
            R16_FLOAT    = GL_R16F,
            R32_FLOAT    = GL_R32F,
            R8_INT       = GL_R8I,
            R16_INT      = GL_R16I,
            R32_INT      = GL_R32I,
            R8U_INT      = GL_R8UI,
            R16_UINT     = GL_R16UI,
            R32_UINT     = GL_R32UI,
            RG8          = GL_RG8,
            RG16         = GL_RG16,
            RG16_FLOAT   = GL_RG16F,
            RG32_FLOAT   = GL_RG32F,
            RG8_INT      = GL_RG8I,
            RG16_INT     = GL_RG16I,
            RG32_INT     = GL_RG32I,
            RG8U_INT     = GL_RG8UI,
            RG16_UINT    = GL_RG16UI,
            RG32_UINT    = GL_RG32UI,
            RGB32_FLOAT  = GL_RGB32F,
            RGB32_INT    = GL_RGB32I,
            RGB32_UINT   = GL_RGB32UI,
            RGBA8        = GL_RGBA8,
            RGBA16       = GL_RGBA16,
            RGBA16_FLOAT = GL_RGBA16F,
            RGBA32_FLOAT = GL_RGBA32F,
            RGBA8_INT    = GL_RGBA8I,
            RGBA16_INT   = GL_RGBA16I,
            RGBA32_INT   = GL_RGBA32I,
            RGBA8U_INT   = GL_RGBA8UI,
            RGBA16_UINT  = GL_RGBA16UI,
            RGBA32_UINT  = GL_RGBA32UI,
        };
        enum class Mask : gl::bitfield_t
        {
            Color   = GL_COLOR_BUFFER_BIT,
            Depth   = GL_DEPTH_BUFFER_BIT,
            Stencil = GL_STENCIL_BUFFER_BIT,

            All = Color | Depth | Stencil, 
        };
        struct     Mapping
        {
            enum class Access : gl::enum_t
            {
                Read      = GL_READ_ONLY,
                Write     = GL_WRITE_ONLY,
                ReadWrite = GL_READ_WRITE,
            };
            enum       AccessFlags : gl::bitfield_t
            {
                Read                = GL_MAP_READ_BIT,
                Write               = GL_MAP_WRITE_BIT, 
                ReadWrite           = Read | Write, 
                                
                ReadPersistent      = GL_MAP_PERSISTENT_BIT, 
                WritePersistent     = GL_MAP_PERSISTENT_BIT, 
                ReadWritePersistent = ReadPersistent | WritePersistent, 

                ReadCoherent        = GL_MAP_COHERENT_BIT | ReadPersistent, 
                WriteCoherent       = GL_MAP_COHERENT_BIT | WritePersistent, 
                ReadWriteCoherent   = GL_MAP_COHERENT_BIT | ReadWritePersistent, 

                InvalidateRange     = GL_MAP_INVALIDATE_RANGE_BIT, 
                InvalidateBuffer    = GL_MAP_INVALIDATE_RANGE_BIT, 
                FlushExplicit       = GL_MAP_FLUSH_EXPLICIT_BIT, 
                Unsynchronized      = GL_MAP_UNSYNCHRONIZED_BIT, 
            };
        };
        enum class Parameter : gl::enum_t
        {
            Access       = GL_BUFFER_ACCESS, 
            AccessFlags  = GL_BUFFER_ACCESS_FLAGS, 
            IsImmutable  = GL_BUFFER_IMMUTABLE_STORAGE, 
            IsMapped     = GL_BUFFER_MAPPED, 
            MapLength    = GL_BUFFER_MAP_LENGTH, 
            MapOffset    = GL_BUFFER_MAP_OFFSET, 
            Size         = GL_BUFFER_SIZE, 
            StorageFlags = GL_BUFFER_STORAGE_FLAGS, 

            Usage        = GL_BUFFER_USAGE, 
        };
        enum       StorageFlags : gl::bitfield_t
        {
            None                = gl::bitfield_t{ 0 },
                                
            Read                = GL_MAP_READ_BIT,
            Write               = GL_MAP_WRITE_BIT,
            ReadWrite           = Read | Write, 
                                
            DynamicStorage      = GL_DYNAMIC_STORAGE_BIT,
            ClientStorage       = GL_CLIENT_STORAGE_BIT,

            ReadPersistent      = GL_MAP_PERSISTENT_BIT | Read,
            WritePersistent     = GL_MAP_PERSISTENT_BIT | Write,
            ReadWritePersistent = GL_MAP_PERSISTENT_BIT | ReadWrite,

            ReadCoherent        = GL_MAP_COHERENT_BIT   | ReadPersistent,
            WriteCoherent       = GL_MAP_COHERENT_BIT   | WritePersistent,
            ReadWriteCoherent   = GL_MAP_COHERENT_BIT   | ReadWritePersistent, 

            Default             = ReadWrite | DynamicStorage
        };
        enum class Target : gl::enum_t
        {
            ArrayBuffer             = GL_ARRAY_BUFFER,
            AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER,
            CopyReadBuffer          = GL_COPY_READ_BUFFER,
            CopyWriteBuffer         = GL_COPY_WRITE_BUFFER,
            DispatchIndirectBuffer  = GL_DISPATCH_INDIRECT_BUFFER,
            DrawIndirectBuffer      = GL_DRAW_INDIRECT_BUFFER,
            ElementArrayBuffer      = GL_ELEMENT_ARRAY_BUFFER,
            PixelPackBuffer         = GL_PIXEL_PACK_BUFFER,
            PixelUnpackBuffer       = GL_PIXEL_UNPACK_BUFFER,
            QueryBuffer             = GL_QUERY_BUFFER,
            ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER,
            TextureBuffer           = GL_TEXTURE_BUFFER,
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
            UniformBuffer           = GL_UNIFORM_BUFFER,
        };
        enum class Usage
        {
            StreamDraw  = GL_STREAM_DRAW, 
            StreamRead  = GL_STREAM_READ, 
            StreamCopy  = GL_STREAM_COPY, 

            StaticDraw  = GL_STATIC_DRAW, 
            StaticRead  = GL_STATIC_READ, 
            StaticCopy  = GL_STATIC_COPY, 

            DynamicDraw = GL_DYNAMIC_DRAW, 
            DynamicRead = GL_DYNAMIC_READ, 
            DynamicCopy = GL_DYNAMIC_COPY, 
        };
    };
    struct     Callback
    {
        enum class Pointer : gl::enum_t
        {
            DebugCallbackFunction      = GL_DEBUG_CALLBACK_FUNCTION, 
            DebugCallbackUserParameter = GL_DEBUG_CALLBACK_USER_PARAM, 
        };
    };
    enum class ClampColor : gl::enum_t
    {
        Read = GL_CLAMP_READ_COLOR, 
    };
    struct     Clip
    {
        enum class Origin : gl::enum_t
        {
            LowerLeft = GL_LOWER_LEFT, 
            UpperLeft = GL_UPPER_LEFT, 
        };
        enum class DepthMode : gl::enum_t
        {
            NegativeOneToOne = GL_NEGATIVE_ONE_TO_ONE, 
            ZeroToOne        = GL_ZERO_TO_ONE, 
        };
    };
    struct     Context
    {
        enum       Flag : gl::bitfield_t
        {
            Debug             = GL_CONTEXT_FLAG_DEBUG_BIT, 
            ForwardCompatible = GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT, 
            NoError           = GL_CONTEXT_FLAG_NO_ERROR_BIT,
            RobustAccess      = GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT,
        };
        enum class Profile
        {
            Core          = GL_CONTEXT_CORE_PROFILE_BIT, 
            Compatibility = GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, 
        };
        enum class ResetStrategy : gl::enum_t
        {
            NoNotification,
            LoseContext,
        };
    };
    enum class Connection : gl::enum_t
    {
        Renderer               = GL_RENDERER, 
        Vendor                 = GL_VENDOR, 
        Version                = GL_VERSION, 
        ShadingLanguageVersion = GL_SHADING_LANGUAGE_VERSION, 
        Extensions             = GL_EXTENSIONS, 
        SpirVExtensions        = GL_SPIR_V_EXTENSIONS, 
    };
    struct     Cubemap
    {
        enum class Format
        {
            RGB8_UNORM   = GL_RGB8, 
            RGBA8_UNORM  = GL_RGBA8, 

            RGB8_SRGB    = GL_SRGB8, 
            RGBA8_SRGB   = GL_SRGB8_ALPHA8, 

            RGB16_FLOAT  = GL_RGB16F, 
            RGBA16_FLOAT = GL_RGBA16F, 

            RGB32_FLOAT  = GL_RGB32F, 
            RGBA32_FLOAT = GL_RGBA32F, 
        };
    };
    struct     Culling
    {
        enum class Face : gl::enum_t
        {
            Front     = GL_FRONT, 
            Back      = GL_BACK, 
            FrontBack = GL_FRONT_AND_BACK, 
        };
    };
    enum class Data : gl::enum_t
    {
        ActiveTexture                                    = GL_ACTIVE_TEXTURE, 
        AliasedLineWidthRange                            = GL_ALIASED_LINE_WIDTH_RANGE, 
        ArrayBufferBinding                               = GL_ARRAY_BUFFER_BINDING, 
        BlendColor                                       = GL_BLEND_COLOR, 
        BlendDestinationAlpha                            = GL_BLEND_DST_ALPHA, 
        BlendDestinationRGB                              = GL_BLEND_DST_RGB, 
        BlendEquationAlpha                               = GL_BLEND_EQUATION_ALPHA, 
        BlendEquationRGB                                 = GL_BLEND_EQUATION_RGB, 
        Blending                                         = GL_BLEND, 
        BlendSourceAlpha                                 = GL_BLEND_SRC_ALPHA, 
        BlendSourceRGB                                   = GL_BLEND_SRC_RGB, 
        ColorClearValue                                  = GL_COLOR_CLEAR_VALUE, 
        ColorLogicOperation                              = GL_COLOR_LOGIC_OP, 
        ColorWritemask                                   = GL_COLOR_WRITEMASK, 
        CompressedTextureFormats                         = GL_COMPRESSED_TEXTURE_FORMATS, 
        ContextFlags                                     = GL_CONTEXT_FLAGS, 
        CopyReadBufferBinding                            = GL_COPY_READ_BUFFER_BINDING, 
        CopyWriteBufferBinding                           = GL_COPY_WRITE_BUFFER_BINDING, 
        CurrentProgram                                   = GL_CURRENT_PROGRAM, 
        DebugGroupStackDepth                             = GL_DEBUG_GROUP_STACK_DEPTH, 
        DebugLoggedMessages                              = GL_DEBUG_LOGGED_MESSAGES, 
        DepthClearValue                                  = GL_DEPTH_CLEAR_VALUE, 
        DepthFunction                                    = GL_DEPTH_FUNC, 
        DepthRange                                       = GL_DEPTH_RANGE, 
        DepthTest                                        = GL_DEPTH_TEST, 
        DepthWritemask                                   = GL_DEPTH_WRITEMASK, 
        DispatchIndirectBufferBinding                    = GL_DISPATCH_INDIRECT_BUFFER_BINDING, 
        Dithering                                        = GL_DITHER, 
        DoubleBuffer                                     = GL_DOUBLEBUFFER, 
        DrawBuffer                                       = GL_DRAW_BUFFER, 
        DrawFramebufferBinding                           = GL_DRAW_FRAMEBUFFER_BINDING, 
        DrawIndirectBufferBinding                        = GL_DRAW_INDIRECT_BUFFER_BINDING, 
        FaceCulling                                      = GL_CULL_FACE, 
        FragmentShaderDerivativeHint                     = GL_FRAGMENT_SHADER_DERIVATIVE_HINT, 
        ImplementationColorReadFormat                    = GL_IMPLEMENTATION_COLOR_READ_FORMAT, 
        ImplementationColorReadType                      = GL_IMPLEMENTATION_COLOR_READ_TYPE, 
        IndexArrayBufferBinding                          = GL_ELEMENT_ARRAY_BUFFER_BINDING, 
        LayerProvokingVertex                             = GL_LAYER_PROVOKING_VERTEX, 
        LineSmooth                                       = GL_LINE_SMOOTH, 
        LineSmoothHint                                   = GL_LINE_SMOOTH_HINT, 
        LineWidth                                        = GL_LINE_WIDTH, 
        LogicOperationMode                               = GL_LOGIC_OP_MODE, 
        MajorVersion                                     = GL_MAJOR_VERSION, 
        Maximum3DTextureSize                             = GL_MAX_3D_TEXTURE_SIZE, 
        MaximumArrayTextureLayers                        = GL_MAX_ARRAY_TEXTURE_LAYERS, 
        MaximumClipDistances                             = GL_MAX_CLIP_DISTANCES, 
        MaximumColorTextureSamples                       = GL_MAX_COLOR_TEXTURE_SAMPLES, 
        MaximumCombinedAtomicCounters                    = GL_MAX_COMBINED_ATOMIC_COUNTERS, 
        MaximumCombinedComputeUniformComponents          = GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS, 
        MaximumCombinedFragmentUniformComponents         = GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, 
        MaximumCombinedGeometryUniformComponents         = GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS, 
        MaximumCombinedShaderStorageBlocks               = GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS, 
        MaximumCombinedTextureImageUnits                 = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, 
        MaximumCombinedUniformBlocks                     = GL_MAX_COMBINED_UNIFORM_BLOCKS, 
        MaximumCombinedVertexUniformComponents           = GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, 
        MaximumComputeAtomicCounterBuffers               = GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS, 
        MaximumComputeAtomicCounters                     = GL_MAX_COMPUTE_ATOMIC_COUNTERS, 
        MaximumComputeShaderStorageBlocks                = GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, 
        MaximumComputeTextureImageUnits                  = GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, 
        MaximumComputeUniformBlocks                      = GL_MAX_COMPUTE_UNIFORM_BLOCKS, 
        MaximumComputeUniformComponents                  = GL_MAX_COMPUTE_UNIFORM_COMPONENTS, 
        MaximumComputeWorkGroupCount                     = GL_MAX_COMPUTE_WORK_GROUP_COUNT, 
        MaximumComputeWorkGroupInvocations               = GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, 
        MaximumComputeWorkGroupSize                      = GL_MAX_COMPUTE_WORK_GROUP_SIZE, 
        MaximumCubemapTextureSize                        = GL_MAX_CUBE_MAP_TEXTURE_SIZE, 
        MaximumDebugGroupStackDepth                      = GL_MAX_DEBUG_GROUP_STACK_DEPTH, 
        MaximumDebugMessageLength                        = GL_MAX_DEBUG_MESSAGE_LENGTH, 
        MaximumDepthTextureSamples                       = GL_MAX_DEPTH_TEXTURE_SAMPLES, 
        MaximumDrawBuffers                               = GL_MAX_DRAW_BUFFERS, 
        MaximumDualSourceDrawBuffers                     = GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, 
        MaximumElementIndex                              = GL_MAX_ELEMENT_INDEX, 
        MaximumFragmentAtomicCounters                    = GL_MAX_FRAGMENT_ATOMIC_COUNTERS, 
        MaximumFragmentInputComponents                   = GL_MAX_FRAGMENT_INPUT_COMPONENTS, 
        MaximumFragmentShaderStorageBlocks               = GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, 
        MaximumFragmentUniformBlocks                     = GL_MAX_FRAGMENT_UNIFORM_BLOCKS, 
        MaximumFragmentUniformComponents                 = GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, 
        MaximumFragmentUniformVectors                    = GL_MAX_FRAGMENT_UNIFORM_VECTORS, 
        MaximumFrameBufferHeight                         = GL_MAX_FRAMEBUFFER_HEIGHT, 
        MaximumFrameBufferLayers                         = GL_MAX_FRAMEBUFFER_LAYERS, 
        MaximumFrameBufferSamples                        = GL_MAX_FRAMEBUFFER_SAMPLES, 
        MaximumFrameBufferWidth                          = GL_MAX_FRAMEBUFFER_WIDTH, 
        MaximumGeometryAtomicCounters                    = GL_MAX_GEOMETRY_ATOMIC_COUNTERS, 
        MaximumGeometryInputComponents                   = GL_MAX_GEOMETRY_INPUT_COMPONENTS, 
        MaximumGeometryOutputComponents                  = GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, 
        MaximumGeometryShaderStorageBlocks               = GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS, 
        MaximumGeometryTextureImageUnits                 = GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, 
        MaximumGeometryUniformBlocks                     = GL_MAX_GEOMETRY_UNIFORM_BLOCKS, 
        MaximumGeometryUniformComponents                 = GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, 
        MaximumIndexElements                             = GL_MAX_ELEMENTS_INDICES, 
        MaximumIntegerSamples                            = GL_MAX_INTEGER_SAMPLES, 
        MaximumLabelLength                               = GL_MAX_LABEL_LENGTH, 
        MaximumProgramTexelOffset                        = GL_MAX_PROGRAM_TEXEL_OFFSET, 
        MaximumRectangleTextureSize                      = GL_MAX_RECTANGLE_TEXTURE_SIZE, 
        MaximumRenderBufferSize                          = GL_MAX_RENDERBUFFER_SIZE, 
        MaximumSampleMaskWords                           = GL_MAX_SAMPLE_MASK_WORDS, 
        MaximumServerWaitTimeout                         = GL_MAX_SERVER_WAIT_TIMEOUT, 
        MaximumShaderStorageBufferBindings               = GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, 
        MaximumTessellationControlAtomicCounters         = GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS, 
        MaximumTessellationControlShaderStorageBlocks    = GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS, 
        MaximumTessellationEvaluationAtomicCounters      = GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS, 
        MaximumTessellationEvaluationShaderStorageBlocks = GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS, 
        MaximumTextureBufferSize                         = GL_MAX_TEXTURE_BUFFER_SIZE, 
        MaximumTextureImageUnits                         = GL_MAX_TEXTURE_IMAGE_UNITS, 
        MaximumTextureLODBias                            = GL_MAX_TEXTURE_LOD_BIAS, 
        MaximumTextureSize                               = GL_MAX_TEXTURE_SIZE, 
        MaximumUniformBlockSize                          = GL_MAX_UNIFORM_BLOCK_SIZE, 
        MaximumUniformBufferBindings                     = GL_MAX_UNIFORM_BUFFER_BINDINGS, 
        MaximumUniformLocations                          = GL_MAX_UNIFORM_LOCATIONS, 
        MaximumVaryingComponents                         = GL_MAX_VARYING_COMPONENTS, 
        MaximumVaryingFloats                             = GL_MAX_VARYING_FLOATS, 
        MaximumVaryingVectors                            = GL_MAX_VARYING_VECTORS, 
        MaximumVertexAtomicCounters                      = GL_MAX_VERTEX_ATOMIC_COUNTERS, 
        MaximumVertexAttributeBindings                   = GL_MAX_VERTEX_ATTRIB_BINDINGS, 
        MaximumVertexAttributeRelativeOffset             = GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, 
        MaximumVertexAttributes                          = GL_MAX_VERTEX_ATTRIBS, 
        MaximumVertexElements                            = GL_MAX_ELEMENTS_VERTICES, 
        MaximumVertexOutputComponents                    = GL_MAX_VERTEX_OUTPUT_COMPONENTS, 
        MaximumVertexShaderStorageBlocks                 = GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, 
        MaximumVertexTextureImageUnits                   = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, 
        MaximumVertexUniformBlocks                       = GL_MAX_VERTEX_UNIFORM_BLOCKS, 
        MaximumVertexUniformComponents                   = GL_MAX_VERTEX_UNIFORM_COMPONENTS, 
        MaximumVertexUniformVectors                      = GL_MAX_VERTEX_UNIFORM_VECTORS, 
        MaximumViewportDimensions                        = GL_MAX_VIEWPORT_DIMS, 
        MaximumViewports                                 = GL_MAX_VIEWPORTS, 
        MinimumMapBufferAlignment                        = GL_MIN_MAP_BUFFER_ALIGNMENT, 
        MinimumProgramTexelOffset                        = GL_MIN_PROGRAM_TEXEL_OFFSET, 
        MinorVersion                                     = GL_MINOR_VERSION, 
        NumberCompressedTextureFormats                   = GL_NUM_COMPRESSED_TEXTURE_FORMATS, 
        NumberExtensions                                 = GL_NUM_EXTENSIONS, 
        NumberProgramBinaryFormats                       = GL_NUM_PROGRAM_BINARY_FORMATS, 
        NumberShaderBinaryFormats                        = GL_NUM_SHADER_BINARY_FORMATS, 
        PackAlignment                                    = GL_PACK_ALIGNMENT, 
        PackImageHeight                                  = GL_PACK_IMAGE_HEIGHT, 
        PackLSBFirst                                     = GL_PACK_LSB_FIRST, 
        PackRowLength                                    = GL_PACK_ROW_LENGTH, 
        PackSkipImages                                   = GL_PACK_SKIP_IMAGES, 
        PackSkipPixels                                   = GL_PACK_SKIP_PIXELS, 
        PackSkipRows                                     = GL_PACK_SKIP_ROWS, 
        PackSwapBytes                                    = GL_PACK_SWAP_BYTES, 
        PixelPackBufferBinding                           = GL_PIXEL_PACK_BUFFER_BINDING, 
        PixelUnpackBufferBinding                         = GL_PIXEL_UNPACK_BUFFER_BINDING, 
        PointFadeThresholdSize                           = GL_POINT_FADE_THRESHOLD_SIZE, 
        PointSize                                        = GL_POINT_SIZE, 
        PointSizeGranularity                             = GL_POINT_SIZE_GRANULARITY, 
        PointSizeRange                                   = GL_POINT_SIZE_RANGE, 
        PolygonOffsetFactor                              = GL_POLYGON_OFFSET_FACTOR, 
        PolygonOffsetFill                                = GL_POLYGON_OFFSET_FILL, 
        PolygonOffsetLine                                = GL_POLYGON_OFFSET_LINE, 
        PolygonOffsetPoint                               = GL_POLYGON_OFFSET_POINT, 
        PolygonOffsetUnits                               = GL_POLYGON_OFFSET_UNITS, 
        PolygonSmooth                                    = GL_POLYGON_SMOOTH, 
        PolygonSmoothHint                                = GL_POLYGON_SMOOTH_HINT, 
        PrimitiveRestartIndex                            = GL_PRIMITIVE_RESTART_INDEX, 
        ProgramBinaryFormats                             = GL_PROGRAM_BINARY_FORMATS, 
        ProgramPipelineBinding                           = GL_PROGRAM_PIPELINE_BINDING, 
        ProgramPointSize                                 = GL_PROGRAM_POINT_SIZE, 
        ProvokingVertex                                  = GL_PROVOKING_VERTEX, 
        QueryBufferBinding                               = GL_QUERY_BUFFER_BINDING, 
        ReadBuffer                                       = GL_READ_BUFFER, 
        ReadFrameBufferBinding                           = GL_READ_FRAMEBUFFER_BINDING, 
        RenderbufferBinding                              = GL_RENDERBUFFER_BINDING, 
        SampleBuffers                                    = GL_SAMPLE_BUFFERS, 
        SampleCoverageInvert                             = GL_SAMPLE_COVERAGE_INVERT, 
        SampleCoverageValue                              = GL_SAMPLE_COVERAGE_VALUE, 
        SampleMaskValue                                  = GL_SAMPLE_MASK_VALUE, 
        SamplerBinding                                   = GL_SAMPLER_BINDING, 
        Samples                                          = GL_SAMPLES, 
        ScissorBox                                       = GL_SCISSOR_BOX, 
        ScissorTest                                      = GL_SCISSOR_TEST, 
        ShaderCompiler                                   = GL_SHADER_COMPILER, 
        ShaderStorageBufferBinding                       = GL_SHADER_STORAGE_BUFFER_BINDING, 
        ShaderStorageBufferOffsetAlignment               = GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, 
        ShaderStorageBufferSize                          = GL_SHADER_STORAGE_BUFFER_SIZE, 
        ShaderStorageBufferStart                         = GL_SHADER_STORAGE_BUFFER_START, 
        SmoothLineWidthGranularity                       = GL_SMOOTH_LINE_WIDTH_GRANULARITY, 
        SmoothLineWidthRange                             = GL_SMOOTH_LINE_WIDTH_RANGE, 
        StencilBackFail                                  = GL_STENCIL_BACK_FAIL, 
        StencilBackFunction                              = GL_STENCIL_BACK_FUNC, 
        StencilBackPassDepthFail                         = GL_STENCIL_BACK_PASS_DEPTH_FAIL, 
        StencilBackPassDepthPass                         = GL_STENCIL_BACK_PASS_DEPTH_PASS, 
        StencilBackRef                                   = GL_STENCIL_BACK_REF, 
        StencilBackValueMask                             = GL_STENCIL_BACK_VALUE_MASK, 
        StencilBackWritemask                             = GL_STENCIL_BACK_WRITEMASK, 
        StencilClearValue                                = GL_STENCIL_CLEAR_VALUE, 
        StencilFail                                      = GL_STENCIL_FAIL, 
        StencilFunction                                  = GL_STENCIL_FUNC, 
        StencilPassDepthFail                             = GL_STENCIL_PASS_DEPTH_FAIL, 
        StencilPassDepthPass                             = GL_STENCIL_PASS_DEPTH_PASS, 
        StencilReference                                 = GL_STENCIL_REF, 
        StencilTest                                      = GL_STENCIL_TEST, 
        StencilValueMask                                 = GL_STENCIL_VALUE_MASK, 
        StencilWritemask                                 = GL_STENCIL_WRITEMASK, 
        Stereo                                           = GL_STEREO, 
        SubpixelBits                                     = GL_SUBPIXEL_BITS, 
        TextureBinding1D                                 = GL_TEXTURE_BINDING_1D, 
        TextureBinding1DArray                            = GL_TEXTURE_BINDING_1D_ARRAY, 
        TextureBinding2D                                 = GL_TEXTURE_BINDING_2D, 
        TextureBinding2DArray                            = GL_TEXTURE_BINDING_2D_ARRAY, 
        TextureBinding2DMultisample                      = GL_TEXTURE_BINDING_2D_MULTISAMPLE, 
        TextureBinding2DMultisampleArray                 = GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, 
        TextureBinding3D                                 = GL_TEXTURE_BINDING_3D, 
        TextureBindingBuffer                             = GL_TEXTURE_BINDING_BUFFER, 
        TextureBindingCubemap                            = GL_TEXTURE_BINDING_CUBE_MAP, 
        TextureBindingRectangle                          = GL_TEXTURE_BINDING_RECTANGLE, 
        TextureBufferBinding                             = GL_TEXTURE_BUFFER_BINDING, 
        TextureBufferOffsetAlignment                     = GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT, 
        TextureCompressionHint                           = GL_TEXTURE_COMPRESSION_HINT, 
        Timestamp                                        = GL_TIMESTAMP, 
        TransformFeedbackBufferBinding                   = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, 
        TransformfeedbackBufferSize                      = GL_TRANSFORM_FEEDBACK_BUFFER_SIZE, 
        TransformFeedbackBufferStart                     = GL_TRANSFORM_FEEDBACK_BUFFER_START, 
        UniformBufferBinding                             = GL_UNIFORM_BUFFER_BINDING, 
        UniformBufferOffsetAlignment                     = GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, 
        UniformBufferSize                                = GL_UNIFORM_BUFFER_SIZE, 
        UniformBufferStart                               = GL_UNIFORM_BUFFER_START, 
        UnpackAlignment                                  = GL_UNPACK_ALIGNMENT, 
        UnpackImageHeight                                = GL_UNPACK_IMAGE_HEIGHT, 
        UnpackLSBFirst                                   = GL_UNPACK_LSB_FIRST, 
        UnpackRowLength                                  = GL_UNPACK_ROW_LENGTH, 
        UnpackSkipImages                                 = GL_UNPACK_SKIP_IMAGES, 
        UnpackSkipPixels                                 = GL_UNPACK_SKIP_PIXELS, 
        UnpackSkipRows                                   = GL_UNPACK_SKIP_ROWS, 
        UnpackSwapBytes                                  = GL_UNPACK_SWAP_BYTES, 
        VertexArrayBinding                               = GL_VERTEX_ARRAY_BINDING, 
        VertexBindingDivisor                             = GL_VERTEX_BINDING_DIVISOR, 
        VertexBindingOffset                              = GL_VERTEX_BINDING_OFFSET, 
        VertexBindingStride                              = GL_VERTEX_BINDING_STRIDE, 
        Viewport                                         = GL_VIEWPORT, 
        ViewportBoundsRange                              = GL_VIEWPORT_BOUNDS_RANGE, 
        ViewportIndexProvokingVertex                     = GL_VIEWPORT_INDEX_PROVOKING_VERTEX, 
        ViewportSubPixelBits                             = GL_VIEWPORT_SUBPIXEL_BITS, 



        PatchDefaultOuterLevel = GL_PATCH_DEFAULT_OUTER_LEVEL, 
        PatchDefaultInnerLevel = GL_PATCH_DEFAULT_INNER_LEVEL, 
        VertexBindingBuffer    = GL_VERTEX_BINDING_BUFFER, 
        ParameterBufferBinding = GL_PARAMETER_BUFFER_BINDING, 
        ClipOrigin             = GL_CLIP_ORIGIN, 
        ClipDepthMode          = GL_CLIP_DEPTH_MODE, 
        TransformFeedbackBinding = GL_TRANSFORM_FEEDBACK_BINDING, 



        //?
        ResetNotificationStrategy = GL_RESET_NOTIFICATION_STRATEGY, 
    };
    enum class DataType : gl::enum_t
    {
        Byte            = GL_BYTE, 
        UnsignedByte    = GL_UNSIGNED_BYTE, 
        Short           = GL_SHORT, 
        UnsignedShort   = GL_UNSIGNED_SHORT, 
        Integer         = GL_INT, 
        UnsignedInteger = GL_UNSIGNED_INT, 
        Float           = GL_FLOAT, 
        Double          = GL_DOUBLE, 
    };
    struct     Debug
    {
        enum class Source : gl::enum_t 
        {
            API            = GL_DEBUG_SOURCE_API,
            WindowSystem   = GL_DEBUG_SOURCE_WINDOW_SYSTEM,
            ShaderCompiler = GL_DEBUG_SOURCE_SHADER_COMPILER,
            ThirdParty     = GL_DEBUG_SOURCE_THIRD_PARTY,
            Application    = GL_DEBUG_SOURCE_APPLICATION,
            Other          = GL_DEBUG_SOURCE_OTHER, 

            DontCare       = GL_DONT_CARE, 
        };
        enum class Type : gl::enum_t 
        {
            DebugTypeError              = GL_DEBUG_TYPE_ERROR,
            DebugTypeDeprecatedBehavior = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
            DebugTypeUndefinedBehavior  = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
            DebugTypePortability        = GL_DEBUG_TYPE_PORTABILITY,
            DebugTypePerformance        = GL_DEBUG_TYPE_PERFORMANCE,
            DebugTypeMarker             = GL_DEBUG_TYPE_MARKER,
            DebugTypePushGroup          = GL_DEBUG_TYPE_PUSH_GROUP,
            DebugTypePopGroup           = GL_DEBUG_TYPE_POP_GROUP,
            DebugTypeOther              = GL_DEBUG_TYPE_OTHER, 

            DontCare                    = GL_DONT_CARE, 
        };
        enum class Severity : gl::enum_t 
        {
            DebugSeverityHigh         = GL_DEBUG_SEVERITY_HIGH,
            DebugSeverityMedium       = GL_DEBUG_SEVERITY_MEDIUM,
            DebugSeverityLow          = GL_DEBUG_SEVERITY_LOW,
            DebugSeverityNotification = GL_DEBUG_SEVERITY_NOTIFICATION, 

            DontCare                  = GL_DONT_CARE, 
        };
    };
    enum class DepthFunction : gl::enum_t
    {
        Always       = GL_ALWAYS, 
        Never        = GL_NEVER, 

        Equal        = GL_EQUAL, 
        NotEqual     = GL_NOTEQUAL, 

        Less         = GL_LESS, 
        LessEqual    = GL_LEQUAL, 

        Greater      = GL_GREATER, 
        GreaterEqual = GL_GEQUAL, 
    };
    struct     Draw
    {
        enum class Mode : gl::enum_t
        {
            Points                 = GL_POINTS,
            Lines                  = GL_LINES,
            LineLoop               = GL_LINE_LOOP,
            LineStrip              = GL_LINE_STRIP,
            Triangles              = GL_TRIANGLES,
            TriangleStrip          = GL_TRIANGLE_STRIP,
            TriangleFan            = GL_TRIANGLE_FAN,
            LinesAdjacency         = GL_LINES_ADJACENCY,
            LineStripAdjacency     = GL_LINE_STRIP_ADJACENCY,
            TrianglesAdjacency     = GL_TRIANGLES_ADJACENCY,
            TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
            Patches                = GL_PATCHES
        };
        enum class Type : gl::enum_t
        {
            UnsignedByte  = GL_UNSIGNED_BYTE, 
            UnsignedShort = GL_UNSIGNED_SHORT, 
            UnsignedInt   = GL_UNSIGNED_INT, 
        };
    };
    struct     Error
    {
        enum class Flag : gl::enum_t
        {
            NoError                     = GL_NO_ERROR, 

            InvalidEnumeration          = GL_INVALID_ENUM, 
            InvalidValue                = GL_INVALID_VALUE, 
            InvalidOperation            = GL_INVALID_OPERATION, 
            InvalidFrameBufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION, 

            OutOfMemory                 = GL_OUT_OF_MEMORY, 
            StackUnderflow              = GL_STACK_UNDERFLOW, 
            StackOverflow               = GL_STACK_OVERFLOW, 
        };
        enum class GraphicsResetStatus : gl::enum_t
        {
            NoError              = GL_NO_ERROR, 
            GuiltyContextReset   = GL_GUILTY_CONTEXT_RESET, 
            InnocentContextReset = GL_INNOCENT_CONTEXT_RESET, 
            UnknownContextReset  = GL_UNKNOWN_CONTEXT_RESET, 
        };
        enum class Sentinel : gl::enum_t
        {
            InvalidIndex = GL_INVALID_INDEX, 
        };
    };
    enum class Feature : gl::enum_t
    {
        Blending                   = GL_BLEND, 
        ClipDistance               = GL_CLIP_DISTANCE0, 
        ColorLogicOperation        = GL_COLOR_LOGIC_OP, 
        FaceCulling                = GL_CULL_FACE, 
        DebugOutput                = GL_DEBUG_OUTPUT, 
        DebugOutputSynchronous     = GL_DEBUG_OUTPUT_SYNCHRONOUS, 
        DepthClamp                 = GL_DEPTH_CLAMP, 
        DepthTest                  = GL_DEPTH_TEST, 
        Dither                     = GL_DITHER, 
        FrameBufferSRGB            = GL_FRAMEBUFFER_SRGB, 
        Multisampling              = GL_MULTISAMPLE, 
        PolygonFillOffset          = GL_POLYGON_OFFSET_FILL, 
        PolygonLineOffset          = GL_POLYGON_OFFSET_LINE, 
        PolygonPointOffset         = GL_POLYGON_OFFSET_POINT, 
        PolygonSmooth              = GL_POLYGON_SMOOTH, 
        PrimitiveRestart           = GL_PRIMITIVE_RESTART, 
        PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX, 
        ProgramPointSize           = GL_PROGRAM_POINT_SIZE, 
        RasterizerDiscard          = GL_RASTERIZER_DISCARD, 
        SampleAlphaToCoverage      = GL_SAMPLE_ALPHA_TO_COVERAGE, 
        SampleAlphaToOne           = GL_SAMPLE_ALPHA_TO_ONE, 
        SampleCoverage             = GL_SAMPLE_COVERAGE, 
        SampleMask                 = GL_SAMPLE_MASK, 
        SampleShading              = GL_SAMPLE_SHADING, 
        ScissorTest                = GL_SCISSOR_TEST, 
        SeamlessCubeMapTexture     = GL_TEXTURE_CUBE_MAP_SEAMLESS, 
        SmoothLines                = GL_LINE_SMOOTH, 
        StencilTest                = GL_STENCIL_TEST, 
    };
    struct     FrameBuffer
    {
        enum class Format : gl::enum_t
        {
            Red            = GL_RED, 
            Green          = GL_GREEN, 
            Blue           = GL_BLUE, 
            RGB            = GL_RGB, 
            RGBA           = GL_RGBA, 
            BGR            = GL_BGR, 
            BGRA           = GL_BGRA, 
            DepthComponent = GL_DEPTH_COMPONENT, 
            DepthStencil   = GL_DEPTH_STENCIL, 
            StencilIndex   = GL_STENCIL_INDEX, 
        };
        enum class Type : gl::enum_t
        {
            Byte            = GL_BYTE,
            UnsignedByte    = GL_UNSIGNED_BYTE,
            Short           = GL_SHORT,
            UnsignedShort   = GL_UNSIGNED_SHORT,
            Integer         = GL_INT,
            UnsignedInteger = GL_UNSIGNED_INT,
            HalfFloat       = GL_HALF_FLOAT, 
            Float           = GL_FLOAT, 
        };
        enum class Buffer : gl::enum_t
        {
            Color   = GL_COLOR, 
            Depth   = GL_DEPTH, 
            Stencil = GL_STENCIL, 
        };
        enum       Attachment : gl::enum_t
        {
            ColorIndex   = GL_COLOR_ATTACHMENT0, 
            Depth        = GL_DEPTH_ATTACHMENT, 
            Stencil      = GL_STENCIL_ATTACHMENT, 
            DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT, 
        };
        enum class Source : gl::enum_t
        {
            None                 = GL_NONE, 

            FrontLeft            = GL_FRONT_LEFT, 
            FrontRight           = GL_FRONT_RIGHT, 
            BackLeft             = GL_BACK_LEFT, 
            BackRight            = GL_BACK_RIGHT, 
            ColorAttachmentIndex = GL_COLOR_ATTACHMENT0, 
        };
        enum class Status : gl::enum_t
        {
            Complete                    = GL_FRAMEBUFFER_COMPLETE, 

            IncompleteAttachment        = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, 
            IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, 
            IncompleteDrawBuffer        = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER, 
            IncompleteReadBuffer        = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER, 
            IncompleteMultisample       = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE, 
            IncompleteLayerTargets      = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS, 

            Undefined                   = GL_FRAMEBUFFER_UNDEFINED, 
            Unsupported                 = GL_FRAMEBUFFER_UNSUPPORTED, 
        };
        enum class Target : gl::enum_t
        {
            Read        = GL_READ_FRAMEBUFFER, 
            Write       = GL_DRAW_FRAMEBUFFER, 

            FrameBuffer = Write, 
        };
        enum class Filter
        {
            Nearest = GL_NEAREST, 
            Linear  = GL_LINEAR, 
        };
        enum class Parameter : gl::enum_t
        {
            DefaultWidth                = GL_FRAMEBUFFER_DEFAULT_WIDTH, 
            DefaultHeight               = GL_FRAMEBUFFER_DEFAULT_HEIGHT, 
            DefaultLayers               = GL_FRAMEBUFFER_DEFAULT_LAYERS, 
            DefaultSamples              = GL_FRAMEBUFFER_DEFAULT_SAMPLES, 
            DefaultFixedSampleLocations = GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS, 
        };
    };
    struct     Geometry
    {
        enum class InputPrimitive : gl::enum_t
        {
            Points                 = GL_POINTS, 
            Lines                  = GL_LINES, 
            LineStrip              = GL_LINE_STRIP, 
            LineLoop               = GL_LINE, 
            LinesAdjacency         = GL_LINES_ADJACENCY, 
            LineStripAdjacency     = GL_LINE_STRIP_ADJACENCY, 
            Triangles              = GL_TRIANGLES, 
            TriangleStrip          = GL_TRIANGLE_STRIP, 
            TriangleFan            = GL_TRIANGLE_FAN, 
            TrianglesAdjacency     = GL_TRIANGLES_ADJACENCY, 
            TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY, 
        };
        enum class OutputPrimitive : gl::enum_t
        {
            Points        = GL_POINTS, 
            LineStrip     = GL_LINE_STRIP, 
            TriangleStrip = GL_TRIANGLE_STRIP, 
        };
    };
    struct     Hint
    {
        enum class Target : gl::enum_t
        {
            LineSmooth               = GL_LINE_SMOOTH_HINT, 
            PolygonSmooth            = GL_POLYGON_SMOOTH_HINT, 
            TextureCompression       = GL_TEXTURE_COMPRESSION_HINT, 
            FragmentShaderDerivative = GL_FRAGMENT_SHADER_DERIVATIVE_HINT, 
        };
        enum class Mode : gl::enum_t
        {
            Fastest  = GL_FASTEST, 
            Nicest   = GL_NICEST, 
            DontCare = GL_DONT_CARE, 
        };
    };
    struct     Image
    {
        enum class Access : gl::enum_t
        {
            ReadOnly  = GL_READ_ONLY, 
            WriteOnly = GL_WRITE_ONLY, 
            ReadWrite = GL_READ_WRITE, 
        };
        enum class Format : gl::enum_t
        {
            R8_UNORM          = GL_R8,
            R16_UNORM         = GL_R16,
            RG8_UNORM         = GL_RG8,
            RG16_UNORM        = GL_RG16,
            RGBA8_UNORM       = GL_RGBA8,
            RGBA16_UNORM      = GL_RGBA16,
            RGB10_A2_UNORM    = GL_RGB10_A2,

            R8_SNORM          = GL_R8_SNORM,
            R16_SNORM         = GL_R16_SNORM,
            RG8_SNORM         = GL_RG8_SNORM,
            RG16_SNORM        = GL_RG16_SNORM,
            RGBA8_SNORM       = GL_RGBA8_SNORM,
            RGBA16_SNORM      = GL_RGBA16_SNORM,
                              
            R16_FLOAT         = GL_R16F,
            R32_FLOAT         = GL_R32F,
            RG16_FLOAT        = GL_RG16F,
            RG32_FLOAT        = GL_RG32F,
            RGBA16_FLOAT      = GL_RGBA16F,
            RGBA32_FLOAT      = GL_RGBA32F,
            R11_G11_B10_FLOAT = GL_R11F_G11F_B10F,

            R8_INT            = GL_R8I,
            R16_INT           = GL_R16I,
            R32_INT           = GL_R32I,
            RG8_INT           = GL_RG8I,
            RG16_INT          = GL_RG16I,
            RG32_INT          = GL_RG32I,
            RGBA8_INT         = GL_RGBA8I,
            RGBA16_INT        = GL_RGBA16I,
            RGBA32_INT        = GL_RGBA32I,
                                      
            R8_UINT           = GL_R8UI,
            R16_UINT          = GL_R16UI,
            R32_UINT          = GL_R32UI,
            RG8_UINT          = GL_RG8UI,
            RG16_UINT         = GL_RG16UI,
            RG32_UINT         = GL_RG32UI,
            RGBA8_UINT        = GL_RGBA8UI,
            RGBA16_UINT       = GL_RGBA16UI,
            RGBA32_UINT       = GL_RGBA32UI,
            RGB10_A2_UINT     = GL_RGB10_A2UI,
        };
    };
    struct     Logic
    {
        enum class Operation : gl::enum_t
        {
            Clear        = GL_CLEAR, 
            Set          = GL_SET, 
            Copy         = GL_COPY, 
            CopyInverted = GL_COPY_INVERTED, 
            NoOp         = GL_NOOP, 
            Invert       = GL_INVERT, 
            And          = GL_AND, 
            Nand         = GL_NAND, 
            Or           = GL_OR, 
            Nor          = GL_NOR, 
            Xor          = GL_XOR, 
            Equivalent   = GL_EQUIV, 
            AndReverse   = GL_AND_REVERSE, 
            AndInverted  = GL_AND_INVERTED, 
            OrReverse    = GL_OR_REVERSE, 
            OrInverted   = GL_OR_INVERTED, 
        };
    };
    struct     Memory
    {
        enum class Barrier : gl::bitfield_t
        {
            VertexAttributeArrayBit = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT, 
            IndexArrayBit           = GL_ELEMENT_ARRAY_BARRIER_BIT, 
            UniformBit              = GL_UNIFORM_BARRIER_BIT, 
            TextureFetchBit         = GL_TEXTURE_FETCH_BARRIER_BIT, 

            ShaderImageAccessBit    = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT, 
            CommandBit              = GL_COMMAND_BARRIER_BIT, 
            PixelBufferBit          = GL_PIXEL_BUFFER_BARRIER_BIT, 

            TextureUpdateBit        = GL_TEXTURE_UPDATE_BARRIER_BIT, 
            BufferUpdateBit         = GL_BUFFER_UPDATE_BARRIER_BIT, 
            ClientMappedBufferBit   = GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT, 
            QueryBufferBit          = GL_QUERY_BUFFER_BARRIER_BIT, 
            FrameBufferBit          = GL_FRAMEBUFFER_BARRIER_BIT, 
            TransformFeedbackBit    = GL_TRANSFORM_FEEDBACK_BARRIER_BIT, 
            AtomicCounterBit        = GL_ATOMIC_COUNTER_BARRIER_BIT, 
            ShaderStorageBit        = GL_SHADER_STORAGE_BARRIER_BIT, 

            All                     = GL_ALL_BARRIER_BITS, 
        };
        enum class RegionalBarrier : gl::bitfield_t
        {
            AtomicCounterBit     = GL_ATOMIC_COUNTER_BARRIER_BIT_EXT, 
            FrameBufferBit       = GL_FRAMEBUFFER_BARRIER_BIT, 
            ShaderImageAccessBit = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT, 
            ShaderStorageBit     = GL_SHADER_STORAGE_BARRIER_BIT, 
            TextureFetchBit      = GL_TEXTURE_FETCH_BARRIER_BIT, 
            UniformBit           = GL_UNIFORM_BARRIER_BIT, 

            All                  = GL_ALL_BARRIER_BITS, 
        };
    };
    struct     Multisample
    {
        enum class Parameter : gl::enum_t
        {
            SamplePosition = GL_SAMPLE_POSITION, 
        };
    };
    struct     Object
    {
        enum class Type : gl::enum_t
        {
            Buffer            = GL_BUFFER, 
            Shader            = GL_SHADER, 
            Program           = GL_PROGRAM, 
            VertexArray       = GL_VERTEX_ARRAY, 
            Query             = GL_QUERY, 
            ProgramPipeline   = GL_PROGRAM_PIPELINE, 
            TransformFeedback = GL_TRANSFORM_FEEDBACK, 
            Sampler           = GL_SAMPLER, 
            Texture           = GL_TEXTURE, 
            RenderBuffer      = GL_RENDERBUFFER, 
            FrameBuffer       = GL_FRAMEBUFFER, 
        };
    };
    enum class Orientation : gl::enum_t
    {
        Clockwise        = GL_CW, 
        CounterClockwise = GL_CCW, 
    };
    enum class PackingMode : gl::enum_t
    {
        PackSwapBytes               = GL_PACK_SWAP_BYTES, 
        PackLsbFirst                = GL_PACK_LSB_FIRST, 
        PackRowLength               = GL_PACK_ROW_LENGTH, 
        PackSkipRows                = GL_PACK_SKIP_ROWS, 
        PackSkipPixels              = GL_PACK_SKIP_PIXELS, 
        PackAlignment               = GL_PACK_ALIGNMENT, 
        PackImageHeight             = GL_PACK_IMAGE_HEIGHT, 
        PackSkipImages              = GL_PACK_SKIP_IMAGES, 
        PackCompressedBlockWidth    = GL_PACK_COMPRESSED_BLOCK_WIDTH, 
        PackCompressedBlockHeight   = GL_PACK_COMPRESSED_BLOCK_HEIGHT, 
        PackCompressedBlockDepth    = GL_PACK_COMPRESSED_BLOCK_DEPTH, 
        PackCompressedBlockSize     = GL_PACK_COMPRESSED_BLOCK_SIZE, 

        UnpackSwapBytes             = GL_UNPACK_SWAP_BYTES, 
        UnpackLsbFirst              = GL_UNPACK_LSB_FIRST, 
        UnpackRowLength             = GL_UNPACK_ROW_LENGTH, 
        UnpackSkipRows              = GL_UNPACK_SKIP_ROWS, 
        UnpackSkipPixels            = GL_UNPACK_SKIP_PIXELS, 
        UnpackAlignment             = GL_UNPACK_ALIGNMENT, 
        UnpackImageHeight           = GL_UNPACK_IMAGE_HEIGHT, 
        UnpackSkipImages            = GL_UNPACK_SKIP_IMAGES, 
        UnpackCompressedBlockWidth  = GL_UNPACK_COMPRESSED_BLOCK_WIDTH, 
        UnpackCompressedBlockHeight = GL_UNPACK_COMPRESSED_BLOCK_HEIGHT, 
        UnpackCompressedBlockDepth  = GL_UNPACK_COMPRESSED_BLOCK_DEPTH, 
        UnpackCompressedBlockSize   = GL_UNPACK_COMPRESSED_BLOCK_SIZE, 
    };
    struct     Patch
    {
        enum class Parameter : gl::enum_t
        {
            PatchVertices          = GL_PATCH_VERTICES, 
            PatchDefaultOuterLevel = GL_PATCH_DEFAULT_OUTER_LEVEL, 
            PatchDefaultInterLevel = GL_PATCH_DEFAULT_INNER_LEVEL, 
        };
    };
    struct     PixelData
    {
        enum class Format : gl::enum_t
        {
            StencilIndex   = GL_STENCIL_INDEX, 
            DepthComponent = GL_DEPTH_COMPONENT, 
            DepthStencil   = GL_DEPTH_STENCIL, 
            Red            = GL_RED, 
            Green          = GL_GREEN, 
            Blue           = GL_BLUE, 
            RGB            = GL_RGB, 
            RGBA           = GL_RGBA, 
            BGR            = GL_BGR, 
            BGRA           = GL_BGRA, 
        };
        enum class Type : gl::enum_t
        {
            Byte                           = GL_BYTE,
            UnsignedByte                   = GL_UNSIGNED_BYTE,
            Short                          = GL_SHORT,
            UnsignedShort                  = GL_UNSIGNED_SHORT,
            Integer                        = GL_INT,
            UnsignedInteger                = GL_UNSIGNED_INT,
            HalfFloat                      = GL_HALF_FLOAT,
            Float                          = GL_FLOAT,
                                           
            UnsignedByte_3_3_2             = GL_UNSIGNED_BYTE_3_3_2,
            UnsignedByte_2_3_3_Rev         = GL_UNSIGNED_BYTE_2_3_3_REV,
            UnsignedShort_5_6_5            = GL_UNSIGNED_SHORT_5_6_5,
            UnsignedShort_5_6_5_Rev        = GL_UNSIGNED_SHORT_5_6_5_REV,
            UnsignedShort_4_4_4_4          = GL_UNSIGNED_SHORT_4_4_4_4,
            UnsignedShort_4_4_4_4_Rev      = GL_UNSIGNED_SHORT_4_4_4_4_REV,
            UnsignedShort_5_5_5_1          = GL_UNSIGNED_SHORT_5_5_5_1,
            UnsignedShort_1_5_5_5_Rev      = GL_UNSIGNED_SHORT_1_5_5_5_REV,
            UnsignedInt_8_8_8_8            = GL_UNSIGNED_INT_8_8_8_8,
            UnsignedInt_8_8_8_8_Rev        = GL_UNSIGNED_INT_8_8_8_8_REV,
            UnsignedInt_10_10_10_2         = GL_UNSIGNED_INT_10_10_10_2,
            UnsignedInt_2_10_10_10_Rev     = GL_UNSIGNED_INT_2_10_10_10_REV,
                                           
            UnsignedInt_24_8               = GL_UNSIGNED_INT_24_8,

            UnsignedInt_10_11_11_Float_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV, 
            UnsignedInt_5_9_9_9_Rev        = GL_UNSIGNED_INT_5_9_9_9_REV, 
            FloatUnsignedInt_24_8_Rev      = GL_FLOAT_32_UNSIGNED_INT_24_8_REV, 
        };
    };
    struct     Polygon
    {
        enum class Face : gl::enum_t
        {
            FrontAndBack = GL_FRONT_AND_BACK, 
        };
        enum class Mode : gl::enum_t
        {
            Point = GL_POINT, 
            Line  = GL_LINE, 
            Fill  = GL_FILL, 
        };
    };
    struct     Point
    {
        enum class Parameter : gl::enum_t
        {
            FadeThresholdSize      = GL_POINT_FADE_THRESHOLD_SIZE, 
            SpriteCoordinateOrigin = GL_POINT_SPRITE_COORD_ORIGIN, 
        };
        enum class CoordinateOrigin : gl::enum_t
        {
            LowerLeft = GL_LOWER_LEFT, 
            UpperLeft = GL_UPPER_LEFT, 
        };
    };
    struct     Program
    {
        enum class Interface : gl::enum_t
        {
            AtomicCounterBuffer                     = GL_ATOMIC_COUNTER_BUFFER, 
            Uniform                                 = GL_UNIFORM, 
            UniformBlock                            = GL_UNIFORM_BLOCK, 
            ProgramInput                            = GL_PROGRAM_INPUT, 
            ProgramOutput                           = GL_PROGRAM_OUTPUT, 
            BufferVariable                          = GL_BUFFER_VARIABLE, 
            ShaderStorageBlock                      = GL_SHADER_STORAGE_BLOCK, 

            VertexSubroutine                        = GL_VERTEX_SUBROUTINE, 
            TessellationControlSubroutine           = GL_TESS_CONTROL_SUBROUTINE, 
            TessellationEvaluationSubroutine        = GL_TESS_EVALUATION_SUBROUTINE, 
            GeometrySubroutine                      = GL_GEOMETRY_SUBROUTINE, 
            FragmentSubroutine                      = GL_FRAGMENT_SUBROUTINE, 
            ComputeSubroutine                       = GL_COMPUTE_SUBROUTINE, 
            VertexSubroutineUniform                 = GL_VERTEX_SUBROUTINE_UNIFORM, 
            TessellationControlSubroutineUniform    = GL_TESS_CONTROL_SUBROUTINE_UNIFORM, 
            TessellationEvaluationSubroutineUniform = GL_TESS_EVALUATION_SUBROUTINE_UNIFORM, 
            GeometrySubroutineUniform               = GL_GEOMETRY_SUBROUTINE_UNIFORM, 
            FragmentSubroutineUniform               = GL_FRAGMENT_SUBROUTINE_UNIFORM, 
            ComputeSubroutineUniform                = GL_COMPUTE_SUBROUTINE_UNIFORM, 

            TransformFeedbackBuffer                 = GL_TRANSFORM_FEEDBACK_BUFFER, 
            TransformFeedbackVarying                = GL_TRANSFORM_FEEDBACK_VARYING, 
        };
        enum class Property : gl::enum_t
        {
            ActiveResources, 
            MaximumNameLength, 
            MaximumNumberActiveVariables, 
            MaximumNumberCompatibleSubroutines, 
        };
        enum class Parameter : gl::enum_t
        {
            IsSeparable                           = GL_PROGRAM_SEPARABLE, 
            DeleteStatus                          = GL_DELETE_STATUS, 
            LinkStatus                            = GL_LINK_STATUS, 
            ValidateStatus                        = GL_VALIDATE_STATUS, 
            AttachedShaders                       = GL_ATTACHED_SHADERS, 
            InfoLogLength                         = GL_INFO_LOG_LENGTH, 
            BinaryLength                          = GL_PROGRAM_BINARY_LENGTH, 
            IsBinaryRetrievable                   = GL_PROGRAM_BINARY_RETRIEVABLE_HINT, 
            ComputeWorkGroupSize                  = GL_COMPUTE_WORK_GROUP_SIZE, 
            ActiveUniforms                        = GL_ACTIVE_UNIFORMS, 
            ActiveUniformMaximumLength            = GL_ACTIVE_UNIFORM_MAX_LENGTH,
            ActiveAttributes                      = GL_ACTIVE_ATTRIBUTES, 
            ActiveAttributeMaximumLength          = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
            GeometryVerticesOut                   = GL_GEOMETRY_VERTICES_OUT, 
            GeometryInputType                     = GL_GEOMETRY_INPUT_TYPE, 
            GeometryOutputType                    = GL_GEOMETRY_OUTPUT_TYPE, 
            GeometryShaderInvocations             = GL_GEOMETRY_SHADER_INVOCATIONS, 
            TransformFeedbackBufferMode           = GL_TRANSFORM_FEEDBACK_BUFFER_MODE, 
            TransformFeedbackVaryings             = GL_TRANSFORM_FEEDBACK_VARYINGS, 
            TransformFeedbackVaryingMaximumLength = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, 
            ActiveUniformBlocks                   = GL_ACTIVE_UNIFORM_BLOCKS, 
            ActiveUniformBlockMaximumNameLength   = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, 
            TessellationControlOutputVertices     = GL_TESS_CONTROL_OUTPUT_VERTICES, 
            TessellationGenerationMode            = GL_TESS_GEN_MODE, 
            TessellationGenerationSpacing         = GL_TESS_GEN_SPACING, 
            TessellationGenerationVertexOrder     = GL_TESS_GEN_VERTEX_ORDER, 
            TessellationGenerationPointMode       = GL_TESS_GEN_POINT_MODE, 
            ActiveAtomicCounterBuffers            = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS, 
        };
        enum class Resource : gl::enum_t
        {
            NameLength                               = GL_NAME_LENGTH, 
            Type                                     = GL_TYPE, 
            ArraySize                                = GL_ARRAY_SIZE, 
            Offset                                   = GL_OFFSET, 
            BlockIndex                               = GL_BLOCK_INDEX, 
            ArrayStride                              = GL_ARRAY_STRIDE, 
            MatrixStride                             = GL_MATRIX_STRIDE, 
            IsRowMajor                               = GL_IS_ROW_MAJOR, 
            AtomicCounterBufferIndex                 = GL_ATOMIC_COUNTER_BUFFER_INDEX, 
            TextureBuffer                            = GL_TEXTURE_BUFFER, 
            BufferBinding                            = GL_BUFFER_BINDING, 
            BufferDataSize                           = GL_BUFFER_DATA_SIZE, 
            NumberActiveVariables                    = GL_NUM_ACTIVE_VARIABLES, 
            ActiveVariables                          = GL_ACTIVE_VARIABLES, 
            ReferencedByVertexShader                 = GL_REFERENCED_BY_VERTEX_SHADER, 
            ReferencedByTessellationControlShader    = GL_REFERENCED_BY_TESS_CONTROL_SHADER, 
            ReferencedByTessellationEvaluationShader = GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
            ReferencedByGeometryShader               = GL_REFERENCED_BY_GEOMETRY_SHADER, 
            ReferencedByFragmentShader               = GL_REFERENCED_BY_FRAGMENT_SHADER, 
            ReferencedByComputeShader                = GL_REFERENCED_BY_COMPUTE_SHADER, 
            NumberCompatibleSubroutines              = GL_NUM_COMPATIBLE_SUBROUTINES, 
            CompatibleSubroutines                    = GL_COMPATIBLE_SUBROUTINES, 
            TopLevelArraySize                        = GL_TOP_LEVEL_ARRAY_SIZE, 
            TopLevelArrayStride                      = GL_TOP_LEVEL_ARRAY_STRIDE, 
            Location                                 = GL_LOCATION, 
            LocationIndex                            = GL_LOCATION_INDEX, 
            IsPerPatch                               = GL_IS_PER_PATCH, 
            LocationComponent                        = GL_LOCATION_COMPONENT, 
            TransformFeedbackBufferIndex             = GL_TRANSFORM_FEEDBACK_BUFFER_INDEX, 
            TransformFeedbackBufferStride            = GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE, 
        };
        enum class Specification : gl::enum_t
        {
            Separable         = GL_PROGRAM_SEPARABLE, 
            BinaryRetrievable = GL_PROGRAM_BINARY_RETRIEVABLE_HINT, 
        };
        enum       Stage : gl::bitfield_t
        {
            Vertex                 = GL_VERTEX_SHADER_BIT, 
            TessellationControl    = GL_TESS_CONTROL_SHADER_BIT, 
            TessellationEvaluation = GL_TESS_EVALUATION_SHADER_BIT, 
            Geometry               = GL_GEOMETRY_SHADER_BIT, 
            Fragment               = GL_FRAGMENT_SHADER_BIT, 
            Compute                = GL_COMPUTE_SHADER_BIT, 

            All                    = GL_ALL_SHADER_BITS, 
        };
        enum class StageProperty : gl::enum_t
        {
            ActiveSubroutineUniformLocations     = GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, 
            ActiveSubroutineUniforms             = GL_ACTIVE_SUBROUTINE_UNIFORMS, 
            ActiveSubroutines                    = GL_ACTIVE_SUBROUTINES, 
            ActiveSubroutineUniformMaximumLength = GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, 
            ActiveSubroutineMaximumLength        = GL_ACTIVE_SUBROUTINE_MAX_LENGTH, 
        };
        struct     Pipeline
        {
            enum class Property : gl::enum_t
            {
                ActiveProgram                = GL_ACTIVE_PROGRAM, 
                VertexShader                 = GL_VERTEX_SHADER, 
                TessellationControlShader    = GL_TESS_CONTROL_SHADER, 
                TessellationEvaluationShader = GL_TESS_EVALUATION_SHADER, 
                GeometryShader               = GL_GEOMETRY_SHADER, 
                FragmentShader               = GL_FRAGMENT_SHADER, 
                ComputeShader                = GL_COMPUTE_SHADER, 
                ValidateStatus               = GL_VALIDATE_STATUS, 
                InfoLogLength                = GL_INFO_LOG_LENGTH, 
            };
        };
    };
    enum class ProvokingVertex : gl::enum_t
    {
        FirstVertex = GL_FIRST_VERTEX_CONVENTION, 
        LastVertex  = GL_LAST_VERTEX_CONVENTION, 
    };
    struct     Query
    {
        enum class Counter : gl::enum_t
        {
            Timestamp = GL_TIMESTAMP, 
        };
        enum class Mode : gl::enum_t
        {
            QueryNoWait         = GL_QUERY_NO_WAIT, 
            QueryNoWaitInverted = GL_QUERY_NO_WAIT_INVERTED, 
            QueryRegionNoWait   = GL_QUERY_BY_REGION_NO_WAIT, 
            QueryRegionWait     = GL_QUERY_BY_REGION_WAIT, 
            QueryWait           = GL_QUERY_WAIT, 
            QueryWaitInverted   = GL_QUERY_WAIT_INVERTED, 
        };
        enum class Target : gl::enum_t
        {
            AnySamplesPassed                        = GL_ANY_SAMPLES_PASSED, 
            AnySamplesPassedConservative            = GL_ANY_SAMPLES_PASSED_CONSERVATIVE, 
            ClippingInputPrimitives                 = GL_CLIPPING_INPUT_PRIMITIVES, 
            ClippingOutputPrimitives                = GL_CLIPPING_OUTPUT_PRIMITIVES, 
            ComputeShaderInvocations                = GL_COMPUTE_SHADER_INVOCATIONS, 
            FragmentShaderInvocations               = GL_FRAGMENT_SHADER_INVOCATIONS, 
            GeometryShaderInvocations               = GL_GEOMETRY_SHADER_INVOCATIONS, 
            GeometryShaderPrimitivesEmitted         = GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED, 
            PrimitivesGenerated                     = GL_PRIMITIVES_GENERATED, 
            PrimitivesSubmitted                     = GL_PRIMITIVES_SUBMITTED, 
            SamplesPassed                           = GL_SAMPLES_PASSED, 
            TessellationControlShaderPatches        = GL_TESS_CONTROL_SHADER_PATCHES, 
            TessellationEvaluationShaderInvocations = GL_TESS_EVALUATION_SHADER_INVOCATIONS, 
            TimeElapsed                             = GL_TIME_ELAPSED, 
            Timestamp                               = GL_TIMESTAMP, 
            TransformFeedbackOverflow               = GL_TRANSFORM_FEEDBACK_OVERFLOW,  
            TransformFeedbackPrimitivesWritten      = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, 
            TransformFeedbackStreamOverflow         = GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW, 
            VertexShaderInvocations                 = GL_VERTEX_SHADER_INVOCATIONS, 
            VerticesSubmitted                       = GL_VERTICES_SUBMITTED, 
        };
        enum class ObjectParameter : gl::enum_t
        {
            Result          = GL_QUERY_RESULT, 
            ResultNoWait    = GL_QUERY_RESULT_NO_WAIT, 
            ResultAvailable = GL_QUERY_RESULT_AVAILABLE, 

            Target          = GL_QUERY_TARGET, 
        };
        enum class TargetParameter : gl::enum_t
        {
            Current     = GL_CURRENT_QUERY, 
            CounterBits = GL_QUERY_COUNTER_BITS, 
        };
    };
    struct     RenderBuffer
    {
        enum class Format : gl::enum_t
        {
            R8                = GL_R8, 
            RG8               = GL_RG8, 
            RGB8              = GL_RGB8, 
            RGBA8             = GL_RGBA8, 

            RGBA8_SRGB        = GL_SRGB8_ALPHA8, 

            D16_UNORM         = GL_DEPTH_COMPONENT16, 
            D24_UNORM         = GL_DEPTH_COMPONENT24, 
            D32_FLOAT         = GL_DEPTH_COMPONENT32, 

            D24_UNORM_S8_UINT = GL_DEPTH24_STENCIL8, 
            D32_FLOAT_S8_UINT = GL_DEPTH32F_STENCIL8, 

            S8_UINT           = GL_STENCIL_INDEX8, 
        };
        enum class Target : gl::enum_t
        {
            RenderBuffer = GL_RENDERBUFFER,
        };
    };
    struct     Sampler
    {
        enum class Parameter : gl::enum_t
        {
            BorderColor         = GL_TEXTURE_BORDER_COLOR, 
            CompareMode         = GL_TEXTURE_COMPARE_MODE, 
            CompareFunction     = GL_TEXTURE_COMPARE_FUNC, 
            MagnificationFilter = GL_TEXTURE_MAG_FILTER, 
            MinificationFilter  = GL_TEXTURE_MIN_FILTER, 
            MaximumAnisotropy   = GL_TEXTURE_MAX_ANISOTROPY, 
            LodBias             = GL_TEXTURE_LOD_BIAS, 
            MaximumLod          = GL_TEXTURE_MAX_LOD, 
            MinimumLod          = GL_TEXTURE_MIN_LOD, 
            WrappingS           = GL_TEXTURE_WRAP_S, 
            WrappingT           = GL_TEXTURE_WRAP_T, 
            WrappingR           = GL_TEXTURE_WRAP_R, 
        };
    };
    struct     Shader
    {
        struct Binary
        {
            enum class Format : gl::enum_t
            {

            };
        };
        enum class Parameter : gl::enum_t
        {
            CompileStatus = GL_COMPILE_STATUS, 
            DeleteStatus  = GL_DELETE_STATUS, 
            InfoLogLength = GL_INFO_LOG_LENGTH, 
            SourceLength  = GL_SHADER_SOURCE_LENGTH, 
            SpirVBinary   = GL_SPIR_V_BINARY, 
            Type          = GL_SHADER_TYPE, 
        };
        enum class PrecisionFormat : gl::enum_t
        {
            LowInteger    = GL_LOW_INT, 
            MediumInteger = GL_MEDIUM_INT, 
            HighInteger   = GL_HIGH_INT, 

            LowFloat      = GL_LOW_FLOAT, 
            MediumFloat   = GL_MEDIUM_FLOAT, 
            HighFloat     = GL_HIGH_FLOAT, 
        };
        enum class Type : gl::enum_t
        {
            Vertex                 = GL_VERTEX_SHADER, 
            TessellationControl    = GL_TESS_CONTROL_SHADER, 
            TessellationEvaluation = GL_TESS_EVALUATION_SHADER, 
            Geometry               = GL_GEOMETRY_SHADER, 
            Fragment               = GL_FRAGMENT_SHADER, 
            Compute                = GL_COMPUTE_SHADER, 
        };
        enum class SubroutineParameter : gl::enum_t
        {
            NumberCompatibleSubroutines, 
            CompatibleSubroutines, 
            UniformSize, 
            UniformNameLength, 
        };
    };
    struct     Stencil
    {
        enum class Function : gl::enum_t
        {
            Always       = GL_ALWAYS, 
            Never        = GL_NEVER, 
            Equal        = GL_EQUAL, 
            NotEqual     = GL_NOTEQUAL, 
            Less         = GL_LESS, 
            LessEqual    = GL_LEQUAL, 
            Greater      = GL_GREATER, 
            GreaterEqual = GL_GEQUAL, 
        };
        enum class Face : gl::enum_t
        {
            Front     = GL_FRONT, 
            Back      = GL_BACK, 
            FrontBack = GL_FRONT_AND_BACK, 
        };
        enum class Action : gl::enum_t
        {
            Keep          = GL_KEEP, 
            Zero          = GL_ZERO, 
            Replace       = GL_REPLACE, 
            Increment     = GL_INCR, 
            IncrementWrap = GL_INCR_WRAP, 
            Decrement     = GL_DECR, 
            DecrementWrap = GL_DECR_WRAP, 
            Invert        = GL_INVERT, 
        };
    };
    struct     Synchronization
    {
        enum class FlushingBehavior : gl::enum_t
        {
            Commands = GL_SYNC_FLUSH_COMMANDS_BIT, 
        };
        struct     Object
        {
            enum class Condition : gl::enum_t
            {
                GPUCommandsComplete = GL_SYNC_GPU_COMMANDS_COMPLETE, 
            };
            enum class Flags : gl::enum_t
            {
                None = GL_NONE, 
            };
            enum class Status : gl::enum_t
            {
                Signaled   = GL_SIGNALED, 
                Unsignaled = GL_UNSIGNALED, 
            };
            enum class Type : gl::enum_t
            {
                Fence = GL_SYNC_FENCE, 
            };
        };
        enum class Property : gl::enum_t
        {
            Type      = GL_OBJECT_TYPE, 
            Status    = GL_SYNC_STATUS, 
            Condition = GL_SYNC_CONDITION, 
            Flags     = GL_SYNC_FLAGS, 
        };
        enum class Status : gl::enum_t
        {
            AlreadySignaled    = GL_ALREADY_SIGNALED, 
            TimeoutExpired     = GL_TIMEOUT_EXPIRED, 
            ConditionSatisfied = GL_CONDITION_SATISFIED, 
            WaitFailed         = GL_WAIT_FAILED, 
        };
        enum class Timeout : gl::uint64_t
        {
            Ignored = GL_TIMEOUT_IGNORED, 
        };
    };
    struct     Texture
    {
        enum class BaseFormat : gl::enum_t
        {
            R    = GL_RED, 
            RG   = GL_RG, 
            RGB  = GL_RGB, 
            RGBA = GL_RGBA, 

            D    = GL_DEPTH_COMPONENT, 
            S    = GL_STENCIL_INDEX, 
        };
        enum class ComparisonFunction : gl::enum_t
        {
            Always       = GL_ALWAYS, 
            Never        = GL_NEVER, 

            Equal        = GL_EQUAL, 
            NotEqual     = GL_NOTEQUAL, 

            Less         = GL_LESS, 
            LessEqual    = GL_LEQUAL, 

            Greater      = GL_GREATER, 
            GreaterEqual = GL_GEQUAL, 
        };
        enum class ComparisonMode : gl::enum_t
        {
            None      = GL_NONE, 
            Reference = GL_COMPARE_REF_TO_TEXTURE, 
        };
        enum class CompressedFormat : gl::enum_t
        {
            RGB8_C_ETC2           = GL_COMPRESSED_RGB8_ETC2, 
            RGBA8_CP_ETC2         = GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, 
            RGBA8_C_ETC2_EAC      = GL_COMPRESSED_RGBA8_ETC2_EAC, 

            RGB8_SRGB_C_ETC2      = GL_COMPRESSED_SRGB8_ETC2, 
            RGBA8_SRGB_CP_ETC2    = GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, 
            RGBA8_SRGB_C_ETC2_EAC = GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC, 

            R11_C_EAC             = GL_COMPRESSED_R11_EAC, 
            RG11_C_EAC            = GL_COMPRESSED_RG11_EAC, 
        };
        enum class Format : gl::enum_t
        {
            R8_UNORM          = GL_R8, 
            RG8_UNORM         = GL_RG8, 
            RGB8_UNORM        = GL_RGB8, 
            RGBA8_UNORM       = GL_RGBA8, 

            R16_UNORM         = GL_R16, 
            RG16_UNORM        = GL_RG16, 
            RGB16_UNORM       = GL_RGB16, 
            RGBA16_UNORM      = GL_RGBA16, 

            R8_SNORM          = GL_R8_SNORM, 
            RG8_SNORM         = GL_RG8_SNORM, 
            RGB8_SNORM        = GL_RGB8_SNORM, 
            RGBA8_SNORM       = GL_RGBA8_SNORM, 

            R16_SNORM         = GL_R16_SNORM, 
            RG16_SNORM        = GL_RG16_SNORM, 
            RGB16_SNORM       = GL_RGB16_SNORM, 
            RGBA16_SNORM      = GL_RGBA16_SNORM, 

            RGB8_SRGB         = GL_SRGB8, 
            RGBA8_SRGB        = GL_SRGB8_ALPHA8, 

            R16_FLOAT         = GL_R16F, 
            RG16_FLOAT        = GL_RG16F, 
            RGB16_FLOAT       = GL_RGB16F, 
            RGBA16_FLOAT      = GL_RGBA16F, 

            R32_FLOAT         = GL_R32F, 
            RG32_FLOAT        = GL_RG32F, 
            RGB32_FLOAT       = GL_RGB32F, 
            RGBA32_FLOAT      = GL_RGBA32F, 

            D16_UNORM         = GL_DEPTH_COMPONENT16, 
            D24_UNORM         = GL_DEPTH_COMPONENT24, 
            D32_FLOAT         = GL_DEPTH_COMPONENT32F, 

            D24_UNORM_S8_UINT = GL_DEPTH24_STENCIL8, 
            D32_FLOAT_S8_UINT = GL_DEPTH32F_STENCIL8, 

            S8_UINT           = GL_STENCIL_INDEX8, 
        };
        enum class MagnificationFilter
        {
            Nearest = GL_NEAREST, 
            Linear  = GL_LINEAR, 
        };
        enum class MinificationFilter
        {
            Nearest              = GL_NEAREST, 
            Linear               = GL_LINEAR, 

            NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST, 
            NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR, 

            LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST, 
            LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR, 
        };
        enum class Parameter : gl::enum_t
        {
            BaseLevel           = GL_TEXTURE_BASE_LEVEL, 
            CompareFunction     = GL_TEXTURE_COMPARE_FUNC, 
            CompareMode         = GL_TEXTURE_COMPARE_MODE, 
            DepthStencilMode    = GL_DEPTH_STENCIL_TEXTURE_MODE, 
            LODBias             = GL_TEXTURE_LOD_BIAS, 
            MagnificationFilter = GL_TEXTURE_MAG_FILTER, 
            MaximumLevel        = GL_TEXTURE_MAX_LEVEL, 
            MaximumLOD          = GL_TEXTURE_MAX_LOD, 
            MinificationFilter  = GL_TEXTURE_MIN_FILTER, 
            MinimumLOD          = GL_TEXTURE_MIN_LOD, 
            SwizzleAlpha        = GL_TEXTURE_SWIZZLE_A,
            SwizzleBlue         = GL_TEXTURE_SWIZZLE_B,
            SwizzleGreen        = GL_TEXTURE_SWIZZLE_G,
            SwizzleRed          = GL_TEXTURE_SWIZZLE_R, 
            WrappingR           = GL_TEXTURE_WRAP_R, 
            WrappingS           = GL_TEXTURE_WRAP_S, 
            WrappingT           = GL_TEXTURE_WRAP_T, 
        };
        enum class Target : gl::enum_t
        {
            _1D                 = GL_TEXTURE_1D, 
            _2D                 = GL_TEXTURE_2D, 
            _3D                 = GL_TEXTURE_3D, 

            _1DArray            = GL_TEXTURE_1D_ARRAY, 
            _2DArray            = GL_TEXTURE_2D_ARRAY,
            _2DMultisample      = GL_TEXTURE_2D_MULTISAMPLE, 
            _2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 

            CubeMap             = GL_TEXTURE_CUBE_MAP, 
            CubeMapArray        = GL_TEXTURE_CUBE_MAP_ARRAY, 

            Rectangle           = GL_TEXTURE_RECTANGLE, 
            Buffer              = GL_TEXTURE_BUFFER, 
        };
        enum class Type : gl::enum_t
        {
            Byte               = GL_BYTE, 
            UnsignedByte       = GL_UNSIGNED_BYTE, 
            Short              = GL_SHORT, 
            UnsignedShort      = GL_UNSIGNED_SHORT, 
            Integer            = GL_INT, 
            UnsignedInteger    = GL_UNSIGNED_INT, 
            Float              = GL_FLOAT, 
        };
        enum class Wrapping : gl::enum_t
        {
            ClampToEdge         = GL_CLAMP_TO_EDGE, 
            ClampToBorder       = GL_CLAMP_TO_BORDER, 
            Repeat              = GL_REPEAT, 
            MirroredRepeat      = GL_MIRRORED_REPEAT, 
            MirroredClampToEdge = GL_MIRROR_CLAMP_TO_EDGE, 
        };
    };
    struct     Tessellation
    {
        enum class GenerationMode : gl::enum_t
        {
            Quads     = GL_QUADS, 
            Triangles = GL_TRIANGLES, 
            Isolines  = GL_ISOLINES, 
        };
        enum class Spacing : gl::enum_t
        {
            Equal          = GL_EQUAL, 
            FractionalEven = GL_FRACTIONAL_EVEN, 
            FractionalOdd  = GL_FRACTIONAL_ODD, 
        };
        enum class VertexOrder : gl::enum_t
        {
            Clockwise        = GL_CW, 
            CounterClockwise = GL_CCW, 
        };
    };
    struct     TransformFeedback
    {
        enum class BufferMode : gl::enum_t
        {
            InterleavedAttributes = GL_INTERLEAVED_ATTRIBS, 
            SeparateAttributes    = GL_SEPARATE_ATTRIBS, 
        };
        enum class Property : gl::enum_t
        {
            BufferBinding = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, 
            BufferStart   = GL_TRANSFORM_FEEDBACK_BUFFER_START, 
            BufferSize    = GL_TRANSFORM_FEEDBACK_BUFFER_SIZE, 
            Paused        = GL_TRANSFORM_FEEDBACK_PAUSED, 
            Active        = GL_TRANSFORM_FEEDBACK_ACTIVE, 
        };
        enum class PrimitiveMode : gl::enum_t
        {
            Points    = GL_POINTS, 
            Lines     = GL_LINES, 
            Triangles = GL_TRIANGLES, 
        };
    };
    struct     Uniform
    {
        enum class Property : gl::enum_t
        {
            Type                     = GL_UNIFORM_TYPE, 
            Size                     = GL_UNIFORM_SIZE, 
            NameLength               = GL_UNIFORM_NAME_LENGTH, 
            BlockIndex               = GL_UNIFORM_BLOCK_INDEX, 
            Offset                   = GL_UNIFORM_OFFSET, 
            ArrayStride              = GL_UNIFORM_ARRAY_STRIDE, 
            MatrixStride             = GL_UNIFORM_MATRIX_STRIDE, 
            IsRowMajor               = GL_UNIFORM_IS_ROW_MAJOR, 
            AtomicCounterBufferIndex = GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX, 
        };
        enum class Type : gl::enum_t 
        {
            Float                                    = GL_FLOAT, 
            Vector2f                                 = GL_FLOAT_VEC2, 
            Vector3f                                 = GL_FLOAT_VEC3, 
            Vector4f                                 = GL_FLOAT_VEC4, 
            Double                                   = GL_DOUBLE, 
            Vector2d                                 = GL_DOUBLE_VEC2, 
            Vector3d                                 = GL_DOUBLE_VEC3, 
            Vector4d                                 = GL_DOUBLE_VEC4, 
            Integer                                  = GL_INT, 
            Vector2i                                 = GL_INT_VEC2, 
            Vector3i                                 = GL_INT_VEC3, 
            Vector4i                                 = GL_INT_VEC4, 
            UnsignedInteger                          = GL_UNSIGNED_INT, 
            Vector2u                                 = GL_UNSIGNED_INT_VEC2, 
            Vector3u                                 = GL_UNSIGNED_INT_VEC3, 
            Vector4u                                 = GL_UNSIGNED_INT_VEC4, 
            Boolean                                  = GL_BOOL, 
            Vector2b                                 = GL_BOOL_VEC2, 
            Vector3b                                 = GL_BOOL_VEC3, 
            Vector4b                                 = GL_BOOL_VEC4, 
            Matrix2f                                 = GL_FLOAT_MAT2, 
            Matrix3f                                 = GL_FLOAT_MAT3, 
            Matrix4f                                 = GL_FLOAT_MAT4, 
            Matrix2x3f                               = GL_FLOAT_MAT2x3, 
            Matrix2x4f                               = GL_FLOAT_MAT2x4, 
            Matrix3x2f                               = GL_FLOAT_MAT3x2, 
            Matrix3x4f                               = GL_FLOAT_MAT3x4, 
            Matrix4x2f                               = GL_FLOAT_MAT4x2, 
            Matrix4x3f                               = GL_FLOAT_MAT4x3, 
            Matrix2d                                 = GL_DOUBLE_MAT2, 
            Matrix3d                                 = GL_DOUBLE_MAT3, 
            Matrix4d                                 = GL_DOUBLE_MAT4, 
            Matrix2x3d                               = GL_DOUBLE_MAT2x3, 
            Matrix2x4d                               = GL_DOUBLE_MAT2x4, 
            Matrix3x2d                               = GL_DOUBLE_MAT3x2, 
            Matrix3x4d                               = GL_DOUBLE_MAT3x4, 
            Matrix4x2d                               = GL_DOUBLE_MAT4x2, 
            Matrix4x3d                               = GL_DOUBLE_MAT4x3, 
            Sampler1D                                = GL_SAMPLER_1D, 
            Sampler2D                                = GL_SAMPLER_2D, 
            Sampler3D                                = GL_SAMPLER_3D, 
            SamplerCube                              = GL_SAMPLER_CUBE, 
            Sampler1DShadow                          = GL_SAMPLER_1D_SHADOW, 
            Sampler2DShadow                          = GL_SAMPLER_2D_SHADOW, 
            Sampler1DArray                           = GL_SAMPLER_1D_ARRAY, 
            Sampler2DArray                           = GL_SAMPLER_2D_ARRAY, 
            Sampler1DArrayShadow                     = GL_SAMPLER_1D_ARRAY_SHADOW, 
            Sampler2DArrayShadow                     = GL_SAMPLER_2D_ARRAY_SHADOW, 
            Sampler2DMultisample                     = GL_SAMPLER_2D_MULTISAMPLE, 
            Sampler2DMultisampleArray                = GL_SAMPLER_2D_MULTISAMPLE_ARRAY, 
            SamplerCubeShadow                        = GL_SAMPLER_CUBE_SHADOW, 
            SamplerBuffer                            = GL_SAMPLER_BUFFER, 
            Sampler2DRectangle                       = GL_SAMPLER_2D_RECT, 
            Sampler2DRectangleShadow                 = GL_SAMPLER_2D_RECT_SHADOW, 
            IntegerSampler1D                         = GL_INT_SAMPLER_1D, 
            IntegerSampler2D                         = GL_INT_SAMPLER_2D, 
            IntegerSampler3D                         = GL_INT_SAMPLER_3D, 
            IntegerSamplerCube                       = GL_INT_SAMPLER_CUBE, 
            IntegerSampler1DArray                    = GL_INT_SAMPLER_1D_ARRAY, 
            IntegerSampler2DArray                    = GL_INT_SAMPLER_2D_ARRAY, 
            IntegerSampler2DMultisample              = GL_INT_SAMPLER_2D_MULTISAMPLE, 
            IntegerSampler2DMultisampleArray         = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, 
            IntegerSamplerBuffer                     = GL_INT_SAMPLER_BUFFER, 
            IntegerSampler2DRectangle                = GL_INT_SAMPLER_2D_RECT, 
            UnsignedIntegerSampler1D                 = GL_UNSIGNED_INT_SAMPLER_1D, 
            UnsignedIntegerSampler2D                 = GL_UNSIGNED_INT_SAMPLER_2D, 
            UnsignedIntegerSampler3D                 = GL_UNSIGNED_INT_SAMPLER_3D, 
            UnsignedIntegerSamplerCube               = GL_UNSIGNED_INT_SAMPLER_CUBE, 
            UnsignedIntegerSampler1DArray            = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY, 
            UnsignedIntegerSampler2DArray            = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY, 
            UnsignedIntegerSampler2DMultisample      = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE, 
            UnsignedIntegerSampler2DMultisampleArray = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, 
            UnsignedIntegerSamplerBuffer             = GL_UNSIGNED_INT_SAMPLER_BUFFER, 
            UnsignedIntegerSampler2DRectangle        = GL_UNSIGNED_INT_SAMPLER_2D_RECT, 
            Image1D                                  = GL_IMAGE_1D, 
            Image2D                                  = GL_IMAGE_2D, 
            Image3D                                  = GL_IMAGE_3D, 
            Image2DRectangle                         = GL_IMAGE_2D_RECT, 
            ImageCube                                = GL_IMAGE_CUBE, 
            ImageBuffer                              = GL_IMAGE_BUFFER, 
            Image1DArray                             = GL_IMAGE_1D_ARRAY, 
            Image2DArray                             = GL_IMAGE_2D_ARRAY, 
            Image2DMultisample                       = GL_IMAGE_2D_MULTISAMPLE, 
            Image2DMultisampleArray                  = GL_IMAGE_2D_MULTISAMPLE_ARRAY, 
            IntegerImage1D                           = GL_INT_IMAGE_1D, 
            IntegerImage2D                           = GL_INT_IMAGE_2D, 
            IntegerImage3D                           = GL_INT_IMAGE_3D, 
            IntegerImage2DRectangle                  = GL_INT_IMAGE_2D_RECT, 
            IntegerImageCube                         = GL_INT_IMAGE_CUBE, 
            IntegerImageBuffer                       = GL_INT_IMAGE_BUFFER, 
            IntegerImage1DArray                      = GL_INT_IMAGE_1D_ARRAY, 
            IntegerImage2DArray                      = GL_INT_IMAGE_2D_ARRAY, 
            IntegerImage2DMultisample                = GL_INT_IMAGE_2D_MULTISAMPLE, 
            IntegerImage2DMultisampleArray           = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY, 
            UnsignedIntegerImage1D                   = GL_UNSIGNED_INT_IMAGE_1D, 
            UnsignedIntegerImage2D                   = GL_UNSIGNED_INT_IMAGE_2D, 
            UnsignedIntegerImage3D                   = GL_UNSIGNED_INT_IMAGE_3D, 
            UnsignedIntegerImage2DRectangle          = GL_UNSIGNED_INT_IMAGE_2D_RECT, 
            UnsignedIntegerImageCube                 = GL_UNSIGNED_INT_IMAGE_CUBE, 
            UnsignedIntegerImageBuffer               = GL_UNSIGNED_INT_IMAGE_BUFFER, 
            UnsignedIntegerImage1DArray              = GL_UNSIGNED_INT_IMAGE_1D_ARRAY, 
            UnsignedIntegerImage2DArray              = GL_UNSIGNED_INT_IMAGE_2D_ARRAY, 
            UnsignedIntegerImage2DMultisample        = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE, 
            UnsignedIntegerImage2DMultisampleArray   = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY, 
            UnsignedIntegerAtomicCounter             = GL_UNSIGNED_INT_ATOMIC_COUNTER, 
        };
    };
    struct     UniformBlock
    {
        enum class Info : gl::enum_t
        {
            Binding                                  = GL_UNIFORM_BLOCK_BINDING, 
            DataSize                                 = GL_UNIFORM_BLOCK_DATA_SIZE, 
            NameLength                               = GL_UNIFORM_BLOCK_NAME_LENGTH, 
            ActiveUniforms                           = GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, 
            ActiveUniformIndices                     = GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, 
            ReferencedByVertexShader                 = GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, 
            ReferencedByTessellationControlShader    = GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, 
            ReferencedByTessellationEvaluationShader = GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, 
            ReferencedByGeometryShader               = GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, 
            ReferencedByFragmentShader               = GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, 
            ReferencedByComputeShader                = GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER, 
        };
    };
    struct     VertexArray
    {
        struct Attribute
        {
            enum class Format : gl::enum_t
            {
                Integer,
                Float,
                Double,
            };
            enum class Type : gl::enum_t
            {
                Byte                                  = GL_BYTE, 
                Double                                = GL_DOUBLE, 
                Fixed                                 = GL_FIXED, 
                Float                                 = GL_FLOAT, 
                HalfFloat                             = GL_HALF_FLOAT, 
                Integer                               = GL_INT, 
                Int_2_10_10_10_Rev                    = GL_INT_2_10_10_10_REV, 
                Short                                 = GL_SHORT, 
                UnsignedByte                          = GL_UNSIGNED_BYTE, 
                UnsignedShort                         = GL_UNSIGNED_SHORT, 
                UnsignedInteger                       = GL_UNSIGNED_INT, 
                UnsignedInteger_2_10_10_10_Rev        = GL_UNSIGNED_INT_2_10_10_10_REV, 
                UnsignedInteger_10_11_11_11_Float_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV, 
            };
        };
        enum class IndexedParameter : gl::enum_t
        {
            Enabled        = GL_VERTEX_ATTRIB_ARRAY_ENABLED, 
            Size           = GL_VERTEX_ATTRIB_ARRAY_SIZE, 
            Stride         = GL_VERTEX_ATTRIB_ARRAY_STRIDE, 
            Type           = GL_VERTEX_ATTRIB_ARRAY_TYPE, 
            IsNormalized   = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, 
            IsIntegerData  = GL_VERTEX_ATTRIB_ARRAY_INTEGER, 
            IsLongData     = GL_VERTEX_ATTRIB_ARRAY_LONG, 
            Divisor        = GL_VERTEX_ATTRIB_ARRAY_DIVISOR, 
            RelativeOffset = GL_VERTEX_ATTRIB_RELATIVE_OFFSET, 

            BindingOffset  = GL_VERTEX_BINDING_OFFSET,
        };
        enum class Parameter : gl::enum_t
        {
            ElementArrayBufferBinding = GL_ELEMENT_ARRAY_BUFFER_BINDING, 
        };
    };
    struct     VertexAttribute
    {
        enum class Address : gl::enum_t
        {
            Pointer = GL_VERTEX_ATTRIB_ARRAY_POINTER, 
        };
        enum class Parameter : gl::enum_t
        {
            Enabled        = GL_VERTEX_ATTRIB_ARRAY_ENABLED, 
            Size           = GL_VERTEX_ATTRIB_ARRAY_SIZE, 
            Stride         = GL_VERTEX_ATTRIB_ARRAY_STRIDE, 
            Type           = GL_VERTEX_ATTRIB_ARRAY_TYPE, 
            IsNormalized   = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, 
            IsIntegerData  = GL_VERTEX_ATTRIB_ARRAY_INTEGER,
            IsLongData     = GL_VERTEX_ATTRIB_ARRAY_LONG,
            Divisor        = GL_VERTEX_ATTRIB_ARRAY_DIVISOR, 
            BufferBinding  = GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, 
            Binding        = GL_VERTEX_ATTRIB_BINDING, 
            RelativeOffset = GL_VERTEX_ATTRIB_RELATIVE_OFFSET, 
        };
        enum class Pointer : gl::enum_t
        {
            Array = GL_VERTEX_ATTRIB_ARRAY_POINTER, 
        };
    };
}
namespace fox::gfx::api::gl
{
    template<> struct BitmaskTraits<glf::Buffer::Mask>            { static constexpr bool enable_bitmask_operations = true; };
    template<> struct BitmaskTraits<glf::FrameBuffer::Source>     { static constexpr bool enable_bitmask_operations = true; };
    template<> struct BitmaskTraits<glf::Memory::Barrier>         { static constexpr bool enable_bitmask_operations = true; };
    template<> struct BitmaskTraits<glf::Memory::RegionalBarrier> { static constexpr bool enable_bitmask_operations = true; };
}
