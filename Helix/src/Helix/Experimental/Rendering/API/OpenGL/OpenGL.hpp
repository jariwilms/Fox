#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Experimental/Rendering/Buffer/Buffer.hpp"
#include "Helix/Experimental/Rendering/Texture/Texture.hpp"

namespace hlx::gfx::api::gl
{
    void init()
    {
        //query max available texture slots => check that slot does not exceed limit in bind_texture();
    }

    template<typename T>
    constexpr GLenum      type_enum()
    {
        if constexpr (std::is_same_v<T, char>)           return GL_BYTE;
        if constexpr (std::is_same_v<T, unsigned char>)  return GL_UNSIGNED_BYTE;
        if constexpr (std::is_same_v<T, short>)          return GL_SHORT;
        if constexpr (std::is_same_v<T, unsigned short>) return GL_UNSIGNED_SHORT;
        if constexpr (std::is_same_v<T, int>)            return GL_INT;
        if constexpr (std::is_same_v<T, unsigned int>)   return GL_UNSIGNED_INT;
        if constexpr (std::is_same_v<T, float>)          return GL_FLOAT;
        if constexpr (std::is_same_v<T, double>)         return GL_DOUBLE;

        throw std::invalid_argument{ "Invalid type!" };
    }
    template<typename T>
    constexpr GLsizei     type_size()
    {
        if constexpr (std::is_same_v<T, char>)               return sizeof(GLbyte);
        if constexpr (std::is_same_v<T, unsigned char>)      return sizeof(GLubyte);
        if constexpr (std::is_same_v<T, short>)              return sizeof(GLshort);
        if constexpr (std::is_same_v<T, unsigned short>)     return sizeof(GLushort);
        if constexpr (std::is_same_v<T, int>)                return sizeof(GLint);
        if constexpr (std::is_same_v<T, unsigned int>)       return sizeof(GLuint);
        if constexpr (std::is_same_v<T, long long>)          return sizeof(GLint64);
        if constexpr (std::is_same_v<T, unsigned long long>) return sizeof(GLuint64);
        if constexpr (std::is_same_v<T, float>)              return sizeof(GLfloat);
        if constexpr (std::is_same_v<T, double>)             return sizeof(GLdouble);

        throw std::invalid_argument{ "Invalid type!" };
    }



