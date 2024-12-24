#pragma once

#include <stdafx.hpp>

#include "glad/glad.h"
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
    using f16_t      = GLhalf;
    using f32_t      = GLfloat;
    using f64_t      = GLdouble;

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

        gl::handle_t m_handle{};
    };

    struct Flags
    {
        struct     Blending
        {
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
        enum       Context : gl::enum_t
        {
            ForwardCompatibleBit = GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT, 
            DebugBit             = GL_CONTEXT_FLAG_DEBUG_BIT, 
            RobustAccessBit      = GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT,
            NoErrorBit           = GL_CONTEXT_FLAG_NO_ERROR_BIT,
        };
        enum class Data : gl::enum_t
        {
            MajorVersion         = GL_MAJOR_VERSION, 
            MinorVersion         = GL_MINOR_VERSION, 
            ContextFlags         = GL_CONTEXT_FLAGS, 
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
        enum class FaceCulling : gl::enum_t
        {
            Front     = GL_FRONT, 
            Back      = GL_BACK, 
            FrontBack = GL_FRONT_AND_BACK, 
        };
        struct     FrameBuffer
        {
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
                DepthStencilMode    = GL_DEPTH_STENCIL_TEXTURE_MODE, 
                BaseLevel           = GL_TEXTURE_BASE_LEVEL, 
                CompareFunction     = GL_TEXTURE_COMPARE_FUNC, 
                CompareMode         = GL_TEXTURE_COMPARE_MODE, 
                LODBias             = GL_TEXTURE_LOD_BIAS, 
                MinificationFilter  = GL_TEXTURE_MIN_FILTER, 
                MagnificationFilter = GL_TEXTURE_MAG_FILTER, 
                MinimumLOD          = GL_TEXTURE_MIN_LOD, 
                MaximumLOD          = GL_TEXTURE_MAX_LOD, 
                MaximumLevel        = GL_TEXTURE_MAX_LEVEL, 
                SwizzleRed          = GL_TEXTURE_SWIZZLE_R, 
                SwizzleGreen        = GL_TEXTURE_SWIZZLE_G,
                SwizzleBlue         = GL_TEXTURE_SWIZZLE_B,
                SwizzleAlpha        = GL_TEXTURE_SWIZZLE_A,
                WrappingS           = GL_TEXTURE_WRAP_S, 
                WrappingT           = GL_TEXTURE_WRAP_T, 
                WrappingR           = GL_TEXTURE_WRAP_R, 
            };
        };
        struct     Query
        {
            enum class Mode : gl::enum_t
            {
                QueryNoWait,
                QueryRegionNoWait,
                QueryRegionWait,
                QueryWait,
            };
        };
    };
}
