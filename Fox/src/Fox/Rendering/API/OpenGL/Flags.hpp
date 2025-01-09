#pragma once

#include "stdafx.hpp"

#include "Fox/Rendering/API/OpenGL/Types.hpp"

namespace fox::gfx::api::gl::flg
{
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
        enum class Access : gl::enum_t
        {
            Read      = GL_READ_ONLY,
            Write     = GL_WRITE_ONLY,
            ReadWrite = GL_READ_WRITE,
        };
        enum class IndexedTarget : gl::enum_t
        {
            AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER,
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
            UniformBuffer           = GL_UNIFORM_BUFFER,
            ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER,
        };
        enum class Mapping : gl::enum_t
        {
            Read      = GL_READ_ONLY, 
            Write     = GL_WRITE_ONLY, 
            ReadWrite = GL_READ_WRITE, 
        };
        enum       Mask : gl::bitfield_t
        {
            ColorBuffer   = GL_COLOR_BUFFER_BIT,
            DepthBuffer   = GL_DEPTH_BUFFER_BIT,
            StencilBuffer = GL_STENCIL_BUFFER_BIT,

            All = ColorBuffer | DepthBuffer | StencilBuffer
        };
        enum       StorageFlags : gl::bitfield_t
        {
            None           = GL_NONE, 

            DynamicStorage = GL_DYNAMIC_STORAGE_BIT,
            MapRead        = GL_MAP_READ_BIT,
            MapWrite       = GL_MAP_WRITE_BIT,
            MapPersistent  = GL_MAP_PERSISTENT_BIT,
            MapCoherent    = GL_MAP_COHERENT_BIT,
            ClientStorage  = GL_CLIENT_STORAGE_BIT,
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
    };
    enum class Capability : gl::enum_t
    {
        Blending                 = GL_BLEND, 
        FaceCulling              = GL_CULL_FACE, 

        DepthTest                = GL_DEPTH_TEST, 
        StencilTest              = GL_STENCIL_TEST, 
        ScissorTest              = GL_SCISSOR_TEST, 

        Multisampling            = GL_MULTISAMPLE, 
        MultisampleCoverage      = GL_SAMPLE_COVERAGE, 
        MultisampleAlphaCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE, 

        FrameBufferSRGB          = GL_FRAMEBUFFER_SRGB, 

        DebugOutput              = GL_DEBUG_OUTPUT, 
        DebugOutputSynchronous   = GL_DEBUG_OUTPUT_SYNCHRONOUS,
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
        MajorVersion         = GL_MAJOR_VERSION, 
        MinorVersion         = GL_MINOR_VERSION, 
        ContextFlags         = GL_CONTEXT_FLAGS, 
        ContextProfile       = GL_CONTEXT_PROFILE_MASK, 
        ExtensionCount       = GL_NUM_EXTENSIONS, 

        ArrayBufferBinding   = GL_ARRAY_BUFFER_BINDING, 
        ElementBufferBinding = GL_ELEMENT_ARRAY_BUFFER_BINDING, 
        RenderBufferBinding  = GL_RENDERBUFFER_BINDING, 
        FrameBufferBinding   = GL_FRAMEBUFFER_BINDING, 

        ActiveTexture        = GL_ACTIVE_TEXTURE, 
        CurrentProgram       = GL_CURRENT_PROGRAM, 

        Viewport             = GL_VIEWPORT, 
        ScissorBox           = GL_SCISSOR_BOX, 

        Blending             = GL_BLEND, 

        DepthRange           = GL_DEPTH_RANGE, 
        DepthTest            = GL_DEPTH_TEST, 
        DepthFunction        = GL_DEPTH_FUNC, 
        StencilFunctioin     = GL_STENCIL_FUNC, 

        PointSize            = GL_POINT_SIZE, 
        LineWidth            = GL_LINE_WIDTH, 
        PolygonMode          = GL_POLYGON_MODE, 

