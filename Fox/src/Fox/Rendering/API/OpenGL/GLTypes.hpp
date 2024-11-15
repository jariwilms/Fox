#include <stdafx.hpp>

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace fox::gfx::api::gl
{
    using bool_t     = GLboolean;
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
    using char_t     = GLchar;
    using size_t     = GLsizei;
    using sizeptr_t  = GLsizeiptr;
    using intptr_t   = GLintptr;
    using enum_t     = GLenum;
    using bitfield_t = GLbitfield;
    using sync_t     = GLsync;

    enum class handle_t : uint32_t {};
    enum class query_t  : uint32_t {};

    
    
    enum : bool_t
    {
        False = GL_FALSE,
        True  = GL_TRUE,
    };
    enum : uint32_t
    {
        NullObject = uint32_t{}
    };



    struct Object
    {
    public:
        handle_t handle() const
        {
            return m_handle;
        }

    protected:
        handle_t m_handle{};
    };

    struct Buffer
    {
        enum       Mask : bitfield_t
        {
            ColorBuffer   = GL_COLOR_BUFFER_BIT,
            DepthBuffer   = GL_DEPTH_BUFFER_BIT,
            StencilBuffer = GL_STENCIL_BUFFER_BIT,

            All = ColorBuffer | DepthBuffer | StencilBuffer
        };
        enum class Access : enum_t
        {
            Read      = GL_READ_ONLY,
            Write     = GL_WRITE_ONLY,
            ReadWrite = GL_READ_WRITE,
        };
        enum class Target : enum_t
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
        enum class TargetBase : enum_t
        {
            AtomicCounterBuffer     = GL_ATOMIC_COUNTER_BUFFER,
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
            UniformBuffer           = GL_UNIFORM_BUFFER,
            ShaderStorageBuffer     = GL_SHADER_STORAGE_BUFFER,
        };
        enum class TargetRange : enum_t
        {
            TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
            UniformBuffer           = GL_UNIFORM_BUFFER,
        };
        enum       StorageFlags : bitfield_t
        {
            DynamicStorage = GL_DYNAMIC_STORAGE_BIT,
            MapRead        = GL_MAP_READ_BIT,
            MapWrite       = GL_MAP_WRITE_BIT,
            MapPersistent  = GL_MAP_PERSISTENT_BIT,
            MapCoherent    = GL_MAP_COHERENT_BIT,
            ClientStorage  = GL_CLIENT_STORAGE_BIT,
        };
    };
    struct Query
    {
        enum class Mode : enum_t
        {
            QueryWait,
            QueryNoWait,
            QueryRegionWait,
            QueryRegionNoWait,
        };
    };
}