#pragma once

#include "stdafx.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Helix/Rendering/Buffer/Buffer.hpp"
#include "Helix/Rendering/Buffer/RenderBuffer.hpp"
#include "Helix/Rendering/Buffer/FrameBuffer.hpp"
#include "Helix/Rendering/Shader/Shader.hpp"
#include "Helix/Rendering/Texture/Texture.hpp"

namespace hlx
{
    class OpenGL
    {
    public:
        static GLenum                type_enum(size_t tHash)                   //Typeid compile vs runtime shenanigans
        {
            if (tHash == typeid(char)          .hash_code()) return GL_BYTE;
            if (tHash == typeid(unsigned char) .hash_code()) return GL_UNSIGNED_BYTE;
            if (tHash == typeid(short)         .hash_code()) return GL_SHORT;
            if (tHash == typeid(unsigned short).hash_code()) return GL_UNSIGNED_SHORT;
            if (tHash == typeid(int)           .hash_code()) return GL_INT;
            if (tHash == typeid(unsigned int)  .hash_code()) return GL_UNSIGNED_INT;
            if (tHash == typeid(float)         .hash_code()) return GL_FLOAT;
            if (tHash == typeid(double)        .hash_code()) return GL_DOUBLE;

            throw std::invalid_argument{ "Invalid type!" };
        }
        static GLsizei               type_size(size_t tHash)
        {
            if (tHash == typeid(char)              .hash_code()) return sizeof(GLbyte);
            if (tHash == typeid(unsigned char)     .hash_code()) return sizeof(GLubyte);
            if (tHash == typeid(short)             .hash_code()) return sizeof(GLshort);
            if (tHash == typeid(unsigned short)    .hash_code()) return sizeof(GLushort);
            if (tHash == typeid(int)               .hash_code()) return sizeof(GLint);
            if (tHash == typeid(unsigned int)      .hash_code()) return sizeof(GLuint);
            if (tHash == typeid(long long)         .hash_code()) return sizeof(GLint64);
            if (tHash == typeid(unsigned long long).hash_code()) return sizeof(GLuint64);
            if (tHash == typeid(float)             .hash_code()) return sizeof(GLfloat);
            if (tHash == typeid(double)            .hash_code()) return sizeof(GLdouble);

            throw std::invalid_argument{ "Invalid type!" };
        }
        static constexpr GLsizei     type_size(GLenum type)
        {
            switch (type)
            {
                case GL_BOOL:		   return sizeof(GLboolean);
                case GL_INT:		   return sizeof(GLint);
                case GL_FLOAT:		   return sizeof(GLfloat);

                case GL_UNSIGNED_INT:  return sizeof(GLuint);
                case GL_UNSIGNED_BYTE: return sizeof(GLbyte);

                default:			   throw std::invalid_argument{ "Invalid type!" };
            }
        }

