#pragma once

#include "stdafx.hpp"

#include "Helix/IO/IO.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexArray.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLVertexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLIndexBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLUniformArrayBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLFrameBufferMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBuffer.hpp"
#include "Helix/Rendering/API/OpenGL/Buffer/OpenGLRenderBufferMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLShader.hpp"
#include "Helix/Rendering/API/OpenGL/Shader/OpenGLPipeline.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2D.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLTexture2DMultisample.hpp"
#include "Helix/Rendering/API/OpenGL/Texture/OpenGLCubemapTexture.hpp"

namespace hlx::gfx
{
    inline std::shared_ptr<VertexArray>            create_vertex_array()
    {
        return std::make_shared<OpenGLVertexArray>();
    }
    inline std::shared_ptr<VertexBuffer>           create_vertex_buffer(size_t size)
    {
        return std::make_shared<OpenGLVertexBuffer>(size);
    }
    template<typename T>
    inline std::shared_ptr<VertexBuffer>           create_vertex_buffer(std::span<const T> data)
    {
        return std::make_shared<OpenGLVertexBuffer>(utl::as_bytes(data));
    }
    inline std::shared_ptr<IndexBuffer>            create_index_buffer(unsigned int count)
    {
        return std::make_shared<OpenGLIndexBuffer>(count);
    }
    inline std::shared_ptr<IndexBuffer>            create_index_buffer(std::span<const unsigned int> data)
    {
        return std::make_shared<OpenGLIndexBuffer>(data);
    }

    template<typename T>
    inline std::shared_ptr<UniformBuffer<T>>       create_uniform_buffer(unsigned int binding)
    {
        return std::make_shared<OpenGLUniformBuffer<T>>(binding);
    }
    template<typename T>
    inline std::shared_ptr<UniformBuffer<T>>       create_uniform_buffer(unsigned int binding, const T& data)
    {
        return std::make_shared<OpenGLUniformBuffer<T>>(binding, data);
    }
    template<typename T>
    inline std::shared_ptr<UniformArrayBuffer<T>>  create_uniform_array_buffer(unsigned int binding, unsigned int count)
    {
        return std::make_shared<OpenGLUniformArrayBuffer<T>>(binding, count);
    }
    template<typename T>
    inline std::shared_ptr<UniformArrayBuffer<T>>  create_uniform_array_buffer(unsigned int binding, std::span<const T> data)
    {
        return std::make_shared<OpenGLUniformArrayBuffer<T>>(binding, data);
    }

    inline std::shared_ptr<FrameBuffer>            create_framebuffer(const Vector2u& dimensions, std::span<const FrameBuffer::TextureManifest> textureManifest, std::span<const FrameBuffer::RenderBufferManifest> renderBufferManifest)
    {
        return std::make_shared<OpenGLFrameBuffer>(dimensions, textureManifest, renderBufferManifest);
    }
    inline std::shared_ptr<FrameBufferMultisample> create_framebuffer_multisample(const Vector2u& dimensions, unsigned int samples, std::span<const FrameBuffer::TextureManifest> textureManifest, std::span<const FrameBuffer::RenderBufferManifest> renderBufferManifest)
    {
        return std::make_shared<OpenGLFrameBufferMultisample>(dimensions, samples, textureManifest, renderBufferManifest);
    }
    inline std::shared_ptr<RenderBuffer>           create_renderbuffer(RenderBuffer::Format format, const Vector2u& dimensions)
    {
        return std::make_shared<OpenGLRenderBuffer>(format, dimensions);
    }
    inline std::shared_ptr<RenderBuffer>           create_renderbuffer_multisample(RenderBuffer::Format format, const Vector2u& dimensions, unsigned int samples)
    {
        return std::make_shared<OpenGLRenderBufferMultisample>(format, dimensions, samples);
    }

    inline std::shared_ptr<Shader>                 create_shader(Shader::Stage stage, std::span<const byte> binary)
    {
        return std::make_shared<OpenGLShader>(stage, binary);
    }
    inline std::shared_ptr<Pipeline>               create_pipeline()
    {
        return std::make_shared<OpenGLPipeline>();
    }
    inline std::shared_ptr<Pipeline>               create_pipeline(std::initializer_list<const std::shared_ptr<Shader>> shaders)
    {
        return std::make_shared<OpenGLPipeline>(shaders);
    }
    inline std::shared_ptr<Pipeline>               create_pipeline(const std::string& vertexPath, const std::string& fragmentPath)
    {
        const auto& vertexSource = IO::load<File>(vertexPath)->read();
        const auto& fragmentSource = IO::load<File>(fragmentPath)->read();
        const auto& vertexShader = create_shader(Shader::Stage::Vertex, std::span{ *vertexSource });
        const auto& fragmentShader = create_shader(Shader::Stage::Fragment, std::span{ *fragmentSource });

        return create_pipeline({ vertexShader, fragmentShader });
    }

    inline std::shared_ptr<Texture2D>              create_texture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const Vector2u& dimensions)
    {
        return std::make_shared<OpenGLTexture2D>(format, filter, wrapping, dimensions);
    }
    template<typename T>
    inline std::shared_ptr<Texture2D>              create_texture(Texture::Format format, Texture::Filter filter, Texture::Wrapping wrapping, const Vector2u& dimensions, Texture::Components components, std::span<const T> data)
    {
        return std::make_shared<OpenGLTexture2D>(format, filter, wrapping, dimensions, components, utl::as_bytes(data));
    }
    inline std::shared_ptr<Texture2DMultisample>   create_texture_multisample(Texture::Format format, const Vector2u& dimensions, unsigned int samples)
    {
        return std::make_shared<OpenGLTexture2DMultisample>(format, dimensions, samples);
    }
}