        MaxTextureSize       = GL_MAX_TEXTURE_SIZE, 
        MaxVertexAttributes  = GL_MAX_VERTEX_ATTRIBS,                      
    };
    struct     Debug
    {
        enum class Source : gl::enum_t 
        {
            DebugSourceAPI            = GL_DEBUG_SOURCE_API,
            DebugSourceWindowSystem   = GL_DEBUG_SOURCE_WINDOW_SYSTEM,
            DebugSourceShaderCompiler = GL_DEBUG_SOURCE_SHADER_COMPILER,
            DebugSourceThirdParty     = GL_DEBUG_SOURCE_THIRD_PARTY,
            DebugSourceApplication    = GL_DEBUG_SOURCE_APPLICATION,
            DebugSourceOther          = GL_DEBUG_SOURCE_OTHER, 

            DontCare                  = GL_DONT_CARE, 
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
            Read  = GL_READ_FRAMEBUFFER, 
            Write = GL_DRAW_FRAMEBUFFER, 
        };
        enum class Filter
        {
            Nearest = GL_NEAREST, 
            Linear  = GL_LINEAR, 
        };
    };
    struct     Memory
    {
        enum       Barrier : gl::bitfield_t
        {
            VertexAttributeArray = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT,
            ElementArray         = GL_ELEMENT_ARRAY_BARRIER_BIT,
            Uniform              = GL_UNIFORM_BARRIER_BIT,
            TextureFetch         = GL_TEXTURE_FETCH_BARRIER_BIT,
            ShaderImageAccess    = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
            Command              = GL_COMMAND_BARRIER_BIT,
            PixelBuffer          = GL_PIXEL_BUFFER_BARRIER_BIT,
            TextureUpdate        = GL_TEXTURE_UPDATE_BARRIER_BIT,
            BufferUpdate         = GL_BUFFER_UPDATE_BARRIER_BIT,
            FrameBuffer          = GL_FRAMEBUFFER_BARRIER_BIT,
            TransformFeedback    = GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
            AtomicCounter        = GL_ATOMIC_COUNTER_BARRIER_BIT,
            ShaderStorage        = GL_SHADER_STORAGE_BARRIER_BIT,
            QueryBuffer          = GL_QUERY_BUFFER_BARRIER_BIT,