        static constexpr GLenum      texture_format(Texture::Format format)
        {
            switch (format)
            {
                case Texture::Format::R:	return GL_RED;
                case Texture::Format::RG:	return GL_RG;
                case Texture::Format::RGB:	return GL_RGB;
                case Texture::Format::RGBA:	return GL_RGBA;

                case Texture::Format::D:    return GL_DEPTH_COMPONENT; //TODO: this does not work prob

                default:			        throw std::invalid_argument{ "Invalid format!" };
            }
        }
        static constexpr GLenum      texture_layout(Texture::Format format, Texture::ColorDepth colorDepth, bool sRGB = false)
        {
            switch (colorDepth)
            {
                case Texture::ColorDepth::_8bit:
                {
                    switch (format)
                    {
                        case Texture::Format::R:    return GL_R8;
                        case Texture::Format::RG:   return GL_RG8;
                        case Texture::Format::RGB:  
                        {
                            if (sRGB) return GL_SRGB8;
                            else      return GL_RGB8;
                        }
                        case Texture::Format::RGBA: 
                        {
                            if (sRGB) return GL_SRGB8_ALPHA8;
                            else      return GL_RGBA8;
                        }

                        case Texture::Format::D:    return GL_DEPTH_COMPONENT;

                        default: throw std::invalid_argument{ "Invalid format!" };
                    }
                }
                case Texture::ColorDepth::_16bit:
                {
                    switch (format)
                    {
                        case Texture::Format::R:    return GL_R16F;
                        case Texture::Format::RG:   return GL_RG16F;
                        case Texture::Format::RGB:  return GL_RGB16F;
                        case Texture::Format::RGBA: return GL_RGBA16F;

                        case Texture::Format::D:    return GL_DEPTH_COMPONENT16;

                        default: throw std::invalid_argument{ "Invalid format!" };
                    }
                }
                case Texture::ColorDepth::_24bit:
                {
                    switch (format)
                    {
                        case Texture::Format::D:  return GL_DEPTH_COMPONENT24;
                        case Texture::Format::DS: return GL_DEPTH24_STENCIL8;
                        
                        default: throw std::invalid_argument{ "Invalid format!" };
                    }
                }
                case Texture::ColorDepth::_32bit:
                {
                    switch (format)
                    {
                        case Texture::Format::R:    return GL_R32F;
                        case Texture::Format::RG:   return GL_RG32F;
                        case Texture::Format::RGB:  return GL_RGB32F;
                        case Texture::Format::RGBA: return GL_RGBA32F;

                        case Texture::Format::D:    return GL_DEPTH_COMPONENT32;

                        default: throw std::invalid_argument{ "Invalid format!" };
                    }
                }

                default: throw std::invalid_argument{ "Invalid color depth!" };
            }
        }
        static constexpr GLenum      texture_wrapping(Texture::Wrapping wrapping)
        {
            switch (wrapping)
            {
                case Texture::Wrapping::ClampToEdge:		 return GL_CLAMP_TO_EDGE;
                case Texture::Wrapping::ClampToBorder:		 return GL_CLAMP_TO_BORDER;
                                                             
                case Texture::Wrapping::MirroredRepeat:		 return GL_MIRRORED_REPEAT;
                case Texture::Wrapping::Repeat:              return GL_REPEAT;
                case Texture::Wrapping::MirroredClampToEdge: return GL_MIRROR_CLAMP_TO_EDGE;
                                                             
                default:									 throw std::invalid_argument{ "Invalid wrapping!" };
            }
        }
        static constexpr GLenum      texture_min_filter(Texture::Filter filter)
        {
            switch (filter)
            {
                case Texture::Filter::Point:     return GL_NEAREST_MIPMAP_NEAREST;
                case Texture::Filter::Bilinear:  return GL_LINEAR;
                case Texture::Filter::Trilinear: return GL_LINEAR_MIPMAP_LINEAR;

                default:                         throw std::invalid_argument{ "Invalid filter!" };
            }
        }
        static constexpr GLenum      texture_mag_filter(Texture::Filter filter)
        {
            switch (filter)
            {
                case Texture::Filter::Point:     return GL_NEAREST;
                case Texture::Filter::Bilinear:  return GL_LINEAR;
                case Texture::Filter::Trilinear: return GL_LINEAR;

                default:                         throw std::invalid_argument{ "Invalid filter!" };
            }
        }

