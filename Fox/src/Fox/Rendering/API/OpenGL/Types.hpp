#pragma once

#include <stdafx.hpp>

#include "glad/gl.h"
#include "glfw/glfw3.h"

namespace fox::gfx::api::gl
{
    using bool_t     = GLboolean;
    using char_t     = GLchar;
    using int8_t     = GLbyte;
    using uint8_t    = GLubyte;
    using int16_t    = GLshort;
    using uint16_t   = GLushort;
    using int32_t    = GLint;
    using uint32_t   = GLuint;
    using int64_t    = GLint64;
    using uint64_t   = GLuint64;
    using float16_t  = GLhalf;
    using float32_t  = GLfloat;
    using float64_t  = GLdouble;

    using size_t     = GLsizei;
    using enum_t     = GLenum;
    using intptr_t   = GLintptr;
    using sizeptr_t  = GLsizeiptr;
    using sync_t     = GLsync;
    using bitfield_t = GLbitfield;



    enum class handle_t   : gl::uint32_t {}; //Strong alias for OpenGL Object id's
    enum class query_t    : gl::uint32_t {}; //Strong alias for OpenGL Query id's
    enum class index_t    : gl::uint32_t {}; //Strong alias for OpenGL Index bindings
    enum class location_t : gl::uint32_t {}; //Strong alias for OpenGL Shader locations
    enum class align_t    : gl::uint32_t {}; //Strong alias for OpenGL memory alignment



    enum : gl::bool_t
    {
        False = GL_FALSE,
        True  = GL_TRUE,
    };
    enum : gl::uint32_t
    {
        NullObject = gl::uint32_t{}, 
    };
    enum : gl::enum_t
    {
        DontCare = GL_DONT_CARE, 
    };

    enum class DataType : gl::enum_t
    {
        Boolean       = GL_BOOL, 
        Byte          = GL_BYTE, 
        UnsignedByte  = GL_UNSIGNED_BYTE, 
        Int           = GL_INT, 
        UnsignedInt   = GL_UNSIGNED_INT, 
        Short         = GL_SHORT, 
        UnsignedShort = GL_UNSIGNED_SHORT, 
        Float         = GL_FLOAT, 
        Double        = GL_DOUBLE, 
    };



    struct Object
    {
    public:
        gl::handle_t handle() const
        {
            return m_handle;
        }

    protected:
        Object()  = default;
        ~Object() = default;
        Object(Object&& other) noexcept = default;

        Object& operator=(Object&& other) noexcept = default;

        gl::handle_t m_handle{};
    };

    struct Flags
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
            enum       Mask : gl::bitfield_t
            {
                ColorBuffer   = GL_COLOR_BUFFER_BIT,
                DepthBuffer   = GL_DEPTH_BUFFER_BIT,
                StencilBuffer = GL_STENCIL_BUFFER_BIT,

                All = ColorBuffer | DepthBuffer | StencilBuffer
            };
            enum class Access : gl::enum_t
            {
                Read      = GL_READ_ONLY,
                Write     = GL_WRITE_ONLY,
                ReadWrite = GL_READ_WRITE,
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
            enum class TargetBase : gl::enum_t
            {
                AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER,
                TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
                UniformBuffer           = GL_UNIFORM_BUFFER,
                ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER,
            };
            enum class TargetRange : gl::enum_t
            {
                TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
                UniformBuffer           = GL_UNIFORM_BUFFER,
            };
            enum       StorageFlags : gl::bitfield_t
            {
                None           = 0, 
                DynamicStorage = GL_DYNAMIC_STORAGE_BIT,
                MapRead        = GL_MAP_READ_BIT,
                MapWrite       = GL_MAP_WRITE_BIT,
                MapPersistent  = GL_MAP_PERSISTENT_BIT,
                MapCoherent    = GL_MAP_COHERENT_BIT,
                ClientStorage  = GL_CLIENT_STORAGE_BIT,
            };
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
        enum class Capability : gl::enum_t
        {
            Blending                 = GL_BLEND, 
            DepthTest                = GL_DEPTH_TEST, 
            FaceCulling              = GL_CULL_FACE, 
            ScissorTest              = GL_SCISSOR_TEST, 
            StencilTest              = GL_STENCIL_TEST, 
            MultisampleCoverage      = GL_SAMPLE_COVERAGE, 
            MultisampleAlphaCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE, 

            Multisampling            = GL_MULTISAMPLE, 
            FrameBufferSRGB          = GL_FRAMEBUFFER_SRGB, 

            DebugOutput              = GL_DEBUG_OUTPUT, 
            DebugOutputSynchronous   = GL_DEBUG_OUTPUT_SYNCHRONOUS,
        };
        struct     Context
        {
            enum class Flag
            {
                DebugBit             = GL_CONTEXT_FLAG_DEBUG_BIT, 
                ForwardCompatibleBit = GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT, 
                NoErrorBit           = GL_CONTEXT_FLAG_NO_ERROR_BIT,
                RobustAccessBit      = GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT,
            };
            enum class Profile
            {
                Core          = GL_CONTEXT_CORE_PROFILE_BIT, 
                Compatibility = GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, 
            };
        };
        enum class Data : gl::enum_t
        {
            MajorVersion         = GL_MAJOR_VERSION, 
            MinorVersion         = GL_MINOR_VERSION, 
            ContextFlags         = GL_CONTEXT_FLAGS, 
            ContextProfile       = GL_CONTEXT_PROFILE_MASK, 
            ExtensionCount       = GL_NUM_EXTENSIONS, 

