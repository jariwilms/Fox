#pragma once

#include "stdafx.hpp"

#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBufferMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLIndexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBufferMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformArrayBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLPipeline.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2DMultisample.hpp"
#include "Helix/Rendering/Buffer/UniformArrayBuffer.hpp"

namespace hlx
{
    class GraphicsAPI
    {
    public:
        static std::shared_ptr<VertexArray>            create_vao()
        {
            return std::make_shared<OpenGLVertexArray>();
        }
                                                       
        template<typename T>                           
        static std::shared_ptr<VertexBuffer<T>>        create_vbo(unsigned int count)
        {
            return std::make_shared<OpenGLVertexBuffer<T>>(count);
        }
        template<typename T>                           
        static std::shared_ptr<VertexBuffer<T>>        create_vbo(std::span<const T> data)
        {
            return std::make_shared<OpenGLVertexBuffer<T>>(data);
        }
        static std::shared_ptr<IndexBuffer>            create_ibo(unsigned int count)
        {
            return std::make_shared<OpenGLIndexBuffer>(count);
        }
        static std::shared_ptr<IndexBuffer>            create_ibo(std::span<const unsigned int> data)
        {
            return std::make_shared<OpenGLIndexBuffer>(data);
        }
        template<typename T>                           
        static std::shared_ptr<UniformBuffer<T>>       create_ubo(unsigned int binding)
        {
            return std::make_shared<OpenGLUniformBuffer<T>>(binding);
        }
        template<typename T>                           
        static std::shared_ptr<UniformBuffer<T>>       create_ubo(unsigned int binding, const T& data)
        {
            return std::make_shared<OpenGLUniformBuffer<T>>(binding, data);
        }
        template<typename T>                           
        static std::shared_ptr<UniformArrayBuffer<T>>  create_uba(unsigned int count, unsigned int binding)
        {
            return std::make_shared<OpenGLUniformArrayBuffer<T>>(count, binding);
        }
        template<typename T>                           
        static std::shared_ptr<UniformArrayBuffer<T>>  create_uba(unsigned int binding, std::span<const T> data)
        {
            return std::make_shared<OpenGLUniformArrayBuffer<T>>(binding, data);
        }
                                                       
        static std::shared_ptr<FrameBuffer>            create_fbo(const Vector2u& dimensions, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>>& renderBuffers)
        {
            return std::make_shared<OpenGLFrameBuffer>(dimensions, textures, renderBuffers);
        }
        static std::shared_ptr<FrameBufferMultisample> create_fbo_ms(const Vector2u& dimensions, unsigned int samples, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, TextureBlueprint>>& textures, const std::vector<std::tuple<std::string, FrameBuffer::Attachment, RenderBufferBlueprint>>& renderBuffers)
        {
            return std::make_shared<OpenGLFrameBufferMultisample>(dimensions, samples, textures, renderBuffers);
        }
        static std::shared_ptr<RenderBuffer>           create_rbo(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions)
        {
            return std::make_shared<OpenGLRenderBuffer>(type, layout, dimensions);
        }
        static std::shared_ptr<RenderBuffer>           create_rbo_ms(RenderBuffer::Type type, RenderBuffer::Layout layout, const Vector2u& dimensions, unsigned int multiSamples)
        {
            return std::make_shared<OpenGLRenderBufferMultisample>(type, layout, dimensions, multiSamples);
        }
                                                       
        static std::shared_ptr<Shader>                 create_sho(Shader::Type type, const std::span<const byte> binary)
        {
            return std::make_shared<OpenGLShader>(type, binary);
        }
        static std::shared_ptr<Pipeline>               create_plo()
        {
            return std::make_shared<OpenGLPipeline>();
        }
        static std::shared_ptr<Pipeline>               create_plo(std::initializer_list<const std::shared_ptr<Shader>> shaders)
        {
            return std::make_shared<OpenGLPipeline>(shaders);
        }
                                                       
        static std::shared_ptr<Texture2D>              create_tex(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels)
        {
            return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, mipLevels);
        }
        static std::shared_ptr<Texture2D>              create_tex(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, std::span<const byte> data)
        {
            return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, mipLevels, data);
        }
        static std::shared_ptr<Texture2D>              create_tex(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter)
        {
            return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, mipLevels, wrappingS, wrappingT, minFilter, magFilter);
        }
        static std::shared_ptr<Texture2D>              create_tex(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter, std::span<const byte> data)
        {
            return std::make_shared<OpenGLTexture2D>(format, layout, dimensions, mipLevels, wrappingS, wrappingT, minFilter, magFilter, data);
        }
                                                       
        static std::shared_ptr<Texture2DMultisample>   create_tex_ms(Texture::Format format, Texture::Layout layout, const Vector2u& dimensions, unsigned int mipLevels, unsigned int samples, Texture::Wrapping wrappingS, Texture::Wrapping wrappingT, Texture::MinFilter minFilter, Texture::MagFilter magFilter)
        {
            return std::make_shared<OpenGLTexture2DMultisample>(format, layout, dimensions, mipLevels, samples, wrappingS, wrappingT, minFilter, magFilter);
        }
    };
}