        static constexpr GLenum      renderbuffer_type(RenderBuffer::Type type)
        {
            switch (type)
            {
                case RenderBuffer::Type::Color:		   return GL_COLOR_ATTACHMENT0;
                case RenderBuffer::Type::Depth:		   return GL_DEPTH_ATTACHMENT;
                case RenderBuffer::Type::Stencil:	   return GL_STENCIL_ATTACHMENT;
                case RenderBuffer::Type::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;

                default:                               throw std::invalid_argument{ "Invalid type!" };
            }
        }
        static constexpr GLenum      renderbuffer_layout(RenderBuffer::Layout colorDepth)
        {
            switch (colorDepth)
            {
                case RenderBuffer::Layout::R8:              return GL_R8;
                case RenderBuffer::Layout::RG8:             return GL_RG8;
                case RenderBuffer::Layout::RGB8:            return GL_RGB8;
                case RenderBuffer::Layout::RGBA8:           return GL_RGBA8;
                case RenderBuffer::Layout::Depth16:         return GL_DEPTH_COMPONENT16;
                case RenderBuffer::Layout::Depth24:			return GL_DEPTH_COMPONENT24;
                case RenderBuffer::Layout::Depth32:			return GL_DEPTH_COMPONENT32;
                case RenderBuffer::Layout::Depth24Stencil8: return GL_DEPTH24_STENCIL8;
                case RenderBuffer::Layout::Depth32Stencil8:	return GL_DEPTH32F_STENCIL8;
                case RenderBuffer::Layout::Stencil8:		return GL_STENCIL_INDEX8;

                default:                                    throw std::invalid_argument{ "Invalid layout!" };
            }
        }
        static constexpr GLenum      framebuffer_target(FrameBuffer::Target target)
        {
            switch (target)
            {
                case FrameBuffer::Target::Default: return GL_FRAMEBUFFER;
                case FrameBuffer::Target::Read:	   return GL_READ_FRAMEBUFFER;
                case FrameBuffer::Target::Write:   return GL_DRAW_FRAMEBUFFER;

                default:                           throw std::invalid_argument{ "Invalid target!" };
            }
        }
        static constexpr GLenum      framebuffer_attachment(FrameBuffer::Attachment attachment)
        {
            switch (attachment)
            {
                case FrameBuffer::Attachment::Color:        return GL_COLOR_ATTACHMENT0;
                case FrameBuffer::Attachment::Depth:        return GL_DEPTH_ATTACHMENT;
                case FrameBuffer::Attachment::Stencil:      return GL_STENCIL_ATTACHMENT;
                case FrameBuffer::Attachment::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;

                default:                                    throw std::invalid_argument{ "Invalid attachment!" };
            }
        }

        static constexpr GLenum      shader_type(Shader::Type type)
        {
            switch (type)
            {
                case Shader::Type::Vertex:                 return GL_VERTEX_SHADER;
                case Shader::Type::TessellationControl:    return GL_TESS_CONTROL_SHADER;
                case Shader::Type::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER;
                case Shader::Type::Geometry:               return GL_GEOMETRY_SHADER;
                case Shader::Type::Fragment:			   return GL_FRAGMENT_SHADER;
                case Shader::Type::Compute:				   return GL_COMPUTE_SHADER;

                default:                                   throw std::invalid_argument{ "Invalid type!" };
            }
        }
        static constexpr GLenum      shader_stage(Shader::Type stage)
        {
            switch (stage)
            {
                case Shader::Type::Vertex:                 return GL_VERTEX_SHADER_BIT;
                case Shader::Type::TessellationControl:    return GL_TESS_CONTROL_SHADER_BIT;
                case Shader::Type::TessellationEvaluation: return GL_TESS_EVALUATION_SHADER_BIT;
                case Shader::Type::Geometry:               return GL_GEOMETRY_SHADER_BIT;
                case Shader::Type::Fragment:			   return GL_FRAGMENT_SHADER_BIT;
                case Shader::Type::Compute:				   return GL_COMPUTE_SHADER_BIT;

                default:                                   throw std::invalid_argument{ "Invalid type!" };
            }
        }
        static constexpr GLint       shader_parameter(GLuint shader, GLenum parameter)
        {
            GLint result{};
            glGetShaderiv(shader, parameter, &result);

            return result;
        }
        static constexpr std::string shader_infolog(GLuint shader)
        {
            std::string infolog{};
            GLsizei length = shader_parameter(shader, GL_INFO_LOG_LENGTH);
            GLsizei bufSize{length};

            infolog.resize(length);
            glGetShaderInfoLog(shader, bufSize, nullptr, infolog.data());

            return infolog;
        }

        static constexpr GLint       program_parameter(GLuint program, GLenum parameter)
        {
            GLint result{};
            glGetProgramiv(program, parameter, &result);

            return result;
        }
        static constexpr GLint       program_uniform_location(Id shaderId, const std::string& identifier)
        {
            return glGetUniformLocation(shaderId, identifier.c_str());
        }
        static constexpr std::string program_infolog(GLuint program)
        {
            std::string infolog{};
            GLsizei length = program_parameter(program, GL_INFO_LOG_LENGTH);
            GLsizei bufSize{ length };

            infolog.resize(length);
            glGetProgramInfoLog(program, bufSize, nullptr, infolog.data());

            return infolog;
        }
    };
}