            Blend                = GL_BLEND, 
            DepthTest            = GL_DEPTH_TEST, 

            ArrayBufferBinding   = GL_ARRAY_BUFFER_BINDING, 
            ElementBufferBinding = GL_ELEMENT_ARRAY_BUFFER_BINDING, 

            Viewport             = GL_VIEWPORT, 
            ScissorBox           = GL_SCISSOR_BOX, 
            FrameBufferBinding   = GL_FRAMEBUFFER_BINDING, 
            RenderBufferBinding  = GL_RENDERBUFFER_BINDING, 
            ActiveTexture        = GL_ACTIVE_TEXTURE, 
                                 
            CurrentProgram       = GL_CURRENT_PROGRAM, 
            MaxTextureSize       = GL_MAX_TEXTURE_SIZE, 
            MaxVertexAttributes  = GL_MAX_VERTEX_ATTRIBS, 

            DepthFunction        = GL_DEPTH_FUNC, 
            DepthRange           = GL_DEPTH_RANGE, 
            StencilFunctioin     = GL_STENCIL_FUNC, 
                                 
            PolygonMode          = GL_POLYGON_MODE, 
            LineWidth            = GL_LINE_WIDTH, 
            PointSize            = GL_POINT_SIZE, 
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
        struct     Draw
        {
            enum class Mode : gl::enum_t
            {
                Points                 = GL_POINTS,
                LineStrip              = GL_LINE_STRIP,
                LineLoop               = GL_LINE_LOOP,
                Lines                  = GL_LINES,
                LineStripAdjacency     = GL_LINE_STRIP_ADJACENCY,
                LinesAdjacency         = GL_LINES_ADJACENCY,
                TriangleStrip          = GL_TRIANGLE_STRIP,
                TriangleFan            = GL_TRIANGLE_FAN,
                Triangles              = GL_TRIANGLES,
                TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
                TrianglesAdjacency     = GL_TRIANGLES_ADJACENCY,
                Patches                = GL_PATCHES
            };
            enum class Type : gl::enum_t
            {
                UnsignedByte  = GL_UNSIGNED_BYTE, 
                UnsignedShort = GL_UNSIGNED_SHORT, 
                UnsignedInt   = GL_UNSIGNED_INT, 
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
        struct     Culling
        {
            enum class Face : gl::enum_t
            {
                Front     = GL_FRONT, 
                Back      = GL_BACK, 
                FrontBack = GL_FRONT_AND_BACK, 
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

            enum class Buffer
            {
                Color = GL_COLOR, 
                Depth = GL_DEPTH, 
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
        enum class Orientation : gl::enum_t
        {
            Clockwise        = GL_CW, 
            CounterClockwise = GL_CCW, 
        };
        struct     Program
        {
            enum class Parameter
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
        };
        struct     Texture
        {
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
        struct     Patch
        {
            enum class Parameter : gl::enum_t
            {
                PatchVertices          = GL_PATCH_VERTICES, 
                PatchDefaultOuterLevel = GL_PATCH_DEFAULT_OUTER_LEVEL, 
                PatchDefaultInterLevel = GL_PATCH_DEFAULT_INNER_LEVEL, 
            };
        };
        enum class ProvokingVertex : gl::enum_t
        {
            FirstVertex = GL_FIRST_VERTEX_CONVENTION, 
            LastVertex  = GL_LAST_VERTEX_CONVENTION, 
        };
        struct     Polygon
        {
            enum class Mode
            {
                Point = GL_POINT, 
                Line  = GL_LINE, 
                Fill  = GL_FILL, 
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
        struct     Memory
        {
            enum class Barrier : gl::bitfield_t
            {
                VertexAttributeArrayBarrier = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT,
                ElementArrayBarrier = GL_ELEMENT_ARRAY_BARRIER_BIT,
                UniformBarrier = GL_UNIFORM_BARRIER_BIT,
                TextureFetchBarrier = GL_TEXTURE_FETCH_BARRIER_BIT,
                ShaderImageAccessBarrier = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
                CommandBarrier = GL_COMMAND_BARRIER_BIT,
                PixelBufferBarrier = GL_PIXEL_BUFFER_BARRIER_BIT,
                TextureUpdateBarrier = GL_TEXTURE_UPDATE_BARRIER_BIT,
                BufferUpdateBarrier = GL_BUFFER_UPDATE_BARRIER_BIT,
                FrameBufferBarrier = GL_FRAMEBUFFER_BARRIER_BIT,
                TransformFeedbackBarrier = GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
                AtomicCounterBarrier = GL_ATOMIC_COUNTER_BARRIER_BIT,
                ShaderStorageBarrier = GL_SHADER_STORAGE_BARRIER_BIT,
                QueryBufferBarrier = GL_QUERY_BUFFER_BARRIER_BIT,
                AllBarrierBits = GL_ALL_BARRIER_BITS,
            };
        };
    };
}