    constexpr GLenum      texture_format(hlx::gfx::api::Texture::Format format)
    {
        switch (format)
        {
            case hlx::gfx::api::Texture::Format::R8_UNORM:          return GL_R8;
            case hlx::gfx::api::Texture::Format::RG8_UNORM:         return GL_RG8;
            case hlx::gfx::api::Texture::Format::RGB8_UNORM:        return GL_RGB8;
            case hlx::gfx::api::Texture::Format::RGBA8_UNORM:       return GL_RGBA8;
            case hlx::gfx::api::Texture::Format::R16_UNORM:         return GL_R16;
            case hlx::gfx::api::Texture::Format::RG16_UNORM:        return GL_RG16;
            case hlx::gfx::api::Texture::Format::RGB16_UNORM:       return GL_RGB16;
            case hlx::gfx::api::Texture::Format::RGBA16_UNORM:      return GL_RGBA16;
            case hlx::gfx::api::Texture::Format::R8_SNORM:          return GL_R8_SNORM;
            case hlx::gfx::api::Texture::Format::RG8_SNORM:         return GL_RG8_SNORM;
            case hlx::gfx::api::Texture::Format::RGB8_SNORM:        return GL_RGB8_SNORM;
            case hlx::gfx::api::Texture::Format::RGBA8_SNORM:       return GL_RGBA8_SNORM;
            case hlx::gfx::api::Texture::Format::R16_SNORM:         return GL_R16_SNORM;
            case hlx::gfx::api::Texture::Format::RG16_SNORM:        return GL_RG16_SNORM;
            case hlx::gfx::api::Texture::Format::RGB16_SNORM:       return GL_RGB16_SNORM;
            case hlx::gfx::api::Texture::Format::RGBA16_SNORM:      return GL_RGBA16_SNORM;
            case hlx::gfx::api::Texture::Format::R8_SRGB:           throw std::invalid_argument{ "This format is not supported in OpenGL!" };
            case hlx::gfx::api::Texture::Format::RG8_SRGB:          throw std::invalid_argument{ "This format is not supported in OpenGL!" };
            case hlx::gfx::api::Texture::Format::RGB8_SRGB:         return GL_SRGB8;
            case hlx::gfx::api::Texture::Format::RGBA8_SRGB:        return GL_SRGB8_ALPHA8;
            case hlx::gfx::api::Texture::Format::R16_SFLOAT:        return GL_R16F;
            case hlx::gfx::api::Texture::Format::RG16_SFLOAT:       return GL_RG16F;
            case hlx::gfx::api::Texture::Format::RGB16_SFLOAT:      return GL_RGB16F;
            case hlx::gfx::api::Texture::Format::RGBA16_SFLOAT:     return GL_RGBA16F;
            case hlx::gfx::api::Texture::Format::R32_SFLOAT:        return GL_R32F;
            case hlx::gfx::api::Texture::Format::RG32_SFLOAT:       return GL_RG32F;
            case hlx::gfx::api::Texture::Format::RGB32_SFLOAT:      return GL_RGB32F;
            case hlx::gfx::api::Texture::Format::RGBA32_SFLOAT:     return GL_RGBA32F;
            case hlx::gfx::api::Texture::Format::D16_UNORM:         return GL_DEPTH_COMPONENT16;
            case hlx::gfx::api::Texture::Format::D24_UNORM:         return GL_DEPTH_COMPONENT24;
            case hlx::gfx::api::Texture::Format::D32_FLOAT:         return GL_DEPTH_COMPONENT32F;
            case hlx::gfx::api::Texture::Format::D24_UNORM_S8_UINT: return GL_DEPTH24_STENCIL8;
            case hlx::gfx::api::Texture::Format::D32_FLOAT_S8_UINT: return GL_DEPTH32F_STENCIL8;
            case hlx::gfx::api::Texture::Format::S8_UINT:           return GL_STENCIL_INDEX8;

            default: throw std::invalid_argument{ "Invalid format!" };
        }
    }
    constexpr GLenum      texture_min_filter(hlx::gfx::api::Texture::Filter filter)
    {
        switch (filter)
        {
            case hlx::gfx::api::Texture::Filter::None:      return GL_NEAREST;
            case hlx::gfx::api::Texture::Filter::Point:     return GL_NEAREST_MIPMAP_NEAREST;
            case hlx::gfx::api::Texture::Filter::Bilinear:  return GL_LINEAR_MIPMAP_NEAREST;
            case hlx::gfx::api::Texture::Filter::Trilinear: return GL_LINEAR_MIPMAP_LINEAR;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    constexpr GLenum      texture_mag_filter(hlx::gfx::api::Texture::Filter filter)
    {
        switch (filter)
        {
            case hlx::gfx::api::Texture::Filter::None:      return GL_NEAREST;
            case hlx::gfx::api::Texture::Filter::Point:     return GL_NEAREST;
            case hlx::gfx::api::Texture::Filter::Bilinear:  return GL_LINEAR;
            case hlx::gfx::api::Texture::Filter::Trilinear: return GL_LINEAR;

            default: throw std::invalid_argument{ "Invalid filter!" };
        }
    }
    constexpr GLenum      texture_wrapping(hlx::gfx::api::Texture::Wrapping wrapping)
    {
        switch (wrapping)
        {
            case hlx::gfx::api::Texture::Wrapping::ClampToEdge:         return GL_CLAMP_TO_EDGE;
            case hlx::gfx::api::Texture::Wrapping::ClampToBorder:       return GL_CLAMP_TO_BORDER;
            case hlx::gfx::api::Texture::Wrapping::MirroredRepeat:      return GL_MIRRORED_REPEAT;
            case hlx::gfx::api::Texture::Wrapping::Repeat:              return GL_REPEAT;
            case hlx::gfx::api::Texture::Wrapping::MirroredClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;

            default: throw std::invalid_argument{ "Invalid wrapping!" };
        }
    }

    constexpr GLbitfield  buffer_usage(hlx::gfx::api::Buffer::Usage usage)
    {
        switch (usage)
        {
            case hlx::gfx::api::Buffer::Usage::Static:  return {};
            case hlx::gfx::api::Buffer::Usage::Dynamic: return GL_DYNAMIC_STORAGE_BIT;

            default: throw std::invalid_argument{ "Invalid usage!" };
        }
    }
    constexpr GLenum      buffer_target(hlx::gfx::api::Buffer::Type type)
    {
        switch (type)
        {
            case hlx::gfx::api::Buffer::Type::Vertex:  return GL_ARRAY_BUFFER;
            case hlx::gfx::api::Buffer::Type::Index:   return GL_ELEMENT_ARRAY_BUFFER;
            case hlx::gfx::api::Buffer::Type::Uniform: return GL_UNIFORM_BUFFER;

            default: throw std::invalid_argument{ "Invalid type!" };
        }
    }




    GLuint create_buffer()
    {
        GLuint id{};
        //glCreateBuffers(1, &id);

        return id;
    }
    void   delete_buffer(GLuint id)
    {
        //glDeleteBuffers(1, &id);
    }
    void   bind_buffer(GLuint id, hlx::gfx::api::Buffer::Type type)
    {
        const auto& target = buffer_target(type);
        //glBindBuffer(target, id);
    }
    template<typename T>
    void   buffer_storage(GLuint id, hlx::gfx::api::Buffer::Usage usage, std::span<const T> data) //TODO: storage types (STATIC, DYNAMIC ETC.)
    {
        const auto& flags = buffer_usage(usage);

        //glNamedBufferStorage(id, static_cast<GLsizeiptr>(data.size_bytes()), data.data(), flags);
    }
    void   buffer_storage(GLuint id, hlx::gfx::api::Buffer::Usage usage, size_t size) //TODO: storage types (STATIC, DYNAMIC ETC.)
    {
        const auto& flags = buffer_usage(usage);

        //glNamedBufferStorage(id, static_cast<GLsizeiptr>(size), nullptr, flags);
    }
    template<typename T>
    void   buffer_sub_data(GLuint id, size_t offset, std::span<const T> data)
    {
        //glNamedBufferSubData(id, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(data.size_bytes()), data.data());
    }









    GLuint create_texture(GLenum target)
    {
        GLuint id{};
        //glCreateTextures(target, 1, &id);

        return id;
    }
    void   delete_texture(GLuint id)
    {
        //glDeleteTextures(1, &id);
    }
    void   bind_texture(GLuint id, u32 slot)
    {
        //glBindTextureUnit(static_cast<GLuint>(slot), id);
    }
    void   texture_parameter(GLuint id, GLenum parameter, GLuint value)
    {
        //glTextureParameteri(id, parameter, value);
    }
    void   texture_storage_1d(GLuint id, GLenum format, const Vector1u& dimensions, GLsizei levels)
    {
        //glTextureStorage1D(id, levels, format, static_cast<GLsizei>(dimensions.x));
    }
    void   texture_storage_2d(GLuint id, GLenum format, const Vector2u& dimensions, GLsizei levels)
    {
        //glTextureStorage2D(id, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y));
    }
    void   texture_storage_3d(GLuint id, GLenum format, const Vector3u& dimensions, GLsizei levels)
    {
        //glTextureStorage3D(id, levels, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z));
    }
    void   texture_storage_2d_multisample(GLuint id, GLenum format, const Vector2u& dimensions, GLsizei samples)
    {
        //glTextureStorage2DMultisample(id, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), GL_TRUE);
    }
    void   texture_storage_3d_multisample(GLuint id, GLenum format, const Vector3u& dimensions, GLsizei samples)
    {
        //glTextureStorage3DMultisample(id, samples, format, static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), static_cast<GLsizei>(dimensions.z), GL_TRUE);
    }
    void   texture_sub_image_2d(GLuint id, GLenum format, const Vector2u& dimensions, const Vector2u& offset, GLuint level, const void* data)
    {
        //glTextureSubImage2D(id, level, static_cast<GLint>(offset.x), static_cast<GLint>(offset.y), static_cast<GLsizei>(dimensions.x), static_cast<GLsizei>(dimensions.y), format, GL_UNSIGNED_BYTE, data);
    }
}