            All                  = GL_ALL_BARRIER_BITS,
        };
    };
    enum class Orientation : gl::enum_t
    {
        Clockwise        = GL_CW, 
        CounterClockwise = GL_CCW, 
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
    struct     Polygon
    {
        enum class Mode : gl::enum_t
        {
            Point = GL_POINT, 
            Line  = GL_LINE, 
            Fill  = GL_FILL, 
        };
    };
    struct     Program
    {
        enum class Parameter : gl::enum_t
        {
            ActiveAttributeMaxLength        = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, 
            ActiveAttributes                = GL_ACTIVE_ATTRIBUTES, 
            ActiveUniformBlockCount         = GL_ACTIVE_UNIFORM_BLOCKS, 
            ActiveUniformBlockMaxNameLength = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, 
            ActiveUniformCount              = GL_ACTIVE_UNIFORMS, 
            ActiveUniformMaxLength          = GL_ACTIVE_UNIFORM_MAX_LENGTH, 
            AttachedShaderCount             = GL_ATTACHED_SHADERS, 
            BinaryLength                    = GL_PROGRAM_BINARY_LENGTH, 
            ComputeWorkGroupSize            = GL_COMPUTE_WORK_GROUP_SIZE, 
            DeleteStatus                    = GL_DELETE_STATUS, 
            GeometryInputType               = GL_GEOMETRY_INPUT_TYPE, 
            GeometryOutputType              = GL_GEOMETRY_INPUT_TYPE, 
            GeometryVerticesOut             = GL_GEOMETRY_VERTICES_OUT, 
            InfoLogLength                   = GL_INFO_LOG_LENGTH, 
            LinkStatus                      = GL_LINK_STATUS, 
            Separable                       = GL_PROGRAM_SEPARABLE, 
            ValidateStatus                  = GL_VALIDATE_STATUS, 
        };
    };
    enum class ProvokingVertex : gl::enum_t
    {
        FirstVertex = GL_FIRST_VERTEX_CONVENTION, 
        LastVertex  = GL_LAST_VERTEX_CONVENTION, 
    };
    struct     Query
    {
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
            AnySamplesPassed                   = GL_ANY_SAMPLES_PASSED, 
            AnySamplesPassedConservative       = GL_ANY_SAMPLES_PASSED_CONSERVATIVE, 
            PrimitivesGenerated                = GL_PRIMITIVES_GENERATED, 
            SamplesPassed                      = GL_SAMPLES_PASSED, 
            TimeElapsed                        = GL_TIME_ELAPSED, 
            Timestamp                          = GL_TIMESTAMP, 
            TransformFeedbackPrimitivesWritten = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, 
        };
        enum class Parameter : gl::enum_t
        {
            Result          = GL_QUERY_RESULT, 
            ResultNoWait    = GL_QUERY_RESULT_NO_WAIT, 
            ResultAvailable = GL_QUERY_RESULT_AVAILABLE, 
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
            TextureWrapS       = GL_TEXTURE_WRAP_S, 
            TextureWrapT       = GL_TEXTURE_WRAP_T, 
            TextureWrapR       = GL_TEXTURE_WRAP_R, 
            TextureMinFilter   = GL_TEXTURE_MIN_FILTER, 
            TextureMagFilter   = GL_TEXTURE_MAG_FILTER, 
            TextureBorderColor = GL_TEXTURE_BORDER_COLOR, 
            TextureMinLod      = GL_TEXTURE_MIN_LOD, 
            TextureMaxLod      = GL_TEXTURE_MAX_LOD, 
            TextureLodBias     = GL_TEXTURE_LOD_BIAS, 
            TextureCompareMode = GL_TEXTURE_COMPARE_MODE, 
            TextureCompareFunc = GL_TEXTURE_COMPARE_FUNC, 
        };
    };
    struct     Shader
    {
        enum class Parameter : gl::enum_t
        {
            CompileStatus = GL_COMPILE_STATUS, 
            DeleteStatus  = GL_DELETE_STATUS, 
            InfoLogLength = GL_INFO_LOG_LENGTH, 
            SourceLength  = GL_SHADER_SOURCE_LENGTH, 
            Type          = GL_SHADER_TYPE, 
        };
        enum class Type : gl::enum_t
        {
            Compute                = GL_COMPUTE_SHADER, 
            Fragment               = GL_FRAGMENT_SHADER, 
            Geometry               = GL_GEOMETRY_SHADER, 
            TessellationControl    = GL_TESS_CONTROL_SHADER, 
            TessellationEvaluation = GL_TESS_EVALUATION_SHADER, 
            Vertex                 = GL_VERTEX_SHADER, 
        };
        enum class Stage : gl::bitfield_t
        {
            Vertex                 = GL_VERTEX_SHADER_BIT, 
            Fragment               = GL_FRAGMENT_SHADER_BIT, 
            Geometry               = GL_GEOMETRY_SHADER_BIT, 
            TessellationControl    = GL_TESS_CONTROL_SHADER_BIT, 
            TessellationEvaluation = GL_TESS_EVALUATION_SHADER_BIT, 
            Compute                = GL_COMPUTE_SHADER_BIT, 
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
    struct     Texture
    {
        enum class BaseFormat : gl::enum_t
        {
            R       = GL_RED, 
            RG      = GL_RG, 
            RGB     = GL_RGB, 
            RGBA    = GL_RGBA, 
            Depth   = GL_DEPTH_COMPONENT, 
            Stencil = GL_STENCIL_INDEX, 
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
        enum class MinificationFilter
        {
            Nearest              = GL_NEAREST, 
            Linear               = GL_LINEAR, 

            NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST, 
            NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR, 

            LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST, 
            LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR, 
        };
        enum class MagnificationFilter
        {
            Nearest = GL_NEAREST, 
            Linear  = GL_LINEAR, 
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
        enum class Wrapping : gl::enum_t
        {
            ClampToEdge         = GL_CLAMP_TO_EDGE, 
            ClampToBorder       = GL_CLAMP_TO_BORDER, 
            Repeat              = GL_REPEAT, 
            MirroredRepeat      = GL_MIRRORED_REPEAT, 
            MirroredClampToEdge = GL_MIRROR_CLAMP_TO_EDGE, 
        };
    };
    struct     TransformFeedback
    {
        enum class PrimitiveMode : gl::enum_t
        {
            Points    = GL_POINTS, 
            Lines     = GL_LINES, 
            Triangles = GL_TRIANGLES, 
        };
    };
    enum class Type
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
}
